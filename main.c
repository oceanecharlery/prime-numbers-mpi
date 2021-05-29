#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int LIMITE_SUP = 1000000;
int rank, size;
MPI_Status status;
MPI_Request request;

void prime(int debut, int fin){
    int a, i, j, bas, haut, portion;   
    int nums[fin];
    
    for(i = debut; i < fin + 1; i++){
        if(i == 0 || i == 1){
            nums[i] = 0;
        }else{
            nums[i] = 1;
        } 
    }
    portion = (fin - debut) / size;
    
    if(rank == 0){
        for(i = 1; i<size; i++){
            bas = debut + (i * portion);
            if(((i + 1) == size) && (((fin - debut) % size) != 0)){
                /*Si la quantité de nombres dans l'intervalle n'est pas divisible par 
                la quantité de processus, le dernier processus prend les nombres restants */
                haut = fin;
            }else{
                haut = bas + portion;
            }

            /* L'utilisation de MPI_SSend au lieu de MPI_Send permet de synchroniser 
            l'envoi et la réception des données, les nombres premiers renvoyés par les processus
            seront donc triés dans l'ordre croissant */
            MPI_Send(&bas, 1, MPI_INT, i, 1+i, MPI_COMM_WORLD);
            MPI_Send(&haut, 1, MPI_INT, i, 2+i, MPI_COMM_WORLD);
        }
        bas = debut;
        haut = bas + portion;
    }

    if(rank > 0){
        MPI_Recv(&bas, 1, MPI_INT, 0, 1+rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&haut, 1, MPI_INT, 0, 2+rank, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    for (a = bas; a <= haut; a++) {
        // 0 et 1 ne sont pas des nombres premiers donc ils ne sont pas traités
        if (a == 1 || a == 0)
            continue;
        // Si le nombre est divisible par un autre nombre que 1 et lui même il n'est pas premier
        for(j = 2; j < a; j++){
            if(a % j == 0){
                nums[a] = 0;
                break;
            }
        }
    }
    // Décommentez le bloc suivant pour l'affichage des nombres premiers
    for(a = bas; a <= haut; a++){
        if(nums[a] == 1){
            printf("%d ", a);
        }
    }
    printf("\nFin du processus %d, intervalle %d - %d.\n", rank, bas, haut);
}

int main(int argc, char *argv[]){
    MPI_Init(&argc, &argv);
	MPI_Comm_rank (MPI_COMM_WORLD, &rank);
	MPI_Comm_size (MPI_COMM_WORLD, &size);
    
    /* Si aucune valeur n'est passée en paramètre, l'intervalle par défaut est 2 - 1 000 000 */
    int deb = argc < 3  ? 2 : atoi(argv[1]); 
    int fin = argc < 3  ? LIMITE_SUP : atoi(argv[2]);
    prime(deb, fin);
    
    MPI_Finalize();
    
    return 0;
}
