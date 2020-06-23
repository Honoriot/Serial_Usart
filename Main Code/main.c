#include <AVR/io.h>
#include <Serial.h>

int main(){
	
	serialBegin(9600);
	
	char data;
	char T_data [] = "Earth is beautiful";
	
	
	while(1){
	
		if(serialAvailable()>0){
			data = serialRead();
		}
		
		serialWrite(T_data);
		serialFlush();
	
	}
	return 0;
}