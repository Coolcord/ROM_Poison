#include "Main_Window.h"
#include "Settings_Profile_Manager.h"
#include <QFileInfo>
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Settings settings;
    QString defaultSettingsPath = QApplication::applicationDirPath()+"/Profiles/Default.rps";
    QFile file(defaultSettingsPath);
    bool loaded = false;
    if (file.exists()) {
        Settings_Profile_Manager manager(QApplication::applicationDirPath());
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
}
