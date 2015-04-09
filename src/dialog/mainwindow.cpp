#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "chart.h"
#include <QPushButton>
#include <QLineEdit>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>

Player *player[50];
int players = 0;
Chart *chart;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene)
{
    scene->setSceneRect(0, 0, 375, 495);
    chart = new Chart();
    for (int i=0; i<players; i++)
        chart->addPlayer(player[i]);
    scene->addItem(chart);
    ui->setupUi(this);
    ui->graphicsView->setScene(scene);
    ui->textEdit->append("New Game");
}

MainWindow::~MainWindow()
{
    delete chart;
    delete scene;
    delete ui;
}

QString getDelta(int a, int b)
{
    if (a<b) return QString("%1+%2").arg(a).arg(b-a);
    if (a>b) return QString("%1%2").arg(a).arg(b-a);
    return QString(" %1 ").arg(a);
}

QString nbsp(QString str)
{
    return str.replace("　", "&nbsp;");
}

void MainWindow::on_pushButton_clicked()
{
    if ( ui->lineEdit->text()=="" || ui->lineEdit_2->text()=="" ) return;
    int n1 = ui->lineEdit->text().toInt() - 1;
    int n2 = ui->lineEdit_2->text().toInt() - 1;
    Player *p1 = player[n1];
    Player *p2 = player[n2];
    int d1 = p1->getPotion();
    int d2 = p2->getPotion();
    bool b1 = p1->isInfected();
    bool b2 = p2->isInfected();
    if ( n1<0 || n2<0 || n1>=players || n2>=players || n1==n2 ) return;
    p1->contactwith(p2);
    ui->textEdit->append(QString("<font color=\"%1\">%2(%3)</font>==接触=="
                                 "<font color=\"%4\">%5(%6)</font>")
                         .arg(b1 ? "red" : "green")
                         .arg(nbsp(p1->getName()))
                         .arg(getDelta(d1, p1->getPotion()))
                         .arg(b2 ? "red" : "green")
                         .arg(nbsp(p2->getName()))
                         .arg(getDelta(d2, p2->getPotion())));
    chart->sort();
}

void MainWindow::on_pushButton_2_clicked()
{
    if ( ui->lineEdit_3->text()=="" ) return;
    int n = ui->lineEdit_3->text().toInt() - 1;
    Player *p = player[n];
    if ( n<0 || n>=players ) return;
    int d = p->getPotion();
    p->takePills();
    ui->textEdit->append(QString("<font color=\"%1\">%2(%3)</font>==吃药==")
                         .arg(p->isInfected() ? "red" : "green")
                         .arg(nbsp(p->getName()))
                         .arg(getDelta(d, p->getPotion())));
    chart->sort();
}

int currentLine = 0;

void MainWindow::on_pushButton_3_clicked()
{
    ui->plainTextEdit->setProperty("readOnly", true);
    QString str = ui->plainTextEdit->toPlainText().section("\n", currentLine, currentLine);
    currentLine++;
    int n1 = str.section(",", 0, 0).toInt();
    int n2 = str.section(",", -3, -3).toInt();
    if (n1==n2)
    {
        ui->lineEdit_3->setText(QString::number(n1));
        on_pushButton_2_clicked();
    } else {
        ui->lineEdit->setText(QString::number(n1));
        ui->lineEdit_2->setText(QString::number(n2));
        on_pushButton_clicked();
    }
}

void MainWindow::on_pushButton_4_clicked()
{
    for (int i=0; i<200; i++)
        on_pushButton_3_clicked();
}

void MainWindow::on_pushButton_5_clicked()
{
    QMessageBox msgbox("Warning", "Sorry, I am unable to make it. Orz\n"
                                  "Press Ok to exit, or cancel me.\n"
                                  "You can restart infection.exe manually.",
                       QMessageBox::Warning, QMessageBox::Ok, QMessageBox::Cancel, 0);
    if (msgbox.exec()==QMessageBox::Ok)
        this->deleteLater();
    //-.- how to do this
}
