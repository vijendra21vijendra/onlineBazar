#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
// first fit ---> first position where a greater or equal free area found
// nextFit --> next of the last used position 
// bextFit ---> means a location which is smallest of largest the required
// it is done only for integers 
typedef struct{
	int arr[2000];
	// 500 1250 1600 2000
}myHeap;

myHeap heap;
// global heap variable

typedef struct allocated{
	char varName[20];
	int *address;
	int size;
	struct allocated *next;
}allocList;

typedef struct freed{
	int *address;
	int size;
	struct freed *next;
}freeList;

freeList* makeNodeFreeList(int *address,int size){
	
	freeList *fp = (freeList*)malloc(sizeof(freeList));
	fp->address = address;
	fp->size = size;
	fp->next = NULL;
}

allocList* makeNodeAllocList(char name[20],int *address,int size){
	
	allocList *fp = (allocList*)malloc(sizeof(allocList));
	fp->address = address;
	fp->size = size;
	strcpy(fp->varName,name);
	fp->next = NULL;
}

typedef struct lists{
	allocList *al;
	freeList *fl;
	int *fornextfit;
}list;

list varList;
// global list variable

void printFreeList(){
	printf("free list is:-\n");
	freeList *fp = varList.fl;
	while(fp!=NULL){
		printf("%d %d\n",fp->address,fp->size);
		fp = fp->next;
	}
}

void printAllocatedList(){
	printf("allocated list is:-\n");
	allocList *fp = varList.al;
	while(fp!=NULL){
		printf("%s %d %d\n",fp->varName,fp->size,fp->address);
		fp = fp->next;
	}
}

void Initialize(myHeap *ptr){
	int i;
	// for heap 
	for(i=0;i<2000;i++){
	   ptr->arr[i] = -1;
	}
	varList.al = NULL;
	freeList *x,*y;
	x = makeNodeFreeList(&(heap.arr[0]),500);
	varList.fl = x;
	x = makeNodeFreeList(&(heap.arr[500]),750);
	varList.fl->next = x;
	y = x;
	x = makeNodeFreeList(&(heap.arr[1250]),350);
	y->next = x;
	y=x;
    x = makeNodeFreeList(&(heap.arr[1600]),400);
    y->next = x;
    varList.fornextfit = &(heap.arr[0]);
}


int firstFit()
{
	int status=0;
	int n,i;
	printf("enter the size: ");
	scanf("%d",&n);
	char name[20];
	printf("enter name of variable: ");
	scanf("%s",name);
	int mem[n];
	int *add;
	for(i=0;i<n;i++){
		printf("enter data: ");
		scanf("%d",&mem[i]);
	}
	
	freeList *fp,*prev;
	prev = fp = varList.fl;
	while(fp!= NULL &&fp->size < n){
		prev = fp;
		fp = fp->next;
	}
	if(fp==NULL){
		status=0;
		printf("cannot be allocated\n");
	}else{
		int *x;
		x = fp->address;
		add = x;
		for(i=0;i<n;i++){
			x[i] = mem[i];
		}
		if(fp==prev){
			if(fp->size==n){
				varList.fl = fp->next;
				free(fp);
			}else{
				// change value
				fp->size -= n;
				fp->address += n;
			}
		}else{
			if(fp->size==n){
				// delete node 
				prev->next = fp->next;
				free(fp);
			}else{
				// change value
				fp->size -= n;
				fp->address += n;
			}
		}
		
		if(add+n > varList.fornextfit){
			varList.fornextfit = add+n;
		}
		// now i have to add it into allocated list
		allocList *y,*z;
		
		allocList *root = makeNodeAllocList(name,add,n);
		
		z = y = varList.al;
		if(y==NULL){
			varList.al = root;
		}else{
			if(root->address < y->address){
				varList.al = root;
				root->next = y;
			}else{
			while(y->address < root->address){
				z = y;
				y = y->next;
			}
			z->next = root;
			root->next = y;	
			}
		}
      printf("successfully done first Fit\n");
      status=1;
	}
	printAllocatedList();
	printFreeList();
  return status;	
}

int bestFit(){
	printf("inside the best Fit\n");
	int status=0;
	int n,i;
	printf("enter the size: ");
	scanf("%d",&n);
	char name[20];
	printf("enter name of variable: ");
	scanf("%s",name);
	int mem[n];
	int *add;
	for(i=0;i<n;i++){
		printf("enter data: ");
		scanf("%d",&mem[i]);
	}
	freeList *fp,*prev,*ourPointer;
	ourPointer = NULL;
	int leastMax = 2000;
	prev = fp = varList.fl;
	while(fp!= NULL){
		if(fp->size > n && fp->size < leastMax){
			ourPointer = fp;
			leastMax = fp->size;
		}
		fp = fp->next;
	}
//	printf("never happened\n");
	if(ourPointer==NULL){
		status=0;
		printf("cannot be allocated\n");
	}else{
		fp = varList.fl;
	//	printf("inside the else condition\n");
		if(fp!=ourPointer){
			while(fp->next!=ourPointer){
				fp = fp->next;
			}
		//	printf("fp and urpointer not same\n");
		}
		//printf("out of it\n");
		int *x;
		x = ourPointer->address;
		add = x;
		for(i=0;i<n;i++){
			x[i] = mem[i];
		}
	//	printf("value done\n");
		if(ourPointer==fp){
			
			if(ourPointer->size==n){
				varList.fl = ourPointer->next;
				free(ourPointer);
			}else{
				// change value
				ourPointer->size -= n;
				ourPointer->address += n;
			}
			//printf("same pointers\n");
		}else{
			if(ourPointer->size==n){
				// delete node 
				fp->next = ourPointer->next;
				free(ourPointer);
			}else{
				// change value
				ourPointer->size -= n;
				ourPointer->address += n;
			}
		//	printf("differ pointer\n");
		}
		
		if(add+n > varList.fornextfit){
			varList.fornextfit = add+n;
		}
		// now i have to add it into allocated list
		allocList *y,*z;
		
		allocList *root = makeNodeAllocList(name,add,n);
		
		z = y = varList.al;
		if(y==NULL){
			varList.al = root;
		}else{
	             if(root->address < y->address){
				varList.al = root;
				root->next = y;
			}else{
			//	printf("at right");
			while(y!=NULL &&y->address < root->address){
				z = y;
				y = y->next;
			}
			z->next = root;
			root->next = y;	
			}
		}
      printf("successfully done best Fit\n");
      status=1;
	}
	printAllocatedList();
	printFreeList();
   return status;	
}

int nextFit()
{
	int status=0;
	int n,i;
	printf("enter the size: ");
	scanf("%d",&n);
	char name[20];
	printf("enter name of variable: ");
	scanf("%s",name);
	int mem[n];
	int *add;
	for(i=0;i<n;i++){
	//	printf("enter data: ");
		//scanf("%d",&mem[i]);
		mem[i] = i+1;
	}
//	printf("values done\n");
	freeList *fp,*prev;
	prev = fp = varList.fl;
	while(fp!=NULL && fp->address<varList.fornextfit){
		prev = fp;
		fp = fp->next;
	}
	while(fp!= NULL &&fp->size < n){
		prev = fp;
		fp = fp->next;
	}
	if(fp==NULL){
		status=0;
		printf("cannot be allocated\n");
	}else{
	//	printf("right");
		int *x;
		x = fp->address;
		add = x;
		for(i=0;i<n;i++){
			x[i] = mem[i];
		}
		if(fp==prev){
			if(fp->size==n){
				varList.fl = fp->next;
				free(fp);
			}else{
				// change value
				fp->size -= n;
				fp->address += n;
			}
		//	printf("both are equal\n");
		}else{
			if(fp->size==n){
				// delete node 
				prev->next = fp->next;
				free(fp);
			}else{
				// change value
				fp->size -= n;
				fp->address += n;
			}
		//	printf("both differ\n");
		}
		if(add+n > varList.fornextfit){
			varList.fornextfit = add+n;
		}
		// now i have to add it into allocated list
		allocList *y,*z;
		
		allocList *root = makeNodeAllocList(name,add,n);
		//printf("in allocation\n");
		z = y = varList.al;
		if(y==NULL){
			//printf("nothing allocated till now\n");
			varList.al = root;
		}else{
			while(y!=NULL && y->address < root->address){
				z = y;
				y = y->next;
			}
			//printf("%d is y",y);
			z->next = root;
			root->next = y;	
			}
      printf("successfully done nextFit\n");
      status=1;
	}
	printAllocatedList();
	printFreeList();
  return status;	
}

int deleteHeap(){
	char name[20];
	int status=1;
	printf("enter the variable name: ");
	scanf("%s",name);
	allocList *x,*y;
	y = x = varList.al;
	while(x!=NULL && strcmp(x->varName,name)!=0){
		y = x;
		x = x->next;
	}
	if(x==NULL){
		status=0;
		printf("variable : %s not present\n",name);
	}else{
		if(y==x){
			varList.al = x->next;
		}else{
			y->next = x->next;
		}
		freeList *fp,*prev,*root;
		root = makeNodeFreeList(x->address,x->size);
	   	prev = fp = varList.fl;
		if(fp==NULL){
			printf("no memory\n");
			varList.fl = root;
		}else{
		
		while(fp!=NULL && fp->address < root->address)
		{
			prev = fp;
			fp = fp->next;
		}	
	//	printf("done\n");
		if(fp==prev){
			varList.fl = root;
			root->next = fp;
		}else{
		//	printf("at come\n");
			prev->next = root;
			root->next = fp;
		}
		
	 }
		free(x);
	}
	printAllocatedList();
	printFreeList();
	return status;
}

int main()
{
	int status;
	Initialize(&heap);
	printf("%d %d %d %d\n",varList.al,varList.fornextfit,varList.fl->size,varList.fl->next->size);
	status = bestFit();
	printf("after best fit %d",status);
    status = firstFit();
	printf("after first fit %d",status);
	status = bestFit();
	printf("after best fit %d",status);
	status = nextFit();
	printf("after next fit %d",status);
	status = deleteHeap();
	printf("after delete %d",status);
	return 0;
}
