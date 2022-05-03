#include "DebagDrawText.h"
DebagDrawText::DebagDrawText() {
	D3DXCreateFont(cdg.lpD3DDevice, 0, 10, 500, 1, FALSE, SHIFTJIS_CHARSET, 0, 0, 0, NULL, &lpFont);
	lpFont->OnResetDevice();
}
DebagDrawText::~DebagDrawText() {
	lpFont->Release();
}

void DebagDrawText::Draw() {
	lpFont->DrawText(NULL,	//�X�v���C�g�̃|�C���^
		buf,	//������̐擪�A�h���X
		-1,		//�`�敶����
		&rect,	//�`��̈�
		DT_LEFT | DT_NOCLIP,					//�E������
		D3DCOLOR_ARGB(255, 255, 0, 0));	//�F
	
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