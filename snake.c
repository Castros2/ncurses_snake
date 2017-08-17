#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define DELAY 40000

//detect keyboard input (credit to stackoverflow user Matthew Slattery)
int kbhit(void){
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

void wrap_x(int* x, int max_x){
    if(*x < 0){
        *x = max_x;
    } else if (*x > max_x) {
        *x = 0;
    }
}

void wrap_y(int* y, int may_y){
    if(*y < 0){
        *y = may_y;
    } else if (*y > may_y) {
        *y = 0;
    }
}

int main(int argc, char *argv[]){
    int x = 0, y = 0;
    int food_x = 0, food_y = 0;
    int max_y = 0, max_x = 0;
    int next_x = 0;
    int direction_x = 1;
    int direction_y = 0;
    int eaten = 1;

    time_t t;

    srand((unsigned) time(&t));

    initscr();
    noecho();
    curs_set(FALSE);

    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    getmaxyx(stdscr, max_y, max_x);

    while(1){
        clear();
        mvprintw(y, x, "o");

        if (eaten){
            food_y = rand() % max_y;
            food_x = rand() % max_x;
            eaten = 0;
        }

        mvprintw(food_y, food_x, "#");

        refresh();

        if(kbhit()){
            switch (getch()){
                //user presses 'w'
                case 119:
                    direction_y = -1;
                    direction_x = 0;
                    break;
                //user presses 'a'
                case 97:
                    direction_y = 0;
                    direction_x = -1;
                    break;
                //user presses 's'
                case 115:
                    direction_y = 1;
                    direction_x = 0;
                    break;
                //user presses 'd'
                case 100:
                    direction_y = 0;
                    direction_x = 1;
                    break;

            }
        }

        usleep(DELAY);

        x += direction_x;
        wrap_x(&x, max_x);
        y += direction_y;
        wrap_y(&y, max_y);

        if(x == food_x && y == food_y){
            eaten = 1;
        }

    }

}
