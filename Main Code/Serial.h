#ifndef Serail
#define Serial

// code to load here
#include <avr/io.h>
#include <avr/interrupt.h>
#define FOSC 16000000 // Clock Speed

void serialBegin(int BAUD_RATE);
unsigned int serialAvailable(void);
void serialWrite(char* str);
void Write(unsigned char data);
unsigned char serialRead(void);
void serialFlush(void);



#endif