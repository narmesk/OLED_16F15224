/*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.2
 *
 * @version Package Version: 3.1.2
 */

/*
� [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
 */
#include "mcc_generated_files/system/system.h" // MCC'nin �retti?i ana ba?l?k dosyas?
#include "oled_ssd1306.h"

// _XTAL_FREQ tan?m? burada veya projenin genel ayarlar?nda yap?lmal?
#ifndef _XTAL_FREQ
#define _XTAL_FREQ 32000000UL // 32MHz
#endif

/*
    Main application
 */

int main(void)
{
    //SYSTEM_Initialize();
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    //INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 

    // Enable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptEnable(); 

    // Disable the Peripheral Interrupts 
    //INTERRUPT_PeripheralInterruptDisable(); 



    // MCC taraf?ndan �retilen ba?latma fonksiyonu
    SYSTEM_Initialize(); // Bu fonksiyon OSCCON, PIN_MANAGER, I2C1 vb. ayarlar?n? yapar.

    // I2C1_Initialize() burada otomatik olarak �a?r?l?r.

    // OLED'i ba?lat
    OLED_Init();

    // OLED'e �rnek bir mesaj yazd?r
    // OLED_ClearScreen(); // OLED_Init i�inde zaten �a?r?l?yor.

    OLED_DrawString(5, 2, "Merhaba Dunya!"); // Fontunuz T�rk�e karakterleri destekliyorsa
    OLED_DrawString(5, 12, "PIC16F15224");
    OLED_DrawString(5, 22, "MCC I2C ile");
    OLED_DrawString(5, 32, "OLED Testi");
    OLED_DrawString(5, 42, "@ 100kHz");


    // �izilenleri ekrana g�nder
    OLED_RefreshScreen();

    // Gerekirse global ve peripheral kesmeleri burada tekrar etkinle?tirin,
    // ancak SYSTEM_Initialize() genellikle bunu halleder.
    // INTCONbits.GIE = 1;
    // INTCONbits.PEIE = 1;

    while (1)
    {
        // Ana d�ng�.
        // Ekran dinamik olarak g�ncelleniyorsa, OLED_RefreshScreen() burada
        // veya bir zamanlay?c? kesmesinde periyodik olarak �a?r?labilir.
        // Bu �rnekte ekran statik.
        __delay_ms(1000); // CPU'yu biraz dinlendir
    }
}
