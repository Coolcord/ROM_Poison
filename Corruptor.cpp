#include "Corruptor.h"
#include <QTime>
#include <QFileInfo>
#include <QMessageBox>
#include <QDebug>
#include <assert.h>

Corruptor::Corruptor(QWidget *parent, Settings *settings, const QString &inFileLocation, const QString &outFileLocation) {
    assert(settings);
    this->parent = parent;
    qsrand(QTime::currentTime().msecsSinceStartOfDay());
    this->settings = settings;
    this->inFileLocation = inFileLocation;
    this->outFileLocation = outFileLocation;
    this->fileSize = 0;
    this->isNESROM = false;
}

Corruptor::~Corruptor() { }

int Corruptor::Run() {
    //Open the input file for reading
    QFile inFile(this->inFileLocation);
    if (!inFile.exists()) return 1; //input file does not exist
    this->fileSize = inFile.size();
    if (this->fileSize > MAX_FILE_SIZE) return 2; //input file is too large
    if (!inFile.open(QFile::ReadOnly)) return 3; //unable to read the input file

    //Open the output file for writing
    QFile outFile(this->outFileLocation);
    if (outFile.exists()) {
        if (!outFile.remove()) {
            return 4; //unable to write the output file
        }
    }
    if (!outFile.open(QFile::ReadWrite)) {
        return 4; //unable to write the output file
    }
    this->isNESROM = this->Use_NES_CPU_Jam_Protection(&inFile);
    if (!inFile.seek(0)) return 3; //unable to read the input file

    //Read the file in sections of 32MB if it is a large file
    if (this->fileSize > MAX_BUFFER_SIZE) {
        int remainingBytes = this->fileSize;
        while (remainingBytes > 0) {
            int bufferSize = 0;
            if (remainingBytes > MAX_BUFFER_SIZE) bufferSize = MAX_BUFFER_SIZE;
            else bufferSize = remainingBytes;
            QByteArray buffer(bufferSize, ' ');
            int startingPosition = inFile.pos();
            if (inFile.read(buffer.data(), bufferSize) != bufferSize) return 3; //unable to read the input file
            int endingPosition = inFile.pos();
            assert(startingPosition <= endingPosition);
            if ((this->settings->startingOffset >= startingPosition && this->settings->startingOffset <= endingPosition)
            || (this->settings->endingOffset >= startingPosition && this->settings->endingOffset <= endingPosition)) {
                int readBytes = this->fileSize-remainingBytes;
                int startingCorruptionPos = this->settings->startingOffset-readBytes;
                if (startingCorruptionPos < 0) startingCorruptionPos = 0;
                int endingCorruptionPos = 0;
                if (this->settings->endingOffset > (readBytes+MAX_BUFFER_SIZE)) endingCorruptionPos = MAX_BUFFER_SIZE;
                else endingCorruptionPos = this->settings->endingOffset-readBytes;
                if (endingCorruptionPos < 0) endingCorruptionPos = 0;
                assert(startingCorruptionPos <= endingCorruptionPos);
                assert(endingCorruptionPos <= this->fileSize);
                assert(this->Corrupt_Buffer(&buffer, startingCorruptionPos, endingCorruptionPos));
            }
            if (outFile.write(buffer, bufferSize) != bufferSize) return 4; //unable to write the output file
            remainingBytes -= bufferSize;
        }
        inFile.close();
    } else { //read the entire file into one buffer
        QByteArray buffer = inFile.readAll();
        inFile.close();
        assert(this->Corrupt_Buffer(&buffer, this->settings->startingOffset, this->settings->endingOffset));
        if (outFile.write(buffer, this->fileSize) != this->fileSize) return 4; //unable to write the output file
    }

    outFile.close();
    this->Handle_Increment();
    return 0;
}

bool Corruptor::Show_Message(int errorCode) {
    QFileInfo inFile(this->inFileLocation);
    QFileInfo outFile(this->outFileLocation);
    if (this->parent != NULL) {
        switch (errorCode) {
        case 0: //success
            QMessageBox::information(this->parent, "ROM Poison",
                                     "Corruption generated successfully!", "OK");
            break;
        case 1: //input file does not exist
            QMessageBox::critical(this->parent, "ROM Poison",
                                  inFile.fileName() + " does not exist!", "OK");
            return true;
        case 2: //input file is too large
            QMessageBox::critical(this->parent, "ROM Poison",
                                  inFile.fileName() + " is larger than the maximum supported filesize of 1GB!", "OK");
            return true;
        case 3: //unable to read the input file
            QMessageBox::critical(this->parent, "ROM Poison",
                                  "ROM Poison does not have proper permissions to read " + inFile.fileName() + "!", "OK");
            return true;
        case 4: //unable to write to the output file
            QMessageBox::critical(this->parent, "ROM Poison",
                                  "ROM Poison does not have proper permissions to write " + outFile.fileName() + "!", "OK");
            return true;
        default:
            return false;
        }
    } else {
        switch (errorCode) {
        case 0: //success
            qDebug() << "Corruption generated successfully!";
            return true;
        case 1: //input file does not exist
            qDebug() << inFile.fileName() + " does not exist!";
            return true;
        case 2: //input file is too large
            qDebug() << inFile.fileName() + " is larger than the maximum supported filesize of 1GB!";
            return true;
        case 3: //unable to read the input file
            qDebug() << "ROM Poison does not have proper permissions to read " + inFile.fileName() + "!";
            return true;
        case 4: //unable to write to the output file
            qDebug() << "ROM Poison does not have proper permissions to write " + outFile.fileName() + "!";
            return true;
        default:
            return false;
        }
    }
    return false;
}

bool Corruptor::Use_NES_CPU_Jam_Protection(QFile *file) {
    assert(file);
    if (this->fileSize > MAX_BUFFER_SIZE) return false; //way too big to be an NES ROM
    if (!file->seek(0)) return false;
    QByteArray buffer(4, ' ');
    if (file->read(buffer.data(), 4) != 4) return false;
    if (buffer.data() == NULL || buffer.size() != 4) return false;
    if (this->Is_NES_ROM(&buffer)) return true;
    if (this->Is_Famicom_ROM(&buffer)) return true;
    return false;
}

bool Corruptor::Is_NES_ROM(QByteArray *buffer) {
    assert(buffer);
    assert(buffer->size() == 4);

    //Make sure the first 4 bytes of the header are valid: "NES"
    if (static_cast<unsigned char>(buffer->at(0)) != 0x4E) return false;
    if (static_cast<unsigned char>(buffer->at(1)) != 0x45) return false;
    if (static_cast<unsigned char>(buffer->at(2)) != 0x53) return false;
    return static_cast<unsigned char>(buffer->at(3)) == 0x1A;
}

bool Corruptor::Is_Famicom_ROM(QByteArray *buffer) {
    assert(buffer);
    assert(buffer->size() == 4);

    //Make sure the first 4 bytes of the header are valid: "FDS"
    if (static_cast<unsigned char>(buffer->at(0)) != 0x46) return false;
    if (static_cast<unsigned char>(buffer->at(1)) != 0x44) return false;
    if (static_cast<unsigned char>(buffer->at(2)) != 0x53) return false;
    return static_cast<unsigned char>(buffer->at(3)) == 0x1A;
}

void Corruptor::Fix_Byte(unsigned char &byte) {
    if (!this->isNESROM) return;

    //These bytes should be avoided
    switch (byte) {
    case 0x00:
    case 0x02:
    case 0x08:
    case 0x12:
    case 0x22:
    case 0x28:
    case 0x32:
    case 0x42:
    case 0x48:
    case 0x52:
    case 0x62:
    case 0x68:
    case 0x72:
    case 0x78:
    case 0x92:
    case 0xB2:
    case 0xD2:
    case 0xF2:
        ++byte;
    default:
        return;
    }
}

bool Corruptor::Is_Byte_Protected(QByteArray *buffer, int pos) {
    assert(buffer);
    if (!this->isNESROM) return false;
    if (pos == 0) {
        return this->Is_Third_Byte_Protected(static_cast<unsigned char>(buffer->data()[pos]));
    } else if (pos == 1) {
        if (!this->Is_Third_Byte_Protected(static_cast<unsigned char>(buffer->data()[pos]))) return false;
        return this->Is_Second_Byte_Protected(static_cast<unsigned char>(buffer->data()[pos-1]));
    } else { //pos >= 2
        if (!this->Is_Third_Byte_Protected(static_cast<unsigned char>(buffer->data()[pos]))) return false;
        if (!this->Is_Second_Byte_Protected(static_cast<unsigned char>(buffer->data()[pos-1]))) return false;
        return this->Is_First_Byte_Protected(static_cast<unsigned char>(buffer->data()[pos-2]));
    }
}

bool Corruptor::Is_First_Byte_Protected(unsigned char byte) {
    switch (byte) {
    case 0x20:
    case 0x4C:
    case 0x6C:
        return true;
    default:
        return false;
    }
}

bool Corruptor::Is_Second_Byte_Protected(unsigned char byte) {
    switch (byte) {
    case 0x10:
    case 0x20:
    case 0x30:
    case 0x4C:
    case 0x50:
    case 0x6C:
    case 0x70:
    case 0x90:
    case 0xB0:
    case 0xD0:
    case 0xF0:
        return true;
    default:
        return false;
    }
}

bool Corruptor::Is_Third_Byte_Protected(unsigned char byte) {
    switch (byte) {
    case 0x00:
    case 0x08:
    case 0x10:
    case 0x20:
    case 0x28:
    case 0x30:
    case 0x40:
    case 0x48:
    case 0x4C:
    case 0x50:
    case 0x60:
    case 0x68:
    case 0x6C:
    case 0x70:
    case 0x78:
    case 0x90:
    case 0xB0:
    case 0xD0:
    case 0xF0:
        return true;
    default:
        return false;
    }
}

bool Corruptor::Corrupt_Buffer(QByteArray *buffer, int startingPos, int endingPos) {
    assert(buffer);
    assert(endingPos <= buffer->size());

    //Perform the Corruption
    for (int i = startingPos; i < endingPos; i += ((qrand()%((this->settings->incrementMaxNum-this->settings->incrementMinNum)+1))+this->settings->incrementMinNum)) {
        if (!Is_Byte_Protected(buffer, i)) {
            unsigned char byte = static_cast<unsigned char>(buffer->data()[i]);
            if (this->settings->random) {
                this->Randomize_Byte(byte);
            } else {
                bool replaced = false;
                if (this->settings->replace) {
                    replaced = this->Replace_Byte(byte);
                }
                if (!replaced) {
                    if (this->settings->add) this->Add_To_Byte(byte);
                    if (this->settings->shiftLeft) this->Shift_Byte(byte);
                }
            }
            this->Fix_Byte(byte);
            buffer->data()[i] = static_cast<char>(byte);
        }
    }
    return true;
}

void Corruptor::Randomize_Byte(unsigned char &byte) {
    byte = (qrand()%0x100);
}

void Corruptor::Add_To_Byte(unsigned char &byte) {
    if (this->settings->addNum < 0) { //decrement
        int decrementAmount = 0-this->settings->addNum;
        if (byte < decrementAmount) {
            while (byte != 0x00) --decrementAmount;
            assert(decrementAmount >= 0);
            byte = 0xFF - decrementAmount;
        } else {
            byte -= decrementAmount;
        }
    } else { //increment
        byte += (this->settings->addNum%0x100);
    }
}

void Corruptor::Shift_Byte(unsigned char &byte) {
    if (this->settings->shiftLeftNum < 0) { //shift right
        int shiftAmount = 0-this->settings->shiftLeftNum;
        byte = byte>>shiftAmount;
    } else { //shift left
        byte = byte<<this->settings->shiftLeftNum;
    }
}

bool Corruptor::Replace_Byte(unsigned char &byte) {
    if (byte == this->settings->replaceOldNum) {
        byte = this->settings->replaceNewNum;
        return true;
    }
    return false;
}

void Corruptor::Handle_Increment() {
    if (this->settings->increment && this->settings->incrementMinNum < this->settings->endingOffset) {
        ++this->settings->incrementMinNum;
        ++this->settings->incrementMaxNum;
        if (this->settings->incrementMinNum > this->settings->endingOffset) {
            this->settings->incrementMinNum = this->settings->endingOffset;
        }
        if (this->settings->incrementMaxNum > this->settings->endingOffset) {
            this->settings->incrementMaxNum = this->settings->endingOffset;
        }
        assert(this->settings->incrementMinNum <= this->settings->incrementMaxNum);
    }
}
