#include <stdio.h>
#include <stdlib.h>
typedef struct{
	int i;
	struct List *next;
}List;
void deleteLast(List* head){
	List* ptr=head;
	List *ptr1=head;
	List *specific_element;
	while(1){
		if(ptr->next==NULL){
			printf("%d\n",ptr->i);
			specific_element=ptr;
			break;
		}
		ptr=ptr->next;
	}
	while(1){
		if((List*)ptr1->next==(List*)specific_element){
			ptr1->next=NULL;
			break;
		}
		ptr1=ptr1->next;
	}

}
List* deleteFirst(List* head){
	List* ptr=head->next;
	head=NULL;
	return ptr;
}
void addLast(List* head, int digit){
	List* ptr=head;
	List* new_element;
	while(1){
		if(ptr->next==NULL){
			new_element=(List*)malloc(sizeof(List));
			new_element->i=digit;
			new_element->next=NULL;
			ptr->next=new_element;
			break;
		}
		ptr=ptr->next;
	}
}
void deleteByValue(List* head, int digit){
	List* ptr=head;
	List* ptr1=head;
	List *specific_element;
	while(ptr!=NULL){
		if(ptr->i==digit){
			specific_element=ptr;
			break;
		}
		ptr=ptr->next;
	}
	while(ptr1!=NULL){
		if(ptr1->next==specific_element){
			ptr1->next=specific_element->next;
			free(specific_element);
			break;
		}
		ptr1=ptr1->next;
	}
}
void uniqueElements(List *head){
	List* ptr=head;
	List* specific_element;
	int counter=0;
	int buff[255]={0};
	while(ptr!=NULL){
		List* ptr1=head;
		buff[counter]=ptr->i;
		for(int i=0;i<counter;i++){
			if(buff[i]==ptr->i){
				specific_element=ptr;
				break;
			}
		}
		while(ptr1!=NULL){
			if((List*)ptr1->next==(List*)specific_element){
				ptr1->next=specific_element->next;
				free(specific_element);
				break;
			}
			ptr1=ptr1->next;
		}
		counter++;
		ptr=ptr->next;
    }
}
List* addFirst(List* current,int digit){
	List* head = (List*)malloc(sizeof(List));
	head->i=digit;
	head->next=current;
	return head;
}
void printElements(List* head){
	List* ptr=head;
	while(ptr!=NULL){
		printf("%d\n",ptr->i);
		ptr=ptr->next;
	}
}

int main(){
	List *head = NULL;
	head=addFirst(head,1);
	head=addFirst(head,2);
	head=addFirst(head,3);
	addLast(head,4);
	addLast(head,5);
	addLast(head,6);
	addLast(head,6);
	addLast(head,2);
	head=addFirst(head,3);
	addLast(head,4);
	addLast(head,10);
	uniqueElements(head);
	printElements(head);
	return 0;
}