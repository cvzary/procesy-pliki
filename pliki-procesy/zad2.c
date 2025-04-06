/*Napisz program tworzący dwa procesy. Każdy ze stworzonych procesów powinien utworzyć proces - potomka. 
Należy wyświetlać identyfikatory procesów rodziców i potomków po każdym wywołaniu funkcji fork.*/
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
        pid_t pid1, pid2;

        pid1 = fork();

        if(pid1 == 0) {
                printf("im A pid=%d, ppid=%d\n", getpid(), getppid());

                pid_t pid1A = fork();
                if(pid1A == 0) {
                        printf("im child of A pid=%d, ppid=%d\n", getpid(), getppid());
                        exit(0);
                }
                wait(NULL);
                exit(0);
        }

        pid2 = fork();

        if(pid2 == 0) {
                printf("im B pid=%d, ppid=%d\n", getpid(), getppid());

                pid_t pid2A = fork();
                if(pid2A == 0) {
                        printf("im child of B pid=%d, ppid=%d\n", getpid(), getppid());
                        exit(0);
                }
                wait(NULL);
                exit(0);
        }

        wait(NULL);
        wait(NULL);
                
        return 0;
}