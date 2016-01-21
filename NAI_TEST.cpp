Skip to content
This repository
Search
Pull requests
Issues
Gist
@flech
Unwatch 1
Star 0
Fork 0 flech / NAI
Code  Issues 0  Pull requests 0  Wiki  Pulse  Graphs  Settings
Branch : master Find file Copy pathNAI / NAI_TEST.cpp
		 84d91f4  an hour ago
		 @flech flech Dodane wykrywanie koloru czerwonego
		 1 contributor
		 RawBlameHistory     58 lines(41 sloc)  1.01 KB
		 // NAI_TEST.cpp : Defines the entry point for the console application.
		 //

#include "stdafx.h"
#include "opencv2/core/core.hpp"
#include <opencv2\\opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"

		 using namespace cv;
using namespace std;

int main()
{


	VideoCapture cap(0);   // open default camer

	if (!cap.isOpened()){
		cout << "ERROR Camera is not working" << endl;
		exit(0);
	}
	else
	{
		Mat edges;  // Przechowuje krawedzie
		cout << "Video display - success. Press ESC to exit." << endl;
		while (cap.isOpened())
		{
			Mat frame;  // Standardowy input
			if (!cap.read(frame))
				break;

			imshow("Screen", frame);

			//cap >> frame; // get a new frame from camera

			cvtColor(frame, edges, COLOR_BGR2HSV);

			Mat filtr;

			//inRange(edges, Scalar(0, 180, 228), Scalar(11, 255, 255), filtr); // Dla czerwonej pokrywki
			//inRange(edges, Scalar(90, 153, 228), Scalar(116, 225, 255), filtr); // Dla niebieskiego korka
			//inRange(edges, Scalar(30, 28, 135), Scalar(86, 160, 255), filtr); // Dla zielonej zapalniczki


			imshow("edges", edges);
			imshow("red", filtr);
			int k = waitKey(10);



			if (k == 27) {   // ASCII 27 dla ESC
				break;
			}
		}
	}
	return 0;
}
