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
    explicit Corruptor_Settings(QWidget *parent = NULL, Settings *settings = NULL);
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

private:
    Ui::Corruptor_Settings *ui;
    Settings *settings;
};

#endif // CORRUPTOR_SETTINGS_H
