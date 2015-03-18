#ifndef SETTINGS_PROFILE_MANAGER_H
#define SETTINGS_PROFILE_MANAGER_H

#include <QWidget>
#include <QString>
#include "Settings.h"

const static QString HEADER = "ROM Poison Corruptor Settings";

class Settings_Profile_Manager
{
public:
    Settings_Profile_Manager(const QString &applicationPath);
    ~Settings_Profile_Manager();
    void Set_Parent(QWidget *parent);
    int Save_Settings(Settings *settings);
    int Load_Settings(Settings *settings);
    int Read_Settings(Settings *settings, const QString &fileLocation);

private:
    QWidget *parent;
    QString applicationPath;
};

#endif // SETTINGS_PROFILE_MANAGER_H
