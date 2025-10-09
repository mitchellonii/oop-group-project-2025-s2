cmake_minimum_required(VERSION 3.16)
project(MySFMLApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(prog main.cpp GameController.cpp PhysicsElement.cpp RenderElement.cpp TextElement.cpp)

set(SFML_INCLUDE_DIR "/opt/homebrew/Cellar/sfml/3.0.2/include")
set(SFML_LIBRARY_DIR "/opt/homebrew/Cellar/sfml/3.0.2/lib")

target_include_directories(prog PRIVATE ${SFML_INCLUDE_DIR})

target_link_directories(prog PRIVATE ${SFML_LIBRARY_DIR})
target_link_libraries(prog
    sfml-graphics
    sfml-window
    sfml-network
    sfml-system
)
