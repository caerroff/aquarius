cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(Debug "Debug" OFF)
if(${Debug})
add_compile_definitions(DEBUG)
endif()


include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG yaml-cpp-0.7.0 # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)
FetchContent_MakeAvailable(yaml-cpp)


add_executable(aquarius src/main.cpp)

add_subdirectory(src/UI)
add_subdirectory(src/Collidables)
add_subdirectory(src/Managers)
add_subdirectory(src/Editor)


target_include_directories(aquarius PUBLIC src/UI)
target_include_directories(aquarius PUBLIC src/Collidables)
target_include_directories(aquarius PUBLIC src/Managers)

target_link_libraries(aquarius PUBLIC yaml-cpp::yaml-cpp)
target_link_libraries(aquarius PRIVATE sfml-graphics)
target_link_libraries(aquarius PRIVATE sfml-audio)
target_link_libraries(aquarius PUBLIC ui)
target_link_libraries(aquarius PUBLIC collidables)
target_link_libraries(aquarius PUBLIC managers)
target_compile_features(aquarius PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET aquarius
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:aquarius>
        VERBATIM)
endif()
