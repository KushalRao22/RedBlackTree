//With deletion
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
void add(node* curr, node* n, int input, node* &root);
void manAdd(node* &root);
void check(node* curr, node* &root);

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
      if(root != NULL){
	display(root, 0);
      }
      else{
	cout << "There is no root" << endl;
      }
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
      check(root, n);
    }
    else{
      add(root, n, num2, root);
    }
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
    check(n, root);
    return;
  }
  add(root, n, input, root);
  
}

void add(node* curr, node* n, int input, node* &root){//Add into the right spot
  if(curr->right != NULL && input > curr->value){
    add(curr->right, n, input, root);
  }
  else if(curr->left != NULL && input <= curr->value){
    add(curr->left, n, input, root);
  }
  else{
    if(input > curr->value){
      n->parent = curr;
      curr->right = n;
      check(curr->right, root);
    }
    if(input <= curr->value){
      n->parent = curr;
      curr->left = n;
      check(curr->left, root);
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
    cout << root->value << " RED";
  }
  else{
    cout << root->value << " BLACK";
  }
  if(root->parent == NULL){
    cout << " NULL" << endl;
  }
  else{
    cout << " parent:" << root->parent->value << endl; 
  }
  if(root->left != NULL){//If there is a right call print on the right
    display(root->left, depth + 1);
  }
}

void check(node* curr, node* &root){
  node* parent = NULL;
  node* grandparent = NULL;
  node* uncle = NULL;
   if (curr->parent != NULL) {
    parent = curr->parent;
    if (parent->parent != NULL) {
      grandparent = parent->parent;
      if (grandparent->left == parent) {
	uncle = grandparent->right;
      }
      else if (grandparent->right == parent) {
	uncle = grandparent->left;
      }
    }
  }
   //Case 1
   if(curr == root){
     curr->color = false;
     return;
   }
   //Case 2
   else if(parent != NULL && !parent->color){
     return;
   }  
  //Case 3
   else if(uncle != NULL && parent->color && uncle->color){
    parent->color = false;
    uncle-> color = false;
    grandparent -> color = true;
    check(grandparent, root);
  }
   //Try else if if this does not work
   else if(uncle == NULL || !uncle->color){
     //Case 4
     if (parent == grandparent->right && curr == parent->left) {
       grandparent->right = curr;
       curr->parent = grandparent;
       node* temp = curr->right;
       curr->right = parent;
       parent->parent = curr;
       if(temp != NULL){
	    temp->parent = parent;
	  }
       parent->left = temp;
       parent = curr;
       curr = parent->right;
       curr->parent = parent;
    }
     else if (parent == grandparent->left && curr == parent->right) {
       grandparent->left = curr;
       curr->parent = grandparent;
       node* temp = curr->left;
       curr->left = parent;
       parent->parent = curr;
       if(temp != NULL){
	    temp->parent = parent;
	  }
       parent->right = temp;
       parent = curr;
       curr = parent->left;
       curr->parent = parent;
     }
     //Case 5
     if (parent->color && curr->color) {
     node* greatgrandparent = NULL;
	if(grandparent->left == parent && parent->left == curr){
	  node* temp = parent->right;
	  parent->right = grandparent;
	  if(grandparent != root){
	    greatgrandparent = grandparent->parent;
	    if(greatgrandparent->left == grandparent){
	      greatgrandparent->left = parent;
	    }
	    else{
	      greatgrandparent->right = parent;
	    }
	    parent->parent = greatgrandparent;
	  }
	  else {
	    parent->parent = NULL;
	    root = parent;
	  }
	  grandparent->parent = parent;
	  if(temp != NULL){
	    temp->parent = grandparent;
	  }
	  grandparent->left = temp;
	  parent->color = false;
	  grandparent->color = true;
	}
	else if(grandparent->right == parent && parent->right == curr){
	  node* temp = parent->left;
	  parent->left = grandparent;
	  if (grandparent != root) {
	    greatgrandparent = grandparent->parent;
	    if(greatgrandparent->left == grandparent){
	      greatgrandparent->left = parent;
	    }
	    else{
	      greatgrandparent->right = parent;
	    }
	    parent->parent = greatgrandparent;
	  }
	  else {
	    parent->parent = NULL;
	    root = parent;
	  }
	  grandparent->parent = parent;
	  if(temp != NULL){
	    temp->parent = grandparent;
	  }
	  grandparent->right = temp;
	  parent->color = false;
	  grandparent->color = true;
	}
      }
   }
}
