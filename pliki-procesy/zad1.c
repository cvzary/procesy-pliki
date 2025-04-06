/*
Stwórz plik, w programie C dodaj jakiś ciąg znaków do tego pliku.
Jako rozszerzenie poprzedniego zadania program powinien przyjmować nazwę pliku. Program powinien sprawdzić czy plik istnieje 
(jeśli nie, rzucić odpowiednim błędem) i zapisać jakąś zawartość do niego. Jeśli plik istnieje to zawartość powinna być dopisywana,
 a nie nadpisywana.
Kolejnym rozszerzeniem jest sprawdzenie jaką długość ma zawartość pliku. Jeśli powyżej 10 znaków, dopisujemy nową zawartość, 
jeśli nie, pomijamy.
Po rozwiązaniu zadań pora na następne:
Teraz, gdy plik nie istnieję należy stworzyć dany plik. Zawartością tego pliku mają być wygenerowane pseudolosowo liczby 
( maksymalna ilość tych liczb powinna być brana ze zmiennej środowiskowej - getenv). Na koniec program powinien podać ilość 
 wygenerowanych liczb - ale tylko przez czytanie zawartości pliku!
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Poprawne uzycie: %s <nazwa_pliku>\n", argv[0]);
        return 1;
    }

    
    const char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Plik %s nie istnieje, tworze nowy...\n", filename);
        char *env_val = getenv("COUNT");
        if(env_val == NULL) {
            perror("Nie znaleziono zmiennej srodowiskowej \"COUNT\"");
            return 1;
        }
        int count = atoi(env_val);
        file = fopen(filename, "w");
        if (file == NULL) {
            perror("Blad przy otwieraniu pliku!");
            return 1;
        }
        srand(time(0));
        for(int i = 0; i < count; ++i) {
            int rand_num = rand() % 100;
            fprintf(file, "%d ", rand_num);
        }
        fclose(file);
    }   else {
        fclose(file);
        fopen(filename, "r");
        int number, total = 0;
        while(fscanf(file, "%d", &number) == 1)
            total++;
        printf("Liczba znalezionych cyfr w pliku: %d\n", total);
        fclose(file);
    }
    
    return 0;
}