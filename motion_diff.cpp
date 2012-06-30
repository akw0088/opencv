#include <opencv/cv.h>
#include <opencv/highgui.h>


int main ( int argc, char **argv )
{
	// use first camera attached to computer
	CvCapture *capture;

	// image data structures
	IplImage *img1;  
	IplImage *img2;
	IplImage *imggray1;
	IplImage *imggray2;
	IplImage *imggray3;
	IplImage *imgsize;
	int key = 0;


	capture = cvCaptureFromCAM(0);
	if(!capture)
    {
        printf("Could not initialize capturing...\n");
        return -1;
    }

	imgsize = cvQueryFrame( capture );
	if( !imgsize )
		return -1;
 
	// grayscale buffers
	imggray1 = cvCreateImage( cvGetSize( imgsize ), IPL_DEPTH_8U, 1);
	imggray2 = cvCreateImage( cvGetSize( imgsize ), IPL_DEPTH_8U, 1);
	imggray3 = cvCreateImage( cvGetSize( imgsize ), IPL_DEPTH_8U, 1);
   

	while ( key != 27 )
	{
		// load image one
		img1 = cvQueryFrame( capture );

		// convert rgb to grayscale
		cvCvtColor( img1, imggray1, CV_RGB2GRAY );
	   
		// quit if user press 'q' and wait a bit between images
		key = cvWaitKey( 20 );
	   
		// load image two
		img2 = cvQueryFrame( capture );

		// convert rgb to grayscale
		cvCvtColor( img2, imggray2, CV_RGB2GRAY );
	   
		// compute difference
		cvAbsDiff( imggray1, imggray2, imggray3 );
	   
		// display difference
		cvNamedWindow( "video", 1 );
		cvShowImage( "video", imggray3 );
	}
 
	// release camera and clean up resources when "q" is pressed
	cvReleaseCapture( &capture );
	cvDestroyWindow( "video" );
	return 0;
}
