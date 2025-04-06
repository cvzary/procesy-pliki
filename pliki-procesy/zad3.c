/*Napisz program którego rezultatem będzie wydruk zawartości bieżącego katalogu 
poprzedzony napisem „Poczatek" a zakończony napisem „Koniec"*/

#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    printf("Poczatek\n");
    pid_t pid = fork();
    if(pid == 0)
    execlp("ls", "ls", NULL);

    wait(NULL);
    printf("Koniec");
    return 0;
}