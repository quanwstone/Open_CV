//º”‘ÿ±æµÿÕº∆¨≤‚ ‘ÕºœÒ«≥øΩ±¥∫Õ…ÓøΩ±¥

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

	Mat m_image_result;

	flip(m_image,m_image_result,0);
	
	Mat m_image_deep;

	m_image_result.copyTo(m_image_deep);

	Mat m_image_shallow;
	
	m_image_shallow = m_image_result;

	flip(m_image,m_image_result,1);
	
	imshow("Show",m_image);
	imshow("Deep",m_image_deep);
	imshow("Shallow",m_image_shallow);
	imshow("Flip",m_image_result);
	
	waitKey(0);

	return 0;
}