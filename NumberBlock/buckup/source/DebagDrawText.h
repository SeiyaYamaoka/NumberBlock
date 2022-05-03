#pragma once
#include<vector>
#include"Main.h"
#include<stdio.h>
#include<string>
#include<iostream>
class DebagDrawText {
public:
#define ddt DebagDrawText::getInstance()

	LPD3DXFONT lpFont;

	char buf[4096];
	RECT rect = { 0,0,50,50 };

	DebagDrawText();
	~DebagDrawText();

	void Draw();
	void SetChar(char ch[]);
	void SetChar(char ch[],int add);
	void SetChar(char ch[], UINT add);
	void SetChar(char ch[], DWORD add);
	void SetChar(char ch[], float add);
	void SetChar(char ch[], D3DXVECTOR3 add);
	void SetChar(char ch[], D3DXVECTOR3* add);
	void SetChar(char ch[], D3DXVECTOR4* add);
	void SetChar(char ch[], std::vector<int *>add);
	void SetChar(char ch[], std::string* add);
	void Bufferreset();

	static DebagDrawText &getInstance() {
		static DebagDrawText Instance;
		return Instance;
	}

};