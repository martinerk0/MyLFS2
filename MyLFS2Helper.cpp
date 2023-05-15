#include "MyLFS2Helper.h"



MyLFS2Helper::MyLFS2Helper(){

};

DynamicJsonDocument MyLFS2Helper::processString(MyLFS2* lfs,std::string s){

  DynamicJsonDocument result(1024);

  if(s.length()>0){
    // Serial.println(s.length());
    // const char* p_data  = s.data();
    const char* p_data  = s.c_str();
    Serial.print("INPUT STRING: ");Serial.println(p_data);

  }
  else{
    Serial.print("GOT EMPTY STRING: ");
    result["result"]="GOT EMPTY STRING:";
    return result;
  }
  // DynamicJsonDocument result(1024);

  DynamicJsonDocument doc(1024);
  deserializeJson(doc, s.c_str());

  Serial.print("Overflowed?: ");
  Serial.println(doc.overflowed());
  JsonObject obj = doc.as<JsonObject>();

  for (JsonPair p : obj) { 
      const char* key = p.key().c_str(); // is a JsonString 
      const char* value = p.value().as<const char*>(); // is a JsonString 
      Serial.print("Key: ");Serial.print(key);Serial.print(" Value: ");Serial.println(value);
      // p.value(); // is a JsonVariant
  }

  
  const char* command2 = obj["command"].as<const char*>();
  Serial.print("COMMAND:(");Serial.print(command2); Serial.println(")");
  char command  = command2[0];

  if(command=='w')  {
    Serial.println("write");
    if(obj.size()==3){
      const char* file = obj["file"];
      if(!obj.containsKey("data")){
            Serial.println("Obj does not contain key file! ");
            return result["result"]="Obj does not contain key file! ";
      }
      else if (obj["data"]==""){
            Serial.println("Obj[data] is empty string! ");
            return result["result"]="Obj[data] is empty string!";
      }
      else{

      }

      const char* data = obj["data"];
      std::string k =  std::string(data);
      for (size_t i = 0; i < k.length(); i++)
      {
        Serial.print("Char: "); Serial.println(k[i]);
      }
      Serial.print(file);Serial.print(data);
      result["result"]=data;
      lfs->write(file,data);
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
    const char* file = obj["file"];
    lfs->delete_file(file);
  }
  else if (command=='r') {

    if(!obj.containsKey("file")){
      Serial.println("obj does not contain correct keys!");
      return result["result"]="obj does not contain correct keys!";
    }
    
    const char* file = obj["file"];
    Serial.print("READ: ");Serial.println(file);
    std::string k =  std::string(file);
    // std::string(device_string);
    if (!k.empty() && k[k.length()-1] == '\n') {
      k.erase(k.length()-1);
      Serial.println("THERE WAS NEWLINE");
    }
    else{
      Serial.println("THERE WAS NO NEWLINE");
    }

    // Serial.println(k.c_str());
    // k.erase(std::find(k.begin(), k.end(), '\0'), k.end());
    if(k[k.length()-1] == '\0'){
       k.pop_back();
       Serial.println("THERE WAS NULL CHARACTER");
    }
    
    for (size_t i = 0; i < k.length(); i++)
    {
      Serial.print("Char: "); Serial.println(k[i]);
    }
    
    // fflush(stdout);
    // const char * filename = path.c_str();
    std::string res = lfs->read_to_string(k);
    result["content"]=res;

  }
  else if (command=='x') {
    // Serial.println("Formatting... ");
    // int err = fs.reformat(bd);
    // Serial.println((err ? "Fail :(" : "Filesystem OK"));
  }
  else if (command=='y') {
    const char* rename_from = obj["rename_from"];
    const char* rename_to = obj["rename_to"];
    lfs->rename_file(rename_from,rename_to);
  }

  else if (command=='l') {
    // Serial.println("list files");
    const char* file = obj["file"];
    //TODO: return listed files!
    std::vector<std::string> res = lfs->list_files_vec(file);
    JsonArray nested = result.createNestedArray();
    for(auto& elem : res){
        nested.add(elem);
    }
    
  }
  else if (command=='m') {
    // Serial.println("Mount!");
    // bd->init();
    // int err = fs.mount(bd);
    // Serial.println((err ? "Init Fail :(" : "Init OK"));
    lfs->mount();
  }
  else if (command=='u') {
    // Serial.println("Unmount!");
    // int err = fs.unmount();
    // Serial.println((err ? "Fail :(" : "Unmounted OK"));
    // err = bd->deinit();
    // Serial.println((err ? "Deinit Fail :(" : "Deinit OK"));
  }
  else if (command=='e') {
    lfs->erase();
  }

  else if (command=='t') {
    result["content"]="reset";
  }
  
  else{
    Serial.println("other");
  }


  return result;
}