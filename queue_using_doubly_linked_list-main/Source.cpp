// wat a shame..... (i don't care)
// am i a bad engineer ? (go fkk uself :) )
#pragma warning( disable : 4715 )
#pragma warning( disable : 28182 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 6308 )
#pragma warning( disable : 6011 )


#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>


#define DEBUG_LIMIT 9
#define MENU_LIMIT 1
#define TAIL 0
#define HEAD 1


using namespace std;


struct Node {
	int element;		// current value of the element in the node
	Node* lower_node;		// pointer to the lower element
	Node* highest_node;	
};


void enqueue(Node** head_node, Node** tail_node, int value, int enqueue_position);
int dequeue(Node** head_node, Node** tail_node, int dequeue_position);
int view(Node* head_node, Node* tail_node, int start_position);
long long int number_input(int limit);
int linked_array_length(Node* head_node);
int individual_task(Node* head_node, Node* tail_node);
void push(int value, Node** head_node);


int main()
{
	srand(time(0));

	short amount_choice;	// Amount of elements in the stack
	short menu_choice;
	Node* head_node = NULL;	// First node of the linked list
	Node* tail_node = NULL;	// Last node of the linked list

	cout << "Welcome to the queue program. Here you"
		<< "\ncan do some stuff with it. The queue is"
		<< "\nimplemented through doubly linked list.";

	cout << "\n\nPress ENTER to continue...";
	cin.get();

	for (;;)		// Main menu loop
	{
		system("CLS");

		cout << "Queue control panel: "
			<< "\n\n1. Enqueue"
			<< "\n2. Dequeue"
			<< "\n3. View"
			<< "\n4. Individual Task"
			<< "\nELSE. Exit"
			<< "\n\nType here: ";

		menu_choice = number_input(DEBUG_LIMIT);

		switch (menu_choice)
		{
		case 1:		// enqueue
		{
			system("CLS");

			cout << "Choose the way how you would"
				<< "\nlike to fill the queue: "
				<< "\n\n0. Fill with random numbers."
				<< "\nELSE. Fill by hand."
				<< "\n\nType here: ";

			short push_type_choice = number_input(DEBUG_LIMIT);

			system("CLS");



			system("CLS");

			cout << "Choose the position of the next"
				<< "\nitem to be enqueued in the queue."
				<< "\n\n0. Tail" 
				<< "\nELSE. Head"
				<< "\n\nType here: ";

			short enqueue_start_positiion = number_input(MENU_LIMIT);

			system("CLS");

			cout << "Choose how many numbers you"
				<< "\nwould to enqueue in the queue."
				<< "\n\nType here: ";

			while ((amount_choice = number_input(DEBUG_LIMIT)) < 1)
			{
				system("CLS");
				cout << "Incorrect value. Try again: ";
			}

			if (push_type_choice == 0) {
				int low_boundary;
				int top_boundary;
				int random_number;
				

				system("CLS");

				cout << "Set the top boundary for the random algorithm: ";
				top_boundary = number_input(DEBUG_LIMIT);
				cout << "\nSet the low boundary for the random algorith: ";

				// Boundaries could not be the same
				while ((low_boundary = number_input(DEBUG_LIMIT)) >= top_boundary)
				{
					system("CLS");
					cout << "Low boundary could not be the same as top boundary or greater. Try again: ";
				}

				system("CLS");
				cout << "Top boundary: " << top_boundary;
				cout << "\nLow boundary: " << low_boundary;
				cout << "\n\nGenerating random numbers...\n";

				if (enqueue_start_positiion == TAIL) {
					for (int i = 0; i < amount_choice; i++)
					{
						random_number = rand() % (top_boundary - low_boundary + 1) + low_boundary;
						enqueue(&head_node, &tail_node, random_number, TAIL);
						cout << endl << random_number << " was successfully pushed under the queue.";
					}
					cout << "\n\nStack filling was successful.\n";
				} else {	// HEAD
					for (int i = 0; i < amount_choice; i++)
					{
						random_number = rand() % (top_boundary - low_boundary + 1) + low_boundary;
						enqueue(&head_node, &tail_node, random_number, HEAD);
						cout << endl << random_number << " was successfully pushed onto the queue";
					}
					cout << "\n\nStack filling was successful.\n";
				}
			}
			else {
				system("CLS");

				if (enqueue_start_positiion == TAIL)
				{
					for (int i = 0; i < amount_choice; i++)
					{
						cout << "Enter a number: ";
						int user_input = number_input(DEBUG_LIMIT);
						enqueue(&head_node, &tail_node, user_input, TAIL);
						cout << endl << endl << user_input << " was successfully pushed under the queue.\n\n";
					}
				} else {
					for (int i = 0; i < amount_choice; i++)
					{
						cout << "Enter a number: ";
						int user_input = number_input(DEBUG_LIMIT);
						enqueue(&head_node, &tail_node, user_input, HEAD);
						cout << endl << endl << user_input << " was successfully pushed onto the queue.\n\n";
					}
				}
			}

			cout << "\n\nPress ENTER to continue...";
			cin.get();
			break;
		}
		case 2:
		{
			system("CLS");

			cout << "Choose the position of the item"
				<< "\nto be dequeued from the queue."
				<< "\n\n0. Tail"
				<< "\nELSE. Head"
				<< "\n\nType here: ";

			short dequeue_start_positiion = number_input(DEBUG_LIMIT);
			int dequeued_element;

			system("CLS");
			if (dequeue_start_positiion == TAIL) {
				if ((dequeued_element = dequeue(&head_node, &tail_node, TAIL)) == NULL) {
					cout << "Dequeue error. Queue underflow";
				} else {
					cout << "Element " << dequeued_element << " was successfully dequeued"
						<< "\nfrom the tail of the queue.";

				}
			} else {
				if ((dequeued_element = dequeue(&head_node, &tail_node, HEAD)) == NULL) {
					cout << "Dequeue error. Queue underflow";
				}
				else {
					cout << "Element " << dequeued_element << " was successfully dequeued"
						<< "\nfrom the head of the queue.";
				}
			}

			cout << "\n\nPress ENTER to continue...";
			cin.get();
			break;
		}
		case 3:
		{
			system("CLS");
			
			cout << "How would you like"
				<< "\nto view the queue?"
				<< "\n\n0. From head"
				<< "\nELSE. From tail"
				<< "\n\nType here: ";
			
			short view_type = number_input(MENU_LIMIT);
			
			system("CLS");

			if (view_type == 0) {
				if (view(head_node, tail_node, HEAD) == -1) {
					cout << "View error. Queue is empty!";
				}
			} else {
				if (view(head_node, tail_node, TAIL) == -1) {
					cout << "View error. Queue is empty!";
				}
			}

			cout << "\n\nPress ENTER to continue...";
			cin.get();
			break;
		}
		case 4:
		{
			system("CLS");

			if (individual_task(head_node, tail_node) == NULL) {
				cout << "Queue is empty.";
			}

			cout << "\n\nPress ENTER to continue...";
			cin.get();
			break;
		}
		default:
		{
			system("CLS");
			cout << "See you!\n";
			return 0;
		}
		}
	}
}


void enqueue(Node** head_node, Node** tail_node, int value, int enqueue_position)
{
	Node* new_node = new Node;
	new_node->element = value;
	
	// adding first element
	if (*head_node == NULL && *tail_node == NULL) {
		new_node->highest_node = new_node->lower_node = NULL;
		*head_node = *tail_node = new_node;
	} else {
		if (enqueue_position == TAIL) {
			new_node->lower_node = NULL;
			(*tail_node)->lower_node = new_node;
			new_node->highest_node = *tail_node;
			*tail_node = new_node;
		} else if (enqueue_position == HEAD) {
			new_node->highest_node = NULL;
			(*head_node)->highest_node = new_node;
			new_node->lower_node = *head_node;
			*head_node = new_node;
		}
	}
}


int dequeue(Node** head_node, Node** tail_node, int dequeue_position) 
{
	if (*head_node == NULL && *tail_node == NULL) {
		return NULL;
	}

	Node* temp_node;
	int element_to_return;

	if (dequeue_position == TAIL) {
		element_to_return = (*tail_node)->element;
		temp_node = (*tail_node)->highest_node;
		temp_node->lower_node = NULL;
		delete* tail_node;
		*tail_node = temp_node;
	} else {
		element_to_return = (*head_node)->element;
		temp_node = (*head_node)->lower_node;
		temp_node->highest_node = NULL;
		delete* head_node;
		*head_node = temp_node;
	}

	return element_to_return;
}


int individual_task(Node* head_node, Node* tail_node)
{
	Node* negative_stack_head = NULL;
	Node* negative_stack_tail = NULL;

	Node* positive_stack_head = NULL;
	Node* positive_stack_tail = NULL;

	int elements_amount = linked_array_length(head_node);
	int max_sub_amount;		// the biggest stack after division
	int positive_amount;
	int negative_amount;

	if (head_node == NULL && tail_node == NULL) { return NULL; }

	cout << "+---------+-----------------------+\t\t+---------+-----------------------+"
		<< "\n|    #    |    NEGATIVE QUEUE     |\t\t|    #    |     POSITIVE QUEUE    |"
		<< "\n+---------+-----------------------+\t\t+---------+-----------------------+";

	// 0 should not be in the stack
	while (head_node != NULL)
	{
		if (head_node->element < 0) {
			enqueue(&negative_stack_head, &negative_stack_tail, head_node->element, HEAD);
		}
		else if (head_node->element > 0) {
			enqueue(&positive_stack_head, &positive_stack_tail, head_node->element, HEAD);
		}
		head_node = head_node->lower_node;
	}

	negative_amount = linked_array_length(negative_stack_head);
	positive_amount = linked_array_length(positive_stack_head);
	max_sub_amount = positive_amount > negative_amount ? positive_amount : negative_amount;

	for (int i = max_sub_amount; i > 0; i--)
	{
		if (i > positive_amount) {
			printf("\n| %7d |      %6d           |\t\t|         |                       |", i, negative_stack_head->element);
			negative_stack_head = negative_stack_head->lower_node;
		}
		else if (i > negative_amount) {
			printf("\n|         |                       |\t\t| %7d |      %6d           |", i, positive_stack_head->element);
			positive_stack_head = positive_stack_head->lower_node;
		}
		else {
			printf("\n| %7d |      %6d           |\t\t| %7d |      %6.d           |", i, negative_stack_head->element, i, positive_stack_head->element);
			negative_stack_head = negative_stack_head->lower_node;
			positive_stack_head = positive_stack_head->lower_node;
		}
	}

	cout << "\n+---------+-----------------------+\t\t+---------+-----------------------+\n\n\n";
}


int linked_array_length(Node* head_node)
{
	if (head_node == NULL) { return 0; }

	int length = 0;

	while (head_node != NULL) {
		head_node = head_node->lower_node;
		length++;
	}
	return length;
}


int view(Node* head_node, Node* tail_node, int start_position)
{
	if (head_node == NULL) { return -1; }


	cout << "+---------+-----------------------+"
		<< "\n|    #    |         QUEUE         |"
		<< "\n+---------+-----------------------+";

	int elements_amount;

	if (start_position == HEAD)
	{
		elements_amount = linked_array_length(head_node);

		while (head_node != NULL) {
			if (head_node->element == 0) {
				printf("\n| %7d |           0           |", elements_amount--);
			}
			else {
				printf("\n| %7d |      %6d           |", elements_amount--, head_node->element);
			}
			head_node = head_node->lower_node;
		}
	} else {
		elements_amount = 1;
		while (tail_node != NULL) {
			if (tail_node ->element == 0) {
				printf("\n| %7d |           0           |", elements_amount++);
			}
			else {
				printf("\n| %7d |      %6d           |", elements_amount++, tail_node->element);
			}
			tail_node = tail_node->highest_node;
		}
	}

	cout << "\n+---------+-----------------------+\n\n\n";
}


void push(int value, Node** head_node)
{
	Node* new_node = new Node;
	new_node->element = value;
	new_node->lower_node = *head_node;
	*head_node = new_node;
}


int pop(Node** head_node)
{
	if (*head_node != NULL) {
		Node* temp_node = (*head_node)->lower_node;
		delete* head_node;
		*head_node = temp_node;
	}
	else {
		return -1;
	}
}


long long int number_input(int limit)
{
	// Limit set the number of digits in the number

	// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	// I have no idea why is that happening 
	// 2.147.483.647 = 2147483647
	// 2.147.483.648 = -2147483648
	// -2.147.483.648 = -2147483648
	// -2.147.483.649 = -2147483647

	char c;				// current entered symbol 	
	int length = 0;		// length of number (digit capacity, minus included), but index for digits is length - 1
	char* number_array_pointer;
	long long int number_array_integer = 0;
	int index;		// index for converting string to integer


	if ((number_array_pointer = (char*)malloc(sizeof(char) * length)) == NULL) {
		cout << "Fatal: failed to allocate " << sizeof(char) * length << " bytes.\n";
		abort();
	}

	for (;;) {
		c = _getch();
		if (c == 13 && length != 0) {		// Enter breaks down the loop
			if (number_array_pointer[0] == '-' && length < 2) {
				continue;
			}
			else {
				break;
			}
		}
		else if (c == '\b' && length != 0) {	// Backspace
			cout << "\b \b";
			length--;
			if (length == 0)
			{
				if ((number_array_pointer = (char*)malloc(sizeof(char) * length)) == NULL) {
					cout << "Fatal: failed to allocate " << sizeof(char) * length << " bytes.\n";
					abort();
				}
			}		// We cannot realloc 0 bytes
			else if ((number_array_pointer = (char*)realloc(number_array_pointer, sizeof(char) * length)) == NULL) {
				cout << "Fatal: failed to reallocate " << sizeof(char) * length << " bytes.\n";
				abort();
			}
		}
		else if (c == 45 && length == 0) {		// Minus for negative number
			length++;
			if ((number_array_pointer = (char*)realloc(number_array_pointer, sizeof(char) * length)) == NULL) {
				cout << "Fatal: failed to reallocate " << sizeof(char) * length << " bytes.\n";
				abort();
			}
			number_array_pointer[length - 1] = c;
			cout << c;
		}
		else if (c > 47 && c < 58 && length < limit) {		//	Allow to enter only digits
			length++;
			if ((number_array_pointer = (char*)realloc(number_array_pointer, sizeof(char) * length)) == NULL) {
				cout << "Fatal: failed to reallocate " << sizeof(char) * length << " bytes.\n";
				abort();
			}
			number_array_pointer[length - 1] = c;
			cout << c;
		}
		else {
			continue;
		}
	}

	if (number_array_pointer[0] == '-') {
		index = 1;
	}
	else {
		index = 0;
	}

	for (index; index < length; index++)
	{
		number_array_integer *= 10;
		number_array_integer += (long long int)number_array_pointer[index] - 48;
	}

	if (number_array_pointer[0] == '-') {
		number_array_integer *= -1;
	}

	// Return without free 'cause the calling code must take responsibility for freeing it (and the function must not free it)
	return number_array_integer;
}
