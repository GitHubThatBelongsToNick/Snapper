#include <fstream>

#include "Params.h"



Params::Params()
{
}


Params::~Params()
{
}

void Params::setRes(double res)
{
	this->resolution = res;
}

double Params::getRes()
{
	return this->resolution;
}

void Params::setMaxClass(int maxClass)
{
	this->maxClass = maxClass;
}

int Params::getMaxClass()
{
	return this->maxClass;
}

void Params::setNoDataClass(int noDataClass)
{
	this->noDataClass = noDataClass;
}

int Params::getNoDataClass()
{
	return this->noDataClass;
}

void Params::setSrcImg(string path)
{
	srcImg.setPath(path, true);
}

void Params::setDestImg(string path)
{
	destImg.setPath(path, false);
}

string Params::getSrcImgPath()
{
	return this->srcImg.getFilePath();
}

string Params::getDestImgPath()
{
	return this->destImg.getFilePath();
}

string Params::getDestImgFolder()
{
	return this->destImg.getFolder();
}

string Params::getDestImgBase()
{
	return this->destImg.getBase();
}

string Params::getDestImgExt()
{
	return this->destImg.getExt();
}

double Params::getSrcResX()
{
	return this->srcImg.getResX();
}

double Params::getSrcResY()
{
	return this->srcImg.getResY();
}

void Params::setDestWorld(int fromSrc, int writeWorldFile)
{
	if (fromSrc)
		destImg.cloneResTL(srcImg);
	else
		; // Get Top Left coordinates from another image

	destImg.setResX(resolution);
	destImg.setResY(resolution);

	if (writeWorldFile)
	{
		destImg.writeWorldFile();

		// copy prj file if it exists.
		std::ifstream    srcPrjFile(srcImg.getPrjFilePath());
		std::ofstream    destPrjFile(destImg.getPrjFilePath());

		destPrjFile << srcPrjFile.rdbuf();
		srcPrjFile.close();
		destPrjFile.close();
	}

}


