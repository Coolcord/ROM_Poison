#ifndef SETTINGS_PROFILE_MANAGER_H
#define SETTINGS_PROFILE_MANAGER_H

#include <QWidget>
#include <QString>
#include "Settings.h"

const static QString HEADER = "ROM Poison Corruptor Settings";

class Settings_Profile_Manager
{
public:
    Settings_Profile_Manager(QWidget *parent, const QString &applicationPath);
    ~Settings_Profile_Manager();
    int Save_Settings(Settings *settings);
    int Save_Settings(Settings *settings, const QString &saveLocation);
    int Load_Settings(Settings *settings);
    int Read_Settings(Settings *settings, const QString &fileLocation);

private:
    QWidget *parent;
    QString applicationPath;
};

#endif // SETTINGS_PROFILE_MANAGER_H
