cmake_minimum_required(VERSION 3.16)        # требуема версия cmake
project(
    lesson9                                 # название проекта
    VERSION 0.0.0
    DESCRIPTION "09 project"                # Описание
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)                  # устанавливаем требуемый стандарт языка
set(CMAKE_CXX_STANDARD_REQUIRED ON)         # при сборке платформа будет проверять поддержку стандарта C++17 компилятора

set(CMAKE_BUILD_TYPE Debug)                 # конфигурация сборки - Debug


add_executable(app)                         # код еомпилирутся в исполняемый файл lesson3

set(sources 
    main.cpp
)

target_sources(app PRIVATE ${sources}) #команда указыват компилятору, что исполняемый файл будет компилироваться из исходников(sources)
