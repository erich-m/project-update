int letter_count(char*line);
int * text_freq(char * line);
#define COUNT 26
long double chi_sq(int shift,char * line);
int offset(char letter);
char encode(char c,int shift);
/*The below defines the english frequencies for each letter respectively (A-Z)*/
#define EF {0.08167,0.01462,0.02782,0.04253,0.12702,0.02228,0.02015,0.06094,0.06966,0.00153,0.00772,0.04025,0.02406,0.06749,0.07707,0.01929,0.00095,0.05987,0.06327,0.09056,0.02758,0.00978,0.02360,0.00150,0.01974,0.00074}
int encode_shift(char * line,int flag);
int to_decode(int shift);