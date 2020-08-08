project(GraphicsTest)
cmake_minimum_required(VERSION 3.17.1)

# add_compile_options(-std=c++17) # Vulkan requires c++17
add_compile_options(-std=c++2a) 

# add_compile_options(-g) # dbg

# add_compile_options(-v) # inf

file(GLOB SOURCE_FILES "*.cpp" "./src/code/arch/*.cpp")
message("Found Source Files ${SOURCE_FILES}")

add_executable(GraphicsTest ${SOURCE_FILES})

### -- REQUIRED -- ###
set(GLFW_LIBRARY_DIR /usr/local/Cellar/glfw/3.3.2)
set(VULKAN_DIR /usr/local/vulkansdk/macOS)

set(VKLAYER_API_DUMP_FLAG FALSE)

####

target_include_directories(GraphicsTest PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_include_directories(GraphicsTest PRIVATE ${GLFW_LIBRARY_DIR}/include)
target_include_directories(GraphicsTest PRIVATE ${VULKAN_DIR}/include)
target_link_libraries(GraphicsTest PRIVATE ${GLFW_LIBRARY_DIR}/lib/libglfw.dylib)
target_link_libraries(GraphicsTest PRIVATE ${VULKAN_DIR}/lib/libvulkan.dylib)
target_link_libraries(GraphicsTest PRIVATE ${VULKAN_DIR}/lib/libVkLayer_khronos_validation.dylib)

if(${VKLAYER_API_DUMP_FLAG})
   message(STATUS "VkLayer_api_dump layer enabled.")
   add_compile_definitions(ENABLE_VKLAYER_API_DUMP)
   # target_link_libraries(GraphicsTest PRIVATE ${VULKAN_DIR}/lib/libVkLayer_api_dump.dylib) # segfault(signal 11)
else()
   message(STATUS "VkLayer_api_dump layer disabled.")
endif()