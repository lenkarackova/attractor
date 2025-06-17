cmake_minimum_required(VERSION 3.16)

project(AttractorExplorer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick Quick3D QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appAttractorExplorer
    main.cpp
)

qt_policy(SET QTP0004 NEW)

qt_add_qml_module(appAttractorExplorer
    URI AttractorExplorer
    VERSION 1.0
    QML_FILES
        ui/Main.qml
        ui/components/AccordionItem.qml
        ui/components/GradientRectangle.qml
    IMPORTS
        QtQuick3D
    RESOURCES
        resource/qml.qrc
    SOURCES
        src/include/Attractor.h src/Attractor.cpp src/include/Attractor.inl
        src/include/AttractorData.h
        src/include/AttractorSystems.h src/AttractorSystems.cpp
        src/include/PointCloud.h src/PointCloud.cpp
        src/include/Vertex.h src/Vertex.cpp
        src/include/helpers.h
        src/include/ColorViewModel.h src/ColorViewModel.cpp
        src/include/ViewModel.h src/ViewModel.cpp
        src/include/Gradient.h src/Gradient.cpp
        src/include/ParameterListModel.h src/ParameterListModel.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appAttractorExplorer PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appAttractorExplorer
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appAttractorExplorer PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Quick
    Qt::Quick3D
    Qt6::QuickControls2
)

# Add includepaths
target_include_directories(appAttractorExplorer PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/include/)

include(GNUInstallDirs)
install(TARGETS appAttractorExplorer
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
