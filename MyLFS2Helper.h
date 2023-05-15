#include "MyLFS2.h"

// #include <Arduino.h>
#include <ArduinoJson.h>

class MyLFS2Helper{
    public:
        MyLFS2Helper();
        DynamicJsonDocument processString(MyLFS2* lfs,std::string s);

};