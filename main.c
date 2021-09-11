#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define V 21
#define H 75

//Prototipado
void start(char field[V][H], int ballX, int ballY, int strPlayer, int endPlayer, int strIA, int endIA);
void edge(char field[V][H]);
void stickPlayer(char field[V][H], int strPlayer, int endPlayer);
void stickIA(char field[V][H], int strIA, int endIA);
void ball(char field[V][H], int ballX, int ballY);
void showField(char field[V][H]);
void gameLoop(char field[V][H], int ballX, int ballY, int strPlayer, int endPlayer, int strIA, int endIA, int modX, int modY, int modIA);
void draw(char field[V][H]);
void input(char field[V][H], int* ballX, int* ballY, int* strPlayer, int* endPlayer, int* strIA, int* endIA, int* modX, int* modY, int* modIA, int* goal);
void update(char field[V][H], int ballX, int ballY, int strPlayer, int endPlayer, int strIA, int endIA);

int main() {

    srand(time(NULL));

    SetConsoleTitle("PONG by EL S");

    system("color 0C");

    //Tamaño de la consola
    system("MODE 75, 25");

    int ballX, ballY, strPlayer, endPlayer, strIA, endIA; //Variables de posición
    int modX, modY, modIA; //Variables de modificación

    char field[V][H];

    //--------------------- [ POSICION ] ---------------------
    //Ubicación pelota
    ballX = 37;
    ballY = (rand() % 10);

    //Ubicación jugador
    strPlayer = 8;
    endPlayer = 12;

    //Ubicación IA
    strIA = 5;
    endIA = 18;

    //--------------------- [ MODIFICACION ] ---------------------
    modX = -1;
    modY = -1;
    modIA = -1;

    start(field, ballX, ballY, strPlayer, endPlayer, strIA, endIA);

    gameLoop(field, ballX, ballY, strPlayer, endPlayer, strIA, endIA, modX, modY, modIA);

    return 0;
}

void start(char field[V][H], int ballX, int ballY, int strPlayer, int endPlayer, int strIA, int endIA) {

    edge(field);
    stickPlayer(field, strPlayer, endPlayer);
    stickIA(field, strIA, endIA);
    ball(field, ballX, ballY);
}

void edge(char field[V][H]) {

    int i, j;

    for(i = 0; i < V; i++) {

        for(j = 0; j < H; j++) {

            if(i == 0 || i == V-1) {

                field[i][j] = '-';
            }
            else if(j == 0 || j == H-1) {
                field[i][j] = '|';
            }
            else{
                field[i][j] = ' ';
            }
        }
    }

}

void stickPlayer(char field[V][H], int strPlayer, int endPlayer) {

    int i, j;

    for(i = strPlayer; i <= endPlayer; i++) {
        for(j = 2; j <= 3; j++) {
            field[i][j] = 'X';
        }
    }
}

void stickIA(char field[V][H], int strIA, int endIA) {

    int i, j;

    for(i = strIA; i <= endIA; i++) {

        for(j = H-4; j <= H - 3; j++) {

            field[i][j] = 'X';
        }

    }
}

void ball(char field[V][H], int ballX, int ballY) {

    field[ballY][ballX] = 'O';
}

void showField(char field[V][H]) {

    int i, j;

    for(i = 0; i < V; i++) {

        for(j = 0; j < H; j++) {
            printf("%c", field[i][j]);
        }

        printf("\n");
    }

}

void gameLoop(char field[V][H], int ballX, int ballY, int strPlayer, int endPlayer, int strIA, int endIA, int modX, int modY, int modIA) {

    int goal = 0;
    int points = 0;
    char repeat = 's';

        do{
            draw(field); //Dibujar en pantalla
            input(field, &ballX, &ballY, &strPlayer, &endPlayer, &strIA, &endIA, &modX, &modY, &modIA, &goal); //Verificar y modificar las posiciones
            update(field, ballX, ballY, strPlayer, endPlayer, strIA, endIA); //Actualizar la matriz campo
            Sleep(10);

            if(goal == 1) {

                points += 1;
            }

        }while(goal == 0);
    }

void draw(char field[V][H]) {

    system("cls");
    showField(field);
}

void input(char field[V][H], int* ballX, int* ballY, int* strPlayer, int* endPlayer, int* strIA, int* endIA, int* modX, int* modY, int* modIA, int* goal) {

    int i;
    char key;

    //Verificacion
    if( (*ballY) == 1 || (*ballY) == V-2) {
        (*modY) *= -1;
    }

    if( (*ballX) == 1 || (*ballX) == H-2) {

        (*goal) = 1;
    }

    if( (*ballX) == 4) {

        for(i = (*strPlayer); i < (*endPlayer); i++) {

            if(i == (*ballY) ) {
                (*modX) *= -1;
            }
        }
    }

    if( (*ballX) == H - 5) {

        for(i = (*strIA); i <= (*endIA); i++) {

            if(i == (*ballY)) {
                (*modX) *= -1;
            }
        }
    }

    if( (*strIA) == 1 || (*endIA) == V-1 ) {

        *modIA *= -1;
    }

    //Modificacion
    if( (*goal) == 0 ) {

        //Pelota
        (*ballX) += (*modX);
        (*ballY) += (*modY);

        //Raqueta de la IA
        (*strIA) += (*modIA);
        (*endIA) += (*modIA);

        //Raqueta Jugador
        if(kbhit() == 1) { //Provisional
            key = getch(); //Lo mismo que888 scanf solo que no hay que pulsar ENTER

            if(key == '8') {
                if( (*strPlayer) != 1) {
                    (*strPlayer) -= 1;
                    (*endPlayer) -= 1;
                }
            }

            if(key == '2') {
                if( (*endPlayer) != V-2) {
                    (*strPlayer) += 1;
                    (*endPlayer) += 1;
                }
            }
        }
    }
}

void update(char field[V][H], int ballX, int ballY, int strPlayer, int endPlayer, int strIA, int endIA) {

    edge(field);
    stickPlayer(field, strPlayer, endPlayer);
    stickIA(field, strIA, endIA);
    ball(field, ballX, ballY);
}











