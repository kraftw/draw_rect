#include <stdio.h>

void draw_rect(int height, int width, char border, char fill) {
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            if (y == 0 || y == height-1) {
                printf("%c", border);
            }
            else if (x == 0 || x == width-1) {
                printf("%c", border);
            }
            else {
                printf("%c", fill);
            }
        }

        printf("\n");
    }
}

int main() {
    draw_rect(4, 4, '@', '*');

    return 0;
}