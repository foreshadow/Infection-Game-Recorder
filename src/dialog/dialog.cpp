#include "dialog.h"
#include "ui_dialog.h"

#include "player.h"
#include <QMessageBox>
#include <QTime>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    if (ui->lineEdit->text()=="") return;
    ui->plainTextEdit->appendPlainText(ui->lineEdit->text());
    ui->lineEdit->clear();
}

void Dialog::on_pushButton_4_clicked()
{
    QString text1 = ui->plainTextEdit->toPlainText().replace("\n\n", "\n");
    if (text1.endsWith("\n")) text1 = text1.left(text1.length()-1);
    if (text1.startsWith("\n")) text1 = text1.right(text1.length()-1);
    ui->plainTextEdit->setPlainText(text1);
    int n1 = ui->plainTextEdit->blockCount();
    if (ui->plainTextEdit->toPlainText()=="") n1 = 0;

    QString text2 = ui->plainTextEdit_2->toPlainText().replace("\n\n", "\n");
    if (text2.endsWith("\n")) text2 = text2.left(text2.length()-1);
    if (text2.startsWith("\n")) text2 = text2.right(text2.length()-1);
    ui->plainTextEdit_2->setPlainText(text2);
    int n2 = ui->plainTextEdit_2->blockCount();
    if (ui->plainTextEdit_2->toPlainText()=="") n2 = 0;

    QMessageBox msgbox("Warning", QString("Are you sure to start the game?\nPlayers: %1, Infected: %2.")
                                  .arg(n1).arg(n2),
                       QMessageBox::Warning, QMessageBox::Ok, QMessageBox::Cancel, 0);
    if (msgbox.exec()==QMessageBox::Ok)
    {
        extern Player *player[50];
        extern int players;
        players = 0;
        for (int i=0; i<n1; i++)
            player[players++] = new Player(text1.section("\n", i, i),
                                           text2.indexOf(text1.section("\n", i, i))!=-1);
        accept();
    }
}


void Dialog::on_pushButton_3_clicked()
{
    QString text1 = ui->plainTextEdit->toPlainText().replace("\n\n", "\n");
    if (text1.endsWith("\n")) text1 = text1.left(text1.length()-1);
    if (text1.startsWith("\n")) text1 = text1.right(text1.length()-1);
    ui->plainTextEdit->setPlainText(text1);
    int n = ui->plainTextEdit->blockCount();
    int j = ui->lineEdit_2->text().toInt();
    if ( j > n ) return;
    ui->plainTextEdit_2->clear();
    qsrand(QTime::currentTime().msec());
    for (int i=0; i<j; i++)
    {
        int k;
        while ( k = qrand() % n,
                ui->plainTextEdit_2->toPlainText().indexOf(
                    ui->plainTextEdit->toPlainText().section("\n", k, k)) !=-1);
        ui->plainTextEdit_2->appendPlainText(ui->plainTextEdit->toPlainText().section("\n", k, k));
    }
}

void Dialog::on_pushButton_2_clicked()
{
    QMessageBox codebox
        ("Code", "void Player::contactwith(Player *p)           \n"
                 "    {                                         \n"
                 "        if ( !p->isInfected() && !isInfected()\n"
                 "             && goodContacted.indexOf(p)==-1) \n"
                 "        {                                     \n"
                 "            p->potion++;                      \n"
                 "            potion++;                         \n"
                 "            goodContacted << p;               \n"
                 "            p->goodContacted << this;         \n"
                 "        } else                                \n"
                 "                                              \n"
                 "        if ( p->isInfected() ^ isInfected() ) \n"
                 "        {                                     \n"
                 "            Player *good, *evil;              \n"
                 "            if ( p->isInfected() )            \n"
                 "            {                                 \n"
                 "                good = this;                  \n"
                 "                evil = p;                     \n"
                 "            } else {                          \n"
                 "                good = p;                     \n"
                 "                evil = this;                  \n"
                 "            }                                 \n"
                 "            if ( good->getPotion() )          \n"
                 "            {                                 \n"
                 "                good->potion--;               \n"
                 "                evil->cure();                 \n"
                 "            }                                 \n"
                 "            good->infect();                   \n"
                 "        }                                     \n"
                 "    }                                         \n"
               , QMessageBox::NoIcon, QMessageBox::Ok, 0, 0);
    codebox.exec();
}
