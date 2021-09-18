//
// Created by pollini on 15/09/2021.
//

#include "csds.h"


#define RAYMATH_IMPLEMENTATION
#include "raylib.h"
#include "raymath.h"
#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS


#include "extras/raygui.h"

#include "boid.h"
#include "boids.h"
#include "perlin.h"
#include "utils.h"
#include "steering.h"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    const int cellSize = 10;

    const int cols = screenWidth/cellSize;
    const int rows = screenHeight/cellSize;

    double freq = 0.0001;
    const double FREQ_INCREMENT = 0.0001;

    boids_init();

    boids_add(Vector2Zero());
    boid_t boid={
            .pos = (Vector2){ .x=200,.y=200},
            .v = Vector2Rotate(Vector2Normalize(Vector2One()), GetRandomValue(0,359)),
            .a = Vector2Zero()
    };

    InitWindow(screenWidth, screenHeight, "Boids simulation");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        Vector2 mousePos = GetMousePosition();
        for (int i = 0; i < boids_count(); ++i) {
            boid_t* p_boid = boids_get(i);
            int x = p_boid->pos.x / cellSize;
            int y = p_boid->pos.y / cellSize;
            Vector2 dir = {.x=2,.y=0};
            dir = Vector2Rotate(dir,MapValue(perlin_noise2d(x,y,freq,4),0.0,1.0,0.0,359));
            p_boid->a.x = dir.x;
            p_boid->a.y = dir.y;
           steering_seek(p_boid,&mousePos);
            steering_flee(p_boid,&mousePos);
            boid_update(p_boid);

        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                Vector2 pos = {.x=x,.y=y};
                Vector2 dir = {.x=1,.y=0};

                dir = Vector2Rotate(dir,MapValue(perlin_noise2d(x,y,freq,4),0.0,1.0,0.0,359));
                DrawLineV(Vector2Scale(pos,cellSize), Vector2Scale(Vector2Add(pos,dir),cellSize),GRAY);
//               // DrawCircle(x*cellSize,y*cellSize,4* perlin_noise2d(x,y,0.1,4),RED);
            }
        }

//        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
//        DrawText(TextFormat("(%d,%d)",boids_get(0)->pos->x,boids_get(0)->pos.y), 190, 200, 20,BLACK);
        DrawText(TextFormat(" BOIDS = %d",boids_count()),100,80,14,BLACK);
         if(GuiButton((Rectangle){.x=100,.y=100, .width=30,.height=30},"+")) {
            boids_add(Vector2Zero());
        }
        if(GuiButton((Rectangle){.x=135,.y=100, .width=30,.height=30},"-")){
            boids_remove();
        }
//        boid_draw(&boid);
        for (int i = 0; i < boids_count(); ++i) {
            boid_t* p_boid = boids_get(i);
            boid_draw(p_boid);
            boid_check_screen_bounds(boids_get(i),screenWidth,screenHeight);

//            printf("[%d] => {%.2f,%.2f}{%.2f,%.2f}\n",i,p_boid->v.x,p_boid->v.y,p_boid->a.x,p_boid->a.y);
//            //printf("[%d] => {%.2f,%.2f} , {%.2f,%.2f}\n",i,p_boid->pos.x,p_boid->pos.y,p_boid->v.x,p_boid->v.y);
        }

        DrawText(TextFormat("MOUSE(%.2f,%.2f)",mousePos.x,mousePos.y),50,40,18,BLACK);
//        for (int i = 0; i < boids_count(); ++i) {
//            boid_t *p_boid = boids_get(i);
//            DrawLineV(p_boid->pos,mousePos,DARKGREEN);
////            steering_seek(p_boid,&mousePos);
//        }

        EndDrawing();

        freq += FREQ_INCREMENT;
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}


