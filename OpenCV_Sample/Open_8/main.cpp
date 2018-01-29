//加载本地图片Mean Shift查找

#include<stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;

class ContentFinder{
private:
	int in_nChannels[1];
	float in_fRange[2];
	int in_nHistSize[1];
	float const *in_fRanges[1];
	MatND histogram;
public:
	ContentFinder(){
	 in_nChannels[0] = 0;
	 in_fRange[0] = 0.0;
	 in_fRange[1] = 255.0;
	 in_fRanges[0] = in_fRange;
	}
	void sethistorgram(MatND hist);
	Mat find(const Mat &image,float min,float max,int *channels,int dim);
};
void ContentFinder::sethistorgram(MatND hist)
{
	histogram = hist;
}
Mat ContentFinder::find(const Mat &image,float min,float max,int *channels,int dim)
{
	Mat result;
	
	in_fRange[0] = min;
	in_fRange[1] = max;

	for(int i=0;i<dim;i++){
		this->in_nChannels[i] = channels[i];
	}

	calcBackProject(&image,1,in_nChannels,histogram,result,in_fRanges,255.0);

	return result;
}
class ColorHistorgram{
private:
	int		in_nChannels[3];
	float	in_fRange[2];
	const float *in_fRanges[3];
	int		in_nHistSize[3];
public:
	ColorHistorgram(){
		in_nChannels[0] = 0;
		in_nChannels[1] = 1;
		in_nChannels[2] = 2;

		in_fRange[0] = 0.0;
		in_fRange[1] = 180.0;

		in_fRanges[0] = in_fRange;
		in_fRanges[1] = in_fRange;
		in_fRanges[2] = in_fRange;

		in_nHistSize[0] = in_nHistSize[1] = in_nHistSize[2] = 255;
	}
	MatND getHueHistorgram(Mat &image,int saturation);
};
MatND ColorHistorgram::getHueHistorgram(Mat &image,int saturation)
{
	MatND hist;
	Mat mlab;
	Mat mask;

	cvtColor(image,mlab,CV_BGR2HSV);
	
	if(saturation >0){
		
		std::vector<Mat>V;
		
		split(image,V);

		threshold(V[1],mask,saturation,255,THRESH_BINARY);
	}
	calcHist(&image,1,in_nChannels,mask,hist,1,in_nHistSize,in_fRanges);

	return hist;
}
int main(int argc,char*argv[])
{
	namedWindow("Show");
	
	Mat m_image;
	Mat m_image2;
	int saturation = 65;

	m_image = imread("baboon1.jpg",1);
	m_image2 = imread("baboon2.jpg",1);

	Mat m_Rio = m_image(Rect(110,260,35,40));

	ColorHistorgram m_ColorInstance;

	MatND m_hist_hvs = m_ColorInstance.getHueHistorgram(m_Rio,saturation);

	ContentFinder m_findInstance;

	m_findInstance.sethistorgram(m_hist_hvs);

	Mat hsv;
	std::vector<Mat>v;

	cvtColor(m_image2,hsv,CV_BGR2HSV);
	
	split(hsv,v);
	
	Mat result;
	
	threshold(v[1],v[1],saturation,255,THRESH_BINARY);
	
	imshow("V1",v[1]);

	int ch[1]={0};
	
	result = m_findInstance.find(hsv,0.0,180.0,ch,1);
	
	imshow("Find",result);

	bitwise_and(result,v[1],result);
	
	imshow("bitwise_and",result);

	Rect rect(110,260,35,40);

	TermCriteria criteria(TermCriteria::MAX_ITER,10,0.01);
	
	cout<<"meanShift:"<<meanShift(result,rect,criteria)<<endl;
	
	rectangle(m_image2,rect,Scalar(0,0,255));

	imshow("Show",m_image2);
	
	imshow("Image1",m_image);

	imshow("Result",result);

	waitKey(0);

	return 0;
}