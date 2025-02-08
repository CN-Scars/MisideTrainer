cmake_minimum_required(VERSION 3.5)

project(MisideTrainer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools Network)

set(TRANSLATIONS_DIR "${CMAKE_SOURCE_DIR}/resources/translations")
set(TS_FILES
    ${TRANSLATIONS_DIR}/MisideTrainer_en_US.ts
    ${TRANSLATIONS_DIR}/MisideTrainer_ru_RU.ts
    ${TRANSLATIONS_DIR}/MisideTrainer_zh_CN.ts
)
qt6_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

# 自动查找并包含.qm文件
file(GLOB QM_FILES "${CMAKE_SOURCE_DIR}/resources/translations/*.qm")

# 在构建时将QM文件复制到合适的目录
foreach(QM_FILE ${QM_FILES})
    configure_file(${QM_FILE} ${CMAKE_BINARY_DIR} COPYONLY)
endforeach()

set(PROJECT_SOURCES
    main.cpp
    manager/trainermanager.cpp
    manager/trainermanager.h
    trainer/alternativemenutrainer.cpp
    trainer/alternativemenutrainer.h
    trainer/dairyscandaltrainer.cpp
    trainer/dairyscandaltrainer.h
    trainer/dancefloortrainer.cpp
    trainer/dancefloortrainer.h
    trainer/hetoortrainer.cpp
    trainer/hetoortrainer.h
    trainer/penguinpilestrainer.cpp
    trainer/penguinpilestrainer.h
    trainer/trainer.cpp
    trainer/trainer.h
    ui/mainwindow.cpp
    ui/mainwindow.h
    ui/mainwindow.ui
    utils/processmonitor.cpp
    utils/processmonitor.h
)

set(app_icon_resource_windows "${CMAKE_SOURCE_DIR}/resources/icons/app_icon.rc")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)

    qt_add_executable(MisideTrainer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        # 需要通过项目构建自动生成.ts文件时取消注释下面一行
        ${QM_FILES}
        resources/resources.qrc
        ${app_icon_resource_windows}
    )

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MisideTrainer APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

else()
    if(ANDROID)
        add_library(MisideTrainer SHARED
            ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MisideTrainer
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(MisideTrainer PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network)

target_include_directories(MisideTrainer PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/manager
    ${CMAKE_CURRENT_SOURCE_DIR}/trainer
    ${CMAKE_CURRENT_SOURCE_DIR}/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MisideTrainer)
endif()
set_target_properties(MisideTrainer PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS MisideTrainer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MisideTrainer)
endif()
