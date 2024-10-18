cmake_minimum_required(VERSION 3.25.1)
PROJECT(queue_system)

set(CMAKE_CXX_STANDARD 26)

if(${MSVC})
#    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:WinMainCRTStartup")
endif()

find_package(wxWidgets CONFIG REQUIRED)

file(GLOB_RECURSE sources src/*.cpp)

add_executable(queue_system ${sources})
target_include_directories(queue_system PRIVATE
        src
)
target_link_libraries(queue_system PRIVATE wx::core)

if(UNIX)
    target_link_libraries(queue_system PRIVATE X11)
endif()
