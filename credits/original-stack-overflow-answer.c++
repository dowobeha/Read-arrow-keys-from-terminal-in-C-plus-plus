// Copyright 2025 Stack Overflow user ssinfod (https://stackoverflow.com/users/3585723/ssinfod)
//
// Made available at https://stackoverflow.com/a/33201364
//
// Under CC-BY-SA 3.0 license (https://creativecommons.org/licenses/by-sa/3.0/)

// kbhit
#include <stdio.h>
#include <sys/ioctl.h> // For FIONREAD
#include <termios.h>
#include <stdbool.h>

int kbhit(void) {
    static bool initflag = false;
    static const int STDIN = 0;

    if (!initflag) {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initflag = true;
    }

    int nbbytes;
    ioctl(STDIN, FIONREAD, &nbbytes);  // 0 is STDIN
    return nbbytes;
}

// main
#include <unistd.h>

int main(int argc, char** argv) {
    char c;
    //setbuf(stdout, NULL); // Optional: No buffering.
    //setbuf(stdin, NULL);  // Optional: No buffering.
    printf("Press key");
    while (!kbhit()) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    c = getchar();
    printf("\nChar received:%c\n", c);
    printf("Done.\n");

    return 0;
}
