#ifndef MASKING_H
#define MASKING_H



int*  apply_mask(int* data, int size,char *mask);
int adjacent_row(int i, int j ,int *masked_data,size);
int adjacent_col(int i, int j, int *masked_data,size);
int penalty_N1(int *masked_data,size);
int penalty_N2(int *masked_data,size);
int finder_row(int i, int* masked_data, int size);
int finder_col(int j,int *masked_data,int size);
int penalty_N3(int *masked_data,size);
int penalty_N4(int *masked_data,int size);
int penalties(int N1,int N2,int N3,int N4);

#endif 
