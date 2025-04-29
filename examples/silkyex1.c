#include <stdio.h>
#include <silky.h>
int
main(int argc, char** argv)
{
    char* my_str = slkinit("Nope");
    printf("woah: %s\n", my_str);
    slkfree(my_str);
}