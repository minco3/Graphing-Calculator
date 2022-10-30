cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(Graphing_Calculator)


# place binaries and libraries according to GNU standards
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})



if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()
#. . . . . . . . . . . . . . . . . . . .

# ------------------------------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)
 
enable_testing() 


# ------------------------------------



#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
#   Grab all cpp files from includes folder
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
set(INCLUDES_FOLDER includes)
FILE(GLOB_RECURSE SOURCE_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}   "${INCLUDES_FOLDER}/*.cpp" )
#- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 



ADD_EXECUTABLE(main
    main.cpp
    ${SOURCE_FILES}
)

ADD_EXECUTABLE(myTest
    _tests/_test_files/myTest.cpp
    ${SOURCE_FILES}
)

ADD_EXECUTABLE(randomSquares
_side_projects/_side_project_files/randomSquares.cpp
${SOURCE_FILES}
)

ADD_EXECUTABLE(bouncingBalls
    _side_projects/_side_project_files/bouncingBalls.cpp
    ${SOURCE_FILES}
)

ADD_EXECUTABLE(bouncingBallsSidePanel
    _side_projects/_side_project_files/bouncingBallsSidePanel.cpp
    ${SOURCE_FILES}
)

TARGET_LINK_LIBRARIES(myTest gtest)


set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(main ${SFML_LIBRARIES})
    target_link_libraries(randomSquares ${SFML_LIBRARIES})
    target_link_libraries(bouncingBalls ${SFML_LIBRARIES})
    target_link_libraries(bouncingBallsSidePanel ${SFML_LIBRARIES})
endif()
