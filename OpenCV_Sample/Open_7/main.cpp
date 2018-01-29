//加载本地图片获取反投影直方图

#include<stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;
class ContentFinder{
private:
	int in_nChannels[1];
	float in_fRange[2];
	const float *in_fRanges[1];
	MatND historgram;
public:
	ContentFinder(){
		
		in_nChannels[0] = 0;
		
		in_fRange[0] = 0.0;
		in_fRange[1] = 255.0;
		
		in_fRanges[0] = in_fRange;
	};
	void sethistorgram(MatND hist);
	Mat find(const Mat &image,float min,float max,int *channels,int dim);
};
void ContentFinder::sethistorgram(MatND hist)
{
	historgram = hist;
	
	normalize(historgram,historgram,1.0);
}
Mat ContentFinder::find(const Mat &image,float min,float max,int *channels,int dim)
{
	Mat result;
	
	in_fRange[0] = min;
	in_fRange[1] = max;

	for(int i=0;i<dim;i++){
		this->in_nChannels[i] = channels[i];
	}

	calcBackProject(&image,1,in_nChannels,historgram,result,in_fRanges,255.0);

	return result;
}
class ColorHist{
public:
	int		in_nChannels[1];
	float	in_fRange[2];
	const float	*in_fRanges[1];
	int		in_nHistSize[1];
public:
	ColorHist(){
		
		in_nChannels[0] = 0;
		in_fRange[0] = 0.0;
		in_fRange[1] = 255.0;
		in_fRanges[0] = in_fRange;
		in_nHistSize[0] = 255;

	};
	MatND getHistorgram(Mat &image);
};

MatND ColorHist::getHistorgram(Mat &image)
{
	MatND result;

	calcHist(&image,1,in_nChannels,Mat(),result,1,in_nHistSize,in_fRanges);

	return result;
}
int main(int argc,char*argv[])
{
	namedWindow("Show");
	
	Mat m_image;

	m_image = imread("waves.jpg",1);

	ColorHist hist;

	Mat RIO = m_image(Rect(360,55,40,50));
	
	rectangle(m_image,cvPoint(360,55),cvPoint(400,110),Scalar(255,0,0),1,1,0); 

	MatND matnd = hist.getHistorgram(RIO);
	
	ContentFinder finder;

	finder.sethistorgram(matnd);

	int channels[1]={0};
	
	Mat re = finder.find(m_image,0.0f,255.0f,channels,1);

	imshow("Show",m_image);
	
	imshow("Find",re);

	waitKey(0);

	return 0;
}