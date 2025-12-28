#include <stdio.h>

/* NASM function */
extern void show_gui(void);

int main(void)
{
    printf("Calling NASM GUI...\n");
    show_gui();
    printf("Returned to C.\n");
    return 0;
}
