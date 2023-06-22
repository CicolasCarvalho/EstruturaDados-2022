#include <stdio.h>
#include <conio.h>

int main(void) {
    int kb, key;

    while(1) {
        kb = kbhit();

        if (kb) {
            key = getch();
            printf("%i\n", key);
        }
    }

    return 0;
}