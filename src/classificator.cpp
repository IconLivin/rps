#include "classificator.h"

HandClassificator::HandClassificator() {
	path_to_model ="../../rps/models/mobilenet_new_graph.pb";
	width = 224;
	height = 224;
	mean = (127.5, 127.5, 127.5);
	swap = 0;
	scale = 0.007;
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