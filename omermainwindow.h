#ifndef OMERMAINWINDOW_H
#define OMERMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class OmerMainWindow; }
QT_END_NAMESPACE

class OmerMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    OmerMainWindow(QWidget *parent = nullptr);
    ~OmerMainWindow();

private:
    Ui::OmerMainWindow *ui;
};
#endif // OMERMAINWINDOW_H
