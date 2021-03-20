struct Double_Array *double_array(int row,int col);
struct Double_Array {/*decalre the structure*/
	int rowsize;/*int for row size*/
	int colsize;/*int for col size*/
	double** array;/*create double array*/
};
void randomize_array(struct Double_Array * d_array,double a,double b);
double rand_double(double a,double b);
int free_array(struct Double_Array *d_array);
int swap_rows(struct Double_Array *d_array,int a,int b);
int swap_columns(struct Double_Array *d_array,int a,int b);
void print_array(struct Double_Array* d_array);
struct Double_Array *shallow_copy(struct Double_Array *d_array);
struct Double_Array *deep_copy(struct Double_Array *d_arary);
void print_struct(struct Double_Array* d_array,char *header);