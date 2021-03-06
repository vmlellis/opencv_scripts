//  Compile: g++ -o camera1 camera1.cpp `pkg-config --cflags --libs opencv`

#include "cv.h" 
#include "highgui.h" 
#include <stdio.h>

using namespace std;

void help()
{
  cout 
  << "--------------------------------------------------------------------------"   << endl
  << "This program demonstrates how to display video"                               << endl
  << "--------------------------------------------------------------------------"   << endl;
}

 // A Simple Camera Capture Framework 
 int main() 
 {
  CvCapture* capture = cvCaptureFromCAM( 1 );

  help();

  if ( !capture ) {
    fprintf( stderr, "ERROR: capture is NULL \n" );
    getchar();
    return -1;
  }
  // Create a window in which the captured images will be presented
  cvNamedWindow( "mywindow", CV_WINDOW_AUTOSIZE );
  // Show the image captured from the camera in the window and repeat
  while ( 1 ) {
    // Get one frame
    IplImage* frame = cvQueryFrame( capture );
    if ( !frame ) {
      fprintf( stderr, "ERROR: frame is null...\n" );
      getchar();
      break;
    }
    cvShowImage( "mywindow", frame );
    // Do not release the frame!
    //If ESC key pressed, Key=0x10001B under OpenCV 0.9.7(linux version),
    //remove higher bits using AND operator
    if ( (cvWaitKey(10) & 255) == 27 ) break;
  }
  // Release the capture device housekeeping
  cvReleaseCapture( &capture );
  cvDestroyWindow( "mywindow" );
  return 0;
 }