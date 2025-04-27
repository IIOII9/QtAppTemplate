cmake_minimum_required(VERSION 3.16)
# 设置默认构建类型为 RelWithDebInfo（如果没有通过命令行传入）
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Build type" FORCE)
endif()

project(QtGuiApp VERSION 1.0 LANGUAGES CXX)

#配置内存泄漏AddressSanitizer 
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
# set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fsanitize=address")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "C:/msys64/mingw64")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC OFF)
set(CMAKE_AUTOUIC OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)  # 可执行文件输出到 bin 目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # 静态库输出到 lib 目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)  # 动态库输出到 lib 目录

find_package(Qt5 REQUIRED COMPONENTS Widgets)

# FFMPeg相关模块
find_package(PkgConfig REQUIRED)
pkg_check_modules(FFMPEG REQUIRED IMPORTED_TARGET
  libavformat
  libavcodec
  libavutil
  libswscale
)

# 添加源文件
add_executable(QtGuiApp
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
)

# 链接 Qt 和 FFmpeg
target_link_libraries(QtGuiApp PRIVATE
  Qt5::Widgets
  PkgConfig::FFMPEG
)

# 防止弹出命令行窗口
set_target_properties(QtGuiApp PROPERTIES WIN32_EXECUTABLE ON)

# 自定义命令：在构建完成后自动执行 windeployqt
# add_custom_command(
#     TARGET QtGuiApp POST_BUILD
#     COMMAND windeployqt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/QtGuiApp.exe
#     COMMENT "Running windeployqt to deploy the application"
# )