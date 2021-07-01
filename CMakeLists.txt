
cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 11)

project(Tables)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Widgets REQUIRED)

set(SRC
    ${PROJECT_SOURCE_DIR}/LayMaterials.cpp
    ${PROJECT_SOURCE_DIR}/LayMaterials.h
    ${PROJECT_SOURCE_DIR}/LayMaterials.ui
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/NewComposite.cpp
    ${PROJECT_SOURCE_DIR}/NewComposite.h
    ${PROJECT_SOURCE_DIR}/NewComposite.ui
    ${PROJECT_SOURCE_DIR}/PeriodicTable.cpp
    ${PROJECT_SOURCE_DIR}/PeriodicTable.h
    ${PROJECT_SOURCE_DIR}/PeriodicTable.ui
    ${PROJECT_SOURCE_DIR}/REMP_OR_PERENOS.cpp
    ${PROJECT_SOURCE_DIR}/REMP_OR_PERENOS.h
    ${PROJECT_SOURCE_DIR}/REMP_OR_PERENOS.ui
    ${PROJECT_SOURCE_DIR}/Tables.cpp
    ${PROJECT_SOURCE_DIR}/Tables.h
    ${PROJECT_SOURCE_DIR}/Tables.ui
)

add_executable(${PROJECT_NAME} WIN32 ${SRC})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

# Installation
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
