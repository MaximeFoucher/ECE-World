cmake_minimum_required(VERSION 3.10)
project(projet-2022-2023-ece-world-ece_world_q C)

set(CMAKE_C_STANDARD 99)

add_executable(projet-2022-2023-ece-world-ece_world_q main.c src/manege.c src/manege.h src/paris/paris_hippiques.c src/paris/paris_hippiques.h src/peche_canards/canard.h src/peche_canards/canard.c src/tir_ballon/tireballon.c src/tir_ballon/tireballon.h src/tableauscore/tableauscore.c src/tableauscore/tableauscore.h src/guitare/guitare.c src/guitare/guitare.h src/Taupe/taupe.c src/Taupe/taupe.h src/Snake/snake.c src/Snake/snake.h src/flappy/flappy.c src/flappy/flappy.h)
target_link_libraries(projet-2022-2023-ece-world-ece_world_q -lmingw32 -lallegro-5.0.10-monolith-md-debug)
