#include "ManualInputDialog.h"
#include <QHeaderView>
#include <QRandomGenerator>
#include <QKeyEvent>

// 实现自定义样式类的drawControl方法
void CustomSpinBoxStyle::drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget) const
{
    // 使用标准绘制
    QProxyStyle::drawControl(element, option, painter, widget);
}

ManualInputDialog::ManualInputDialog(QWidget *parent)
    : QDialog(parent)
    , nodeCount(4)
    , graph(nullptr)
    , customStyle(new CustomSpinBoxStyle())
{
    setupUI();
    updateEdgeTable();
}

ManualInputDialog::~ManualInputDialog()
{
    delete customStyle;
}

void ManualInputDialog::setupUI()
{
    // 设置窗口标题
    setWindowTitle("人工输入图");
    setFixedSize(600, 500); // 增大窗口尺寸

    // 设置样式表，为QSpinBox应用与主窗口相同的样式，但移除上下按钮
    setStyleSheet(
        "QSpinBox { " 
        "    border: 1px solid #dcdfe6; " 
        "    border-radius: 6px; " 
        "    padding: 8px 10px; /* 减少右侧内边距，因为不再需要上下按钮 */" 
        "    font-size: 16px; " 
        "    background-color: white; " 
        "    min-height: 40px; /* 增加最小高度 */" 
        "    width: 100%; /* 让QSpinBox充满表格单元格 */" 
        "}" 
        "QSpinBox:focus { " 
        "    border-color: #4285f4; " 
        "    outline: none; " 
        "    box-shadow: 0 0 0 2px rgba(66, 133, 244, 0.2); " 
        "}" 
        "QSpinBox::up-button, QSpinBox::down-button { " 
        "    width: 0px; /* 将按钮宽度设为0，隐藏按钮 */" 
        "    height: 0px; /* 将按钮高度设为0，隐藏按钮 */" 
        "    border: none; " 
        "    background-color: transparent; " 
        "    image: none; "
        "    text-align: center; "
        "}"
    );

    // 创建主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 创建节点数量部分
    QHBoxLayout *nodeLayout = new QHBoxLayout();
    nodeLabel = new QLabel("节点数量：", this);
    nodeCountSpinBox = new QSpinBox(this);
    nodeCountSpinBox->setMinimum(2);
    nodeCountSpinBox->setMaximum(20);
    nodeCountSpinBox->setValue(nodeCount);
    nodeCountSpinBox->setFixedWidth(120); // 增大宽度，为上下按钮提供更多空间
    nodeCountSpinBox->setStyle(customStyle); // 应用自定义样式
    nodeCountSpinBox->installEventFilter(this); // 安装事件过滤器

    nodeLayout->addWidget(nodeLabel);
    nodeLayout->addWidget(nodeCountSpinBox);
    nodeLayout->addStretch();

    // 创建边表格
    edgeTableWidget = new QTableWidget(this);
    edgeTableWidget->setColumnCount(3);
    QStringList headers;
    headers << "源节点" << "目标节点" << "权重";
    edgeTableWidget->setHorizontalHeaderLabels(headers);
    edgeTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    edgeTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    edgeTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    edgeTableWidget->verticalHeader()->setDefaultSectionSize(45); // 增加行高，确保QSpinBox完整显示

    // 创建按钮布局
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    addEdgeBtn = new QPushButton("添加边", this);
    removeEdgeBtn = new QPushButton("删除选中边", this);
    removeEdgeBtn->setEnabled(false);

    buttonLayout->addWidget(addEdgeBtn);
    buttonLayout->addWidget(removeEdgeBtn);
    buttonLayout->addStretch();

    // 创建对话框按钮
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    // 添加所有组件到主布局
    mainLayout->addLayout(nodeLayout);
    mainLayout->addWidget(edgeTableWidget);
    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(buttonBox);

    // 连接信号和槽
    connect(nodeCountSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &ManualInputDialog::onNodeCountChanged);
    connect(addEdgeBtn, &QPushButton::clicked, this, &ManualInputDialog::onAddEdgeBtnClicked);
    connect(removeEdgeBtn, &QPushButton::clicked, this, &ManualInputDialog::onRemoveEdgeBtnClicked);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &ManualInputDialog::onAccepted);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    connect(edgeTableWidget, &QTableWidget::cellChanged, this, &ManualInputDialog::onTableCellChanged);
    connect(edgeTableWidget, &QTableWidget::itemSelectionChanged, [=]() {
        QList<QTableWidgetSelectionRange> ranges = edgeTableWidget->selectedRanges();
        removeEdgeBtn->setEnabled(!ranges.isEmpty());
    });
}

void ManualInputDialog::onNodeCountChanged(int count)
{
    nodeCount = count;
    updateEdgeTable();
}

void ManualInputDialog::onAddEdgeBtnClicked()
{
    // 添加一行到边表格
    int row = edgeTableWidget->rowCount();
    edgeTableWidget->insertRow(row);

    // 创建源节点选择器
    QSpinBox *srcSpinBox = new QSpinBox(edgeTableWidget);
    srcSpinBox->setMinimum(0);
    srcSpinBox->setMaximum(nodeCount - 1);
    srcSpinBox->setValue(QRandomGenerator::global()->bounded(nodeCount));
    srcSpinBox->setStyle(customStyle); // 应用自定义样式
    srcSpinBox->installEventFilter(this); // 安装事件过滤器
    edgeTableWidget->setCellWidget(row, 0, srcSpinBox);

    // 创建目标节点选择器
    QSpinBox *destSpinBox = new QSpinBox(edgeTableWidget);
    destSpinBox->setMinimum(0);
    destSpinBox->setMaximum(nodeCount - 1);
    destSpinBox->setValue(QRandomGenerator::global()->bounded(nodeCount));
    destSpinBox->setStyle(customStyle); // 应用自定义样式
    destSpinBox->installEventFilter(this); // 安装事件过滤器
    edgeTableWidget->setCellWidget(row, 1, destSpinBox);

    // 创建权重选择器
    QSpinBox *weightSpinBox = new QSpinBox(edgeTableWidget);
    weightSpinBox->setMinimum(1);
    weightSpinBox->setMaximum(100);
    weightSpinBox->setValue(QRandomGenerator::global()->bounded(1, 101));
    weightSpinBox->setStyle(customStyle); // 应用自定义样式
    weightSpinBox->installEventFilter(this); // 安装事件过滤器
    edgeTableWidget->setCellWidget(row, 2, weightSpinBox);

    // 记录新添加的边
    Edge edge(srcSpinBox->value(), destSpinBox->value(), weightSpinBox->value());
    edges.append(edge);

    // 连接信号以便实时更新
    connect(srcSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) {
        edges[row].setSrc(value);
    });
    connect(destSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) {
        edges[row].setDest(value);
    });
    connect(weightSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), [=](int value) {
        edges[row].setWeight(value);
    });
    
    // 自动选中新添加的行
    edgeTableWidget->selectRow(row);
}

void ManualInputDialog::onRemoveEdgeBtnClicked()
{
    // 获取选中的行
    QList<QTableWidgetSelectionRange> ranges = edgeTableWidget->selectedRanges();
    if (!ranges.isEmpty()) {
        int row = ranges.first().topRow();
        if (row >= 0 && row < edgeTableWidget->rowCount()) {
            // 从表格中删除行
            edgeTableWidget->removeRow(row);
            // 从边列表中删除
            edges.remove(row);
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

    // 添加所有边到图中
    for (const Edge &edge : edges) {
        graph->addEdge(edge.getSrc(), edge.getDest(), edge.getWeight());
    }

    // 检查图是否连通
    if (!graph->isConnected()) {
        QMessageBox::warning(this, "警告", "生成的图不连通，可能导致Kruskal算法无法正常工作。建议添加更多边确保图连通。");
    }

    // 接受对话框
    accept();
}

bool ManualInputDialog::eventFilter(QObject *obj, QEvent *event)
{
    // 检查是否是QSpinBox的键盘事件
    if (qobject_cast<QSpinBox*>(obj) && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        
        // 过滤掉会改变数值的按键
        switch (keyEvent->key()) {
        case Qt::Key_Up:
        case Qt::Key_Down:
        case Qt::Key_PageUp:
        case Qt::Key_PageDown:
        case Qt::Key_Home:
        case Qt::Key_End:
            // 返回true表示事件已处理，不会继续传播
            return true;
        default:
            break;
        }
    }
    
    // 当点击QSpinBox时，自动选中所在行
    if (qobject_cast<QSpinBox*>(obj) && event->type() == QEvent::MouseButtonPress) {
        // 查找QSpinBox所在的行
        for (int row = 0; row < edgeTableWidget->rowCount(); ++row) {
            for (int col = 0; col < edgeTableWidget->columnCount(); ++col) {
                if (edgeTableWidget->cellWidget(row, col) == obj) {
                    edgeTableWidget->selectRow(row);
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
    // 实时更新边数据
    if (row < edges.size()) {
        QSpinBox *spinBox = dynamic_cast<QSpinBox*>(edgeTableWidget->cellWidget(row, column));
        if (spinBox) {
            int value = spinBox->value();
            switch (column) {
            case 0:
                edges[row].setSrc(value);
                break;
            case 1:
                edges[row].setDest(value);
                break;
            case 2:
                edges[row].setWeight(value);
                break;
            }
        }
    }
}

void ManualInputDialog::updateEdgeTable()
{
    // 清除现有表格内容
    edgeTableWidget->setRowCount(0);
    edges.clear();

    // 初始化一些默认边
    for (int i = 0; i < qMin(nodeCount - 1, 3); ++i) {
        onAddEdgeBtnClicked();
    }
}

bool ManualInputDialog::validateInput()
{
    // 检查是否有边
    if (edges.isEmpty()) {
        QMessageBox::warning(this, "错误", "至少需要添加一条边");
        return false;
    }

    // 检查是否有重复边
    QSet<QString> edgeSet;
    for (const Edge &edge : edges) {
        QString key;
        if (edge.getSrc() < edge.getDest()) {
            key = QString("%1-%2").arg(edge.getSrc()).arg(edge.getDest());
        } else {
            key = QString("%1-%2").arg(edge.getDest()).arg(edge.getSrc());
        }
        if (edgeSet.contains(key)) {
            QMessageBox::warning(this, "错误", "存在重复的边");
            return false;
        }
        edgeSet.insert(key);
    }

    // 检查是否有自环边
    for (const Edge &edge : edges) {
        if (edge.getSrc() == edge.getDest()) {
            QMessageBox::warning(this, "错误", "存在自环边（源节点和目标节点相同）");
            return false;
        }
    }

    return true;
}

Graph *ManualInputDialog::getGraph()
{
    Graph *temp = graph;
    graph = nullptr;
    return temp;
}
