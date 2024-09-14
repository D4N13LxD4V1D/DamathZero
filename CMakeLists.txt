cmake_minimum_required(VERSION 3.30.3 FATAL_ERROR)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_CXX_MODULE_STD ON)

project(damath.ai VERSION 1.0.0 LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
 SFML
  GIT_REPOSITORY https://github.com/SFML/SFML.git
  GIT_TAG 2.6.x
  GIT_SHALLOW ON
  EXCLUDE_FROM_ALL
  SYSTEM
)
FetchContent_MakeAvailable(SFML)

find_package(Torch REQUIRED)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

if (APPLE)
  add_executable(damath.ai MACOSX_BUNDLE src/main.cc)
else()
  add_executable(damath.ai src/main.cc)
endif()

target_compile_features(damath.ai PRIVATE cxx_std_23)
target_link_libraries(damath.ai PRIVATE sfml-graphics ${TORCH_LIBRARIES})
target_sources(
 damath.ai
  PUBLIC
   FILE_SET CXX_MODULES FILES
    src/app/app.cc
    src/game/damath.cc
    src/game/game.cc
    src/game/tictactoe.cc
    src/mcts/tree.cc
    src/neural/network.cc
)

if(APPLE)
  set_target_properties(
   damath.ai
    PROPERTIES
      BUNDLE true
      MACOSX_BUNDLE_GUI_IDENTIFIER damath.ai
      MACOSX_BUNDLE_BUNDLE_NAME damath.ai
      MACOSX_BUNDLE_BUNDLE_VERSION "1.0.0"
      MACOSX_BUNDLE_SHORT_VERSION_STRING "1.0.0"
      MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_LIST_DIR}/cmake/MacOSXBundleInfo.plist.in
  )
  install(TARGETS damath.ai BUNDLE DESTINATION .)
  install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/assets/ DESTINATION ./assets)
else()
  install(TARGETS damath.ai)
  install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/assets/ DESTINATION ${CMAKE_INSTALL_PREFIX}/assets)
endif()

include(CTest)

include(InstallRequiredSystemLibraries)
include(CPack)

add_custom_command(
  TARGET damath.ai POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_SOURCE_DIR}/assets ${CMAKE_CURRENT_BINARY_DIR}/assets
  DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/assets
)

if (MSVC)
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET example-app
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:example-app>)
endif (MSVC)
