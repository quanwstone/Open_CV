//加载本地图片修改像素点

#include<stdio.h>
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>

using namespace cv;
using namespace std;
#define VEC

void Salt(Mat &image,int inCount)
{
#ifdef VEC
	Mat_<Vec3b>::iterator iter = image.begin<Vec3b>();
	for(;iter !=image.end<Vec3b>();iter++){
		(*iter)[0] =(*iter)[0] = 255;
		(*iter)[1] =(*iter)[1] = 255;
		(*iter)[2] =(*iter)[2] = 255;
	}

#else
	for(int i=0;i<inCount;i++)
	{
		int row = rand()%image.rows;
		int col = rand()%image.cols;
		if(image.channels() ==1){
			image.at<uchar>(row,col) = 255;
		}else{//3
			image.at<Vec3b>(row,col)[0] = 255;//B
			image.at<Vec3b>(row,col)[1] = 255;//G
			image.at<Vec3b>(row,col)[2] = 255;//R
		}
	}
#endif

}
void ColorReduce(Mat &image,int inreduce)
{
	int irow = image.rows;
	int icol = image.cols;
	int ichan = image.channels();
	
	for(int i=0;i<irow;i++){

		uchar *data = image.ptr<uchar>(i);

		for(int j=0;j<icol*ichan;j++){
			
			data[j] = data[j]/inreduce *inreduce + inreduce / 2;

		}
	}
}
int main(int argc,char*argv[])
{
	namedWindow("Show");
	
	Mat m_image;

	m_image = imread("bitmap.png",1);
#ifdef VEC
	Salt(m_image,3000);
#endif
	ColorReduce(m_image,64);

	imshow("Show",m_image);
	
	waitKey(0);

	return 0;
}