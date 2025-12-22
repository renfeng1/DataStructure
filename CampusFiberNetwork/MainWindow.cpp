#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "GraphFileIO.h"
#include "ManualInputDialog.h"
#include "Node.h"
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
#include <QWheelEvent>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , scene(new QGraphicsScene(this))
    , currentGraph(nullptr)
    , isAlgorithmExecuted(false)
    , currentScale(1.0)
{
    ui->setupUi(this);
    
    // 设置图形视图
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);
    ui->graphicsView->setBackgroundBrush(QColor(240, 240, 240));
    
    // 设置窗口标题
    setWindowTitle("校园光纤网络铺设 - 最小生成树");
    
    // 初始绘制坐标系
    drawGraph();
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
    
    // 创建图
    if (currentGraph) {
        delete currentGraph;
    }
    currentGraph = new Graph(numNodes);
    
    // 清空用户节点列表
    userNodes.clear();
    
    // 生成随机坐标的节点
    QRandomGenerator *generator = QRandomGenerator::global();
    
    // 创建Node数组
    Node** nodes = new Node*[numNodes];
    nodePositions.clear();
    
    // 设置场景中心为坐标原点
    qreal centerX = 400;
    qreal centerY = 300;
    
    // 生成随机坐标的节点（在扩大后的坐标系范围内）
    for (int i = 0; i < numNodes; ++i) {
        // 在X轴方向（-700到700，相对于原点，为了留一些边距）
        int x = generator->bounded(-700, 701);
        // 在Y轴方向（-500到500，相对于原点，为了留一些边距）
        int y = generator->bounded(-500, 501);
        
        // 添加到用户节点列表
        userNodes.append(QPointF(x, y));
        
        // 创建Node对象
        nodes[i] = new Node(x, y);
        
        // 计算节点在场景中的位置（转换为Qt坐标系）
        qreal sceneX = centerX + x;
        qreal sceneY = centerY - y; // Qt坐标系Y轴向下，需要反转
        
        // 存储节点位置
        nodePositions[i] = QPointF(sceneX, sceneY);
    }
    
    // 根据节点坐标自动生成边（使用欧氏距离作为权重）
    NodesToEdges(*currentGraph, nodes, numNodes);
    
    // 释放Node数组
    for (int i = 0; i < numNodes; ++i) {
        delete nodes[i];
    }
    delete[] nodes;
    
    // 绘制图
    drawGraph();
    
    // 重置算法执行标志
    isAlgorithmExecuted = false;
    
    // 重置最小生成树总权重标签
    ui->mstWeightLabel->setText("最小生成树总权重: 未计算");
    
    QMessageBox::information(this, "成功", QString("随机生成了%1个节点的连通图，边权值为节点间的欧氏距离").arg(numNodes));
}

void MainWindow::on_fileInputBtn_clicked()
{
    // 文件输入图
    QString fileName = QFileDialog::getOpenFileName(this, "打开图文件", ".", "文本文件 (*.txt)");
    if (fileName.isEmpty()) return;
    
    // 先读取节点数量
    int vertexCount = GraphFileIO::readVertexCountOnly(fileName.toStdString().c_str());
    if (vertexCount <= 0) {
        QMessageBox::warning(this, "错误", "无法读取节点数量或节点数量无效");
        return;
    }
    
    // 创建正确大小的图
    Graph *graph = new Graph(vertexCount);
    if (!GraphFileIO::readNodesAndBuildGraph(*graph, fileName.toStdString().c_str())) {
        QMessageBox::warning(this, "错误", "文件读取失败");
        delete graph;
        return;
    }
    
    // 更新当前图
    if (currentGraph) {
        delete currentGraph;
    }
    currentGraph = graph;
    
    // 重置算法执行标志
    isAlgorithmExecuted = false;
    
    // 重置最小生成树总权重标签
    ui->mstWeightLabel->setText("最小生成树总权重: 未计算");
    
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
        
        // 获取节点坐标
        QVector<Node> nodes = dialog.getNodes();
        
        // 设置节点位置
        nodePositions.clear();
        for (int i = 0; i < nodes.size(); ++i) {
            // 使用节点的实际坐标，但缩放以适应场景
            float x = nodes[i].getX() * 0.5;
            float y = nodes[i].getY() * 0.5;
            nodePositions.insert(i, QPointF(x, y));
        }
        
        // 重置算法执行标志
        isAlgorithmExecuted = false;
        
        // 重置最小生成树总权重标签
        ui->mstWeightLabel->setText("最小生成树总权重: 未计算");
        
        // 绘制图
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
    
    // 设置算法已执行标志
    isAlgorithmExecuted = true;
    
    // 更新最小生成树总权重标签
    double totalWeight = currentGraph->getMSTTotalWeight();
    ui->mstWeightLabel->setText(QString("最小生成树总权重: %1").arg(totalWeight));
    
    QMessageBox::information(this, "成功", "Kruskal算法已执行，最小生成树边已高亮显示");
}

void MainWindow::drawGraph()
{
    clearScene();
    
    // 设置坐标轴原点（场景中心）
    qreal centerX = 400;
    qreal centerY = 300;
    
    // 扩大坐标系范围
    qreal extendedRangeX = 750; // X轴从-750到750
    qreal extendedRangeY = 550; // Y轴从-550到550
    
    // 绘制坐标轴
    // X轴（扩大到-750到750相对于原点）
    QGraphicsLineItem *xAxis = scene->addLine(centerX - extendedRangeX, centerY, centerX + extendedRangeX, centerY, QPen(Qt::black, 2));
    xAxis->setZValue(-2); // 放在底层
    
    // Y轴（扩大到-550到550相对于原点）
    QGraphicsLineItem *yAxis = scene->addLine(centerX, centerY - extendedRangeY, centerX, centerY + extendedRangeY, QPen(Qt::black, 2));
    yAxis->setZValue(-2); // 放在底层
    
    // 绘制坐标轴箭头
    // X轴箭头
    QGraphicsLineItem *xArrow1 = scene->addLine(centerX + extendedRangeX, centerY, centerX + extendedRangeX - 10, centerY - 5, QPen(Qt::black, 2));
    QGraphicsLineItem *xArrow2 = scene->addLine(centerX + extendedRangeX, centerY, centerX + extendedRangeX - 10, centerY + 5, QPen(Qt::black, 2));
    
    // Y轴箭头
    QGraphicsLineItem *yArrow1 = scene->addLine(centerX, centerY - extendedRangeY, centerX - 5, centerY - extendedRangeY + 10, QPen(Qt::black, 2));
    QGraphicsLineItem *yArrow2 = scene->addLine(centerX, centerY - extendedRangeY, centerX + 5, centerY - extendedRangeY + 10, QPen(Qt::black, 2));
    
    // 绘制坐标轴标签
    QGraphicsTextItem *xLabel = scene->addText("X");
    xLabel->setFont(QFont("Arial", 12, QFont::Bold));
    xLabel->setPos(centerX + extendedRangeX - 50, centerY - 10);
    
    QGraphicsTextItem *yLabel = scene->addText("Y");
    yLabel->setFont(QFont("Arial", 12, QFont::Bold));
    yLabel->setPos(centerX + 5, centerY - extendedRangeY * 0.75 + 15);
    

    
    // 绘制网格线和数值刻度
    QPen gridPen(Qt::lightGray, 0.5, Qt::DashLine);
    QFont tickFont("Arial", 8);
    
    // 绘制垂直线（Y轴平行线）和X轴刻度
    int xTickValue = 0;
    // 从原点开始，先绘制原点刻度（0）
    qreal x = centerX;
    
    // 绘制原点处的刻度线和标签
    QGraphicsLineItem *originTickX = scene->addLine(x, centerY - 5, x, centerY + 5, QPen(Qt::black, 2));
    originTickX->setZValue(-1); // 放在坐标轴上方
    
    // 绘制数值标签
    QGraphicsTextItem *originLabelX = scene->addText(QString::number(xTickValue));
    originLabelX->setFont(tickFont);
    originLabelX->setPos(x - 15, centerY + 8);
    originLabelX->setZValue(-1);
    
    // 绘制X轴正方向的刻度
    xTickValue = 50;
    for (x = centerX + 50; x < centerX + extendedRangeX; x += 50) {
        // 绘制网格线
        QGraphicsLineItem *line = scene->addLine(x, centerY - extendedRangeY, x, centerY + extendedRangeY, gridPen);
        line->setZValue(-3); // 放在坐标轴下方
        
        // 绘制刻度线
        QGraphicsLineItem *tick = scene->addLine(x, centerY - 5, x, centerY + 5, QPen(Qt::black, 2));
        tick->setZValue(-1); // 放在坐标轴上方
        
        // 绘制数值标签
        QGraphicsTextItem *tickLabel = scene->addText(QString::number(xTickValue));
        tickLabel->setFont(tickFont);
        tickLabel->setPos(x - 15, centerY + 8);
        tickLabel->setZValue(-1);
        
        xTickValue += 50;
    }
    
    // 绘制X轴负方向的刻度
    xTickValue = -50;
    for (x = centerX - 50; x > centerX - extendedRangeX; x -= 50) {
        // 绘制网格线
        QGraphicsLineItem *line = scene->addLine(x, centerY - extendedRangeY, x, centerY + extendedRangeY, gridPen);
        line->setZValue(-3); // 放在坐标轴下方
        
        // 绘制刻度线
        QGraphicsLineItem *tick = scene->addLine(x, centerY - 5, x, centerY + 5, QPen(Qt::black, 2));
        tick->setZValue(-1); // 放在坐标轴上方
        
        // 绘制数值标签
        QGraphicsTextItem *tickLabel = scene->addText(QString::number(xTickValue));
        tickLabel->setFont(tickFont);
        tickLabel->setPos(x - 15, centerY + 8);
        tickLabel->setZValue(-1);
        
        xTickValue -= 50;
    }
    
    // 绘制水平线（X轴平行线）和Y轴刻度
    int yTickValue = 0;
    // 从原点开始，先绘制原点刻度（0）
    qreal y = centerY;
    
    // 绘制原点处的刻度线和标签
    QGraphicsLineItem *originTickY = scene->addLine(centerX - 5, y, centerX + 5, y, QPen(Qt::black, 2));
    originTickY->setZValue(-1); // 放在坐标轴上方
    
    // 绘制数值标签
    QGraphicsTextItem *originLabelY = scene->addText(QString::number(yTickValue));
    originLabelY->setFont(tickFont);
    originLabelY->setPos(centerX + 8, y - 10);
    originLabelY->setZValue(-1);
    
    // 绘制Y轴负方向的刻度（向下为负）
    yTickValue = -50;
    for (y = centerY + 50; y < centerY + extendedRangeY; y += 50) {
        // 绘制网格线
        QGraphicsLineItem *line = scene->addLine(centerX - extendedRangeX, y, centerX + extendedRangeX, y, gridPen);
        line->setZValue(-3); // 放在坐标轴下方
        
        // 绘制刻度线
        QGraphicsLineItem *tick = scene->addLine(centerX - 5, y, centerX + 5, y, QPen(Qt::black, 2));
        tick->setZValue(-1); // 放在坐标轴上方
        
        // 绘制数值标签
        QGraphicsTextItem *tickLabel = scene->addText(QString::number(yTickValue));
        tickLabel->setFont(tickFont);
        tickLabel->setPos(centerX + 8, y - 10);
        tickLabel->setZValue(-1);
        
        yTickValue -= 50;
    }
    
    // 绘制Y轴正方向的刻度（向上为正）
    yTickValue = 50;
    for (y = centerY - 50; y > centerY - extendedRangeY; y -= 50) {
        // 绘制网格线
        QGraphicsLineItem *line = scene->addLine(centerX - extendedRangeX, y, centerX + extendedRangeX, y, gridPen);
        line->setZValue(-3); // 放在坐标轴下方
        
        // 绘制刻度线
        QGraphicsLineItem *tick = scene->addLine(centerX - 5, y, centerX + 5, y, QPen(Qt::black, 2));
        tick->setZValue(-1); // 放在坐标轴上方
        
        // 绘制数值标签
        QGraphicsTextItem *tickLabel = scene->addText(QString::number(yTickValue));
        tickLabel->setFont(tickFont);
        tickLabel->setPos(centerX + 8, y - 10);
        tickLabel->setZValue(-1);
        
        yTickValue += 50;
    }
    
    // 获取视图的大小
    QSize viewSize = ui->graphicsView->size();
    qreal viewWidth = viewSize.width();
    qreal viewHeight = viewSize.height();
    
    // 计算需要的边界范围
    // 基于当前缩放比例计算所需的场景范围
    qreal requiredWidth = viewWidth * (1.0 / currentScale);
    qreal requiredHeight = viewHeight * (1.0 / currentScale);
    
    // 确保场景范围至少覆盖我们的坐标系范围
    qreal sceneWidth = qMax(requiredWidth, extendedRangeX * 3);
    qreal sceneHeight = qMax(requiredHeight, extendedRangeY * 3);
    
    // 设置场景范围，以中心点为中心
    scene->setSceneRect(centerX - sceneWidth / 2, centerY - sceneHeight / 2, sceneWidth, sceneHeight);
    
    if (!currentGraph) {
        return;
    }
    
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
        
        // 计算标签位置（边的中心）
        QRectF labelRect = weightLabel->boundingRect();
        QPointF midPos = (srcPos + destPos) / 2;
        QPointF labelPos = midPos;
        labelPos.setX(labelPos.x() - labelRect.width() / 2);
        labelPos.setY(labelPos.y() - labelRect.height() / 2);
        weightLabel->setPos(labelPos);
        
        // 将权重标签放在上层显示
        weightLabel->setZValue(10);
        
        // 为权重标签添加背景框
        QGraphicsRectItem *background = scene->addRect(labelPos.x() - 4, labelPos.y() - 2, 
            labelRect.width() + 8, labelRect.height() + 4, 
            QPen(Qt::NoPen), QBrush(Qt::yellow));
        // 将背景放在标签下方但在边上方
        background->setZValue(9);
        
        // 存储边对象
        QString key = QString("%1-%2").arg(src).arg(dest);
        this->edges[key] = line;
    }
    
    // 设置场景范围，确保覆盖扩大后的坐标系
    scene->setSceneRect(400 - extendedRangeX * 1.5, 300 - extendedRangeY * 1.5, extendedRangeX * 3, extendedRangeY * 3);
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
    
    // 设置坐标轴原点（场景中心）
    qreal centerX = 400;
    qreal centerY = 300;
    
    if (currentGraph) {
        // 使用Graph对象中存储的节点坐标
        for (int i = 0; i < numNodes; ++i) {
            double x = currentGraph->getNodeX(i);
            double y = currentGraph->getNodeY(i);
            
            // 将坐标转换为场景坐标（以中心为原点）
            qreal sceneX = centerX + x;
            qreal sceneY = centerY - y; // Qt坐标系Y轴向下，需要反转
            
            nodePositions[i] = QPointF(sceneX, sceneY);
        }
    } else {
        // 如果没有Graph对象，生成圆形布局的节点位置
        qreal radius = qMin(700.0, qMin(ui->graphicsView->width(), ui->graphicsView->height()) * 0.4);
        
        for (int i = 0; i < numNodes; ++i) {
            qreal angle = 2 * M_PI * i / numNodes;
            qreal x = centerX + radius * cos(angle);
            qreal y = centerY + radius * sin(angle);
            nodePositions[i] = QPointF(x, y);
        }
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
                       "- 使用Kruskal算法求解最小生成树\n" 
                       "- 放大缩小视图\n\n");
}

void MainWindow::on_clearGraphBtn_clicked()
{
    // 清除当前图
    if (currentGraph) {
        delete currentGraph;
        currentGraph = nullptr;
    }
    
    // 清空用户节点列表
    userNodes.clear();
    
    // 清空节点位置
    nodePositions.clear();
    
    // 重置算法执行标志
    isAlgorithmExecuted = false;
    
    // 重置最小生成树总权重标签
    ui->mstWeightLabel->setText("最小生成树总权重: 未计算");
    
    // 重新绘制坐标系
    drawGraph();
    
    QMessageBox::information(this, "成功", "已清除当前图，现在可以添加新节点或生成新图");
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    // 检查是否点击在图形视图区域
    if (ui->graphicsView->geometry().contains(mapFromGlobal(event->globalPos()))) {
        // 只有在未执行算法前才能添加节点
        if (!isAlgorithmExecuted) {
            // 将全局坐标转换为视图坐标
            QPoint viewPos = ui->graphicsView->mapFromGlobal(event->globalPos());
            // 转换为场景坐标
            QPointF scenePos = ui->graphicsView->mapToScene(viewPos);
            
            // 设置坐标系原点（场景中心）
            qreal centerX = 400;
            qreal centerY = 300;
            
            // 转换为用户坐标系（以中心为原点）
            qreal userX = scenePos.x() - centerX;
            qreal userY = centerY - scenePos.y(); // Qt坐标系Y轴向下，需要反转
            
            // 限制节点坐标在坐标系范围内（X: -750到750，Y: -550到550）
            userX = qBound(-750.0, userX, 750.0);
            userY = qBound(-550.0, userY, 550.0);
            
            // 添加节点到用户节点列表
            userNodes.append(QPointF(userX, userY));
            
            // 创建或更新图对象
            if (currentGraph) {
                delete currentGraph;
            }
            
            int numNodes = userNodes.size();
            currentGraph = new Graph(numNodes);
            
            // 创建Node数组
            Node** nodes = new Node*[numNodes];
            nodePositions.clear();
            
            // 设置场景中心为坐标原点
            for (int i = 0; i < numNodes; ++i) {
                // 创建Node对象
                nodes[i] = new Node(userNodes[i].x(), userNodes[i].y());
                
                // 计算节点在场景中的位置（转换为Qt坐标系）
                qreal sceneX = centerX + userNodes[i].x();
                qreal sceneY = centerY - userNodes[i].y(); // Qt坐标系Y轴向下，需要反转
                
                // 存储节点位置
                nodePositions[i] = QPointF(sceneX, sceneY);
            }
            
            // 根据节点坐标自动生成边（使用欧氏距离作为权重）
            NodesToEdges(*currentGraph, nodes, numNodes);
            
            // 释放Node数组
            for (int i = 0; i < numNodes; ++i) {
                delete nodes[i];
            }
            delete[] nodes;
            
            // 绘制图
            drawGraph();
            
            // 显示添加节点的消息
            QMessageBox::information(this, "成功", QString("已添加节点(%1, %2)，当前共有%3个节点").arg(userX, 0, 'f', 1).arg(userY, 0, 'f', 1).arg(numNodes));
        } else {
            QMessageBox::warning(this, "提示", "算法已执行，无法添加节点。请重新生成或导入图");
        }
    }
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
    // 只有按住Ctrl键时才允许缩放
    if (event->modifiers() & Qt::ControlModifier) {
        double scaleFactor = 1.15;
        
        // 获取当前变换矩阵
        QTransform transform = ui->graphicsView->transform();
        // 计算当前缩放比例（取x和y方向的平均值）
        currentScale = (transform.m11() + transform.m22()) / 2.0;
        
        // 设置最小和最大缩放比例
        const double minScale = 0.5;
        const double maxScale = 3.0;
        
        // 如果滚轮向上滚动，放大视图
        if (event->angleDelta().y() > 0) {
            if (currentScale * scaleFactor <= maxScale) {
                ui->graphicsView->scale(scaleFactor, scaleFactor);
                // 更新当前缩放比例
                currentScale *= scaleFactor;
            }
        }
        // 如果滚轮向下滚动，缩小视图
        else {
            if (currentScale / scaleFactor >= minScale) {
                ui->graphicsView->scale(1 / scaleFactor, 1 / scaleFactor);
                // 更新当前缩放比例
                currentScale /= scaleFactor;
            }
        }
        
        // 重新绘制图以更新边界
        drawGraph();
    }
}
