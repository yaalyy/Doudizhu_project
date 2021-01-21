#include "index.h"
#include "ui_index.h"
//#include "maininterface.h"
#include <QPixmap>
#include <QPainter>
#include <QFont>

Index::Index(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Index)
{
    originWindow();         //initialise the window
    originDanjiButton();    //initialise the button of starting the game
    ui->setupUi(this);
}

Index::~Index()
{
    delete ui;
}

//initialise the window
void Index::originWindow()
{
    setFixedSize(800,600); //set the size of the window
}

//set the background image
void Index::paintEvent(QPaintEvent *event)
{
    static QPixmap backpic(":/resources/register.jpg");
    QPainter painter(this);
    painter.drawPixmap(this->rect(),backpic);
}

//initialise the button to start the game
void Index::originDanjiButton()
{
    _danji=new QPushButton(this);
    _danji->setGeometry(200,180,400,70); //the size of the button
    QFont font;
    font.setPointSize(25);
    font.setFamily("Arial Rounded MT Bold");
    font.setBold(true);
    _danji->setFont(font);
    _danji->setStyleSheet("color:#2b2b2b");
    _danji->setCursor(Qt::PointingHandCursor);
    _danji->setText("Single    Player");
    _danji->installEventFilter(this);//listen to the action on the button
    _canDanji=true;                  //let the button can be clicked
}


/*
 * this filter is to avoid the button from clicking many times
 * if the single mode button is clicked and the button is available
 * {
 *      set the button to false
 *      close the window
 *      create a new window for game
 * }

 */
/*
bool Index::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==_danji && event->type()==QEvent::MouseButtonPress && _canDanji)
    {
        _canDanji=false;
        close();
        MainInterface * newPage=new MainInterface;
        newPage->setWindowTitle("Single Mode");
        newPage->show();
        return true;
    }

    return QWidget::eventFilter(obj,event);
}  */
