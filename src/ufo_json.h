#ifndef JSON_INTERFACE_H
#define JSON_INTERFACE_H
#include "../external/cJSON.h"
#include <string>
#include <vector>
#include "file.h"
#include "console.h"
#include "file.h"

namespace ujson{
    cJSON* JsonParse(std::string _path);
    cJSON* GetObject(cJSON* _obj, std::string _name);
    int ArrayLen(cJSON* _obj);
    cJSON* GetElement(cJSON* _obj, int _index);
    cJSON* CreateObject();
    cJSON* CreateString(std::string _s);
    cJSON* CreateNumber(double _num);
    cJSON* CreateNumber(int _num);
    cJSON* CreateArray();
    void AddItemToArray(cJSON* _obj_a, cJSON* _obj_b);
    void AddItemToObject(cJSON* _obj_a, std::string _name, cJSON* _obj_b);
    
}

/*class Json;

namespace json_get{
    template<typename tType>
    tType Get(cJSON* _json, std::string _name);

    template<>
    int Get<int>(cJSON* _json, std::string _name);
    template<>
    double Get<double>(cJSON* _json, std::string _name);
    template<>
    std::string Get<std::string>(cJSON* _json, std::string _name);
    template<>
    Json Get<Json>(cJSON* _json, std::string _name);
}*/

class Json{
public:
    cJSON *member;
    std::string path;
    bool is_top_node = false;
    Json() = default;

    //new functions

    /*template<typename tType>
    tType Get(std::string _name){
        return json_get::Get<tType>(this, _name);
    }*/

    static Json Read(std::string _path);

    static Json NewJson(std::string _path);

    void Save(){
        Write(path);
    }
    
    void Write(std::string _path){
        auto file = File::New(_path);
        file.Insert(GetJsonAsString());
        file.Save();
    }

    static Json NewJson(){
        Json json;
        json.member = ujson::CreateObject();
        json.is_top_node = true;
        return json;
    }

    Json GetObject(std::string _name){
        Json json;
        json.member = ujson::GetObject(member, _name);
        return json;
    }

    int GetAsInt(std::string _name){
        return GetObject(_name).GetAsInt();
    }

    double GetAsDouble(std::string _name){
        return GetObject(_name).GetAsDouble();
    }

    std::string GetAsString(std::string _name){
        return GetObject(_name).GetAsString();
    }

    std::vector<Json> GetAsArray(std::string _name){
        return GetObject(_name).GetAsArray();
    }

    int GetAsInt(){
        return member->valueint;
    }

    double GetAsDouble(){
        return member->valuedouble;
    }

    std::string GetAsString(){
        return member->valuestring;
    }

    std::vector<Json> GetAsArray(){
        std::vector<Json> v;
        for(int i = 0; i < ujson::ArrayLen(member); i++){
            Json json;
            json.member = ujson::GetElement(member, i);
            v.push_back(json);
        }
        return v;
    }

    static Json New(int _number){
        Json json;
        json.member = ujson::CreateNumber(_number);
        return json;
    }

    static Json New(double _number){
        Json json;
        json.member = ujson::CreateNumber(_number);
        return json;
    }

    static Json New(std::string _s){
        Json json;
        json.member = ujson::CreateString(_s);
        return json;
    }

    template<typename tType>
    static Json New(std::vector<tType>& _v){
        Json json;
        json.member = ujson::CreateArray();
        for(tType item : _v){
            ujson::AddItemToArray(json.member, item);
        }
        return json;
    }

    static Json NewArray(){
        Json json;
        json.member = ujson::CreateArray();
        return json;
    }
    void PushToObject(std::string _name, Json _json){
        ujson::AddItemToObject(member, _name, _json.member);
    }

    void PushToArray(Json _json){
        ujson::AddItemToArray(member, _json.member); //this object may or may not even be an array
    }

    std::string GetJsonAsString(){
        return cJSON_Print(member);
    }

    ~Json(){
        if(is_top_node){
            cJSON_Delete(member);
            Console::Out("cJSON_Delete");
        }
    }
    
};

/*namespace json_get{
    template<typename tType>
    tType Get(cJSON* _json, std::string _name){
        
    }

    template<>
    int Get<int>(cJSON* _json, std::string _name){
        return ujson::GetObject(_json, _name)->valueint;
    }
    template<>
    double Get<double>(cJSON* _json, std::string _name){
        return ujson::GetObject(_json, _name)->valuedouble;
    }
    template<>
    std::string Get<std::string>(cJSON* _json, std::string _name){
        return ujson::GetObject(_json, _name)->valuestring;
    }
    template<>
    Json Get<Json>(cJSON* _json, std::string _name){
        Json json;
        json.member = ujson::GetObject(_json, _name);
        return json;
    }
}*/

#endif