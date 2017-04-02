cmake_minimum_required(VERSION 3.0)
project(VisualSort)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14 -fno-exceptions -fno-rtti -DELEMENT_COUNT=75 -DINTERNAL=static -DGLOBAL=static")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -DDEBUG=1")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -flto")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} ${CMAKE_CXX_FLAGS_DEBUG} ${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(SOURCE_FILES src/Renderer.cpp src/InsertionSort.cpp src/SelectionSort.cpp src/BubbleSort.cpp src/QuickSort.cpp src/audio.c src/main.cpp)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR})

add_executable(VisualSort ${SOURCE_FILES})
target_link_libraries(VisualSort ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})

add_custom_command(TARGET VisualSort PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/OpenSans-Regular.ttf $<TARGET_FILE_DIR:VisualSort>)

add_custom_command(TARGET VisualSort PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/BrokeForFree.wav $<TARGET_FILE_DIR:VisualSort>)
