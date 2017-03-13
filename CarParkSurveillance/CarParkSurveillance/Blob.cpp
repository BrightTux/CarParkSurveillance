// Blob.cpp

#include "Blob.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
Blob::Blob(std::vector<cv::Point> _contour) {
	


	addornot = false;
	currentContour = _contour;

	currentBoundingRect = cv::boundingRect(currentContour);



	cv::Point currentCenter;

	currentCenter.x = (currentBoundingRect.x + currentBoundingRect.x + currentBoundingRect.width) / 2;
	currentCenter.y = (currentBoundingRect.y + currentBoundingRect.y + currentBoundingRect.height) / 2;

	centerPositions.push_back(currentCenter);

	dblCurrentDiagonalSize = sqrt(pow(currentBoundingRect.width, 2) + pow(currentBoundingRect.height, 2));

	dblCurrentAspectRatio = (float)currentBoundingRect.width / (float)currentBoundingRect.height;

	blnStillBeingTracked = true;
	blnCurrentMatchFoundOrNewBlob = true;

	////test
	isAdded = true;
	////

	intNumOfConsecutiveFramesWithoutAMatch = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
void Blob::predictNextPosition(void) {

	int numPositions = (int)centerPositions.size();

	if (numPositions == 1) {

		predictedNextPosition.x = centerPositions.back().x;
		predictedNextPosition.y = centerPositions.back().y;

	}
	
	else if (numPositions == 2) {

		int deltaX = centerPositions[1].x - centerPositions[0].x;
		int deltaY = centerPositions[1].y - centerPositions[0].y;

		predictedNextPosition.x = centerPositions.back().x + deltaX;
		predictedNextPosition.y = centerPositions.back().y + deltaY;

	}
	else if (numPositions == 3) {

		int sumOfXChanges = ((centerPositions[2].x - centerPositions[1].x) * 2) +
			((centerPositions[1].x - centerPositions[0].x) * 1);

		int deltaX = (int)std::round((float)sumOfXChanges / 3.0);

		int sumOfYChanges = ((centerPositions[2].y - centerPositions[1].y) * 2) +
			((centerPositions[1].y - centerPositions[0].y) * 1);

		int deltaY = (int)std::round((float)sumOfYChanges / 3.0);

		predictedNextPosition.x = centerPositions.back().x + deltaX;
		predictedNextPosition.y = centerPositions.back().y + deltaY;

	}
	else if (numPositions == 4) {

		int sumOfXChanges = ((centerPositions[3].x - centerPositions[2].x) * 3) +
			((centerPositions[2].x - centerPositions[1].x) * 2) +
			((centerPositions[1].x - centerPositions[0].x) * 1);

		int deltaX = (int)std::round((float)sumOfXChanges / 6.0);

		int sumOfYChanges = ((centerPositions[3].y - centerPositions[2].y) * 3) +
			((centerPositions[2].y - centerPositions[1].y) * 2) +
			((centerPositions[1].y - centerPositions[0].y) * 1);

		int deltaY = (int)std::round((float)sumOfYChanges / 6.0);

		predictedNextPosition.x = centerPositions.back().x + deltaX;
		predictedNextPosition.y = centerPositions.back().y + deltaY;

	}
	else if (numPositions == 5) {



		int sumOfXChanges = ((centerPositions[4].x - centerPositions[3].x) * 4) +
			((centerPositions[3].x - centerPositions[2].x) * 3) +
			((centerPositions[2].x - centerPositions[1].x) * 2) +
			((centerPositions[1].x - centerPositions[0].x) * 1);

		int deltaX = (int)std::round((float)sumOfXChanges / 10.0);

		int sumOfYChanges = ((centerPositions[4].y - centerPositions[3].y) * 4) +
			((centerPositions[3].y - centerPositions[2].y) * 3) +
			((centerPositions[2].y - centerPositions[1].y) * 2) +
			((centerPositions[1].y - centerPositions[0].y) * 1);

		int deltaY = (int)std::round((float)sumOfYChanges / 10.0);

		predictedNextPosition.x = centerPositions.back().x + deltaX;
		predictedNextPosition.y = centerPositions.back().y + deltaY;

	}
	else if (numPositions == 6) {
		int sumOfXChanges = ((centerPositions[5].x - centerPositions[4].x) * 5) +
			((centerPositions[4].x - centerPositions[3].x) * 4) +
			((centerPositions[3].x - centerPositions[2].x) * 3) +
			((centerPositions[2].x - centerPositions[1].x) * 2) +
			((centerPositions[1].x - centerPositions[0].x) * 1);

		int deltaX = (int)std::round((float)sumOfXChanges / 15.0);

		int sumOfYChanges = ((centerPositions[5].y - centerPositions[4].y) * 5) +
			((centerPositions[4].y - centerPositions[3].y) * 4) +
			((centerPositions[3].y - centerPositions[2].y) * 3) +
			((centerPositions[2].y - centerPositions[1].y) * 2) +
			((centerPositions[1].y - centerPositions[0].y) * 1);

		int deltaY = (int)std::round((float)sumOfYChanges / 15.0);

		predictedNextPosition.x = centerPositions.back().x + deltaX;
		predictedNextPosition.y = centerPositions.back().y + deltaY;
	}
	else if (numPositions == 7) {
		int sumOfXChanges = ((centerPositions[6].x - centerPositions[5].x) * 6) +
			((centerPositions[5].x - centerPositions[4].x) * 5) +
			((centerPositions[4].x - centerPositions[3].x) * 4) +
			((centerPositions[3].x - centerPositions[2].x) * 3) +
			((centerPositions[2].x - centerPositions[1].x) * 2) +
			((centerPositions[1].x - centerPositions[0].x) * 1);

		int deltaX = (int)std::round((float)sumOfXChanges / 21.0);

		int sumOfYChanges = ((centerPositions[6].y - centerPositions[5].y) * 6) +
			((centerPositions[5].y - centerPositions[4].y) * 5) +
			((centerPositions[4].y - centerPositions[3].y) * 4) +
			((centerPositions[3].y - centerPositions[2].y) * 3) +
			((centerPositions[2].y - centerPositions[1].y) * 2) +
			((centerPositions[1].y - centerPositions[0].y) * 1);

		int deltaY = (int)std::round((float)sumOfYChanges / 21.0);

		predictedNextPosition.x = centerPositions.back().x + deltaX;
		predictedNextPosition.y = centerPositions.back().y + deltaY;
	}

	else if (numPositions == 8) {
		int sumOfXChanges = ((centerPositions[7].x - centerPositions[6].x) * 7) +
			((centerPositions[6].x - centerPositions[5].x) * 6) +
			((centerPositions[5].x - centerPositions[4].x) * 5) +
			((centerPositions[4].x - centerPositions[3].x) * 4) +
			((centerPositions[3].x - centerPositions[2].x) * 3) +
			((centerPositions[2].x - centerPositions[1].x) * 2) +
			((centerPositions[1].x - centerPositions[0].x) * 1);

		int deltaX = (int)std::round((float)sumOfXChanges / 28.0);

		int sumOfYChanges = ((centerPositions[7].y - centerPositions[6].y) * 7) +
			((centerPositions[6].y - centerPositions[5].y) * 6) +
			((centerPositions[5].y - centerPositions[4].y) * 5) +
			((centerPositions[4].y - centerPositions[3].y) * 4) +
			((centerPositions[3].y - centerPositions[2].y) * 3) +
			((centerPositions[2].y - centerPositions[1].y) * 2) +
			((centerPositions[1].y - centerPositions[0].y) * 1);

		int deltaY = (int)std::round((float)sumOfYChanges / 28.0);

		predictedNextPosition.x = centerPositions.back().x + deltaX;
		predictedNextPosition.y = centerPositions.back().y + deltaY;
	}

	else if (numPositions == 9) {
		int sumOfXChanges = ((centerPositions[8].x - centerPositions[7].x) * 8) +
			((centerPositions[7].x - centerPositions[6].x) * 7) +
			((centerPositions[6].x - centerPositions[5].x) * 6) +
			((centerPositions[5].x - centerPositions[4].x) * 5) +
			((centerPositions[4].x - centerPositions[3].x) * 4) +
			((centerPositions[3].x - centerPositions[2].x) * 3) +
			((centerPositions[2].x - centerPositions[1].x) * 2) +
			((centerPositions[1].x - centerPositions[0].x) * 1);

		int deltaX = (int)std::round((float)sumOfXChanges / 36.0);

		int sumOfYChanges = ((centerPositions[8].y - centerPositions[7].y) * 8) +
			((centerPositions[7].y - centerPositions[6].y) * 7) +
			((centerPositions[6].y - centerPositions[5].y) * 6) +
			((centerPositions[5].y - centerPositions[4].y) * 5) +
			((centerPositions[4].y - centerPositions[3].y) * 4) +
			((centerPositions[3].y - centerPositions[2].y) * 3) +
			((centerPositions[2].y - centerPositions[1].y) * 2) +
			((centerPositions[1].y - centerPositions[0].y) * 1);

		int deltaY = (int)std::round((float)sumOfYChanges / 36.0);

		predictedNextPosition.x = centerPositions.back().x + deltaX;
		predictedNextPosition.y = centerPositions.back().y + deltaY;
	}
	else if (numPositions >= 10) {
		int sumOfXChanges = ((centerPositions[numPositions - 1].x - centerPositions[numPositions - 2].x) * 9) +
			((centerPositions[numPositions - 2].x - centerPositions[numPositions - 3].x) * 8) +
			((centerPositions[numPositions - 3].x - centerPositions[numPositions - 4].x) * 7) +
			((centerPositions[numPositions - 4].x - centerPositions[numPositions - 5].x) * 6) +
			((centerPositions[numPositions - 5].x - centerPositions[numPositions - 6].x) * 5) +
			((centerPositions[numPositions - 6].x - centerPositions[numPositions - 7].x) * 4) +
			((centerPositions[numPositions - 7].x - centerPositions[numPositions - 8].x) * 3) +
			((centerPositions[numPositions - 8].x - centerPositions[numPositions - 9].x) * 2) +
			((centerPositions[numPositions - 9].x - centerPositions[numPositions - 10].x) * 1);

		int deltaX = (int)std::round((float)sumOfXChanges / 45.0);

		int sumOfYChanges = ((centerPositions[numPositions - 1].y - centerPositions[numPositions - 2].y) * 9) +
			((centerPositions[numPositions - 2].y - centerPositions[numPositions - 3].y) * 8) +
			((centerPositions[numPositions - 3].y - centerPositions[numPositions - 4].y) * 7) +
			((centerPositions[numPositions - 4].y - centerPositions[numPositions - 5].y) * 6) +
			((centerPositions[numPositions - 5].y - centerPositions[numPositions - 6].y) * 5) +
			((centerPositions[numPositions - 6].y - centerPositions[numPositions - 7].y) * 4) +
			((centerPositions[numPositions - 7].y - centerPositions[numPositions - 8].y) * 3) +
			((centerPositions[numPositions - 8].y - centerPositions[numPositions - 9].y) * 2) +
			((centerPositions[numPositions - 9].y - centerPositions[numPositions - 10].y) * 1);

		int deltaY = (int)std::round((float)sumOfYChanges / 45.0);

		predictedNextPosition.x = centerPositions.back().x + deltaX;
		predictedNextPosition.y = centerPositions.back().y + deltaY;
	}

}

void Blob::predictNextPositionPark(void) {
	predictedNextPosition.x = centerPositions.back().x;
	predictedNextPosition.y = centerPositions.back().y;
}
void Blob::storeImage(cv::Mat rawImage) {
	this->rawImage = rawImage.clone();

	image = cv::Mat(rawImage.size(), CV_8U, cv::Scalar(0.0, 0.0, 0.0));

	std::vector<std::vector<cv::Point> > contourVec;
	contourVec.push_back(currentContour);
	cv::drawContours(image, contourVec, -1, cv::Scalar(255.0, 255.0, 255.0), -1);

	cv::Mat colorForegrounds = cv::Mat::zeros(image.size(), image.type());
	rawImage.copyTo(colorForegrounds, image);
	cv::cvtColor(colorForegrounds, colorForegrounds, CV_BGR2GRAY);
	maskImage = colorForegrounds.clone();

	//useORBGPU();
	//getFeatures();
	//desFeatures();
    //drawMaskImage(rawImage, image);
	//getAverageColor(rawImage, image);
}

void Blob::getAverageColor() {
	cv::Scalar average = cv::mean(rawImage, image);
	AvgColor.push_back(average);
}	

void Blob::getAverageColorLast() {
	avgColorBeforeMerge = cv::mean(rawImage, image);
}


void Blob::drawMaskImage() {

	cv::Mat image(rawImage.size(), CV_8UC3, cv::Scalar(0.0, 0.0, 0.0));

	std::vector<std::vector<cv::Point> > contourVec;
	contourVec.push_back(currentContour);
	cv::drawContours(image, contourVec, -1, cv::Scalar(255.0, 255.0, 255.0), -1);


	cv::Mat colorForegrounds = cv::Mat::zeros(image.size(), image.type());
	rawImage.copyTo(colorForegrounds, image);


	cv::imshow("cut", colorForegrounds);
}

void Blob::getFeatures() {

	cv::Mat image(rawImage.size(), CV_8UC3, cv::Scalar(0.0, 0.0, 0.0));

	std::vector<std::vector<cv::Point> > contourVec;
	contourVec.push_back(currentContour);
	cv::drawContours(image, contourVec, -1, cv::Scalar(255.0, 255.0, 255.0), -1);


	cv::Mat colorForegrounds = cv::Mat::zeros(image.size(), image.type());
	rawImage.copyTo(colorForegrounds, image);

	cv::cvtColor(colorForegrounds, colorForegrounds, CV_BGR2GRAY);




	cv::gpu::GpuMat colourForegroundGPU(colorForegrounds);

	cv::gpu::FAST_GPU::FAST_GPU(15).operator() (colourForegroundGPU, colourForegroundGPU, keypoints_new);


	for (it = keypoints_new.begin(); it != keypoints_new.end(); it++) {
		points.push_back(it->pt);
	}




	cv::drawKeypoints(colorForegrounds, keypoints_new, colorForegrounds);
	//cv::imshow("sds", colorForegrounds);

	//std::cout << "get features done\n";






}

cv::gpu::GpuMat Blob::getGpuImage() {

	cv::Mat image(rawImage.size(), CV_8UC3, cv::Scalar(0.0, 0.0, 0.0));

	std::vector<std::vector<cv::Point> > contourVec;
	contourVec.push_back(currentContour);
	cv::drawContours(image, contourVec, -1, cv::Scalar(255.0, 255.0, 255.0), -1);


	cv::Mat colorForegrounds = cv::Mat::zeros(image.size(), image.type());
	rawImage.copyTo(colorForegrounds, image);

	cv::cvtColor(colorForegrounds, colorForegrounds, CV_BGR2GRAY);
	cv::gpu::GpuMat colourForegroundGPU(colorForegrounds);

	//std::cout << "get GPU done\n";

	return colourForegroundGPU;
}

void Blob::desFeatures() {
	cv::gpu::ORB_GPU descriptorGPU;

	descriptorGPU.operator() (getGpuImage(), getGpuImage(), keypoints_new, des);

	//std::cout << "get des done\n";

	/*cv::SurfDescriptorExtractor extractor;

	extractor.compute(rawImage, keypoints_new, desNoGpu);
	std::cout << "des " << desNoGpu.size() << " " << desNoGpu.type() << "\n";*/

}

cv::Mat Blob::getDes() {
	if (!des.empty())
		des.download(desNoGpu);

	//std::cout << desNoGpu.size() << " " << desNoGpu.type() <<"\n";
	//	std::cout << "got it\n";


	return desNoGpu;

	//std::cout << "got it\n";
}

cv::gpu::GpuMat Blob::getGpuDes() {

	return des;
}

cv::Mat Blob::getRawImage() {
	return rawImage;
}

void Blob::useORBGPU() {
	cv::gpu::ORB_GPU orb(1000);


	cv::Mat image(rawImage.size(), CV_8UC3, cv::Scalar(0.0, 0.0, 0.0));

	std::vector<std::vector<cv::Point> > contourVec;
	contourVec.push_back(currentContour);
	cv::drawContours(image, contourVec, -1, cv::Scalar(255.0, 255.0, 255.0), -1);


	cv::Mat colorForegrounds = cv::Mat::zeros(image.size(), image.type());
	rawImage.copyTo(colorForegrounds, image);

	cv::cvtColor(colorForegrounds, colorForegrounds, CV_BGR2GRAY);




	cv::gpu::GpuMat colourForegroundGPU(colorForegrounds);

	orb(colourForegroundGPU, cv::gpu::GpuMat(), keypoints_new, des);




}

cv::Scalar Blob::getAverageColorOnce() {
	cv::Scalar average = cv::mean(rawImage, image);
	return average;
}

void Blob::setEnter() {
	enter = true;
}

void Blob::setExit(){
	exit = true;
}

void Blob::setPark() {
	park = true;

}



