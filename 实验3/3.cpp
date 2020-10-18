#include <cstdio>
#include <cstring>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

const int STACK_INIT_SIZE = 100;
const int STACKINCREMENT = 10;

const int M = 15;//行数
const int N = 15;//列数

const int X = 4;//X指示迷宫障碍出现的概率

typedef enum {
    Wall,// 外墙
    Obstacle,// 迷宫内部的障碍
    Way,// 通路
    Impasse,// “死胡同”
    East, South, West, North// 探索方向：东南西北
} MazeNode;

typedef int MazeType[M][N];

typedef struct {
    int x;
    int y;
}PosType;

typedef struct {
    int ord;
    PosType seat;
    int di;
} SElemType;

typedef struct {
    SElemType* base;
    SElemType* top;
    int stacksize;
}SqStack;

bool InitStack(SqStack* S);
bool StackEmpty(SqStack S);
bool Push(SqStack* S, SElemType e);
bool Pop(SqStack* S, SElemType* e);
bool MazePath(MazeType maze, PosType start, PosType end);
void InitMaze(MazeType maze, PosType* start, PosType* end);
bool Pass(MazeType maze, PosType seat);
PosType NextPos(PosType seat, int di);
void FootPrint(MazeType maze, PosType seat);
void MarkPrint(MazeType maze, PosType seat, int mark);
SElemType Construct(int ord, PosType seat, int di);
bool Equals(PosType a, PosType b);
void PaintMaze(MazeType maze);


bool InitStack(SqStack* S) {
    if(S == NULL) {
        return false;
    }

    S->base = (SElemType*) malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(S->base == NULL) {
        exit(-2);
    }

    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;

    return true;
}

bool StackEmpty(SqStack S) {

    if(S.top==S.base)
        return true;
    else
        return false;

}

bool Push(SqStack* S, SElemType e) {
    if(S == NULL || S->base == NULL) {
        return false;
    }

    if(S->top - S->base >= S->stacksize) {
        S->base = (SElemType*) realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(SElemType));
        if(S->base == NULL) {
            exit(-2);
        }
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }

    *(S->top++) = e;

    return true;
}

bool Pop(SqStack* S, SElemType* e) {
    if(S == NULL || S->base == NULL) {
        return false;
    }

    if(S->top == S->base) {
        return false;
    }

    *e = *(--S->top);

    return true;
}


bool MazePath(MazeType maze, PosType start, PosType end) {
    SqStack S;
    SElemType e;
    PosType curPos;
    int curStep;

    InitStack(&S);

    curPos = start;
    curStep = 1;

    do {
        if(Pass(maze, curPos)) {
            FootPrint(maze, curPos);

            e = Construct(curStep, curPos, East);

            Push(&S, e);

            if(Equals(curPos, end) == true) {
                printf("\nfind it！！\n\n");
                return true;
            }

            curPos = NextPos(curPos, East);
            curStep++;

        } else {
            if(!StackEmpty(S)) {
                Pop(&S, &e);

                while(e.di == North && !StackEmpty(S)) {
                    MarkPrint(maze, e.seat, Impasse);
                    Pop(&S, &e);
                }

                if(e.di < North) {
                    ++e.di;

                    MarkPrint(maze, e.seat, e.di);
                    Push(&S, e);
                    curPos = NextPos(e.seat, e.di);
                }
            }
        }
    } while(!StackEmpty(S));

    printf("\nnot find！！\n\n");

    return false;
}

void InitMaze(MazeType maze, PosType* start, PosType* end) {
    int i, j, tmp;

    srand((unsigned) time(NULL));

    for(i = 0; i < M; i++) {
        for(j = 0; j < N; j++) {
            if(i == 0 || j == 0 || i == M - 1 || j == N - 1) {
                maze[i][j] = Wall;
            } else {
                tmp = rand() % X;

                if(tmp == 0) {
                    maze[i][j] = Obstacle;
                } else {
                    maze[i][j] = Way;
                }
            }
        }
    }
    start->x = 1;
    start->y = 0;

    end->x = M - 2;
    end->y = N - 1;

    maze[1][0] = maze[M - 2][N - 1] = Way;
    maze[1][1] = maze[M - 2][N - 2] = Way;
    PaintMaze(maze);
}

bool Pass(MazeType maze, PosType seat) {
    int x = seat.x;
    int y = seat.y;

    if(x < 0 || y < 0 || x > M - 1 || y > N - 1) {
        return false;
    }

    if(maze[x][y] != Way) {
        return false;
    }

    return true;
}

PosType NextPos(PosType seat, int di) {
    PosType tmp = seat;

    switch(di) {
        case East:
            tmp.y++;
            break;
        case South:
            tmp.x++;
            break;
        case West:
            tmp.y--;
            break;
        case North:
            tmp.x--;
            break;
    }

    return tmp;
}
void FootPrint(MazeType maze, PosType seat) {
    MarkPrint(maze, seat, East);
}

void MarkPrint(MazeType maze, PosType seat, int mark) {
    int x = seat.x;
    int y = seat.y;

    maze[x][y] = mark;

    PaintMaze(maze);
}

SElemType Construct(int ord, PosType seat, int di) {
    SElemType e;

    e.ord = ord;
    e.seat = seat;
    e.di = di;

    return e;
}

bool Equals(PosType seat1, PosType seat2) {
    if(seat1.x == seat2.x && seat1.y == seat2.y) {
        return true;
    } else {
        return false;
    }
}

void PaintMaze(MazeType maze) {
    int i, j;

	system("cls");

    for(i = 0; i < M; i++) {
        for(j = 0; j < N; j++) {
            if(maze[i][j] == Wall) {
                printf("▇");
            } else if(maze[i][j] == Obstacle) {
                printf("▓");
            } else if(maze[i][j] == East) {
                printf("→");
            } else if(maze[i][j] == South) {
                printf("↓");
            } else if(maze[i][j] == West) {
                printf("←");
            } else if(maze[i][j] == North) {
                printf("↑");
            } else if(maze[i][j] == Impasse) {
                printf("★");
            } else {
                printf("　");
            }

            if(j != 0 && j % (N - 1) == 0) {
                printf("\n");
            }
        }
    }

    printf("\n");
}

int main(int argc, char* argv[]) {
    MazeType maze;
    PosType start, end;
    char n, Re = 'Y';

    while(Re == 'Y' || Re == 'y') {
        InitMaze(maze, &start, &end);

        MazePath(maze, start, end);

        printf("restart？（Y/N）：");
        scanf("%c%c", &Re, &n);

		printf("\n");
    }

    return 0;
}