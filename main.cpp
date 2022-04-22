/*
This is a class that emulates a Binary Search Tree
By: Kushal Rao
Last Modified: 4/22/22
*/
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
  bool red = true;
  struct node *left = NULL;
  struct node *right = NULL;
  struct node *parent = NULL;
};

//Methods
void fileAdd(node* &root, int &cou);
void display(node* root, int depth);
void add(node* &root, int input);
void manAdd(node* &root);

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
    add(root, num2);
  }
}

void manadd(node* &head){//Add manually
  cout << "What is the number you want to add(1-1000)" << endl;
  int input;
  cin >> input;
  cin.clear();
  add(head, input);
}

void add(node* &curr, int input){//Add into the right spot
  if(curr->right != NULL && input > curr->value){
    add(curr->right, input);
  }
  else if(curr->left != NULL && input <= curr->value){
    add(curr->left, input);
  }
  else{
    node* n = new node();
    n->value = input;
    if(input > curr->value){
      n->parent = curr;
      curr->right = n;
    }
    if(input <= curr->value){
      n->parent = curr;
      curr->left = n;
    }
    check(n); 
  }
}

void display(node* root, int depth){//Display method
  if(root->right != NULL){//If there is a right call print on the right
    display(root->right, depth + 1);
  }
  for(int i =0; i < depth; i++){//print tabs then yourself
    cout << "\t";
  }
  cout << root->value << endl;
  if(root->left != NULL){//If there is a right call print on the right
    display(root->left, depth + 1);
  }
}
