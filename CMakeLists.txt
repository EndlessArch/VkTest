project(GraphicsTest)
cmake_minimum_required(VERSION 3.17.1)

# add_compile_options(-std=c++17) # Vulkan requires c++17

add_compile_options(-std=c++2a) 

# add_compile_options(-g) # dbg

file(GLOB SOURCE_FILES "*.cpp" "./code/arch/*.cpp")
message("Found Source Files ${SOURCE_FILES}")

add_executable(GraphicsTest ${SOURCE_FILES})
target_include_directories(GraphicsTest PRIVATE /usr/local/Cellar/glfw/3.3.2/include)
target_include_directories(GraphicsTest PRIVATE /usr/local/vulkansdk/macOS/include)
target_link_libraries(GraphicsTest PRIVATE /usr/local/Cellar/glfw/3.3.2/lib/libglfw.3.3.dylib)
target_link_libraries(GraphicsTest PRIVATE /usr/local/vulkansdk/macOS/lib/libvulkan.dylib)
target_link_libraries(GraphicsTest PRIVATE /usr/local/vulkansdk/macOS/lib/libVkLayer_khronos_validation.dylib)
target_link_libraries(GraphicsTest PRIVATE /usr/local/vulkansdk/macOS/lib/libVkLayer_api_dump.dylib)