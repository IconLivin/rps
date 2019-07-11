#include <iostream>
#include "classificator.h"
#include "detector.h"
const string labels[21] = { "background",
"aeroplane",
"bicycle",
"bird",
"boat",
"bottle",
"bus",
"car",
"cat",
"chair",
"cow",
"diningtable",
"dog",
"horse",
"motorbike",
"person",
"pottedplant",
"sheep",
"sofa",
"train",
"tvmonitor"
};

int main() 
{
	//Initialized arguments
	string name = "C:\\Users\\temp2019\\Desktop\\rps\\rps\\models\\mobilnet_for_rps.pb";
	Mat frame;
	VideoCapture cap(0);
	cap >> frame;
	int x1 = frame.cols / 8;
	int y1 = frame.rows / 8;
	/*string model_path =" ";
	string config_path = " ";
	string label_path = " ";*/
	int frame1 = 0;
	
	//work with video
	while(true)
	{
		vector<DetectedObject> res;
		DnnDetector det;
		
		//HandClassificator ds;
		cap >> frame;
		//if (frame1 == 15) {
			res = det.Detect(frame);
			while (!res.empty()) {
				string conf = "Confidence: " + std::to_string(res.back().score);
				Point leftbottom(res.back().Left, res.back().Bottom);
				Point righttop(res.back().Right, res.back().Top
				);
				cout << leftbottom << " " << righttop << endl;
				Rect box(leftbottom, righttop);
				rectangle(frame, box, Scalar(71, 99, 255), 1, 1, 0);
				putText(frame, conf, Size(res.back().Right - 10, res.back().Top - 2), FONT_HERSHEY_COMPLEX_SMALL, 1,
					Scalar(10, 99, 255), 1, 0);
				res.pop_back();
			}
			frame1 = 0;

		//}
		//frame1++;
		imshow("Tracking by Matching", frame);
		//frame1++;
		char c = (char)waitKey(2);
		if (c == 'q')
			break;
	}

	
	cout << " " << endl;
	return 0;
}