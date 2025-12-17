/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *gridContainer;
    QHBoxLayout *rootLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QPushButton *btnCalculate;
    QPushButton *btnClear;
    QPushButton *btnRandom;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_4;
    QLabel *lblAlgorithmInfo;
    QLabel *label_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1400, 900);
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"/* \345\205\250\345\261\200\351\200\232\347\224\250\346\240\267\345\274\217 */\n"
"QWidget {\n"
"    font-family: \"Microsoft YaHei\", \"PingFang SC\", sans-serif;\n"
"}\n"
"/* \347\275\221\346\240\274\347\273\230\345\233\276\345\214\272\345\272\225\345\261\202\345\256\271\345\231\250 - \344\270\223\351\227\250\346\211\277\350\275\275XY\347\275\221\346\240\274 */\n"
"#gridContainer {\n"
"    background-color: #ffffff;\n"
"    border-radius: 16px;\n"
"    margin: 15px;\n"
"}\n"
"/* \345\267\246\344\276\247\351\235\242\346\235\277\346\240\267\345\274\217 - \346\202\254\346\265\256\346\204\237\357\274\214\344\270\215\351\201\256\346\214\241\347\275\221\346\240\274 */\n"
"#frame {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #f9fafb, stop:1 #f1f3f5);\n"
"    border-radius: 16px;\n"
"    border: none;\n"
"    box-shadow: 0 6px 16px rgba(0, 0, 0, 0.08);\n"
"    padding: 20px;\n"
"    /* \351\235\242\346\235\277\350\275\273\345\276\256\346\202\254\346\265\256\357\274\214\344\270\215\351\201"
                        "\256\346\214\241\347\275\221\346\240\274 */\n"
"    margin: 15px 0 15px 15px;\n"
"}\n"
"QLabel {\n"
"    color: #333333;\n"
"}\n"
"QPushButton {\n"
"    border-radius: 8px;\n"
"    font-weight: 600;\n"
"    transition: all 0.2s ease;\n"
"}\n"
"QPushButton:hover {\n"
"    transform: translateY(-2px);\n"
"}\n"
"QPushButton:pressed {\n"
"    transform: translateY(0);\n"
"}\n"
"   "));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridContainer = new QWidget(centralwidget);
        gridContainer->setObjectName("gridContainer");
        rootLayout = new QHBoxLayout(gridContainer);
        rootLayout->setSpacing(0);
        rootLayout->setObjectName("rootLayout");
        rootLayout->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(gridContainer);
        frame->setObjectName("frame");
        frame->setMinimumSize(QSize(320, 700));
        frame->setMaximumSize(QSize(350, 16777215));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(15);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setStyleSheet(QString::fromUtf8("\n"
"font-size: 26px;\n"
"font-weight: 700;\n"
"color: white;\n"
"background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #4361ee, stop:1 #3a0ca3);\n"
"padding: 20px;\n"
"border-radius: 12px;\n"
"margin-bottom: 10px;\n"
"box-shadow: 0 4px 8px rgba(67, 97, 238, 0.2);\n"
"text-align: center;\n"
"           "));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("\n"
"font-size: 18px;\n"
"font-weight: 600;\n"
"color: #2d3748;\n"
"background-color: #edf2f7;\n"
"padding: 12px 16px;\n"
"border-radius: 8px;\n"
"border-left: 4px solid #4361ee;\n"
"           "));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("\n"
"font-size: 14px;\n"
"color: #4a5568;\n"
"background-color: white;\n"
"padding: 16px;\n"
"border-radius: 8px;\n"
"border: 1px solid #e2e8f0;\n"
"line-height: 1.8;\n"
"box-shadow: 0 2px 4px rgba(0, 0, 0, 0.03);\n"
"           "));
        label_3->setWordWrap(true);

        verticalLayout->addWidget(label_3);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        btnCalculate = new QPushButton(frame);
        btnCalculate->setObjectName("btnCalculate");
        btnCalculate->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #4361ee, stop:1 #3a0ca3);\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 16px 24px;\n"
"    font-size: 16px;\n"
"    min-height: 50px;\n"
"    box-shadow: 0 4px 8px rgba(67, 97, 238, 0.2);\n"
"}\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #3a0ca3, stop:1 #2a0878);\n"
"    box-shadow: 0 6px 12px rgba(67, 97, 238, 0.3);\n"
"}\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #2a0878, stop:1 #1e0659);\n"
"}\n"
"           "));

        verticalLayout->addWidget(btnCalculate);

        btnClear = new QPushButton(frame);
        btnClear->setObjectName("btnClear");
        btnClear->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #ef4444, stop:1 #dc2626);\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 16px 24px;\n"
"    font-size: 16px;\n"
"    min-height: 50px;\n"
"    box-shadow: 0 4px 8px rgba(239, 68, 68, 0.2);\n"
"}\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #dc2626, stop:1 #b91c1c);\n"
"    box-shadow: 0 6px 12px rgba(239, 68, 68, 0.3);\n"
"}\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #b91c1c, stop:1 #991b1b);\n"
"}\n"
"           "));

        verticalLayout->addWidget(btnClear);

        btnRandom = new QPushButton(frame);
        btnRandom->setObjectName("btnRandom");
        btnRandom->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #10b981, stop:1 #059669);\n"
"    color: white;\n"
"    border: none;\n"
"    padding: 16px 24px;\n"
"    font-size: 16px;\n"
"    min-height: 50px;\n"
"    box-shadow: 0 4px 8px rgba(16, 185, 129, 0.2);\n"
"}\n"
"QPushButton:hover {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #059669, stop:1 #047857);\n"
"    box-shadow: 0 6px 12px rgba(16, 185, 129, 0.3);\n"
"}\n"
"QPushButton:pressed {\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #047857, stop:1 #065f46);\n"
"}\n"
"           "));

        verticalLayout->addWidget(btnRandom);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");
        label_4->setStyleSheet(QString::fromUtf8("\n"
"font-size: 18px;\n"
"font-weight: 600;\n"
"color: #2d3748;\n"
"background-color: #edf2f7;\n"
"padding: 12px 16px;\n"
"border-radius: 8px;\n"
"border-left: 4px solid #4361ee;\n"
"           "));

        verticalLayout->addWidget(label_4);

        lblAlgorithmInfo = new QLabel(frame);
        lblAlgorithmInfo->setObjectName("lblAlgorithmInfo");
        lblAlgorithmInfo->setStyleSheet(QString::fromUtf8("\n"
"font-size: 14px;\n"
"color: #4a5568;\n"
"background-color: white;\n"
"padding: 16px;\n"
"border-radius: 8px;\n"
"border: 1px solid #e2e8f0;\n"
"line-height: 1.8;\n"
"box-shadow: 0 2px 4px rgba(0, 0, 0, 0.03);\n"
"           "));
        lblAlgorithmInfo->setWordWrap(true);

        verticalLayout->addWidget(lblAlgorithmInfo);


        rootLayout->addWidget(frame);

        label_5 = new QLabel(gridContainer);
        label_5->setObjectName("label_5");
        label_5->setStyleSheet(QString::fromUtf8("\n"
"background-color: transparent;\n"
"/* \347\273\230\345\233\276\345\214\272\345\206\205\350\276\271\350\267\235\357\274\214\351\201\277\345\205\215\347\275\221\346\240\274\350\264\264\350\276\271 */\n"
"padding: 20px;\n"
"        "));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);

        rootLayout->addWidget(label_5);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1400, 18));
        menubar->setStyleSheet(QString::fromUtf8("\n"
"background-color: #f8fafc;\n"
"border: none;\n"
"    "));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        statusbar->setStyleSheet(QString::fromUtf8("\n"
"background-color: #f8fafc;\n"
"color: #4a5568;\n"
"border-top: 1px solid #e2e8f0;\n"
"    "));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\351\202\256\345\261\200\351\200\211\345\235\200\351\227\256\351\242\230 - \346\234\200\347\237\255\350\267\257\345\276\204\347\256\227\346\263\225\346\261\202\350\247\243", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\360\237\217\244 \351\202\256\345\261\200\351\200\211\345\235\200\351\227\256\351\242\230", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\360\237\223\213 \346\223\215\344\275\234\350\257\264\346\230\216", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\342\200\242 \360\237\226\261\357\270\217 \347\202\271\345\207\273\345\217\263\344\276\247\347\273\230\345\233\276\345\214\272\345\237\237\346\267\273\345\212\240\345\261\205\346\260\221\345\260\217\345\214\272\n"
"\342\200\242 \342\232\241 \344\275\277\347\224\250\344\270\213\346\226\271\346\214\211\351\222\256\350\277\233\350\241\214\347\233\270\345\205\263\346\223\215\344\275\234\n"
"\342\200\242 \360\237\223\212 \347\263\273\347\273\237\350\207\252\345\212\250\350\256\241\347\256\227\346\234\200\344\274\230\351\202\256\345\261\200\344\275\215\347\275\256\n"
"\342\200\242 \360\237\224\204 \346\224\257\346\214\201\346\270\205\347\251\272\345\222\214\351\232\217\346\234\272\347\224\237\346\210\220\345\212\237\350\203\275\n"
"\342\200\242 \360\237\223\217 \344\275\277\347\224\250\346\233\274\345\223\210\351\241\277\350\267\235\347\246\273\344\274\230\345\214\226\347\256\227\346\263\225", nullptr));
        btnCalculate->setText(QCoreApplication::translate("MainWindow", "\360\237\223\212 \350\256\241\347\256\227\346\234\200\344\274\230\351\202\256\345\261\200\344\275\215\347\275\256", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 \346\270\205\347\251\272\346\211\200\346\234\211\345\260\217\345\214\272", nullptr));
        btnRandom->setText(QCoreApplication::translate("MainWindow", "\360\237\216\262 \351\232\217\346\234\272\347\224\237\346\210\220\345\260\217\345\214\272", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\360\237\247\256 \347\256\227\346\263\225\344\277\241\346\201\257", nullptr));
        lblAlgorithmInfo->setText(QCoreApplication::translate("MainWindow", "\342\200\242 \360\237\223\212 \344\275\277\347\224\250\344\270\255\344\275\215\346\225\260\346\226\271\346\263\225\346\261\202\350\247\243\n"
"\342\200\242 \360\237\223\217 \346\233\274\345\223\210\351\241\277\350\267\235\347\246\273\346\234\200\345\260\217\345\214\226\n"
"\342\200\242 \342\232\241 \346\227\266\351\227\264\345\244\215\346\235\202\345\272\246\357\274\232O(n)\n"
"\342\200\242 \342\234\205 \344\277\235\350\257\201\346\234\200\344\274\230\350\247\243\n"
"\342\200\242 \360\237\216\257 \346\224\257\346\214\201\345\212\250\346\200\201\346\267\273\345\212\240\345\260\217\345\214\272", nullptr));
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
