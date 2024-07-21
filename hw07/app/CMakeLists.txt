cmake_minimum_required(VERSION 3.18) # требуемая версия cmake
project(
    app # название проекта
    VERSION 0.0.0 # номер версии проекта
    DESCRIPTION "Home work 07" # описание
    LANGUAGES CXX # язык программирования
)
set(CMAKE_CXX_STANDARD 17) # устанавливаем требуемый стандарт языка (это значит, что в проекте буду использоваться фичи этоо стандарта)
set(CMAKE_CXX_STANDARD_REQUIRED ON) # при сборке платформа будет проверять поддержку стандарта C++17 компилятором

set(CMAKE_BUILD_TYPE Debug) # конфигурация сборки - Debug

add_executable(app) # эта команда сообщает платформе сборке, что код будет компилироваться в исполняемый файл с названием lesson3.exe

set(sources  main.cpp)

target_sources(app PRIVATE ${sources}) # команда указывает компилятору, что исполняемый файл будет компилироваться из исходников, перечисленных в sources

target_link_libraries(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/matrix/matrixlib.so)
