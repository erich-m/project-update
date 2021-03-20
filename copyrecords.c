#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "a3_functions.h"


int main (int argc, char * argv[]){
	int flags[4] = {0,0,0,0};/*Store the state of my flags in the following order:  -F -O -D -r*/
	int a = 1;
	int in_arg = 0;
	int out_arg = 0;
	int d_arg = 0;
	while(argv[a] != NULL){/*set up a while loop to loop through the contents of the command line, excluding the execution command*/
	/*searches for a hyphen signifying a flag. Depending on the type of flag, either file based or output based*/
		if(argv[a][0] == '-'){/*if the argument starts with a dash, it is a flag*/
			if(argv[a][1] != 'F' && argv[a][1] != 'O' && argv[a][1] != 'D'){/*checks the next character for the flag*/
				if(argv[a][1] == 'r'){/*r is the only flag that does not come with a file so it will print an error if it sees anything that is not an file flag, an error will be created*/
					flags[3]++;
				}else{
					printf("Please check the command line arguments");
					return(-1);
				}
			}else if (argv[a][1] == 'F'){/*sets an int to the index location of the file*/
				in_arg = a + 1;
				flags[0]++;
			}else if (argv[a][1] == 'O'){/*sets an int to the index location of the file*/
				out_arg = a + 1;
				flags[1]++;
			}else if (argv[a][1] == 'D'){/*sets an int to the index location of the file*/
				d_arg = a + 1;
				flags[2]++;
			}
			if((argv[a][1] == 'F' || argv[a][1] == 'O' || argv[a][1] == 'D')&& argv[a][0] == '-'){/*this is an extra check to see if a fiel based flag is entered. Will add a second 1 to a so that it skips processing of the file name*/
				a++;
			}
		}else{
			fprintf(stderr,"Please check that the arguments are correct\n");
			return(-1);
		}
		a++;
	}

	if(flags[0] + flags[1] < 2){/*From the courselink announcements: "a missing -F should be an error as should a missing -O"*/
		printf("Please make sure that a -F and -O are provided in the command line");
		return(-1);
	}/*if there is a -F, -r may or may not be provided.Similarly, -D may or may not be provided*/

		int es = 0;/*encode shift variable*/
		int ds = 0;/*decode shift variable*/
	/* if -D and file are provided, find the shift using the code from question 2.The shift for the text in the provided file is the shift for the records in the binary file*/
	
	if(flags[2] == 1){/*if there is a a -D flag, it will open the file, read in the full file by reading in chars, and using the created functions to decode it and get the shift value*/
		char *text_input = NULL;/*standard file input stuff*/
		FILE *fpIn = NULL;
		fpIn = fopen(argv[d_arg],"r");/*open fIn from reading*/
		int sz = 0;
		fseek(fpIn, 0L, SEEK_END);
		sz = ftell(fpIn);
		rewind(fpIn);
		text_input = malloc(sz + 2);
		if(fpIn == NULL){
			fprintf(stderr,"file not found\n");
			return(1);
		}/*standard file input stuff*/
		int count = 0;/*count is the number of chars read in by the following loop*/
		char nextChar;
		nextChar = fgetc(fpIn);/*begin reading in chars from file*/
		while(nextChar != EOF){
			text_input[count] = nextChar;
			count++;
    		nextChar = fgetc(fpIn);
		}
		text_input[count] = '\0';/*set the last char to null*/
		es = encode_shift(text_input,0);
		ds = to_decode(es);/*find the shift to decode the records*/
		free(text_input);
		fclose(fpIn);
	}else{
		ds = es;/*else, leave ds as 0*/
	}
/*If the user gets here, they HAVE given the correct flags to allow reading and writing to the files*/
	if(flags[0] == 1 && flags[1] == 1){/*check to be safe*/
		FILE *fp = NULL;
		fp = fopen(argv[in_arg],"rb");
		
		FILE *fpOut = NULL;
		fpOut = fopen(argv[out_arg],"wb");

		if(fp == NULL || fpOut == NULL){
			printf("The file could not be opened");
			return(-1);
		}
		char field_1[24];
		double field_2[24];
		char field_3[144];
		int field_4[12];

		int rec = 1;

		if(flags[3] == 0){/*if -r is NOT entered  then print out all the records in normal order as they are read in*/
		/*read in from the record file according to the field type, and print to the output file with encode of ds. If it is 0, it will not shift anything*/
			while((fread(field_1,sizeof(char)*24,1,fp)) != 0){
				if(rec > 1){
					fprintf(fpOut,"\n");
				}
				/*print out with encode*/
				int f1 = 0;
				while(field_1[f1] != '\0'){
					fprintf(fpOut,"%c",encode(field_1[f1],ds));
					f1++;
				}
				fprintf(fpOut,"\n");
				/*print with encode*/
				fread(field_2,sizeof(double)*24,1,fp);
				int d = 0;
				for(d = 0;d < 24;d++){
					fprintf(fpOut,"%f ",field_2[d]);
				}
				fread(field_3,sizeof(char)*144,1,fp);
				fprintf(fpOut,"\n");
				/*print out with encode*/
				int f3 = 0;
				while(field_3[f3] != '\0'){
					fprintf(fpOut,"%c",encode(field_3[f3],ds));
					f3++;
				}
				fprintf(fpOut,"\n");
				/*print with encode*/
				fread(field_4,sizeof(int)*12,1,fp);
				int i = 0;
				for(i = 0;i < 12;i++){
					fprintf(fpOut,"%d ",field_4[i]);
				}
				rec++;
			}
		}else if(flags[3] == 1){/* if -r IS entered, print it out in reverse order*/
			/*similary process to the above...uses the following:
			1. gets file size
			2. seek to the END of the file
			3. Enter while loop to check that the file pointer location is not less than 0
				a.If the pointer can successfully backtrack by the offset of the total record byte size from the file 
				(SEEK_END - (-record size)*(the counter)) will give the location of the new pointer, complete that action.
				This moves the file pointer to the start of a new record
				b.Read in the file based on field type
				c. Increase counter by 1 so that the pointer is offset from the end by the size of that number of records*/
			int rec_size = (sizeof(char)*24)+(sizeof(double)*24)+(sizeof(char)*144)+(sizeof(int)*12);
			fseek(fp,0,SEEK_END);
			long int f_length = ftell(fp);
			int rec = 1;
			while(f_length-(rec_size * rec) >= 0){
				fseek(fp,-rec_size*rec,SEEK_END);/*jump to the end of the file offset by negative record size so it starts at the beginning of the record*/
				if(rec > 1){
					fprintf(fpOut,"\n");
				}
				fread(field_1,sizeof(char)*24,1,fp);/*read in field 1*/
				/*print out with encode*/
				int f1 = 0;
				while(field_1[f1] != '\0'){
					fprintf(fpOut,"%c",encode(field_1[f1],ds));
					f1++;
				}
				fprintf(fpOut,"\n");
				/*print with encode*/

				fread(field_2,sizeof(double)*24,1,fp);/*read in field 2*/
				int d = 0;
				for(d = 0;d < 24;d++){
					fprintf(fpOut,"%f ",field_2[d]);
				}
				fread(field_3,sizeof(char)*144,1,fp);/*read in field 3*/
				fprintf(fpOut,"\n");
				/*print out with encode*/
				int f3 = 0;
				while(field_3[f3] != '\0'){
					fprintf(fpOut,"%c",encode(field_3[f3],ds));
					f3++;
				}
				fprintf(fpOut,"\n");
				/*print with encode*/
				fread(field_4,sizeof(int)*12,1,fp);/*read in field 4*/
				int i = 0;
				for(i = 0;i < 12;i++){
					fprintf(fpOut,"%d ",field_4[i]);
				}
				rec++;
			}
		}
		fclose(fp);/*free the file pointers*/
		fclose(fpOut);
	}else {/*From the courselink announcements: "a missing -F should be an error as should a missing -O"*/
		printf("Please make sure that a -F and -O are provided in the command line");
		return(-1);
	}/*if there is a -F, -r may or may not be provided.Similarly, -D may or may not be provided*/

	return(0);
}