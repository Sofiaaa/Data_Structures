# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <assert.h>

typedef struct treeNode{
	double item;
	struct treeNode *left;
	struct treeNode *right;
}TreeNode;
void insertHeap(double key,double *A);
void swapHeap(double *a,double *b);
double deleteMaxHeap(double *A);
void destroyHeap(double * A);
int isEmptyHeap(double *A);
TreeNode* insertBst(TreeNode *root, double x); 
double deleteMaxBst(TreeNode **root);
//TreeNode  *searchBst(TreeNode *v,double x);
int searchBst(TreeNode **root,TreeNode **parNode,double x);
int rotateRight(TreeNode *parNode,TreeNode **root,double x);
int rotateLeft(TreeNode *parNode,TreeNode **root,double x);
void destroyBst(TreeNode *t);

int N;
int n=0;
static int  counter=0;

int main (void){
	srand((int)time(NULL));
	int i;
	double *A;
	double key;
	double maxKey;
	TreeNode *root=NULL;	//dhmiourgia kenou duadikou dentrou anazhthshs
	TreeNode *node=NULL;
	TreeNode *parNode=NULL;
	
	printf("Give number of elements\n");
	scanf("%d",&N);							
	A=(double*)malloc(N*sizeof(double));  //desmeuoume ton pinaka gia th dhmiourgia tou swrou
	printf("\n");
	for(i=0;i<N;i++){
		key=((double)rand()/((double)RAND_MAX+1))*100;		//epilegei N tuxaious pragmatikous arithmous
		insertHeap(key,A);									//tous eisagei sto swro
		root=insertBst(root,key);				//kai sto duadiko dentro anazhthshs
		printf("%f\n",key);
	}
	
	printf("\n");
	
	for (i=0;i<N/2;i++){				//oses fores einai ta misa stoixeia tou pinaka kai tou swrou
		maxKey=deleteMaxHeap(A);			//diagrafei to megisto stoixeio tou swrou
		printf("MaxKey in Heap is %f            ",maxKey);
		if(root!=NULL)	{					
			maxKey=deleteMaxBst(&root);			//kai to megisto stoixeio tou dentrou
			printf("MaxKey in Binary Search Tree is %f\n",maxKey);
		}
	}
	printf("\n");
	int x=((double)rand()/((double)RAND_MAX+1))*n;	//epilegei tuxaia anamesa sta enapomeinanta stoixeia tou swrou kapoio apo auta
	printf("%d\n",x);
	key=A[x];
	printf("Look into the Binary Search Tree for element %f\n",key);
	if(searchBst(&root,&parNode,key)==1){				//to anazhta sto dentro kai elegxei an vrethhke
		printf("We found the element after %d comparisons\n",counter);	
		int a=rotateRight(parNode,&root,key);			//epixeirei deksia peristrofh
		if (a==1)						//an einai epituxhs 
			printf("Right rotation of element %f succeed!!!\n",key);	//to ektupwnei
		else {								
			a=rotateLeft(parNode,&root,key);		//alliws epixeirei aristerh peristrofh
			if(a==1)								//an einai epituxhs to ektupwnei
				printf("Left rotation of element %f succeed!!!\n",key);
		}
	}
	else 					
		printf("Error!!The element is not found!!");
	printf("\n");
	
	destroyHeap(A);
	A=NULL;
	destroyBst(root);
	root=NULL;

	return 0;
}

void insertHeap(double key,double *A){ //eisagwgh sto swro
	assert (n<N);				//elegxos ean o swros exei gemisei
	A[n]=key;					//to eisagei teleutaio 
	int i=n+1; int pari=i/2;		//gia na broume to gonea diairoume me to duo
									//epeidh o pinakas ksekina na metra apo to 0 kai oxi apo 1,prosthetoume kai 
									//afairoume opou xreiazetai to 1  wste na briskoume to gonea kai to paidi alla kai 
									//na exoume prosbash sta swsta stoixeia tou pinaka
	n++;		//to epomeno stoixeio tha eisaxthei s auth th thesh 
	while(((i-1)>0)&&(A[i-1]>A[pari-1])){	
		swapHeap(&A[i-1],&A[pari-1]);
		i=pari; pari= i/2;
		
	}
}
	
	
void swapHeap(double *a,double *b){		//antallagh timwn 
	double temp=*a;
	*a=*b;
	*b=temp;
}

double deleteMaxHeap(double *A){
	assert(!isEmptyHeap(A));
	double maxKey=A[0];			//to prwto stoixeio einai to megalutero
	A[0]=A[--n];					//to teleutaio stoixeio ginetai prwto
	realloc(A,sizeof(double)*n);	//meiwnetai o pinakas kata 1 stoixeio
	int i=1, l=2 , r=3;
	while(l<=n){
		int mc=l;					
		if (r<=n&&A[r-1]>A[l-1])		//elegxei poio paidi einai megalutero
			mc=r;
		if (A[i-1]>=A[mc-1])			//to sugkrinei me to gonio
			break;
		swapHeap(&A[i-1],&A[mc-1]);
		i=mc; l=2*i; r=l+1;
	}
	return maxKey;
}

int isEmptyHeap(double *A){
	if(n==0)
		return 1;
	else return 0;
}

void destroyHeap(double * A){
	free(A);
}

TreeNode* insertBst(TreeNode *root, double x) {  
   TreeNode *v = root; 						 // v trexon kombos
   TreeNode *pv = NULL; 					// pv goneas tou v 
   while (v != NULL) {  
      pv = v; 
      if (x < v->item) v=v->left;		//an x mikrotero tou trexontos stoixeiou sugkrinoume me to aristero paidi tou v
      else if (x > v->item) v=v->right;	//alliws me to megalutero
           else { 
                printf("To %f yparxei idi sto dentro.\n", x);
				return root;
           }   
   }
   TreeNode *tmp = (TreeNode *) malloc(sizeof(TreeNode));	//dhmiourgia tou kainourgiou komvou
   tmp->item=x; tmp->left=tmp->right=NULL;    
   if (root != NULL) { 
      if (x < pv->item) pv->left=tmp;		
         else pv->right=tmp;
   } else root=tmp;
   return root;					 // epistrofi rizas dentrou
}

double deleteMaxBst(TreeNode **root){
	TreeNode *v= *root;			//trexwn komvos
	TreeNode *pv= NULL;			//goneas pv
	while(v->right!= NULL){			//psaxnei to deksiotero komvo
		pv=v;
		v=v->right;
	}
	double max=v->item;				
	if(v==*root)			//an to stoixeio auto einai h  riza
		if(v->left!=NULL)		
			*root=v->left;		//to aristero paidi ginetai h nea riza (profanws deksi paidi den uparxei)
		else					
			*root=NULL;			//alliws an einai fullo adeiazei to dentro
	else if(v->left!=NULL)			//an den einai h riza
			pv->right=v->left;		//o gonios tou v uiothetei to aristero tou paidi tou v
		else
			pv->right=NULL;
	free(v);
	return max;
}

int searchBst(TreeNode **root,TreeNode **parNode,double x){
	TreeNode *node=*root;		//ksekina apo th riza to psaksimo
	if (node==NULL) 			//an einai adeio to dentro 
		return 0; 
	
	while(1){
		counter+=1;			//o metrhths auksanetai me kathe sugkrish tou stoixeiou x pou psaxnoume me kapoion komvo
		if(x<node->item)		//an x mikrotero tou komvou 
			if(node->left==NULL)	//kai to aristero paidi einai NULL tote apotuxia
				return 0;
			else{					//an oxi NULL
				*parNode=node;		//h sugkrish tha sunexistei me to aristero paidi
				node=node->left;
			}
		else if(x>node->item)		//antistoixa an x megalutero
			if (node->right==NULL)
				return 0;
			else{
				*parNode=node;
				node=node->right;
			}
		else					//an vrethei epistrefei 1
			return 1;
		
	}
}

int rotateRight(TreeNode *parNode,TreeNode **root,double x){	//deksia peristrofh
	if(*root==NULL) return 0;			//ann to dentro einai adeio apotuxia
	TreeNode *node=NULL;
	if (parNode==NULL){			//an o komvos pou tha peristrepsoume den exe gonio
		node=*root;				//einai h riza
		if(node->left==NULL)		//proupothesh gia na ginei deksia peristrofh einai na uparxei aristero paidi
			return 0;
		else{
			*root=node->left;		//an uparxei to aristero paidi ginetai riza
			node->left=(*root)->right;	//kai to deksi paidi ths rizas ginetai aristero paidi tou komvou pou peristrefoume
			(*root)->right=node;		//to deksi paidi ths rizas einai o komvos peristrofhs
			return 1;
		}
	}
	else if(x<parNode->item){	//an exei gonio o komvos
		node=parNode->left;			//vriskei ton komvo peristrofhs mesw ths timhs tou komvou
		if(node->left==NULL) return 0;
		parNode->left=node->left;	//paidi tou goniou ginetai to aristero paidi tou komvou peristrofhs 
		node->left=parNode->left->right;	//aristero paidi tou komvou peristrofhs ginetai to deksi paidi tou prohgoumenou
											//aristerou paidiou tou komvou
		parNode->left->right=node;			
		return 1;
	}
	else{
		node=parNode->right;
		if(node->left==NULL) return 0;
		parNode->right=node->left;
		node->left=parNode->right->right;
		parNode->right->right=node;
		return 1;
	}
}
int rotateLeft(TreeNode *parNode,TreeNode **root,double x){			//antistoixa gia thn aristerh peristrofh  
	if(*root==NULL) return 0;								
	TreeNode *node=NULL;
	if(parNode==NULL){
		node=*root;
		if(node->right==NULL) 
			return 0;
		else{
			*root=node->right;
			node->right=(*root)->left;
			(*root)->left=node;
			return 1;
		}
	}
	else if(x<parNode->item){
		node=parNode->left;
		if(node->right==NULL) return 0;
		parNode->left=node->right;
		node->right=parNode->left->left;
		parNode->left->left=node;
		return 1;
	}
	else{
		node=parNode->right;
		if(node->right==NULL) return 0;
		parNode->right=node->right;
		node->right=parNode->right->left;
		parNode->right->left=node;
		return 1;
	}
}

void destroyBst(TreeNode *t) {
    // apodesmeysi mnimis me xrisi postorder diasxisis
    if (t==NULL) return;
    destroyBst(t->left);   // diagrafi kombwn aristerou ypodentrou
    destroyBst(t->right);  // diagrafi kombwn deksiou ypodentrou
    free(t); // diagrafi kombou t
}