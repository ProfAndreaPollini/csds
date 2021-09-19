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
#include "app_config.h"

void target_draw(boid_t *p_target) {
    Vector2 base_dir = Vector2Normalize(Vector2Rotate(p_target->v,90));
    Vector2 v1 = Vector2Add(p_target->pos, Vector2Scale(base_dir,5));
    Vector2 v2 = Vector2Add(p_target->pos, Vector2Scale(Vector2Rotate(base_dir,180),5));
    Vector2 v3 = Vector2Add(p_target->pos,Vector2Scale(Vector2Normalize(p_target->v),15));

    //DrawTriangle(v1,v3,v2,BLUE);
    DrawCircleV(p_target->pos,5,BLUE);
}


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

 app_config_t app_config={
         .mouse_as_target = FALSE, // if true use 'target'
         .use_flee = FALSE,
         .use_seek = FALSE
 };


boids_init();

    boids_add(Vector2Zero());
    boid_t target={
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
            boid_check_screen_bounds(p_boid,screenWidth,screenHeight);
            boid_update(p_boid);
            if (app_config.mouse_as_target) {
                if (app_config.use_seek)steering_seek(p_boid, &mousePos);
                if (app_config.use_flee)steering_flee(p_boid, &mousePos);
            } else {
                if (app_config.use_seek)steering_seek(p_boid, &target.pos);
                if (app_config.use_flee)steering_flee(p_boid, &target.pos);
            }
        }

        //
        // target update
        //
        Vector2 target_dir = {.x=2,.y=0};
        int target_noise_cell_x = target.pos.x / cellSize;
        int target_noise_cell_y = target.pos.y / cellSize;
        target_dir = Vector2Rotate(target_dir,MapValue(perlin_noise2d(target_noise_cell_x,target_noise_cell_y,freq,4),0.0,1.0,0.0,359));
        target.a.x = target_dir.x;
        target.a.y = target_dir.y;
        boid_update(&target);
        boid_check_screen_bounds(&target,screenWidth,screenHeight);

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
        // app settings
        app_config.mouse_as_target = GuiToggle((Rectangle){.x=135,.y=120, .width=80,.height=20},"mouse as target?",app_config.mouse_as_target);
        app_config.use_seek = GuiToggle((Rectangle){.x=135,.y=140, .width=80,.height=20},"seek",app_config.use_seek);
        app_config.use_flee = GuiToggle((Rectangle){.x=135,.y=160, .width=80,.height=20},"flee",app_config.use_flee);

        for (int i = 0; i < boids_count(); ++i) {
            boid_t* p_boid = boids_get(i);
            boid_draw(p_boid);
        }

        // target draw

        target_draw(&target);


        //DrawText(TextFormat("MOUSE(%.2f,%.2f)",mousePos.x,mousePos.y),50,40,18,BLACK);
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


