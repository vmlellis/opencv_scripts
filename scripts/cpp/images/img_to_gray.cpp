#include <cv.h>
#include <highgui.h>

using namespace cv;

int main( int argc, char** argv )
{
 char* imageName = argv[1];

 Mat image;
 image = imread( imageName, 1 );

 if( argc < 2 || !image.data )
 {
   printf( " No image data \n " );
   return -1;
 }

 if( argc != 3  )
 {
   printf( " No output image \n " );
   return -1;
 }

 Mat gray_image;
 cvtColor( image, gray_image, CV_BGR2GRAY );

 imwrite( argv[2], gray_image );

 namedWindow( imageName, CV_WINDOW_AUTOSIZE );
 namedWindow( "Gray image", CV_WINDOW_AUTOSIZE );

 imshow( imageName, image );
 imshow( "Gray image", gray_image );

 waitKey(0);

 return 0;
}