#include "Settings_Profile_Manager.h"
#include <QFileDialog>
#include <QTextStream>
#include <QDir>
#include <QFile>
#include <assert.h>

Settings_Profile_Manager::Settings_Profile_Manager(QWidget *parent, const QString &applicationPath) {
    this->parent = parent;
    this->applicationPath = applicationPath;
}

Settings_Profile_Manager::~Settings_Profile_Manager() { }

int Settings_Profile_Manager::Save_Settings(Settings *settings, const QString &saveLocation) {
    assert(settings);
    QDir dir(this->applicationPath);
    if (!dir.exists()) return false;
    if (!dir.cd("Profiles")) {
        if (!dir.mkdir("Profiles")) return 3;
    }

    //Write the file to the buffer
    QFile file(saveLocation);
    if (!file.open(QFile::ReadWrite | QFile::Truncate)) return 2;
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
    stream << settings->increment << "\n";
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

int Settings_Profile_Manager::Save_Settings(Settings *settings) {
    assert(this->parent);
    QString profileLocation = this->applicationPath + "/Profiles";
    QString saveLocation = QFileDialog::getSaveFileName(this->parent, "Save Location", profileLocation, "ROM Poison Settings File (*.rps)");
    if (saveLocation == NULL || saveLocation.isEmpty()) return 1; //the user canceled the save
    if (!saveLocation.endsWith(".rps")) saveLocation += ".rps";
    return this->Save_Settings(settings, saveLocation);
}

int Settings_Profile_Manager::Load_Settings(Settings *settings) {
    assert(this->parent);
    assert(settings);
    QDir dir(this->applicationPath);
    if (!dir.exists()) return false;
    if (!dir.cd("Profiles")) {
        if (!dir.mkdir("Profiles")) return 3;
    }
    QString profileLocation = this->applicationPath + "/Profiles";
    QString loadLocation = QFileDialog::getOpenFileName(this->parent, "Open a ROM Poison Settings File", profileLocation, "ROM Poison Settings File (*.rps)");
    if (loadLocation == NULL || loadLocation.isEmpty()) return 1; //the user canceled the load
    return this->Read_Settings(settings, loadLocation);
}

int Settings_Profile_Manager::Read_Settings(Settings *settings, const QString &fileLocation) {
    assert(settings);
    assert(fileLocation != NULL && !fileLocation.isEmpty());
    QFile file(fileLocation);
    if (!file.exists() || !file.open(QFile::ReadWrite)) return 2;
    QTextStream stream(&file);
    if (stream.status() != QTextStream::Ok) {
        file.close();
        return 2;
    }

    //Check the header
    QString line = file.readLine().trimmed();
    if (line != HEADER) {
        file.close();
        return 4;
    }

    //Create a new settings struct just in case this data ends up being invalid
    Settings newSettings;
    stream >> newSettings.startingOffset;
    if (stream.status() != QTextStream::Ok) {
        file.close();
        return 4;
    }
    stream >> newSettings.endingOffset;
    if (stream.status() != QTextStream::Ok) {
        file.close();
        return 4;
    }
    stream >> newSettings.incrementMinNum;
    if (stream.status() != QTextStream::Ok) {
        file.close();
        return 4;
    }
    stream >> newSettings.incrementMaxNum;
    if (stream.status() != QTextStream::Ok) {
        file.close();
        return 4;
    }
    int value = 0;
    stream >> value;
    if (stream.status() != QTextStream::Ok) {
        file.close();
        return 4;
    }
    newSettings.increment = static_cast<bool>(value);
    stream >> value;
    if (stream.status() != QTextStream::Ok) {
        file.close();
        return 4;
    }
    newSettings.random = static_cast<bool>(value);
    stream >> value;
    if (stream.status() != QTextStream::Ok) {
        file.close();
        return 4;
    }
    newSettings.add = static_cast<bool>(value);
    stream >> value;
    if (stream.status() != QTextStream::Ok) {
        file.close();
        return 4;
    }
    newSettings.shiftLeft = static_cast<bool>(value);
    stream >> value;
    if (stream.status() != QTextStream::Ok) {
        file.close();
        return 4;
    }
    newSettings.replace = static_cast<bool>(value);
    stream >> newSettings.addNum;
    if (stream.status() != QTextStream::Ok) {
        file.close();
        return 4;
    }
    stream >> newSettings.shiftLeftNum;
    if (stream.status() != QTextStream::Ok) {
        file.close();
        return 4;
    }
    stream >> newSettings.replaceOldNum;
    if (stream.status() != QTextStream::Ok) {
        file.close();
        return 4;
    }
    stream >> newSettings.replaceNewNum;
    if (stream.status() != QTextStream::Ok) {
        file.close();
        return 4;
    }
    stream >> line; //ignore the last newline
    if (!stream.atEnd()) {
        file.close();
        return 4;
    }

    //Copy the data over to the settings now that it is confirmed to be valid
    settings->startingOffset = newSettings.startingOffset;
    settings->endingOffset = newSettings.endingOffset;
    settings->incrementMinNum = newSettings.incrementMinNum;
    settings->incrementMaxNum = newSettings.incrementMaxNum;
    settings->increment = newSettings.increment;
    settings->random = newSettings.random;
    settings->add = newSettings.add;
    settings->shiftLeft = newSettings.shiftLeft;
    settings->replace = newSettings.replace;
    settings->addNum = newSettings.addNum;
    settings->shiftLeftNum = newSettings.shiftLeftNum;
    settings->replaceOldNum = newSettings.replaceOldNum;
    settings->replaceNewNum = newSettings.replaceNewNum;
    file.close();
    return 0;
}

