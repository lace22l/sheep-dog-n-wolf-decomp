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
        src/File/FileInfo.h
        src/RandomFunctionsIFound.cpp
        #src/main2.cpp
        #src/File/FileFunctions.cpp
        src/Strings/StringFunctions.cpp
        src/Strings/StringFunctions.h
        src/globals.h
        src/Structs/EngineState.h
)


target_include_directories(SheepRaiderDecomp PRIVATE

        resources
)



target_link_libraries(SheepRaiderDecomp


        user32
        gdi32
        kernel32
)