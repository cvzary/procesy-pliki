/*3. Napisz program który utworzy dowolny plik o dowolnej nazwie (jeśli już taki istnieje, program powinien go otworzyć w trybie
„dopisywania”). Program powinien dopisywać losowo wygenerowane ciągi znaków - liczba słów powinna być uzależniona od 
zmiennej środowiskowej, jak również maksymalna liczba znaków). 
W programie powinny także powstać dwa osobne procesy które zrobią dokładnie to samo, co główny proces.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

char random_char() {
    int r = rand() % 62;
    if(r < 10)
        return '0' + r;
    else if(r < 36)
        return 'A' + (r - 10);
    else
        return 'a' + (r - 36);
}

void write_random_words(const char* filename, int num_words, int word_len) {
    FILE *file = fopen(filename, "a");
    if(!file) {
        perror("blad przy otwieraniu pliku!");
        exit(1);
    }

    for(int i = 0; i < num_words; ++i) {
        int len = rand() % word_len + 1;
            for(int j = 0; j < len; ++j)
                fputc(random_char(), file);
        fputc(' ', file);
    }
    fclose(file);
}

int main() {
    srand(time(0));
    const char *filename = "plik.txt";


    
    const char *num_env = getenv("MAX_WORDS");
    const char *word_env = getenv("WORD_LEN");
    

    int num_words = atoi(num_env);
    int word_len = atoi(word_env);

    write_random_words(filename, num_words, word_len);

    pid_t pid1, pid2;

    pid1 = fork();
    if(pid1 == 0) {
        write_random_words(filename, num_words, word_len);
        exit(0);
    } 

    pid2 = fork();
    if(pid2 == 0) {
        write_random_words(filename, num_words, word_len);
        exit(0);
    }

    wait(NULL);
    wait(NULL);

    return 0;
}