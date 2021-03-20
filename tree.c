#include <stdlib.h>
#include <stdio.h>
#include "tree.h"
#include <string.h>

struct Performance *newPerformance(){
	struct Performance * perf = malloc(sizeof(struct Performance));
	if(perf == NULL){
		fprintf(stderr, "Error: memory allocation for perf failed");
		exit(-1);
	}
	perf->reads = 0;
	perf->writes=0;
	perf->frees=0;
	perf->mallocs=0;

	return(perf);
}

void attachNode(struct Performance *performance,struct Node **node_ptr,void *src,unsigned int width){
	struct Node * new_node = malloc(sizeof(struct Node));//malloc space for a new Node struct (not a new struct pointer)
	if(new_node == NULL){
		fprintf(stderr, "Error: memory allocation for new_node failed");
		exit(-1);
	}
	new_node->data = malloc(width);//malloc WIDTH bytes of data (not size of width)	
	if(new_node->data == NULL){
		fprintf(stderr, "Error: memory allocation for new nodes data failed");
		exit(-1);
	}
	memcpy(new_node->data, src,width);//copy Width bytes of data from source into new nodes data

	new_node->lt = NULL;//set new nodes lt to NULL
	new_node->gte = NULL;//set new nodes gte to NULL

	//copy the ADDRESS of the new node into the POINTER POINTED to by NODe_PTR
	(*node_ptr) = &(*new_node);

	performance->writes++;
	performance->mallocs++;
}

int comparNode(struct Performance *performance,struct Node **node_ptr,int (*compar)(const void *,const void *),void *target){
	performance->reads++;
	return compar(target, (*node_ptr)->data);
}

struct Node **next(struct Performance *performance, struct Node **node_ptr,int direction){
	if(*node_ptr == NULL){
		fprintf(stderr, "Error: next cannot be returned. there is no next node in the tree");
		exit(-1);
	}

	performance->reads++;
	//if direction is less than 0, return the lt node
	if(direction < 0){
		return &((*node_ptr)->lt);
	}else{
		return &((*node_ptr)->gte);
	}
	//if direction is greater than or equal to 0, return the gte node
}

void readNode(struct Performance *performance,struct Node **node_ptr,void *dest,unsigned int width){
	if(*node_ptr == NULL){
		fprintf(stderr, "Error: tree is empty. no nodes to read");
		exit(-1);
	}
	//copy width bytes of data from the data pointer in the node pointed to by the pointer pointed to by node_ptr into dest

	memcpy(dest,(*node_ptr)->data,width);

	performance->reads++;
}

void detachNode(struct Performance *performance, struct Node **node_ptr){
	if(*node_ptr == NULL){
		fprintf(stderr, "Error: tree is empty. no nodes to detach");
		exit(-1);
	}

	struct Node * temp = (*node_ptr);
	free(temp->data);
	temp->data = NULL;
	free(temp);
	*node_ptr = NULL;

	performance->frees++;
}

int isEmpty(struct Performance *performance, struct Node ** node_ptr){
	if(*node_ptr == NULL){
		return 1;//returns 1 if the tree is empty
	}else{
		return 0;//otherwise return 0
	}
}

void addItem(struct Performance *performance,struct Node **node_ptr,int (*compar)(const void *,const void *),void *src,unsigned int width){
	struct Node **temp = node_ptr;
	int added = 0;
	while(added == 0){
		if(isEmpty(performance,temp) == 0){//if the list is not empty
			temp = next(performance,temp,comparNode(performance,temp,compar,src));
		}else{//if the list is empty, use attach node
			attachNode(performance,temp,src,width);
			added++;
		}
	}
}

void freeTree(struct Performance *performance, struct Node **node_ptr){
	struct Node **temp = node_ptr;
	if(isEmpty(performance,next(performance,temp,-1)) == 0 || isEmpty(performance,next(performance,temp,1)) == 0){//if there are nodes that are not empty
		if(isEmpty(performance,next(performance,temp,-1)) == 0){
			next(performance,temp,-1);
		}else{
			detachNode(performance,temp);
		}
		if(isEmpty(performance,next(performance,temp,1)) == 0){
			next(performance,temp,1);
		}else{
			detachNode(performance,temp);
		}

	}else{
		detachNode(performance,temp);
	}
}

int searchItem (struct Performance *performance, struct Node **node_ptr,int(*compar)(const void *,const void*),void * target,unsigned int width){
	struct Node **temp = node_ptr;
	unsigned char tempData[width];
	unsigned char *src = target;
	if(isEmpty(performance,temp) == 0){//is empty returns 0 if the tree is not empty
		readNode(performance,(temp),tempData,width);
		printf("Read from search: %s\nItem to search: %s\n",tempData,src);
		/*if(isEmpty(performance, &(*temp)->lt) == 1 && isEmpty(performance, &(*temp)->gte) == 1 ){//if it gets to here, the loop is at a leaf, and if the data does not match, return 0
			if(compar(tempData,target) == 0){
				return(1);
			}else{
				return(0);
			}
		}*/
		int check = compar(tempData,target);
		printf("Compar output: %d\n",check);
		//printf("Entered search item\n");
		if(compar(tempData,target) < 0){
			//printf("Low\n");
			searchItem(performance,next(performance,temp,-1),compar,target,width);
		}else  if(compar(tempData,target) > 0){
			//printf("High\n");
			searchItem(performance,next(performance,temp,1),compar,target,width);
		}else{
			return(1);
		}
		
	}
	return(0);
}