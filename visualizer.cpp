#include "raylib.h"
#include <string>
#include <vector>
#include <iostream>
#include <functional>
#include <algorithm>
#include <cmath>

#define MAIN_FRAME_WIDTH 1000
#define MAIN_FRAME_HEIGHT 600
#define DEBUG_FRAME_WIDTH MAIN_FRAME_WIDTH
#define DEBUG_FRAME_HEIGHT 200 
#define SCREEN_WIDTH MAIN_FRAME_WIDTH
#define SCREEN_HEIGHT MAIN_FRAME_HEIGHT+DEBUG_FRAME_HEIGHT

#define LINE_PADDING 2
#define INITIAL_PADDING 20

#define AVAILABLE_WIDTH (MAIN_FRAME_WIDTH - INITIAL_PADDING*2)

#define MIN_LINE_HEIGHT 20
#define MAX_LINE_HEIGHT 400
#define STARTING_LINE_POS 100

// Callback type for visualization
using VisualizeStepCallback = std::function<void(const std::vector<int>&)>;

int CalculateYPlacement(int number_value, int max_value){
    int final_pos;
    float perc = float(number_value)/float(max_value);
    // printf("Perc before rounding: %f\n", perc);
    perc = std::round(perc * 100.0f) / 100.0f;
    // printf("%d of %d is: %.2f\n", number_value, max_value, perc);

    int down_displacement = (1-perc) * MAX_LINE_HEIGHT;

    final_pos = STARTING_LINE_POS + down_displacement;
    printf("Final pos: %d\n", final_pos);
    return final_pos;
}

int CalculateLineHeight(int number_value, int max_value){
    float perc = float(number_value)/float(max_value);
    perc = std::round(perc * 100.0f) / 100.0f;
    return MAX_LINE_HEIGHT * perc;
}

void DrawMainFrame(std::vector<int> list, int lineWidth, int max_value, Color lineColor){
    for (int i = 0; i < list.size(); i++){
        int x_placement = INITIAL_PADDING + i*(lineWidth + LINE_PADDING);
        int y_placement = CalculateYPlacement(list[i], max_value);
        int lineHeight = CalculateLineHeight(list[i], max_value);
        // Draw line
        DrawRectangle(x_placement, y_placement, lineWidth, lineHeight, lineColor);
        // Draw line index
        DrawText(std::to_string(i).c_str(), x_placement, 80, 12, GREEN);
        // Draw line value
        DrawText(std::to_string(list[i]).c_str(), x_placement+lineWidth/2-2*LINE_PADDING, STARTING_LINE_POS+MAX_LINE_HEIGHT+20, 16, GREEN);
    }
}

void DrawDebugFrame(int lineWidth, float waitTime){
        DrawLine(0, MAIN_FRAME_HEIGHT, MAIN_FRAME_WIDTH, MAIN_FRAME_HEIGHT, GRAY);
        DrawText("Available Width", INITIAL_PADDING, 620, 12, GREEN);
        DrawRectangle(INITIAL_PADDING, 640, AVAILABLE_WIDTH, 20, BLUE);
        DrawText("Line Width", INITIAL_PADDING, 680, 12, GREEN);
        DrawRectangle(INITIAL_PADDING, 700, lineWidth, 20, RED);
        std::string waitText = "Wait Time (ms): " + std::to_string(waitTime) + " (UP/DOWN to adjust)";
        DrawText(waitText.c_str(), INITIAL_PADDING, 740, 12, GREEN);
}

void CheckSpeed(float& waitTime, float increment = 0.0005f){
    if (IsKeyDown(KEY_UP)){
        waitTime = std::min(0.1f, waitTime + increment);
        printf("Wait time: %.3f\n", waitTime);
    }
    if (IsKeyDown(KEY_DOWN)){
        waitTime = std::max(0.001f, waitTime - increment);
        printf("Wait time: %.3f\n", waitTime);
    }
}

void AnimateEnd(std::vector<int> list, int lineWidth, int max_value, Color lineColor, Color completed, int colored_index){
    for (int i = 0; i < list.size(); i++){
        int x_placement = INITIAL_PADDING + i*(lineWidth + LINE_PADDING);
        int y_placement = CalculateYPlacement(list[i], max_value);
        int lineHeight = CalculateLineHeight(list[i], max_value);
        // Draw line
        Color c;
        if (i > colored_index){
            c = lineColor;
        } else {
            c = completed;
        } 

        DrawRectangle(x_placement, y_placement, lineWidth, lineHeight, c);
        // Draw line index
        DrawText(std::to_string(i).c_str(), x_placement, 80, 12, GREEN);
        // Draw line value
        DrawText(std::to_string(list[i]).c_str(), x_placement+lineWidth/2-2*LINE_PADDING, STARTING_LINE_POS+MAX_LINE_HEIGHT+20, 16, GREEN);
    }
}

// Updated visualize function to accept a callback
void visualize(void(*sortFunc)(std::vector<int>&, VisualizeStepCallback), std::string algorithm, std::vector<int> list, int max_value){
    
    printf("Visualizing algorithm for: %s\n", algorithm.c_str());
    std::string title = algorithm + " Simulation";
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, title.c_str());
    SetWindowPosition(400,100);
    SetTargetFPS(60);     

    InitAudioDevice();      // Initialize audio device
    Sound fxWav = LoadSound("resources/boop.wav");         // Load WAV audio file
    SetMasterVolume(0.2f);                             // Set master volume (listener)

    // WAVE TEST
    // Wave beepWave = LoadWave("resources/boop.wav");

    // const int SND_POOL = 8;              // how many overlaps you allow
    // std::vector<Sound> beepPool(SND_POOL);
    // for (int i = 0; i < SND_POOL; ++i) {
    //     beepPool[i] = LoadSoundFromWave(beepWave);

    // }
    // UnloadWave(beepWave);                // wave no longer needed
    // int beepIdx = 0;

    int lineWidth = (AVAILABLE_WIDTH - LINE_PADDING * list.size()) / list.size();
    // printf("%d\n", lineWidth);

    std::vector<int> currentList = list;
    bool sortingDone = false;
    float waitTime = 0.025f; 
    bool paused = false;

    // Visualization callback
    auto stepCallback = [&](const std::vector<int>& state) {
        currentList = state;
        CheckSpeed(waitTime);

        if (IsKeyPressed(KEY_SPACE)) paused = !paused;
        while (paused) {
            BeginDrawing();
                ClearBackground(BLACK);
                DrawMainFrame(currentList, lineWidth, max_value, YELLOW);
                DrawDebugFrame(lineWidth, waitTime);
                DrawText("PAUSED (press SPACE to resume)", INITIAL_PADDING, 770, 20, RED);
            EndDrawing();
            if (IsKeyPressed(KEY_SPACE)) paused = false;
            WaitTime(0.01f);
        }

        BeginDrawing();
            ClearBackground(BLACK);
            DrawMainFrame(currentList, lineWidth, max_value, WHITE);
            DrawDebugFrame(lineWidth, waitTime);
            // if (IsSoundPlaying(beepPool[beepIdx])) {
            //     StopSound(beepPool[beepIdx]);  // comment this out if you prefer true overlap even if it clips
            // }
            // PlaySound(beepPool[beepIdx]);
            // beepIdx = (beepIdx + 1) % SND_POOL;
        EndDrawing();
        PlaySound(fxWav);  // Play sound on each step

        WaitTime(waitTime);
    };

    // Run the sorting algorithm with visualization
    sortFunc(currentList, stepCallback);
    sortingDone = true;

    // Show the final sorted state until window is closed
    int colored_index = 0;
    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(BLACK);
            // DrawMainFrame(currentList, lineWidth, max_value, GREEN);
            AnimateEnd(currentList, lineWidth, max_value, WHITE, GREEN, colored_index);
            DrawDebugFrame(lineWidth, waitTime);
            PlaySound(fxWav);  // Play sound on completion
        EndDrawing();
        colored_index++;
    }

    // for (auto& s : beepPool) UnloadSound(s);
    
    UnloadSound(fxWav);     
    CloseAudioDevice();    
    CloseWindow();
}
