#ifndef SPELPLAN_H
#define SPELPLAN_H

#include <QWidget>
#include <deque>
class Spelplan : public QWidget
{
    Q_OBJECT
public:

    explicit Spelplan(QWidget *parent = nullptr);
    ~Spelplan();

    void uppdateraSpelet();

private slots:
    void uppdateraMasken();
protected:
    void keyPressEvent(QKeyEvent * event) override;
    void paintEvent(QPaintEvent * event) override;
private :

    const int m_cellstorlek = 10;
    struct Pixel {
        Pixel(int x = 0, int y = 0) : m_x(x), m_y(y) {}
        int m_x;
        int m_y;
    };
    Pixel m_rkRiktning;
    Pixel m_rkHuvud;
    std::deque<Pixel> m_masken;

    const int m_timerintervall = 10; // in milliseconds
    const int m_spelplan_bredd = 400; // in pixels
    const int m_spelplan_hojd = 400; // in pixels
    const int m_matbitstorlek = 5; // in pixels

    Pixel slumpMatBit();
    bool krockarMedMatBit(Pixel huvud);
    bool krockarMedMasken(Pixel huvud);
    bool krockarMedVaggen(Pixel& huvud);

    Pixel m_fixedMatBit;
    bool m_gameOver = false;
};

//    const int m_cellstorlek = 10;
//    struct RK {
//        RK(int r=0, int k=0) : m_r(r),m_k(k){}
//        int m_r;
//        int m_k;

//    };
//    RK m_rkRiktning;
//    RK m_rkHuvude;
//    std::deque<RK> m_masken;

////    const int m_timerintervall = 50; // in milliseconds
//   const int m_spelplan_bredd = 400; // in pixels
//    const int m_spelplan_hojd = 400; // in pixels
//  const int m_matbitstorlek = 5; // in pixels
//    RK slumpMatBit();
//    bool krockarMedMatBit(RK huvud);

//    bool krockarMedMasken(RK huvud);
//    bool krockarMedVaggen(RK &huvud);
//    RK m_fixedMatBit ;
//     bool m_gameOver = false;


#endif // SPELPLAN_H
