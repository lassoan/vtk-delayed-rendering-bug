cmake_minimum_required(VERSION 3.3 FATAL_ERROR)

if(POLICY CMP0020)
  cmake_policy(SET CMP0020 NEW)
  cmake_policy(SET CMP0071 NEW)
endif()

project(renderbug)

find_package(VTK COMPONENTS  
  vtkCommonColor
  vtkCommonCore
  vtkFiltersCore
  vtkFiltersSources
  vtkInfovisCore
  vtkInteractionStyle
  vtkRenderingContextOpenGL2
  vtkRenderingCore
  vtkRenderingFreeType
  vtkRenderingGL2PSOpenGL2
  vtkRenderingOpenGL2
  vtkViewsQt
  QUIET
)

message (STATUS "VTK_VERSION: ${VTK_VERSION}")

if(vtkGUISupportQt_LOADED OR TARGET VTK::GUISupportQt)
  if (VTK_VERSION VERSION_LESS "8.90.0")
    # Instruct CMake to run moc automatically when needed.
    set(CMAKE_AUTOMOC ON)
  else()
     # Instruct CMake to run moc automatically when needed.
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
  endif()
  # We have ui files, this will bring in the macro: qt5_wrap_ui
  find_package(Qt5Widgets REQUIRED QUIET)
else()
  message(STATUS "GuiSupportQt not found.")
  return()
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB UI_FILES )
file(GLOB QT_WRAP )
file(GLOB CXX_FILES renderbug.cpp)

qt5_wrap_ui(UISrcs ${UI_FILES})

if (VTK_VERSION VERSION_LESS "8.90.0")
  # old system
  include(${VTK_USE_FILE})
  # CMAKE_AUTOMOC in ON so the MOC headers will be automatically wrapped.
  add_executable(renderbug MACOSX_BUNDLE
    ${CXX_FILES} ${UISrcs} ${QT_WRAP})
  qt5_use_modules(renderbug Core Gui)
  target_link_libraries(renderbug ${VTK_LIBRARIES})
else()
  # CMAKE_AUTOMOC in ON so the MOC headers will be automatically wrapped.
  add_executable(renderbug MACOSX_BUNDLE
    ${CXX_FILES} ${UISrcs} ${QT_WRAP})
  qt5_use_modules(renderbug Core Gui)
  target_link_libraries(renderbug ${VTK_LIBRARIES})
  # vtk_module_autoinit is needed
  vtk_module_autoinit(
    TARGETS renderbug
    MODULES ${VTK_LIBRARIES}
  )
endif()
