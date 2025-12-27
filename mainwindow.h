#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QWidget>
#include "postoffice.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// 主窗口类，负责邮局选址问题的可视化界面
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    // 重绘事件处理函数

    void paintEvent(QPaintEvent *event) override;
    
    // 鼠标点击事件处理函数

    void mousePressEvent(QMouseEvent *event) override;
    
    // 窗口大小改变事件处理函数

    void resizeEvent(QResizeEvent *event) override;

private slots:
    // 计算最优邮局位置
    void calculateOptimalLocation();
    
    // 清空所有居民小区
    void clearAllAreas();
    
    // 随机生成居民小区
    void generateRandomAreas();
    
    // 从文件加载居民小区
    void loadAreasFromFile();
    
    // 更新状态栏信息
    void updateStatusBar();
    
    // 切换模式（普通模式/权重模式）
    void switchMode();

private:
    // 初始化界面
    void initializeUI();
    
    // 获取用户输入的权重

    int getWeightFromUser();
    
    // 绘制坐标网格
    
    void drawGrid(QPainter &painter, const QRect &contentRect);
    
    // 绘制简单网格（网格图模式）


    void drawSimpleGrid(QPainter &painter, const QRect &contentRect);
    
    // 绘制居民小区

    void drawResidentialAreas(QPainter &painter);
    
    // 绘制邮局位置

    void drawPostOffice(QPainter &painter);
    
    // 绘制连接线

    void drawConnections(QPainter &painter);
    
    // 坐标转换：逻辑坐标到屏幕坐标
    
    QPoint logicalToScreen(const QPoint &logicalPoint) const;
    
    // 坐标转换：屏幕坐标到逻辑坐标
    
    QPoint screenToLogical(const QPoint &screenPoint) const;

private:
    Ui::MainWindow *ui;
    PostOfficeLocator m_locator;          ///< 邮局选址器
    QPoint m_optimalPostOffice;           ///< 最优邮局位置
    bool m_hasCalculated;                 ///< 是否已计算最优位置
    QRect m_drawingArea;                  ///< 绘图区域（现在使用frame_2）
    QRect m_logicalBounds;                ///< 逻辑坐标边界
    double m_scaleX, m_scaleY;            ///< 坐标缩放比例
    int m_gridSize;                       ///< 网格大小
    bool m_showGridMode;                  ///< 是否显示网格模式（true: 网格图, false: XY坐标图）
    bool m_isWeightMode;                  ///< 当前是否为权重模式（true: 权重模式, false: 普通模式）
};

#endif // MAINWINDOW_H
