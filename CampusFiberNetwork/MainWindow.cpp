#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "GraphFileIO.h"
#include "ManualInputDialog.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
    , currentGraph(nullptr)
{
    ui->setupUi(this);
    
    // 设置图形视图
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);
    ui->graphicsView->setBackgroundBrush(QColor(240, 240, 240));
    
    // 设置窗口标题
    setWindowTitle("校园光纤网络铺设 - 最小生成树");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    if (currentGraph) {
        delete currentGraph;
    }
}

void MainWindow::on_randomGenerateBtn_clicked()
{
    // 获取参数
    int numNodes = ui->nodesSpinBox->value();
    int minEdges = ui->minEdgesSpinBox->value();
    int maxEdges = ui->maxEdgesSpinBox->value();
    int minWeight = ui->minWeightSpinBox->value();
    int maxWeight = ui->maxWeightSpinBox->value();
    
    // 计算最大可能的边数
    int maxPossibleEdges = numNodes * (numNodes - 1) / 2;
    
    // 参数验证
    if (minEdges < numNodes - 1) {
        QMessageBox::warning(this, "警告", "最小边数不能小于节点数-1，否则图无法连通");
        ui->minEdgesSpinBox->setValue(numNodes - 1);
        minEdges = numNodes - 1;
    }
    
    if (maxEdges > maxPossibleEdges) {
        QMessageBox::warning(this, "警告", QString("最大边数不能超过%1，已自动调整").arg(maxPossibleEdges));
        ui->maxEdgesSpinBox->setValue(maxPossibleEdges);
        maxEdges = maxPossibleEdges;
    }
    
    if (minEdges > maxEdges) {
        QMessageBox::warning(this, "警告", "最小边数不能大于最大边数");
        return;
    }
    
    if (minWeight > maxWeight) {
        QMessageBox::warning(this, "警告", "最小权值不能大于最大权值");
        return;
    }
    
    // 创建图
    if (currentGraph) {
        delete currentGraph;
    }
    currentGraph = new Graph(numNodes);
    
    // 生成随机边
    QRandomGenerator *generator = QRandomGenerator::global();
    
    // 首先确保图是连通的：生成一棵随机生成树
    for (int i = 1; i < numNodes; ++i) {
        // 随机选择一个已连接的节点
        int connectedNode = generator->bounded(i);
        int weight = generator->bounded(minWeight, maxWeight + 1);
        currentGraph->addEdge(connectedNode, i, weight);
    }
    
    // 然后生成剩余的边
    int currentEdgeCount = numNodes - 1;
    int targetEdgeCount = generator->bounded(minEdges, maxEdges + 1);
    
    // 生成所有可能的边对，然后随机选择
    QVector<QPair<int, int>> possibleEdges;
    for (int u = 0; u < numNodes; ++u) {
        for (int v = u + 1; v < numNodes; ++v) {
            if (!currentGraph->hasEdge(u, v)) {
                possibleEdges.append(qMakePair(u, v));
            }
        }
    }
    
    // 打乱可能的边顺序
    std::random_shuffle(possibleEdges.begin(), possibleEdges.end());
    
    // 添加剩余的边
    for (const auto &edge : possibleEdges) {
        if (currentEdgeCount >= targetEdgeCount) break;
        
        int weight = generator->bounded(minWeight, maxWeight + 1);
        currentGraph->addEdge(edge.first, edge.second, weight);
        currentEdgeCount++;
    }
    
    // 绘制图
    generateNodePositions(numNodes);
    drawGraph();
    
    QMessageBox::information(this, "成功", QString("随机生成了%1个节点、%2条边的连通图").arg(numNodes).arg(currentEdgeCount));
}

void MainWindow::on_fileInputBtn_clicked()
{
    // 文件输入图
    QString fileName = QFileDialog::getOpenFileName(this, "打开图文件", ".", "文本文件 (*.txt)");
    if (fileName.isEmpty()) return;
    
    // 读取文件
    GraphFileIO io(fileName.toStdString().c_str());
    Graph *graph = io.readGraphFromFile();
    if (graph == nullptr) {
        QMessageBox::warning(this, "错误", "文件读取失败");
        return;
    }
    
    // 更新当前图
    if (currentGraph) {
        delete currentGraph;
    }
    currentGraph = graph;
    
    // 绘制图
    generateNodePositions(currentGraph->getVertices());
    drawGraph();
    
    QMessageBox::information(this, "成功", QString("从文件读取了%1个节点的图").arg(currentGraph->getVertices()));
}

void MainWindow::on_manualInputBtn_clicked()
{
    // 使用新的人工输入对话框
    ManualInputDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        // 获取创建的图
        Graph *graph = dialog.getGraph();
        if (graph == nullptr) {
            QMessageBox::warning(this, "错误", "图创建失败");
            return;
        }
        
        // 更新当前图
        if (currentGraph) {
            delete currentGraph;
        }
        currentGraph = graph;
        
        // 绘制图
        generateNodePositions(currentGraph->getVertices());
        drawGraph();
        
        QMessageBox::information(this, "成功", QString("人工输入了%1个节点和%2条边的图").arg(currentGraph->getVertices()).arg(currentGraph->getEdgeCount()));
    }
}

void MainWindow::on_runKruskalBtn_clicked()
{
    if (!currentGraph) {
        QMessageBox::warning(this, "错误", "请先创建图");
        return;
    }
    
    // 运行Kruskal算法
    currentGraph->kruskalMST();
    
    // 重新绘制图
    drawGraph();
    
    // 高亮MST边
    highlightMSTEdges();
    
    QMessageBox::information(this, "成功", "Kruskal算法已执行，最小生成树边已高亮显示");
}

void MainWindow::drawGraph()
{
    if (!currentGraph) return;
    
    clearScene();
    
    int numNodes = currentGraph->getVertices();
    
    // 定义节点颜色列表 - 使用更鲜艳、更有区分度的颜色
    QList<QColor> nodeColors = {
        QColor(230, 25, 75), QColor(60, 180, 75), QColor(255, 225, 25), QColor(0, 130, 200),
        QColor(245, 130, 49), QColor(145, 30, 180), QColor(70, 240, 240), QColor(240, 50, 230),
        QColor(250, 190, 190), QColor(0, 128, 128), QColor(230, 255, 255), QColor(128, 0, 0),
        QColor(170, 255, 195), QColor(0, 0, 128), QColor(255, 216, 177), QColor(128, 128, 0),
        QColor(255, 250, 200), QColor(128, 0, 128), QColor(150, 255, 255), QColor(245, 166, 35)
    };
    
    // 绘制节点
    for (int i = 0; i < numNodes; ++i) {
        QPointF pos = nodePositions[i];
        
        // 选择节点颜色
        QColor nodeColor = nodeColors[i % nodeColors.size()];
        
        // 绘制节点
        QGraphicsEllipseItem *node = scene->addEllipse(pos.x() - 15, pos.y() - 15, 30, 30, 
            QPen(Qt::black, 2), QBrush(nodeColor));
        
        // 设置节点在顶层显示
        node->setZValue(1);
        
        // 添加节点标签（使用大写字母）
        QGraphicsTextItem *label = scene->addText(QString(QChar('A' + i)));
        QFont nodeFont("Arial", 12, QFont::Bold);
        label->setFont(nodeFont);
        
        // 计算标签位置，确保在节点中心
        QRectF labelRect = label->boundingRect();
        label->setPos(pos.x() - labelRect.width() / 2, pos.y() - labelRect.height() / 2);
        label->setDefaultTextColor(Qt::white);
        
        // 设置标签在节点上方
        label->setZValue(2);
        
        // 设置节点可选中
        node->setFlag(QGraphicsItem::ItemIsSelectable);
    }
    
    // 绘制边
    Edge** edges = currentGraph->getEdges();
    int edgeCount = currentGraph->getEdgeCount();
    
    for (int i = 0; i < edgeCount; ++i) {
        Edge* edge = edges[i];
        if (!edge) continue;
        
        int src = edge->getSrc();
        int dest = edge->getDest();
        int weight = edge->getWeight();
        
        QPointF srcPos = nodePositions[src];
        QPointF destPos = nodePositions[dest];
        
        // 计算边的方向向量
        double dx = destPos.x() - srcPos.x();
        double dy = destPos.y() - srcPos.y();
        double length = sqrt(dx * dx + dy * dy);
        
        // 定义节点半径
        double nodeRadius = 15.0;
        
        // 计算边在节点边缘的起始和结束点
        QPointF startPoint = srcPos + QPointF(dx * nodeRadius / length, dy * nodeRadius / length);
        QPointF endPoint = destPos - QPointF(dx * nodeRadius / length, dy * nodeRadius / length);
        
        // 绘制边
        QGraphicsLineItem *line = scene->addLine(startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y(), 
            QPen(Qt::black, 1));
        // 设置边在底层显示
        line->setZValue(0);
        
        // 添加权重标签
        QGraphicsTextItem *weightLabel = scene->addText(QString::number(weight));
        QFont weightFont("Arial", 10, QFont::Bold);
        weightLabel->setFont(weightFont);
        weightLabel->setDefaultTextColor(Qt::black);
        
        // 计算标签位置
        QRectF labelRect = weightLabel->boundingRect();
        QPointF midPos = (srcPos + destPos) / 2;
        
        // 垂直于边的单位向量
        QPointF normal(-dy / length, dx / length);
        
        // 调整标签位置，使其偏离边的中心，避免与边重叠
        QPointF offset = normal * 15; // 向垂直边的方向偏移15像素
        QPointF labelPos = midPos + offset;
        labelPos.setX(labelPos.x() - labelRect.width() / 2);
        labelPos.setY(labelPos.y() - labelRect.height() / 2);
        weightLabel->setPos(labelPos);
        
        // 为权重标签添加背景框
        QGraphicsRectItem *background = scene->addRect(labelPos.x() - 4, labelPos.y() - 2, 
            labelRect.width() + 8, labelRect.height() + 4, 
            QPen(Qt::NoPen), QBrush(Qt::yellow));
        // 将背景放在标签下方
        background->setZValue(-1);
        
        // 存储边对象
        QString key = QString("%1-%2").arg(src).arg(dest);
        this->edges[key] = line;
    }
    
    // 设置场景范围
    scene->setSceneRect(-50, -50, 900, 600);
}

void MainWindow::clearScene()
{
    scene->clear();
    edges.clear();
    mstEdges.clear();
}

void MainWindow::generateNodePositions(int numNodes)
{
    nodePositions.clear();
    
    // 生成圆形布局的节点位置
    qreal centerX = 400;
    qreal centerY = 300;
    qreal radius = qMin(350.0, qMin(ui->graphicsView->width(), ui->graphicsView->height()) * 0.4);
    
    for (int i = 0; i < numNodes; ++i) {
        qreal angle = 2 * M_PI * i / numNodes;
        qreal x = centerX + radius * cos(angle);
        qreal y = centerY + radius * sin(angle);
        nodePositions[i] = QPointF(x, y);
    }
}

void MainWindow::highlightMSTEdges()
{
    // 高亮MST边
    Edge** mstEdges = currentGraph->getMSTEdges();
    int mstEdgeCount = currentGraph->getMSTEdgeCount();
    
    for (int i = 0; i < mstEdgeCount; ++i) {
        Edge* edge = mstEdges[i];
        if (!edge) continue;
        
        QString key = QString("%1-%2").arg(edge->getSrc()).arg(edge->getDest());
        if (edges.contains(key)) {
            QGraphicsItem *item = edges[key];
            QGraphicsLineItem *line = dynamic_cast<QGraphicsLineItem*>(item);
            if (line) {
                line->setPen(QPen(Qt::red, 3));
            }
        }
    }
}

void MainWindow::resetEdgeColors()
{
    // 重置边颜色
    for (QGraphicsItem *item : edges.values()) {
        QGraphicsLineItem *line = dynamic_cast<QGraphicsLineItem*>(item);
        if (line) {
            line->setPen(QPen(Qt::black, 1));
        }
    }
}

qreal MainWindow::calculateDistance(const QPointF &p1, const QPointF &p2)
{
    return qSqrt(qPow(p2.x() - p1.x(), 2) + qPow(p2.y() - p1.y(), 2));
}

void MainWindow::on_actionOpen_Graph_File_triggered()
{
    // 打开图文件功能，与文件输入图按钮功能相同
    on_fileInputBtn_clicked();
}

void MainWindow::on_actionExit_triggered()
{
    // 退出应用程序
    close();
}

void MainWindow::on_actionAbout_triggered()
{
    // 显示关于对话框
    QMessageBox::about(this, "关于校园光纤网络铺设程序",
                       "校园光纤网络铺设程序\n\n" 
                       "基于Qt 6开发，使用Kruskal算法求解最小生成树\n" 
                       "功能包括：\n" 
                       "- 随机生成图\n" 
                       "- 从文件读取图\n" 
                       "- 人工输入图\n" 
                       "- 使用Kruskal算法求解最小生成树\n\n");
}
