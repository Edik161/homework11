# CMakeList.txt: файл проекта CMake верхнего уровня; проведите глобальную конфигурацию
# и включите сюда подпроекты.
cmake_minimum_required (VERSION 3.8)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("Homework11")

cmake_minimum_required(VERSION 3.10)
project(Homework11 LANGUAGES CXX)

# Добавляем исполняемый файл ТОЛЬКО ОДИН РАЗ
add_executable(${PROJECT_NAME}
    Homework11/Homework11.cpp
    # Другие исходные файлы...
)

# Настройки GSL (если используется)
if(EXISTS "${CMAKE_SOURCE_DIR}/extern/GSL")
    target_include_directories(${PROJECT_NAME} PRIVATE extern/GSL/include)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)