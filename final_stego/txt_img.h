#include <fstream>
#include "cv.h"
#include "highgui.h"
using namespace std;

class Txt_img
{
	public:
		void encode(string txt,IplImage* inp_img, string out_img);
		void decode(IplImage* inp_img, string out);
};
