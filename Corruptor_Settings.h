#ifndef CORRUPTOR_SETTINGS_H
#define CORRUPTOR_SETTINGS_H

#include <QDialog>
#include <QAbstractButton>
#include "Settings.h"

namespace Ui {
class Corruptor_Settings;
}

class Corruptor_Settings : public QDialog
{
    Q_OBJECT

public:
    Corruptor_Settings(QWidget *parent, Settings *settings, int fileSize);
    ~Corruptor_Settings();

private slots:
    void on_cbRandomByteCorruption_toggled(bool checked);
    void on_cbAdd_toggled(bool checked);
    void on_cbShiftLeft_toggled(bool checked);
    void on_cbReplace_toggled(bool checked);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_btnSaveSettings_clicked();
    void on_btnLoadSettings_clicked();
    void on_sbStartingOffset_valueChanged(int arg1);
    void on_sbEndingOffset_valueChanged(int arg1);
    void on_sbMinBytes_valueChanged(int arg1);
    void on_sbMaxBytes_valueChanged(int arg1);

    void on_btnEndOfFile_clicked();

private:
    void Set_Random_Corruption_Mode(bool random);
    void Set_Add_Mode(bool add);
    void Set_Shift_Left_Mode(bool shift);
    void Set_Replace_Mode(bool replace);
    void Load_Settings(int fileSize);
    Ui::Corruptor_Settings *ui;
    Settings *settings;
    int fileSize;
};

#endif // CORRUPTOR_SETTINGS_H
