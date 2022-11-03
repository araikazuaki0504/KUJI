#include "App.h" 

int Rand::Random()
{
	int tmp = 0;
	Sum = 0;
	for (int i = 0; i < _Con.size(); i++)
	{
		Sum += std::get<2>(_Con[i]);
	}

	if(Sum==0)return -1;

	tmp = rand() % Sum;

	Sum = 0;

	for (int i = 0; i < _Con.size(); i++)
	{
		if (std::get<2>(_Con[i]) <= 0)continue;
		Sum += std::get<2>(_Con[i]);
		if (Sum >= tmp)
		{
			std::get<2>(_Con[i]) -= 1;
			num = i;
			break;
		}
	}
	Ghandle = LoadGraph(std::get<1>(_Con[num]).c_str());
	return num;
}

void Rand::DrawImage(int tmp)
{
	

	DrawString(X + 10 , Y + 120, std::get<0>(_Con[tmp]).c_str(), Cr);

	/*--------------------画像描画----------------------*/
	//DrawExtendGraph(X, Y, X + 100, Y + 100, Ghandle, TRUE);
	/*--------------------------------------------------*/
}

void Rand::ImageDelete()
{
	DeleteGraph(Ghandle);
}

void Rand::Count()
{
	std::string str;
	for (int i = 0; i < _Con.size(); i++)
	{
		str = std::get<0>(_Con[i]) + ":" + std::to_string(std::get<2>(_Con[i])) + "個";
		DrawString(0, i * 15, str.c_str(), Cr_2);
		//wsprintf(tmp, TEXT("%d"), std::get<2>(_Con[i]));
		//DrawFormatString(0, i*15, Cr, "%s : %d 個", std::get<0>(_Con[i]), std::get<2>(_Con[i]));
	}
}

bool Rand::LoadDate()
{
	std::ifstream ifs(u8"loadDate.txt");
	std::string str, str_tmp_1, str_tmp_2, tmp;

	while (getline(ifs, str)) {

		tmp = str;
		str.erase(str.begin() + str.find(","), str.end());
		str_tmp_1 = str;
		str = tmp;
		str.erase(0, str.find(",") + 1);
		str.erase(str.begin() + str.find(","), str.end());
		str_tmp_2 = str;
		str = tmp;
		str.erase(str.begin(), str.begin() + str.rfind(",") + 1);
		_Con.push_back(std::make_tuple(str_tmp_1, str_tmp_2, stoi(str)));
	}

	return true;
}

bool Rand::SaveDate()
{
	std::ofstream writing_file;
	std::string filename = u8"loadDate.txt";
	writing_file.open(filename, std::ios::out);
	for (int i = 0; i < _Con.size(); i++)
	{
		std::string writing_text = std::get<0>(_Con[i]) + "," + std::get<1>(_Con[i]) + "," + std::to_string(std::get<2>(_Con[i]));
		if (i >= 0 && i < _Con.size() - 1)writing_file << writing_text << std::endl;
		else writing_file << writing_text;
	}

	writing_file.close();

	return true;
}