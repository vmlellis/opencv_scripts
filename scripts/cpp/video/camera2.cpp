#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;
using namespace std;
 
int main() {
VideoCapture stream1(1);   //0 is the id of video device.0 if you have only one camera.
 
if (!stream1.isOpened()) { //check if video device has been initialised
cout << "cannot open camera";
return -1;
}

//unconditional loop
while (true) {
Mat cameraFrame;
stream1.read(cameraFrame);
imshow("cam", cameraFrame);
if (waitKey(90) >= 0)
break;
}
return 0;
}