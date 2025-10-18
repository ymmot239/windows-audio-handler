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

#define SAFE_RELEASE(punk)  \
              if ((punk) != NULL)  \
                { (punk)->Release(); (punk) = NULL; }

using namespace std;


wstringstream AudioAccess::getDevices() {
    //initialize wide string buffer
    wstringstream wss;

    //start enumerator
        
    IMMDeviceEnumerator* pEnumerator;
    IMMDeviceCollection* collection;
    CoInitialize(nullptr);

    try {
        const HRESULT hr = CoCreateInstance(
            CLSID_MMDeviceEnumerator, NULL,
            CLSCTX_ALL, IID_IMMDeviceEnumerator,
            (void**)&pEnumerator);

        //get media collection
        pEnumerator[0].EnumAudioEndpoints(eAll, DEVICE_STATE_ACTIVE, &collection);

        //get collection count
        UINT devCount;
        collection->GetCount(&devCount);

        //put in string buffer
        wss << "Device count: " << devCount << endl;

        for (UINT x = 0; x < devCount; x++) {
            IMMDevice* device;
            IPropertyStore* props;
            PROPVARIANT varName;
            //try getting device name
            try {
                //get individual devices
                collection->Item(x, &device);

                //get device props
                device->OpenPropertyStore(STGM_READ, &props);

                //get individual prop by name
                PropVariantInit(&varName);
                props->GetValue(PKEY_Device_FriendlyName, &varName);

                //append to string buffer
                wss << "Device #" << x + 1 << " : " << varName.pwszVal << endl;
            }
            catch (exception e) {
                wss << "Device #" << x + 1 << " : " << "error " << e.what() << endl;
            }

            PropVariantClear(&varName);
            SAFE_RELEASE(props);
            SAFE_RELEASE(device);
        }

    }
    catch (exception e) {
        wss << "Device error";
    }

    SAFE_RELEASE(collection);
    SAFE_RELEASE(pEnumerator);

    return wss;
}
