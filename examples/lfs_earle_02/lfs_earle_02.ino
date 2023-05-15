#include <Arduino.h>

#include <string>
#include <vector>
#include <sstream>
#include <stdio.h>
#include <functional>
#include <errno.h>

#include <MyLFS2.h>


// - read command from serial and:
// - understand following commands:
// w <file name> <file contents>       ... writes contents to file
// a <file name> <file contents>       ... appends contents to the end of file
// r <file name>                       ... reads file and sends contents over UDP
// d <file name>                       ... deletes file
// e                                   ... erase filesysyem

MyLFS2 *lfs;

char incomingByte;
std::string s;

void setup() {
  Serial.begin(115200 );
  while (!Serial);
  lfs = new MyLFS2();
  Serial.println("LFS Begun!");

  // for (int i = 0; i < 50; i++)
  //   {
  //     std::string num = std::to_string(i);
  //     std::string p ="test";
  //     p.append(num);
  //     lfs->write(p,p);
  //   }


  // for (size_t i = 0; i < 50; i++)
  // {
  //   std::string num = std::to_string(i);
  //   std::string p ="test";
  //   p.append(num);
  //   lfs->read(p.c_str());

  // }
  

}

void processString(std::string s){
  if(s.length()>0){
    // Serial.println(s.length());
    // const char* p_data  = s.data();
    const char* p_data  = s.c_str();
    Serial.print("INPUT STRING: ");Serial.println(p_data);

  }
  else{
    Serial.print("GOT EMPTY STRING: ");
    return;
  }
  
  char delimeter = ':';
 
  std::vector<std::string>   result;
  std::stringstream  data(s);

  std::string line;
  while(std::getline(data,line,delimeter)){
      result.push_back(line); // Note: You may get a couple of blank lines
  }
  if (result.size()<1){
    return;
  }
    
  char command = (char) result[0][0];

  if(command=='w')  {
    Serial.println("write");
    if(result.size()==3){
      //TODO: write to file using earle's LITTLEFS
      // Serial.println("File name: "+result[1].c_str()+" file contents: "+result[2].c_str());
      // Serial.println("File name: "+result[1].c_str()+" file contents: "+result[2].c_str());
       lfs->write(result[1],result[2]);
    }
    else{
      Serial.println("wrong number of arguments!");
    }
  }
  else if (command=='a') {
    Serial.println("append");
  }
  else if (command=='d') {
    Serial.println("delete");
    // lfs->delete_file(result[1]);
  }
  else if (command=='r') {
    Serial.println("read");
    std::string k =  std::string(result[1]);
    // std::string(device_string);
    if (!k.empty() && k[k.length()-1] == '\n') {
      k.erase(k.length()-1);
      Serial.println("THERE WAS NEWLINE");
    }
    else{
      Serial.println("THERE WAS NO NEWLINE");
    }

    Serial.println(k.c_str());
    // k.erase(std::find(k.begin(), k.end(), '\0'), k.end());
    if(k[k.length()-1] == '\0'){
       k.pop_back();
    }
    
    for (size_t i = 0; i < k.length(); i++)
    {
      Serial.print("Char: "); Serial.println(k[i]);
    }
    
    // fflush(stdout);
    // const char * filename = path.c_str();
    // lfs->read(k.c_str());
    std::string s = lfs->read_to_string(k.c_str());
    Serial.println(s.c_str());
  }
  else if (command=='x') {
    // Serial.println("Formatting... ");
    // int err = fs.reformat(bd);
    // Serial.println((err ? "Fail :(" : "Filesystem OK"));
  }
  else if (command=='y') {
    // lfs->rename_file(result[1],result[2]);
  }

  else if (command=='l') {
    // Serial.println("list files");
    // lfs->list_files(result[1].c_str());
  }
  else if (command=='m') {
    // Serial.println("Mount!");
    // bd->init();
    // int err = fs.mount(bd);
    // Serial.println((err ? "Init Fail :(" : "Init OK"));
    // lfs->mount();
  }
  else if (command=='u') {
    // Serial.println("Unmount!");
    // int err = fs.unmount();
    // Serial.println((err ? "Fail :(" : "Unmounted OK"));
    // err = bd->deinit();
    // Serial.println((err ? "Deinit Fail :(" : "Deinit OK"));
  }
  else if (command=='e') {
    // lfs->erase();
  }
  
  else{
    Serial.println("other");
  }
}



void loop(){
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    if (incomingByte == '\n'){
        // say what you got:
        Serial.print("I received: ");
        // Serial.println(s);
        Serial.println(s.c_str());
        processString(s.c_str());
        s.clear();
    }
    else{
        s.push_back(incomingByte);
    }
  }
}
