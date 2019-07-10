#include "classificator.h"

HandClassificator::HandClassificator(string ptm/*, string ptc, string ptl, int nwidth, int nheight, Scalar nmean, bool srb*/) {
	path_to_model = ptm;
	//path_to_config = ptc;
	//path_to_labels = ptl;
	width = 224;
	height = 224;
	mean = (103.94, 116.78, 123.68);
	swap = 0;
	scale = 0.017;
	net = readNet(path_to_model);
	net.setPreferableBackend(DNN_BACKEND_OPENCV);
	net.setPreferableTarget(DNN_TARGET_CPU);
}

Mat HandClassificator::Classify(Mat image) {
	Mat tens, res;
	blobFromImage(image, tens, scale, Size(width, height), mean, swap, false);
	net.setInput(tens);
	res = net.forward();
	res = res.reshape(1, 1);
	return res;
}