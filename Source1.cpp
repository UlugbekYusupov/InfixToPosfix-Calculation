#include"Header.h"

int main() {
	
	STACK* stack1 = createStack();
	STACK* stack2 = createStack();

	char arr[80] = { 0 };
	infixToPostfix(arr,stack1);
	postfixCalculation(stack2, arr);

	destroyStack(stack1);
	destroyStack(stack2);
	_getch();
	return 0;
}