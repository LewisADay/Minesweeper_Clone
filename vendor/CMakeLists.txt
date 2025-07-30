
set(PROJECT_VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${PROJECT_VENDOR_DIR})

#EXAMPLES:
#set(GLAD_DIR "GLAD")
#set(GLAD_DIR "${VENDOR_DIR}/${GLAD_DIR}" PARENT_SCOPE)
#target_sources(${PROJECT_NAME} PRIVATE "${GLAD_DIR}/src/glad.c")
#target_include_directories(${PROJECT_NAME} PUBLIC "${GLAD_DIR}/include")

FetchContent_Declare(
	raylib
	GIT_REPOSITORY https://github.com/raysan5/raylib.git
	GIT_TAG 5.5
)
FetchContent_MakeAvailable(raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

FetchContent_Declare(
	LoggingAD
	GIT_REPOSITORY https://github.com/LewisADay/LoggingAD.git
)
FetchContent_MakeAvailable(LoggingAD)
target_link_libraries(${PROJECT_NAME} PRIVATE ${LOGGINGAD_LIBRARY_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${LOGGINGAD_INCLUDE_DIR})
