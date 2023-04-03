#ifndef QR_CODE_H
#define QR_CODE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


#define NB_MOTIFS_RECHERCHE 3

void copier_matrice(int *source, int *destination, int N);

void appliquer_masque(int masque, int *matrice,int N);

void placer_bit_format(int masque, int *matrice,int N);

int choisir_masque(int *matrice,int N);

void placer_motif_recherche(int *matrice , int N);

void placer_motif_synchronisation(int *matrice , int N);

void placer_motif_alignement(int *matrice ,int N, int version);

void encoder_qr_code(char donnees[], int longueur_donnees, int *matrice,int N,int version);

#endif

