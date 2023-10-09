#include "spelplan.h"
#include <QTimer>
#include <QPainter>
#include <QKeyEvent>
#include <QPaintEvent>
#include <chrono>
#include <thread>
#include <deque>
using namespace std;


Spelplan::Spelplan(QWidget *parent)
    : QWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer,&QTimer :: timeout, this,&Spelplan ::uppdateraMasken);
    timer->start(50);
    setFocus();
    m_rkHuvud=Pixel(50,50);
    m_rkRiktning = Pixel(0,0);
    m_fixedMatBit = slumpMatBit();



}


Spelplan::~Spelplan()
{

}
void Spelplan::uppdateraMasken()
{

    for (auto it = m_masken.begin(); it != m_masken.end(); ++it) {
        if (it->m_x == m_rkHuvud.m_x && it->m_y == m_rkHuvud.m_y) {
            m_gameOver = true;
            break;
        }
    }


    m_masken.push_front(m_rkHuvud);


    if (m_masken.size() > 100) {
        m_masken.pop_back();
    }


    m_rkHuvud.m_x += m_rkRiktning.m_x;
    m_rkHuvud.m_y += m_rkRiktning.m_y;


    krockarMedVaggen(m_rkHuvud);


    if (krockarMedMatBit(m_rkHuvud)) {

        m_fixedMatBit = slumpMatBit();
    }

    for (auto it = m_masken.begin(); it != m_masken.end(); ++it) {
        if (it->m_x == m_rkHuvud.m_x && it->m_y == m_rkHuvud.m_y) {
            m_gameOver = true;
            break;
        }
    }


    if (m_gameOver) {
        update();
    }
}


//void Spelplan::uppdateraMasken()
//{

//    for (auto it = m_masken.begin(); it != m_masken.end(); ++it) {
//        if (it->m_x == m_rkHuvud.m_x && it->m_y == m_rkHuvud.m_y) {
//            m_gameOver = true;
//            break;
//        }
//    }

//    // Add the new position of the head to the deque
//    m_masken.push_front(m_rkHuvud);

//    // Remove the last position of the tail if the deque is too long
//    if (m_masken.size() > 100) {
//        m_masken.pop_back();
//    }

//    // Update the position of the head
//    m_rkHuvud.m_x += m_rkRiktning.m_x;
//    m_rkHuvud.m_y += m_rkRiktning.m_y;

//    // Update the widget if the game is not over
//    if (!m_gameOver) {
//        update();
//    }
//}
//#include "spelplan.h"
//#include <QTimer>
//#include <QPainter>
//#include <QKeyEvent>
//#include <QPaintEvent>
//#include <chrono>
//#include <thread>
//#include <deque>
//using namespace std;

//Spelplan::Spelplan(QWidget *parent)
//    : QWidget(parent)
//{
//    QTimer *timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, &Spelplan::uppdateraMasken);
//    timer->start(50);
//    setFocus();
//    m_rkHuvud = Pixel(50, 50);
//    m_rkRiktning = Pixel(0, 0);
//    m_fixedMatBit = slumpMatBit();
//}

//Spelplan::~Spelplan()
//{

//}

//void Spelplan::uppdateraMasken()
//{
//    //qDebug() << "Head position:" << m_rkHuvud.m_x << "," << m_rkHuvud.m_y;

//    // Check for collisions with the masken
//    for (auto it = m_masken.begin(); it != m_masken.end(); ++it) {
//        if (it->m_x == m_rkHuvud.m_x && it->m_y == m_rkHuvud.m_y) {
//            m_gameOver = true;
//            break;
//        }
//    }

//    // Add the new position of the head to the deque
//    m_masken.push_front(m_rkHuvud);

//    // Remove the last position of the tail if the deque is too long
//    if (m_masken.size() > 100) {
//        m_masken.pop_back();
//    }

//    // Update the position of the head
//    m_rkHuvud.m_x += m_rkRiktning.m_x;
//    m_rkHuvud.m_y += m_rkRiktning.m_y;

//    // Check for collisions with the walls
//    krockarMedVaggen(m_rkHuvud);

//    // Check for collisions with the matbit
//    if (krockarMedMatBit(m_rkHuvud)) {
//        m_fixedMatBit = slumpMatBit();
//    }

//    // Check for collisions with the masken again
//    for (auto it = m_masken.begin(); it != m_masken.end(); ++it) {
//        if (it->m_x == m_rkHuvud.m_x && it->m_y == m_rkHuvud.m_y) {
//            m_gameOver = true;
//            break;
//        }
//    }

//    // Update the display
//    if (!m_gameOver) {
//        update();
//    }
//}
//////////////////////////////////////////////////////////////////////////////////////////////////
void Spelplan::keyPressEvent(QKeyEvent *event)
{
    int k=event->key();
    if(k== Qt:: Key_Down) m_rkRiktning= Pixel(0,1);
    if(k== Qt:: Key_Up) m_rkRiktning= Pixel(0,-1);
    if(k== Qt:: Key_Left) m_rkRiktning= Pixel(-1,0);
    if(k== Qt:: Key_Right) m_rkRiktning= Pixel(1,0);
    uppdateraMasken();

    //this_thread::sleep_for( chrono::seconds(30));
}

void Spelplan::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    float cellbredd = m_cellstorlek * width() / m_spelplan_bredd;
    float cellhojd = m_cellstorlek * height() / m_spelplan_hojd;

    qDebug() << cellbredd << "\t" << cellhojd;

    for (unsigned int i = 0; i < m_masken.size(); ++i) {

        Pixel rk = m_masken[i];
        if (m_gameOver) {
            // Color red if the gameover
            painter.fillRect(rk.m_x * cellbredd,
                             rk.m_y * cellhojd,
                             cellbredd,
                             cellhojd,
                             Qt::red);
        } else {
            painter.fillRect(rk.m_x * cellbredd,
                             rk.m_y * cellhojd,
                             cellbredd,
                             cellhojd,
                             Qt::black);
        }
    }


    painter.fillRect(m_fixedMatBit.m_x * cellbredd,
                     m_fixedMatBit.m_y * cellhojd,
                     cellbredd,
                     cellhojd,
                     Qt::green);


//    painter.drawText()
}



Spelplan::Pixel Spelplan::slumpMatBit()
{

    int max_r = m_spelplan_hojd / m_cellstorlek;
    int max_k = m_spelplan_bredd / m_cellstorlek;
    int r = rand() % max_r;
    int k = rand() % max_k;
    return Pixel(r, k);

}

bool Spelplan::krockarMedMatBit(Pixel huvud)
{
//    if (){
//        return
//    }
   Pixel matBit = m_fixedMatBit;
   qDebug() << "X: " << huvud.m_x << " | " << matBit.m_x;
   qDebug() << "Y: " << huvud.m_y << " | " << matBit.m_y;
    return huvud.m_x == matBit.m_x && huvud.m_y == matBit.m_y;
//    int max_x = m_spelplan_hojd / m_matbitstorlek;
//    int max_y = m_spelplan_bredd / m_matbitstorlek;
//    int x = rand() % max_x;
//    int y = rand() % max_y;
//    return (x, y);

}
bool Spelplan::krockarMedMasken(Pixel huvud)
{

    for (auto it = m_masken.begin(); it != m_masken.end(); ++it) {
        if (it->m_x == huvud.m_x && it->m_y == huvud.m_y) {
            return true;
        }
    }
    return false;
}
bool Spelplan::krockarMedVaggen(Pixel& huvud)
{
    if (huvud.m_x < 0) {
        huvud.m_x = m_spelplan_bredd / m_cellstorlek - 1;
    } else if (huvud.m_x >= m_spelplan_bredd / m_cellstorlek) {
        huvud.m_x = 0;
    } else if (huvud.m_y < 0) {
        huvud.m_y = m_spelplan_hojd / m_cellstorlek - 1;
    } else if (huvud.m_y >= m_spelplan_hojd / m_cellstorlek) {
        huvud.m_y = 0;
    } else {
        return false;
    }

    return true;
}

