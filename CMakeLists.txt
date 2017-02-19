cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

project(license-validator)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

set(QT_MIN_VERSION "5.5.0")
find_package(Qt5 ${QT_MIN_VERSION} REQUIRED COMPONENTS Core Quick Widgets)

qt5_add_resources(qml_QRC ${CMAKE_SOURCE_DIR}/src/ui/qml.qrc)

set(license_validator_SRCS src/validate.cpp src/main.cpp)
add_executable(validator ${license_validator_SRCS} ${qml_QRC})
target_link_libraries(validator
    Qt5::Qml
    Qt5::Core
    Qt5::Quick
    Qt5::Widgets
)

install(TARGETS validator DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
