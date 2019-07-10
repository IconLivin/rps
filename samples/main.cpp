#include <iostream>
#include "classificator.h"


int main() 
{
	//Initialized arguments
	VideoCapture cap("C:/Users/temp2019/Desktop/Новая папка/CV-SUMMER-CAMP/data/topdogs.mp4");
	Mat frame;
	string model_path =" ";
	string config_path = " ";
	string label_path = " ";
	HandClassificator(model_path, config_path, label_path);
	//work with video
	while (true) {
		cap >> frame;

		imshow("Я люблю собак", frame);
		char ch = (char)waitKey(2);
		if (ch == 'q')
			break;
	}
	cout << " " << endl;
	return 0;
}