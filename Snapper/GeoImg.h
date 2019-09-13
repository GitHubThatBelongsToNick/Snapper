#pragma once
#include <string>

using namespace std;

class GeoImg
{
private:
	string path;
	string baseName;
	string ext;
	double resX;
	double resY;
	//actual top left
	double topLeftX;
	double topLeftY;
	

public:
	GeoImg();
	~GeoImg();
	void setPath(string path, bool setSR);
	string getFilePath();
	string getFolder();
	string getBase();
	string getExt();


	void cloneResTL(GeoImg srcImg);
	double getTopLeftX();
	double getTopLeftY();
	double getResX();
	double getResY();

	void setTopLeftX(double loc);
	void setTopLeftY(double loc);
	void setResX(double res);
	void setResY(double res);

	int writeWorldFile();
	string getPrjFilePath();

	double getTop();
	double getLeft();
	double getBotom(int rows);
	double getRight(int cols);

private:
	string getWorldFilePath();

};

