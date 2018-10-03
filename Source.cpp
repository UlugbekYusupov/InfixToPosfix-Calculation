#include"Header.h"
STACK* createStack(void) {
	STACK* stack;
	try {
		stack = (STACK*)malloc(sizeof(STACK));
		if (!stack)
			throw "Bad Allocation";
		else {
			stack->count = 0;
			stack->top = nullptr;
		}
	}
	catch (const char* msg) {
		cout << msg;
	}
	return stack;
}
STACK_NODE* createNode(STACK* stack, void* dataInPtr) {
	STACK_NODE* newNode;
	try {
		newNode = (STACK_NODE*)malloc(sizeof(STACK_NODE));
		if (!newNode)
			throw "Bad Allocation Node";
		else {
			newNode->dataPtr = dataInPtr;
			newNode->link = nullptr;
		}
	}
	catch (const char* msg) {
		cout << msg;
	}
	return newNode;
}
bool pushStack(STACK* stack, void* dataInPtr) {

	STACK_NODE* newNode = createNode(stack, dataInPtr);
	newNode->link = stack->top;
	stack->top = newNode;

	(stack->count)++;

	return true;
}
void* popStack(STACK* stack) {

	void* dataOutPtr;
	STACK_NODE* temp;

	if (stack->count != 0) {
		temp = stack->top;
		dataOutPtr = stack->top->dataPtr;
		stack->top = stack->top->link;
		delete temp;
		(stack->count)--;
	}
	else
		dataOutPtr = nullptr;

	return dataOutPtr;
}
void* stackTop(STACK* stack) {
	if (stackCount(stack) == 0) {
		return nullptr;
	}
	else {
		return stack->top->dataPtr;
	}
}
bool emptyStack(STACK* stack) {
	return(stack->count == 0);
}
int stackCount(STACK* stack) {
	return stack->count;
}
STACK* destroyStack(STACK* stack) {
	STACK_NODE* temp;

	if (stack) {
		while (stack->top != nullptr) {
			free(stack->top->dataPtr);
			temp = stack->top;
			stack->top = stack->top->link;
			free(temp);
		}
		free(stack);
	}
	return nullptr;
}
void infixToPostfix(char* ar, STACK* stack) {

	char postfix[80] = { 0 };
	char temp[2] = { 0 };
	char token;
	char* dataPtr;
	while ((token = getchar()) != '\n') {
		if (token == '(') {
			dataPtr = (char*)malloc(sizeof(char));
			*dataPtr = token;
			pushStack(stack, dataPtr);
		}
		else if (token == ')') {
			dataPtr = (char*)popStack(stack);
			while (*dataPtr != '(') {
				temp[0] = *dataPtr;
				char space[] = " ";
				strcat(space, temp);
				strcat(postfix, space);
				dataPtr = (char*)popStack(stack);
			}
		}
		else if (isOperator(token)) {
			dataPtr = (char*)stackTop(stack);
			while (!emptyStack(stack) && priority(token) <= priority(*dataPtr)) {
				dataPtr = (char*)popStack(stack);
				temp[0] = *dataPtr;
				char space[] = " ";
				strcat(space, temp);
				strcat(postfix, space);
				dataPtr = (char*)stackTop(stack);
			}
			dataPtr = (char*)malloc(sizeof(char));
			*dataPtr = token;
			pushStack(stack, dataPtr);
		}
		else {
			temp[0] = token;
			char space[] = " ";
			strcat(space, temp);
			strcat(postfix, space);
		}
	}
	while (!emptyStack(stack)) {
		dataPtr = (char*)popStack(stack);
		temp[0] = *dataPtr;
		char space[] = " ";
		strcat(space, temp);
		strcat(postfix, space);
	}
	puts(postfix);
	strcpy(ar, postfix);
}
void postfixCalculation(STACK* stack, char* arr) {

	char token;
	int operand1, operand2, value;
	int* dataPtr;
	int i = 0;
	while (i < strlen(arr)) {

		if (!isOperator(arr[i])) {
			dataPtr = (int*)malloc(sizeof(int));
			*dataPtr = arr[i] - '0';
			pushStack(stack, dataPtr);
		}
		else {
			dataPtr = (int*)popStack(stack);
			operand2 = *dataPtr;
			dataPtr = (int*)popStack(stack);
			operand1 = *dataPtr;
			value = calc(operand1, arr[i], operand2);
			dataPtr = (int*)malloc(sizeof(int));
			*dataPtr = value;
			pushStack(stack, dataPtr);
		}

		i++;
	}
	dataPtr = (int*)popStack(stack);
	value = *dataPtr;
	cout << value;
}
int priority(char token) {
	if (token == '*' || token == '/')
		return 2;
	if (token == '+' || token == '-')
		return 1;
	return  0;
}
bool isOperator(char token) {
	if (token == '*' || token == '/' || token == '+' || token == '-')
		return true;
	return false;
}
int calc(int operand1, int oper, int operand2) {
	int result;

	switch (oper)
	{
	case '+':
		result = operand1 + operand2;
		break;
	case '-':
		result = operand1 - operand2;
		break;
	case '*':
		result = operand1 * operand2;
		break;
	case '/':
		result = operand1 / operand2;
		break;
	}
	return result;
}