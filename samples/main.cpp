#include <iostream>
#include "classificator.h"
#include "detector.h"


int main() 
{
	//Initialized arguments
	string name = "C:\\Users\\temp2019\\Desktop\\rps\\rps\\models\\mobilnet_for_rps.pb";
	VideoCapture cap(0);
	Mat frame;
	cap >> frame;
	int x = frame.cols / 8;
	int y = frame.rows / 8;
	//HandClassificator ds(name);
	Rect rect(Point(x,y*8),Point(7*x,4*y));
	//work with video
	while (true) {
		DnnDetector det;
		vector<DetectedObject> res;
		cap >> frame;
		Mat crop;
		crop = frame(rect);
		imshow("Sasha", crop);
		res = det.Detect(crop);
		while (!res.empty()) {
			string conf = "Confidence: " + std::to_string(res.back().score);
			Point leftbottom(res.back().Left, res.back().Bottom);
			Point righttop(res.back().Right, res.back().Top
			);
			cout << leftbottom << " " << righttop << endl;
			rectangle(frame, rect, Scalar(127, 255, 0), 2);

			putText(frame, conf, Size(res.back().Right - 10, res.back().Top - 2), FONT_HERSHEY_COMPLEX_SMALL, 1,
				Scalar(10, 99, 255), 1, 0);
			res.pop_back();
		}
		rectangle(frame, rect, Scalar(0, 0, 255),2);

		char c = (char)waitKey(2);
		if (c == 'q')
			break;
			
	}
	
	cout << " " << endl;
	return 0;
}