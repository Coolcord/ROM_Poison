#include "Corruptor_Settings.h"
#include "ui_Corruptor_Settings.h"
#include "Settings_Profile_Manager.h"
#include <QMessageBox>
#include <assert.h>

Corruptor_Settings::Corruptor_Settings(QWidget *parent, Settings *settings, int fileSize) :
    QDialog(parent, Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint),
    ui(new Ui::Corruptor_Settings) {
    assert(parent);
    assert(settings);
    this->settings = settings;
    this->fileSize = fileSize;
    ui->setupUi(this);
    this->Load_Settings(this->fileSize);
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

void Corruptor_Settings::on_buttonBox_accepted() {
    this->settings->startingOffset = this->ui->sbStartingOffset->value();
    this->settings->endingOffset = this->ui->sbEndingOffset->value();
    this->settings->incrementMinNum = this->ui->sbMinBytes->value();
    this->settings->incrementMaxNum = this->ui->sbMaxBytes->value();
    this->settings->random = this->ui->cbRandomByteCorruption->isChecked();
    this->settings->add = this->ui->cbAdd->isChecked();
    this->settings->shiftLeft = this->ui->cbShiftLeft->isChecked();
    this->settings->replace = this->ui->cbReplace->isChecked();
    this->settings->addNum = this->ui->sbAdd->value();
    this->settings->shiftLeftNum = this->ui->sbShiftLeft->value();
    this->settings->replaceOldNum = this->ui->sbOldByte->value();
    this->settings->replaceNewNum = this->ui->sbNewByte->value();
    this->close();
}

void Corruptor_Settings::on_buttonBox_rejected() {
    this->close();
}

void Corruptor_Settings::on_btnSaveSettings_clicked() {
    Settings_Profile_Manager manager(this, QApplication::applicationDirPath());

    //Pull the current settings for saving
    Settings currentSettings;
    currentSettings.startingOffset = this->ui->sbStartingOffset->value();
    currentSettings.endingOffset = this->ui->sbEndingOffset->value();
    currentSettings.incrementMinNum = this->ui->sbMinBytes->value();
    currentSettings.incrementMaxNum = this->ui->sbMaxBytes->value();
    currentSettings.increment = this->ui->cbIncrement->isChecked();
    currentSettings.random = this->ui->cbRandomByteCorruption->isChecked();
    currentSettings.add = this->ui->cbAdd->isChecked();
    currentSettings.shiftLeft = this->ui->cbShiftLeft->isChecked();
    currentSettings.replace = this->ui->cbReplace->isChecked();
    currentSettings.addNum = this->ui->sbAdd->value();
    currentSettings.shiftLeftNum = this->ui->sbShiftLeft->value();
    currentSettings.replaceOldNum = this->ui->sbOldByte->value();
    currentSettings.replaceNewNum = this->ui->sbNewByte->value();

    //Perform the save
    switch (manager.Save_Settings(&currentSettings)) {
    case 0: //success
        QMessageBox::information(this, "ROM Poison",
                                 "Settings saved successfully!", "OK");
        break;
    case 1: //user canceled the save
        break;
    case 2: //standard error
        QMessageBox::critical(this, "ROM Poison",
                              "Unable to save settings!", "OK");
        break;
    case 3: //no profile folder
        QMessageBox::critical(this, "ROM Poison",
                              "ROM Poison was unable to create the Profiles folder!", "OK");
        break;
    default:
        assert(false);
        break;
    }
}

void Corruptor_Settings::on_btnLoadSettings_clicked() {
    Settings_Profile_Manager manager(this, QApplication::applicationDirPath());

    switch (manager.Load_Settings(this->settings)) {
    case 0: //success
        this->Load_Settings(this->fileSize);
        QMessageBox::information(this, "ROM Poison",
                                 "Settings loaded successfully!", "OK");
        break;
    case 1: //user canceled the load
        break;
    case 2: //standard error
        QMessageBox::critical(this, "ROM Poison",
                              "Unable to load settings!", "OK");
        break;
    case 3: //no profile folder
        QMessageBox::critical(this, "ROM Poison",
                              "ROM Poison was unable to create the Profiles folder!", "OK");
        break;
    case 4: //invalid ROM Poison Settings file
        QMessageBox::critical(this, "ROM Poison",
                              "This is not a valid ROM Poison settings file!", "OK");
        break;
    default:
        assert(false);
        break;
    }
}

void Corruptor_Settings::Set_Random_Corruption_Mode(bool random) {
    this->Set_Add_Mode(random);
    this->Set_Shift_Left_Mode(random);
    this->Set_Replace_Mode(random);
    this->ui->cbAdd->setEnabled(!random);
    this->ui->cbShiftLeft->setEnabled(!random);
    this->ui->cbReplace->setEnabled(!random);

    if (random) {
        this->ui->cbAdd->setChecked(false);
        this->ui->cbShiftLeft->setChecked(false);
        this->ui->cbReplace->setChecked(false);
    }
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
    this->ui->sbAdd->setValue(0);
}

void Corruptor_Settings::Set_Shift_Left_Mode(bool shift) {
    this->ui->sbShiftLeft->setEnabled(shift);
    this->ui->sbShiftLeft->setValue(0);
}

void Corruptor_Settings::Set_Replace_Mode(bool replace) {
    this->ui->sbOldByte->setEnabled(replace);
    this->ui->sbNewByte->setEnabled(replace);
    this->ui->lblWith->setEnabled(replace);
    this->ui->sbOldByte->setValue(0);
    this->ui->sbNewByte->setValue(0);
}

void Corruptor_Settings::Load_Settings(int fileSize) {
    this->ui->sbStartingOffset->setMaximum(fileSize);
    this->ui->sbEndingOffset->setMaximum(fileSize);
    this->ui->sbMinBytes->setMaximum(fileSize);
    this->ui->sbMaxBytes->setMaximum(fileSize);
    this->ui->sbStartingOffset->setValue(this->settings->startingOffset);
    this->ui->sbEndingOffset->setValue(this->settings->endingOffset);
    this->ui->sbMinBytes->setValue(this->settings->incrementMinNum);
    this->ui->sbMaxBytes->setValue(this->settings->incrementMaxNum);
    this->ui->cbIncrement->setChecked(this->settings->increment);
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
    if (this->settings->add) this->ui->sbAdd->setValue(this->settings->addNum);
    if (this->settings->shiftLeft) this->ui->sbShiftLeft->setValue(this->settings->shiftLeftNum);
    if (this->settings->replace) {
        this->ui->sbOldByte->setValue(this->settings->replaceOldNum);
        this->ui->sbNewByte->setValue(this->settings->replaceNewNum);
    }
}

void Corruptor_Settings::on_sbStartingOffset_valueChanged(int arg1) {
    if (this->ui->sbEndingOffset->value() < arg1) this->ui->sbEndingOffset->setValue(arg1);
}

void Corruptor_Settings::on_sbEndingOffset_valueChanged(int arg1) {
    if (this->ui->sbStartingOffset->value() > arg1) this->ui->sbStartingOffset->setValue(arg1);
}

void Corruptor_Settings::on_sbMinBytes_valueChanged(int arg1) {
    if (this->ui->sbMaxBytes->value() < arg1) this->ui->sbMaxBytes->setValue(arg1);
}

void Corruptor_Settings::on_sbMaxBytes_valueChanged(int arg1) {
    if (this->ui->sbMinBytes->value() > arg1) this->ui->sbMinBytes->setValue(arg1);
}

void Corruptor_Settings::on_btnEndOfFile_clicked() {
    this->ui->sbEndingOffset->setValue(this->fileSize);
    assert(this->ui->sbStartingOffset->value() <= this->fileSize);
}
