#pragma once
#include <iostream>

//클라에게 보낼 정보 

class Interface {
private:
	static bool sendFlag;
	
public:
	void serverSend(char* buf);
	

};