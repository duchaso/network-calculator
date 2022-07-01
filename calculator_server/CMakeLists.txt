cmake_minimum_required(VERSION 3.14)

project(calculator_server LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt5 REQUIRED COMPONENTS Network)

add_executable(calculator_server
  main.cpp
  server.h server.cpp
  calculator.h calculator.cpp
)
#target_link_libraries(calculator_server PRIVATE Qt5::Network)
target_link_libraries(calculator_server Qt${QT_VERSION_MAJOR}::Core Qt5::Network)
