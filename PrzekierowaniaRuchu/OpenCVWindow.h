#pragma once

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "MySqlConnection.h"

#define _USE_MATH_DEFINES
#include <cmath> 
#include <math.h>

using namespace cv;

class OpenCVWindow
{
public:
	OpenCVWindow();
	void openwindow();
	static void MyFilledCircle(Mat img, Point center);
	static void DrawLine(Mat img, Point start, Point end);

private:
	double width, heigh;
};
