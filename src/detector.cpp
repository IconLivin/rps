#include "detector.h"

DnnDetector::DnnDetector(string ptm, string ptc, string ptl, int nwidth, int nheight, Scalar nmean, bool srb, double sc) {
	path_to_model = "C:\\Users\\temp2019\\Desktop\\rps\\rps\\Transportation\\action_recognition\\resnet34_vtn\\kinetics\\decoder\\dldt\\action-recognition-0001-decoder-fp16.bin";
	path_to_config = "C:\\Users\\temp2019\\Desktop\\rps\\rps\\Transportation\\action_recognition\\resnet34_vtn\\kinetics\\decoder\\dldt\\action-recognition-0001-decoder-fp16.xml";
	path_to_labels = ptl;
	predict = new vector<Mat>(16);
	width = 224;
	height = 224;
	mean = (0,0,0);
	swap = 0;
	scale = 1;
	net = readNet(path_to_model, path_to_config);
	net.setPreferableBackend(DNN_BACKEND_OPENCV);
	net.setPreferableTarget(DNN_TARGET_CPU);
}

//Функция получения закодированного вектора предсказаний
void DnnDetector::Detect(Mat image) {
	Mat tens, tmp1;
	blobFromImage(image, tens, scale, Size(width, height), mean, swap, false);
	net.setInput(tens);
	tmp1 = net.forward().reshape(1, 1);
	predict->push_back(tmp1);
}

