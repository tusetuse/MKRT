#include "stdio.h"
#include "c8051f330.h"

const char *code morse_table[36] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---",   	// A-J
    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-",     	// K-T
    "..-", "...-", ".--", "-..-", "-.--", "--..",                           	// U-Z
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...",  	// 0-7
    "---..", "----."                                                       	// 8-9
};

extern void Init_Device(void);

void UART_Transmit(char c) {				//funkcia nacita a transmitne jednotlive znaky morse kodu prisluchajuce ku danemu pismenu/cislu
	
    while (!TI0);
		TI0 = 0;
    SBUF0 = c;
}

void Send_Morse_UART(char *morse) {			//funkcia podla indexu najde ekvivalent morsovho kodu pre jednotlive pismena/cisla v poli a passne ich do Transmit funkcie
	
    while (*morse) {					//Loopuje pokial nehitne null character(koniec stringu) = koniec pismena/cisla v morse kode
        UART_Transmit(*morse++);			//Nacita jeden znak z pismena/cisla morse kodu a prejde na dalsi 
    }
    UART_Transmit(' ');					//Nacita medzeru ked loop skonci
}

void main() {
	char *ptr;		
	char ch;
	char input[64];
	Init_Device();
	TR1 = 1;              				// Start Timer 
	TI0 = 1; 					// Nastavenie transmit interupt flag na prvy prenos

    while (1) {
        printf("Enter a message: ");
        scanf("%63s", input);				//Obmedzi user input na 63 znakov
        ptr = input;
        while (*ptr) {					//Loop bezi pokial pointer nepride na koniec stringu 
            ch = *ptr++;
            if (ch >= 'a' && ch <= 'z') {
                ch -= 'a';				//Prevod na index 0-25
            } else if (ch >= 'A' && ch <= 'Z') {
                ch -= 'A';				//Prevod na index 0-25
            } else if (ch >= '0' && ch <= '9') {
                ch -= '0' + 26;				//Prevod na index 26-35
            } else {
                continue;
            }
            Send_Morse_UART(morse_table[ch]);
        }
        UART_Transmit('\n');
    }
}
