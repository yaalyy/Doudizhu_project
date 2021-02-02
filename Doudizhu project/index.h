#ifndef INDEX_H
#define INDEX_H

#include <QWidget>
#include <QPushButton>
#include <QPaintEvent>
#include <QEvent>

namespace Ui {
class Index;
}

//the first page
class Index : public QWidget
{
    Q_OBJECT
public:
    explicit Index(QWidget *parent = 0);
    ~Index();
private:
    void originWindow();                            //initialise the window
    void paintEvent(QPaintEvent * event);           //set the background image
    void originDanjiButton();                       //initialise the button of single mode
    bool eventFilter(QObject * obj, QEvent * event);// avoid being clicked many times
private:
    Ui::Index *ui;
    //ui member:
    QPushButton * _danji;  //the button of single mode
    //non-ui member:
    bool _canDanji;        //if the button of single mode can be clicked
};

#endif // INDEX_H
