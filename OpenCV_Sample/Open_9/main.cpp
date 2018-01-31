//加载本地图片 通过直方图比较图片

#include<stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;
//
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
	MatND getHistogram(Mat &image);
	Mat colorReduce(Mat &image,int div);
};
Mat ColorHistorgram::colorReduce(Mat &image,int div)
{
	int n= static_cast<int>(log(static_cast<double>(div))/log(2.0));
	// mask used to round the pixel value
	uchar mask= 0xFF<<n; // e.g. for div=16, mask= 0xF0

	Mat_<Vec3b>::const_iterator it= image.begin<Vec3b>();
	Mat_<Vec3b>::const_iterator itend= image.end<Vec3b>();

	// Set output image (always 1-channel)
	Mat result(image.rows,image.cols,image.type());
	Mat_<Vec3b>::iterator itr= result.begin<Vec3b>();

	for ( ; it!= itend; ++it, ++itr) {
        
		(*itr)[0]= ((*it)[0]&mask) + div/2;
		(*itr)[1]= ((*it)[1]&mask) + div/2;
		(*itr)[2]= ((*it)[2]&mask) + div/2;
	}
	return result;
}
	// Computes the histogram.
MatND ColorHistorgram::getHistogram(Mat &image) {

	MatND result;

	// Compute histogram
	calcHist(&image, 
		1,			// histogram of 1 image only
		in_nChannels,	// the channel used
		Mat(),	// no mask is used
		result,		// the resulting histogram
		3,			// it is a 3D histogram
		in_nHistSize,	// number of bins
		in_fRanges		// pixel value range
	);

	return result;
}
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
//
class ImageComparator{

private:
	
	Mat		m_Reference; 
	Mat		m_Input;
	MatND	m_RefHist;
	MatND	m_InHist;
	int		m_div;
	ColorHistorgram m_color;

public:

	ImageComparator():m_div(32){

	};
	void SetColorReduction(int in_ireduction);
	int GetColorReduction();
	void SetReferenceImage(Mat& reImage);
	double Compore(Mat& input);
};
void ImageComparator::SetReferenceImage(Mat& in_reImage)
{
	m_Reference = m_color.colorReduce(in_reImage,m_div);
	m_RefHist = m_color.getHistogram(m_Reference);
}
void ImageComparator::SetColorReduction(int in_ireduction)
{
	m_div = in_ireduction;
}
int ImageComparator::GetColorReduction()
{
	return m_div;
}
double ImageComparator::Compore(Mat& in_image)
{
	double dRe = 0.0;
	
	m_Input = m_color.colorReduce(in_image,m_div);
	m_InHist = m_color.getHistogram(m_Input);
	
	dRe = compareHist(m_InHist,m_RefHist,CV_COMP_INTERSECT);

	return dRe;
}
//
int main(int argc,char*argv[])
{
	namedWindow("Show");
	
	Mat image_wa = imread("waves.jpg",1);
	Mat image_be = imread("beach.jpg",1);
	Mat image_bea = imread("bear.jpg",1);
	Mat image_mo = imread("moose.jpg",1);
	Mat image_po = imread("polar.jpg",1);

	ImageComparator compa;

	compa.SetReferenceImage(image_wa);

	cout<<"beach:"<<compa.Compore(image_be)<<endl;
	cout<<"bear:"<<compa.Compore(image_bea)<<endl;
	cout<<"mosse:"<<compa.Compore(image_mo)<<endl;
	cout<<"polar:"<<compa.Compore(image_po)<<endl;

	waitKey(0);

	return 0;
}