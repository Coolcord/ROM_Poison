#include "Corruptor_Settings.h"
#include "ui_Corruptor_Settings.h"
#include <assert.h>

Corruptor_Settings::Corruptor_Settings(QWidget *parent, Settings *settings) :
    QDialog(parent),
    ui(new Ui::Corruptor_Settings) {
    assert(settings);
    this->settings = settings;
    ui->setupUi(this);
    this->Load_Settings();
}

Corruptor_Settings::~Corruptor_Settings() {
    delete ui;
}

void Corruptor_Settings::on_cbRandomByteCorruption_toggled(bool checked) {
    this->Set_Random_Corruption_Mode(checked);
}

void Corruptor_Settings::on_cbAdd_toggled(bool checked) {
    this->Set_Add_Mode(checked);
}

void Corruptor_Settings::on_cbShiftLeft_toggled(bool checked) {
    this->Set_Shift_Left_Mode(checked);
}

void Corruptor_Settings::on_cbReplace_toggled(bool checked) {
    this->Set_Replace_Mode(checked);
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

void Corruptor_Settings::Set_Random_Corruption_Mode(bool random) {
    this->Set_Add_Mode(random);
    this->Set_Shift_Left_Mode(random);
    this->Set_Replace_Mode(random);
    this->ui->cbAdd->setEnabled(!random);
    this->ui->cbShiftLeft->setEnabled(!random);
    this->ui->cbReplace->setEnabled(!random);

    this->ui->cbAdd->setChecked(random);
    this->ui->cbShiftLeft->setChecked(random);
    this->ui->cbReplace->setChecked(random);
    this->Set_Add_Mode(!random);
    this->Set_Shift_Left_Mode(!random);
    this->Set_Replace_Mode(!random);
    if (!random) {
        this->Set_Add_Mode(false);
        this->Set_Shift_Left_Mode(false);
        this->Set_Replace_Mode(false);
    }
}

void Corruptor_Settings::Set_Add_Mode(bool add) {
    this->ui->sbAdd->setEnabled(add);
    if (add) this->ui->sbAdd->setValue(0);
}

void Corruptor_Settings::Set_Shift_Left_Mode(bool shift) {
    this->ui->sbShiftLeft->setEnabled(shift);
    if (shift) this->ui->sbShiftLeft->setValue(0);
}

void Corruptor_Settings::Set_Replace_Mode(bool replace) {
    this->ui->sbOldByte->setEnabled(replace);
    this->ui->sbNewByte->setEnabled(replace);
    this->ui->lblWith->setEnabled(replace);
    if (replace) {
        this->ui->sbOldByte->setValue(0);
        this->ui->sbNewByte->setValue(0);
    }
}

void Corruptor_Settings::Load_Settings() {
    this->ui->sbStartingOffset->setValue(this->settings->startingOffset);
    this->ui->sbEndingOffset->setValue(this->settings->endingOffset);
    this->ui->sbMinBytes->setValue(this->settings->incrementMinNum);
    this->ui->sbMaxBytes->setValue(this->settings->incrementMaxNum);
    this->ui->cbRandomByteCorruption->setChecked(this->settings->random);
    if (this->settings->random) {
        this->Set_Random_Corruption_Mode(true);
    } else {
        this->ui->cbAdd->setChecked(this->settings->add);
        this->ui->cbShiftLeft->setChecked(this->settings->shiftLeft);
        this->ui->cbReplace->setChecked(this->settings->replace);
    }

    //Set each UI setting accordingly
    this->Set_Add_Mode(this->settings->add);
    this->Set_Shift_Left_Mode(this->settings->shiftLeft);
    this->Set_Replace_Mode(this->settings->replace);
}
