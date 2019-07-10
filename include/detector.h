#pragma once
#include <iostream>
#include <string>

#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include "detectedobject.h"

using namespace cv;
using namespace cv::dnn;
using namespace std;


class DnnDetector {
	string path_to_model, path_to_config, path_to_labels;
	int width, height;
	Scalar mean;
	bool swap;
	Net net;
	double scale;
	vector<Mat> *predict;
public:
	DnnDetector(string ptm, string ptc, string ptl, int nwidth, int nheight, Scalar nmean = (0, 0, 0, 0), bool srb = 0, double scale = 0);
	void Detect(Mat image);
	DnnDetector() { delete predict; }
};