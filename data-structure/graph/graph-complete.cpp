#include<stdio.h>
#include<malloc.h>

struct node {
	int data;
	int limit;
	node * ref[10];
};

void show( node * current, FILE * fp2 ) {
	if(current != NULL ) {
		fprintf(fp2, " %d  ", current->data );
		for(int i=0;i<current->limit; i++)  
			show(current->ref[i], fp2);
	}
}

node * search( FILE * fp2, node *current, int val) {
	if( current == NULL ) 
		return NULL;

	if( current->data == val ) 
		return current;
	
	for(int i=0; i<current->limit; i++ ) {
		node * res = search( fp2, current->ref[i], val);
		if( res != NULL )
			return res;	
	} 
	
	return NULL;
}

void insert(FILE *fp, FILE * fp2, node * head, node * current) {
	int val, limit;
	int start, end;
	fscanf(fp, "%d %d", &val, &limit);
	fprintf(fp2, "%d %d \n", val, limit);
	if( val != -1 ) {
		node * info = search(fp2, head, val);
		if(info != NULL) {
			current = info;
			start = info->limit;
			end = start + limit;
		}else {
			current->limit = limit;
			current->data = val;
			start = 0, end = limit;
		}

		for(int i=start; i<end; i++) {
			current->ref[i] = (node *) malloc( sizeof(node) );
			insert(fp, fp2, head, current->ref[i]);
			if( current->ref[i]->limit == 0 ) 
				current->ref[i] = NULL;
		}
	}
}

int main() {
	node * head, *current;
	FILE *fp, *fp2;
	int searchVal;
	
	fp = fopen("./input.txt", "r");
	fp2 = fopen("./output.txt", "a");

	if( fp != NULL && fp2 != NULL ) {
		fprintf(fp2, "\n\n ++++++++++++++++  graph-same-node.cpp ++++++++ \n\n");
		node * head = (node *) malloc(sizeof(node));
		insert(fp, fp2, head, head);

		fprintf(fp2, "\n\n #############  Show  ################## \n");
		show(head, fp2);
	}

	return 0;
}
