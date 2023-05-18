#ifndef DATA_ENCODATION_H
#define DATA_ENCODATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>





void appliquer_masque(int masque, int *matrice,int size) ;
void placer_bit_format(int masque, int *matrice,int size) ;
void copier_matrice(int *matrice_source, int *matrice_dest,int size) ;
int choisir_masque(int *matrice,int size) ;
void placer_motif_recherche(int *matrice,int size) ;
void placer_motif_synchronisation(int *matrice,int size) ;
void placer_motif_alignement(int *matrice, int version,int size) ;
void encoder_qr_code(char donnees[], int longueur_donnees,int size, int *matrice) ;

#endif
