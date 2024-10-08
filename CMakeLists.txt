cmake_minimum_required(VERSION 3.30.3 FATAL_ERROR)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "0e5b6991-d74f-4b3d-a41c-cf096e0b2508")
set(CMAKE_CXX_MODULE_STD ON)

project(
 DamathZero
  DESCRIPTION "AlphaZero for Damath"
  VERSION 1.0.0
  LANGUAGES CXX
)

include(FetchContent)

FetchContent_Declare(
  SFML
  GIT_REPOSITORY "https://github.com/SFML/SFML.git"
  GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(
  Torch
  URL "https://download.pytorch.org/libtorch/cpu/libtorch-macos-arm64-2.4.1.zip"
)
FetchContent_MakeAvailable(Torch)

list(APPEND CMAKE_PREFIX_PATH "${torch_SOURCE_DIR}")

find_package(Torch REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")

add_executable(${CMAKE_PROJECT_NAME} WIN32 MACOSX_BUNDLE src/main.cc)

target_sources(
 ${CMAKE_PROJECT_NAME}
  PRIVATE
   FILE_SET CXX_MODULES FILES
    src/app/app.cc
    src/game/damath.cc
    src/game/game.cc
    src/game/tictactoe.cc
    src/mcts/tree.cc
    src/neural/network.cc
)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE src)
target_compile_features(${CMAKE_PROJECT_NAME} PRIVATE cxx_std_23)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE sfml-graphics ${TORCH_LIBRARIES})

include(GNUInstallDirs)

install(
  TARGETS ${CMAKE_PROJECT_NAME}
   BUNDLE DESTINATION .
   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
 )

set(SHARED_STATIC_ASSETS assets/fonts/Akrobat-Black.ttf)

if (CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  set(MACOSX_STATIC_ASSETS ${SHARED_STATIC_ASSETS} assets/icons/icon.icns)
  set_source_files_properties(${MACOSX_STATIC_ASSETS}
    PROPERTIES MACOSX_PACKAGE_LOCATION ${CMAKE_INSTALL_DATADIR})
  target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${MACOSX_STATIC_ASSETS} src/utils/resource.mm)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE "-framework Foundation")

  string(TIMESTAMP CURR_YEAR "%Y")
  set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    INSTALL_RPATH @executable_path/../Frameworks
    RESOURCE "${MACOSX_STATIC_ASSETS}"
    MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/assets/manifests/Info.plist"
    MACOSX_BUNDLE_BUNDLE_VERSION "${BUILD_VERSION}"
    MACOSX_BUNDLE_SHORT_VERSION_STRING "${PROJECT_VERSION}"
    MACOSX_BUNDLE_GUI_IDENTIFIER "${CMAKE_PROJECT_NAME}"
    XCODE_ATTRIBUTE_PRODUCT_BUNDLE_IDENTIFIER "${CMAKE_PROJECT_NAME}"
    MACOSX_BUNDLE_COPYRIGHT "(c) ${CURR_YEAR} Daniel David N. Bador"
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "")

  set(CPACK_GENERATOR TGZ DragNDrop)
endif()

# Base package settings
set(CPACK_PACKAGE_VENDOR ${CMAKE_PROJECT_NAME})
set(CPACK_PACKAGE_DIRECTORY distribution)
set(CPACK_PACKAGE_INSTALL_DIRECTORY ${CPACK_PACKAGE_NAME})
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR ${CMAKE_PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${CMAKE_PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${CMAKE_PROJECT_VERSION_PATCH})
set(CPACK_VERBATIM_VARIABLES YES)
set(CPACK_MONOLITHIC_INSTALL TRUE)

# macOS settings for DragNDrop generator
set(CPACK_DMG_SLA_USE_RESOURCE_FILE_LICENSE OFF)
set(CPACK_DMG_VOLUME_NAME "${CMAKE_PROJECT_NAME}")
set(CPACK_DMG_BACKGROUND_IMAGE "${CMAKE_CURRENT_LIST_DIR}/assets/dmg/AppDMGBackground.tiff")
set(CPACK_DMG_DS_STORE_SETUP_SCRIPT "${CMAKE_CURRENT_LIST_DIR}/assets/dmg/AppDMGSetup.scpt")
set(CPACK_PACKAGE_ICON "${CMAKE_CURRENT_LIST_DIR}/assets/dmg/volume.icns")

include(CPack)
