cmake_minimum_required(VERSION 3.5)

project(renderbug)

find_package(Qt5Widgets REQUIRED)

find_package(VTK 8.2.0 REQUIRED COMPONENTS
    vtkGUISupportQt
    vtkInteractionStyle
    vtkRenderingCore
    vtkRenderingOpenGL2
)

add_executable(renderbug WIN32
    renderbug.cpp
)

target_link_libraries(renderbug PRIVATE
    Qt5::Widgets
    vtkGUISupportQt
    vtkInteractionStyle
    vtkRenderingCore
    vtkRenderingOpenGL2
)

target_include_directories(renderbug SYSTEM PRIVATE
    ${VTK_INCLUDE_DIRS}
)

target_compile_definitions(renderbug PRIVATE
    ${VTK_DEFINITIONS}
)
