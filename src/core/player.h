#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QString name, bool infected = false, QObject *parent = 0);
    ~Player();

    int getPotion() const;
    bool isInfected() const;
    QString getName() const;

    void reset();
    void infect();
    void cure();
    void takePills();
    void contactwith(Player *p);

    const bool originInfected;

protected:
    int potion;
    bool infected;
    QList<Player*> goodContacted;
    QString name;

signals:

public slots:
};

#endif // PLAYER_H
