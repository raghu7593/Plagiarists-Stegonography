#include <iostream>
#include "img_img.h"
#include <cstdlib>
using namespace std;

//image is resized to given height and width
/*
	FUNCTION NAME	:  resize_val
	INPUT		  		:  IplImage(input image pointer),int(height),int(width)
	OUTPUT 			:  IplImage(input image pointer)
	DESCRIPTION		:  resize image into given size
*/

IplImage* Img_img :: resize_val(IplImage* img,int height,int width)
{
	IplImage *result = cvCreateImage(cvSize(width,height),img->depth,img->nChannels);  //creates image of given quantities
	cvResize(img,result);		//resizes img to result
	return result;
}

/*
	FUNCTION NAME	:  resize_per
	INPUT		  		:  IplImage(input image pointer),int(height percentage),int(width percentage)
	OUTPUT 			:  IplImage(input image pointer)
	DESCRIPTION		:  resize image into given size
*/	
//image is resized to given percentage
IplImage* Img_img :: resize_per(IplImage* img,int height_per,int width_per)
{
	int height,width;
	width = (img->width*width_per)/100;
	height = (img->height*height_per)/100;
	IplImage *result = cvCreateImage(cvSize(width,height),img->depth,img->nChannels);
	cvResize(img,result);
	return result;
}

//returns width percentage i.e, how much % width(main image) > width(hide image)	
/*
	FUNCTION NAME	:  width_per
	INPUT		  		:  IplImage(main image pointer),IplImage(hide image pointer)
	OUTPUT 			:  int(% of width more or less)
	DESCRIPTION		:  precentage of width more or less
*/
int Img_img :: width_per(IplImage* main_img,IplImage* hide_img)
{
	int wi_percent;
	wi_percent = (hide_img->width*100)/main_img->width;
	return wi_percent;
}

//returns height percentage i.e, how much % height(main image) > height(hide image)	
/*
	FUNCTION NAME	:  height_per
	INPUT		  		:  IplImage(main image pointer),IplImage(hide image pointer)
	OUTPUT 			:  int(% of height more or less)
	DESCRIPTION		:  precentage of height more or less
*/
int Img_img :: height_per(IplImage* main_img,IplImage* hide_img)
{
	int hi_percent;
	hi_percent = (hide_img->height*100)/main_img->height;
	return hi_percent;
}

//encrypts images	
/*
	FUNCTION NAME	:  encrypt
	INPUT		  		:  IplImage(main image pointer),IplImage(hide image pointer),string(encrypted image name)
	OUTPUT 			:  NONE
	DESCRIPTION		:  takes first four values in binary from each pixel of RGB in main and add it to the 
							first four values in binary from each pixel of RGB in hide combines to form an image
*/
void Img_img :: encrypt(IplImage* main_img, IplImage* hide_img, string output_img)
{
	if((main_img == 0) or (hide_img == 0))
	{
		cout<<"given images are not found"<<endl;
		exit(0);
	}
	else 
	{
		int ht_per,wd_per;
		ht_per = height_per(main_img,hide_img);
		wd_per = width_per(main_img,hide_img);
		IplImage* resized_hide_img = resize_val(hide_img,main_img->height,main_img->width);
	   cvNamedWindow(output_img.c_str(), CV_WINDOW_AUTOSIZE);		//creates window by name encrypted image
	   cvMoveWindow(output_img.c_str(), 100, 100);					//starting position of image is 100,100
		IplImage *des = cvCreateImage(cvSize(main_img->width,main_img->height),main_img->depth,main_img->nChannels);
		CvScalar mi,hi,fi;
		for(int i=0;i<main_img->height;i++)
		{
			for(int j=0;j<main_img->width;j++)
			{	
				mi = cvGet2D(main_img,i,j);  //cvGet2D(main_img,i,j) returns pixel i,j of main_img
				hi = cvGet2D(resized_hide_img,i,j);
				for(int k=0;k<3;k++)
					fi.val[k] = ((((int)(((int)mi.val[k])/16))*16) + ((int)(((int)hi.val[k])/16)));
				cvSet2D(des,i,j,fi);
			}
		}
		fi.val[0] = ht_per;
		fi.val[1] = wd_per;
		fi.val[2] = 0;
		cvSet2D(des,0,0,fi);	
		cvSaveImage(output_img.c_str(),des);				//saves image to given out file name
		cvShowImage(output_img.c_str(),des);				//display image
		cvWaitKey(0);											//waits until user presses a button
		cvDestroyWindow(output_img.c_str());				//destroys window
	}
}

//decrypts image
/*
	FUNCTION NAME	:  decrypt
	INPUT		  		:  IplImage(encrypted image pointer),string(encrypted image name)
	OUTPUT 			:  NONE
	DESCRIPTION		:  takes last four values in binary from each pixel of RGB in encrypted image and forms an image
*/
void Img_img :: decrypt(IplImage* encrypted_img,string output_img)
{
	if(encrypted_img == 0)
	{
		cout<<"given path is not correct for image"<<endl;
		exit(0);
	}
	else
	{
		int height_per,width_per;
		IplImage *des = cvCreateImage(cvSize(encrypted_img->width,encrypted_img->height),encrypted_img->depth,encrypted_img->nChannels);
		CvScalar mi,fi;
	   cvNamedWindow(output_img.c_str(), CV_WINDOW_AUTOSIZE);
	   cvMoveWindow(output_img.c_str(), 100, 100);
		mi = cvGet2D(encrypted_img,0,0);
		height_per = mi.val[0];
		width_per = mi.val[1];
		for(int i=0;i<encrypted_img->height;i++)
		{
			for(int j=0;j<encrypted_img->width;j++)
			{
				mi = cvGet2D(encrypted_img,i,j);
				for(int k=0;k<3;k++)
					fi.val[k] = (((int)((int)mi.val[k])%16)*16);
				cvSet2D(des,i,j,fi);
			}
		}
		IplImage *resized_img = resize_per(des,height_per,width_per);
		cvSaveImage(output_img.c_str(),resized_img);
		cvShowImage(output_img.c_str(),resized_img);
		cvWaitKey(0);
		cvDestroyWindow(output_img.c_str());
	}
}
