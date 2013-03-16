#include "txt_img.h"
#include <fstream>
using namespace std;

/*
	FUNCTION NAME	:  encode
	INPUT		  		:  string(txt file path),IplImage(input image pointer),string(output image name)
	OUTPUT 			:  NONE
	DESCRIPTION		:  encodes text into image
							first converts text into image and then encrypts image in image
*/

void Txt_img :: encode(string txt,IplImage* inp_img,string out_img)
{
	if(inp_img == 0)
	{
		cout<<"given input image path was not correct"<<endl;
		exit(0);
	}
	IplImage *des = cvCreateImage( cvSize(inp_img->width,inp_img->height), inp_img->depth, inp_img->nChannels);
	
	ifstream inp_file(txt.c_str());
	if(!inp_file.is_open())
	{
		cout<<"txt file cannot be opened"<<endl;
		exit(0);
	}
	
	int des_width = inp_img->width;
	int des_height = inp_img->height;
	
	string line;
	int line_len;
	
	int char_ascii;
	CvScalar i2;
	
	int px_x = 0,px_y = 1;
	
	while(!inp_file.eof())
	{
		getline(inp_file,line);
		line_len = line.length();
		
		for(int k=0;k<line_len;k++)
		{
			char_ascii = (int)line[k];     //char ascii value;
			i2.val[0] = (char_ascii/16) * 16;
			i2.val[1] = (char_ascii%16) * 16;
			i2.val[2] = 0;
		
			cvSet2D(des,px_x,px_y,i2);
		
			if(px_y == des_width-1) 
			{
				px_y=0;
				px_x++;
			}
			else px_y++;
		}
		
		if(!inp_file.eof())
		{
			char_ascii = 10;     //char ascii value;
			i2.val[0] = 0;			//(char_ascii/16) * 16;
			i2.val[1] = 160;		//(char_ascii%16) * 16;
			i2.val[2] = 0;
		
			cvSet2D(des,px_x,px_y,i2);
		
			if(px_y == des_width-1) 
			{
				px_y=0;
				px_x++;
			}
			else px_y++;
		}
	}
	inp_file.close();
	
	while(px_x != des_height)
	{
		for(int k=0; k<3; k++)
		{
			i2.val[k] = 255;
			cvSet2D(des,px_x,px_y,i2);
		}
		
		if(px_y == des_width-1) 
		{
			px_y=0;
			px_x++;
		}
		else px_y++;
	}
	Img_img obj;
	obj.encrypt(inp_img,des,out_img);
}

/*
	FUNCTION NAME	:  decode
	INPUT		  		:  IplImage(input image pointer),string(output image name)
	OUTPUT 			:  NONE
	DESCRIPTION		:  decodes txt from image
							first converts internal image from given image(i.e, decrypts given image) and then converts image into text
*/

void Txt_img :: decode (IplImage* inp_img ,string out)
{
	if(inp_img == 0)
	{
		cout<<"Given input image is not found"<<endl;
		exit(0);
	}
	ofstream out_file(out.c_str());
	if(!out_file.is_open())
	{
		cout<<"txt file cannot be opened"<<endl;
		exit(0);
	}
	
	Img_img obj;
	obj.decrypt(inp_img,"image_representing_text.bmp");
	IplImage* img = cvLoadImage("image_representing_text.bmp");

	int img_width = img->width;
	int img_height = img->height;
	
	int mchar_ascii;
	char mchar;
	CvScalar i2;
	
	for(int i=0;i<img_height;i++)
	{
		for(int j=0;j<img_width;j++)
		{	
			if((i==0)and(j==0))
				continue;
			i2 = cvGet2D(img, i,j);
			
			mchar_ascii = ((int)i2.val[0]/16)*16 + ((int)i2.val[1]/16);
			
			if(mchar_ascii<=128)
			{
				mchar = mchar_ascii;
				if(mchar_ascii == 10) 
				{
					out_file<<'\n';
				}
				else 
				{
					out_file<<mchar;
				}
			}
		}
	}
	out_file.close();
}
