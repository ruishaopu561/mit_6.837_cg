void cartoonifyImage(){
	Mat gray;
	cvtColor(srcColor,gray, CV_BGR2GRAY);
	const int MEDIAN_BLUE_FILTER_SIZE = 7;
	medianBlur(gray, gray, MEDIAN_BLUE_FILTER_SIZE);
	Mat edges;
	const int LAPLACIAN_FILTER_SIZE = 5;
	//Laplacian边缘滤波器，得到黑白效果
	Laplacian(gray, edges, CV_8U, LAPLACIAN_FILTER_SIZE);

	Mat mask;
	const int EDGES_THRESHOLD = 80;
	threshold(edges, mask, EDGES_THRESHOLD, 255, THRESH_BINARY_INV);}
