#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define LARGURA 1000
#define ALTURA 800
#define VELOCIDADE 500

#define RAYGUI_IMPLEMENTATION

#include "raygui.h"

int main(){
    // Criar janela
    InitWindow(LARGURA, ALTURA, "Meu primeiro jogo em C");
    SetTargetFPS(60);

    srand(time(0));

    Color azul = {0, 0, 255, 255};

    // Pos de nosso circulo
    Vector2 posCirculo = {LARGURA / 2, ALTURA / 2};
    float raio = 50;

    float dt;

    // Retangulo
    Rectangle rec = {rand() % (LARGURA - 75), rand() % (ALTURA- 75), 200, 200};

    // Moeda
    Vector2 centroMoeda = {rand() % (LARGURA - 75), rand() % (ALTURA- 75)};
    float raioMoeda = 20;

    // Vidas
    int vidas = 3;

    char bufferMoeda[100];
    char bufferVida[100];

    int pontuacao = 0;

    sprintf(bufferVida, "Quantidade de Vida: %d", vidas);
    sprintf(bufferMoeda, "Quantidade de Moedas: %d", pontuacao);

    Texture2D img = LoadTexture("img/et.png");

    // Loop principal
    while(!WindowShouldClose()){
        // Lógica
        dt = GetFrameTime();

        if(IsKeyDown(KEY_W) && posCirculo.y > raio){
            // Estiver indo pra frente
            posCirculo.y -= VELOCIDADE * dt;
        }
        if(IsKeyDown(KEY_A) && posCirculo.x > raio){
            posCirculo.x -= VELOCIDADE * dt;
        }
        if(IsKeyDown(KEY_S) && posCirculo.y < ALTURA - raio){
            posCirculo.y += VELOCIDADE * dt;
        }
        if(IsKeyDown(KEY_D) && posCirculo.x < LARGURA - raio){
            posCirculo.x += VELOCIDADE * dt;
        }

        // Checa colisão
        if(CheckCollisionCircleRec(posCirculo, raio, rec)){
            vidas--;

            sprintf(bufferVida, "Quantidade de Vida: %d", vidas);

            rec = (Rectangle){rand() % (LARGURA - 75), rand() % (ALTURA- 75), 75, 75};
        }

        if(CheckCollisionCircles(centroMoeda, raioMoeda, posCirculo, raio)){
            pontuacao++;

            sprintf(bufferMoeda, "Quantidade de Moedas: %d", pontuacao);

            centroMoeda = (Vector2){rand() % (LARGURA - 75), rand() % (ALTURA- 75)};
        }

        // desenho
        BeginDrawing();
        ClearBackground(WHITE);
        DrawFPS(100, 100);

        DrawCircleV(posCirculo, raio, azul);

        DrawText("Bem vindo ao meu jogo", 100, 20, 32, BLACK);

        //DrawTexture(img, rec.x, rec.y, WHITE);
        DrawTexturePro(img, (Rectangle){0,0,img.width, img.height}, rec, (Vector2){0,0}, 0, WHITE);

        DrawText(bufferVida, LARGURA - 500, 20, 32, RED);

        DrawText(bufferMoeda, LARGURA - 500, 70, 32, YELLOW);

        DrawCircleV(centroMoeda, raioMoeda, YELLOW);

        if(GuiButton((Rectangle){LARGURA / 2, ALTURA - 100, 100, 50}, "Resetar")){
            vidas = 3;
            pontuacao = 0;

            sprintf(bufferVida, "Quantidade de Vida: %d", vidas);
            sprintf(bufferMoeda, "Quantidade de Moedas: %d", pontuacao);
        }

        EndDrawing();
    }

    UnloadTexture(img);

    CloseWindow();
}
