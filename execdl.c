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

#include <graphics/drawing.h>
#include <graphics/color.h>
#include <graphics/text.h>
#include <graphics/lcdc.h>
#include <sh4a/input/keypad.h>
#include "execdl.h"

static const wchar_t *execdl_wcschr(const wchar_t *s, wchar_t c)
{
    while (*s) {
        if (*s == c) {
            return s;
        }
        s++;
    }
    return NULL;
}

const unsigned char unknownfontdata[128] = {0x00, 0xC1, 0xC0, 0x00, 0x01, 0xC3, 0xC0, 0x00, 0x01, 0xE3, 0xC0, 0x00, 0x01, 0xE7, 0xE0, 0x00, 0x01, 0xFF, 0xE0, 0x00, 0x01, 0xFF, 0xE0, 0x00, 0x03, 0xFF, 0xE0, 0x00, 0x03, 0xFF, 0xE0, 0x00, 0x07, 0xFF, 0xE0, 0x00, 0x1F, 0xFF, 0xF0, 0x3C, 0x3F, 0xFF, 0xF0, 0x3E, 0x7F, 0xFF, 0xF0, 0x0E, 0xFF, 0xFF, 0xF0, 0x07, 0x3F, 0xFF, 0xE0, 0x07, 0x1F, 0xFF, 0xE0, 0x07, 0x07, 0xFF, 0xC0, 0x0E, 0x03, 0xFF, 0x9F, 0x3E, 0x00, 0xFF, 0xFF, 0xFC, 0x00, 0xFF, 0xFF, 0xF8, 0x00, 0xFF, 0xFF, 0xE0, 0x00, 0xFF, 0xFF, 0xE0, 0x00, 0xFF, 0xFF, 0xE0, 0x00, 0xFF, 0xFF, 0xE0, 0x00, 0xFF, 0xFF, 0xE0, 0x00, 0x7F, 0xFF, 0xC0, 0x00, 0x7F, 0xFF, 0xC0, 0x00, 0x3F, 0xFF, 0xC0, 0x00, 0x3F, 0x0F, 0xC0, 0x00, 0x3F, 0x0F, 0xC0, 0x00, 0x3F, 0x0F, 0xC0, 0x00, 0x3F, 0x0F, 0xC0, 0x00, 0x7F, 0x0F, 0xC0};

const unsigned char* execdl_getfontdata(wchar_t targ_char){
    const wchar_t* hit = execdl_wcschr(execdl_fontdataindex, targ_char);

    if(hit != NULL){
        int index = hit - execdl_fontdataindex;
        return execdl_fontdata[index];
    }

    return unknownfontdata;
}

void execdl_drawfont(const unsigned char* font_address, int basex, int basey, unsigned short color){
    if(font_address == NULL){
        return;
    }
    int byte_index = 0;
    for (int y = 0; y < 32; y++) {
        for (int b = 0; b < 4; b++) {
            unsigned char data = font_address[byte_index];
            byte_index++;

            // 1バイトの中の8つのビットをチェック
            for (int bit = 0; bit < 8; bit++) {
                // ビットが立っている（1）ならドットを描画
                if ((data & (0x80 >> bit)) != 0) {
                    int current_x = basex + (b * 8) + bit;
                    int current_y = basey + y;

                    set_pixel(current_x, current_y, color);
                }
            }
        }
    }
}

void execdl_drawtext(const wchar_t* text, int basex, int basey, unsigned short color){
    if(text == NULL){
        return;
    }
    for(int i = 0; text[i] != L'\0'; i++){
        const unsigned char* fontdataaddress = execdl_getfontdata(text[i]);
        if(fontdataaddress != NULL){
            execdl_drawfont(fontdataaddress, basex + (i * 32), basey, color);
        }
    }
}