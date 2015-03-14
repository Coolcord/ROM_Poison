#include "Main_Window.h"
#include "ui_Main_Window.h"
#include "Corruptor_Settings.h"

Main_Window::Main_Window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Main_Window) {
    this->settings = new Settings();
    this->settings->startingOffset = 0;
    this->settings->endingOffset = 999999999;
    this->settings->incrementMinNum = 1;
    this->settings->incrementMaxNum = 0x1000;
    this->settings->random = true;
    this->settings->add = false;
    this->settings->shiftLeft = false;
    this->settings->replace = false;
    this->settings->addNum = 0;
    this->settings->shiftLeftNum = 0;
    this->settings->replace = 0;
    ui->setupUi(this);
}

Main_Window::~Main_Window() {
    delete ui;
    delete settings;
}

void Main_Window::on_btnConfigure_clicked() {
    Corruptor_Settings corruptorSettings(this, this->settings);
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
