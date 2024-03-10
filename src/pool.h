#ifndef POOL_H
#define POOL_H
#include <functional>
#include <memory>
#include "ufo_json.h"
template<typename tActor, typename tScene>
class Pool{
public:
    int id_count;
    tScene* scene;
    Pool() = default;
    void
    Initialize(tScene* _scene){
        scene = _scene;
        _scene->tasks.push_back([this](){UpdatePool();});
        _scene->load_events.push_back([this](Json _json){OnLoad(_json);});
    }

    std::vector<std::unique_ptr<tActor>> actors;
    template<typename ...tArgs>
    void NewActor(tArgs ...args){
        std::unique_ptr<tActor> actor =  std::make_unique<tActor>(args...);
        actor->SetID(id_count++);
        actors.push_back(std::move(actor));
    }
    void UpdatePool(){
        for(auto &i : actors){
            OnUpdate(i.get());
        }
        for(auto i : scene->events){
            i();
        }
    }
private:
    virtual void OnUpdate(tActor* actor){
        
    }
    virtual void OnLoad(Json _json){
        
    }
    
};
#endif