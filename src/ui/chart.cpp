#include "chart.h"

#include <QPainter>

Chart::Chart(int x, int y)
{
    playerList.clear();
    setPos(x, y);
}

Chart::~Chart()
{

}

QRectF Chart::boundingRect() const
{
    return QRectF(0, 0, 380, 500);
}

void Chart::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    int width = 400;
    int height = 500;
    int margin = 30;
    int barX = margin * 2;
    int barY = margin;
    int barW = 30;
    int barH = 20;
    int space = 3;
    painter->drawLine(barX, margin, barX, height - margin);
    painter->drawLine(barX, margin, width - margin, margin);
    for (int i=0; i<10; i++)
    {
        painter->drawLine(barX + i * barW, barY - barH/4, barX + i * barW, barY + barH/4);
        painter->drawText(barX + i * barW - 2, barY - barH/2, QString::number(i));
    }
    foreach (Player *p, playerList)
    {
        painter->drawText(barX - 45, barY + 18, p->getName());
        painter->fillRect(barX - 3, barY += space, p->getPotion() * barW + 3, barH,
                          p->isInfected() ? QColor(255, 0, 0, 127) : QColor(0, 255, 0, 127));
        painter->drawText(barX + 6, barY + 18, QString(p->getPotion()));
        barY += barH;
    }
}

void Chart::addPlayer(Player *p)
{
    playerList << p;
}

void Chart::sort()
{
    qSort(playerList.begin(), playerList.end(), lessthan);
    this->update();
}

bool Chart::lessthan(Player *p1, Player *p2)
{
    if (p1->isInfected() ^ p2->isInfected())
        if (p2->isInfected()) return true;
        else return false;
    else return p1->getPotion() > p2->getPotion();
}
