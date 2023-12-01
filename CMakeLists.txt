cmake_minimum_required(VERSION 3.8)

project(SortingVisualizer)

add_executable(SortingVisualizer
    SortingVisualizer/SortingVisualizer.cpp
    SortingVisualizer/UseImgui.cpp
    SortingVisualizer/DX9Window.cpp
    SortingVisualizer/proc.cpp
    imgui/imgui.cpp imgui/imgui_impl_win32.cpp
    imgui/imgui_impl_dx9.cpp
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    SortingVisualizer/SortingAlgorithm.cpp
    SortingVisualizer/ShellSort.cpp SortingVisualizer/QuickSort.cpp)

target_include_directories(SortingVisualizer PRIVATE ${CMAKE_SOURCE_DIR}/imgui)

target_link_libraries(SortingVisualizer d3dcompiler dwmapi libd3dx9.a libd3d9.a)
