#include "cv.h" 
#include "highgui.h" 
#include <stdio.h>

int main(int argc, char** argv)
{
  IplImage *capturedImg = cvLoadImage(argv[1],1);

  cvNamedWindow( "image", CV_WINDOW_AUTOSIZE );
	cvShowImage("image",capturedImg);
	while(1)
	{
		if ( (cvWaitKey(10) & 255) == 27 ) break;
	}

  cvDestroyWindow( "mywindow" );
}