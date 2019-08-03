
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

camera.set(cv::CV_CAP_PROP_FRAME_WIDTH,640);
camera.set(cv::CV_CAP_PROP)
