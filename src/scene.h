#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include <vector>
#include <memory>
#include <functional>
#include "ufo_json.h"

class Scene{
public:
    Scene() = default;
public:
    typedef std::function<bool()> Event; //Event is a function that the engine will delete if the event returns true
    typedef std::function<void()> Task; //Task is a function that runs during the entire runtime and should not be detached.
    typedef std::function<void(Json _json)> LoadEvent;
    std::vector<Event> events;
    std::vector<Task> tasks;
    std::vector<LoadEvent> load_events;
    virtual ~Scene() = default;
    virtual void Update(){
        std::vector<Event> leftover_events;
        for(int event_index = 0; event_index < events.size(); event_index++){
            if(!events[event_index]()) leftover_events.push_back(events[event_index]);
        }
        events.clear();
        for(Event event : leftover_events) events.push_back(event);
        for(Task task : tasks){
            task();
        }
    }
    virtual void Load(std::string _path){
        Json json = Json::Read(_path);
        std::vector<Json> actor_jsons = json.GetAsArray("actors");
        Console::Out(actor_jsons.size());
        for(auto actor_json : actor_jsons){
            for(LoadEvent event : load_events){
                event(actor_json);
            }
        }
    }
};

#endif