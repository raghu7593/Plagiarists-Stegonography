#include <cstdlib>
#include <string>
#include "img_img.cpp"
#include "txt_img.cpp"
#include "cv.h"
#include "highgui.h"
using namespace cv;
using namespace std;

int main()
{	
	int action;
	cout<<"Enter one option as given below"<<endl;
	cout<<"1 for hiding image in image"<<endl;
	cout<<"2 for retriving image from image(make sure you have an encrypted image)"<<endl;
	cout<<"3 for hiding text in image"<<endl;
	cout<<"4 for retriving text from image(make sure you have an encrypted image)"<<endl;
	cout<<"waiting for your option:";
	cin>>action;
	switch (action)
	{
		case 1:
		{
			Img_img img_img;
			string host_img,guest_img,out_img;
			cout<<"Enter host image path:";
			cin>>host_img;
			cout<<"Enter guest image path:";
			cin>>guest_img;
			cout<<"Enter output image path:";
			cin>>out_img;
			IplImage* main_img = 0;
			IplImage* hide_img = 0;
			main_img = cvLoadImage(host_img.c_str());			//loads image assign it to pointer
			hide_img = cvLoadImage(guest_img.c_str());
			if(main_img == 0)
			{
				cout<<"host image path is not correct"<<endl;
				exit(0);
			}
			if(hide_img == 0)
			{
				cout<<"guest image path is not correct"<<endl;
				exit(0);
			}
			img_img.encrypt(main_img,hide_img,out_img);
			break;
		}	
	
		case 2:
		{
			Img_img img_img;
			IplImage* encrypted_img = 0;
			string ei,out_img;
			cout<<"Enter encrypted image path:";
			cin>>ei;
			cout<<"Enter output image path:";
			cin>>out_img;
			encrypted_img = cvLoadImage(ei.c_str());		//loads image assign it to pointer
			if(encrypted_img == 0)
			{
				cout<<"encrypted image path is not correct"<<endl;
				exit(0);
			}
			img_img.decrypt(encrypted_img,out_img);
			break;
		}
		
		case 3:
		{
			Txt_img txt_img;
			string img_path,txt,out_img;
			IplImage* img = 0;
			cout<<"Enter host image path:";
			cin>>img_path;
			cout<<"Enter txt file path:";
			cin>>txt;
			cout<<"Enter output image path:";
			cin>>out_img;
			img = cvLoadImage(img_path.c_str());		//loads image assign it to pointer
			if(img == 0)
			{
				cout<<"host image cannot be opened"<<endl;
				exit(0);
			}
			txt_img.encode(txt,img,out_img);
			break;
		}
		
		case 4:
		{
			Txt_img txt_img;
			string img_path,out_file;
			IplImage* img = 0;
			cout<<"Enter encrypted image path:";
			cin>>img_path;
			cout<<"Enter output txt file path:";
			cin>>out_file;
			img = cvLoadImage(img_path.c_str());		//loads image assign it to pointer
			if(img == 0)
			{
				cout<<"image cannot be opened"<<endl;
				exit(0);
			}
			txt_img.decode(img,out_file);
			break;
		}
		
		default:
			cout<<"Enter a valid option"<<endl;
	}
	return 0;
}
