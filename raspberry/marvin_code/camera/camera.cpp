#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include "client.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;
using namespace cv;

/* Function Headers */
int detectAndDisplay( Mat frame );
/* Global variables */
//String face_cascade_name = "haarcascade_frontalface_alt.xml";
String face_cascade_name = "/home/pi/marvin_code/haarcascade_frontalface_alt.xml";
//String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
String eyes_cascade_name = "/home/pi/marvin_code/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "Capture - Face detection";

int main()
{

	VideoCapture capture;
	Mat frame; // matrice de l'image;
	char buffer[BUF_SIZE_SOCKET];
	int retour = 0;
	int capture_ok = 0;

	fd_set rdfs;

	struct timeval tv;
	tv.tv_sec = 1;
	    tv.tv_usec = 0;
	SOCKET sock = init_connection("127.0.0.1");

	write_server(sock, "camera");

	//-- 1. Load the cascades
	if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
	if( !eyes_cascade.load( eyes_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n"); return -1; };

	capture.open( -1 );
	if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }

	capture.set(CV_CAP_PROP_FRAME_WIDTH,200);
	capture.set(CV_CAP_PROP_FRAME_HEIGHT,200);
	while (  capture.read(frame) )
	{
		/*CONNEXION*/	

		FD_ZERO(&rdfs); // Vide l'ensemble
		/*add STDION_FILENO */ //descripteur 0
		FD_SET(STDIN_FILENO, &rdfs);
		/* add socket*/
		FD_SET(sock, &rdfs);

		//if (select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
		if (select(sock + 1, &rdfs, NULL, NULL, &tv) == -1)
		{
			perror("error select");
			exit(errno);
		}
		/*
		 *
		 * Camera*/
		if( frame.empty() )
		{
			printf(" --(!) No captured frame -- Break!");
			break;
		}
		//-- 3. Apply the classifier to the frame
		retour	 = detectAndDisplay( frame );
		int c = waitKey(10);
		if( (char)c == 27 ) { break; } // escape

//		sleep(1);
		/*message*/
		if (capture_ok)
		{
			if (retour)
			{
		 		write_server(sock, "1");
				retour = 0;
			}
			else
				write_server(sock, "0");
		}
		if(FD_ISSET(sock, &rdfs))
		{
			int n = read_server(sock, buffer);

			/*server down*/
			if (n == 0)
			{
				printf("Server disconnected !\n");
				break;
			}
			if (!strcmp(buffer, "start"))
				capture_ok = 1;
			if (!strcmp(buffer, "stop"))
				capture_ok = 0;
			puts(buffer);
		}
	}
	end_connection(sock);
	return 0;
}
int detectAndDisplay( Mat frame )
{
	std::vector<Rect> faces;
	Mat frame_gray;
	cvtColor( frame, frame_gray, COLOR_BGR2GRAY );

	equalizeHist( frame_gray, frame_gray );
	face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
	/*
	for( size_t i = 0; i < faces.size(); i++ )
	{
		Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
		ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
		Mat faceROI = frame_gray( faces[i] );
		std::vector<Rect> eyes;
		eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );
		for( size_t j = 0; j < eyes.size(); j++ )
		{
			Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
			int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
			circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
		}
	}
	*/
	imshow( window_name, frame );
	if (faces.size() > 0)
	{
		return 1;
	}else
		return 0;

}
