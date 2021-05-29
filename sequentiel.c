#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int LIMITE_SUP = 1000000;

void prime(int debut, int fin){
    int i, j;
    int nums[fin];

    for(i = debut; i < fin + 1; i++){
        if(i == 0 || i == 1){
            nums[i] = 0;
        }else{
            nums[i] = 1;
        }
    }

    for (i = debut; i <= fin; i++) {
        // 0 et 1 ne sont pas des nombres premiers donc ils ne sont pas traités
        if (i == 1 || i == 0)
            continue;
 
        for (j = 2; j < i; j++) {
            if (i % j == 0) {
                nums[i] = 0;
                break;
            }
        }
    }
    // Décommentez le bloc suivant pour l'affichage des nombres premiers et du total de nombres premiers trouvés
    int count = 0;
    for(i = debut; i <= fin; i++){
        if(nums[i] == 1){
            count++;
            printf("%d, ", i);
        }
    }
    printf("\nNombres premiers trouvés dans l'intervalle %d - %d : %d\n", debut, fin, count);
}

int main(int argc, char *argv[]){
    // Si aucune valeur n'est passée en paramètre, l'intervalle par défaut est 2 - 1 000 000 
    int deb = argc < 3 ? 2 : atoi(argv[1]); 
    int fin = argc < 3 ? 1000000 : atoi(argv[2]); 
    prime(deb, fin);
    return  0;
}