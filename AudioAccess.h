#include <sstream>

using namespace std;

static class AudioAccess {
private:
    const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
    const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
    const IID IID_IDeviceTopology = __uuidof(IDeviceTopology);
    const IID IID_IPart = __uuidof(IPart);
public:
    wstringstream getDevices();
};