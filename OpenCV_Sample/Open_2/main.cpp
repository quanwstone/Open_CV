//加载本地图片并且旋转

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

	Mat m_image_flip_level;
	
	flip(m_image,m_image_flip_level,1);

	Mat m_image_flip_Vertical;

	flip(m_image,m_image_flip_Vertical,0);

	imshow("Show",m_image);
	
	imshow("Flip_Level",m_image_flip_level);

	imshow("Flip_Vertical",m_image_flip_Vertical);
	
	imwrite("Write.png",m_image_flip_Vertical);

	waitKey(0);

	return 0;
}