#include "DebagDrawText.h"
DebagDrawText::DebagDrawText() {
	D3DXCreateFont(cdg.lpD3DDevice, 0, 10, 500, 1, FALSE, SHIFTJIS_CHARSET, 0, 0, 0, NULL, &lpFont);
	lpFont->OnResetDevice();
}
DebagDrawText::~DebagDrawText() {
	lpFont->Release();
}

void DebagDrawText::Draw() {
	lpFont->DrawText(NULL,	//スプライトのポインタ
		buf,	//文字列の先頭アドレス
		-1,		//描画文字数
		&rect,	//描画領域
		DT_LEFT | DT_NOCLIP,					//右揃え等
		D3DCOLOR_ARGB(255, 255, 0, 0));	//色
	
}
void DebagDrawText::SetChar(char ch[]) {
	char kbuf[256];
	sprintf_s(kbuf, sizeof(kbuf), ch);
	strcat_s(buf, kbuf);
}
void DebagDrawText::SetChar(char ch[],int add) {
	char kbuf[256];
	sprintf_s(kbuf, sizeof(kbuf), ch,add);
	strcat_s(buf, kbuf);
}
void DebagDrawText::SetChar(char ch[], DWORD add) {
	char kbuf[256];
	sprintf_s(kbuf, sizeof(kbuf), ch, add);
	strcat_s(buf, kbuf);
}
void DebagDrawText::SetChar(char ch[], float add) {
	char kbuf[256];
	sprintf_s(kbuf, sizeof(kbuf), ch, add);
	strcat_s(buf, kbuf);
}
void DebagDrawText::SetChar(char ch[], D3DXVECTOR3 add) {
	char kbuf[256];
	sprintf_s(kbuf, sizeof(kbuf), ch, add.x,add.y,add.z);
	strcat_s(buf, kbuf);
}
void DebagDrawText::SetChar(char ch[], D3DXVECTOR3* add) {
	char kbuf[256];
	sprintf_s(kbuf, sizeof(kbuf), ch, add->x, add->y, add->z);
	strcat_s(buf, kbuf);
}
void DebagDrawText::SetChar(char ch[], D3DXVECTOR4* add) {
	char kbuf[256];
	sprintf_s(kbuf, sizeof(kbuf), ch, add->x, add->y, add->z,add->w);
	strcat_s(buf, kbuf);
}
void DebagDrawText::SetChar(char ch[], std::vector<int *> add)
{
	char kbuf[256];
	sprintf_s(kbuf, sizeof(kbuf), ch, add);
	strcat_s(buf, kbuf);
}
void DebagDrawText::SetChar(char ch[], std::string* add) {
	char kbuf[256];
	sprintf_s(kbuf, sizeof(kbuf), ch, add);
	strcat_s(buf, kbuf);
}
void DebagDrawText::SetChar(char ch[], UINT add) {
	char kbuf[256];
	sprintf_s(kbuf, sizeof(kbuf), ch, add);
	strcat_s(buf, kbuf);
}
void DebagDrawText::Bufferreset() {
	for (int i = 0; i < 256; i++) {
		buf[i] = '\0';
	}
}