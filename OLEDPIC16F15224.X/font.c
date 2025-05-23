/*
 * File:   font.c
 * Author: armag
 *
 * Created on May 22, 2025, 7:55 PM
 */
#include "font.h"

// Basit 5x7 Font (ASCII 32-126)
// Her karakter 5 byte (5 kolon)
// Font verisi: http:// B�rgermeister.de/wp-content/uploads/2014/01/font5x7.h sitesinden al?nabilir
// veya basit bir tane olu?turulabilir. Bu �rnekte sadece 'H' ve 'i' harfleri i�in basit bir g�sterim:
// Daha tam bir font seti kullanman?z gerekecektir.
const uint8_t basicFont_5x7[] = {
    // Bo?luk ' ' (ASCII 32)
    0x00, 0x00, 0x00, 0x00, 0x00,
    // �nlem '!'
    0x00, 0x00, 0x5F, 0x00, 0x00,
    // ... Di?er karakterler ...
    // �rnek olarak 'H' (ASCII 72)
    // Varsayal?m ki 'H' fontun (72-32) = 40. karakteri
    // ... (39 karakter * 5 byte) ...
    0x7F, 0x08, 0x08, 0x08, 0x7F, // H
    // �rnek olarak 'e' (ASCII 101)
    // ...
    0x3E, 0x4A, 0x4A, 0x4A, 0x32, // e (yakla??k)
    // �rnek olarak 'l' (ASCII 108)
    0x00, 0x41, 0x7F, 0x40, 0x00, // l
    // �rnek olarak 'o' (ASCII 111)
    0x3E, 0x41, 0x41, 0x41, 0x3E, // o
    // �rnek olarak 'P' (ASCII 80)
    0x7F, 0x09, 0x09, 0x09, 0x06, // P
    // �rnek olarak 'I' (ASCII 73) -> 'i' ile kar??mamas? i�in b�y�k I
    0x00, 0x00, 0x7F, 0x00, 0x00, // I
    // �rnek olarak 'C' (ASCII 67)
    0x3E, 0x41, 0x41, 0x41, 0x22, // C
    // �rnek olarak '1' (ASCII 49)
    0x00, 0x42, 0x7F, 0x40, 0x00, // 1
    // �rnek olarak '6' (ASCII 54)
    0x7E, 0x49, 0x49, 0x49, 0x36, // 6
    // ... Di?er karakterler ...
};
// �NEML?: Yukar?daki font verisi sadece bir �rnektir ve eksiktir.
// Tam bir 5x7 font tablosu kullanman?z gerekmektedir.
// ?nternette "5x7 font c array" gibi aramalarla haz?r fontlar bulabilirsiniz.