#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 9

typedef struct {
    int size;
    int x, y;
    char direction; 
} Ship;

typedef struct {
    char name[10];
    Ship ship1;
    Ship ship2;
    Ship ship3;
} Player;

void copy2DArray(char dest[SIZE][SIZE], char src[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '.';
        }
    }
}

void printBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

void placeShip(char board[SIZE][SIZE], Ship ship) {
    for (int i = 0; i < ship.size; i++) {
        if (ship.direction == 'H') {
            board[ship.y][ship.x + i] = 'S';
        } else {
            board[ship.y + i][ship.x] = 'S';
        }
    }
}

void clearShip(char board[SIZE][SIZE], Ship ship) {
    for (int i = 0; i < ship.size; i++) {
        if (ship.direction == 'H') {
            board[ship.y][ship.x + i] = '.';
        } else {
            board[ship.y + i][ship.x] = '.';
        }
    }
}

void moveShip(char board[SIZE][SIZE], Ship *ship, char input, Player *player) {
    clearShip(board, *ship);
    
    switch (input) {
        case 'w':
            if (ship->y > 0) ship->y--;
            break;
        case 's':
            if (ship->y < SIZE - ship->size && ship->direction == 'V') ship->y++;
            if (ship->y < SIZE - 1 && ship->direction == 'H') ship->y++;
            break;
        case 'a': 
            if (ship->x > 0) ship->x--;
            break;
        case 'd': 
            if (ship->x < SIZE - ship->size && ship->direction == 'H') ship->x++;
            if (ship->x < SIZE - 1 && ship->direction == 'V') ship->x++;
            break;
        case 'r': 
            ship->direction = (ship->direction == 'H') ? 'V' : 'H';
            if (ship->direction == 'H' && ship->x + ship->size > SIZE) ship->x = SIZE - ship->size;
            if (ship->direction == 'V' && ship->y + ship->size > SIZE) ship->y = SIZE - ship->size;
            break;
        case 'g':
            player->ship1 = *ship;
            printf("Barco guardado para %s en posición (%d, %d) con dirección %c\n", player->name, player->ship1.x, player->ship1.y, player->ship1.direction);
            break;
    }

    placeShip(board, *ship);
}

int main() {
    char board[SIZE][SIZE];
    Ship ship1 = {4, 0, 0, 'H'}; 
    Ship ship2 = {3, 0, 0, 'H'}; 
    Ship ship3 = {2, 0, 0, 'H'}; 
    
    Player player1 = {"player1"};

    initializeBoard(board);
    placeShip(board, ship1);

    while (1) {
        printBoard(board);
        printf("Use 'w', 'a', 's', 'd' para mover el barco, 'r' para rotar, 'g' para guardar ubicacion.\n");

        char input = getchar();
        moveShip(board, &ship1, input, &player1);

        system("clear"); 
    }

    return 0;
}
