cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
set(PROJECT scratcher)
project(${PROJECT})

set(CMAKE_CXX_FLAGS
    "-Wall -fPIC -std=c++11 -DQT_NO_VERSION_TAGGING -rdynamic"
)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Core Multimedia Widgets REQUIRED)

include_directories(
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Multimedia_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
)

# Генерировать moc-файлы автоматически
set(CMAKE_AUTOMOC ON)

set(SOURCES
    main.cpp
    src/application.cpp
    src/audio_player.cpp
)

add_executable(${PROJECT} ${SOURCES})

# Libs
set(LIBRARIES
    Qt5::Core
    Qt5::Multimedia
)

target_link_libraries (${PROJECT} ${LIBRARIES})
