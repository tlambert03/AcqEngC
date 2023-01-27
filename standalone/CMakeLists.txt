cmake_minimum_required(VERSION 3.14...3.22)

project(GreeterStandalone LANGUAGES CXX)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

set(CPM_SOURCE_CACHE $ENV{HOME}/.cache/CPM)
include(../cmake/CPM.cmake)

CPMAddPackage(
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 3.0.0
  OPTIONS "CXXOPTS_BUILD_EXAMPLES NO" "CXXOPTS_BUILD_TESTS NO" "CXXOPTS_ENABLE_INSTALL YES"
)

# CPMAddPackage(
#   NAME MMCore
#   GITHUB_REPOSITORY micro-manager/mmCoreAndDevices
#   GIT_TAG ce92a47dc1b06317756317b1f27d8cbc64b9c412
#   # OPTIONS "CXXOPTS_BUILD_EXAMPLES NO" "CXXOPTS_BUILD_TESTS NO" "CXXOPTS_ENABLE_INSTALL YES"
# )

CPMAddPackage(NAME Greeter SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

include_directories(/Users/talley/dev/forks/mmCoreAndDevices/MMCore/)
LINK_DIRECTORIES(/Users/talley/dev/forks/mmCoreAndDevices/MMCore/.libs)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(${PROJECT_NAME} ${sources})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 14 OUTPUT_NAME "Greeter")

target_link_libraries(${PROJECT_NAME} Greeter::Greeter cxxopts MMCore "-framework CoreFoundation" "-framework IOKit" )