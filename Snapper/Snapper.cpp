//opencv includes
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"

//c++ includes
#include <stdlib.h>
#include <stdio.h>

#include "GeoImg.h"
#include "Params.h"

#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
	Mat mHyperSpacialBdr;
	Mat mHyperSpacialSrc;
	Mat mHyperSpacialDisplay;
	Mat mMediumResoulution;
	   	
	GeoImg gMediumResolutionInfo;
	GeoImg gHyperSpacialInfo;

	gHyperSpacialInfo.setPath("C:\\Work\\Spacial\\Imagery\\Hoodoo\\HoodooOrtho\\Hoodoo 6-1-17.tif", true);
	gMediumResolutionInfo.setPath("C:\\Work\\Spacial\\Imagery\\Hoodoo\\HoodoLandSat_Reproj2.tif", true);

	gHyperSpacialInfo.writeWorldFile();
	gMediumResolutionInfo.writeWorldFile();

	double topHigh, bottomHigh, leftHigh, rightHigh;
	double topMed, bottomMed, leftMed, rightMed;
	double topDiff, bottomDiff, leftDiff, rightDiff;

	double topPxls, bottomPxls, leftPxls, rightPxls;

		
	int borderType = BORDER_CONSTANT;
	Scalar value;
	const char* window_name = "Snap drone to Landsat";
	RNG rng(12345);

	int listener;

	//load drone imagery
	mMediumResoulution = imread(argv[2], IMREAD_COLOR);// Read the file

	// Make sure image loaded
	if (!mMediumResoulution.data)
	{
		return -1;
		printf(" No data entered for hyperspacial , please enter the path to an image file \n");
	}


	//load LandSat imagery
	mHyperSpacialSrc = imread(argv[1], IMREAD_COLOR);// Read the file

	// Make sure image loaded
	if (!mHyperSpacialSrc.data)
	{
		return -1;
		printf(" No data entered for LandSat , please enter the path to an image file \n");
	}


	// create window without border
	namedWindow(window_name, WINDOW_AUTOSIZE);
	//imshow(window_name, mHyperSpacialSrc);
	//waitKey(0); // Wait for a keystroke in the window

	// add borders
	topHigh = gHyperSpacialInfo.getTop();
	leftHigh = gHyperSpacialInfo.getLeft();
	bottomHigh = gHyperSpacialInfo.getBotom(mHyperSpacialSrc.rows);
	rightHigh = gHyperSpacialInfo.getRight(mHyperSpacialSrc.cols);

	topMed = gMediumResolutionInfo.getTop();
	leftMed = gMediumResolutionInfo.getLeft();
	bottomMed = gMediumResolutionInfo.getBotom(mMediumResoulution.rows);
	rightMed = gMediumResolutionInfo.getRight(mMediumResoulution.cols);

	topDiff = topMed - topHigh;
	bottomDiff = bottomHigh - bottomMed;
	leftDiff = leftHigh - leftMed;
	rightDiff = rightMed - rightHigh;

	double resX = gHyperSpacialInfo.getResX();
	double resY = gHyperSpacialInfo.getResY();

	topPxls = topDiff / resY;
	bottomPxls = bottomDiff / resY;
	leftPxls = leftDiff / resX;
	rightPxls = rightDiff / resX;


	mHyperSpacialBdr = mHyperSpacialSrc;

	borderType = BORDER_CONSTANT;
	value = NULL;
	copyMakeBorder(mHyperSpacialSrc, mHyperSpacialBdr, topPxls, bottomPxls, leftPxls, rightPxls, borderType, value);

	//save image
	try {
		imwrite("C:\\Work\\Spacial\\Imagery\\Hoodoo\\OrthoBrdr.tif", mHyperSpacialBdr);

	}
	catch (runtime_error& ex) {
		fprintf(stderr, "Exception converting image to TIFF format: %s\n", ex.what());
		return 1;
	}

	//create Spatial Reference for Boarder image
	GeoImg gBoarderInfo;
	gBoarderInfo.setPath("C:\\Work\\Spacial\\Imagery\\Hoodoo\\OrthoBrdr.tif", false);

	gBoarderInfo.setTopLeftX(gMediumResolutionInfo.getTopLeftX());
	gBoarderInfo.setTopLeftY(gMediumResolutionInfo.getTopLeftY());
	gBoarderInfo.setResX(gHyperSpacialInfo.getResX());
	gBoarderInfo.setResY(gHyperSpacialInfo.getResY());

	gBoarderInfo.writeWorldFile();

	//display image
	mHyperSpacialDisplay = mHyperSpacialBdr;
	resize(mHyperSpacialDisplay, mHyperSpacialDisplay, Size(mHyperSpacialDisplay.cols / 32, mHyperSpacialDisplay.rows / 32)); // to half size or even smaller

	imshow(window_name, mHyperSpacialDisplay);
	//imshow(window_name, mHyperSpacial);


	listener = waitKey(0);
	return 0;
}
