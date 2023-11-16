#pragma once

#include "imgui.h"
#include "params.h"

class UseImgui {
private:
    ImGuiIO* io;
    void ResetDevice();

    Params params;
public:
    UseImgui(Params params);
    void Update(bool& done);
    void Render();
    ~UseImgui();
};
