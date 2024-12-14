//
// Created by mwiner on 12/13/24.
//

#include <QApplication>
#include <QSettings>
#include <QMessageBox>
#include <iostream>
#include "organizer.h"
using namespace std;
int main(int argc,char* argv[]){
    QApplication app(argc,argv);
    cout << "Running\n";
    //Read Config File
    QSettings settings("config.ini",QSettings::IniFormat);
    QString importPath = settings.value("Paths/import","./import").toString();
    QString photosPath = settings.value("Paths/photos","./photos").toString();

    //Create organizer obj
    organizer organizer(importPath.toStdString(),photosPath.toStdString());
    organizer.organizePhotos();
    int filesOrganized = organizer.getFilesOrganized();
    cout << filesOrganized;
    return app.exec();
}