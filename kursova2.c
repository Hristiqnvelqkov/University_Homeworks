#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	char product[15];
	float price;
	struct Products* next_product;
}Products;

typedef struct {
	char consumation[10];
	struct Consumation* next;
}Consumation;

typedef struct{
	char name[15];
	struct Persons* next_person;
}Persons;

typedef struct{
	int table_number;
	Persons* person;
	Consumation* consume_head;
}TableInfo;

typedef struct{
	TableInfo table;
	struct Restaurant* next;
}Restaurant;
float calculateBill(Products* head,Consumation *cons_head){
	Products* product_head=head;
	float sum=0;
	Consumation* ptr_cons=cons_head;
	while(ptr_cons!=NULL){
		product_head=head;
		while(product_head!=NULL){
			if(strcmp(ptr_cons->consumation,product_head->product)==0){
				printf("%f\n",product_head->price);
				sum+=product_head->price;
			}	
			product_head=product_head->next_product;
		}
		ptr_cons=ptr_cons->next;
	}
	return sum;
}

void printElements(Consumation* head){
	Consumation* ptr=head;
	while(ptr!=NULL){
		printf("%s",ptr->consumation);
		ptr=ptr->next;
	}
}
void printHumans(Persons* head){
	Persons* ptr=head;
	while(ptr!=NULL){
		printf("%s",ptr->name);
		ptr=ptr->next_person;
	}
}
Products* addProduct(Products* current,char product[15],float price){
	Products* head=(Products*)malloc(sizeof(Products));
	head->next_product=current;
	for(int i=0;i<strlen(product);i++){
		head->product[i]=product[i];
	}
	head->price=price;
	return head;
}
 
void addPerson(Restaurant *table,char person_name[15],Persons* current){
	table->table.person=(Persons*)malloc(sizeof(Persons));
	for(int i=0;i<strlen(person_name);i++){
		table->table.person->name[i]=person_name[i];
	}
	table->table.person->next_person=current;
}

Restaurant* addFirst(Restaurant* current,int table_number){
	Restaurant* head=(Restaurant*)malloc(sizeof(Restaurant));
	head->table.table_number=table_number;
	head->next = (Restaurant*)current;	
	return head;
}
void closeRestaurant(Restaurant * head){
	Restaurant* ptr=head;
	while(ptr!=NULL){
		ptr=ptr->next;
		free(ptr);
	}
}
Restaurant* findTable(int table_number,Restaurant* head){
	Restaurant* ptr=head;
	Restaurant* table=NULL;
	if(head==NULL){
		printf("There is no tables\n");
	}else{
		for(int i=0;i<15;i++){
			if(ptr->table.table_number==table_number){
				table=ptr;
				break;
			}else{
				table=ptr->next;
			}
			i++;
		}
	}
	return table;
}
void addConsumation(Restaurant *table,char consumation[15],Consumation* current_consumation){
	table->table.consume_head=(Consumation*)malloc(sizeof(Consumation));
	for(int i=0;i<strlen(consumation);i++){
		table->table.consume_head->consumation[i]=consumation[i];
	}
	table->table.consume_head->next=current_consumation;
}
TableInfo makeTable(Persons* head,int number){
	TableInfo table;
	table.person=head;
	table.table_number=number;

	return table;
}
int main(){
	Restaurant* head=NULL;
	Products* products_head=NULL;
//	head->table.consume_next=NULL;
	int option;
	int tables_number=15;
	int person_number;
	char all_products[10][10]={{"kola"},{"rakiq"},{"uiski"},{"spirt"},{"lukanka"},{"kartofi"},{"mastika"},{"menta"},{"bira"},{"uzo"}};
	float prices[10]={1,1.2,2.5,0.9,2.7,2,1.5,1.2,1.6,2};
	for(int i=0;i<10;i++){
		char current_product[15];
		for(int j=0;j<10;j++){	
			current_product[j]=all_products[i][j];
		}
		products_head=addProduct(products_head,current_product,prices[i]);
	}
	while(1){
		printf("For make table click: 1\nFor fill new Consumption click: 2\nFor fill new products click: 3\nFor calculate bill click: 4\nFor add new client click: 5\nFor close restuarant click 6\n");
		scanf("%d",&option);
		if(option==1){
			head=addFirst(head,tables_number);
			tables_number--;
		}
		if(option==2){
			printf("Select table for new cosumation: ");
			int table_number;
			scanf("%d",&table_number);
			Restaurant* selected_table=findTable(table_number,head);
			printf("%d\n",selected_table->table.table_number);
			if(selected_table==NULL){
				printf("this table is empty\n");
				continue;
			}
			if(selected_table->table.consume_head->consumation==NULL){
				selected_table->table.consume_head=NULL;
			}
			printf("Enter consumation\n");
			char cons[15];
			scanf("%s",cons);
			addConsumation(selected_table,cons,selected_table->table.consume_head);
			printElements(selected_table->table.consume_head);
		}
		if(option==3){
			char name_of_product[15];
			int price_of_product=0;
			printf("Enter name of product: ");
			scanf("%s",name_of_product);
			printf("Enter price of product ");
			scanf("%d",&price_of_product);
			products_head=addProduct(products_head,name_of_product,price_of_product);
		}
		if(option==4){
			int table_number;
			printf("Enter table number: ");
			scanf("%d",&table_number);
			Restaurant* table_bill=findTable(table_number,head);
			float sum=calculateBill(products_head, table_bill->table.consume_head);
			printf("%f\n",sum);
		}
		if(option==5){
			int table_number;
			char name_of_person[15];
			printf("Enter table ");
			scanf("%d",&table_number);
			Restaurant* selected_table=findTable(table_number,head);
			if(selected_table==NULL){
				printf("this table was't being created\n");
				continue;
			}
			if(selected_table->table.person->name==NULL){
				selected_table->table.person=NULL;
			}
			printf("Enter Person name\n");
			scanf("%s",name_of_person);
			addPerson(selected_table,name_of_person,selected_table->table.person);
			printHumans(selected_table->table.person);

		}
		if(option==6){
			closeRestaurant(head);
			break;
		}
	}
	return 0;
}
