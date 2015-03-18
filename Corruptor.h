#ifndef CORRUPTOR_H
#define CORRUPTOR_H

#include "Settings.h"
#include <QString>
#include <QFile>
#include <QByteArray>
#include <QWidget>

const static int MAX_BUFFER_SIZE = 33554432; //32MB

class Corruptor
{
public:
    Corruptor(QWidget *parent, Settings *settings, const QString &inFileLocation, const QString &outFileLocation);
    ~Corruptor();
    int Run();
    bool Show_Message(int errorCode);

private:
    bool Use_NES_CPU_Jam_Protection(QFile *file);
    bool Is_NES_ROM(QByteArray *buffer);
    bool Is_Famicom_ROM(QByteArray *buffer);
    void Fix_Byte(unsigned char &byte);
    bool Is_Byte_Protected(QByteArray *buffer, int pos);
    bool Is_First_Byte_Protected(unsigned char byte);
    bool Is_Second_Byte_Protected(unsigned char byte);
    bool Is_Third_Byte_Protected(unsigned char byte);
    bool Corrupt_Buffer(QByteArray *buffer, int startingPos, int endingPos);
    void Randomize_Byte(unsigned char &byte);
    void Add_To_Byte(unsigned char &byte);
    void Shift_Byte(unsigned char &byte);
    bool Replace_Byte(unsigned char &byte);

    QWidget *parent;
    Settings *settings;
    QString inFileLocation;
    QString outFileLocation;
    bool isNESROM;
    int fileSize;
};

#endif // CORRUPTOR_H
