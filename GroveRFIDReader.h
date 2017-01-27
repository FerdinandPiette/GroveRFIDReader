#ifndef GroveRFIDReader_H
#define GroveRFIDReader_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "../Grove/Grove.h"

class GroveRFIDReader {
	private:
		unsigned int _pinRX;
		unsigned int _pinTX;
		SoftwareSerial * _serialRFID;
		unsigned char * _charBuffer;
		unsigned char _charBufferSize;
		unsigned char _charBufferIndex;
		unsigned long * _tagBuffer;
		unsigned char _tagBufferSize;
		unsigned char _tagBufferIndexRead;
		unsigned char _tagBufferIndexWrite;
		boolean _isHardwareSerial();
		void _readSerial();
		void _processCharBuffer();
		
	public:
		GroveRFIDReader(GrovePin pins, unsigned char tabBufferSize = 64, unsigned char charBufferSize = 16);
		virtual ~GroveRFIDReader();
		void initialize();
		boolean isTagAvailable();
		unsigned long read();
};

#endif