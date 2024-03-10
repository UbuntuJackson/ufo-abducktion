#ifndef UFO_ENGINE_MAIN
#define UFO_ENGINE_MAIN
#include "ufo_pge.h"
#include "scene_system.h"
class UFO_EngineMain{
public:
    SceneSystem scene_system;
    
    UFO_EngineMain() = default;
    UFO_EngineMain(int _w, int _h, int _pw, int _ph, bool _v_sync = false);
    virtual bool Start(int _w, int _h, int _pw, int _ph, bool _v_sync = false);
    virtual bool OnMainReady();
    virtual bool OnMainUpdate(float _delta_time);
};

#endif