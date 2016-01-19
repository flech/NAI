// NAI_TEST.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include <opencv2\\opencv.hpp>
#include "opencv2/highgui/highgui.hpp"


using namespace cv;
int main()
{


		VideoCapture cap(0);
		while (cap.isOpened())
		{
			std::cout << "HEHE";
			Mat frame;
			if (!cap.read(frame))
				break;
			imshow("Screen", frame);
			int k = waitKey(10);
			if (k == 27) {
				break;
			}
		}
		return 0;
}
