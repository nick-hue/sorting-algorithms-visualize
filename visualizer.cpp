#include "raylib.h"
#include <string>
#include <vector>
#include <iostream>

#define MAIN_FRAME_WIDTH 1000
#define MAIN_FRAME_HEIGHT 300
#define DEBUG_FRAME_WIDTH 300
#define DEBUG_FRAME_HEIGHT MAIN_FRAME_HEIGHT 
#define SCREEN_WIDTH MAIN_FRAME_WIDTH+DEBUG_FRAME_WIDTH
#define SCREEN_HEIGHT MAIN_FRAME_HEIGHT+DEBUG_FRAME_HEIGHT




#define LINE_WIDTH 

void visualize(std::string algorithm, std::vector<int> list){
    printf("Visualizing algorithm for: %s\n", algorithm.c_str());

    std::string title = algorithm + " Simulation";
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title.c_str());
    SetWindowPosition(400,100);
    SetTargetFPS(60);     

    int lineWidth = MAIN_FRAME_WIDTH / list.size();
    printf("%d\n", lineWidth);
    int initialPadding = 20;
    int linePadding = 10;


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        

        BeginDrawing();

            ClearBackground(BLACK);
            for (int i = 0; i < list.size(); i++){
                DrawRectangle(initialPadding + i*(lineWidth + linePadding), 100, lineWidth, 400, WHITE);
            }
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
