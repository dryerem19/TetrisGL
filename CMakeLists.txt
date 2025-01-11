cmake_minimum_required (VERSION 3.12)

# Включение горячей перезагрузки для компиляторов MSVC, если поддерживается.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("Tetris")

file(GLOB_RECURSE PROJECT_SRC
	"src/*.h"
	"src/*.cpp"
)

add_executable(${PROJECT_NAME} ${PROJECT_SRC})

find_package(SndFile CONFIG REQUIRED)
find_package(OpenAl CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(Freetype REQUIRED)
find_package(Stb REQUIRED)

target_link_libraries(${PROJECT_NAME} 
	PRIVATE 
		glfw 
		glm::glm
		glad::glad
		imgui::imgui
		OpenAL::OpenAL
		SndFile::sndfile
		Freetype::Freetype
)

target_include_directories(${PROJECT_NAME} 
	PRIVATE
		${Stb_INCLUDE_DIR}
)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()
