#include"FileOperation.h"
void FileOperation::Split(std::vector<std::string> & _out, std::string _str, std::string _split)
{
	_out.clear();
	int cp = std::string::npos;
	while ((cp = _str.find(_split)) != std::string::npos)
	{
		if (cp>0) { _out.push_back(_str.substr(0, cp)); }
		_str = _str.substr(cp + _split.length());
	}
	if (_str.length()>0) { _out.push_back(_str); }
}
int FileOperation::ReadScore() {
	int score = 10;
	std::ifstream fin("Data/score.txt");
	if (!fin)
		return 1;
	char s;
	fin >> score;
	fin.close();
	//core = std::stof(strstream);
	return score;
}
void FileOperation::WriteScore(int score) {
	std::ofstream ofs("Data/score.txt", std::ios::out);
	
	ofs << score;
	
	ofs.close();
}
std::vector<Mesh *>FileOperation::ReadFile(std::vector<Mesh *> meshinf) {
	std::ifstream ifs("Data/4.txt");
	std::string line;
	std::vector<std::string> sp;
	std::vector<std::string> state;
	std::vector<std::string> value;
	int i = 0;
	//  b1.x / P = 0,0,0 / S = 1,1,1 / R = 0,0,0 
	//  b1.x/ P = 0,0,0 ~ 10,0,0 /2, 
	while (std::getline(ifs, line)) {
		if (ifs.fail()) { break; }
		Split(sp, line, "/");
		if (sp[0] == "")continue;
		Mesh *lpm = new Mesh();
		lpm->mname = sp[0];
		lpm->Init();
		for (int i = 1; i < sp.size(); i++) {
			Split(state, sp[i], "=");
			if (state[0] == "p") {
				Split(value, state[1], ",");
				lpm->SetPos(std::stof(value[0]), std::stof(value[1]), std::stof(value[2]));
			}
			if (state[0] == "r") {
				Split(value, state[1], ",");
				lpm->SetRot(std::stof(value[0]), std::stof(value[1]), std::stof(value[2]));
			}
			if (state[0] == "s") {
				Split(value, state[1], ",");
				lpm->SetScale(std::stof(value[0]), std::stof(value[1]), std::stof(value[2]));
			}
		}
		lpm->Update();
		if (!lpm) { break; }
		meshinf.push_back(lpm);
	}
	ifs.close();
	return meshinf;
}
void FileOperation::WriteFile(std::vector<D3DXVECTOR3> _data) {
	std::ofstream ofs("Data/2.txt", std::ios::out);
	for (int i = 0; i < _data.size(); i++) {
		ofs << _data[i].x << "," << _data[i].y << "," << _data[i].z << "," << std::endl;
	}
	ofs.close();
}
void FileOperation::AppWriteFile(float x, float y, float z) {
	std::ofstream ofs("Data/2.txt", std::ios::app);
	ofs << x << "," << y << "," << z << "," << std::endl;
	ofs.close();
}
void FileOperation::TruncWriteFile() {
	std::ofstream ofs("Data/2.txt", std::ios::trunc);
	ofs.close();
}