#include "mainwindow.h"
#include "dialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog dlg;
    if ( dlg.exec() == QDialog::Rejected ) return 0;
    MainWindow w;
    w.show();
    return a.exec();
}
