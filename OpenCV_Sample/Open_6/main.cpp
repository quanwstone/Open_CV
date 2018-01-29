//加载本地图片获取直方图

#include<stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;

class Histogram1D{
private:
	int HistSize[3];//项的数量
	float frange[2];//像素最大值和最小值
	int ichannels[3];//通道个数
	const float *ranges[3];
public:
	Histogram1D(){
		HistSize[0] = 256;
		HistSize[1] = 256;
		HistSize[2] = 256;
		frange[0] = 0.0;
		frange[1] = 255.0;
		ichannels[0] = 0;
		ichannels[1] = 1;
		ichannels[2] = 2;
		ranges[0] = frange;
		ranges[1] = frange;
		ranges[2] = frange;
	};
	MatND gethistogram(Mat &image);
	Mat   gethistogramImage(Mat &image);
};
MatND Histogram1D::gethistogram(Mat &image)
{
	MatND hist;
	//SparseMat hist(3,HistSize,CV_32F);
	
	calcHist(&image,1,ichannels,Mat(),hist,1,HistSize,ranges);
	
	return hist;
}
Mat Histogram1D::gethistogramImage(Mat &image)
{
	
	MatND hist = gethistogram(image);

	double maxVal = 0;
	double minVal = 0;

	minMaxLoc(hist,&minVal,&maxVal,0,0);

	Mat histImage(HistSize[0],HistSize[0],CV_8U,Scalar(255));

	int hpt = static_cast<int>(0.9*HistSize[0]);

	for(int h=0;h<HistSize[0];h++){
		float binVal = hist.at<float>(h);
		int intensity = static_cast<int>(binVal*hpt/maxVal);
		line(histImage,Point(h,HistSize[0]),Point(h,HistSize[0]-intensity),Scalar::all(0));
	}
	return histImage;
}
int main(int argc,char*argv[])
{
	namedWindow("Show");
	
	Mat m_image;

	m_image = imread("bitmap.png",1);
	
	Histogram1D hist;
	
	Mat m_Hist = hist.gethistogramImage(m_image);

	Mat m_threshold;
	threshold(m_image,m_threshold,60,255,THRESH_BINARY);

	imshow("Show",m_Hist);
	
	imshow("Bmp",m_threshold);

	waitKey(0);

	return 0;
}