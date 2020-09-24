#include <stdio.h>
#include <iostream>

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

// T为非空串，若主串S中第pos个字符之后存在T相等的子串
//则返回第一个这样的子串在S中的位置，否则返回0
int Index(String S,String T,int pos)
{
    int n,m,i;
    String sub;
    if(pos>0)
    {
        n = StrLength(S);
        m = StrLength(T);
        i = pos;
        while(i<=n-m+1)
        {
            SubString(sub,S,i,m);
            if(StrCompare(sub,T) !=0)
                ++i;
            else
                return i;
        }
    }
    return 0;
}

//返回子串T在主串S中第pos个字符之后的位置，若不存在，则函数返回值为0
// T非空，1<=pos<=StrLength(s)

int Index(String S,String T,int pos)
{
    int i = pos; //i用于主串S中当前位置下标，若pos不为1
                // 则从pos位置开始匹配
                
    int j = 1;  //j用于子串T中当前位置下标值

    while(i<=S[0] && j<=T[0])
    {
        if(S[i] ==T[j])
        {
            ++j;
            ++j;
        }
        else
        {
            i = i-j+2;
            j=1;
        }
    }
    if(j>T[0])
        return i-T[0];
    else
        return 0;
}

