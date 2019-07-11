#include "classificator.h"

HandClassificator::HandClassificator(/*string ptm  , string ptc, string ptl, int nwidth, int nheight, Scalar nmean, bool srb*/) {
	path_to_model = "C:\\Users\\temp2019\\Desktop\\rps\\rps\\models\\mobilnet_for_rps.pb";
	path_to_config = "C:\\Users\\temp2019\\Desktop\\Новая папка\\CV-SUMMER-CAMP\\data\\classification\\squeezenet\\1.1\\caffe\\squeezenet1.1.prototxt";
	//path_to_labels = ptl;
	width = 227;
	height = 227;
	mean = (104, 117, 123);
	swap = 0;
	scale = 1;
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