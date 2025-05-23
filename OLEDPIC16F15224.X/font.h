/* 
 * File:   font.h
 * Author: armag
 *
 * Created on May 22, 2025, 7:54 PM
 */
#ifndef FONT_H
#define FONT_H

#include <stdint.h>

// Basit 5x7 Font (ASCII 32-126)
// Her karakter 5 byte (5 kolon) + 1 byte bo?luk için ideal
#define FONT_WIDTH 5
#define FONT_HEIGHT 7 // Asl?nda 8 piksel yükseklikte bir sayfaya s??ar

extern const uint8_t basicFont_5x7[];

#endif // FONT_H