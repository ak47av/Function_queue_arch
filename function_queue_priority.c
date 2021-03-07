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

typedef struct {
	fptr function;
	int priority;
}PriorityFunction;

struct Queue{
	int front, rear, size;
	int capacity;
	PriorityFunction* funcQueue;
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

void insert(struct Queue *queue, fptr func, int priority)
{
	if(isFull(queue))
		return;
	
	PriorityFunction funcToBeInserted;
	funcToBeInserted.function = func;
	funcToBeInserted.priority = priority; 
	
	if(isEmpty(queue)){
		queue->funcQueue[0] = funcToBeInserted;
	}
	else if(priority > queue->funcQueue[queue->size].priority){
		queue->funcQueue[queue->size] = funcToBeInserted;
	}
	else 
	{
		int currentPos = queue->size-1;
		PriorityFunction temp;
		queue->funcQueue[queue->size] = funcToBeInserted;
		while(currentPos >= 0){
			if(priority<queue->funcQueue[currentPos].priority){
				temp.function = queue->funcQueue[currentPos+1].function;
				temp.priority = queue->funcQueue[currentPos+1].priority; 
				queue->funcQueue[currentPos+1].function = queue->funcQueue[currentPos].function; 
				queue->funcQueue[currentPos+1].priority = queue->funcQueue[currentPos].priority;
				queue->funcQueue[currentPos].function = temp.function;
				queue->funcQueue[currentPos].priority = temp.priority;
			}
			else currentPos--;
		}
	}
	queue->rear = (queue->rear + 1)%queue->capacity;	
	queue->size = queue->size + 1;
}

fptr dequeue(struct Queue *queue)
{
	if(isEmpty(queue))
		return NULL;
	fptr func = queue->funcQueue[queue->front].function;
	queue->front = (queue->front+1)%queue->capacity;
	queue->size = queue->size-1; 
	return func;
}


fptr front(struct Queue* queue)
{
	if(isEmpty(queue))
		return NULL;
	return queue->funcQueue[queue->front].function;
}

fptr rear(struct Queue* queue)
{
	if(isEmpty(queue))
		return NULL;
	return queue->funcQueue[queue->rear].function;
}

void showQueue(struct Queue *queue)
{
	int i=0;
	printf("Queue: \n");
	for(i=queue->front;i<queue->front+queue->size;i++){
		printf("%d: %p\n",queue->funcQueue[i].priority,queue->funcQueue[i].function);
	}
	printf("\n\n");
}




int main(int argc, char **argv)
{
	
	struct Queue *queue = createQueue(5);
	/*
	insert(queue,functionA,2);	
	showQueue(queue);
	insert(queue,functionB,5);
	showQueue(queue);
	insert(queue,functionE,3);
	showQueue(queue);
	insert(queue,functionC,1);
	showQueue(queue);
	insert(queue,functionD,4);
	*/
	
	return 0;
}
