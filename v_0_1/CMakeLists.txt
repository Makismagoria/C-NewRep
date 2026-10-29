cmake_minimum_required(VERSION 3.16) # Минимальная версия CMake, которая должна понимать этот файл.
project(UlLinkAdaptation CXX) # название проекта, CXX - язык C++

set(CMAKE_CXX_STANDARD 17) #  Стандарт языка C++, по которому компилируется код: C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON) # Стандарт обязателен: если компилятор не умеет C++17
set(CMAKE_CXX_EXTENSIONS OFF) # Без расширений компилятора: флаг -std=c++17 вместо -std=gnu++17.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)# Создать файл build/compile_commands.json со списком точных команд компиляции.

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release) # Тип сборки по умолчанию — Release
endif()

add_executable(simulaTron main.cpp Sinr.cpp TransmissionGenerator.cpp MeasureSinr.cpp LinkAdapt.cpp Reception.cpp) #   simulaTron — имя итогового файла 
target_compile_options(simulaTron PRIVATE -Wall -Wextra -Wpedantic) # исходный файл. Путь считается от папки с этим CMakeLists.txt