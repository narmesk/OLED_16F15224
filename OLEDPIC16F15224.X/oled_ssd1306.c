// =============================================================================
// EN ÜSTE EKLENMES? GEREKEN BA?LIK DOSYALARI
// =============================================================================
#ifndef _XTAL_FREQ
    // Bu makro, __delay_ms fonksiyonunun do?ru çal??mas? için gereklidir.
    // Projenizin sistem saat frekans?yla (Hz cinsinden) e?le?melidir.
    #define _XTAL_FREQ 32000000UL 
#endif

#include <xc.h> // XC8 derleyicisinin temel ba?l?k dosyas? (__delay_ms için gerekli)
#include <string.h> // memset fonksiyonu için

#include "oled_ssd1306.h"
#include "font.h" // Font dosyan?z?n ba?l???

// MCC taraf?ndan üretilen I2C sürücüsünün ba?l?k dosyas?.
// Projenizdeki dosya ad? farkl? olabilir (örn: i2c1.h). Lütfen kontrol edin.
#include "mcc_generated_files/i2c_host/mssp1.h" 

// =============================================================================


// Ekran tamponu
static uint8_t oled_buffer[OLED_BUFFER_SIZE];

// Komutlar? ve küçük veri paketlerini göndermek için geçici bir tampon.
#define OLED_CMD_BUFFER_SIZE 4
static uint8_t i2c_command_tx_buffer[OLED_CMD_BUFFER_SIZE];

// Ekran?n bir sayfas?n? (128 byte) + 1 kontrol byte'?n? göndermek için tampon.
#define OLED_PAGE_TX_BUFFER_SIZE (OLED_WIDTH + 1)
static uint8_t i2c_page_tx_buffer[OLED_PAGE_TX_BUFFER_SIZE];


// Dahili yard?mc? fonksiyon: Tek bir komut veya komut dizisi gönderir.
static void oled_send_command_sequence(uint8_t* commands, uint8_t length) {
    if (length == 0 || length > (OLED_CMD_BUFFER_SIZE - 1)) {
        return;
    }

    while (I2C1_IsBusy()) {
    }

    i2c_command_tx_buffer[0] = OLED_CONTROL_BYTE_COMMAND;
    for (uint8_t i = 0; i < length; ++i) {
        i2c_command_tx_buffer[i + 1] = commands[i];
    }

    I2C1_Write(OLED_I2C_ADDRESS, i2c_command_tx_buffer, length + 1);

    while (I2C1_IsBusy()) {
    }
}

// Dahili yard?mc? fonksiyon: Tek bir komut byte'? gönderir.
static void oled_send_command(uint8_t command_byte) {
    oled_send_command_sequence(&command_byte, 1);
}


void OLED_Init(void) {
    __delay_ms(20);

    oled_send_command(0xAE);

    uint8_t cmd_seq[2];

    cmd_seq[0] = 0xD5; cmd_seq[1] = 0x80;
    oled_send_command_sequence(cmd_seq, 2);

    cmd_seq[0] = 0xA8; cmd_seq[1] = 0x3F;
    oled_send_command_sequence(cmd_seq, 2);

    cmd_seq[0] = 0xD3; cmd_seq[1] = 0x00;
    oled_send_command_sequence(cmd_seq, 2);

    oled_send_command(0x40);

    cmd_seq[0] = 0x8D; cmd_seq[1] = 0x14;
    oled_send_command_sequence(cmd_seq, 2);

    cmd_seq[0] = 0x20; cmd_seq[1] = 0x00;
    oled_send_command_sequence(cmd_seq, 2);

    oled_send_command(0xA1);
    oled_send_command(0xC8);

    cmd_seq[0] = 0xDA; cmd_seq[1] = 0x12;
    oled_send_command_sequence(cmd_seq, 2);

    cmd_seq[0] = 0x81; cmd_seq[1] = 0xCF;
    oled_send_command_sequence(cmd_seq, 2);

    cmd_seq[0] = 0xD9; cmd_seq[1] = 0xF1;
    oled_send_command_sequence(cmd_seq, 2);

    cmd_seq[0] = 0xDB; cmd_seq[1] = 0x40;
    oled_send_command_sequence(cmd_seq, 2);

    oled_send_command(0xA4);
    oled_send_command(0xA6);

    OLED_ClearScreen();
    OLED_RefreshScreen();

    oled_send_command(0xAF);
    __delay_ms(100);
}

static void oled_set_address_window(uint8_t col_start, uint8_t col_end, uint8_t page_start, uint8_t page_end) {
    uint8_t cmd_seq[3];

    cmd_seq[0] = 0x21; cmd_seq[1] = col_start; cmd_seq[2] = col_end;
    oled_send_command_sequence(cmd_seq, 3);

    cmd_seq[0] = 0x22; cmd_seq[1] = page_start; cmd_seq[2] = page_end;
    oled_send_command_sequence(cmd_seq, 3);
}

void OLED_RefreshScreen(void) {
    oled_set_address_window(0, OLED_WIDTH - 1, 0, OLED_PAGES - 1);

    i2c_page_tx_buffer[0] = OLED_CONTROL_BYTE_DATA;

    for (uint8_t page = 0; page < OLED_PAGES; ++page) {
        memcpy(&i2c_page_tx_buffer[1], &oled_buffer[page * OLED_WIDTH], OLED_WIDTH);

        while (I2C1_IsBusy()) {}
        I2C1_Write(OLED_I2C_ADDRESS, i2c_page_tx_buffer, OLED_WIDTH + 1);
    }
    
    while (I2C1_IsBusy()) {}
}

void OLED_ClearScreen(void) {
    memset(oled_buffer, 0x00, OLED_BUFFER_SIZE);
}

void OLED_SetPixel(uint8_t x, uint8_t y, bool color) {
    if (x >= OLED_WIDTH || y >= OLED_HEIGHT) {
        return;
    }

    uint16_t byte_index;
    uint8_t bit_mask;

    byte_index = (y / 8) * OLED_WIDTH + x;
    
    // UYARI DÜZELTMES?:
    // `1` bir int oldu?u için, bit kayd?rma i?leminin sonucu da bir int olur.
    // Bu sonucu uint8_t olan bit_mask'a atarken derleyici uyar? verir.
    // (uint8_t)1 kullanarak i?lemi do?ru türde ba?lat?yoruz.
    bit_mask = (uint8_t)1 << (y % 8);

    if (byte_index < OLED_BUFFER_SIZE) {
        if (color) {
            oled_buffer[byte_index] |= bit_mask;
        } else {
            oled_buffer[byte_index] &= ~bit_mask;
        }
    }
}

void OLED_DrawChar(uint8_t x, uint8_t y, char character) {
    if (x > OLED_WIDTH - FONT_WIDTH || y > OLED_HEIGHT - FONT_HEIGHT) {
        return;
    }
    if (character < ' ' || character > '~') {
        character = ' ';
    }

    uint16_t font_char_offset = (character - ' ') * FONT_WIDTH;

    for (uint8_t col = 0; col < FONT_WIDTH; ++col) {
        uint8_t font_column_data = basicFont_5x7[font_char_offset + col];
        for (uint8_t row_bit = 0; row_bit < FONT_HEIGHT; ++row_bit) {
            if ((font_column_data >> row_bit) & 0x01) {
                OLED_SetPixel(x + col, y + row_bit, true);
            } else {
                OLED_SetPixel(x + col, y + row_bit, false);
            }
        }
    }
}

void OLED_DrawString(uint8_t x, uint8_t y, const char* str) {
    uint8_t current_x = x;
    char character;

    while ((character = *str++) != '\0') {
        if (character == '\n') {
            current_x = x;
            y += FONT_HEIGHT + 1;
            if (y + FONT_HEIGHT > OLED_HEIGHT) break;
            continue;
        }
        if (current_x + FONT_WIDTH > OLED_WIDTH) {
            current_x = x;
            y += FONT_HEIGHT + 1;
            if (y + FONT_HEIGHT > OLED_HEIGHT) break;
        }
        OLED_DrawChar(current_x, y, character);
        current_x += FONT_WIDTH + 1;
    }
}