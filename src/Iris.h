/*
Iris.h - Iris library v0.6 - 2016-6-26
Copyright (c) 2016 Thales Services. All rights reserved.
I2C communication in which Arduino is the slave
*/
#ifndef Iris_h
#define Iris_h

#include <arduino.h>
#include <Wire.h> // I2C library
#include "FifoContainer.h"
#include "IrisBehaviour.h"

/* Version numbers for the protocol. The protocol is still changing, so these
* version numbers are important.
* Query using the REPORT_VERSION message.
*/
#define Iris_PROTOCOL_MAJOR_VERSION 0
#define Iris_PROTOCOL_MINOR_VERSION 6
/* Version numbers for the Iris library.
* The firmware version will not always equal the protocol version going forward.
* Query using the REPORT_FIRMWARE message.
*/
#define Iris_FIRMWARE_MAJOR_VERSION 0
#define Iris_FIRMWARE_MINOR_VERSION 2

// message command bytes
#define PIN_MODE_MSG_ID 0x01
#define DIGITAL_READ_MSG_ID 0x02
#define DIGITAL_WRITE_MSG_ID 0x03
#define DIGITAL_WRITES_MSG_ID 0x04
#define ANALOG_READ_MSG_ID 0x05
#define ANALOG_WRITE_MSG_ID 0x06
#define DEFINE_ENCODER_MSG_ID 0x07
#define GET_ENCODER_COUNTER_MSG_ID 0x08
#define GET_SOFT_VERSION_MSG_ID 0x09
#define GET_STATUS_MSG_ID 0x0A
#define GET_TYPE_ARDUINO_MSG_ID 0x0B
#define GET_IDL_VERSION_MSG_ID 0x0C
#define DIGITAL_READ_VALUE_MSG_ID 0xF2
#define ANALOG_READ_VALUE_MSG_ID 0xF5
#define ENCODER_COUNTER_MSG_ID 0xF8
#define STATUS_MSG_ID 0xFA
#define TYPE_ARDUINO_MSG_ID 0xFB
#define IDL_VERSION_MSG_ID 0xFC
#define SOFT_VERSION_MSG_ID 0xF9

// Digital pin mode (Iris protocol value)
#define INPUT_PIN_MODE 0
#define OUTPUT_PIN_MODE 1
#define PULLUP_PIN_MODE 2

// Digital pin value (Iris protocol value)
#define DIGITAL_LOW 0
#define DIGITAL_HIGH 1

/* That is a class function (method) which has an implicit this pointer. You can't use it as a static ISR.
In general, classes cannot implement ISRs for this reason. There are a few workarounds, one being to make it a static class function.
However then it will affect the entire class, not just one instance. */
void sendData(); // callback
void receiveData(int numBytes);


class IrisClass
{
public:
	IrisClass();
	/* Application of APIStyleGuide of Arduino:
	Use begin() to initialize a library instance, usually with some settings */
	void begin();
	void begin(int i2cAddress);
	boolean available(); // naw data available
	//void decodeMessage(byte msgBuffer[], int bufferSize); //Don’t assume knowledge of pointers so * is replaced by [] : APIStyleGuide
	void decodeMessage();
private:
	int _i2cAdress; // I2C Address of the Arduino device
	void initI2cAsSlave(int i2cAddress);
	FifoContainer * _ptMsgContainerQueue;
	
	IrisBehaviour * _irisBehaviour;
	
	void interpretPinModeMsg(byte data[], int msgSize);
	void digitalWriteMsg_received(byte data[], int msgSize);
	
	void decodePinModeMsg(byte data[], int msgSize);
	
	
	void printDebug(const String &functionName, const String &strToPrint);
};

extern IrisClass Iris;
#endif