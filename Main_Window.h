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
    Main_Window(Settings *settings, bool loaded, QWidget *parent);
    ~Main_Window();

private slots:
    void on_btnConfigure_clicked();
    void on_btnGenerate_clicked();
    void on_btnFileLocation_clicked();
    void on_btnSaveLocation_clicked();
    void on_tbFileLocation_textChanged(const QString &arg1);
    void on_tbSaveLocation_textChanged(const QString &arg1);

private:
    void Set_Save_Location_Enabled(bool enabled);
    void Set_Generate_Enabled(bool enabled);
    Ui::Main_Window *ui;
    Settings *settings;
    qint64 fileSize;
    bool loaded;
};

#endif // MAIN_WINDOW_H
