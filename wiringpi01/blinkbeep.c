#include <iostream>		// Include all needed libraries here
#include <wiringPi.h>
#include <stdlib.h>
using namespace std;		// No need to keep using “std”

int main(int argc, char * argv [])
{
	if (argc==1) {
		cout<<"check input: blinkbeep gpiopin blink_time(default=50ms)"<<endl;
		return 0;
	}
	int pinno=atoi(argv[1]);
	int blinktime=50;
	if (argc==3) blinktime=atoi(argv[2]);
	wiringPiSetup();			// Setup the library
	pinMode(pinno, OUTPUT);		// Configure GPIO0 as an output
	digitalWrite(pinno, LOW);
	digitalWrite(pinno, HIGH);
	delay(blinktime);
	digitalWrite(pinno, LOW);
	return 0;
}

