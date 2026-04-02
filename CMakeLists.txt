cmake_minimum_required(VERSION 3.20)
project(SheepRaiderDecomp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(SheepRaiderDecomp WIN32
        src/main.cpp
        src/bitmapUtils.cpp
        src/bitmapUtils.h
        resources/resource.h
        resources/embed_bmp.rc
        resources/launcher.rc
        src/RandomFunctionsIFound.cpp
        #src/main2.cpp
)

add_executable(ImplTracker
        src/tracker.cpp
        src/RandomFunctionsIFound.h
        src/Structs/structs.cpp
)
#target_compile_definitions(ImplTracker PRIVATE
#        SRC_DIR="${CMAKE_SOURCE_DIR}/src/main2.cpp"
#)*/
target_include_directories(SheepRaiderDecomp PRIVATE

        resources
)



target_link_libraries(SheepRaiderDecomp


        user32
        gdi32
        kernel32
)