#ifndef MY_SCENE_H
#define MY_SCENE_H
#include "scene.h"
#include "bob.h"
#include "bean_pool.h"
#include <string>
#include "ufo_json.h"
class SceneSystem;

class MyScene : public Scene{
public:
    SceneSystem* scene_system;
    std::string name;
    BeanPool<MyScene> beans;
    MyScene(){
        beans.Initialize(this);
    }
    void
    Update(){
        Scene::Update();
    }

};

#endif