#include "MyLFS2.h"




MyLFS2::MyLFS2(){
  LittleFS.begin();
}

void MyLFS2::mount(){
  
}

void MyLFS2::erase(){
 
}

void MyLFS2::write(std::string file_name, std::string string_to_write){
    File f = LittleFS.open(file_name.c_str(), "w");
    if (f) {
      f.write(string_to_write.c_str(),string_to_write.length());
      f.close();
    }
}


/**
 * @brief Reads content of file to std::string
 * 
 * @param file_name 
 * @return std::string 
 */
std::string MyLFS2::read_to_string(std::string file_name){
  
    File file = LittleFS.open(file_name.c_str(), "r");
    
    Serial.println(file.size());
    std::string s;
    
    if(file){
      while(file.available()){
        char c = (char)file.read();
        s.push_back(c);
        // Serial.println(c);
      }
      file.close();
    }
    
    
    
    
    return s;
}


// read to Serial
void MyLFS2::read(std::string file_name){
  Serial.println("READIIIN");
  File file = LittleFS.open(file_name.c_str(), "r");
    
  Serial.println(file.size());
  
  if(file){
    while(file.available()){
      Serial.write(file.read());
      // Serial.println(c);
    }
    file.close();
  }
  
}

void MyLFS2::rename_file(std::string old_file_name, std::string new_file_name){
   


}

void MyLFS2::delete_file(std::string file_name){
    
}

void MyLFS2::list_files(std::string path){
    // //TODO: test this method!
    // Serial.println("Opening the root directory... ");
    // // Serial.println(dir);
    // // fflush(stdout);
    // DIR *d = opendir("/fs/");
    // // DIR *d = opendir(dir);
    // Serial.println(!d ? "Fail :(" : "OK");
    // Serial.println(strerror(errno));
    // if (!d) {
    //     // error("error: %s (%d)\n", strerror(errno), -errno);
    // }

    // Serial.println("root directory:\n");
    // while (true) {
    //     struct dirent *e = readdir(d);
    //     if (!e) {
    //         break;
    //     }
    //     Serial.println(e->d_name);
    // }

    // Serial.println("Closing the root directory... ");
    // // fflush(stdout);
    // int err = closedir(d);
    // Serial.println(err < 0 ? "Fail :(" : "OK");
    // if (err < 0) {
    //     // error("error: %s (%d)\n", strerror(errno), -errno);
    //     Serial.println(strerror(errno));
    // }	
}

std::vector<std::string> MyLFS2::list_files_vec(std::string path){
  //TODO: test this method!

    std::vector<std::string> results;

    // Serial.println("Opening the root directory... ");
    // DIR *d = opendir("/fs/");
    // Serial.println(!d ? "Fail :(" : "OK");
    // Serial.println(strerror(errno));
    // if (!d) {
    //     // error("error: %s (%d)\n", strerror(errno), -errno);
    // }

    // Serial.println("root directory:\n");
    // while (true) {
    //     struct dirent *e = readdir(d);
    //     if (!e) {
    //         break;
    //     }
    //     Serial.println(e->d_name);
    //     results.push_back(std::string (e->d_name));
    // }

    // Serial.println("Closing the root directory... ");
    // // fflush(stdout);
    // int err = closedir(d);
    // Serial.println(err < 0 ? "Fail :(" : "OK");
    // if (err < 0) {
    //     // error("error: %s (%d)\n", strerror(errno), -errno);
    //     Serial.println(strerror(errno));
    // }	

    return results;
}

