#pragma once
#include "GeoImg.h"

using namespace std;

class Params
{
private:
	GeoImg srcImg;
	GeoImg destImg;
	int maxClass;
	int noDataClass;
	int resolution;
public:
	Params();
	~Params();

	void setSrcImg(string path);
	string getSrcImgPath();
	void setDestImg(string path);
	string getDestImgPath();
	string getDestImgFolder();
	string getDestImgBase();
	string getDestImgExt();


	void setRes(double res);
	double getRes();

	void setMaxClass(int maxClass);
	int getMaxClass();

	void setNoDataClass(int maxClass);
	int getNoDataClass();

	void setDestWorld(int fromSrc = 1, int writeWorldFile = 1);

	double getSrcResX();
	double getSrcResY();
};

