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
#include <QPointF>
#include "Graph.h"
#include "Node.h"

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
    QVector<Node> getNodes() const; // 添加获取节点列表的方法

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void onAddNodeBtnClicked();
    void onRemoveNodeBtnClicked();
    void onAccepted();
    void onTableCellChanged(int row, int column);

private:
    void setupUI();
    void updateNodeTable();
    bool validateInput();

    // UI组件
    QTableWidget *nodeTableWidget;
    QPushButton *addNodeBtn;
    QPushButton *removeNodeBtn;
    QDialogButtonBox *buttonBox;
    QLabel *nodeLabel;

    // 数据
    int nodeCount;
    Graph *graph;
    QVector<Node> nodes;
    CustomSpinBoxStyle *customStyle; // 自定义样式实例
};

#endif // MANUALINPUTDIALOG_H
