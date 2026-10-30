cmake_minimum_required(VERSION 3.16)

project(jisuanqi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_standard_project_setup()

qt_add_executable(jisuanqi
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
)

target_link_libraries(jisuanqi PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
