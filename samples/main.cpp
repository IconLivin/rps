#include <iostream>
#include "classificator.h"


int main() 
{
	VideoCapture cap("C:/Users/temp2019/Desktop/����� �����/CV-SUMMER-CAMP/data/topdogs.mp4");
	Mat frame;
	while (true) {
		cap >> frame;

		imshow("� ����� �����", frame);
		char ch = (char)waitKey(2);
		if (ch == 'q')
			break;
	}
	cout << " " << endl;
	return 0;
}