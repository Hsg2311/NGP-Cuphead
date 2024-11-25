// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#ifndef __FRAMEWORK_H
#define __FRAMEWORK_H


#define SERVERIP "192.168.219.188"
//#define SERVERIP "127.0.0.1"


#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일

// C 런타임 헤더 파일입니다.
#include <winsock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#endif // __FRAMEWORK_H