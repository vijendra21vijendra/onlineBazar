#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>

// now declarations of structures

// this is for dataBase of products which are stored with site
char *GCArray[6][3]={
{"Android Mobiles","Iphones","Simple Mobiles"}
,{"chargers","Earphones",""},{"i3 lapis","i5 lapis","i7 lapis"},
{"racing car","helis",""},{"pub-G","Gt-5",""}
,{"oven","cattle","induction"}
};
typedef struct dbp{
	int cat1;// there are total 6 categories
	int cat2;// 2 for some and 3 for some
	char nameOfProduct[20];
	float cost;
	int available;
	int sold;
	struct dbp *next;
}dataBaseProduct;

// this is product which is stored in wish list and purchased list of a customer
typedef struct pt{
	int cat1;// there are total 6 categories
	int cat2;
	char nameOfProduct[20];
	float cost;
	int quantity;
	struct pt *next;
}product;

//this structure is for balance mode

typedef struct bt{
	float cod;
	float upi;
	float debitCard;
	int arrBalance[3];
}balanceType;

//this is structures for customer Data Base 

typedef struct cdb{
	int id;//id should be unique and should be implemented such %100
	char email[20];//email should be unique but as google make email unique so i have no worry about it.
	char nameOfCustomer[20];
	char phone[11];
	char address[20];
	product *wishList;
	product *purchasedList;
	balanceType balanceMode;
	int totalPurchase;// means add only 1 when u order something means if u order 10 at once then also it adds 1
	int favItems[6][3];
	struct cdb *next;
}customerDataBase;



//
dataBaseProduct ***GDBP;
customerDataBase **GCDB;
//
//this just initializes the field with null value of product data base
void createProductDataBase()
 {
   dataBaseProduct ***x;
   int i,j;
   x = (dataBaseProduct***)malloc(sizeof(dataBaseProduct**)*6);
   int arr[6]={3,2,3,2,2,3};//this is a temp array for cat2.
   for(i=0;i<6;i++)
   {
   	 x[i] = (dataBaseProduct**)malloc(sizeof(dataBaseProduct*)*arr[i]);
   	 //this is for cretaion of field of cat2
   }
   	for(i=0;i<6;i++)
	{
		for(j=0;j<arr[i];j++)
		{
			x[i][j] = NULL;
		}
	}
	GDBP = x;
 }
 
 // this just initializes the filed values with null for customer data bases
void createCustomerDataBase()
{
   	customerDataBase **cp;
	int i;
	cp = (customerDataBase**)malloc(sizeof(customerDataBase*)*100);
	for(i=0;i<100;i++)
	{
	  cp[i] = NULL;
	}
   GCDB = cp;
}

//

    void initializeProductDataBase()
 	{
		dataBaseProduct *p,*q,*r;
		int n=16;
		int cat1,cat2,available,sold;
		float cost;
		char name[20];
		FILE *fp; 
		fp = fopen("product.txt","r");
		while(n-- >0)
		{
		 fscanf(fp, "%d %d %s %f %d %d",&cat1,&cat2,name,&cost,&available,&sold);
		  p = (dataBaseProduct*)malloc(sizeof(dataBaseProduct));
		  p->available = available;
		  p->cat1 = cat1;
		  p->cat2 = cat2;
		  p->sold = sold;
		  p->cost = cost;
		  p->next = NULL;
		  strcpy(p->nameOfProduct,name);
		  q = GDBP[cat1][cat2];
		  if(q==NULL)
		  {
		  //	printf("first position: ");
		  	GDBP[cat1][cat2] = p;
		  }
		  else
		  {
		  	GDBP[cat1][cat2] = p;
		  	p->next = q;
		  //	printf("present first position: ");
		  }
		 // printf("%d %d %s %.2f %d %d\n",cat1,cat2,name,cost,available,sold);
		}
	fclose(fp);	
	}
	
	
void initializeCustomerDataBase()
	{
		int n,d,id,i,j;
		n=5;
		FILE *fp; 
		fp = fopen("customer.txt","r");
		customerDataBase *x,*y,*z;
		char name[20],mobile[11],address[20],email[20];
		float b1,b2;//for balance
		while(n-- >0)
		{
	       x = (customerDataBase*)malloc(sizeof(customerDataBase));
		  fscanf(fp,"%d %s %s %s %s %f %f",&id,email,name,mobile,address,&b1,&b2);
		  x->id = id;
		  x->purchasedList = NULL;
		  x->totalPurchase =0;
		  x->wishList = NULL;
		  x->next = NULL;
		  x->balanceMode.debitCard = b1;
		  x->balanceMode.upi = b2;//b2 upi and b1 debit card
		  strcpy(x->phone,mobile);
		  strcpy(x->nameOfCustomer,name);
		  strcpy(x->email,email);
		  strcpy(x->address,address);
		  for(i=0;i<6;i++)
		  {
		  	for(j=0;j<3;j++)
		  	{
		  	  x->favItems[i][j] = 0;
			}
		  }
		  for(i=0;i<3;i++){
		  x->balanceMode.arrBalance[i] = 0;
		}	
		d = id%100;
		y = GCDB[d];
		   if(y==NULL)
			{
				GCDB[d] = x;
				//printf("in null : ");
			}
		else
		{
			
			GCDB[d] = x;
			x->next = y;
			//printf("collide: ");
		}
	//	printf("%d %s %s %s %s %.2f %.2f\n",id,email,name,mobile,address,b1,b2);
	 }
	fclose(fp);	
	}


//now function starts



// this function is for checking that customers is already registered or not 
//if already registered then return id else return -1


int isUserRegistered()
{
	int id;
	char email[20];
	printf("enter id: ");
	scanf("%d",&id);
	printf("enter your email: ");
	scanf("%s",email);
	int d;
	d = id%100;
	customerDataBase *x;
	x = GCDB[d];
	while(x!=NULL && x->id!=id)
	{
		x = x->next;
	}
	if(x!=NULL)
	{
		if(strcmp(email,x->email)==0)
		{
			printf("yes user is registered\n");
			return id;
		}
	}
	printf("user is not registered\n");
	return -1;
}





/// registerUser function that registers anyhow to user and just returns id of the user


//it returns true if id found else false 
int isIdFound(int id)
{
	int d;
	d = id%100;
	customerDataBase *x;
	x = GCDB[d];
	while(x!=NULL && x->id!=id)
	{
		x = x->next;
	}
	if(x!=NULL)
	{
		return 1;
	}
	return 0;
}

// returns true if email found else false
int isEmailFound(char email[20])
{
    int i=0;
	customerDataBase *x;
	int flag=1;
	while(i<100 && flag)
	{
       	x = GCDB[i];
		while(x!=NULL && strcmp(x->email,email)!=0)
		{
			x = x->next;
		}
		if(x!=NULL)
		{
			flag=0;
		}
		i++;		
	}
	if(flag==0)
	{
		return 1;
	}
	return 0;
}


//it just creates a user account and returns pointer of customer but it doesn't register user
customerDataBase* createCustomer()
{
	customerDataBase *x;
	x = (customerDataBase*)malloc(sizeof(customerDataBase));
    char str[20];
	printf("enter name: ");
	scanf("%s",str);
	strcpy(x->nameOfCustomer,str);
	printf("enter mobile no: ");
	scanf("%s",str);
	strcpy(x->phone,str);
	printf("enter address: ");
	scanf("%s",str);
	strcpy(x->address,str);
	x->wishList = x->purchasedList = NULL;
	x->next = NULL;
	x->totalPurchase = 0;
	float fp;
	printf("enter money in account connected with debit card: ");
	scanf("%f",&fp);
	x->balanceMode.debitCard = fp;
	printf("enter money in account connected to upi but not earlier debit card:");
	scanf("%f",&fp);
	x->balanceMode.upi = fp;
	x->balanceMode.cod = 0;
	int i,j;
	for(i=0;i<3;i++)
	{
		x->balanceMode.arrBalance[i] = 0;
	}
	for(i=0;i<6;i++)
	{
		for(j=0;j<3;j++)
		{
			x->favItems[i][j] = 0;
		}
	}
	return x;
}



// it registers user and just return id of user 
int registerUser()
{
	int flag=1;
	int id;
	char email[20];
	while(flag==1)
	{
		printf("enter id: ");
		scanf("%d",&id);
		printf("enter your email: ");
		scanf("%s",email);
		int d;
		d = id%100;
		
		if(!isIdFound(id))
		{
			if(!isEmailFound(email))
			{
				// create a customer and just register it
				customerDataBase *x;
				// it takes input of all values except id and email
				x = createCustomer();
				x->id = id;
				strcpy(x->email,email);
				// and add it into the data base
				d = id%100;
				customerDataBase *y;
				// implementation is insert at start
				y = GCDB[d];
				if(y==NULL)
				{
					GCDB[d] = x;
				}
				else
				{
					GCDB[d] = x;
					x->next = y;
				}
				flag=0;
			}
			else
			{
				printf("your id is unique but email is present please try again\n");
			}
		}
		else
		{
			printf("entered id is present alredy please try again\n");
		}
    }
    printf("registration successfull\n");
return id;
}

int callCat1Show()
{
	int cat1;
	printf("\t\twe have these 6 categories of product enter: \n");
	printf("\t\t0.for Mobile Phones\n\t\t1.for Mobile Accessories\n\t\t2.for Laptops\n");
	printf("\t\t3.for Electronics Gadgets\n\t\t4. for Games purchase\n\t\t5. Kitchen Appliances: ");
	scanf("%d",&cat1);
	return cat1;
}

int callCat2Show(int cat1)
{
	printf("\t\t\tNow in your choice we have these much categories enter:\n");
	int cat2;
	switch(cat1)
	{
		case 0:
			{
				printf("\t\t0. for Android Mobiles\n\t\t1. for Iphones\n\t\t2. for normalMobiles: ");
			}
		break;
		case 1:
			{
				printf("\t\t0. chargers\n\t\t1. for Earphones: ");
			}
        break;
		case 2:
			{
				printf("\t\t0. i3 Generation Laptops\n\t\t1. for i5 Generation Laptops\n\t\t2. for i7 Generation laptops : ");
			}
		break;
		case 3:
			{
				printf("\t\t0. for Racing Cars\n\t\t1. for Helis(Helicopters): ");
			}
        break;
		case 4:
			{
				printf("\t\t0. for PUB-G\n\t\t1. for GT-5: ");
			}
		break;
		case 5:
			{
				printf("\t\t0. for Ovens\n\t\t1. for cattles\n\t\t3. for Inductions: ");
			}
        break;
	}
	scanf("%d",&cat2);
	return cat2;
}


//it just prints the wishlist product information and takes input of *product which is in customer->wishlist 
void printW(product *p)
{
	printf("%d %s are here \n",p->quantity,p->nameOfProduct);
}
// it prints wish list for a user if it is present else it says no
void printPurchasedList(int id)
{
	customerDataBase *c = GCDB[id%100];
	
	if(c==NULL)
	{
		printf("customer not present\n");
	}
	 else
	 {
		while(c!=NULL && c->id!=id)
		{
			c = c->next;
		}
		if(c==NULL)
		{
			printf("customer not present\n");
		}
		else{
			product *p;
			p = c->purchasedList;
			if(p==NULL)
			{
				printf("Purchased list is empty\n");
			}
			while(p!=NULL)
			{
				printW(p);
				p = p->next;
			}
		}	
     }
	printf("\n");
}

void printWishList(int id)
{
	customerDataBase *c = GCDB[id%100];
	
	if(c==NULL)
	{
		printf("customer not present\n");
	}
	 else
	 {
		while(c!=NULL && c->id!=id)
		{
			c = c->next;
		}
		if(c==NULL)
		{
			printf("customer not present\n");
		}
		else{
			product *p;
			p = c->wishList;
			if(p==NULL)
			{
				printf("Wish list is empty\n");
			}
			while(p!=NULL)
			{
				printW(p);
				p = p->next;
			}
		}	
     }
	printf("\n");
}


//it just prints information of a structure of databaseProduct pointer
void printP(dataBaseProduct *p)
{
	printf("%d %s are available with %.2f rupees per item\n",p->available,p->nameOfProduct,p->cost);
}

// it prints product list that are present if cat1 and cat2 are present 
void printProductList(int cat1,int cat2)
{
	int arr[] = {3,2,3,2,2,3};
	if(cat1>=0 && cat1<=5 && (cat2>=0 && cat2<arr[cat1]))
	{	
		dataBaseProduct *x;
		x = GDBP[cat1][cat2];
		if(x==NULL)
		{
			printf("it's empty list \n");
		}
		while(x!=NULL)
		{
			printP(x);
			x = x->next;
		}
    }
    else
    {
    	printf("categories are wrong\n");
	}
	printf("\n");
}

// it just prints customer information
void printC(customerDataBase *x)
{
	printf("id: %d\n",x->id);
	printf("Name : %s\n",x->nameOfCustomer);
	printf("email : %s\n",x->email);
	printf("Mobile : %s\n",x->phone);
	printf("address: %s\n",x->address);
	printf("upi balance: %f \n and debit card balance: %f\n",x->balanceMode.upi,x->balanceMode.debitCard);
}

//it prints customer information if id is present
void printCustomerInformation(int id)
{
	customerDataBase *c;
	c = GCDB[id%100];
	if(c==NULL)
	{
		printf("customer not present in dataBase\n");
	}
	else
	 {
	 	 while(c!=NULL && c->id!=id)
		{
			c = c->next;
		}
		if(c!=NULL)
		{
			printC(c);
		}
		else
		{
		  printf("customer not present in dataBase\n");	
		}
     } 
	printf("\n");
}

//it prints the items category which are frequently purchased for given id
void printFreqPurForUser(int id)
{
	customerDataBase *x;
	x = GCDB[id%100];
	if(x==NULL)
	{
		printf("customer not present\n");
	}
	else
	{
		while(x!=NULL&&x->id!=id)
		{
			x = x->next;
		}
		if(x!=NULL)
		{
			int max = x->favItems[0][0];
			int i,j,p,q;
			for(i=0;i<6;i++)
			{
				for(j=0;j<3;j++)
				{
					if(x->favItems[i][j]>=max)
					{
						p=i;
						q=j;
						max = x->favItems[i][j];
					}
				}
			}
			// now i have to print this from an array
			if(max>0){
			printf("%s cat1: %d and cat2: %d is purchased max times\n",GCArray[p][q],p,q);				
			}else{
				printf("nothing puchased till now\n");
			}
		}
		else
		{
			printf("customer not present\n");
		}
	}
	printf("\n");
}

void printFreqPurForAllUser()
{
	customerDataBase *x;
	int id,k,l,max;
	int i,j,p,q;
	k=0;
	max=0;
	while(k<100)
	{
		x = GCDB[k];
		while(x!=NULL)
		{
		   for(i=0;i<6;i++)
			{
				for(j=0;j<3;j++)
				{
					if(x->favItems[i][j]>=max)
					{
						p=i;
						q=j;
						max = x->favItems[i][j];
						id = x->id;
					}
				}
			}
			x = x->next;		
		}
		k+=1;
	}
	// now i have to print this from an array
	if(max>0){
	printf("%s is purchased max times by id: %d\n",GCArray[p][q],id);	
	}else{
		printf("nothing puchased till now by any customer\n");
	}
}


// here totalPurchase is an variable of customer database which tells that how many times customer purchased things
void printCustomer6f()
{
	customerDataBase *x;
	int i,j,k,p;
	int arr[100][2];
	// where first row represents maxpurchase and second represents id and i have to sort basis on val in decreasing order
	k=0;
	while(k<100)
	{
		x = GCDB[k];
		while(x!=NULL)
		{
			arr[i][0] = x->totalPurchase;
			arr[i][1] = x->id;
			i++;
			x = x->next;
		}
		k+=1;
	}
	p=i;
	int sorted=0;
	int temp1,temp2;
	for(i=0;i<p-1 && sorted==0;i++)
	{
		sorted=1;
		for(j=0;j<p-1;j++)
		{
		  if(arr[j][0] < arr[j+1][0])
		  {
		  	temp1 = arr[j][0];
		  	temp2 = arr[j][1];
		  	arr[j][0] = arr[j+1][0];
		  	arr[j][1] = arr[j+1][1];
		  	arr[j+1][0] = temp1;
		  	arr[j+1][1] = temp2;
		  	sorted=0;
		  }	
		}
	}
	if(arr[0][0]!=0)
	{
		for(i=0;i<p && arr[i][0]>0;i++)
		{
			printf("%d times\n",arr[i][0]);
			printCustomerInformation(arr[i][1]);
			printf("\n");
		}
	}else{
		printf("nothing purchased till now\n");
	}
	printf("\n");
}



//function for odering 
void order(int id,int cat1,int cat2)
{
	char proName[20];
	int quantity,po,d;
	customerDataBase *c;
	dataBaseProduct *db;
	product *p;
	int flag=1;
	while(flag){
				printf("enter the product name: ");
				scanf("%s",proName);
				printf("enter quantity: ");
				scanf("%d",&quantity);
				printf("enter payment option ");
				printf("enter\n\t\t0. for cod\n\t\t1. for debitCard\n\t\t2. for upi Enabled: ");
				scanf("%d",&po);
				db = GDBP[cat1][cat2];
				d = id%100;
				c = GCDB[d];
				while(c!=NULL&&c->id!=id)
				{
					c = c->next;
				}
				if(c==NULL)
				{
					printf("customer not present\n");
					return;
				}
				else
				{
					while(db!=NULL&&strcmp(db->nameOfProduct,proName)!=0)
					{
						db = db->next;
					}
					if(db==NULL)
					{
						printf("product not found\n");
					}
					// now db contains product in product data bases
					// now i have a special problem of remember things
					else
					{
					  if(db->available >= quantity)
					   {
						// order done successfully then i have to also copy it in purchased list of user
						if(po==0)
						{
							printf("cod done successfully\n");
							db->available =db->available - quantity;
							db->sold += quantity;
							c->balanceMode.arrBalance[0]+=1;
							flag=0;
						}
						else if(po==1)
						{
							if(quantity * db->cost <= c->balanceMode.debitCard)
							{
								db->available =db->available - quantity;
								c->balanceMode.debitCard -= quantity*db->cost;
								db->sold += quantity;
								c->balanceMode.arrBalance[1]+=1;
								printf("debit card  done successfully\n");
								flag=0;
							}
							else
							{
								printf("Don't have enough money\n");
							}
						}
						else if(po==2)
						{
							if(quantity * db->cost <= c->balanceMode.upi)
							{
								db->available =db->available - quantity;
								c->balanceMode.upi -= quantity*db->cost;
								db->sold += quantity;
								c->balanceMode.arrBalance[2]+=1;
								printf("upi  done successfully\n");
								flag=0;
							}
							else
							{
								printf("Don't have enough money\n");
							}
						}
						else
						{
							printf("wrong payment option\n");
						}
					
					// add into purchased list
					}
						else
						{
							printf(" sorry for inconvenince we don't have enough items\n");
						}	
					}		
				}
					//now c contains the user entries
			}
	// we have to do something that it should come here after ordering something
	
	c->favItems[cat1][cat2]+=1;
	// that if u entered then you have to order
	// now i have to just immplement it in the purchased
	product *tp,*tp1;
	tp1 = tp = c->purchasedList;
	if(tp==NULL)
	{
	   tp = (product*)malloc(sizeof(product));
	   tp->cat1 = cat1;
	   tp->cat2 = cat2;
	   tp->cost = db->cost;
	   tp->quantity = quantity;
	   strcpy(tp->nameOfProduct,proName);
	   tp->next = NULL;
	   c->purchasedList = tp;
	}
	else
	{
		while(tp->next!=NULL && strcmp(tp->nameOfProduct,proName)!=0)
		{
			tp = tp->next;
		}
		if(strcmp(tp->nameOfProduct,proName)==0)
		{
			tp->quantity+=quantity;
		}
		else
		{
		   tp1 = tp;
		   tp = (product*)malloc(sizeof(product));
		   tp->cat1 = cat1;
		   tp->cat2 = cat2;
		   tp->cost = db->cost;
		   tp->quantity = quantity;
		   strcpy(tp->nameOfProduct,proName);
		   tp->next = NULL;
		   tp1->next = tp;
		}
	}
	printf("\n");
}



void addWishList(int id,int cat1,int cat2)
{
	char proName[20];
	int quantity,d;
	customerDataBase *c;
	dataBaseProduct *db;
	product *p;
	int flag=1;
	while(flag){
			printf("enter the product name: ");
			scanf("%s",proName);
			printf("enter quantity: ");
			scanf("%d",&quantity);
			db = GDBP[cat1][cat2];
			d = id%100;
			c = GCDB[d];
			while(c!=NULL && c->id!=id)
			{
				c = c->next;
			}
			if(c==NULL)
			{
				printf("cusomer not present\n");
				return;
			}
			else
			{
				//now c contains the user entries
				while(db!=NULL &&strcmp(db->nameOfProduct,proName)!=0)
				{
					db = db->next;
				}
				if(db==NULL)
				{
					printf("product not found\n");
				}
				else
				{
					
					if(db->available >= quantity)
					{
						// it will just add items into wish list nothing more than that
						// order done successfully then i have to also copy it in purchased list of user
							printf("added into wish list  successfully\n");
							flag=0;
					}
					else
					{
						printf("we don't have so enough products\n");
					}
					
				}
				// now db contains product in product data bases
				// now i have a special problem of remember things		
			}
}
	// we have to do something that it should come here after add in wish list 
	
	// that if u entered then you have to add something into wish list
	// now i have to just immplement it in the wish list 
	
	product *tp,*tp1;
	tp1 = tp = c->wishList;
	if(tp==NULL)
	{
	   tp = (product*)malloc(sizeof(product));
	   tp->cat1 = cat1;
	   tp->cat2 = cat2;
	   tp->cost = db->cost;
	   tp->quantity = quantity;
	   strcpy(tp->nameOfProduct,proName);
	   tp->next = NULL;
	   c->wishList = tp;
	}
	else
	{
		while(tp->next!=NULL && strcmp(tp->nameOfProduct,proName)!=0)
		{
			tp = tp->next;
		}
		if(strcmp(tp->nameOfProduct,proName)==0)
		{
			tp->quantity+=quantity;
		}
		else
		{
		   tp1 = tp;
		   tp = (product*)malloc(sizeof(product));
		   tp->cat1 = cat1;
		   tp->cat2 = cat2;
		   tp->cost = db->cost;
		   tp->quantity = quantity;
		   strcpy(tp->nameOfProduct,proName);
		   tp->next = NULL;
		   tp1->next = tp;
		}
	}
	printf("\n");
}


// return product means money will be added in upi directly doesn't matter what was the way of paying

void returnProduct(int id)
{
	char proName[20];
	int cat1,cat2,quantity,d;
	customerDataBase *c;
	dataBaseProduct *db;
	product *p;
			printf("enter the product name: ");
			scanf("%s",proName);
			printf("enter quantity: ");
			scanf("%d",&quantity);
			d = id%100;
			c = GCDB[d];
			while(c!=NULL &&c->id!=id)
			{
				c = c->next;
			}
			if(c==NULL)
			{
				printf("customer is not present\n");
				return;
			}	
	product *tp,*tp1;
	tp1 = tp = c->purchasedList;
	if(tp==NULL)
	{
	   printf("item not present\n");
	}
	else
	{
		while(tp->next!=NULL && strcmp(tp->nameOfProduct,proName)!=0)
		{
			tp1 =tp;
			tp = tp->next;
		}
		if(strcmp(tp->nameOfProduct,proName)==0)
		{
			// added balance and deleted node if no quantity else only reduced quantity
			
			if(quantity <= tp->quantity)
			{
				c->balanceMode.upi += quantity*tp->cost;
				cat1 = tp->cat1;
				cat2 = tp->cat2;
				if(tp->quantity- quantity>0)
				{
					tp->quantity -=quantity;
				}
				else
				{
					tp1->next = tp->next;
					free(tp);
				}
				db = GDBP[cat1][cat2];
				while(strcmp(db->nameOfProduct,proName)!=0)
				{
					db = db->next;
				}
				db->available+=quantity;
				db->sold-=quantity;	
			}
			else
			{
				printf("you have not purchased this much items\n");
			}
		}
		else
		{
		    printf("item not present\n");
		}
	}
	printf("\n");
}


int main(int argc, char *argv[]) {
	createProductDataBase();
	createCustomerDataBase();
	initializeProductDataBase();
	initializeCustomerDataBase();
	printf("\t\t\t******This is Online Bazar created by BT17cse081 and BT17cse089 *****\n");
	int flag1=1,ord,ad,ret,oar,flag2,flag3;
	int id=-1;
	int cat1,cat2;
	while(flag1)
	{
		int user;
		printf("\tenter\n\t1. for login \n\t2. for Sign Up: ");
		scanf("%d",&user);
		if(user==1)
		{
		   id = isUserRegistered();
		   if(id==-1)
		   {
		   	printf("you are not a registered user\n");
		   	printf("please sign up first here\n");
		   	id = registerUser();
		   }
		   // now users having id of user
		}
		else
		{
			printf("register here\n");
			id = registerUser();
		}
		// now user is registered with id is also present with me
		// here i am implementing order return and addWishList functions
	flag2=1;
	while(flag2)
	{
		   printf("\t\tNow you can perform these things\n");
		   printf("enter :\n\t\t1.for order\n\t\t2. for addWishList\n\t\t3. for return any Product: ");
		   scanf("%d",&oar);
		   if(oar==1)
		   {
		   	   printf("Now U can Purchase\n");
			   cat1 = callCat1Show();
			   cat2 = callCat2Show(cat1);
			   printProductList(cat1,cat2);
			   // now i can go towards order or not
			   ord = 0;
			   printf("enter:\n\t\t1. for order\n\t\tany other key  else: ");
			   scanf("%d",&ord);
			   if(ord==1)
			   {
			   	order(id,cat1,cat2);
			   }
		   }
		   else if(oar==2)
		   {
		   	   printf("Now you can add to wishList\n");
			   cat1 = callCat1Show();
			   cat2 = callCat2Show(cat1);
			   printProductList(cat1,cat2);
			   // now i can go towards order or not
			   ad = 0;
			   printf("enter:\n\t\t1. for addWishList\n\t\tany other key else: ");
			   scanf("%d",&ad);
			   if(ad==1)
			   {
			   	addWishList(id,cat1,cat2);
			   }
		   }
		   else
		   {
		   	 printf("Now you can return product from these purchased products: \n");
		   	  printPurchasedList(id);
		   	  ret=0;
		   	  printf("\t\tenter 1. for return any product\n\t\tany other key else: ");
		   	  scanf("%d",&ret);
		   	  if(ret==1)
		   	  {
		   	  	returnProduct(id);
			  }
		   }
		   printf("\t\tenter 1 if you want to continue with addWishList , order or returnProduct\n\telse enter 0: ");
		   scanf("%d",&flag2);		
	}
	  // else don't order
	printf("\t\tenter\n\t\t 1. for logout and to login in other user Account\n\t\t0. for  enter into another interface of type admin: ");
	scanf("%d",&flag1);	
  }
  printf("\t\t\tadmin Mode On now You can access these things enter: \n");
  flag1=1;
  while(flag1)
  {
  	int fuc;
  	printf("\t\t1. for PrintWishList\n\t\t2. for printProductList\n\t\t3. for customer Information\n");
  	printf("\t\t4. for Items Purchased frequently by a customer\n");
  	printf("\t\t5. for itmes purchased frequently by all customer\n");
  	printf("\t\t6. for Customer list of decreasing list in freq. of purchase: ");
  	scanf("%d",&fuc);
  	switch(fuc)
  	{
  	 case 1:
  	 	{
  	 	 printf("enter id: ");
  	 	 scanf("%d",&id);
  	 	 printWishList(id);
  	 	 break;
		}
  	 case 2:
  	 	{
  	 	 printf("enter cat1: ");
  	 	 scanf("%d",&cat1);
  	 	 printf("enter cat2: ");
  	 	 scanf("%d",&cat2);
  	 	 printProductList(cat1,cat2);
  	 	 break;
		}
  	 case 3:
  	 	{
  	 	 printf("enter id: ");
  	 	 scanf("%d",&id);
         printCustomerInformation(id);
  	 	 break;
		}
  	 case 4:
  	 	{
  	 	 printf("enter id: ");
  	 	 scanf("%d",&id);
  	 	 printFreqPurForUser(id);
  	 	 break;
		}
  	 case 5:
  	 	{
          printFreqPurForAllUser();
  	 	 break;
		}
  	 case 6:
  	 	{
		  printCustomer6f();
  	 	 break;
		}
		default: printf("wrong input\n"); break;	
	}
  	printf("\t\tenter: \n\t\t1 for be in this admin mode \n\t\t0. for close: ");
  	scanf("%d",&flag1);
  }
  
	printf("successful");
	return 0;
}
