#pragma once

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class Serial
{
private:
	HANDLE H_handler;
	bool b_connected;
	COMSTAT cs_status;
	DWORD ul_errors;
	DWORD ul_bytesSend;

	char* p_portName;

public:
	Serial(char *portName);
	~Serial();

	int connect();
	void disconnect();

	bool writeSerialPort(void* buffer, DWORD bufferSize);
};