//º”‘ÿ±æµÿÕº∆¨

#include<stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;

int main(int argc,char*argv[])
{
	namedWindow("Show");
	
	Mat m_image;

	m_image = imread("bitmap.png",1);

	imshow("Show",m_image);
	
	waitKey(0);

	return 0;
}