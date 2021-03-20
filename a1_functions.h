int file_size(FILE *fp);
char **read_words(FILE *fp);
void print_words(char **word_arr);
int* alphabetical_word_count(char **word_arr);
void print_alphabetical_word_count(int* alpha_w_count);
char ***create_alphabetical_array(char **word_arr,int *alpha_w_count);
void print_words_alphabetically(char ***word_arr);
void free_alphabetical_array(char ***word_arr);