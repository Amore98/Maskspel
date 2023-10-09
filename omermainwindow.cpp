#include "omermainwindow.h"
#include "ui_omermainwindow.h"

OmerMainWindow::OmerMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OmerMainWindow)
{
    ui->setupUi(this);
}

OmerMainWindow::~OmerMainWindow()
{
    delete ui;
}

