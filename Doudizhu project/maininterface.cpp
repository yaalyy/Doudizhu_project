//
//  maininterface.cpp
//  Doudizhu project
//
//  Created by ARCK on 03/02/2021.
//

#include "maininterface.h"
#include "ui_maininterface.h"
#include <QDebug>
#include <QMessageBox>
#include <QApplication>

#define card_width 80
#define card_height 105

MainInterface::MainInterface(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainInterface)
{
    ui->setupUi(this);
    setWindowTitle("Doudizhu Game");
    setFixedSize(1000,650);
    m_gameprocess = new GameProcess(this);

    Init();
    InitCardsMap();

    /*****signals to gameprocess**********/
    connect(m_gameprocess,SIGNAL(TellPlayerStatus(Player*,Player::PlayerStatus)),\
            this,SLOT(SetPlayerStatus(Player*,Player::PlayerStatus)));
    connect(m_gameprocess,SIGNAL(TellPlayerCallLord(Player*,int)),\
            this,SLOT(CallingLord(Player*,int)));
    connect(m_gameprocess,SIGNAL(TellPlayerPlayHand(Player*,QList<card>)),\
            this,SLOT(PlayingHand(Player*,QList<card>)));
    connect(m_gameprocess,SIGNAL(TellGameProcess(GameProcess::GameStatus)),\
            this,SLOT(StartProcess(GameProcess::GameStatus)));
}

MainInterface::~MainInterface()
{
    delete ui;
}

void MainInterface::Init()
{
    QFont ft;
    ft.setPointSize(30);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);

    time=60;
    MoveDistance=0;
    m_pickingCardTimer=new QTimer(this);
    m_pickingCardTimer->setInterval(8);
    connect(m_pickingCardTimer,SIGNAL(timeout()),this,SLOT(PickingCards()));

    /*set cards moving and not moving*/
    m_AllCardsPic.load(":/resources/card2.png");
    m_cardBackPic = m_AllCardsPic.copy(160,4*105,80,105);
    m_basecardPos = QPoint( (width()-card_width)/2, height()/2-100 );
    m_movingcard=new CardPicture(this);
    m_basecard=new CardPicture(this);
    m_movingcard->setPic(m_cardBackPic);
    m_basecard->setPic(m_cardBackPic);
    m_movingcard->move(m_basecardPos);
    m_basecard->move(m_basecardPos);

    //images of a clock
    m_clock=new QLabel(this);
    m_clock->setPixmap(QPixmap(":/resources/clock.png"));
  //  m_clock->move((width()-m_clock->width())/2-10,(height()-m_clock->width())/2+30);
    m_clock->move(434,305);
    m_clock->hide();

    m_rePickingCards = new QLabel(this);
    m_rePickingCards->setText("Reallocating Cards");
    m_rePickingCards->setFont(ft);
    m_rePickingCards->setPalette(pa);
    m_rePickingCards->move((width()-m_clock->width())/2-50,(height()-m_clock->height())/2);
    m_rePickingCards->hide();

    QPalette timer_color;
    timer_color.setColor(QPalette::WindowText,Qt::red);

    m_timeLabel=new QLabel(this);
    m_timeLabel->setFont(ft);
    m_timeLabel->setPalette(timer_color);
    m_timeLabel->move(490,350);
    m_timeLabel->hide();

    timer=new QTimer(this);
    timer->setInterval(1000);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeDisplay()));

    /*initialise buttons*/
    /*the button to start a game*/
    m_start= new QPushButton(this);
    m_start->setText("Start Game");
    m_start->move((width()-m_start->width())/2-5,height()-card_height-100);
    connect(m_start,SIGNAL(clicked()),this,SLOT(on_start_clicked()));

    /*buttons to be a landlord*/
    m_bet0=new QPushButton(this);
    m_bet1=new QPushButton(this);
    m_bet2=new QPushButton(this);
    m_bet3=new QPushButton(this);

    m_bet0->hide();
    m_bet1->hide();
    m_bet2->hide();
    m_bet3->hide();

    m_bet0->setText("Do Not Bid");
    m_bet1->setText("1");
    m_bet2->setText("2");
    m_bet3->setText("3");

    m_bet0->move(360,height()-card_height-50);
    m_bet1->move(480,height()-card_height-50);
    m_bet2->move(530,height()-card_height-50);
    m_bet3->move(580,height()-card_height-50);

    connect(m_bet0,SIGNAL(clicked()),this,SLOT(on_bet0_clicked()));
    connect(m_bet1,SIGNAL(clicked()),this,SLOT(on_bet1_clicked()));
    connect(m_bet2,SIGNAL(clicked()),this,SLOT(on_bet2_clicked()));
    connect(m_bet3,SIGNAL(clicked()),this,SLOT(on_bet3_clicked()));

    /*buttons for playing the game*/
    m_playhand=new QPushButton(this);
    m_pass = new QPushButton(this);
    m_tip = new QPushButton(this);
    m_playhand->hide();
    m_pass->hide();
    m_tip->hide();
    m_playhand->setText("Play");
    m_pass->setText("Pass");
    m_tip->setText("Reminder");
    m_pass->move(width()/2-160,height()-card_height-40);
    m_playhand->move(width()/2+60,height()-card_height-40);
    m_tip->move(width()/2-40,height()-card_height-40);

    connect(m_playhand,SIGNAL(clicked()),this,SLOT(on_playhand_clicked()));
    connect(m_pass,SIGNAL(clicked()),this,SLOT(on_pass_clicked()));
    connect(m_tip,SIGNAL(clicked()),this,SLOT(on_tip_clicked()));

    /*the button to continue the next game*/
    m_continue= new QPushButton(this);
    m_continue->hide();
    m_continue->setText("New Game");
    m_continue->move((width()-m_continue->width())/2-30,height()-card_height-40);

    connect(m_continue,SIGNAL(clicked()),this,SLOT(on_continue_clicked()));

    /*Sound*/
    bkMusic=new QSound(":/resources/bkMusic.wav",this);
    winMusic=new QSound(":/resources/win.wav",this);
    loseMusic=new QSound(":/resources/loseMusic.wav",this);
    shuffleCardsMusic=new QSound(":/resources/shuffleCardsMusic.wav",this);
    passMusic=new QSound(":/resources/passMusic.wav",this);
   // noCallMusic=new QSound(":/sound/res/bujiao.wav",this);
   // callLordMusic=new QSound(":/sound/res/jiaodizhu.wav",this);
    bkMusic->play();
    bkMusic->setLoops(-1);

    /*the label of bet points*/
    m_gameprocess->getDownPlayer()->betLabel=new QLabel(this);
    m_gameprocess->getDownPlayer()->betLabel->setFont(ft);
    m_gameprocess->getDownPlayer()->betLabel->setPalette(pa);
    m_gameprocess->getDownPlayer()->betLabel->move(width()/2,height()-card_height-50);

    m_gameprocess->getLeftPlayer()->betLabel=new QLabel(this);
    m_gameprocess->getLeftPlayer()->betLabel->setFont(ft);
    m_gameprocess->getLeftPlayer()->betLabel->setPalette(pa);
    m_gameprocess->getLeftPlayer()->betLabel->move(150,m_basecardPos.y());

    m_gameprocess->getRightPlayer()->betLabel=new QLabel(this);
    m_gameprocess->getRightPlayer()->betLabel->setFont(ft);
    m_gameprocess->getRightPlayer()->betLabel->setPalette(pa);
    m_gameprocess->getRightPlayer()->betLabel->move(width()-250,m_basecardPos.y());

    /*the label of pass*/
    m_gameprocess->getDownPlayer()->passLabel=new QLabel(this);
    m_gameprocess->getDownPlayer()->passLabel->setText("Pass");
    m_gameprocess->getDownPlayer()->passLabel->move(width()/2-50,(height()-card_height-100));
    m_gameprocess->getDownPlayer()->passLabel->setFont(ft);
    m_gameprocess->getDownPlayer()->passLabel->setPalette(pa);
    m_gameprocess->getDownPlayer()->passLabel->hide();

    m_gameprocess->getLeftPlayer()->passLabel=new QLabel(this);
    m_gameprocess->getLeftPlayer()->passLabel->setText("Pass");
    m_gameprocess->getLeftPlayer()->passLabel->move(150,m_basecardPos.y());
    m_gameprocess->getLeftPlayer()->passLabel->setFont(ft);
    m_gameprocess->getLeftPlayer()->passLabel->setPalette(pa);
    m_gameprocess->getLeftPlayer()->passLabel->hide();

    m_gameprocess->getRightPlayer()->passLabel=new QLabel(this);
    m_gameprocess->getRightPlayer()->passLabel->setText("Pass");
    m_gameprocess->getRightPlayer()->passLabel->move(width()-250,m_basecardPos.y());
    m_gameprocess->getRightPlayer()->passLabel->setFont(ft);
    m_gameprocess->getRightPlayer()->passLabel->setPalette(pa);
    m_gameprocess->getRightPlayer()->passLabel->hide();

    /*the label of players*/
    m_gameprocess->getDownPlayer()->roleLabel=new QLabel(this);
    m_gameprocess->getDownPlayer()->roleLabel->move(700,400);
    m_gameprocess->getDownPlayer()->roleLabel->hide();

    m_gameprocess->getLeftPlayer()->roleLabel=new QLabel(this);
    m_gameprocess->getLeftPlayer()->roleLabel->move(110,50);
    m_gameprocess->getLeftPlayer()->roleLabel->hide();

    m_gameprocess->getRightPlayer()->roleLabel=new QLabel(this);
    m_gameprocess->getRightPlayer()->roleLabel->move(820,50);
    m_gameprocess->getRightPlayer()->roleLabel->hide();

}

void MainInterface::InitCardsMap()
{
    //jokers will be added at the end
    card c;
    c.point = Card_BJ;
    c.suit = Suit_Begin;
    CutCardPic(card_width, 4 * card_height, c);

    c.point = Card_SJ;
    c.suit = Suit_Begin;
    CutCardPic(0, 4 * card_height, c);

    for (int point = Card_2, j = 12; point>Card_Begin; point--,j--)
    {
        for (int suit = Suit_End-1, i = 3; suit>Suit_Begin; suit--,i--)
        {
            card c;
            c.point=(CardPoint)point;
            c.suit =(CardSuit)suit;
            CutCardPic( j * card_width, i * card_height, c);
        }
    }

}

void MainInterface::timeDisplay()
{
    if(m_gameprocess->m_gamestatus==GameProcess::CallingLord && time<1)
    {
        NoOneCallLord();
        return;
    }

    if(time<1)
    {
        timer->stop();
        on_pass_clicked();


    }
    else
    {
        QString str;
        str.setNum(--time);
        m_timeLabel->setText(str);
    }


}

void MainInterface::CutCardPic(int x,int y,card c)
{
    QPixmap pic = m_AllCardsPic.copy(x,y,card_width,card_height);
    CardPicture* cardpic = new CardPicture(this);
    cardpic->hide();

    cardpic->setPic(pic);
    cardpic->setCard(c);

    m_Cards.insert(c,cardpic);       //insert into QMap
    connect(cardpic,SIGNAL(TellSelected()),this,SLOT(CardSelected()));
}

void MainInterface::StartProcess(GameProcess::GameStatus status)
{
    switch(status)
    {
    case (GameProcess::PickingCard):
        shuffleCardsMusic->play();
        shuffleCardsMusic->setLoops(-1);
        ReStart();
        m_basecard->show();
        m_movingcard->show();
        m_pickingCardTimer->start();
        m_gameprocess->m_gamestatus=GameProcess::PickingCard;
        break;
    case (GameProcess::CallingLord):
        m_gameprocess->m_gamestatus=GameProcess::CallingLord;
        m_timeLabel->setText("60");
        m_timeLabel->show();
        timer->start();
        m_clock->show();
        PlayerStartCallingLord();
        break;
    case (GameProcess::PlayingHand):
        m_gameprocess->m_gamestatus=GameProcess::PlayingHand;
        m_clock->hide();
        //labels of players
        if(m_gameprocess->getDownPlayer()->getRole()==Player::Lord)
            m_gameprocess->getDownPlayer()->roleLabel->setPixmap(QPixmap(":/resources/lord.png"));
        else
            m_gameprocess->getDownPlayer()->roleLabel->setPixmap(QPixmap(":/resources/farmer.png"));

        m_gameprocess->getDownPlayer()->roleLabel->show();

        if(m_gameprocess->getLeftPlayer()->getRole()==Player::Lord)
            m_gameprocess->getLeftPlayer()->roleLabel->setPixmap(QPixmap(":/resources/lord.png"));
        else
            m_gameprocess->getLeftPlayer()->roleLabel->setPixmap(QPixmap(":/resources/farmer.png"));

        m_gameprocess->getLeftPlayer()->roleLabel->show();

        if(m_gameprocess->getRightPlayer()->getRole()==Player::Lord)
            m_gameprocess->getRightPlayer()->roleLabel->setPixmap(QPixmap(":/resources/lord.png"));
        else
            m_gameprocess->getRightPlayer()->roleLabel->setPixmap(QPixmap(":/resources/farmer.png"));

        m_gameprocess->getRightPlayer()->roleLabel->show();

        m_bet0->hide();
        m_bet1->hide();
        m_bet2->hide();
        m_bet3->hide();

        m_gameprocess->getDownPlayer()->betLabel->hide();
        m_gameprocess->getLeftPlayer()->betLabel->hide();
        m_gameprocess->getRightPlayer()->betLabel->hide();

        QList<card> restthreecards=m_gameprocess->getAllCards();
        //add the rest of three landlord cards
        for(int i=0;i<3;i++)
        {
            m_gameprocess->getCurrentPlayer()->addCard(restthreecards[i]);
            CardPicture* cardpic=new CardPicture(this);
            cardpic->setPic(m_Cards.value(restthreecards[i])->getPic());

            m_restThreeCards.append(cardpic);
            m_restThreeCards[i]->move(360+i*100,5);
            m_restThreeCards[i]->setTurn(true);
            m_restThreeCards[i]->show();
        }
        m_gameprocess->getAllCards().clear();
        UpdateCards(m_gameprocess->getCurrentPlayer());
        break;
    }
}

void MainInterface::SetPlayerStatus(Player *player, Player::PlayerStatus status)
{
    if( status==Player::waitingCallingLord )
    {
        if(player==m_gameprocess->getDownPlayer())
        {
            m_bet0->show();
            m_bet1->show();
            m_bet2->show();
            m_bet3->show();
        }
    }
    else if(status==Player::waitingPlayingHand)
    {
        /*hide cards played previously*/
        QList<card> cardsToPlay=player->getCardsToPlay();
        for(int i=0;i<cardsToPlay.size();i++)
            m_Cards.value(cardsToPlay[i])->hide();

        player->passLabel->hide();

        player->getCardsToPlay().clear();

        if(player==m_gameprocess->getDownPlayer())
        {
            time=60;
            timer->start();
            m_timeLabel->setText("60");
            m_timeLabel->show();
            m_clock->show();

            //if the current player is the strongest, hide the button of Pass
            if((m_gameprocess->getHitPlayer()==m_gameprocess->getDownPlayer())
                    ||(m_gameprocess->getHitPlayer()==NULL))
            {
                m_pass->hide();
                //m_playhand->move((width()-m_playhand->width())/2,height()-card_height-40);
                //m_playhand->show();
                //m_tip->show();
            }
            else
            {
                m_pass->show();
                // m_playhand->move(width()/2+40,height()-card_height-40);
                //                m_playhand->show();
                //                m_tip->show();
            }
            m_playhand->show();
            m_tip->show();

        }
        else
        {
            timer->stop();
            m_timeLabel->hide();
            m_clock->hide();

            m_tip->hide();
            m_pass->hide();
            m_playhand->hide();
        }
    }
    else if(status==Player::winning)
    {
        m_playhand->hide();
        m_pass->hide();
        m_tip->hide();
        m_clock->hide();
        m_timeLabel->hide();
        timer->stop();

        //turn landlord cards over
        card c;
        foreach(c,m_gameprocess->getDownPlayer()->getCards())
            m_Cards.value(c)->setTurn(true);
        foreach(c,m_gameprocess->getLeftPlayer()->getCards())
            m_Cards.value(c)->setTurn(true);
        foreach(c,m_gameprocess->getRightPlayer()->getCards())
            m_Cards.value(c)->setTurn(true);

        UpdateCards(m_gameprocess->getDownPlayer());
        UpdateCards(m_gameprocess->getLeftPlayer());
        UpdateCards(m_gameprocess->getRightPlayer());

        m_continue->show();
        if(player->getRole()==m_gameprocess->getDownPlayer()->getRole())
        {
            winMusic->play();
            QMessageBox::about(this,tr("Result"),tr("You Win!"));
        }
        else
        {
            loseMusic->play();
            QMessageBox::about(this,tr("Result"),tr("You Lose!"));
        }

        m_gameprocess->setCurrentPlayer(player);
    }
}


void MainInterface::on_start_clicked()
{
    bkMusic->stop();
    m_start->hide();                            //hide the button of start
    StartProcess(GameProcess::PickingCard);     //run the game process
}

void MainInterface::PickingCards()
{
    Player* curPlayer=m_gameprocess->getCurrentPlayer();
    if(MoveDistance>270)
    {
        m_gameprocess->getOneCard(curPlayer);
        MoveDistance=0;
        UpdateCards(curPlayer);

        if(m_gameprocess->getAllCards().size() ==3)            //allocation of cards ends
        {
            shuffleCardsMusic->stop();
            m_pickingCardTimer->stop();

            m_movingcard->hide();
            m_basecard->hide();
            m_gameprocess->setCurrentPlayer(m_gameprocess->getNextPlayer());

            StartProcess(GameProcess::CallingLord);
            return;
        }

        m_gameprocess->setCurrentPlayer(m_gameprocess->getNextPlayer());


    }
    else
    {
        MoveDistance+=14;
        PickingCardsAnimation(curPlayer);
    }
}

void MainInterface::PickingCardsAnimation(Player* player)
{

    if(player == m_gameprocess->getLeftPlayer())
        m_movingcard->move(m_basecardPos.x()-MoveDistance*1.5,m_basecardPos.y());
    if(player == m_gameprocess->getRightPlayer())
        m_movingcard->move(MoveDistance*1.5+m_basecardPos.x(),m_basecardPos.y());
    if(player == m_gameprocess->getDownPlayer())
        m_movingcard->move(m_basecardPos.x(),m_basecardPos.y()+MoveDistance);
}

void MainInterface::paintEvent(QPaintEvent *event)
{
    /*background image*/
    QPixmap bk(":/resources/bk.png");
    QPainter painter(this);
    painter.drawPixmap(this->rect(),bk);
}


void MainInterface::CardSelected()
{
    if( (m_gameprocess->m_gamestatus) == GameProcess::PickingCard) return;

    CardPicture* cardpic=(CardPicture*) sender();//signals of images of cards

    QSet<CardPicture*>::iterator  it=m_Selected.find(cardpic);
    if(cardpic->getSelected())
    {
        cardpic->setSelected(false);
        m_Selected.remove(cardpic);
    }
    else
    {
        cardpic->setSelected(true);
        m_Selected.insert(cardpic);
    }
    UpdateCards(m_gameprocess->getDownPlayer()); //update cards in hand
}

void MainInterface::UpdateCards(Player *player)
{
    QList<card> cards=player->getCards();
    qSort(cards.begin(),cards.end(),qGreater<card>());//sort cards in hand
    int cardsInterval=20;

    //show cards in hand
    if(player == m_gameprocess->getDownPlayer())
    {
        for(int j=0;j<cards.size();j++)
        {
            int topBorder = (height()-card_height-5);                           //the top border
            int leftbase=m_basecardPos.x()-((cards.size()-1)*cardsInterval)/2;  //the start point from left
            CardPicture* cardpic=m_Cards.value(cards[j]);
            cardpic->setTurn(true);
            if(cardpic->getSelected()) topBorder-=10;

            cardpic->move(leftbase+j*cardsInterval,topBorder);
            cardpic->show();
        }
    }
    else
    {

        if(player == m_gameprocess->getLeftPlayer())
        {
            int leftBorder=5,upbase;
            for(int j=0;j<cards.size();j++)
            {
                upbase= m_basecardPos.y()-((cards.size()-1)*cardsInterval)/2;
                CardPicture* cardpic = m_Cards.value(cards[j]);

                cardpic->move(leftBorder,upbase+j*cardsInterval);
                cardpic->show();
            }

        }
        else if(player == m_gameprocess->getRightPlayer())
        {
            int leftBorder=width()-card_width-5,upbase;
            for(int j=0;j<cards.size();j++)
            {
                upbase= m_basecardPos.y()-((cards.size()-1)*cardsInterval)/2;
                CardPicture* cardpic = m_Cards.value(cards[j]);
                cardpic->move(leftBorder,upbase+j*cardsInterval);
                cardpic->show();
            }
        }
    }

    //cards are played
    QList<card> cardsToPlay = player->getCardsToPlay();
    if(!cardsToPlay.isEmpty())
    {
        //sorting
        qSort(cardsToPlay.begin(),cardsToPlay.end(),qGreater<card>());
        if(player==m_gameprocess->getDownPlayer())
        {
            for(int i=0;i<cardsToPlay.size();i++)
            {
                int topBorder = (height()-card_height-150);
                int leftbase=m_basecardPos.x()-((cardsToPlay.size()-1)*cardsInterval)/2;

                CardPicture* cardpic=m_Cards.value(cardsToPlay[i]);
                cardpic->setTurn(true);
                cardpic->move(leftbase+i*cardsInterval,topBorder);
                cardpic->show();
            }
        }
        else if(player==m_gameprocess->getLeftPlayer())
        {
            int topBorder = m_basecardPos.y();
            int leftbase=105;

            for(int i=0;i<cardsToPlay.size();i++)
            {
                CardPicture* cardpic=m_Cards.value(cardsToPlay[i]);
                cardpic->setTurn(true);
                cardpic->move(leftbase+i*cardsInterval,topBorder);
                cardpic->show();
            }
        }
        else if(player==m_gameprocess->getRightPlayer())
        {
            int topBorder = m_basecardPos.y();
            int leftbase = width()-card_width*2-105-(cardsToPlay.size()-1)*cardsInterval;
            for(int i=0;i<cardsToPlay.size();i++)
            {
                CardPicture* cardpic=m_Cards.value(cardsToPlay[i]);
                cardpic->setTurn(true);
                cardpic->move(leftbase+i*cardsInterval,topBorder);
                cardpic->show();
            }
        }
    }

}

void MainInterface::PlayerStartPlayingHand()
{
    /*get the type of group from images of cards*/
    if(m_Selected.isEmpty()) return;
    QList<card> cards;
    QSet<CardPicture*>::iterator it = m_Selected.begin();
    for(;it!=m_Selected.end();it++)
        cards.append((*it)->getCard());

    /****************judge if cards are able to be played*********************/
    Hand hand(cards);
    //if type is unknown, cards connot be played
    if( hand.getHandType() == Hand_Unknown )
    {
        qDebug()<<"Unkown HandType";
        return;
    }

    //if a group of cards cannot beat the other group, this group cannot be played
    Hand handToHit(m_gameprocess->getHitCards());
    Player* hitPlayer=m_gameprocess->getHitPlayer();
    if(hitPlayer!=m_gameprocess->getDownPlayer()&&hitPlayer!=NULL)
        if(!hand.Defeat(handToHit))
        {
            qDebug()<<"Cannot Defeat";
            return;
        }


    /****************************************/
    m_Selected.clear();
    m_gameprocess->getDownPlayer()->playHand(cards);

}

void MainInterface::PlayerStartCallingLord()
{
    SetPlayerStatus(m_gameprocess->getCurrentPlayer(),Player::waitingCallingLord);
    m_gameprocess->getCurrentPlayer()->beginCallingLord();
}

void MainInterface::PlayingHand(Player* player,QList<card> cards)
{
    HandType type=Hand(cards).getHandType();

    switch(type)
    {
    case Hand_Pass:
        handtype=new QSound(":/resources/passMusic.wav",this);
        player->passLabel->show();
        break;
    case Hand_Triple:
        handtype=new QSound(":/sound/res/sange.wav",this);
        break;
    case Hand_Triple_Single:
        handtype=new QSound(":/sound/res/sandaiyi.wav",this);
        break;
    case Hand_Triple_Pair:
        handtype=new QSound(":/sound/res/sandaiyidui.wav",this);
        break;
    case Hand_Plane:
    case Hand_Plane_Two_Single:
    case Hand_Plane_Two_Pair:
        handtype=new QSound(":/resources/planeMusic.wav",this);
        break;
    case Hand_Bomb:
        handtype=new QSound(":/sound/res/zhadan.wav",this);
        break;
    case Hand_Bomb_Jokers:
        handtype=new QSound(":/sound/res/bombJokerMusic.wav",this);
        break;
    case Hand_Seq_Single:
        handtype=new QSound(":/sound/res/shunzi.wav",this);
        break;
    case Hand_Seq_Pair:
        handtype=new QSound(":/sound/res/liandui.wav",this);
        break;

    case Hand_Single:
    {
        switch(cards[0].point)
        {
        case Card_A:
            handtype=new QSound(":/sound/res/1.wav",this);
            break;
        case Card_2:
            handtype=new QSound(":/sound/res/2.wav",this);
            break;
        case Card_3:
            handtype=new QSound(":/sound/res/3.wav",this);
            break;
        case Card_4:
            handtype=new QSound(":/sound/res/4.wav",this);
            break;
        case Card_5:
            handtype=new QSound(":/sound/res/5.wav",this);
            break;
        case Card_6:
            handtype=new QSound(":/sound/res/6.wav",this);
            break;
        case Card_7:
            handtype=new QSound(":/sound/res/7.wav",this);
            break;
        case Card_8:
            handtype=new QSound(":/sound/res/8.wav",this);
            break;
        case Card_9:
            handtype=new QSound(":/sound/res/9.wav",this);
            break;
        case Card_10:
            handtype=new QSound(":/sound/res/10.wav",this);
            break;
        case Card_J:
            handtype=new QSound(":/sound/res/11.wav",this);
            break;
        case Card_Q:
            handtype=new QSound(":/sound/res/12.wav",this);
            break;
        case Card_K:
            handtype=new QSound(":/sound/res/13.wav",this);
            break;
        case Card_SJ:
            handtype=new QSound(":/sound/res/14.wav",this);
            break;
        case Card_BJ:
            handtype=new QSound(":/sound/res/15.wav",this);
            break;

        }
        break;
    }
    case Hand_Pair:
    {

        switch((int)cards[0].point)
        {
        case Card_A:
            handtype=new QSound(":/sound/res/dui1.wav",this);
            break;
        case Card_2:
            handtype=new QSound(":/sound/res/dui2.wav",this);
            break;
        case Card_3:
            handtype=new QSound(":/sound/res/dui3.wav",this);
            break;
        case Card_4:
            handtype=new QSound(":/sound/res/dui4.wav",this);
            break;
        case Card_5:
            handtype=new QSound(":/sound/res/dui5.wav",this);
            break;
        case Card_6:
            handtype=new QSound(":/sound/res/dui6.wav",this);
            break;
        case Card_7:
            handtype=new QSound(":/sound/res/dui7.wav",this);
            break;
        case Card_8:
            handtype=new QSound(":/sound/res/dui8.wav",this);
            break;
        case Card_9:
            handtype=new QSound(":/sound/res/dui9.wav",this);
            break;
        case Card_10:
            handtype=new QSound(":/sound/res/dui10.wav",this);
            break;
        case Card_J:
            handtype=new QSound(":/sound/res/dui11.wav",this);
            break;
        case Card_Q:
            handtype=new QSound(":/sound/res/dui12.wav",this);
            break;
        case Card_K:
            handtype=new QSound(":/sound/res/dui13.wav",this);
            break;
        }
        break;
    }

    }
    handtype->play();
    player->getCardsToPlay()=cards;   //move selected cards to a buffer
    UpdateCards(player);              //play cards
}

void MainInterface::CallingLord(Player *player, int bet)
{
    switch(bet)
    {
    case 3:
        player->betLabel->setText(("3"));
        //callLordMusic->play();
        break;
    case 2:
        player->betLabel->setText("2");
        //callLordMusic->play();
        break;
    case 1:
        player->betLabel->setText("1");
        //callLordMusic->play();
        break;
    case 0:
        player->betLabel->setText("Do Not Bid");
       // player->betLabel->move(440,height()-card_height-50);
        //noCallMusic->play();
        break;
    }

    player->betLabel->show();

    if(player==m_gameprocess->getDownPlayer())
    {
        m_bet0->hide();
        m_bet1->hide();
        m_bet2->hide();
        m_bet3->hide();
    }
}

void MainInterface::NoOneCallLord()
{
    timer->stop();
    m_rePickingCards->show();
    QTime dieTime = QTime::currentTime().addMSecs(800);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 2000);

    m_rePickingCards->hide();

    //if nobody wants to be a landlord, reallocate cards
    if(m_gameprocess->BetList.size()==0)
    {
        m_timeLabel->hide();
        m_clock->hide();
        StartProcess(GameProcess::PickingCard);
    }
    return;
}

void MainInterface::on_bet0_clicked()
{
    m_gameprocess->getDownPlayer()->callingLord(0);
}

void MainInterface::on_bet1_clicked()
{
    m_gameprocess->getDownPlayer()->callingLord(1);
}

void MainInterface::on_bet2_clicked()
{
    m_gameprocess->getDownPlayer()->callingLord(2);
}

void MainInterface::on_bet3_clicked()
{
    m_gameprocess->getDownPlayer()->callingLord(3);
}

void MainInterface::on_playhand_clicked()
{
    PlayerStartPlayingHand();
}

void MainInterface::on_pass_clicked()
{
    //reset the position of cards
    CardPicture* cardpic;
    foreach(cardpic,m_Selected)
        cardpic->setSelected(false);
    m_Selected.clear();
    UpdateCards(m_gameprocess->getDownPlayer());
    m_gameprocess->getDownPlayer()->playHand(QList<card>());
}

void MainInterface::on_continue_clicked()
{
    StartProcess(GameProcess::PickingCard);
}

void MainInterface::on_tip_clicked()
{
    CardPicture* cardpic;
    foreach(cardpic,m_Selected)
        cardpic->setSelected(false);

    m_Selected.clear();
    Method st(m_gameprocess->getDownPlayer(),m_gameprocess->getDownPlayer()->getCards());
    QList<card> cards = st.MakeDecision();
    card c;
    foreach(c,cards)
    {
        m_Selected.insert(m_Cards.value(c));
    }

    foreach(cardpic,m_Selected)
    {
        cardpic->setSelected(true);
    }

    UpdateCards(m_gameprocess->getDownPlayer());
}

void MainInterface::ReStart()
{
    m_timeLabel->hide();
    m_clock->hide();
    timer->stop();
    time=60;
    m_gameprocess->getDownPlayer()->roleLabel->hide();
    m_gameprocess->getLeftPlayer()->roleLabel->hide();
    m_gameprocess->getRightPlayer()->roleLabel->hide();

    m_gameprocess->getDownPlayer()->betLabel->hide();
    m_gameprocess->getLeftPlayer()->betLabel->hide();
    m_gameprocess->getRightPlayer()->betLabel->hide();

    m_bet0->hide();
    m_bet1->hide();
    m_bet2->hide();
    m_bet3->hide();

    m_continue->hide();             //hide button of continue
    CardPicture* cardpic;           //hide images on the table
    foreach(cardpic,m_Cards)
    {
        cardpic->hide();
        cardpic->setTurn(false);
        cardpic->setSelected(false);
    }

    foreach(cardpic,m_restThreeCards)
        cardpic->hide();

    m_restThreeCards.clear();

    //hide the button of pass
    m_gameprocess->getDownPlayer()->passLabel->hide();
    m_gameprocess->getLeftPlayer()->passLabel->hide();
    m_gameprocess->getRightPlayer()->passLabel->hide();

    //clear cards in hand
    m_gameprocess->getDownPlayer()->getCards().clear();
    m_gameprocess->getRightPlayer()->getCards().clear();
    m_gameprocess->getLeftPlayer()->getCards().clear();

    m_gameprocess->getDownPlayer()->getCardsToPlay().clear();
    m_gameprocess->getRightPlayer()->getCardsToPlay().clear();
    m_gameprocess->getLeftPlayer()->getCardsToPlay().clear();
    m_gameprocess->Restart();

}

