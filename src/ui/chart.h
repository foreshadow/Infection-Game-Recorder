#ifndef CHART_H
#define CHART_H

#include "player.h"
#include <QGraphicsItem>

class Chart : public QGraphicsItem
{
public:
    Chart(int x = 0, int y = 0);
    ~Chart();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    void addPlayer(Player *p);
    void sort();

protected:
    QList<Player*> playerList;
    static bool lessthan(Player *p1, Player *p2);
};

#endif // CHART_H
