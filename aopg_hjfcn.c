#include <stdio.h>
#include <stdlib.h>

struct node{
	int height;
	int data;
	struct node * left;
	struct node * right;
};

struct node * insert(struct node * root,int x);
int heights(struct node * root);
struct node * rotateright(struct node * root);
struct node * rotateleft(struct node *root);
int height(struct node * root);
void inorder(struct node * root);
int findIndex(struct node * root, int number, int count);

int main(){

	struct node * root = NULL;

	int iterations;

	scanf("%d", &iterations);

	for (int i = 0; i < iterations; i++){
		int choice;
		int number;
		scanf("%d %d",&choice, &number);

		if(choice == 1){
			root = insert(root, number);
		}else{
			printf("%d\n", findIndex(root, number, 0));
		}

	}

	//inorder(root);

	
	return 0;
}

struct node * insert(struct node * root,int x){

	if(root == NULL){
		root = (struct node*)malloc(sizeof(struct node));
		root->data = x;
		root->left = NULL;
		root->right  = NULL;
	}
	else{
		if(x > root->data){
			root->right = insert (root->right , x);
			if(heights(root) == -2){
				if(x > root->right->data){
					root = rotateleft(root);
				}else{
					root->right = rotateright(root->right);
					root = rotateleft(root);
				}
			}
		}
		else{
			if(x < root->data){
				root->left = insert(root->left , x);
				if(heights(root) == 2){
					if(x < root->left->data){
						root = rotateright(root);
					}else{

						root->left = rotateleft(root->left);
						root = rotateright(root);
					}
				}
			}
		
		root->height = height(root);
		}
	}
	return(root);
}

int heights(struct node * root){
	int lefth;
	int righth;
	if(root == NULL){
		return(0);
	}
 
	if(root->left==NULL){
		lefth = 0;
	}
	else{
		lefth = 1 + root->left->height;
	}
 
	if(root->right == NULL){
		righth = 0;
	}
	else{
		righth = 1 + root->right->height;
	}
 
	return(lefth - righth);
}


struct node * rotateright(struct node * root){
	struct node * temp;
	temp = root->left;
	root->left = temp->right;
	temp->right = root;
	root->height = height(root);
	temp->height = height(temp);
	return(temp);
}
 
struct node * rotateleft(struct node *root){
	struct node * temp;
	temp = root->right;
	root->right = temp->left;
	temp->left = root;
	root->height = height(root);
	temp->height = height(temp);
	
	return(temp);
}

int height(struct node * root)
{
	int lefth;
	int righth;
	if(root == NULL){
		return(0);
	}
	
	if(root->left == NULL){
		lefth = 0;
	}else{
		lefth = 1 + root->left->height;
	}
		
	if(root->right == NULL){
		righth = 0;
	}else{
		righth = 1 + root->right->height;
	}
	
	if(lefth > righth){
		return(lefth);
	}
	
	return(righth);
}

int findIndex(struct node * root, int number, int count){
	if(root != NULL){
		findIndex(root->left, number, count);
		if(root->data == number){
			return count;
		}
		printf("%d\n",root->data);
		count++;
		findIndex(root->right, number, count);
	}
}

void inorder(struct node * root){
	//static int count = 0;
	if(root != NULL){
		inorder(root->left);
		printf("%d\n",root->data);
		inorder(root->right);
	}
}