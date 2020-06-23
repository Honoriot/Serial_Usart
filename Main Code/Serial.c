#include <Serial.h>

void serialBegin(int BAUD_RATE){
	
	// Set baud rate
	#if BAUD_RATE < 57600
	uint16_t UBRR0_value = ((F_CPU / (8L * BAUD_RATE)) - 1)/2 ;
	UCSR0A &= ~(1 << U2X0); // baud doubler off  
	#else
	uint16_t UBRR0_value = ((F_CPU / (4L * BAUD_RATE)) - 1)/2;
	UCSR0A |= (1 << U2X0);  // baud doubler on for high baud rates, i.e. 115200
	#endif
	
	
	/*Set baud rate */
	UBRR0H = (UBRR0_value>>8);
	UBRR0L = UBRR0_value;
	
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
	
	// defaults to 8-bit, no parity, 1 stop bit
}

unsigned int serialAvailable(void){
	/* Wait for data to be received:*/
	while (!(UCSR0A & (1<<RXC0))){
		return 1;
	}
	return -1;	
}

void serialWrite(char* str){
	unsigned char i;
	while(str[i]!=0){
		Write(str[i]);
		i++;
	}
}

void Write(unsigned char data){
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
		;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char serialRead(void){
	
	/* If error, return -1 */
	if ( UCSR0A & (1<<FE0)|(1<<DOR0)|(1<<UPE0) )
		return -1;
	/* Get and return received data from buffer */
	return UDR0;
}

void serialFlush(void){
	unsigned char dummy;    
	
	/* wait for outgoing transmission to complete */
	while(!(UCSR0A & (1<<UDRE0)))
		;	
	UDR0 = dummy;
}

