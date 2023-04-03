# include <pthread.h>
# include <err.h>
#include <stdlib.h>
# include <stdio.h>
#include<unistd.h>
#include "qr.h"

void trouver_positions_alignement(int version, int* positions, int nb_positions,int N) {
    int taille_code = 17 + version * 4;
    int nombre_positions = (version / 7) + 2;

    if (version < 2) {
        nb_positions = 0;
        return;
    }

    nb_positions = nombre_positions;

    if (positions == NULL) {
        positions = malloc(nombre_positions * 2 * sizeof(int));
    }

    for (int i = 0; i < nombre_positions; i++) {
        int pos = 0;
        while (pos < nb_positions) {
            if (positions[pos] == -1) {
                break;
            }
            pos++;
        }

        int max_distance = (pos == 0 || pos == nb_positions - 1) ? taille_code - 7 : taille_code - 1;
        int min_distance = (pos == 0 || pos == nb_positions - 1) ? 0 : -6;

        int distance_min = max_distance;
        int position_alignement = -1;

        for (int j = 0; j < max_distance - min_distance + 1; j++) {
            int distance = distance_points(alignement_position(pos, j), centre_qr_code(taille_code,N),N);

            if (distance < distance_min) {
                distance_min = distance;
                position_alignement = alignement_position(pos, j);
            }
        }

        positions[pos] = position_alignement / N;
        positions[pos + 1] = position_alignement % N;
    }
}

int alignement_position(int pos, int j,int N) {
    if (j == 0) {
        return pos * N + pos;
    }

    int taille_module = (pos == 0 || pos == 0 - 1) ? 2 : 4;

    int distance_bordure = (taille_module - 1) / 2;
    int offset = (j - distance_bordure) * ((pos % 2 == 0) ? -1 : 1);

    return (pos + offset) * N + pos + offset;
}

int distance_points(int pos1, int pos2,int N) {
    int x1 = pos1 / N;
    int y1 = pos1 % N;
    int x2 = pos2 / N;
    int y2 = pos2 % N;

    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int centre_qr_code(int taille_code,int N) {
    return (taille_code - 1) / 2 * N + (taille_code - 1) / 2;
}

void appliquer_masque(int masque, int *matrice, int N) {
    switch (masque) {
        case 0:
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if ((i + j) % 2 == 0) {
                        matrice[i*N+j] ^= 1;
                    }
                }
            }
            break;
        case 1:
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (i % 2 == 0) {
                        matrice[i*N+j] ^= 1;
                    }
                }
            }
            break;
        // Autres cas de masques

    }
}
void placer_bit_format(int masque, int *matrice,int N) {
    int bit_format = 0b101010000010010;

    for (int i = 0; i < 6; i++) {
        matrice[8*N+N - 1 - i] = (bit_format >> i) & 1;
    }

    matrice[8*N+N - 7] = (bit_format >> 6) & 1;
    matrice[8*N+N - 8] = (bit_format >> 7) & 1;
    matrice[7*N+N - 8] = (bit_format >> 8) & 1;
    matrice[5*N+N - 8] = (bit_format >> 9) & 1;
    matrice[4*N+N - 8] = (bit_format >> 10) & 1;
    matrice[3*N+N - 8] = (bit_format >> 11) & 1;
    matrice[2*N+N - 8] = (bit_format >> 12) & 1;
    matrice[1*N+N - 8] = (bit_format >> 13) & 1;
    matrice[0*N+N - 8] = (bit_format >> 14) & 1;

    switch (masque) {
        case 0:
            matrice[8*N+N - 2] = 0;
            break;
        case 1:
            matrice[8*N+N - 3] = 0;
            break;
        // Autres cas de masques (non présentés ici)
    }
}


void copier_matrice(int *matrice_source, int *matrice_dest,int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(matrice_source[i*N+j]<0)
	    {

		matrice_source[i*N+j]=matrice_dest[i*N+j];
	    }
        }
    }
}

int choisir_masque(int *matrice,int N) {
    int NB_MASQUES = 8;
    int *valeurs= calloc(NB_MASQUES , sizeof(int));

    for (int i = 0; i < NB_MASQUES; i++) {
        int *matrice_temp = calloc(N,sizeof(int));
        copier_matrice(matrice, matrice_temp,N);
        appliquer_masque(i, matrice_temp,N);
        placer_bit_format(i, matrice_temp,N);

        int somme = 0;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (matrice_temp[i*N+j] == 1) {
                    somme++;
                }
            }
        }

        valeurs[i] = somme;
    }

    int min = valeurs[0];
    int indice_min = 0;

    for (int i = 1; i < NB_MASQUES; i++) {
        if (valeurs[i] < min) {
            min = valeurs[i];
            indice_min = i;
        }
    }

    return indice_min;
}

void placer_motif_recherche(int *matrice , int N) {
    int position[NB_MOTIFS_RECHERCHE][2] = {{3, 3}, {3, N - 4}, {N - 4, 3}};
    int i = 0;
    while(i<7)
    {
	*(matrice+i)=1;
	*(matrice+i*21)=1;
	*(matrice+22*6-i)=1;
	*(matrice+22*6-i*21)=1;
	i++;

    }
    int j = 0;
    for(int x = 0;x<3;x++)
    {
	for(int y = 0; y<3;y++)
	{
		*(matrice+2*22+y+x*21)=1;
	}
    }

}

void placer_motif_synchronisation(int *matrice , int N) {
    int position = 6;
    int y=6;
    int x = 0;
    for (int i = 0; i < 9; i++) {
        if (x == 0) {
            *(matrice+i) = 1;
            *(matrice+21*i) = 1;
	    x++;
	}
	else{
	    x--;
	}

    }
}


void placer_motif_alignement(int *matrice ,int N, int version) {
    if (version < 2) {
        return;
    }

    int *positions = NULL;
    int nb_positions = 0;

    trouver_positions_alignement(version, positions, nb_positions,N);

    for (int k = 0; k < nb_positions; k++) {
        int i = positions[k] / N;
        int j = positions[k] % N;

        for (int p = -2; p <= 2; p++) {
            for (int q = -2; q <= 2; q++) {
                if (abs(p) == 2 || abs(q) == 2 || (p == 0 && q == 0)) {
                    matrice[(i + p)*N+j + q] = 1;
                }
            }
        }
    }

    free(positions);
}
void encoder_qr_code(char donnees[], int longueur_donnees, int *matrice, int N,int N_version) {
    // Initialisation de la matrice avec des valeurs vides (0)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrice[i * N + j] = 0;
        }
    }

    // Placement des motifs de recherche
    placer_motif_recherche(matrice, N);
    placer_motif_recherche(matrice + (N - 7), N);
    placer_motif_recherche(matrice + N * (N - 7), N);

    // Placement des motifs d'alignement
    placer_motif_alignement(matrice, N, N_version);
    placer_motif_alignement(matrice + (N - 7), N, N_version);
    placer_motif_alignement(matrice + N * (N - 7), N, N_version);

    // Placement des motifs de synchronisation
    placer_motif_synchronisation(matrice, N);

    // Placement du bit de format et du masque
    placer_bit_format(0, matrice, N);
    int masque = choisir_masque(matrice, N);
    appliquer_masque(masque, matrice, N);
    placer_bit_format(masque, matrice, N);

    // Placement des données
    int index_donnees = 0;
    int i = N - 1;
    int j = N - 1;
    int dir = 0; // 0 pour gauche, 1 pour haut

    while (i >= 0) {
        if (j == 6) {
            j--;
        }

        if (matrice[i * N + j] == 0) {
            if (index_donnees < longueur_donnees * 8) {
                int bit = (donnees[index_donnees / 8] >> (7 - (index_donnees % 8))) & 1;
                matrice[i * N + j] = bit;
                index_donnees++;
            } else {
                matrice[i * N + j] = 0;
            }
        }

        if (dir == 0) {
            if (j == 0) {
                i--;
                dir = 1;
            } else {
                j--;
            }
        } else {
            if (j == N - 1) {
                i--;
                dir = 0;
            } else {
                j++;
            }
        }
    }
}

int* creer_matric(){
	int *matr = calloc(441,sizeof(int));
	placer_motif_recherche(matr, 21);
	placer_motif_recherche(matr + 14, 21);
	placer_motif_recherche(matr + 294, 21);
	placer_motif_synchronisation(matr+6*22,21);
	placer_bit_format(0,matr,21);

	int i = 0;
	for(int x = 0; x<21;x++)
	{
		for(int y=0;y<21;y++)
		{
			printf("%i ",matr[x*21+y]);
		}
		printf("\n");
	}

	return matr;

}

