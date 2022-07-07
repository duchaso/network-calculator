project(gtests)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(../)


add_executable(gtests_run
    test.cpp
    ../calculator.h ../calculator.cpp
)
target_link_libraries(gtests_run Qt${QT_VERSION_MAJOR}::Core gtest gtest_main)
