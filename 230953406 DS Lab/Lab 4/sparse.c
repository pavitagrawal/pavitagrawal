#include<stdio.h>
#define max 5
#include<stdlib.h>
struct CircularQueue{
    int front,rear,size;
    int arr[max];
};
void initQueue(struct CircularQueue *q){
    q->front=q->rear=-1;
    q->size =0;
}
int isEmpty(struct CircularQueue *q){
    return(q->size==0);
}
int isFull(struct CircularQueue *q){
    return(q->size == max);
}
void enqueue(struct CircularQueue *q,int value){
    if(isFull(q)){
        printf("Queue is full,cannot enqueue.\n");
        return;
    }
    if(isEmpty(q)){
        q->front = q->rear = 0;
    }
    else{
        q->rear = (q->rear+1)%max;
    }
    q->arr[q->rear] = value;
    q->size++;
    printf("Enqueued %d\n",value);
}
int dequeue(struct CircularQueue *q){
    if(isEmpty(q)){
        printf("Cannot dequeue,queue is empty");
        return -1;
    }
    int value = q->arr[q->front];
    if(q->front ==q->rear){
        q->front = q->rear = -1;
    }
    else{
        q->front =(q->front+1)%max;
    }
    q->size--;
    return value;
}
void displayQueue(struct CircularQueue *q){
    if(isEmpty(q)){
        printf("Queue is empty");
        return 0;
    }
    printf("Queue elements: ");
    int i = q->front;
    while (1) {
        printf("%d ", q->arr[i]);
        if (i == q->rear) break;
        i = (i + 1) % max;
    }
    printf("\n");
}
int main(){
    struct CircularQueue q;
    initQueue(&q);
    enqueue(&q,10);
    enqueue(&q,20);
    enqueue(&q,30);
    enqueue(&q,40);
    enqueue(&q,50);
    displayQueue(&q);
    enqueue(&q,60);
    printf("Dequeued %d\n", dequeue(&q));
    printf("Dequeued %d\n", dequeue(&q));
    displayQueue(&q);
    enqueue(&q, 60);
    enqueue(&q, 70);
    displayQueue(&q);
    return 0;
}





