#include <opencv/cv.h>
#include <opencv/highgui.h>


// C++
#include <iostream>
#include <string>
#include <utility>

// C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include <limits.h>
#include <time.h>
#include <ctype.h>

using namespace std;

bool DEBUG;
static CvMemStorage* storage = 0;
static CvHaarClassifierCascade* cascade = 0;

// Function to detect and draw any faces that is present in an image
void detect_and_draw( IplImage* img )
{
    int scale = 1;
    IplImage* temp = cvCreateImage( cvSize( img->width / scale, img->height / scale ), 8, 3 );
    CvPoint pt1, pt2;

    cvClearMemStorage( storage );

    if( cascade )
	{
        // There can be more than one face in an image. So create a growable sequence of faces.
        // Detect the objects and store them in the sequence
        CvSeq* faces = cvHaarDetectObjects( img, cascade, storage,
                                            1.1, 2, CV_HAAR_DO_CANNY_PRUNING,
                                            cvSize( 40, 40 ) );

        // Loop the number of faces found.
        for( int i = 0; i < ( faces ? faces->total : 0 ); i++ )
		{
            // Create a new rectangle for drawing the face
            CvRect* r = ( CvRect* )cvGetSeqElem( faces, i );

            // Find the dimensions of the face,and scale it if necessary
            pt1.x = r->x * scale;
            pt2.x = ( r->x + r->width ) * scale;
            pt1.y = r->y * scale;
            pt2.y = ( r->y + r->height ) * scale;

            // Draw the rectangle in the input image
            cvRectangle( img, pt1, pt2, CV_RGB( 255, 0, 0 ), 3, 8, 0 );
        }
    }

    cvReleaseImage( &temp );
}

// Main function, defines the entry point for the program.
int main( int argc, char** argv )
{
	string imageIn;
	string imageOut;
	string cascade_file = "haarcascade_frontalface_alt.xml";

	IplImage* image = NULL;
	bool in = true;
	int key = 0;

	DEBUG = false;

	CvCapture *capture;

	while ( key != 27 )
	{
		capture = cvCaptureFromCAM(0);

        // Load the HaarClassifierCascade
        cascade = ( CvHaarClassifierCascade* )cvLoad("haarcascade_frontalface_alt.xml", 0, 0, 0 );

        if( !cascade )
		{
            cerr << "ERROR: Could not load classifier cascade" << endl;
            return -1;
        }

        storage = cvCreateMemStorage( 0 );
        image = cvQueryFrame( capture );

        if(!image)
		{
			break;
        }
		detect_and_draw( image );
		cvNamedWindow( "video", 1 );
		cvShowImage( "video", image );
		key = cvWaitKey( 20 );
   }

    return 0;
}
