#include "Main_Window.h"
#include "Settings_Profile_Manager.h"
#include "Corruptor.h"
#include <QFileInfo>
#include <QFile>
#include <QApplication>
#include <iostream>
#include <assert.h>

int main(int argc, char *argv[]) {
    if (argc == 1) { //GUI mode
        QApplication a(argc, argv);

        Settings settings;
        QString defaultSettingsPath = QApplication::applicationDirPath()+"/Profiles/Default.rps";
        QFile file(defaultSettingsPath);
        bool loaded = false;
        if (file.exists()) {
            Settings_Profile_Manager manager(NULL, QApplication::applicationDirPath());
            int ret = manager.Read_Settings(&settings, defaultSettingsPath);
            if (ret == 0) {
                loaded = true;
            } else {
                file.remove(); //delete the default settings file if it is invalid
            }
        }
        Main_Window w(&settings, loaded, NULL);
        w.show();

        return a.exec();
    } else if (argc == 4) { //CLI mode
        QApplication a(argc, argv);

        Settings settings;
        Settings_Profile_Manager manager(NULL, QApplication::applicationDirPath());

        //Try to load from the main profiles path first
        QString settingsPath = QApplication::applicationDirPath()+"/Profiles/"+argv[3];
        int ret = manager.Read_Settings(&settings, settingsPath);
        if (ret == 2) {
            settingsPath = QString(argv[3]);
            ret = manager.Read_Settings(&settings, settingsPath);
        }
        if (ret != 0) {
            std::cerr << "Unable to load settings profile " << argv[3] << "!" << std::endl;
            return 5;
        }

        Corruptor corruptor(NULL, &settings, argv[1], argv[2]);
        ret = corruptor.Run();
        corruptor.Show_Message(ret);
        if (settings.increment) {
            if (manager.Save_Settings(&settings, settingsPath) != 0) {
                std::cerr << "Unable to save settings!" << std::endl;
                return 6;
            }
        }
        return ret;
    }

    //Improper number of command line arguments
    std::cout << "ROM_Poison <original file> <save location> <ROM Poison Settings File>" << std::endl;
    return 7;
}
