cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(scrather)

# set(REQUIRED_QT_VERSION 5.9.1)
# find_package(Qt5 ${REQUIRED_QT_VERSION}
#     CONFIG REQUIRED
#     Core Multimedia)

find_package(Qt5Multimedia REQUIRED)

# Генерировать moc-файлы автоматически
# set(CMAKE_AUTOMOC ON)

add_executable(scratcher
    main.cpp
)

# target_link_libraries(scratcher Qt5::Multimedia)
