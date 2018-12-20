#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "GenericHashTable.h" 

#define N 5
#define Nchar 500

int sumOfAscii(char* s){
	int sum =0;
	for(int i = 0; s[i] != '\0' ;i++)
		sum+=s[i];
	return sum;
}

int cheackTable(Table* table,int m,int type){
	int blook;
	int d = table->curr_size/table->original_size;
	if(type == 0){
		for(blook =0 ; blook < m; blook ++){
			for(int j = blook*d ; j < blook*d +d; j++){ // over from i (from the hash) and next d index
				// if the cell is empty
				if(table->arr[j]->next == NULL)
					continue;
				
				Object* current = table->arr[j]->next;
				Object* prev = NULL;
				while(current != NULL){
					if(*((int*)current->data)% m != blook){
						return j;
					}
					prev = current;
					current = current->next;
				}
			}
		}
	}
	if(type == 1){
		for(blook =0 ; blook < m; blook ++){
			for(int j = blook*d ; j < blook*d +d; j++){ // over from i (from the hash) and next d index
				// if the cell is empty
				if(table->arr[j]->next == NULL)
					continue;
				
				Object* current = table->arr[j]->next;
				Object* prev = NULL;
				while(current != NULL){
					if(sumOfAscii((char*)current->data)% m != blook){
						return j;
					}
					prev = current;
					current = current->next;
				}
			}
		}
	}
	
	
	return -1;
}

int main() {
	
	srand(time(NULL));   // Initialization, should only be called once.


	int m,type,t;
	char buffer[10];

	m=rand()%7 +1;

	t = rand()%5 +1;
	puts("Enter type:");
	fgets(buffer, 10, stdin);
	type = atoi(buffer);
	
	Table* ht = createTable(m, type, t);
	printf("\n == OriginalSize:%d  listLength:%d type:%d ==\n\n",m,t,type);
	
	if (type == 1){
		char** randomStr = (char**)malloc(sizeof(char*)*Nchar);
		int istr=0;
		puts("enter a to add 5 random objects / r to remove  random objects / s to search  random objects / c to cheack exit to exit");
		fgets(buffer, 10, stdin);
		buffer[strlen(buffer)-1]='\0';
		while(strcmp(buffer,"exit") != 0){
			if(strcmp(buffer,"a") == 0){
				puts("the objects:");
				for(int i=0;i<N;i++){
					int l = rand()%5 +1;
					randomStr[istr] = (char*)malloc(l+1);
					for(int j = 0; j < l;j++){
						randomStr[istr][j] =(rand()%23 + 99);
					}
					printf("ramdomStr: %s, ",randomStr[istr]);
					istr++;
				}
				puts("");
				for(int i=istr-N;i<istr;i++){
					add(ht,randomStr[i]);
				}		
			}
			puts("");
			if(strcmp(buffer,"r") == 0){
				int r = rand()%istr;
				if(removeObj(ht,randomStr[r]) != -1)	
					printf("Removed: %s\n",randomStr[r]);
				else
					printf("NOOOTT found:%s\n",randomStr[r]);
				r = rand()%istr;
				if(removeObj(ht,randomStr[r]) != -1)
					printf("Removed: %s\n",randomStr[r]);
				else
					printf("NOOOTT found:%s\n",randomStr[r]);
			}
			if(strcmp(buffer,"s") == 0){
				int r = rand()%istr;
				Object* obj = search(ht,randomStr[r]);
				if(obj != NULL)
					printf("found:%s\n",(char*)obj->data);
				else
					printf("NOOOTT found:%s\n",randomStr[r]);
				
				r = rand()%istr;
				obj = search(ht,randomStr[r]);
				if(obj != NULL)
					printf("found:%s\n",(char*)obj->data);	
				else
					printf("NOOOTT found:%s\n",randomStr[r]);				
			}
			if(strcmp(buffer,"c") == 0){
				int index = cheackTable(ht,m,type);
				if(index > -1 )
					printf("ERRRRROOOOOORRRRR in index:%d\n",index);
				else{
					puts(" === cheack: OK! ====");
					puts(" === cheack: OK! ====");
					puts(" === cheack: OK! ====");
				}
			}
			
			
			if(strcmp(buffer,"c") != 0)
				printTable(ht);
			puts("enter a to add 5 random objects / r to remove  random objects / s to search  random objects / c to cheack exit to exit");					
			fgets(buffer, 10, stdin);
			buffer[strlen(buffer)-1]='\0';
		}
		
		for(int i=0;i<istr;i++){
			free(randomStr[i]);
		}
		free(randomStr);
	}
	
	
	
	if (type == 0){
		puts("enter a to add 5 random objects / r to remove  random objects / s to search  random objects / c to cheack exit to exit");
		fgets(buffer, 10, stdin);
		buffer[strlen(buffer)-1]='\0';
		while(strcmp(buffer,"exit") != 0){
			int n[N];
			if(strcmp(buffer,"c") != 0){
				puts("the objects:");
				for(int i=0;i<N;i++){
					n[i] = (rand()%40);
					printf(" %d, ",n[i]);
				}
				puts("");
			}
			if(strcmp(buffer,"a") == 0){
				for(int i=0;i<N;i++){
					add(ht,&n[i]);
				}		
			}
			if(strcmp(buffer,"r") == 0){
				for(int i=0;i<N;i++){
					removeObj(ht,&n[i]);
				}		
			}
			if(strcmp(buffer,"s") == 0){
				for(int i=0;i<N;i++){
					Object* obj = search(ht,&n[i]);
					if(obj != NULL)
						printf("found:%d\n",*((int*)obj->data));
				}		
			}
			if(strcmp(buffer,"c") == 0){
				int index = cheackTable(ht,m,type);
				if(index > -1 )
					printf("ERRRRROOOOOORRRRR in index:%d\n",index);
				else{
					puts(" === cheack: OK! ====");
					puts(" === cheack: OK! ====");
					puts(" === cheack: OK! ====");
				}
			}
			
			
			
			if(strcmp(buffer,"c") != 0)
				printTable(ht);
			puts("enter a to add 5 random objects / r to remove  random objects / s to search  random objects / c to cheack exit to exit");
			fgets(buffer, 10, stdin);
			buffer[strlen(buffer)-1]='\0';
		}
	}
	
	freeTable(ht);
	return 0;
	
}
