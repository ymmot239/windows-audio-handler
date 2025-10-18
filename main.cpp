#ifndef UNICODE
#define UNICODE
#endif 

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include <objbase.h>
#include <mmdeviceapi.h>
#include <devicetopology.h>
#include <Functiondiscoverykeys_devpkey.h>
#include <fstream>

#include "AudioAccess.h"

using namespace std;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
    AudioAccess audio = AudioAccess();

    wstringstream wss = audio.getDevices();

    //note in case is needed
    //const wstring& s = ws.str(); then wstring.c_str()
    MessageBox(NULL, wss.str().c_str(), TEXT("HelloMsg"), 0);
    FILE *myfile = fopen("example.txt", "w+, ccs=UTF-8");
    fputws(wss.str().c_str(), myfile);
    fclose(myfile);
    return 0 ;
}