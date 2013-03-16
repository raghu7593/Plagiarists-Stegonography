#include <iostream>
#include <QtGui> 
#include <fstream>
#include <string>
//dirent.h is for getting all file names in a folder
#include <dirent.h>
#include "GUI.h"
#include <cstdlib>
using namespace std;

/*constructor which is for initilization*/
GUI :: GUI()
{
	parent = 0;
	noof_txts = 0;
	count = 0;
	setupUi(this);
	
	//Disabling all line edits...
	
	file_path->setEnabled(false);
	folder_path->setEnabled(false);
	noof_words->setEnabled(false);
	
	//actions for push buttons
	
	connect(pushButton_browse, SIGNAL(clicked()), this, SLOT(getPathfolder()));
	connect(pushButton_browse_2, SIGNAL(clicked()), this, SLOT(getPathfile()));
	connect(radioButton_yes, SIGNAL(clicked()), this, SLOT(yes()));
	connect(radioButton_no, SIGNAL(clicked()), this, SLOT(no()));
	connect(pushButton_about, SIGNAL(clicked()), this, SLOT(about())); 
	connect(pushButton_ok, SIGNAL(clicked()), this, SLOT(ok())); 
	connect(pushButton_Quit, SIGNAL(clicked()), this, SLOT(quit())); 
}


/*
	FUNCTION NAME	:  getPathfolder
	INPUT  			:  NONE
	OUTPUT 			:  NONE
	DESCRIPTION		:  Checks weather radio button either yes or no is selected or not if true set the path of folder in line edit folder_path
							of corresponding folder given by user by browse button else if it is false this fun will do nothing.
*/

void GUI :: getPathfolder()
{
	if((radioButton_yes->isChecked()) or (radioButton_no->isChecked()))
	{
		QString path;
		path = QFileDialog::getExistingDirectory(this, tr("Open Directory"),"/home",QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
		folder_path->setText(path);
	}
}

/*
	FUNCTION NAME	:  getPathfile
	INPUT  			:  NONE
	OUTPUT 			:  NONE
	DESCRIPTION		:  Checks weather radio button is in yes or not if true set the path of referance file in line edit file_path of 
							corresponding file given by user by browse button else if it is false this fun will do nothing .
*/


void GUI :: getPathfile()
{
	if(radioButton_yes->isChecked())
	{
		QString path;
		path = QFileDialog::getOpenFileName(this, tr("Open File"), "",tr("Text Files (*.txt)"));
		file_path->setText(path);
	}
}

/*
	FUNCTION NAME	:  yes
	INPUT		  		:  NONE
	OUTPUT 			:  NONE
	DESCRIPTION		:  Checks weather radio button is in yes or not if true then it enables all line edit's.
*/


void GUI :: yes()
{
	if(radioButton_yes->isChecked())
	{
		file_path->setEnabled(true);
		folder_path->setEnabled(true);
		noof_words->setEnabled(true);
	}
}

/*
	FUNCTION NAME	:  no
	INPUT		  		:  NONE
	OUTPUT 			:  NONE
	DESCRIPTION		:  Checks weather radio button is in no or not if true then it enables corresponding line edit's.
*/


void GUI :: no()
{
	if(radioButton_no->isChecked())
	{
		file_path->setEnabled(false);
		folder_path->setEnabled(true);
		noof_words->setEnabled(true);
	}
}

/*
	FUNCTION NAME	:  about
	INPUT		  		:  NONE
	OUTPUT 			:  NONE
	DESCRIPTION		:  Gives a message about description just like help.
*/

void GUI :: about() 
{
	QMessageBox::about(this, "Help","Tips:\n1.first select either yes or no.\n"
														"2.next push browse button to give a folder path and press ok.\n"
														"3.if(yes) give path of file also.\n"
														"4.give number of words per sequence.\n"
														"5.press ok button and compile main code\n"
														"4.if you want to exit program then press quit button.");
}

/*
	FUNCTION NAME	:  ok(Main function in GUI)
	INPUT		  		:  NONE
	OUTPUT 			:  NONE
	DESCRIPTION		:  1.checks weather user option is yes or no
							2.takes folder path and prints all the paths of .txt files into file(list_of_filenames.txt)
							3.yes	:	takes referance file path also(this file path is in first line of list_of_filenames.txt)
							4.no	:	doesn't take any file path.
							5.choice will be printed in choice.txt
							6.number of words per sequence will be printed in no_of_words.txt
							7.there are corresponding error messages if there is an error
*/

void GUI :: ok() 
{
    ofstream out1;
    out1.open("list_of_filenames.txt",ios::out);
    out1<<"";
    out1.close();
	if((radioButton_yes->isChecked()) or (radioButton_no->isChecked()))
	{
		QString path1,path2;
		string line,substring,file_name;
		path1 = folder_path->displayText ();
		path2 = file_path->displayText ();
		ofstream output,a,choice;
		ifstream input;
		output.open("list_of_filenames.txt",ios::out | ios::app);
		a.open("no_of_words.txt",ios::out | ios::app);
		choice.open("choice.txt",ios::out);
		if(radioButton_no->isChecked())
			choice<<"no"<<endl;
		if(radioButton_yes->isChecked())
		{
			choice<<"yes"<<endl;
			input.open(path2.toStdString().c_str());
			if(input.is_open())
				output<<path2.toStdString()<<endl;
			else
				QMessageBox::about(this, "Error message","Input referance file cannot be opened");
		}
		
		std::string Str = noof_words->displayText().toStdString().c_str();
		int wps = atoi(Str.c_str());
		if(wps <= 0)
			QMessageBox::about(this, "Error message","Enter a valid integer in number of words");
		else
		{
			a<<wps<<endl;
			DIR *dir;
			int k = 0;
			string dir_name = path1.toStdString();
			struct dirent *ent;
   	  	dir = opendir (dir_name.c_str());
			if (dir != NULL) 
			{
   			while ((ent = readdir (dir)) != NULL) 
  				{
  					file_name = ent->d_name;
  					if((file_name != ".") and (file_name != ".."))
  					{
  					  	 k = file_name.length();
  		  			    if(k>=4) 
  		  				 {
  						 	substring = file_name.substr(k-4);
  						 	if(substring==".txt")
  		  					output<<dir_name+"/"+file_name<<endl;
  		  				 }
  		 			}
  				}
  				closedir (dir);
  				quit();
			}
			else 
				QMessageBox::about(this, "Error message","sorry the given directory has an error in opening");
			noof_words->setEnabled(false);
		}
		a.close();
		choice.close();
	}
}

/*
	FUNCTION NAME	:  quit
	INPUT		  		:  NONE
	OUTPUT 			:  NONE
	DESCRIPTION		:  Just exits program of GUI.
*/

void GUI :: quit()
{
	exit(0);
}
