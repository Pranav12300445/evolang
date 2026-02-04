cmake_minimum_required(VERSION 3.16)

project(evolang
    VERSION 0.1.0
    DESCRIPTION "Self-learning, evolving programming language"
    LANGUAGES CXX
)

# Force console subsystem on Windows (GLOBAL, not per-target)
if (MINGW)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mconsole")
endif()

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Sources
file(GLOB_RECURSE EVOLANG_SRC
    src/*.cpp
)

add_executable(evolang ${EVOLANG_SRC})

target_include_directories(evolang PRIVATE src)
