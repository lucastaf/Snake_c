#include <stdio.h>
#include <raylib.h>
#include <time.h>


Vector2 GridSize = {15,15}; //Tamanho da Grid do jogo
int pixel_size = 50; //Tamanho dos pixeis na tela
int key_press = 0; //Qual a ultima tecla pressionada
Vector2 snake_body[] = {0}; //Array que armazena todos as coordenadas do corpo da cobra
Vector2 screen_size = {15*50,15*50}; //tamanho da tela
Vector2 pos; //cabeça da cobra
int score,i; //score serve tanto para definir a pontuação quanto para definir o tamanho da cobra
int vivo = 1; //vivo ou nao
Vector2 maca; //coordenada da maça

void DrawTextCentered(const char *text, int posX, int posY, int fontSize, Color color) //função que desenha texto centralizado
{
    Vector2 text_size = MeasureTextEx(GetFontDefault(),text,fontSize,fontSize/10);
    float halfx = text_size.x/2;
    float halfy = text_size.y/2;
    DrawText(text,posX-halfx,posY-halfy,fontSize,color);
}

void gerar_maca() //Gera a maça na tela
{
    int check_col = 1;
    int size_x = GridSize.x;
    int size_y = GridSize.y;
    while(check_col) {
        check_col = 0;
        maca.x = ((rand() % (size_x-2))+1)*pixel_size;
        maca.y = ((rand() % (size_y-2))+1)*pixel_size;
        for(i=0;i<=score;i++){
            if (maca.x == snake_body[i].x & maca.y == snake_body[i].y){
                check_col = 1;
            }
        }
    }
}

void game_restart() {
    key_press = 0;
    vivo = 1;
    score = 0;
    gerar_maca();
    pos.x = (GridSize.x*pixel_size/2-(pixel_size/2));
    pos.y = (GridSize.y*pixel_size/2-(pixel_size/2));
}

int main() {

    int tutorial = 1;
    srand(time(0));
    gerar_maca();
    score = 0;
    pos.x = (GridSize.x*pixel_size/2-(pixel_size/2));
    pos.y = (GridSize.y*pixel_size/2-(pixel_size/2));
    InitWindow(screen_size.x,screen_size.y,"Snake");
    SetTargetFPS(8);


    while(tutorial & !WindowShouldClose()){
        BeginDrawing();
        DrawTextCentered("Snake",screen_size.x/2,100,50,GREEN);
        DrawTextCentered("Use as setinhas para mover a cobrinha",screen_size.x/2,250,25,GRAY);
        DrawTextCentered("Coma as maças para ganhar pontos",screen_size.x/2,330,25,GRAY);
        DrawTextCentered("Não bata nas paredes ou em si mesmo",screen_size.x/2,410,25,GRAY);
        DrawTextCentered("Pressione Barra de espaço para começar",screen_size.x/2,490,25,GRAY);
        if (IsKeyPressed(KEY_SPACE)) tutorial = 0;

        EndDrawing();
    }

    while(!WindowShouldClose()) {
        if (IsKeyPressed(KEY_R)) game_restart();

        if(vivo) {
            if (IsKeyDown(KEY_UP) & key_press != 2) key_press = 1;
            if (IsKeyDown(KEY_DOWN) & key_press != 1) key_press = 2;
            if (IsKeyDown(KEY_LEFT) & key_press != 4) key_press = 3;
            if (IsKeyDown(KEY_RIGHT) & key_press != 3) key_press = 4;

            switch (key_press) {
                case 1:
                    pos.y -= pixel_size;
                    break;
                case 2:
                    pos.y += pixel_size;
                    break;
                case 3:
                    pos.x -= pixel_size;
                    break;
                case 4:
                    pos.x += pixel_size;
                    break;
            }

            if (pos.x == maca.x & pos.y == maca.y) {
                score++;
                gerar_maca();
            }

            if (pos.x >= screen_size.x) vivo = 0;
            if (pos.x < 0) pos.x = vivo = 0;
            if (pos.y >= screen_size.y) vivo = 0;
            if (pos.y < 0) pos.y = vivo = 0;

            snake_body[score] = pos;

            //Começar a desenhar:
            BeginDrawing();
            ClearBackground(BLACK);
            DrawRectangle(maca.x, maca.y, pixel_size, pixel_size, RED);

            for (i = 0; i < score; i++) {
                DrawRectangle(snake_body[i].x, snake_body[i].y, pixel_size, pixel_size, DARKGREEN);
                if (pos.x == snake_body[i].x & pos.y == snake_body[i].y) vivo = 0;

            }
            DrawRectangle(pos.x,pos.y,pixel_size,pixel_size,GREEN);
            for (i = 1; i <= score; i++) {
                snake_body[i - 1] = snake_body[i];
            }
            DrawTextCentered(TextFormat("Score: %d",score),pixel_size,pixel_size,15,GRAY);
            EndDrawing();
            //fim do state VIVO
        }
        if(!vivo){
            BeginDrawing();
            ClearBackground(BLACK);
            DrawTextCentered("Game Over (Press R to Restart)",screen_size.x/2,screen_size.y/2 - pixel_size,25,GRAY);
            DrawTextCentered(TextFormat("Final Score: %d",score),screen_size.x/2,screen_size.y/2 + pixel_size, 25, GRAY);
            EndDrawing();
        }
    }
    return 0;
}
