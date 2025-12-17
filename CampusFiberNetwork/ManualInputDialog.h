#ifndef MANUALINPUTDIALOG_H
#define MANUALINPUTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QSpinBox>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QProxyStyle>
#include <QPainter>
#include "Graph.h"

// 自定义样式类，用于绘制+和-符号
class CustomSpinBoxStyle : public QProxyStyle
{
public:
    using QProxyStyle::QProxyStyle;
    void drawControl(ControlElement element, const QStyleOption* option, QPainter* painter, const QWidget* widget = nullptr) const override;
};

class ManualInputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManualInputDialog(QWidget *parent = nullptr);
    ~ManualInputDialog();

    Graph *getGraph();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void onNodeCountChanged(int count);
    void onAddEdgeBtnClicked();
    void onRemoveEdgeBtnClicked();
    void onAccepted();
    void onTableCellChanged(int row, int column);

private:
    void setupUI();
    void updateEdgeTable();
    bool validateInput();

    // UI组件
    QSpinBox *nodeCountSpinBox;
    QTableWidget *edgeTableWidget;
    QPushButton *addEdgeBtn;
    QPushButton *removeEdgeBtn;
    QDialogButtonBox *buttonBox;
    QLabel *nodeLabel;

    // 数据
    int nodeCount;
    Graph *graph;
    QVector<Edge> edges;
    CustomSpinBoxStyle *customStyle; // 自定义样式实例
};

#endif // MANUALINPUTDIALOG_H
