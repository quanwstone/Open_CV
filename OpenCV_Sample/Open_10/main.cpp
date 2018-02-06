//º”‘ÿ±æµÿÕº∆¨erode dilate

#include<stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;
class MorphFeatures{
private:
	Mat mat_input;
public:
	MorphFeatures(){
	};
	Mat SetThreshold(Mat& in_mat,int in_shold);
	Mat GetEdges(Mat& in_mat,int in_shold);
};
Mat MorphFeatures::GetEdges(Mat &in_mat,int in_shold)
{
	Mat result;
	
	morphologyEx(in_mat,result,MORPH_GRADIENT,Mat());
	result = SetThreshold(result,in_shold);

	return result;
}
Mat MorphFeatures::SetThreshold(Mat& in_mat,int in_shold)
{
	Mat result;
	if(in_shold >0){
		threshold(in_mat,result,in_shold,255,THRESH_BINARY);
	}
	return result;
}
int main(int argc,char*argv[])
{
	namedWindow("Show");
	
	Mat m_image;

	m_image = imread("bitmap.png",0);

//	imshow("Show",m_image);
	
	Mat m_erode;
	
	erode(m_image,m_erode,Mat());
//	imshow("Erode",m_erode);

	Mat m_dilate;
	
	dilate(m_image,m_dilate,Mat());
//	imshow("Dilate",m_dilate);

	Mat m_elemnt(5,5,CV_8U,Scalar(1));
	Mat m_close;

	morphologyEx(m_image,m_close,MORPH_CLOSE,m_elemnt);
//	imshow("Close",m_close);

	Mat m_open;
	morphologyEx(m_image,m_open,MORPH_OPEN,m_elemnt);
//	imshow("Open",m_open);

	Mat m_edges;
	m_edges = imread("building.jpg",0);
	
	MorphFeatures morphfeature;
	
	Mat m_edges_result = morphfeature.GetEdges(m_edges,40);
	
	Mat m_shold = morphfeature.SetThreshold(m_edges,40);
	
	imshow("Edges",m_edges_result);
	imshow("Shold",m_shold);

	waitKey(0);

	return 0;
}