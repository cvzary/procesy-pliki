#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

void generate_random_word(char *word, int length) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i < length; ++i) {
        int ranval = rand() % (sizeof(charset) - 1);
        word[i] = charset[ranval];
    }
    word[length] = '\0';
}

int main() {
    srand(time(0));
    const char *env_count = getenv("COUNT");
    const char *env_wordlen = getenv("WORDLEN");
    const char *filename = "ciag.txt";

    int count = atoi(env_count);
    int wordlen = atoi(env_wordlen);

    FILE *file = fopen(filename, "w+");
    if(!file) {
        perror("blad!");
        return 1;
    }
    char word[wordlen * 2 + 1];
    
    generate_random_word(word, wordlen * 2);
    for(int i = 0; i < count; ++i)
    fprintf(file, "%s ", word);
    

    fclose(file);


    return 0;
}