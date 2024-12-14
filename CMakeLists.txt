cmake_minimum_required(VERSION 3.15)
project(ADHDPhotoOrganizer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Try to find Qt6 first, fallback to Qt5
find_package(Qt6 COMPONENTS Core Sql Widgets QUIET)
if (Qt6_FOUND)
    set(QT_VERSION_MAJOR 6)
    set(QtCore_LIB Qt6::Core)
    set(QtSql_LIB Qt6::Sql)
    set(QtWidgets_LIB Qt6::Widgets)
else ()
    find_package(Qt5 COMPONENTS Core Sql Widgets REQUIRED)
    set(QT_VERSION_MAJOR 5)
    set(QtCore_LIB Qt5::Core)
    set(QtSql_LIB Qt5::Sql)
    set(QtWidgets_LIB Qt5::Widgets)
endif ()

message(STATUS "Using Qt${QT_VERSION_MAJOR}")
find_package(exiv2 REQUIRED)
# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)

# Add the source files
set(SOURCES
        main.cpp
        organizer.cpp
        )

# Add header files
set(HEADERS
        organizer.h
        )

# Add executable
add_executable(${PROJECT_NAME}
        ${SOURCES}
        ${HEADERS}
        #ui/mainwindow.ui
        )

# Link Qt libraries
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${QtCore_LIB}
        ${QtWidgets_LIB}
        exiv2
        )
# Copy SQL files to the runtime directory
#add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_SOURCE_DIR}/sql $<TARGET_FILE_DIR:${PROJECT_NAME}>/sql
#       )
