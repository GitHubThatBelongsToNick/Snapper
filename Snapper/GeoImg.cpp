#include <iostream>
#include <fstream>
#include <string>

#include "GeoImg.h"

GeoImg::GeoImg()
{
}

GeoImg::~GeoImg()
{
}


void GeoImg::setPath(string path, bool setSR)
{
	//parse out path variable
	this->path = path.substr(0, path.find_last_of("\\"));
	if (path.find_last_of(".") != string::npos)
	{
		ext = path.substr(path.find_last_of(".") + 1);
		baseName = path.substr(path.find_last_of("\\") + 1,
			path.find_last_of(".") - path.find_last_of("\\") - 1);

	}
	else
		baseName = path.substr(path.find_last_of("\\")+1 , 
			       path.find_last_of(".")- path.find_last_of("\\")-1);

	//populate member variables
	if (setSR)
	{
		string worldExt;
		ifstream file;
		if (ext == "tif")
			worldExt = "tfw";
		string fname = this->path + "\\" + baseName + "." + worldExt;

		file.open(this->path + "\\" + baseName + "." + worldExt);
		if (file)
		{
			string num;
			file >> num;
			resX = stod(num);
			file >> num;
			file >> num;
			file >> num;
			resY = stod(num)*-1.0;
			file >> num;
			topLeftX = stod(num)-(resX/2.0);
			file >> num;
			topLeftY = stod(num)+(resY/2.0);
			file.close();

		}
		else
		{
			cout << "ERROR: unable to open world file." << endl;
		}
	}
	int i = 0;

}

string GeoImg::getFilePath()
{
	return this->path + "\\" + this->baseName + "." + this->ext;
}

string GeoImg::getFolder()
{
	return this->path;
}

string GeoImg::getBase()
{
	return this->baseName;
}

string GeoImg::getExt()
{
	return this->ext;
}

string GeoImg::getPrjFilePath()
{
	return this->path + "\\" + this->baseName + ".prj";
}

double GeoImg::getTop()
{
	return topLeftY;
}

double GeoImg::getLeft()
{
	return topLeftX;
}

double GeoImg::getBotom(int rows)
{
	double top = getTop();
	double botom = top - rows * this->resY;

	return botom;
}

double GeoImg::getRight(int cols)
{
	double left = getLeft();
	double right = left + cols * this->resX;

	return right;
}

//double GeoImg::getRight(int cols)
//{
//	double left = getLeft();
//	double right = left - cols * getResX();
//
//	return right;
//}

string GeoImg::getWorldFilePath()
{
	string worldExt;
	if (ext == "tif")
		worldExt = "tfw";
	else if (ext.empty())
		worldExt = "tfw";
	else
		cout << "ERROR: image format not tif" << endl;

	return this->path + "\\" + this->baseName + "." + worldExt;

}

double GeoImg::getTopLeftX()
{
	return this->topLeftX;
}

double GeoImg::getTopLeftY()
{
	return this->topLeftY;
}

double GeoImg::getResX()
{
	return this->resX;
}

double GeoImg::getResY()
{
	return this->resY;
}

int GeoImg::writeWorldFile()
{
	// open world file
	ofstream worldFile;
	string tfwPath = this->getWorldFilePath();

	worldFile.open(this->getWorldFilePath());
	// write settings
	worldFile << to_string(this->getResX()) << endl;
	worldFile << "0" << endl<< "0"<< endl;
	worldFile << to_string(this->getResY()*-1.0) << endl;
	

	double tlX = topLeftX - (resX / 2.0);
	double tlY = topLeftY - (resY / 2.0);
	worldFile << to_string(topLeftX + (resX / 2.0)) << endl;
	worldFile << to_string(topLeftY - (resY / 2.0)) << endl;
	worldFile.close();

	return 1;

}

void GeoImg::cloneResTL(GeoImg srcImg)
{
	this->resX = srcImg.resX;
	this->resY = srcImg.resY;
	this->topLeftX = srcImg.topLeftX;
	this->topLeftY = srcImg.topLeftY;
}

void GeoImg::setTopLeftX(double loc)
{
	this->topLeftX = loc;
}

void GeoImg::setTopLeftY(double loc)
{
	this->topLeftY = loc;
}

void GeoImg::setResX(double res)
{
	this->resX = res;
}

void GeoImg::setResY(double res)
{
	this->resY = res;
}