#include "ufo_pge.h"
#include "ufo_engine_main.h"

UFO_PixelGameEngine::UFO_PixelGameEngine()
{
    sAppName = "UFO-Cells";
}

bool UFO_PixelGameEngine::OnUserCreate(){
    return ufo_engine_main->OnMainReady();
}

bool UFO_PixelGameEngine::OnUserUpdate(float fElapsedTime){
    return ufo_engine_main->OnMainUpdate(fElapsedTime);
}