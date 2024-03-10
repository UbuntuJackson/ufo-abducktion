#include "ufo_engine_main.h"
#include "graphics_provider.h"
UFO_EngineMain::UFO_EngineMain(int _w, int _h, int _pw, int _ph, bool _v_sync){
    //scene_system.NewScene<InfiniteRoom>(); //In a Room you can spawn pretty much anything you want.
    Start(_w, _h, _pw, _ph, _v_sync);
}

bool
UFO_EngineMain::Start(int _w, int _h, int _pw, int _ph, bool _v_sync){
    if(GraphicsProvider::Get().Construct(1600,1000,1,1,false,true,true)){
        GraphicsProvider::Get().ufo_engine_main = this;
        GraphicsProvider::Get().Start();
        return false;
    }
    return true;
}

bool
UFO_EngineMain::OnMainReady(){
    return true;
}

bool
UFO_EngineMain::OnMainUpdate(float _delta_time){
    GraphicsProvider::Get().Clear(olc::GREY);
    GraphicsProvider::Get().SetPixelMode(olc::Pixel::NORMAL);
    scene_system.Update();
    return true;
}