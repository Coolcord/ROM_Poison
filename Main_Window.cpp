#include "Main_Window.h"
#include "ui_Main_Window.h"
#include "Corruptor_Settings.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <assert.h>

Main_Window::Main_Window(Settings *settings, bool loaded, QWidget *parent) :
    QDialog(parent, Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint | Qt::WindowCloseButtonHint),
    ui(new Ui::Main_Window) {
    assert(settings);
    this->settings = settings;
    if (!loaded) {
        this->settings->startingOffset = 0;
        this->settings->endingOffset = MAX_FILE_SIZE;
        this->settings->incrementMinNum = 1;
        this->settings->incrementMaxNum = 0x1000;
        this->settings->random = true;
        this->settings->add = false;
        this->settings->shiftLeft = false;
        this->settings->replace = false;
        this->settings->addNum = 0;
        this->settings->shiftLeftNum = 0;
        this->settings->replace = 0;
    }
    this->fileSize = 0;
    ui->setupUi(this);
    this->Set_Save_Location_Enabled(false);
}

Main_Window::~Main_Window() {
    delete ui;
}

void Main_Window::on_btnConfigure_clicked() {
    qDebug() << this->fileSize;
    Corruptor_Settings corruptorSettings(this, this->settings, this->fileSize);
    corruptorSettings.exec();
}

void Main_Window::on_btnGenerate_clicked() {
    //TODO: Implement this...
}

void Main_Window::on_btnFileLocation_clicked() {
    QString fileLocation = QFileDialog::getOpenFileName(this, "Open a ROM or a File", QApplication::applicationDirPath(), "All files (*.*)");
    if (fileLocation == NULL || fileLocation.isEmpty()) return;
    QFileInfo file(fileLocation);
    if (!file.exists()) {
        QMessageBox::critical(this, "ROM Poison",
                              fileLocation + " could not be found!", "OK");
        return;
    }
    if (!file.isReadable()) {
        QMessageBox::critical(this,"ROM Poison",
                              "ROM Poison does not have proper read permissions to access " +
                              file.fileName() + ". Cannot continue!", "OK");
        return;
    }
    this->ui->tbFileLocation->setText(fileLocation);
}

void Main_Window::on_btnSaveLocation_clicked() {
    QFileInfo originalFile(this->ui->tbFileLocation->text());
    QString extension = originalFile.fileName().split('.').last().toLower();
    QString filter = "All files (*.*)";
    if (extension != NULL && !extension.isEmpty()) filter = "*." + extension + ";;" + filter;
    QString saveLocation = QFileDialog::getSaveFileName(this, "Save Location", QApplication::applicationDirPath(), filter);
    if (saveLocation == NULL || saveLocation.isEmpty()) return;
    QFileInfo file(saveLocation);
    QDir dir = file.dir();
    if (file.isDir()) {
        QMessageBox::critical(this,"ROM Poison",
                              file.fileName() + " is a directory!", "OK");
        return;
    }
    if (!dir.exists()) {
        QMessageBox::critical(this,"ROM Poison",
                              "ROM Poison does not have proper read/write permissions to access " +
                              file.fileName() + ". Cannot continue!", "OK");
        return;
    }
    if (originalFile.absolutePath() == file.absolutePath() && originalFile.fileName() == file.fileName()) {
        QMessageBox::critical(this,"ROM Poison",
                              "Don't overwrite the original file! Save the file under a different name.", "OK");
        return;
    }
    this->ui->tbSaveLocation->setText(saveLocation);
}

void Main_Window::on_tbFileLocation_textChanged(const QString &arg1) {
    QFileInfo file(arg1);
    this->Set_Save_Location_Enabled(file.exists() && file.isFile());
}

void Main_Window::on_tbSaveLocation_textChanged(const QString &arg1) {
    QFileInfo file(arg1);
    QDir dir = file.dir();
    bool valid = (dir.exists() && !file.isDir() && this->ui->tbFileLocation->text() != arg1);
    this->Set_Generate_Enabled(valid);

    //Update the corruptor settings
    if (valid) {
        QFileInfo originalFile(this->ui->tbFileLocation->text());
        if (!originalFile.exists()) {
            QMessageBox::critical(this,"ROM Poison",
                                  file.fileName() + " does not exist!", "OK");
            this->Set_Save_Location_Enabled(false);
            this->ui->tbFileLocation->setText("");
            return;
        }
        if (originalFile.size() > MAX_FILE_SIZE) this->settings->endingOffset = MAX_FILE_SIZE;
        else this->settings->endingOffset = originalFile.size(); //TODO: Handle the case where settings have been loaded
        this->fileSize = this->settings->endingOffset;
        if (this->settings->incrementMaxNum > this->settings->endingOffset) this->settings->incrementMaxNum = this->settings->endingOffset;
        if (this->settings->incrementMinNum > this->settings->incrementMaxNum) this->settings->incrementMinNum = this->settings->incrementMaxNum;
    }
}

void Main_Window::Set_Save_Location_Enabled(bool enabled) {
    this->ui->lblSaveLocation->setEnabled(enabled);
    this->ui->tbSaveLocation->setEnabled(enabled);
    this->ui->btnSaveLocation->setEnabled(enabled);
    this->ui->tbSaveLocation->setText("");
    if (!enabled) this->fileSize = 0;
    this->Set_Generate_Enabled(false);
}

void Main_Window::Set_Generate_Enabled(bool enabled) {
    this->ui->btnConfigure->setEnabled(enabled);
    this->ui->btnGenerate->setEnabled(enabled);
}
