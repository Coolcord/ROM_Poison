#include "Settings_Profile_Manager.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDir>
#include <QFile>
#include <assert.h>

Settings_Profile_Manager::Settings_Profile_Manager(QWidget *parent, const QString &applicationPath) {
    assert(parent);
    this->parent = parent;
    this->applicationPath = applicationPath;
}

Settings_Profile_Manager::~Settings_Profile_Manager() { }

int Settings_Profile_Manager::Save_Settings(Settings *settings) {
    assert(settings);
    QDir dir(this->applicationPath);
    if (!dir.exists()) return false;
    if (!dir.cd("Profiles")) {
        if (!dir.mkdir("Profiles")) return 3;
    }
    QString profileLocation = this->applicationPath + "/Profiles";
    QString saveLocation = QFileDialog::getSaveFileName(this->parent, "Save Location", profileLocation, "ROM Poison Settings File (*.rps)");
    if (saveLocation == NULL || saveLocation.isEmpty()) return 1; //the user canceled the save
    if (!saveLocation.endsWith(".rps")) saveLocation += ".rps";

    //Write the file to the buffer
    QFile file(saveLocation);
    if (!file.open(QFile::ReadWrite | QFile::Truncate)) return false;
    QTextStream stream(&file);
    if (stream.status() != QTextStream::Ok) {
        stream.flush();
        file.close();
        file.remove();
        return 2;
    }
    stream << HEADER << "\n"; //use Unix end lines for cross platform compatability
    stream << settings->startingOffset << "\n";
    stream << settings->endingOffset << "\n";
    stream << settings->incrementMinNum << "\n";
    stream << settings->incrementMaxNum << "\n";
    stream << settings->random << "\n";
    stream << settings->add << "\n";
    stream << settings->shiftLeft << "\n";
    stream << settings->replace << "\n";
    stream << settings->addNum << "\n";
    stream << settings->shiftLeftNum << "\n";
    stream << settings->replaceOldNum << "\n";
    stream << settings->replaceNewNum << "\n";
    stream.flush(); //flush the buffer to the disk
    file.close();
    if (stream.status() != QTextStream::Ok) {
        file.remove();
        return 2;
    }
    return 0;
}

int Settings_Profile_Manager::Load_Settings(Settings *settings) {
    assert(settings);

}

