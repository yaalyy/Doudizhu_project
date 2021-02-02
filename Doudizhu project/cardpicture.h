#ifndef CARDPICTURE_H
#define CARDPICTURE_H


#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include "card.h"


class CardPicture : public QWidget
{
    Q_OBJECT
public:
    CardPicture(QWidget *parent = 0);
    void setPic(QPixmap& pic);
    void setCard(card& c);
    card getCard();
    void setTurn(bool t);
    bool getTurn();
    void setSelected(bool s);
    bool getSelected();


    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);

    QPixmap &getPic();
signals:
    void TellSelected();    //card is selected

private:
    QPixmap m_pic;    //the picture of the front of a card
    QPixmap m_back;   //the picture of the back of a card
    bool m_turn;      //flip a card
    bool m_selected;  //whether a card is selected

    card m_card;      //card

};

#endif // CARDPICTURE_H
