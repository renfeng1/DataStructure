#include "ManualInputDialog.h"
#include <QHeaderView>
#include <QRandomGenerator>
#include <QKeyEvent>
#include <QDoubleSpinBox>

// 实现自定义样式类的drawControl方法
void CustomSpinBoxStyle::drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    // 使用标准绘制
    QProxyStyle::drawControl(element, option, painter, widget);
}

ManualInputDialog::ManualInputDialog(QWidget *parent)
    : QDialog(parent)
    , nodeCount(0)
    , graph(nullptr)
    , customStyle(new CustomSpinBoxStyle())
{
    setupUI();
    updateNodeTable();
}

ManualInputDialog::~ManualInputDialog()
{
    delete customStyle;
}

void ManualInputDialog::setupUI()
{
    // 设置窗口标题
    setWindowTitle("坐标输入图");
    setFixedSize(600, 500);

    // 设置样式表
    setStyleSheet(
        "QSpinBox, QDoubleSpinBox { " 
        "    border: 1px solid #dcdfe6; " 
        "    border-radius: 6px; " 
        "    padding: 8px 10px; "
        "    font-size: 16px; " 
        "    background-color: white; " 
        "    min-height: 40px; " 
        "    width: 100%; " 
        "}" 
        "QSpinBox:focus, QDoubleSpinBox:focus { " 
        "    border-color: #4285f4; " 
        "    outline: none; " 
        "    box-shadow: 0 0 0 2px rgba(66, 133, 244, 0.2); " 
        "}" 
        "QSpinBox::up-button, QSpinBox::down-button, " 
        "QDoubleSpinBox::up-button, QDoubleSpinBox::down-button { " 
        "    width: 0px; "
        "    height: 0px; "
        "    border: none; " 
        "    background-color: transparent; " 
        "    image: none; "
        "}"
    );

    // 创建主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 创建节点表格
    nodeTableWidget = new QTableWidget(this);
    nodeTableWidget->setColumnCount(3);
    QStringList headers;
    headers << "节点ID" << "X坐标" << "Y坐标";
    nodeTableWidget->setHorizontalHeaderLabels(headers);
    nodeTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    nodeTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    nodeTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    nodeTableWidget->verticalHeader()->setDefaultSectionSize(45);

    // 创建按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    addNodeBtn = new QPushButton("添加节点", this);
    removeNodeBtn = new QPushButton("删除选中节点", this);
    removeNodeBtn->setEnabled(false);

    buttonLayout->addWidget(addNodeBtn);
    buttonLayout->addWidget(removeNodeBtn);
    buttonLayout->addStretch();

    // 创建对话框按钮
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    // 添加所有组件到主布局
    mainLayout->addWidget(nodeTableWidget);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(buttonBox);

    // 连接信号和槽
    connect(addNodeBtn, &QPushButton::clicked, this, &ManualInputDialog::onAddNodeBtnClicked);
    connect(removeNodeBtn, &QPushButton::clicked, this, &ManualInputDialog::onRemoveNodeBtnClicked);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ManualInputDialog::onAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(nodeTableWidget, &QTableWidget::cellChanged, this, &ManualInputDialog::onTableCellChanged);
    connect(nodeTableWidget, &QTableWidget::itemSelectionChanged, [=]() {
        QList<QTableWidgetSelectionRange> ranges = nodeTableWidget->selectedRanges();
        removeNodeBtn->setEnabled(!ranges.isEmpty());
    });
}

void ManualInputDialog::onAddNodeBtnClicked()
{
    // 添加一行到节点表格
    int row = nodeTableWidget->rowCount();
    nodeTableWidget->insertRow(row);

    // 创建节点ID显示
    QLabel *idLabel = new QLabel(QString::number(row), nodeTableWidget);
    idLabel->setAlignment(Qt::AlignCenter);
    nodeTableWidget->setCellWidget(row, 0, idLabel);

    // 创建X坐标输入框
    QDoubleSpinBox *xSpinBox = new QDoubleSpinBox(nodeTableWidget);
    xSpinBox->setMinimum(-750.0);
    xSpinBox->setMaximum(750.0);
    xSpinBox->setDecimals(2);
    // 生成-700.0到700.0之间的随机值
    double xValue = -700.0 + QRandomGenerator::global()->bounded(1400.0);
    xSpinBox->setValue(xValue);
    xSpinBox->setStyle(customStyle);
    xSpinBox->installEventFilter(this);
    nodeTableWidget->setCellWidget(row, 1, xSpinBox);

    // 创建Y坐标输入框
    QDoubleSpinBox *ySpinBox = new QDoubleSpinBox(nodeTableWidget);
    ySpinBox->setMinimum(-550.0);
    ySpinBox->setMaximum(550.0);
    ySpinBox->setDecimals(2);
    // 生成-500.0到500.0之间的随机值
    double yValue = -500.0 + QRandomGenerator::global()->bounded(1000.0);
    ySpinBox->setValue(yValue);
    ySpinBox->setStyle(customStyle);
    ySpinBox->installEventFilter(this);
    nodeTableWidget->setCellWidget(row, 2, ySpinBox);

    // 记录新添加的节点
    Node node(xSpinBox->value(), ySpinBox->value());
    nodes.append(node);
    nodeCount++;

    // 连接信号以便实时更新
    connect(xSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=](double value) {
        nodes[row].setX(value);
    });
    connect(ySpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), [=](double value) {
        nodes[row].setY(value);
    });
    
    // 自动选中新添加的行
    nodeTableWidget->selectRow(row);
}

void ManualInputDialog::onRemoveNodeBtnClicked()
{
    // 获取选中的行
    QList<QTableWidgetSelectionRange> ranges = nodeTableWidget->selectedRanges();
    if (!ranges.isEmpty()) {
        int row = ranges.first().topRow();
        if (row >= 0 && row < nodeTableWidget->rowCount()) {
            // 从表格中删除行
            nodeTableWidget->removeRow(row);
            // 从节点列表中删除
            nodes.remove(row);
            nodeCount--;
            
            // 更新节点ID标签
            for (int i = row; i < nodeTableWidget->rowCount(); i++) {
                QLabel *idLabel = dynamic_cast<QLabel*>(nodeTableWidget->cellWidget(i, 0));
                if (idLabel) {
                    idLabel->setText(QString::number(i));
                }
            }
        }
    }
}

void ManualInputDialog::onAccepted()
{
    // 验证输入
    if (!validateInput()) {
        return;
    }

    // 创建图
    if (graph) {
        delete graph;
    }
    graph = new Graph(nodeCount);

    // 将节点转换为边，边的权重由欧几里得距离确定
    Node** nodeArray = new Node*[nodeCount];
    for (int i = 0; i < nodeCount; i++) {
        nodeArray[i] = new Node(nodes[i].getX(), nodes[i].getY());
    }
    
    // 使用外部函数NodesToEdges将节点转换为边
    NodesToEdges(*graph, nodeArray, nodeCount);
    
    // 释放节点数组
    for (int i = 0; i < nodeCount; i++) {
        delete nodeArray[i];
    }
    delete[] nodeArray;

    // 接受对话框
    accept();
}

bool ManualInputDialog::eventFilter(QObject *obj, QEvent *event)
{
    // 当点击输入框时，自动选中所在行
    if ((qobject_cast<QSpinBox*>(obj) || qobject_cast<QDoubleSpinBox*>(obj)) && event->type() == QEvent::MouseButtonPress) {
        // 查找输入框所在的行
        for (int row = 0; row < nodeTableWidget->rowCount(); ++row) {
            for (int col = 0; col < nodeTableWidget->columnCount(); ++col) {
                if (nodeTableWidget->cellWidget(row, col) == obj) {
                    nodeTableWidget->selectRow(row);
                    return QDialog::eventFilter(obj, event);
                }
            }
        }
    }
    
    // 其他事件继续处理
    return QDialog::eventFilter(obj, event);
}

void ManualInputDialog::onTableCellChanged(int row, int column)
{
    // 实时更新节点数据
    if (row < nodes.size() && (column == 1 || column == 2)) {
        QDoubleSpinBox *spinBox = dynamic_cast<QDoubleSpinBox*>(nodeTableWidget->cellWidget(row, column));
        if (spinBox) {
            double value = spinBox->value();
            if (column == 1) {
                nodes[row].setX(value);
            } else {
                nodes[row].setY(value);
            }
        }
    }
}

void ManualInputDialog::updateNodeTable()
{
    // 清除现有表格内容
    nodeTableWidget->setRowCount(0);
    nodes.clear();
    nodeCount = 0;
}

bool ManualInputDialog::validateInput()
{
    // 检查是否有节点
    if (nodes.isEmpty()) {
        QMessageBox::warning(this, "错误", "至少需要添加一个节点");
        return false;
    }

    // 检查是否有重复坐标的节点
    QSet<QString> coordSet;
    for (const Node &node : nodes) {
        QString key = QString("%1-%2").arg(node.getX()).arg(node.getY());
        if (coordSet.contains(key)) {
            QMessageBox::warning(this, "错误", "存在相同坐标的节点");
            return false;
        }
        coordSet.insert(key);
    }

    return true;
}

Graph *ManualInputDialog::getGraph()
{
    Graph *temp = graph;
    graph = nullptr;
    return temp;
}

QVector<Node> ManualInputDialog::getNodes() const
{
    return nodes;
}
