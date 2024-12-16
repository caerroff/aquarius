cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
fetchcontent_declare(SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM)
fetchcontent_makeavailable(SFML)

fetchcontent_declare(yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG yaml-cpp-0.7.0 # Can be a tag (yaml-cpp-x.x.x), a commit hash, or a branch name (master)
)
fetchcontent_makeavailable(yaml-cpp)

add_library(collidables STATIC
  src/CollisionEntity.cpp
  src/Character.cpp
  src/Player.cpp
  src/Item.cpp
)
target_link_libraries(collidables PUBLIC yaml-cpp::yaml-cpp)
target_link_libraries(collidables PRIVATE sfml-graphics)
target_link_libraries(collidables PRIVATE sfml-audio)
target_include_directories(collidables PRIVATE ../UI)
target_link_libraries(collidables PRIVATE ui)
target_compile_features(collidables PRIVATE cxx_std_17)

if(WIN32)
  add_custom_command(
    TARGET collidables
    COMMENT "Copy OpenAL DLL"
    PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:collidables>
    VERBATIM)
endif()
