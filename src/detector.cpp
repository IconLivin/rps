#include "detector.h"

DnnDetector::DnnDetector(/*string ptm, string ptc, string ptl, int nwidth, int nheight, Scalar nmean, bool srb, double sc*/) {
	path_to_model = "C:\\Users\\temp2019\\Desktop\\rps\\rps\\models\\res10_300x300_ssd_iter_140000.caffemodel";
	path_to_config = "C:\\Users\\temp2019\\Desktop\\rps\\rps\\models\\deploy.prototxt.txt";
	//path_to_labels = ptl;
	//predict = new vector<Mat>(16);
	width = 300;
	height = 300;
	mean = (104, 177, 123);
	swap = 0;
	scale = 1;
	net = readNet(path_to_model, path_to_config);
	net.setPreferableBackend(DNN_BACKEND_OPENCV);
	net.setPreferableTarget(DNN_TARGET_CPU);
}

//Функция получения закодированного вектора предсказаний
vector<DetectedObject> DnnDetector::Detect(Mat image) {
	Mat tens, tmp1;
	blobFromImage(image, tens, scale, Size(width, height), mean, swap, false);
	net.setInput(tens);
	tmp1 = net.forward().reshape(1, 1);
	int rows = tmp1.cols / 7;
	tmp1 = tmp1.reshape(1, rows);
	vector<DetectedObject> result;
	for (int i = 0; i < rows; i++) {
		DetectedObject tmp;
		tmp.score = tmp1.at<float>(i, 2);
		if (tmp.score > 0.7) {
			tmp.classId = tmp1.at<float>(i, 1);
			tmp.Left = tmp1.at<float>(i, 3)*image.cols;
			tmp.Bottom = tmp1.at < float>(i, 4)*image.rows;
			tmp.Right = tmp1.at<float>(i, 5)*image.cols;
			tmp.Top = tmp1.at<float>(i, 6)*image.rows;
			result.push_back(tmp);
		}
	}
	return result;
}

