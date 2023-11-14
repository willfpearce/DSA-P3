#pragma once

#include "imgui.h"
#include "params.h"

class UseImgui {
private:
    bool show_demo_window;
    bool show_another_window;
    ImVec4 clear_color;
    ImGuiIO* io;
    void ResetDevice();

    Params params;
public:
    UseImgui(Params params);
    void Update(bool& done);
    void Render();
    ~UseImgui();
};
