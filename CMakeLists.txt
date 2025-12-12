cmake_minimum_required(VERSION 3.10)
project(DragonFractal)

# Находим FLTK
find_package(FLTK REQUIRED)

# Добавляем исполняемый файл
add_executable(DragonFractal main.cpp)

# Подключаем FLTK
target_include_directories(DragonFractal PRIVATE ${FLTK_INCLUDE_DIRS})
target_link_libraries(DragonFractal ${FLTK_LIBRARIES})