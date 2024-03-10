#include "my_scene.h"
#include "ufo_engine_main.h"
#include "asset_manager.h"
#include "graphics_provider.h"
#include "../external/olcPixelGameEngine.h"

int main(){

    UFO_EngineMain ue;
    ue.scene_system.LoadScene<MyScene>("../res/scene.json");
    ue.scene_system.GetActiveScene()->events.push_back(
        [](){
            AssetManager::Get().LoadDecal("../res/assets/fireduck.png", "duck");
            return true;
        }
    );
    ue.scene_system.GetActiveScene()->tasks.push_back(
        [](){
            GraphicsProvider::Get().DrawSprite({20,20}, AssetManager::Get().GetSprite("duck"));
        }
    );
    int x;
    int y;
    ue.scene_system.GetActiveScene()->tasks.push_back(
        [&](){
            x += (
                GraphicsProvider().Get().GetKey(olc::Key::D).bHeld -
                GraphicsProvider().Get().GetKey(olc::Key::A).bHeld) * 10;
            y += (
                GraphicsProvider().Get().GetKey(olc::Key::S).bHeld -
                GraphicsProvider().Get().GetKey(olc::Key::W).bHeld) * 10;
            GraphicsProvider::Get().FillCircle(x,y,60);
        }
    );
    ue.Start(400,200,1,1,true);

    return 0;
}