cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)


set(project "1_iteration_cmake")
project(${project})

set(${project}_SOURCES
        main.cpp)

add_subdirectory(ExpenseTrackerLib)

set(${project}_SOURCE_LIST
        ${${project}_SOURCES})

add_executable(${project}
        ${${project}_SOURCE_LIST} "ExpenseTrackerLib/ExpenseTracker.h" "ExpenseTrackerLib/ExpenseTracker.cpp")

target_link_libraries(${project} ExpenseTrackerLib)


configure_file(${CMAKE_CURRENT_SOURCE_DIR}/categories.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)