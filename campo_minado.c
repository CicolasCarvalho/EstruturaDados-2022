/*
Nícolas dos Santos Carvalho
Maringá, PR - Brasil
21/02/2023
Campo Minado CLI feito por Nícolas dos Santos Carvalho
https://github.com/Cicolas
*/

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#ifndef bool
	#define bool int
	#define true 1
	#define false 0
#endif

//-UTILIDADES-------------------------------------------------------------------
#define BLACK			0
#define BLUE			1
#define GREEN			2
#define CYAN			3
#define RED				4
#define MAGENTA			5
#define YELLOW			6
#define LIGHT_GRAY		7
#define DARK_GRAY		8
#define LIGHT_BLUE		9
#define LIGHT_GREEN		10
#define LIGHT_CYAN		11
#define LIGHT_RED		12
#define LIGHT_MAGENTA	13
#define LIGHT_YELLOW	14
#define WHITE			15
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

void setColor(int clr, int backgroud);
void hidecursor(void);
void gotoxy(int x, int y);
void clearScr(int x, int y, int w, int h);

char *itoanz(int n, char *s);
//------------------------------------------------------------------------------

#define DEBUG_MAP 0

#define WIDTH 20
#define HEIGHT 20
#define BOMBS 50

typedef struct {
	int width, height;

	// -1 => bomba
	//  0 => nada
	//  q => quantidade de bombas proximas
	int **map;
	bool **playing_map;
	bool **flag_map;
} campo_minado;

typedef struct {
	int x, y;
	char valor;
} cursor;

campo_minado* init_map(int w, int h, int bombs);
void generate_bombs(campo_minado* cmp, int quantity);
void indexize_map(campo_minado* cmp);
void print_map(campo_minado map, int w, int h);
int  discover_map(campo_minado* cmp, int x, int y);
void print_playing_map(campo_minado cmp);
void free_map(campo_minado* map);

void beauty_print(campo_minado cmp, int x, int y, bool masked);
void reset(campo_minado* cmp);
int  look_around(int** map, int x, int y, int w, int h);

void move(int key, cursor* cur, campo_minado cmp);
void put_flag(campo_minado* cmp, int x, int y);
bool check_win(campo_minado cmp);

void print_title(void);
void print_borders(void);
void print_commands(void);

//global vars
int offsetx = 10;
int offsety = 3;

int main(void) {
	system("cls");
	srand(time(NULL));
	setlocale(LC_ALL, "portuguese");

	campo_minado* map = init_map(WIDTH, HEIGHT, BOMBS);
	cursor cur = {.x = 0, .y = 0, .valor = 0};

	print_title();
	print_borders();
	print_commands();

	print_playing_map(*map);

	bool end = false;
	int kb = 0, key;
	while(key != 'q' && !end) {
		kb = kbhit();
		if(!kb) continue;

		key = getch();

		switch (key) {
		case 'r':
			reset(map);
			break;
		case 'x':
			put_flag(map, cur.x, cur.y);
			if (check_win(*map)) {
				print_playing_map(*map);
				end = true;
			}
			break;
		case 'z':
			if (discover_map(map, cur.x, cur.y) == -1) {
				print_map(*map, map->width, map->height);
				end = true;
				break;
			}
			print_playing_map(*map);
			break;
		default:
			break;
		}

        // input manager
		move(key, &cur, *map);

		gotoxy(offsetx+(cur.x*2), offsety+cur.y);
		setColor(BLACK, WHITE);
		printf("%c", cur.valor);

		kb = 0;
	}

	gotoxy(0, offsety+map->height*2+3);
	setColor(WHITE, BLACK);
	free_map(map);

	return 0;
}

campo_minado* init_map(int w, int h, int bombs) {
	campo_minado* map = malloc(sizeof(campo_minado));

	map->width = w;
	map->height = h;

	map->map = malloc(sizeof(int*)*w);
	map->playing_map = malloc(sizeof(bool*)*w);
	map->flag_map = malloc(sizeof(bool*)*w);

	for (int i = 0; i < map->width; i++) {
		map->map[i] = malloc(sizeof(int)*h);
		map->playing_map[i] = malloc(sizeof(bool)*h);
		map->flag_map[i] = malloc(sizeof(bool)*h);

		for (int j = 0; j < map->height; j++) {
			map->map[i][j] = 0;
			map->playing_map[i][j] = 0;
			map->flag_map[i][j] = 0;
		}
	}

	generate_bombs(map, bombs);
	indexize_map(map);

	return map;
}

void free_map(campo_minado* map) {
	for (int i = 0; i < map->width; i++) {
		free(map->map[i]);
		free(map->playing_map[i]);
		free(map->flag_map[i]);
	}

	free(map->map);
	free(map->playing_map);
	free(map->flag_map);
}

void generate_bombs(campo_minado* cmp, int quantity) {
	if (DEBUG_MAP) {
		for (int i = 0; i < 4; i++) {
			cmp->map[i*3][i*3] = -1;
		}
		return;
	}

	int x = 0,
		y = 0;

	if (quantity > cmp->width*cmp->height) return;


	for (int i = 0; i < quantity; i++) {
		// FIXME: Problema quando todos os espaços já forem preenchidos
		do {
			x = rand()%cmp->width;
			y = rand()%cmp->height;
		} while(cmp->map[x][y]);

		cmp->map[x][y] = -1;
	}
}

int look_around(int** map, int x, int y, int w, int h) {
	int counter = 0;

	if (map[x][y] == -1) return -1;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (
				(i == j && j == 0) ||
				(x+i < 0) ||
				(y+j < 0) ||
				(x+i >= w) ||
				(y+j >= h)
			) continue;

			counter += map[x+i][y+j]==-1;
		}
	}

	return counter;
}

void indexize_map(campo_minado* cmp) {
	for (int i = 0; i < cmp->width; i++) {
		for (int j = 0; j < cmp->height; j++) {
			cmp->map[i][j] = look_around(cmp->map, i, j, cmp->width, cmp->height);
		}
	}
}

void print_map(campo_minado map, int w, int h) {
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			beauty_print(map, i, j, false);
		}
	}
}

void print_playing_map(campo_minado cmp) {
	for (int i = 0; i < cmp.width; i++) {
		for (int j = 0; j < cmp.height; j++) {
			beauty_print(cmp, i, j, true);
		}
	}
}


int discover_map(campo_minado* cmp, int x, int y) {
	bool should_return = (cmp->playing_map[x][y] || cmp->map[x][y] != 0);
	cmp->playing_map[x][y] = 1;
	cmp->flag_map[x][y] = 0;

	if (should_return) return cmp->map[x][y];

	// propagar
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (
				(i == j && j == 0) 		||
				(x+i < 0) 				||
				(y+j < 0) 				||
				(x+i >= cmp->width) 	||
				(y+j >= cmp->height)
			) continue;

			discover_map(cmp, x+i, y+j);
		}
	}

	return cmp->map[x][y];
}

void reset(campo_minado* cmp) {
	free_map(cmp);
	*cmp = *init_map(WIDTH, HEIGHT, BOMBS);
	print_playing_map(*cmp);
}

void beauty_print(campo_minado cmp, int x, int y, bool masked) {
	int displayX = offsetx+x*2;
	int displayY = offsety+y;

	gotoxy(displayX, displayY);
	if (masked) {
		if (cmp.flag_map[x][y]) {
			setColor(LIGHT_RED, BLACK);
			printf("!");
			return;
		}

		if (!cmp.playing_map[x][y]) {
			setColor(DARK_GRAY, BLACK);
			printf("#");
			return;
		}
	}

	if (cmp.map[x][y] == -1) {
		setColor(RED, BLACK);
		printf("@");
	}
	else if (cmp.map[x][y] > 0) {
		setColor(WHITE, BLACK);
		printf("%i", cmp.map[x][y]);
	}
	else {
		setColor(DARK_GRAY, BLACK);
		printf(".");
	}
}

void move(int key, cursor* cur, campo_minado cmp) {
	beauty_print(cmp, cur->x, cur->y, true);

	switch(key) {
        case 72: {
            cur->y = MAX(cur->y-1, 0);
            break;
        }
        case 80: {
            cur->y = MIN(cur->y+1, cmp.height-1);
            break;
        }
        case 75: {
            cur->x = MAX(cur->x-1, 0);
            break;
        }
        case 77: {
            cur->x = MIN(cur->x+1, cmp.width-1);
            break;
        }
        default:
            break;
    }

    if (cmp.playing_map[cur->x][cur->y]) {
    	int num = cmp.map[cur->x][cur->y];

    	if (num == -1)
    		cur->valor = '@';
    	else if (num == 0)
    		cur->valor = '.';
    	else
    		itoanz(num, &(cur->valor));
    }
    else if (cmp.flag_map[cur->x][cur->y])
    	cur->valor = '!';
    else
    	cur->valor = '#';
}

void put_flag(campo_minado* cmp, int x, int y) {
	if (!cmp->playing_map[x][y]) {
		cmp->flag_map[x][y] = !cmp->flag_map[x][y];
	}
}

bool check_win(campo_minado cmp) {
	for (int i = 0; i < cmp.width; i++) {
		for (int j = 0; j < cmp.height; j++) {
			if (
				cmp.map[i][j] == -1 &&
				!cmp.flag_map[i][j]
			) return 0;
		}
	}

	return 1;
}

void print_title(void) {
	gotoxy(offsetx, offsety-2);
	printf("C A M P O  M I N A D O");
}

void print_borders(void) {
	// border top
	gotoxy(offsetx-2, offsety-1);
	printf("+-");
	for (int i = 0; i < WIDTH; i++) {
		printf("--");
	}
	printf("+");

	// border left
	for (int i = 0; i < HEIGHT; ++i) {
		gotoxy(offsetx-2, offsety+i);
		printf("|");
	}

	// border right
	for (int i = 0; i < HEIGHT; ++i) {
		gotoxy(offsetx+WIDTH*2, offsety+i);
		printf("|");
	}

	// border down
	gotoxy(offsetx-2, offsety+HEIGHT);
	printf("+-");
	for (int i = 0; i < WIDTH; i++) {
		printf("--");
	}
	printf("+");
}

void print_commands(void) {
	setColor(DARK_GRAY, BLACK);
	gotoxy(0, offsety+HEIGHT+2);
	printf("z - explorar | x - bandeira | q - sair | setas - mover");
}

//-IMPLEMENTAÇÃO-DAS-UTILIDADES-------------------------------------------------
void setColor(int clr, int backgroud){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (clr)+16*backgroud);
}

void hidecursor(void){
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearScr(int x, int y, int w, int h) {
    for(int i=x; i < x+w; i++){
        for (int j=y; j < j+h; j++) {
        	gotoxy(i, j);
        	printf(" ");
        }
    }
}

//int to string no zero
char *itoanz(int n, char *s) {
    if (n > 0)
        itoa(n, s, 10);
    else
    	*s = ' ';
    return s;
}
//------------------------------------------------------------------------------
