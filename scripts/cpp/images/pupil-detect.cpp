/**
 * Program to detect pupil, based on
 * http://www.codeproject.com/Articles/137623/Pupil-or-Eyeball-Detection-and-Extraction-by-C-fro
 * with some improvements.
 * Compile: g++ -o pupil-detect pupil-detect.cpp `pkg-config --cflags --libs opencv`
 */
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>

int main(int argc, char** argv)
{
	// Load image
	cv::Mat src = cv::imread(argv[1]);
	if (src.empty())
		return -1;

	// Invert the source image and convert to grayscale
	cv::Mat gray;
	cv::cvtColor(~src, gray, CV_BGR2GRAY);

	//cv::imshow("invert", ~src);
	//cv::imshow("gray", gray);

	// Convert to binary image by thresholding it
	cv::threshold(gray, gray, 220, 255, cv::THRESH_BINARY);

	//cv::imshow("binary", gray);

	// Find all contours
	std::vector<std::vector<cv::Point> > contours;
	cv::findContours(gray.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	// Fill holes in each contour
	cv::drawContours(gray, contours, -1, CV_RGB(255,255,255), -1);

	//cv::imshow("contour", gray);

	for (int i = 0; i < contours.size(); i++)
	{
		double area = cv::contourArea(contours[i]);
		cv::Rect rect = cv::boundingRect(contours[i]);
		int radius = rect.width/2;

		// If contour is big enough and has round shape
		// Then it is the pupil
		if (area >= 30 && 
		    std::abs(1 - ((double)rect.width / (double)rect.height)) <= 0.2 &&
				std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2)	
		{
			cv::circle(src, cv::Point(rect.x + radius, rect.y + radius), radius, CV_RGB(255,0,0), 2);
		}
	}

	cv::imshow("image", src);
	cv::waitKey(0);

	return 0;
}
