#pragma once
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <string>
#include <tchar.h>
#include <malloc.h>
#include <tuple>
#include <fstream>
#include "DxLib.h"

class Rand {
private:
	std::vector<std::tuple<std::string, std::string, int>> _Con = {};
	int Sum = 0;
	int Ghandle = 0;
	const int X = 270;
	const int Y = 80;
	const unsigned int Cr = GetColor(0, 0, 0);
	const unsigned int Cr_2 = GetColor(255, 255, 255);
	int num = 0;
	TCHAR tmp[8] = "";

public:
	Rand() { srand(time(NULL)); };
	~Rand() {};
	int Random();
	void DrawImage(int tmp);
	void ImageDelete();
	void Count();
	bool LoadDate();
	bool SaveDate();
};
