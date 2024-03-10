#ifndef BEAN_POOL_H
#define BEAN_POOL_H
#include "pool.h"
#include "console.h"
#include "asset_manager.h"

struct Bean{
public:
    int price;
    int colour;
    int length;
    Bean(
    int _price,
    int _colour,
    int _length
    ) :
    price{_price},
    colour{_colour},
    length{_length}{}
private:
    int id;
public:
    void SetID(int _id){id = _id;}
};

template<typename tScene>
struct BeanPool : public Pool<Bean, tScene>{
using Base = Pool<Bean,tScene>;
private:
    void OnUpdate(Bean* _actor){
        _actor->price++;
        std::cout << _actor->price << std::endl;
    }
    void OnLoad(Json _json){
        Console::Out("loading");
        if(!(_json.GetAsString("name") == "Bean")) return;
        Base::NewActor(
            _json.GetAsInt("price"),
            _json.GetAsInt("colour"),
            _json.GetAsInt("length"));
    }
};

#endif