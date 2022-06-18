#include <stdlib.h>
#include <stdio.h>
typedef struct Node {
	void* value;
	struct Node* next;
	struct Node* prev;
}Node;
typedef struct DBLinkedList {
	Node* head;
	Node* tail;
	size_t size;
}DBLinkedList;
DBLinkedList* createDBLinkedList() {
	DBLinkedList* tmp = (DBLinkedList*)malloc(sizeof(DBLinkedList));
	tmp->head = tmp->tail = NULL;
	tmp->size = 0;
	return tmp;
}
void deleteDBLinkedList(DBLinkedList** list) {
	Node* tmp = (*list)->head;
	Node* next = NULL;
	while (tmp) {
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	free(*list);
	*list = NULL;
}


void pushFront(DBLinkedList* list, void* data) {
	Node* tmp = (Node*)malloc(sizeof(Node));
	if (tmp == NULL) {
		exit(1);
	}
	tmp->value = data;
	tmp->next = list->head;
	tmp->prev = NULL;
	if (list->head) {
		list->head->prev = tmp;
	}
	list->head = tmp;

	if (list->tail == NULL) {
		list->tail = tmp;
	}
	list->size++;
}
void* popFront(DBLinkedList* list) {
	Node* prev;
	void* tmp;
	if (list->head == NULL) {
		exit(2);
	}
	prev = list->head;
	tmp = prev->value;
	list->head = list->head->next;
	if (list->head) {
		list->head->prev = NULL;
	}
	if (prev == list->tail) {
		list->tail = NULL;
	}
	free(prev);
	list->size--;
	return tmp;
}
void pushBack(DBLinkedList* list, void* data) {
	Node* tmp = (DBLinkedList*)malloc(sizeof(DBLinkedList));
	if (tmp == NULL) { exit(1); }
	tmp->value = data;
	tmp->next = NULL;
	tmp->prev = list->tail;
	if (list->head == NULL) {
		list->head = tmp;
	}
	if (list->tail) {
		list->tail->next = tmp;
	}
	list->tail = tmp;
	list->size++;
}
void* popBack(DBLinkedList* list) {
	Node* next;
	void* tmp;
	if (list->tail == NULL) {
		exit(2);
	}
	next = list->tail;
	tmp = next->value;
	list->head = list->head->next;
	if (list->tail) {
		list->tail->next = NULL;
	}
	if (next == list->head) {
		list->head = NULL;
	}
	free(next);
	list->size--;
	return tmp;
}
void printDblLinkedList(DBLinkedList* list) {
	Node* tmp = list->head;
	while (tmp) {
		printf("%d ", *((int*)tmp->value));
		tmp = tmp->next;
	}
	printf("\n");
}

int main(void)
{
	DBLinkedList* list = createDBLinkedList();
	int a, b, c;

	a = 10;
	b = 20;
	c = 30;

	pushFront(list, &b);
	pushFront(list, &a);
	pushBack(list, &c);

	printDblLinkedList(list);
}