//Imports
#include <iostream>
#include <fstream>
#include <cstring>
#include <math.h>
#include<stdio.h>
#include<stdlib.h>

using namespace std;

struct node{//Create a node struct
  int value;
  bool color = true;//true is red
  struct node *left = NULL;
  struct node *right = NULL;
  struct node *parent = NULL;
};

//Methods
void fileAdd(node* &root, int &cou);
void display(node* root, int depth);
void add(node* root, node* n, int input);
void manAdd(node* &root);
void check(node* &curr, node* root);

int main(){
  int count = 1;
  bool quit = false;//bool to check when user wants to quit
  node* root = NULL;
  while(!quit){//Main while
    cout << "Type a valid command(ADD, MADD, DISPLAY, QUIT)" << endl;//Prompt user for input
    char input[10];//Get input from user
    cin >> input;
    if(strcmp(input, "MADD") == 0){//if user wants to manually add
      manAdd(root);
    }
    if(strcmp(input,"ADD") == 0){//If user wants to add students
      fileAdd(root, count);
    }
    else if(strcmp(input, "DISPLAY")==0){//Dislay as a tree
      display(root, 0);
    }
    else if(strcmp(input,"QUIT") == 0){//If user wants to quit
      quit = true;
    }
  }
  return 0;
}

void fileAdd(node* &root, int &count){//Add using file
  cout << "How many numbers do you want to add?" << endl;
  int ninput;
  cin >> ninput;
  cin.clear();
  for(int i = 0; i < ninput; i ++){//Create how many numbers the user wants
    fstream file("nums.txt");//Import the number file
    char input[100];
    int num = 0;
    char temp[100];
    if(count > 50){
      count = 1;
    }
    //Get random number and add it 
    while (file.getline(input, 100, ' ')) {
      if (count == num) {
	strcpy(temp,input);
	num++;
      }
      num++;
    }
    int num2 = atoi(temp);
    count++;
    node* n = new node();
    n->value = num2; 
    if(root == NULL){
      n->parent = NULL;
      root = n;
    }
    else{
      add(root, n, num2);
    }
    check(n, root);
  }
}

void manAdd(node* &root){//Add manually
  cout << "What is the number you want to add(1-1000)" << endl;
  int input;
  cin >> input;
  cin.clear();
  node* n = new node();
  n->value = input; 
  if(root == NULL){
    root = n;
    return;
  }
  add(root, n, input);
  check(n, root);
}

void add(node* curr, node* n, int input){//Add into the right spot
  if(curr->right != NULL && input > curr->value){
    add(curr->right, n, input);
  }
  else if(curr->left != NULL && input <= curr->value){
    add(curr->left, n, input);
  }
  else{
    if(input > curr->value){
      n->parent = curr;
      curr->right = n;
    }
    if(input <= curr->value){
      n->parent = curr;
      curr->left = n;
    }
  }
}

void display(node* root, int depth){//Display method
  if(root->right != NULL){//If there is a right call print on the right
    display(root->right, depth + 1);
  }
  for(int i =0; i < depth; i++){//print tabs then yourself
    cout << "\t";
  }
  if(root->color){
    cout << root->value << " RED"<< endl;
  }
  else{
    cout << root->value << " BLACK"<< endl;
  }
  if(root->left != NULL){//If there is a right call print on the right
    display(root->left, depth + 1);
  }
}

void check(node* &curr, node* root){
  node* parent = curr->parent;
  node* grandparent;
  node* uncle;
  if(parent != NULL){
    grandparent = parent->parent;
  }
  else{
    grandparent = NULL;
  }
  if(grandparent != NULL){
    if(parent == grandparent->right){
      uncle = grandparent->left;
    }
    else{
      uncle = grandparent->right;
    }
  }
  else{
    uncle = NULL;
  }
  if(curr == root){
    curr->color = false;
  }
  if(parent != NULL && uncle != NULL && grandparent != NULL && parent->color && uncle->color){
    parent->color = false;
    uncle-> color = false;
    grandparent -> color = true;
    check(grandparent, root);
  }
  if(uncle == NULL || !uncle->color){
    if(grandparent != NULL){
      if(curr->value < grandparent->value && curr->value > parent->value || curr->value > grandparent->value && curr->value < parent->value){
	if(parent->right == curr){
	  node* one = parent->left;
	  node* two = curr->left;
	  node* three = curr->right;
	  grandparent->left = curr;
	  curr->right = three;
	  curr->left = parent;
	  parent->left = one;
	  parent->right = two;
	}
	else{
	  node* three = curr->left;
	  node* four = curr->right;
	  node* five = parent->right;
	  grandparent-> right = curr;
	  curr->right = parent;
	  curr->left = three;
	  parent->left = four;
	  parent->right = five;
	}
      }
    }
  }
  
  display(root, 0);
  cout << endl << "____________________________________________" << endl << endl;
  
}
