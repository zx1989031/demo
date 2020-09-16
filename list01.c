#include <stdio.h>

int Fbi(int i){
    if(i<2)
        return i==0?0:1;
    return Fbi(i-1)+Fbi(i-2); //递归调用
}


int main()
{
    int i;
    int a[40];
    a[0] = 0;
    a[1] = 1;
    printf(" %d " ,a[0]);
    printf(" %d " ,a[1]);
    for(i=2;i<40;i++)
    {
        a[i] = a[i-1]+a[i-2];
        printf(" %d ",a[i]);
    }

    Fbi(40);

    return 0;
}

#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
typedef int QElemType; /*QElemType 类型根据实际情况而定，这里假设int*/
/*循环队列的顺序存储结构*/
typedef struct
{
    QElemType data[MAXSIZE];
    int front;  /*头指针*/
    int rear;   /*尾指针，若队列不空，指向队列尾元素的下一个位置*/
}SqQueue;

/*初始化一个空队列*/
Status InitQueue(SqQueue *Q)
{
    Q->front=0;
    Q->rear=0;
    return OK;
}

int QueueLenght(SqQueue Q)
{
    return (Q.rear-Q.front+MAXSIZE)%MAXSIZE;
}

/*若队列未满，则插入元素e为Q新的队尾元素*/
Status EnQueue(SqQueue *Q,QElemType e)
{   
    if((Q->rear+1)%MAXSIZE ==Q->front)   /*队列满的判断*/
        return ERROR;
    Q->data[Q->rear] = e;
    Q->rear = (Q->rear+1) %MAXSIZE;     //rerar 指针向后移一位置
    return OK;
}

//若队列不空 ,则删除Q中队列头元素，用e返回其值
Status DeQueue(SqQueue *Q,QElemType *e)
{
    if(Q->front ==Q->rear)
        return ERROR;
    *e = Q->data[Q->front];
    Q->front = (Q->front+1)%MAXSIZE;
    return OK;
}

typedef int QElemType;
typedef struct Qnode
{
    QElemType data;
    struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
    QueuePtr front,rear;
}LinkQueue;

Status EnQueue(LinkQueue *Q,QElemType e)
{
    QueuePtr s= (QueuePtr)malloc(sizeof(QNode));
    if(!s)
        exit(0);
    s->data = e;
    s->next = NULL;
    Q->rear->next = s;

    Q->rear = s;
    return OK;
}

Status DeQueue(LinkQueue *Q,QElemType *e)
{
    QueuePtr p;
    if(Q->front==Q->rear)
        return ERROR;
    p = Q->front->next;
    *e = p->data;
    Q->front->next = p->next;

    if(Q->rear ==p)
        Q->rear = Q->front;
    free(p);
    return OK;
}