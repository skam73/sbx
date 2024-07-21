cmake_minimum_required(VERSION 3.18)    # требуемая версия cmake
project(
    hw07                                # название проекта
    VERSION 0.0.1                       # номер версии проекта
    DESCRIPTION "hw07"             # описание
    LANGUAGES CXX                       # язык программирования
)
set(CMAKE_CXX_STANDARD 17)              # устанавливаем требуемый стандарт языка (это значит, что в проекте буду использоваться фичи этоо стандарта)
set(CMAKE_CXX_STANDARD_REQUIRED ON)     # при сборке платформа будет проверять поддержку стандарта C++17 компилятором

#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(matrix)
add_subdirectory(app)