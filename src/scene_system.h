#ifndef SCENE_SYSTEM_H
#define SCENE_SYSTEM_H
#include <vector>
#include <memory>
#include "scene.h"
#include <string>

class SceneSystem{
public:
    SceneSystem() = default;
    std::vector<std::unique_ptr<Scene>> scenes;

    template<typename tScene, typename ...tArgs>
    tScene* NewScene(tArgs ... _args){
        std::unique_ptr<tScene> scene = std::make_unique<tScene>(_args...);
        tScene* scene_raw = scene.get();
        scene->scene_system = this;
        scenes.push_back(std::move(scene));
        return scene_raw;
    }

    template<typename tScene, typename ...tArgs>
    tScene* LoadScene(std::string _path, tArgs ... _args){
        std::unique_ptr<tScene> scene = std::make_unique<tScene>(_args...);
        tScene* scene_raw = scene.get();
        scene->scene_system = this;
        scene->Load(_path);
        scenes.push_back(std::move(scene));
        return scene_raw;
    }

    template<typename tScene, typename ...tArgs>
    void ReplaceScene(tArgs ..._args){
        scenes.pop_back();
        scenes.push_back(_args...);
    }
    
    void GotoScene(std::string _scene_name);
    void RemoveActiveScene();

    Scene* GetActiveScene();

    void Update();
};

#endif