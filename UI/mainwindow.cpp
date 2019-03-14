#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>
#include <string.h>
#include <QFileDialog>
#include <QLibrary>
#include <QMessageBox>
typedef int(*gen_chain_word)(char * words[], int len, char * result[], char head, char tail, bool enable_loop);
typedef int(*gen_chain_char)(char * words[], int len, char * result[], char head, char tail, bool enable_loop);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    drawUI(this);
    connect(this->pushButton,SIGNAL(clicked()),this,SLOT(fileOpen()));
    connect(this->pushButton_2,SIGNAL(clicked()),this,SLOT(generate()));
    connect(this->pushButton_3,SIGNAL(clicked()),this,SLOT(fileSave()));


}
void MainWindow::fileOpen(){
    QString filePath= QFileDialog::getOpenFileName(this,tr("file"),"",tr("TXT(*.txt)"));
    if (filePath.isEmpty()){
        return;
    }else{
        QFile fin(filePath);
        if (fin.open(QIODevice::ReadOnly | QIODevice::Text)){
            while (!fin.atEnd()){
                QByteArray line = fin.readLine();
                QString strin(line);
                this->textEdit->insertPlainText(strin);
            }
        }
        fin.close();
    }
}
void MainWindow::generate(){
    bool allFlag=true;
    QLibrary lib("Core.dll");
    gen_chain_word get_chain_word=(gen_chain_word)lib.resolve("gen_chain_word");
    gen_chain_word get_chain_char=(gen_chain_char)lib.resolve("gen_chain_char");
    bool A_w,A_c,A_r,A_h,A_t;
    A_w=this->checkBox->isChecked()?true:false;
    A_c=this->checkBox_2->isChecked()?true:false;
    A_r=this->checkBox_3->isChecked()?true:false;
    A_h=this->checkBox_4->isChecked()?true:false;
    A_t=this->checkBox_5->isChecked()?true:false;
    QString textin=this->textEdit->toPlainText();
    qDebug() << textin;
    char*  ch;
    QByteArray ba = textin.toLatin1();
    ch=ba.data();
    char ** words=new char*[10000];
    char ** result=new char*[10000];
    int len=0;
    int chLen=strlen(ch);
    int currPos=0;
    while (currPos<chLen){
        if (isalpha(ch[currPos]) != 0) {
            char * wordBuff = new char[1000];
            int wordBuffPos = 0;
            //printf("%c",currentChar);
            while (isalpha(ch[currPos]) != 0) {
                wordBuff[wordBuffPos] = tolower(ch[currPos]);
                wordBuffPos++;
                currPos++;
            }
            wordBuff[wordBuffPos] = '\0';
            words[len] = wordBuff;
            len++;
        }
        else {
           currPos++;
        }
    }
    qDebug()<<ch;
    qDebug()<<len;
    qDebug()<<words[len-1];
    char head=0,tail=0;
    if (A_t){
        QString tmp=this->plainTextEdit_2->toPlainText();
        char*  tt;
        QByteArray ba = tmp.toLatin1();
        tt=ba.data();
        if (strlen(tt)!=1){
            allFlag=false;
            QMessageBox::critical(0 , "ERROR" , "More than one char or no char got in -h or -t", QMessageBox::Ok | QMessageBox::Default ,0 , 	0 );
        }else{
            tail=tt[0];
        }
    }
    if (A_h){
        QString tmp=this->plainTextEdit->toPlainText();
        char*  tt;
        QByteArray ba = tmp.toLatin1();
        tt=ba.data();
        if (strlen(tt)!=1){
            allFlag=false;
            QMessageBox::critical(0 , "ERROR" , "More than one char or no char got in -h or -t", QMessageBox::Ok | QMessageBox::Default ,0 , 	0 );

        }else{
            head=tt[0];
        }
    }
    if (A_w && A_c){
        allFlag=false;
        QMessageBox::critical(0 , "ERROR" , "Cannot choose both -w and -c", QMessageBox::Ok | QMessageBox::Default ,0 , 	0 );
    }
    if ((!A_w)&&(!A_c)){
        allFlag=false;
        QMessageBox::critical(0 , "ERROR" , "Must choose -w or -c", QMessageBox::Ok | QMessageBox::Default ,0 , 	0 );
    }
     qDebug()<<"!!!!!!";
    qDebug()<<(int)tail;
    qDebug()<<(int)head;
    if (allFlag){
        try {
            if (A_c) get_chain_char(words,len,result,head,tail,A_r);
            if (A_w) get_chain_word(words,len,result,head,tail,A_r);
        } catch (const char* msg) {
            QMessageBox::critical(0 , "ERROR" , msg, QMessageBox::Ok | QMessageBox::Default ,0 , 	0 );
        }catch(...){
            QMessageBox::critical(0 , "ERROR" , "ERROR", QMessageBox::Ok | QMessageBox::Default ,0 , 	0 );

        }
        qDebug()<<"!!!!!!";
        int pp=0;
        while (result[pp]!=NULL){
            qDebug(result[pp]);
            this->textEdit_2->insertPlainText(result[pp]);
            this->textEdit_2->insertPlainText("\n");
            pp++;
        }
    }



}
void MainWindow::fileSave(){
    QString filePath= QFileDialog::getSaveFileName(this,tr("file"),"",tr("TXT(*.txt)"));
    if (filePath.isEmpty()){
        return;
    }else{
        QFile fout(filePath);
        if (fout.open(QIODevice::WriteOnly | QIODevice::Text)){
            QString textin=this->textEdit_2->toPlainText();
            QTextStream out(&fout);
            out << textin << endl;
        }
        fout.close();
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
