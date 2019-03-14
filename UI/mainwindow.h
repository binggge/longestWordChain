#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QWidget *centralWidget;
        QTextEdit *textEdit;
        QCheckBox *checkBox;
        QCheckBox *checkBox_2;
        QCheckBox *checkBox_3;
        QCheckBox *checkBox_4;
        QCheckBox *checkBox_5;
        QPlainTextEdit *plainTextEdit;
        QPlainTextEdit *plainTextEdit_2;
        QLabel *label;
        QPushButton *pushButton;
        QPushButton *pushButton_2;
        QTextEdit *textEdit_2;
        QMenuBar *menuBar;
        QToolBar *mainToolBar;
        QStatusBar *statusBar;
        QPushButton *pushButton_3;

        void drawUI(QMainWindow *MainWindow)
        {
            if (MainWindow->objectName().isEmpty())
                MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
            MainWindow->resize(588, 247);
            centralWidget = new QWidget(MainWindow);
            centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
            textEdit = new QTextEdit(centralWidget);
            textEdit->setObjectName(QString::fromUtf8("textEdit"));
            textEdit->setGeometry(QRect(30, 40, 101, 141));
            checkBox = new QCheckBox(centralWidget);
            checkBox->setObjectName(QString::fromUtf8("checkBox"));
            checkBox->setGeometry(QRect(160, 40, 71, 16));
            checkBox_2 = new QCheckBox(centralWidget);
            checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
            checkBox_2->setGeometry(QRect(210, 40, 71, 16));
            checkBox_3 = new QCheckBox(centralWidget);
            checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
            checkBox_3->setGeometry(QRect(160, 70, 71, 16));
            checkBox_4 = new QCheckBox(centralWidget);
            checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
            checkBox_4->setGeometry(QRect(160, 110, 71, 16));
            checkBox_5 = new QCheckBox(centralWidget);
            checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
            checkBox_5->setGeometry(QRect(160, 150, 71, 16));
            plainTextEdit = new QPlainTextEdit(centralWidget);
            plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
            plainTextEdit->setGeometry(QRect(200, 100, 61, 31));
            plainTextEdit_2 = new QPlainTextEdit(centralWidget);
            plainTextEdit_2->setObjectName(QString::fromUtf8("plainTextEdit_2"));
            plainTextEdit_2->setGeometry(QRect(200, 140, 61, 31));
            label = new QLabel(centralWidget);
            label->setObjectName(QString::fromUtf8("label"));
            label->setGeometry(QRect(50, 10, 61, 16));
            pushButton = new QPushButton(centralWidget);
            pushButton->setObjectName(QString::fromUtf8("pushButton"));
            pushButton->setGeometry(QRect(160, 10, 75, 23));
            pushButton_2 = new QPushButton(centralWidget);
            pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
            pushButton_2->setGeometry(QRect(270, 70, 75, 23));
            pushButton_3 = new QPushButton(centralWidget);
            pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
            pushButton_3->setGeometry(QRect(380, 10, 75, 23));
            textEdit_2 = new QTextEdit(centralWidget);
            textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
            textEdit_2->setGeometry(QRect(360, 40, 201, 141));
            MainWindow->setCentralWidget(centralWidget);
            menuBar = new QMenuBar(MainWindow);
            menuBar->setObjectName(QString::fromUtf8("menuBar"));
            menuBar->setGeometry(QRect(0, 0, 588, 23));
            MainWindow->setMenuBar(menuBar);
            mainToolBar = new QToolBar(MainWindow);
            mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
            MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
            statusBar = new QStatusBar(MainWindow);
            statusBar->setObjectName(QString::fromUtf8("statusBar"));
            MainWindow->setStatusBar(statusBar);

            retranslateUi(MainWindow);

            QMetaObject::connectSlotsByName(MainWindow);
        } // setupUi

        void retranslateUi(QMainWindow *MainWindow)
        {
            MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
            checkBox->setText(QApplication::translate("MainWindow", "-w", nullptr));
            checkBox_2->setText(QApplication::translate("MainWindow", "-c", nullptr));
            checkBox_3->setText(QApplication::translate("MainWindow", "-r", nullptr));
            checkBox_4->setText(QApplication::translate("MainWindow", "-h", nullptr));
            checkBox_5->setText(QApplication::translate("MainWindow", "-t", nullptr));
            label->setText(QApplication::translate("MainWindow", "Input text", nullptr));
            pushButton->setText(QApplication::translate("MainWindow", "Open File", nullptr));
            pushButton_2->setText(QApplication::translate("MainWindow", "Generate", nullptr));
            pushButton_3->setText(QApplication::translate("MainWindow", "Write File", nullptr));
        } // retranslateUi
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
private slots:
    void generate();
    void fileOpen();
    void fileSave();
};

#endif // MAINWINDOW_H
