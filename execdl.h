//Copyright (C) 2026 kwmsnode
//
//  This program is free software:
//  you can redistribute it and/or modify
//  it under the terms of the GNU General Public License.
// EX Extended Character Display Library
// EX拡張文字表示ライブラリ
// 非公式開発環境の文字表示機能を拡張。
// アルファ0.1バージョン。GPL、保証なし。
// kwmsnodeが作成。

#ifndef EXECDL_H
#define EXECDL_H

#include <stddef.h>

extern const wchar_t* execdl_fontdataindex;
extern const unsigned char execdl_fontdata[][128];

const unsigned char* execdl_getfontdata(wchar_t targ_char);
void execdl_drawfont(const unsigned char* font_address, int basex, int basey, unsigned short color);
void execdl_drawtext(const wchar_t* text, int basex, int basey, unsigned short color);

#endif