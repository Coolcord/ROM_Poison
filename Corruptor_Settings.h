#ifndef CORRUPTOR_SETTINGS_H
#define CORRUPTOR_SETTINGS_H

#include <QDialog>

namespace Ui {
class Corruptor_Settings;
}

class Corruptor_Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Corruptor_Settings(QWidget *parent = 0);
    ~Corruptor_Settings();

private:
    Ui::Corruptor_Settings *ui;
};

#endif // CORRUPTOR_SETTINGS_H
