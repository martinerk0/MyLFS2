#ifndef MYLFS2_H
#define MYLFS2_H


// #include "mbed.h"

#include <Arduino.h>
// #include <FlashIAP.h>
// #include <FlashIAPBlockDevice.h>

// #include "FlashIAPLimits.h"
// #include "LittleFileSystem.h"
#include <LittleFS.h>

#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <functional>
#include <errno.h>


// struct FlashIAPLimits {
//   size_t flash_size;
//   uint32_t start_address;
//   uint32_t available_size;
// };

class MyLFS2{
    public:
        MyLFS2();
        void write(std::string file_name, std::string string_to_write);
        void read(std::string file_name);
        std::string read_to_string(std::string file_name);
        void rename_file(std::string old_file_name, std::string new_file_name);
        void delete_file(std::string file_name);
        std::vector<std::string> list_files_vec(std::string path);
        void list_files(std::string path);
        void erase();
        void mount();
        // FlashIAPLimits getFlashIAPLimits();
    private:
        // FlashIAPBlockDevice* blockDevicePtr;
        // mbed::LittleFileSystem* fs;
    
};

#endif

