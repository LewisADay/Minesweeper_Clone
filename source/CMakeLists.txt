
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(PROJECT_SOURCE_DIR ${OORENDERER_SOURCE_DIR} PARENT_SCOPE)

target_sources(${PROJECT_NAME} PRIVATE
	"main.cpp"
	"Application.h"
	"Application.cpp"
	"Spritesheet.h"
	"Spritesheet.cpp"
	"Board.h"
	"Board.cpp")

target_include_directories(${PROJECT_NAME} PRIVATE
	${PROJECT_SOURCE_DIR}
)
