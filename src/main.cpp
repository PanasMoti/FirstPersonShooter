#include <raylib.h>
#include <raymath.h>
#include "rlFP/rlFPCamera.h"

const int WIDTH = 1280;
const int HEIGHT = 720;
const char* TITLE = "First Person Shooter";
#define ASSETS "../assets"


static rlFPCamera cam;

static Model map;
static Texture2D map_texture;
static Color* mapPixels;
static Texture2D cubicmap;

static Vector3 mapPosition;

void init() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(WIDTH,HEIGHT,TITLE);
    SetTargetFPS(60);
    rlFPCameraInit(&cam,45,(Vector3){1,0,0});
    cam.MoveSpeed.z = 5;
    cam.MoveSpeed.x = 5;
    cam.FarPlane = 5000; // render distance
    cam.ControlsKeys[4] = KEY_SPACE;
    cam.ControlsKeys[5] = KEY_LEFT_CONTROL;
    cam.ControlsKeys[6] = KEY_RIGHT;
    cam.ControlsKeys[7] = KEY_LEFT;
    cam.ControlsKeys[8] = KEY_DOWN;
    cam.ControlsKeys[9] = KEY_UP;

    Image imMap = LoadImage(ASSETS"/Textures/cubicmap.png");      // Load cubicmap image (RAM)
    cubicmap = LoadTextureFromImage(imMap);       // Convert image to texture to display (VRAM)
    Mesh mesh = GenMeshCubicmap(imMap, (Vector3){ 1.0f, 1.0f, 1.0f });
    map = LoadModelFromMesh(mesh);
    // NOTE: By default each cube is mapped to one part of texture atlas
    map_texture = LoadTexture(ASSETS"/Textures/test.png");    // Load map texture
    map.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = map_texture;             // Set map diffuse texture
    mapPixels = LoadImageColors(imMap);
    UnloadImage(imMap);             // Unload image from RAM
    mapPosition = { -16.0f, 0.0f, -8.0f };  // Set model position

}

void close() {
    UnloadTexture(map_texture);
    UnloadModel(map);
    UnloadImageColors(mapPixels);
    UnloadTexture(cubicmap);
    CloseWindow();
}

int main(int argc,char** argv)
{
    init();
    while (!WindowShouldClose()) {
        rlFPCameraUpdate(&cam);
        BeginDrawing();
        ClearBackground(BLACK);
        rlFPCameraBeginMode3D(&cam);
        DrawModel(map,mapPosition,1.0f,WHITE);
        rlFPCameraEndMode3D();
        DrawTextureEx(cubicmap, (Vector2){ GetScreenWidth() - cubicmap.width*4.0f - 20, 20.0f }, 0.0f, 4.0f, WHITE);
        DrawRectangleLines(GetScreenWidth() - cubicmap.width*4 - 20, 20, cubicmap.width*4, cubicmap.height*4, GREEN);
        DrawFPS(10,10);
        EndDrawing();
    }
    close();
    return 0;
}