cmake_minimum_required(VERSION 3.18)    # требуемая версия cmake
project(
    matrix                           # название проекта
    VERSION 0.0.1                       # номер версии проекта
    DESCRIPTION "matrixlib"             # описание
    LANGUAGES CXX                       # язык программирования
)
set(CMAKE_CXX_STANDARD 17)              # устанавливаем требуемый стандарт языка (это значит, что в проекте буду использоваться фичи этоо стандарта)
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # при сборке платформа будет проверять поддержку стандарта C++17 компилятором

set(CMAKE_BUILD_TYPE Debug)             # конфигурация сборки - Debug

set(MATH_USE_DOUBLE_PRESION "Use double presion" ON)


set(sources # создаем cmake-переменную sources, которая содержит список файлов исходного когда (в данном случае main.cpp)
    src/matrix.h
    src/matrix.cpp

    src/export.h

    src/c/c_api.h
    src/c/c_api.cpp
)

#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
#set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)


include(GenerateExportHeader)

add_library(matrixlib_static STATIC ${sources})    # эта команда сообщает платформе сборке, что код будет компилироваться в статическую библиотеку с названием lesson3.lib

target_include_directories(matrixlib_static
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
)

#убрать префикс (lib)static-matrix
set_target_properties(matrixlib_static PROPERTIES PREFIX "")

target_compile_definitions(
    matrixlib_static
    PUBLIC
        MATH_STATIC_DEFINE
        "$<$<BOOL:$(MATH_USE_DOUBLE_PRESION)>:MATH_DOUBLE_PREC_DEFINE>" 
)

generate_export_header(
    matrixlib_static
    EXPORT_FILE_NAME "${PROJECT_BINARY_DIR}/export_static.h"
    BASE_NAME matrixlib
)

add_library(matrixlib SHARED ${sources}) 

target_include_directories(matrixlib
    PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
)

target_compile_definitions(
    matrixlib
    PUBLIC
        "$<$<BOOL:$(MATH_USE_DOUBLE_PRESION)>:MATH_DOUBLE_PREC_DEFINE>" 
)

set_target_properties(matrixlib PROPERTIES PREFIX "")

generate_export_header(
    matrixlib
    EXPORT_FILE_NAME "${PROJECT_BINARY_DIR}/export_shared.h"
    BASE_NAME matrixlib
)


#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)



