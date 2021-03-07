#include <stdio.h>
#include <stdlib.h>

void functionA(void)
{
	printf("\nfunction A is running\n");
}

void functionB(void)
{
	printf("\nfunction B is running\n");
}

void functionC(void)
{
	printf("\nfunction C is running\n");
}

void functionD(void)
{
	printf("\nfunction D is running\n");
}

void functionE(void)
{
	printf("\nfunction E is running\n");
}

typedef void (*fptr)(void);

struct Queue{
	int front, rear, size;
	int capacity;
	fptr* funcQueue;
};

struct Queue *createQueue(int capacity)
{
	struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
	queue->front = queue->size = 0;
	queue->capacity = capacity;
	queue->rear = capacity-1;
	queue->funcQueue = malloc(queue->capacity*sizeof(queue->funcQueue));
	return queue;
}

int isFull(struct Queue* queue)
{
	return(queue->size == queue->capacity);
}

int isEmpty(struct Queue* queue)
{
	return(queue->size==0);
}

void enqueue(struct Queue *queue, fptr func)
{
	if(isFull(queue))
		return;
	queue->rear = (queue->rear + 1)%queue->capacity;
	queue->funcQueue[queue->rear] = func;
	queue->size = queue->size + 1;
}

fptr dequeue(struct Queue *queue)
{
	if(isEmpty(queue))
		return NULL;
	fptr func = queue->funcQueue[queue->front];
	queue->front = (queue->front+1)%queue->capacity;
	queue->size = queue->size-1; 
	return func;
}

void showQueue(struct Queue *queue)
{
	int i=0;
	printf("Queue: \n");
	for(i=queue->front;i<queue->rear+1;i++){
		printf("%d: %p\n",i,queue->funcQueue[i]);
	}
	printf("\n\n");
}

fptr front(struct Queue* queue)
{
	if(isEmpty(queue))
		return NULL;
	return queue->funcQueue[queue->front];
}

fptr rear(struct Queue* queue)
{
	if(isEmpty(queue))
		return NULL;
	return queue->funcQueue[queue->rear];
}


int main(int argc, char **argv)
{
	
	struct Queue *queue = createQueue(5);
	enqueue(queue,functionA);	
	showQueue(queue);
	enqueue(queue,functionB);
	showQueue(queue);
	front(queue)();
	return 0;
}
