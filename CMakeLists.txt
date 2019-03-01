cmake_minimum_required(VERSION 3.13)
project(Bomberman C)
set(CMAKE_C_STANDARD 11)
find_package(SDL2 REQUIRED)
include_directories(Bomberman ${SDL2_INCLUDE_DIRS})
add_executable(Bomberman
        ./main.c
        ./animationPlayer.c ./bomber.c ./error.c ./ main_menu.c ./map.c ./menuHostGame.c ./menuJoinGame.c ./playerMove.c ./recv.c ./send.c ./userWrite.c)
target_link_libraries(Bomberman ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lfreetype)
