#include "Main_Window.h"
#include "ui_Main_Window.h"
#include "Corruptor_Settings.h"

Main_Window::Main_Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Main_Window)
{
    ui->setupUi(this);
}

Main_Window::~Main_Window()
{
    delete ui;
}

void Main_Window::on_btnConfigure_clicked()
{
    Corruptor_Settings corruptorSettings(this);
    corruptorSettings.exec();
}

void Main_Window::on_btnGenerate_clicked()
{
    //TODO: Implement this...
}

void Main_Window::on_btnFileLocation_clicked()
{
    //TODO: Implement this...
}

void Main_Window::on_btnSaveLocation_clicked()
{
    //TODO: Implement this...
}
