#include "GroveRFIDReader.h"

GroveRFIDReader::GroveRFIDReader() {}

GroveRFIDReader::~GroveRFIDReader() {
	delete this->_serialRFID;
	delete this->_charBuffer;
}

void GroveRFIDReader::initialize(GrovePin pins, unsigned char tagBufferSize, unsigned char charBufferSize) {	
	this->_pinRX = pins.pin2;
	this->_pinTX = pins.pin1;
	this->_charBufferSize = charBufferSize;
	this->_charBufferIndex = 0;
	this->_charBuffer = new unsigned char[this->_charBufferSize];
	this->_tagBufferSize = tagBufferSize;
	this->_tagBuffer = new unsigned long[this->_tagBufferSize];
	this->_tagBufferIndexRead = 0;
	this->_tagBufferIndexWrite = 0;
	this->_serialRFID = new SoftwareSerial(this->_pinTX, this->_pinRX);
	this->_serialRFID->begin(9600);
}

void GroveRFIDReader::_readSerial() {
	unsigned char c;
	if(this->_serialRFID->available()) {
		while(this->_serialRFID->available())  {
            c = this->_serialRFID->read();
			if(0 != this->_charBufferIndex || 2 == c) {
				this->_charBuffer[this->_charBufferIndex++] = c;
			}
			if(3 == c || this->_charBufferIndex == this->_charBufferSize) {
				this->_processCharBuffer();
			}
        }
	}
}

void GroveRFIDReader::_processCharBuffer() {
	if(this->_charBufferIndex < 14) { return; }
	unsigned char index;
	unsigned long data, tagId = 0;
	for(index = 3; index < 11; ++index) {
		if(48 <= this->_charBuffer[index] && 57 >= this->_charBuffer[index]) {
			data = this->_charBuffer[index] - 48;
		} else if(65 <= this->_charBuffer[index] && 70 >= this->_charBuffer[index]) {
			data = this->_charBuffer[index] - 65 + 10;
		}
		tagId += data << 4*(8-(index-2));
		
	}
	this->_tagBuffer[this->_tagBufferIndexWrite++] = tagId;
	if(this->_tagBufferIndexWrite >= this->_tagBufferSize) {
		this->_tagBufferIndexWrite = 0;
	}
	if(this->_tagBufferIndexWrite == this->_tagBufferIndexRead) {
		++this->_tagBufferIndexRead;
	}
	this->_charBufferIndex = 0;
};

boolean GroveRFIDReader::isTagAvailable() {
	this->_readSerial();
	if(this->_tagBufferIndexRead == this->_tagBufferIndexWrite) {
		return false;
	}
	return true;
}

unsigned long GroveRFIDReader::read() {
	unsigned long tagId = 0;
	if(this->isTagAvailable()) {
		tagId = this->_tagBuffer[this->_tagBufferIndexRead++];
	}
	return tagId;
}