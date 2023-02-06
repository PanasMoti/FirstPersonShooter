#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include "rlFP/rlFPCamera.h"
#include "Player.h"
const int WIDTH = 1280;
const int HEIGHT = 720;
const char* TITLE = "First Person Shooter";
#define ASSETS "../assets"


static Model map;
static Texture2D map_texture;
static Color* mapPixels;
static Texture2D cubicmap;
static Texture2D gun;
static int cframe = 0;
static Rectangle frameRec;

static Vector3 mapPosition;

void init() {
    SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
    InitWindow(WIDTH,HEIGHT,TITLE);
    SetTargetFPS(60);
    Player::init(3);
    gun = LoadTexture(ASSETS "/Textures/super_shotgun.png");
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
    UnloadTexture(gun);
    CloseWindow();
}


int main(int argc,char** argv)
{
    init();
    Player& player = Player::instance();

    while (!WindowShouldClose()) {
        frameRec = {(float(gun.width)/8)*cframe ,0.0f,(float)gun.width/8,(float)gun.height/2};
        if(IsKeyPressed(KEY_F)) {
            cframe++;
            if(cframe == 8) cframe = 0;
        }
        rlFPCameraUpdate(&player.cam);
        BeginDrawing();
        ClearBackground(BLACK);
        rlFPCameraBeginMode3D(&player.cam);
        DrawModel(map,mapPosition,1.0f,WHITE);
        rlFPCameraEndMode3D();
        DrawTexturePro(gun,frameRec,Rectangle{0.0f,0.0f,200,200},{0,0},0.0f,WHITE);
        DrawTextureEx(cubicmap, (Vector2){ GetScreenWidth() - cubicmap.width*4.0f - 20, 20.0f }, 0.0f, 4.0f, WHITE);
        DrawRectangleLines(GetScreenWidth() - cubicmap.width*4 - 20, 20, cubicmap.width*4, cubicmap.height*4, GREEN);
        DrawFPS(10,10);
        EndDrawing();
    }
    close();
    return 0;
}