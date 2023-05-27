cmake_minimum_required(VERSION 3.5)

project(Image-Editor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
set(OpenCV_DIR "C:/prog/opencv/opencv-4.2.0-build2/install/x64/mingw/lib")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

set(TS_FILES Image-Editor_en_ZA.ts)
set(CLASSES_DIR ./Classes)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        layerwidget.h layerwidget.cpp layerwidget.ui
        toolswidget.h toolswidget.cpp toolswidget.ui

        figurecontainer.h figurecontainer.cpp figurecontainer.ui
        figurecontent.h figurecontent.cpp #figurecontent.ui
        figureframe.h figureframe.cpp #figureframe.ui

        Popups/ResizePopup/resizepopup.h Popups/ResizePopup/resizepopup.cpp Popups/ResizePopup/resizepopup.ui
        Popups/LightenPopup/lightenpopup.h Popups/LightenPopup/lightenpopup.cpp Popups/LightenPopup/lightenpopup.ui
        Popups/CannyPopup/cannypopup.h Popups/CannyPopup/cannypopup.cpp Popups/CannyPopup/cannypopup.ui

        ${CLASSES_DIR}/LayerManager/LayerManager.h ${CLASSES_DIR}/LayerManager/LayerManager.cpp
        ${CLASSES_DIR}/ImageTransformer/ImageTransformer.h ${CLASSES_DIR}/ImageTransformer/ImageTransformer.cpp

        res.qrc
        ${TS_FILES}
)

# headerbar.h headerbar.cpp headerbar.ui

find_package( OpenCV REQUIRED )
include_directories(${OpenCV_INCLUDE-DIRECTORIES})
#I added this line because the compiler could not find the header when promoting a widget
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Image-Editor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Image-Editor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(Image-Editor SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Image-Editor
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(Image-Editor PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        ${OpenCV_LIBS}
)
#target_link_libraries(Image-Editor ${OpenCV_LIBS})

set_target_properties(Image-Editor PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Image-Editor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Image-Editor)
endif()
