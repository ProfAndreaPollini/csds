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
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    boids_init();

    boids_add(Vector2Zero());
    boid_t boid={
            .pos = (Vector2){ .x=200,.y=200},
            .v = Vector2One(),
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
        for (int i = 0; i < boids_count(); ++i) {
            boid_update(boids_get(i));
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

//        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
//        DrawText(TextFormat("(%d,%d)",boids_get(0)->pos->x,boids_get(0)->pos.y), 190, 200, 20,BLACK);
        DrawText(TextFormat(" BOIDS = %d",boids_count()),100,80,18,BLACK);
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
//            //printf("[%d] => {%.2f,%.2f} , {%.2f,%.2f}\n",i,p_boid->pos.x,p_boid->pos.y,p_boid->v.x,p_boid->v.y);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}