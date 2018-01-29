//加载本地图片进行简单的图片计算

#include<stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;

int main(int argc,char*argv[])
{
	
	Mat m_imageF,m_imageS,m_imageR;

	m_imageF = imread("bitmap.png",1);
#ifdef Add
	m_imageS = imread("bitmapBlend.png",1);

	addWeighted(m_imageF,0.5,m_imageS,0.9,0,m_imageR);
#endif
	m_imageS = imread("Logo.png",1);

	Mat m_image_ROI;
	m_image_ROI = m_imageF(Rect(200,200,m_imageS.cols,m_imageS.rows));

	Mat m_image_mask = imread("Logo.png",0);

	m_imageS.copyTo(m_image_ROI,m_image_mask);

	imshow("FShow",m_imageF);
//	imshow("SShow",m_imageS);
//	imshow("RShow",m_image_RIO);

	waitKey(0);

	return 0;
}