#include <stdio.h>
#include <stdlib.h>
 
typedef struct digit{		
	char symbol;
	int number;
	struct digit* next;
	struct digit* right;
	struct digit* left;
}digit;


digit* push(digit* head,char s);	
char pop(digit** head);
void empty(digit** head);
digit* reverse(digit* head);
digit* new(char symbol,digit* left,digit* right);
void print(digit* head);
digit* parse(digit* head);
void prefix(digit* head);

int main(){
	char choice1[50];
	int choice2;
	char t;
	digit* head1=NULL;	
	digit* head2=NULL;
	int count=0;	

	START:
	do{
		do{
			printf("1.Import numeric expression\n");
			printf("2.Display postorder format\n");
			printf("3.Display preoder format\n");
			printf("4.Exit\n");
			gets(choice1);
			choice2=atoi(choice1);		//metatrepei th sumboloseira pou eishgage o xrhsths se akeraio arithmo
			if (choice2!=1 && choice2!=2 && choice2!=3 && choice2!=4)	//ki elegxei gia thn egkurothta ths
			printf("Type a valid input!\n");
		}while(choice2!=1 && choice2!=2 && choice2!=3 && choice2!=4);
	
		switch(choice2){
			case 1:
				empty(&head1);		//diagrafei prohgoumenh sumboloseira pou eixame apothhkeusei
				printf("Insert numeric expression\n");
				if ((t=getchar())!='(') {		//an den arxizei me parenthesh h sumboloseira einai akurh
					printf("Invalid expression!Put all the brackets!\n");
					while(getchar()!='\n');			//kai katharizoume thn eisodo dedomenon apo authn
					continue;
				}
				while (t!='\n'){
					if(t=='('){count++;}	//o count auksanei me kathe anoigma parentheshs
					if (isdigit(t)){		
						head1=push(head1,t);	//oi telesteoi apothhkeuontai sth stoiba me deikth head1
					}
					if ((t=='+') || (t=='-') || (t=='*') || (t=='/'))
						head2=push(head2,t);	//eno oi telestes sth stoiba me deikth head2
					if (t==')'){
						if (head2==NULL){
							printf("Invalid expression!More brackets than necessary!!!\n");
							empty(&head1);		//an me to kleisimo kapoias parentheshs den uparxei sth 
							empty(&head2);		//deuterh stoiba telesths shmainei perissoteres parentheseis
							while(getchar()!='\n');
							goto START;	//kai to programma epistrefei sto arxiko menou (line 34)
						}
						else {
							head1=push(head1,pop(&head2));//me to kleisimo parenthesis prostithetai sthn proth 
							count--;			   //stoiba telesths pou eksagetai apo th deuterh
							}
					}t=getchar();
				}	
				if (count){	//mono an einai mhden o count exoume kleisei toses parentheseis oses exoume anoiksei
					printf("Invalid expression!More/less brackets!!!\n");
					empty(&head1);
					empty(&head2);
				}
					
			break; 	
			case 2:
				if(head1!=NULL)
					print(head1);	//ektuponei thn postfix parastash
				else{
					printf("There is no numeric expression to display!!!First insert one!");
				}
				printf("\n");
			break;
			case 3:
				if(head1!=NULL){
					head2=parse(head1);		//dhmiourgei to dentro 
					prefix(head2);			//kai to ektuponei prothematika
				}else{
					printf("There is no numeric expression to display!!!First insert one!");
					}
				printf("\n");
			break;
		}		
	
	}while(choice2!=4);	//mexri o xrhsths na epileksei eksodo
return 0;
}

		
char pop(digit** head){	 		//pairnei to sumbolo enos kombou kai diagrafei ton kombo apo th stoiba
	char result=(*head)->symbol;	
	digit* temp=(*head);
			*head=temp->next;
			free(temp);
			return result;
		
}

digit* push(digit* head,char s){		//dhmiourgei kombo me sumbolo s kai ton prosthetei sth stoiba
	digit* temp=(digit*)malloc(sizeof(digit));
	temp->symbol=s;
	temp->next=head;		
	return temp;
}

void empty(digit** head){		//adeiazei th stoiba
	while(*head!=NULL){
		pop(head);
	}
}

digit* reverse(digit* head){		//antistrefei th stoiba
	digit* ptr=head;
	digit* ptr1;
	digit* ptr2=NULL;
	while(ptr!=NULL){
		ptr1=ptr->next;
		ptr->next=ptr2;
		ptr2=ptr;
		ptr=ptr1;
	}	
	return ptr2;
}

void print(digit* head){		
	head=reverse(head);	//prota antistrefei th stoiba gia na thn ektuposei apo thn arxh ths postfix sumboloseiras kai oxi
	while(head!=NULL){			//apo to telos opou deixnei h head
		printf("%c ",head->symbol);
		head=head->next;
	}
	reverse(head);			//sto telos epanaferei th stoiba sthn arxikh ths katastash gia na mporesei na dhmiourghthei to dentro
}						//sto case 3

digit* new(char symbol,digit* left,digit* right){	//dhmiourgei kombo dentrou
	digit* x=(digit*)malloc(sizeof(digit));
	x->symbol=symbol;
	x->left=NULL;
	x->right=NULL;
	return x;
}

digit* parse(digit* head){			//dhmiourgei to dentro
	char ch=pop(&head);			//eksagei apo th stoiba ton proto xarakthra kai 
	digit* x=new(ch,NULL,NULL);		//dhmiourgei kombo dentrou 
		if((ch=='+')||(ch=='-')||(ch=='*')||(ch=='/')){		//ean einai telesths 
			x->right=parse(head);			//kalei pali thn parse opote eksagontai kai oi epomenoi xarakthres ths stoibas
			x->left=parse(head);
		}
		return x;
}

void prefix(digit* head){		//ektuponeii to dentro
	if(head!=NULL){				
		printf("%c ",head->symbol);	//prota ektuponei to sumbolo tou kombou 
		prefix(head->left);		//ki ustera phgainei na ektuposei kai ta paidia tou kombou
		prefix(head->right);
	}
	return;
}
