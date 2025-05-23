/*
 * File:   font.c
 * Author: armag
 *
 * Created on May 22, 2025, 7:55 PM
 */
#include "font.h"

// Basit 5x7 Font (ASCII 32-126)
// Her karakter 5 byte (5 kolon)
// Font verisi: http:// Bürgermeister.de/wp-content/uploads/2014/01/font5x7.h sitesinden al?nabilir
// veya basit bir tane olu?turulabilir. Bu örnekte sadece 'H' ve 'i' harfleri için basit bir gösterim:
// Daha tam bir font seti kullanman?z gerekecektir.
const uint8_t basicFont_5x7[] = {
    // Bo?luk ' ' (ASCII 32)
    0x00, 0x00, 0x00, 0x00, 0x00,
    // Ünlem '!'
    0x00, 0x00, 0x5F, 0x00, 0x00,
    // ... Di?er karakterler ...
    // Örnek olarak 'H' (ASCII 72)
    // Varsayal?m ki 'H' fontun (72-32) = 40. karakteri
    // ... (39 karakter * 5 byte) ...
    0x7F, 0x08, 0x08, 0x08, 0x7F, // H
    // Örnek olarak 'e' (ASCII 101)
    // ...
    0x3E, 0x4A, 0x4A, 0x4A, 0x32, // e (yakla??k)
    // Örnek olarak 'l' (ASCII 108)
    0x00, 0x41, 0x7F, 0x40, 0x00, // l
    // Örnek olarak 'o' (ASCII 111)
    0x3E, 0x41, 0x41, 0x41, 0x3E, // o
    // Örnek olarak 'P' (ASCII 80)
    0x7F, 0x09, 0x09, 0x09, 0x06, // P
    // Örnek olarak 'I' (ASCII 73) -> 'i' ile kar??mamas? için büyük I
    0x00, 0x00, 0x7F, 0x00, 0x00, // I
    // Örnek olarak 'C' (ASCII 67)
    0x3E, 0x41, 0x41, 0x41, 0x22, // C
    // Örnek olarak '1' (ASCII 49)
    0x00, 0x42, 0x7F, 0x40, 0x00, // 1
    // Örnek olarak '6' (ASCII 54)
    0x7E, 0x49, 0x49, 0x49, 0x36, // 6
    // ... Di?er karakterler ...
};
// ÖNEML?: Yukar?daki font verisi sadece bir örnektir ve eksiktir.
// Tam bir 5x7 font tablosu kullanman?z gerekmektedir.
// ?nternette "5x7 font c array" gibi aramalarla haz?r fontlar bulabilirsiniz.