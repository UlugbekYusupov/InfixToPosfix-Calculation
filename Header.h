#pragma once
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include<conio.h>
#include<string>
using namespace std;

/*Stack ADT Type Initialization
	Written by: Yusupov Mirzoulugbek
	Data: 2018.10.03
*/

typedef struct node {
	void* dataPtr;
	struct node* link;
}STACK_NODE;

typedef struct {
	int count;
	STACK_NODE* top;
}STACK;

STACK* createStack(void);
STACK* destroyStack(STACK* stack);
STACK_NODE* createNode(STACK* stack, void* dataInPtr);
void* popStack(STACK* stack);
void* stackTop(STACK* stack);
bool pushStack(STACK* stack, void* dataInPtr);

void infixToPostfix(char* ar, STACK* stack);
void postfixCalculation(STACK* stack, char* arr);

bool emptyStack(STACK* stack);
int stackCount(STACK* stack);

int priority(char token);
bool isOperator(char token);
int calc(int operand1, int oper, int operand2);
