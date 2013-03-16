#include <QApplication>
#include <iostream>
#include <fstream>
#include "GUI.h"
using namespace std;

//	just opens a window

int main(int argc, char *argv[])
{
    ofstream out1,out2,out3;
    out1.open("list_of_filenames.txt",ios::out);
    out1<<"";
    out1.close();

    out2.open("no_of_words.txt",ios::out);
    out2<<"";
    out2.close();
    
    out3.open("choice.txt",ios::out);
    out3<<"";
    out3.close();
    
    QApplication app(argc, argv);
    GUI *dialog = new GUI;
    dialog->show();
    return app.exec();
}
