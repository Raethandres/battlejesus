#include <stdio.h>
#include <stdlib.h>

#define SIZE 9

typedef struct {
    int size;
    int x, y;
    char direction; 
    int placed;
} Ship;

typedef struct {
    char name[10];
    Ship ship1;
    Ship ship2;
    Ship ship3;
} Player;

void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = '.';
        }
    }
}

void printBoard(char board[SIZE][SIZE]) {
    printf("   ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d  ", i);
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int isSpaceAvailable(char board[SIZE][SIZE], Ship ship) {
    for (int i = 0; i < ship.size; i++) {
        if (ship.direction == 'H') {
            if (ship.x + i >= SIZE || board[ship.y][ship.x + i] != '.') {
                return 0;
            }
        } else {
            if (ship.y + i >= SIZE || board[ship.y + i][ship.x] != '.') {
                return 0; 
            }
        }
    }
    return 1;
}

void placeShip(char board[SIZE][SIZE], Ship ship) {
    if (!isSpaceAvailable(board, ship)) {
        printf("No se puede colocar el barco en la posición (%d, %d) con dirección %c. Espacio ocupado o fuera del tablero.\n", ship.x, ship.y, ship.direction);
        return;
    }
    
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

void moveShip(char board[SIZE][SIZE], Ship *ship, char input) {
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
            ship->placed = 1;
            printf("Barco guardado en posición (%d, %d) con dirección %c\n", ship->x, ship->y, ship->direction);
            break;
    }

    if (isSpaceAvailable(board, *ship)) {
        placeShip(board, *ship);
    } else {
        printf("La nueva posición del barco está ocupada o fuera del tablero. Inténtelo de nuevo.\n");
        clearShip(board, *ship); 
    }
}

void placeShipsForPlayer(Player *player, char board[SIZE][SIZE]) {
    while (1) {
        printBoard(board);
        printf("%s, use 'w', 'a', 's', 'd' para mover el barco, 'r' para rotar, 'g' para guardar ubicación.\n", player->name);

        char input = getchar();
        getchar(); 

        if (!player->ship1.placed) {
            moveShip(board, &player->ship1, input);
        } else if (!player->ship2.placed) {
            moveShip(board, &player->ship2, input);
        } else if (!player->ship3.placed) {
            moveShip(board, &player->ship3, input);
        } else {
            printf("Todos los barcos de %s están colocados.\n", player->name);
            break;
        }

        system("clear"); 
    }
}

int checkHit(char board[SIZE][SIZE], int x, int y) {
    if (board[y][x] == 'S') {
        board[y][x] = 'X';
        return 1; 
    } else {
        board[y][x] = 'O';
        return 0;
    }
}

void takeTurn(Player *attacker, Player *defender, char board[SIZE][SIZE]) {
    int x, y;
    printf("%s, ingresa las coordenadas para disparar (x y): ", attacker->name);
    scanf("%d %d", &x, &y);
    
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
        printf("Coordenadas inválidas. Intenta de nuevo.\n");
        return;
    }

    int hit = checkHit(board, x, y);
    if (hit) {
        printf("¡Impacto en (%d, %d)!\n", x, y);
    } else {
        printf("Fallo en (%d, %d).\n", x, y);
    }
}

int allShipsSunk(Player *player, char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 'S') {
                return 0; 
            }
        }
    }
    return 1; 
}

int main() {
    char board1[SIZE][SIZE];
    char board2[SIZE][SIZE];
    char board1Shots[SIZE][SIZE];
    char board2Shots[SIZE][SIZE];

    Player player1 = {"Player1", {4, 0, 0, 'H', 0}, {3, 0, 0, 'H', 0}, {2, 0, 0, 'H', 0}};
    Player player2 = {"Player2", {4, 0, 0, 'H', 0}, {3, 0, 0, 'H', 0}, {2, 0, 0, 'H', 0}};

    initializeBoard(board1);
    initializeBoard(board2);
    initializeBoard(board1Shots);
    initializeBoard(board2Shots);

    printf("Jugador 1: ¡Coloca tus barcos!\n");
    placeShipsForPlayer(&player1, board1);
åç
    system("clear"); 

    printf("Jugador 2: ¡Coloca tus barcos!\n");
    placeShipsForPlayer(&player2, board2);

    system("clear"); 
    int gameOn = 1;
    while (gameOn) {
        printf("%s, tu tablero de disparos:\n", player1.name);
        printBoard(board1Shots);
        printf("%s, elige dónde disparar:\n", player1.name);
        takeTurn(&player1, &player2, board2);

        if (allShipsSunk(&player2, board2)) {
            printf("%s ha ganado. Todos los barcos de %s han sido hundidos.\n", player1.name, player2.name);
            gameOn = 0;
            break;
        }

        printf("%s, tu tablero de disparos:\n", player2.name);
        printBoard(board2Shots);
        printf("%s, elige dónde disparar:\n", player2.name);
        takeTurn(&player2, &player1, board1);

        if (allShipsSunk(&player1, board1)) {
            printf("%s ha ganado. Todos los barcos de %s han sido hundidos.\n", player2.name, player1.name);
            gameOn = 0;
            break;
        }
    }

    return 0;
}
