#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QVector>
#include <QPointF>
#include <QMap>
#include "Graph.h"
#include "ManualInputDialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 随机生成图
    void on_randomGenerateBtn_clicked();
    // 文件输入图
    void on_fileInputBtn_clicked();
    // 人工输入图
    void on_manualInputBtn_clicked();
    // 运行Kruskal算法
    void on_runKruskalBtn_clicked();
    // 清除图
    void on_clearGraphBtn_clicked();
    // 菜单功能
    void on_actionOpen_Graph_File_triggered();
    void on_actionExit_triggered();
    void on_actionAbout_triggered();

protected:
    // 鼠标滚轮事件，用于放大缩小
    void wheelEvent(QWheelEvent *event) override;
    // 鼠标点击事件，用于添加节点
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;
    // 图形场景和视图
    QGraphicsScene *scene;
    // 图对象
    Graph *currentGraph;
    // 节点位置映射
    QMap<int, QPointF> nodePositions;
    // 边对象映射
    QMap<QString, QGraphicsItem*> edges;
    // MST边集合
    QVector<Edge*> mstEdges;
    // 算法是否已经执行
    bool isAlgorithmExecuted;
    // 当前缩放比例
    double currentScale;
    // 存储鼠标点击添加的节点坐标（相对于用户坐标系）
    QVector<QPointF> userNodes;

    // 绘制图
    void drawGraph();
    // 清除场景
    void clearScene();
    // 生成节点位置
    void generateNodePositions(int numNodes);
    // 高亮MST边
    void highlightMSTEdges();
    // 重置边颜色
    void resetEdgeColors();
    // 计算两个节点之间的距离
    qreal calculateDistance(const QPointF &p1, const QPointF &p2);
};

#endif // MAINWINDOW_H
