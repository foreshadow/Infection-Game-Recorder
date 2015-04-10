#include "mainwindow.h"
#include "dialog.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    extern QPixmap *logopix;
    logopix = new QPixmap("img/icon/logo.png");
    a.setWindowIcon(QIcon(*logopix));
    Dialog dlg;
    if ( dlg.exec() == QDialog::Rejected ) return 0;
    MainWindow w;
    w.show();
    return a.exec();
}
