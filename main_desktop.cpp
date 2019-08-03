
using namespace std;

int cameraNumber = 0;
if(argc>1)
	cameraNumber = atoi(argv[1])

//get access to the camera
cv::VideoCapture camera;
camera.open(cameraNumber);
if (!camera.isOpened()){
	cerr<< "Error: Could nort access the camera or video!" << endl;
	exit(1);
}

//try to set the camera resolution;
camera.set(cv::CV_CAP_PROP_FRAME_WIDTH, 640);
camera.set(cv::CV_CAP_PROP_FRAME_HEIGHT, 480);

while(true){
	//grab the next camera frame.
	cv::Mat cameraFrame;
	camera >> cameraFrame;
	if(cameraFrame.empty()){
		cerr<<"Error: couldn't grab a camera frame." << endl;
		exit(1);
	}
	//create a blank output image, that we will draw onto.
	cv::Mat displayedFrame(cameraFrame.size(), cv::CV_8UC3);

	//Run the cartoonifier filter on the camera frame.
	cartoonifyImage(cameraFrame, displayedFrame);
	
	//Display the processed image onto the screen.
	imshow("Cartoonifier", displayedFrame);

	char keypress = cv::waitKey(20); //Need this to see anything!
	if(keypress == 27){
		break;
	}
}
