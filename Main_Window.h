#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QDialog>
#include "Settings.h"

class Corruptor_Settings;

namespace Ui {
class Main_Window;
}

class Main_Window : public QDialog
{
    Q_OBJECT

public:
    explicit Main_Window(QWidget *parent = 0);
    ~Main_Window();

private slots:
    void on_btnConfigure_clicked();
    void on_btnGenerate_clicked();
    void on_btnFileLocation_clicked();
    void on_btnSaveLocation_clicked();

private:
    Ui::Main_Window *ui;
    Settings *settings;
};

#endif // MAIN_WINDOW_H
