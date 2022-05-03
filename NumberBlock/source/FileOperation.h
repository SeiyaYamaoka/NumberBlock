#pragma once
#include"Main.h"
#include"Mesh.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include<vector>
class FileOperation {
public:
	// 簡単にアクセスできるようにするためのマクロ
#define fop FileOperation::getInstance()
	FileOperation() {};
	~FileOperation() {};

	void Split(std::vector<std::string> & _out, std::string _str, std::string _split);
	std::vector<Mesh *> ReadFile(std::vector<Mesh *> meshinf);
	void WriteFile(std::vector<D3DXVECTOR3> _data);
	void AppWriteFile(float, float, float);
	void TruncWriteFile();
	int ReadScore();
	void WriteScore(int score);
	static FileOperation &getInstance() {
		static FileOperation Instance;
		return Instance;
	}
};