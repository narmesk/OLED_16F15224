/* 
 * File:   oled_ssd1306.h
 * Author: armag
 *
 * Created on May 22, 2025, 7:59 PM
 */
#ifndef OLED_SSD1306_H
#define OLED_SSD1306_H

#include <stdint.h>
#include <stdbool.h>


// Gerekirse eklenebilir

#define OLED_I2C_ADDRESS         0x3C // 7-bit I2C adresi (SSD1306 için genellikle bu veya 0x3D)

// OLED kontrolcü komutlar? (SSD1306 için)
#define OLED_CONTROL_BYTE_COMMAND 0x00
#define OLED_CONTROL_BYTE_DATA    0x40

#define OLED_WIDTH  32//128
#define OLED_HEIGHT 16//64
#define OLED_PAGES  (OLED_HEIGHT / 8) // 64 / 8 = 8 sayfa
#define OLED_BUFFER_SIZE (OLED_WIDTH * OLED_PAGES) // 128 * 8 = 1024 byte

void OLED_Init(void);
void OLED_ClearScreen(void); // Ekran tamponunu temizler
void OLED_RefreshScreen(void); // Ekran tamponunu OLED'e gönderir

void OLED_SetPixel(uint8_t x, uint8_t y, bool color); // color=true (set), false (clear)
void OLED_DrawChar(uint8_t x, uint8_t y, char character);
void OLED_DrawString(uint8_t x, uint8_t y, const char* str);

// ?ste?e ba?l?: OLED sürücüsünün me?gul olup olmad???n? kontrol etmek için
// bool OLED_IsBusy(void); // Do?rudan I2C1_IsBusy() kullan?labilir.

#endif // OLED_SSD1306_H