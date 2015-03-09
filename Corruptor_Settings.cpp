#include "Corruptor_Settings.h"
#include "ui_Corruptor_Settings.h"

Corruptor_Settings::Corruptor_Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Corruptor_Settings)
{
    ui->setupUi(this);
}

Corruptor_Settings::~Corruptor_Settings()
{
    delete ui;
}
