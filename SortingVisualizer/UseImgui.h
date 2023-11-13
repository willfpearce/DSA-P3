#pragma once

#include <imgui.h>

class UseImgui {
public:
    void Init();
    virtual void Update();
    void Render();
    void Shutdown();
};
