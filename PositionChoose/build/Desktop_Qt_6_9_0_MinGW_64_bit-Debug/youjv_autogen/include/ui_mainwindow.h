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
    QPushButton *btnLoadFromFile;
    QPushButton *btnModeSwitch;
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
"    border-radius: 8px;\n"
"    margin: 10px;\n"
"}\n"
"/* \345\267\246\344\276\247\351\235\242\346\235\277\346\240\267\345\274\217 - \346\202\254\346\265\256\346\204\237\357\274\214\344\270\215\351\201\256\346\214\241\347\275\221\346\240\274 */\n"
"#frame {\n"
"    background-color: #f5f5f5;\n"
"    border-radius: 8px;\n"
"    border: 1px solid #dcdcdc;\n"
"    padding: 15px;\n"
"    margin: 10px 0 10px 10px;\n"
"}\n"
"QLabel {\n"
"    color: #333333;\n"
"}\n"
"QPushButton {\n"
"    border-radius: 4px;\n"
"    font-weight: 600;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #e0"
                        "e0e0;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #c0c0c0;\n"
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
"font-size: 24px;\n"
"font-weight: 700;\n"
"color: white;\n"
"background-color: #4361ee;\n"
"padding: 16px;\n"
"border-radius: 6px;\n"
"margin-bottom: 10px;\n"
"text-align: center;\n"
"border: 1px solid #3a0ca3;\n"
"           "));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setStyleSheet(QString::fromUtf8("\n"
"font-size: 16px;\n"
"font-weight: 600;\n"
"color: #2d3748;\n"
"background-color: #edf2f7;\n"
"padding: 10px 14px;\n"
"border-radius: 4px;\n"
"border-left: 4px solid #4361ee;\n"
"           "));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");
        label_3->setStyleSheet(QString::fromUtf8("\n"
"font-size: 13px;\n"
"color: #4a5568;\n"
"background-color: white;\n"
"padding: 12px;\n"
"border-radius: 4px;\n"
"border: 1px solid #e2e8f0;\n"
"line-height: 1.7;\n"
"           "));
        label_3->setWordWrap(true);

        verticalLayout->addWidget(label_3);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        btnCalculate = new QPushButton(frame);
        btnCalculate->setObjectName("btnCalculate");
        btnCalculate->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background-color: #4361ee;\n"
"    color: white;\n"
"    border: 1px solid #3a0ca3;\n"
"    padding: 14px 20px;\n"
"    font-size: 15px;\n"
"    min-height: 45px;\n"
"    border-radius: 4px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #3a0ca3;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #2a0878;\n"
"    border-style: inset;\n"
"}\n"
"           "));

        verticalLayout->addWidget(btnCalculate);

        btnClear = new QPushButton(frame);
        btnClear->setObjectName("btnClear");
        btnClear->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background-color: #ef4444;\n"
"    color: white;\n"
"    border: 1px solid #dc2626;\n"
"    padding: 14px 20px;\n"
"    font-size: 15px;\n"
"    min-height: 45px;\n"
"    border-radius: 4px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #dc2626;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #b91c1c;\n"
"    border-style: inset;\n"
"}\n"
"           "));

        verticalLayout->addWidget(btnClear);

        btnRandom = new QPushButton(frame);
        btnRandom->setObjectName("btnRandom");
        btnRandom->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background-color: #10b981;\n"
"    color: white;\n"
"    border: 1px solid #059669;\n"
"    padding: 14px 20px;\n"
"    font-size: 15px;\n"
"    min-height: 45px;\n"
"    border-radius: 4px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #059669;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #047857;\n"
"    border-style: inset;\n"
"}\n"
"           "));

        verticalLayout->addWidget(btnRandom);

        btnLoadFromFile = new QPushButton(frame);
        btnLoadFromFile->setObjectName("btnLoadFromFile");
        btnLoadFromFile->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background-color: #f59e0b;\n"
"    color: white;\n"
"    border: 1px solid #d97706;\n"
"    padding: 14px 20px;\n"
"    font-size: 15px;\n"
"    min-height: 45px;\n"
"    border-radius: 4px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #d97706;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #b45309;\n"
"    border-style: inset;\n"
"}\n"
"           "));

        verticalLayout->addWidget(btnLoadFromFile);

        btnModeSwitch = new QPushButton(frame);
        btnModeSwitch->setObjectName("btnModeSwitch");
        btnModeSwitch->setStyleSheet(QString::fromUtf8("\n"
"QPushButton {\n"
"    background-color: #8b5cf6;\n"
"    color: white;\n"
"    border: 1px solid #7c3aed;\n"
"    padding: 14px 20px;\n"
"    font-size: 15px;\n"
"    min-height: 45px;\n"
"    border-radius: 4px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: #7c3aed;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: #6d28d9;\n"
"    border-style: inset;\n"
"}\n"
"           "));

        verticalLayout->addWidget(btnModeSwitch);

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
        label->setText(QCoreApplication::translate("MainWindow", "\351\202\256\345\261\200\351\200\211\345\235\200\351\227\256\351\242\230", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\360\237\223\213 \346\223\215\344\275\234\350\257\264\346\230\216", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\342\200\242 \347\202\271\345\207\273\345\217\263\344\276\247\347\273\230\345\233\276\345\214\272\345\237\237\346\267\273\345\212\240\345\261\205\346\260\221\345\260\217\345\214\272\n"
"\342\200\242 \344\275\277\347\224\250\344\270\213\346\226\271\346\214\211\351\222\256\350\277\233\350\241\214\347\233\270\345\205\263\346\223\215\344\275\234\n"
"\342\200\242 \344\273\216\346\226\207\344\273\266\345\212\240\350\275\275\345\260\217\345\214\272\346\225\260\346\215\256\357\274\210\346\224\257\346\214\201\346\235\203\351\207\215\357\274\211\n"
"\342\200\242 \347\263\273\347\273\237\350\207\252\345\212\250\350\256\241\347\256\227\346\234\200\344\274\230\351\202\256\345\261\200\344\275\215\347\275\256\n"
"\342\200\242 \346\224\257\346\214\201\346\270\205\347\251\272\345\222\214\351\232\217\346\234\272\347\224\237\346\210\220\345\212\237\350\203\275\n"
"\342\200\242 \345\217\257\345\210\207\346\215\242\346\231\256\351\200\232\346\250\241\345\274\217/\346\235\203\351\207\215\346\250\241\345\274\217\n"
"\342\200\242 \344"
                        "\275\277\347\224\250\345\212\240\346\235\203\346\233\274\345\223\210\351\241\277\350\267\235\347\246\273\344\274\230\345\214\226\347\256\227\346\263\225\n"
"\n"
"\346\250\241\345\274\217\350\257\264\346\230\216\357\274\232\n"
"- \346\231\256\351\200\232\346\250\241\345\274\217\357\274\232\346\267\273\345\212\240\345\260\217\345\214\272\346\227\266\346\235\203\351\207\215\350\207\252\345\212\250\344\270\2721\n"
"- \346\235\203\351\207\215\346\250\241\345\274\217\357\274\232\346\267\273\345\212\240\345\260\217\345\214\272\346\227\266\351\234\200\350\276\223\345\205\245\346\235\203\351\207\215\357\274\2101-100\357\274\211", nullptr));
        btnCalculate->setText(QCoreApplication::translate("MainWindow", "\350\256\241\347\256\227\346\234\200\344\274\230\351\202\256\345\261\200\344\275\215\347\275\256", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\211\200\346\234\211\345\260\217\345\214\272", nullptr));
        btnRandom->setText(QCoreApplication::translate("MainWindow", "\351\232\217\346\234\272\347\224\237\346\210\220\345\260\217\345\214\272", nullptr));
        btnLoadFromFile->setText(QCoreApplication::translate("MainWindow", "\344\273\216\346\226\207\344\273\266\345\212\240\350\275\275\345\260\217\345\214\272", nullptr));
        btnModeSwitch->setText(QCoreApplication::translate("MainWindow", "\346\250\241\345\274\217\345\210\207\346\215\242", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\360\237\247\256 \347\256\227\346\263\225\344\277\241\346\201\257", nullptr));
        lblAlgorithmInfo->setText(QCoreApplication::translate("MainWindow", "\342\200\242 \344\275\277\347\224\250\345\212\240\346\235\203\344\270\255\344\275\215\346\225\260\346\226\271\346\263\225\346\261\202\350\247\243\n"
"\342\200\242 \345\212\240\346\235\203\346\233\274\345\223\210\351\241\277\350\267\235\347\246\273\346\234\200\345\260\217\345\214\226\n"
"\342\200\242 \346\227\266\351\227\264\345\244\215\346\235\202\345\272\246\357\274\232O(n log n)\n"
"\342\200\242 \344\277\235\350\257\201\346\234\200\344\274\230\350\247\243\n"
"\342\200\242 \346\224\257\346\214\201\346\235\203\351\207\215\345\222\214\346\226\207\344\273\266\345\212\240\350\275\275", nullptr));
        label_5->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
