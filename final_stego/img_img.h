#include "cv.h"
#include "highgui.h"
#include <string>
using namespace std;

class Img_img
{
	public:
		//image is resized to given height and width
		IplImage* resize_val(IplImage* img,int height,int width);
		
		//image is resized to given percentage
		IplImage* resize_per(IplImage* img,int height_per,int width_per);
		
		//returns width percentage i.e, how much % width(main image) > width(hide image)
		int width_per(IplImage* main_img,IplImage* hide_img);
		
		//returns height percentage i.e, how much % height(main image) > height(hide image)
		int height_per(IplImage* main_img,IplImage* hide_img);
		
		//encrypts images
		void encrypt(IplImage* main_img,IplImage* hide_img, string output_img);
		
		//decrypts image
		void decrypt(IplImage* encrypted_img, string output_img);
};
