#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

void Initialize(int screenWidth, int screenHeight, RenderTexture2D *target);
void DrawSquares(RenderTexture2D target, int rows, int columns, int width, int height, Color colors[], int colorsSize);
void MainLoop(RenderTexture2D target, Rectangle buttonRec, bool *redraw, int rows, int columns, int width, int height, Color colors[], int colorsSize);
void Cleanup(RenderTexture2D target);

void Initialize(int screenWidth, int screenHeight, RenderTexture2D *target) {
  InitWindow(screenWidth, screenHeight, "raylib [textures] example - texture rendering" );
  SetTargetFPS(60);
  *target = LoadRenderTexture(screenWidth, screenHeight);
}

void DrawSquares(RenderTexture2D target, int rows, int columns, int width, int height, Color colors[], int colorsSize) {
  BeginTextureMode(target);
  ClearBackground(BLACK);

  int x, y, i, j;
  for(i = 0; i < rows; i++) {
    for(j = 0; j < columns; j++) {
      x = i * width;
      y = j * height;
      int colorIndex = rand() % colorsSize;
      DrawRectangle(x, y, width, height, colors[colorIndex]);
    }
  }

  EndTextureMode();
}

void MainLoop(RenderTexture2D target, Rectangle buttonRec, bool *redraw, int rows, int columns, int width, int height, Color colors[], int colorsSize) {
  while (!WindowShouldClose()) {
    BeginDrawing();

    if (GuiButton(buttonRec, "Generate")) {
      *redraw = true;
    }

    if (*redraw) {
      DrawSquares(target, rows, columns, width, height, colors, colorsSize);
      *redraw = false;
    }

    ClearBackground(BLACK);
    DrawTexture(target.texture, 0, 0, WHITE);

    if (GuiButton(buttonRec, "Generate")) {
      DrawRectangleLinesEx(buttonRec, 2, WHITE);
    }

    EndDrawing();
  }
}

void Cleanup(RenderTexture2D target) {
  UnloadRenderTexture(target);
  CloseWindow();
}

int main(void)
{
  const int screenWidth = 600;
  const int screenHeight = 450;
  int rows = 10;
  int columns = 10;
  int width = 40;
  int height = 40;

  srand(time(NULL));

  Color colors[] = {
    LIGHTGRAY,
    GRAY,
    DARKGRAY,
    YELLOW,
    GOLD,
    ORANGE,
    PINK,
    RED,
    MAROON,
    GREEN,
    LIME,
    DARKGREEN,
    SKYBLUE,
    BLUE,
    DARKBLUE,
    PURPLE,
    VIOLET,
    DARKPURPLE,
    BEIGE,
    DARKBROWN,
    MAGENTA,
  };

  int colorsSize = sizeof(colors) / sizeof(Color);

  Rectangle buttonRec = { screenWidth - 150, 20, 130, 30 };
  bool redraw = false;

  RenderTexture2D target;
  Initialize(screenWidth, screenHeight, &target);
  MainLoop(target, buttonRec, &redraw, rows, columns, width, height, colors, colorsSize);
  Cleanup(target);

  return 0;
}

