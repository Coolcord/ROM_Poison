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

void Corruptor_Settings::on_cbRandomByteCorruption_toggled(bool checked)
{
    //TODO: Implement this...
}

void Corruptor_Settings::on_cbAdd_toggled(bool checked)
{
    //TODO: Implement this...
}

void Corruptor_Settings::on_cbShiftLeft_toggled(bool checked)
{
    //TODO: Implement this...
}

void Corruptor_Settings::on_cbReplace_toggled(bool checked)
{
    //TODO: Implement this...
}

void Corruptor_Settings::on_buttonBox_accepted()
{
    //TODO: Implement this...
}

void Corruptor_Settings::on_buttonBox_rejected()
{
    //TODO: Implement this...
}

void Corruptor_Settings::on_btnSaveSettings_clicked()
{
    //TODO: Implement this...
}

void Corruptor_Settings::on_btnLoadSettings_clicked()
{
    //TODO: Implement this...
}
