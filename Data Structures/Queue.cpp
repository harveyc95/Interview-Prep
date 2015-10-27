#include <assert.h>

struct node {
	Tid thread_id;
	struct node* next;
};

void queue_print (struct wait_queue *q) {
	printf("---------------------------------------------\n");
	struct node* nodePointer = q->head;
	int i = 0;
	while (nodePointer != NULL) {
		printf("(Node %d -> %d)", i, nodePointer->thread_id);
		i++;
		nodePointer = nodePointer->next;
	}
	if (q->tail == NULL) 
		return;
	printf("tail is: %d\n", q->tail->thread_id);
	printf("---------------------------------------------\n");
}

void queue_add (struct wait_queue *q, Tid id) {
	struct node *newNode = (struct node*)malloc(sizeof(struct node));
	newNode->thread_id = id;
	newNode->next = NULL;
	if (q->head == NULL) {
		q->head = newNode;
		q->tail = newNode;
	} else {
		q->tail->next = newNode;
		q->tail = newNode;
	}
	return;
}

Tid queue_remove_first (struct wait_queue *q) {
	if (q->head == NULL)
		return -1;
	Tid removedTid = q->head->thread_id;
	if (q->head == q->tail) { // if there is only 1 element
		q->head = NULL;
		free(q->tail);
		q->tail = NULL;
		return removedTid;
	}
	// there are multiple elements in the queue
	struct node* nodePointer = q->head; // save the head pointer
	q->head = q->head->next; // advance the head pointer by one
	nodePointer->next = NULL;
	free(nodePointer);
	return removedTid;
}

Tid queue_remove_index (struct wait_queue *q, Tid  id) {
	struct node *currNode = q->head;
	struct node *prevNode = NULL;
	// if id is the first element
	if (q->head == NULL)
		return -1;
	if (q->head->thread_id == id) {
		return queue_remove_first(q);
	}
	while (currNode != NULL && currNode->thread_id != id) {
		prevNode = currNode;
		currNode = currNode->next;
	}
	if (currNode == NULL) // if not found
		return -1;
	Tid removedTid = currNode->thread_id; // save removed Tid
	if (currNode == q->tail) { // id is at the end of the list
		prevNode->next = NULL;
		q->tail = prevNode;
	} else { // id is in the middle
		prevNode->next = currNode->next;
		currNode->next = NULL;
	}
	free(currNode);
	return removedTid;
}