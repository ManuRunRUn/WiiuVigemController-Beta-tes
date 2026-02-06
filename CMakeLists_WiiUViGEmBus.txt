cmake_minimum_required(VERSION 3.18)
project(WiiUViGEmBusController)

find_package(PkgConfig REQUIRED)

include(FetchContent)
FetchContent_Declare(
  inih
  URL https://github.com/benhoyt/inih/archive/refs/tags/r58.tar.gz
)
FetchContent_Declare(
  rapidjson
  URL https://github.com/Tencent/rapidjson/archive/refs/heads/master.tar.gz
)
FetchContent_Populate(rapidjson)
FetchContent_MakeAvailable(inih)

add_executable(WiiUViGEmBusController)

target_compile_features(WiiUViGEmBusController PRIVATE cxx_std_20)

target_compile_options(WiiUViGEmBusController PRIVATE
  -Werror
  -Wextra
  -Wshadow
  -Wpedantic
  -Wnull-dereference
  -Wmisleading-indentation
  -Wduplicated-cond
  -Wduplicated-branches
)

target_sources(WiiUViGEmBusController PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/source_custom/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source_custom/console.c
  ${CMAKE_CURRENT_SOURCE_DIR}/source_custom/udp.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source_custom/vpad_to_json.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/source_custom/screen_utils.c
  ${inih_SOURCE_DIR}/ini.c
)

target_include_directories(WiiUViGEmBusController SYSTEM PRIVATE
  ${inih_SOURCE_DIR}
  ${rapidjson_SOURCE_DIR}/include
)

target_include_directories(WiiUViGEmBusController PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/source_custom
)

target_link_libraries(WiiUViGEmBusController PRIVATE
)

wut_create_rpx(WiiUViGEmBusController)

wut_create_wuhb(WiiUViGEmBusController
  CONTENT
  NAME "WiiU ViGEmBus Controller"
  SHORTNAME "ViGEmBus"
  AUTHOR "Custom Build - Based on MiisendU by Crayon"
  ICON "wuhb_custom/icon.png"
  TVSPLASH "wuhb_custom/tv-image.png"
  DRCSPLASH "wuhb_custom/drc-image.png"
)
