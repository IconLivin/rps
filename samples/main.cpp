#include <iostream>
#include "classificator.h"


int main() 
{
	VideoCapture cap("C:/Users/temp2019/Desktop/Новая папка/CV-SUMMER-CAMP/data/topdogs.mp4");
	Mat frame;
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