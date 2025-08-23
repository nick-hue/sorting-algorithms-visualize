#include "raylib.h"
#include <string>
#include <vector>
#include <iostream>

#define MAIN_FRAME_WIDTH 1000
#define MAIN_FRAME_HEIGHT 600
#define DEBUG_FRAME_WIDTH MAIN_FRAME_WIDTH
#define DEBUG_FRAME_HEIGHT 200 
#define SCREEN_WIDTH MAIN_FRAME_WIDTH
#define SCREEN_HEIGHT MAIN_FRAME_HEIGHT+DEBUG_FRAME_HEIGHT

#define LINE_PADDING 2
#define INITIAL_PADDING 20

#define MIN_LINE_HEIGHT 20
#define MAX_LINE_HEIGHT 400
#define STARTING_LINE_POS 100


int calculateYPlacement(int number_value, int max_value){
    int final_pos;
    float perc = float(number_value)/float(max_value);
    printf("%d of %d is: %.2f\n", number_value, max_value, perc);

    int down_displacement = (1-perc) * MAX_LINE_HEIGHT;

    final_pos = STARTING_LINE_POS + down_displacement;
    // printf("Final pos: %d\n", final_pos);
    return final_pos;
}

int calculateLineHeight(int number_value, int max_value){
    float perc = float(number_value)/float(max_value);
    return MAX_LINE_HEIGHT * perc;
}

void visualize(std::string algorithm, std::vector<int> list, int max_value){
    printf("Visualizing algorithm for: %s\n", algorithm.c_str());

    std::string title = algorithm + " Simulation";
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title.c_str());
    SetWindowPosition(400,100);
    SetTargetFPS(60);     

    int availableWidth = MAIN_FRAME_WIDTH - INITIAL_PADDING*2;
    int lineWidth = (availableWidth - LINE_PADDING * list.size()) / list.size();
    printf("%d\n", lineWidth);


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        BeginDrawing();
            ClearBackground(BLACK);
        
            // Draw main frame
            for (int i = 0; i < list.size(); i++){
                int x_placement = INITIAL_PADDING + i*(lineWidth + LINE_PADDING);
                int y_placement = calculateYPlacement(list[i], max_value);
                int lineHeight = calculateLineHeight(list[i], max_value);
                // Draw line
                DrawRectangle(x_placement, y_placement, lineWidth, lineHeight, WHITE);
                // Draw line index
                DrawText(std::to_string(i).c_str(), x_placement, 80, 12, GREEN);
                // Draw line value
                DrawText(std::to_string(list[i]).c_str(), x_placement+lineWidth/2-2*LINE_PADDING, STARTING_LINE_POS+MAX_LINE_HEIGHT+20, 16, GREEN);
            }

            // Draw debug frame
            DrawLine(0, MAIN_FRAME_HEIGHT, MAIN_FRAME_WIDTH, MAIN_FRAME_HEIGHT, GRAY);
            DrawText("Available Width", INITIAL_PADDING, 620, 12, GREEN);
            DrawRectangle(INITIAL_PADDING, 640, availableWidth, 20, BLUE);
            DrawText("Line Width", INITIAL_PADDING, 680, 12, GREEN);
            DrawRectangle(INITIAL_PADDING, 700, lineWidth, 20, RED);
            
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}
