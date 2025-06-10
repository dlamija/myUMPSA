cmake_minimum_required(VERSION 3.16)

project(myUMPSA VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Network WebEngineWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Network WebEngineWidgets)

# Add frmservlet.jnlp to resources
set(RESOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/frmservlet.jnlp"
    "${CMAKE_CURRENT_SOURCE_DIR}/source.jnlp"
)

set(PROJECT_SOURCES
        main.cpp
        myumpsa.cpp
        myumpsa.h
        myumpsa.ui
        staff.h
        staff.cpp
)

# Set properties for resource files
set_source_files_properties(${RESOURCE_FILES}
    PROPERTIES MACOSX_PACKAGE_LOCATION "Resources"
)

# NOTE: Don't include the path in MACOSX_BUNDLE_ICON_FILE -- this is
# the property added to Info.plist
set(MACOSX_BUNDLE_ICON_FILE icon2.icns)

# And this part tells CMake where to find and install the file itself
set(APP_ICON_MACOSX "${CMAKE_CURRENT_SOURCE_DIR}/images/icon2.icns")
set_source_files_properties(${APP_ICON_MACOSX} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(myUMPSA
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${APP_ICON_MACOSX}
        ${RESOURCE_FILES}
        Resources.qrc
        ecommumpsa.h ecommumpsa.cpp
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET myUMPSA APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(myUMPSA SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(myUMPSA
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(myUMPSA PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::WebEngineWidgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.myUMPSA)
endif()
set_target_properties(myUMPSA PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS myUMPSA
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(myUMPSA)
endif()
