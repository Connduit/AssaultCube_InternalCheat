#pragma once

class Memory
{
public:
    // TODO: add functions to get HMODULE before doing reinterpret_cast???

    // TODO: readAddress function
    // TODO: readBase+Offset function
    // TODO: writeAddress function
    // TODO: writeBase+Offset function

    // TODO: void resetPointers(); // see constants.cpp::resetPointers()

    // TODO: probably can make these functions inline, right?
    void setBaseAddress()
    {
        // baseAddress_ = reinterpret_cast<uintptr_t>(GetModuleHandle(L"ac_client.exe"));
        baseAddress_ = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)); // passing nullptr just gets handle to current/main process (aka. the process we injected into)
    }
    static uintptr_t getBaseAddress()
    {
        return baseAddress_;
    }
private:
    static uintptr_t baseAddress_;
};
