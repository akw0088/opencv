#include <opencv/cv.h>
#include <opencv/highgui.h>

#ifdef IMAGE
int main(int argc, char *argv[])
{
	IplImage* img = cvLoadImage( "test.jpg" );
	cvNamedWindow( "Example1", CV_WINDOW_AUTOSIZE );
	cvShowImage("Example1", img);
	cvWaitKey(0);
	cvReleaseImage( &img );
	cvDestroyWindow( "Example1" );
	return 0;
}
#endif