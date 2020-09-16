#include <stdio.h>

#define MAXSIZE 20 /*存储空间初始分配量*/
typedef int ElemType; /*ElemType 类型根据实际情况而定，这里假设为int*/
typedef struct list
{
    /* data */
    ElemType data[MAXSIZE]; /*数组存储数据元素，最大值为MAXSIZE*/
    int length;/*线性表当前长度*/
}SqList;



#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
/*Status 是函数的类型，其值是函数结果状态代码，如OK等*/
/*初始条件：顺序线性表 L已存在，1<=i<ListLength(L)*/
/*操作结果：用e返回L中第i数据元素的值*/

Status GetElem(SqList L,int i,ElemType *e){
    if(L.length==0 || i<1 || i>L.length)
        return ERROR;
    *e=L.data[i-1];
    return OK;
}


/*初始条件：顺序线表L已存在，1<=i<=ListLength(L)*/
/*操作结果：在L中第不个位置之前插入新的数据元素e,L的长度加1*/
Status ListInsert(SqList *L,int i,ElemType e){

    int k;
    if(L->length==MAXSIZE)  /*顺序线性表已满*/
        return ERROR;
    if(i<1 || i>L->length+1) /*当i不存范围内时*/
        return ERROR;
    if(i<=L->length){       /*若插入数据位置不存表尾*/
        for(k=L->length-1;k>=i-1;k--) /*将要插入位置后数据元素向后移动一位*/
            L->data[k+1] = L->data[k];
    } 
    L->data[i-1] = e;
    L->length++;
    return OK;
}

/*初始条件：顺序线表L已存在，1<=i<=ListLength(L)*/
/*操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减-1*/
Status ListDelete(SqList *L,int i,ElemType *e){

    int k;
    if(L->length==MAXSIZE)  /*顺序线性表已满*/
        return ERROR;
    *e=L->data[i-1];
    if(i<L->length){       /*若插入数据位置不存表尾*/
        for(k=i;k>L->length;k++) /*将要插入位置后数据元素向后移动一位*/
            L->data[k-1] = L->data[k];
    } 
    L->length--;
    return OK;
}

/*线性表的单链表存储结构*/
typedef struct Node{
    ElemType data;
    struct  Node *next;
    
} Node;

typedef struct Node *LinkList; /*定主LinkList*/

Status GetElem(LinkList L,int i,ElemType *e){
    int j;
    LinkList p;         /*声明一个结点*/
    p = L->next;        /*让p指向链表L的第一个结点*/
    j = 1;
    while(p && j<1){
        p = p->next;    /*让p指向下一个结点*/
        ++j;
        if(!p || j>i){
            return ERROR;
        }
        *e = p->data;
        return OK;
    }
}

Status ListInsert(LinkList *L,int i,ElemType e){
    int j;
    LinkList p,s;
    p=*L;
    j=1;
    while(p && j<i){
        p = p->next;
        ++j;
    }
    if(!p || j>i)
        return ERROR;
    s = (LinkList) malloc(sizeof(Node));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}

Status ListDelete(LinkList *L,int i,ElemType *e){

    int j;
    LinkList p, q;
    p = *L;
    j =1;
    while(p->next && j<i){ /*遍历寻找第 i 个元素*/
        p = p->next;
        ++j;
    }
    if(!(p->next) || j>i)
        return ERROR;
    q = p->next;
    p->next = q->next;      /*将 q的后继赋值给p的后续*/
    *e = q->data;           /*将q结点中的数据给 e*/
    free(q);                /*让系统回收此结点，释放内存*/
    return OK;
}


/*随机产生n个元素的值，建立带表头结点的单链线性表L（头插法）*/
void CreateListHead(LinkList *L,int n){
    LinkList p;
    int i;
    srand(time(0));
    *L = (LinkList)malloc(sizeof(Node));
    (*L)->next = NULL;
    for(i = 0;i<n ;i++){
        p = (LinkList)malloc(sizeof(Node)); /*生成新结点*/
        p->data = rand()%100+1;
        p->next = (*L)->next;
        (*L)->next = p;
    }
}


void CreateListTail(LinkList *L,int n){
    LinkList p,r;
    int i;
    srand(time(0));
    *L = (LinkList) malloc(sizeof(Node));
    r = *L;
    for(i=0;i<n;i++){
        p = (Node*)malloc(sizeof(Node));
        p->data = rand()%100+1;
        r->next = p;
        r = p;
    }
    r->next = NULL;
}

Status ClearList(LinkList *L){
    LinkList p,q;
    p = (*L)->next;
    while(p){
        q = p->next;
        free(p);
        p=q;
    }
    (*L)->next = NULL;
    return OK;
}

/*线性表的静态链表存储结构*/
#define MAXSIZE 1000
typedef struct{
    ElemType data;
    int cur;
} Compoonent,StaticLinkList[MAXSIZE];

/*将一堆数组 space 中各分量链成一备用链表*/
/*space[0].cur为头指针，0表示空指针*/
Status InitList(StaticLinkList space){
    int i;
    for(i=0;i<MAXSIZE-1;i++){
        space[i].cur = i+1;
    }
    space[MAXSIZE-1].cur = 0; /*目前静态表为空，最后一个元素的cur为0*/
    return OK;
}

/*若备用空间链表非空，则返回分配的结点下标，否则返回 0*/
int Malloc_SLL(StaticLinkList space){
    int i = space[0].cur; 
    if(space[0].cur)
        space[0].cur = space[i].cur;
    return i;
}

/*在L中第i个元素之前插入新的数据元素*/
Status ListInsert(StaticLinkList L, int i,ElemType e){
    int j,k,l;
    k = MAXSIZE -1 ;               /*注意k首先是最后一个元素的下标*/
    if(i<1 || i>ListLength(L)+1)
        return ERROR;
    j = Malloc_SLL(L);              /*获得空闲分量的下标*/
    if(j){
        L[j].data = e;
        for(l=1;i<=i-1;l++)
            k=L[k].cur;
        L[j].cur = L[k].cur;
        L[k].cur = j;
        return OK;
    }
    return ERROR;
}

/*将下标为k的空闲结点回收备用链表*/
void Free_SSL(StaticLinkList space,int k){
    space[k].cur = space[0].cur;
    space[0].cur = k;
}

/*删除在L中第i个数据元素*/
Status ListDelete(StaticLinkList L,int i){
    int j,k;
    if(i<1 || i>ListLength(L))
        return ERROR;
    k = MAXSIZE-1;
    for(j=1;j<=i-1;j++)
        k=L[k].cur;
    j = L[k].cur;
    L[k].cur = L[j].cur;
    Free_SSL(L,j);
    return OK;
}

/*初始条件：静态链表L已存在，操作结果：返回L中数据元素个数*/
int ListLength(StaticLinkList L){
    int j=0;
    int i = L[MAXSIZE-1].cur;
    while(i){
        i = L[i].cur;
        j++;
    }
    return j;
}

typedef struct DulNode{
    ElemType data;
    struct DuLNode *pricor;
    struct DuLnode *next;

} DulNode, *DuLinkList;


typedef int SElemType; /*SElemType 类型根据实际情况而定，这里假设为int*/
typedef struct {
    SElemType data[MAXSIZE];
    int top; /*用于栈顶指针*/
}SqStack;

/*插入元素e为新的栈顶元素*/
Status Push(SqStack *S, SElemType e){
    if(S->top ==MAXSIZE-1) /*栈满*/
    {
        return ERROR;
    }
    S->top++;
    S->data[S->top] = e;
    return OK;
}

Status Pop(SqStack *S, SElemType *e){
    if(S->top ==-1){
        return ERROR;
    }
    *e = S->data[S->top];
    S->top--;
    return OK;
}

/*两栈共享空间结构*/
typedef struct{
    SElemType data[MAXSIZE];
    int top1; /*栈1栈顶指针*/
    int top2; /*栈2栈顶指针*/
}SqDoubleStack;

/*插入元素e为新的栈顶元素*/
Status Push(SqDoubleStack *S,SElemType e, int stackNumber){
    if(S->top1+1==S->top2){         /*栈已满，不能再push新元素*/
        return ERROR;
    }
    if(stackNumber==1)               /*栈1有元素进栈*/
        S->data[++S->top1]=e;       /*若栈1则先top1+1 后给数组元素赋值*/
    else if(stackNumber==2)         /*栈2有元素进栈*/
        S->data[--S->top2] = e;    /*若栈2则先top2-1 后给数组元素赋值*/
    return OK;
}

/*若栈不空，则删除S的栈顶元素，用e返回其值，并返回其值，并返回OK; 否则返回ERROR*/
Status Pop(SqDoubleStack *S,SElemType *e,int stackNumber){
    if(stackNumber==1){
        if(S->top1==-1){
            return ERROR;
        }
        *e = S->data[S->top1--];
    }else if(stackNumber==2){
        if(S->top2==MAXSIZE){
            return ERROR;
        }
        *e = S->data[S->top2++];
    }
    return OK;
}

typedef struct  StatckNode{
    SElemType data;
    struct StackNode *next;

}StackNode,*LinkStackPtr;

typedef struct LinkStack{
    LinkStackPtr top;
    int count;
}LinkStack;

/*插入元素e为新的栈顶元素*/
Status Push(LinkStack *S, SElemType e){
    LinkStackPtr news = (LinkStackPtr)malloc(sizeof(StackNode));
    news->data = e;
    news->next = S->top;
    S->top = news;
    S->count++;
    return OK;
}

/*若栈不空，则删除S的栈顶元素，用e返回其值，并反加OK;否则返回ERROR*/
Status Pop(LinkStack *S,SElemType *e){
    LinkStackPtr p;
    if(StackEmpty(*S)){
        return ERROR;
    }
    *e = S->top->data;          
    p = S->top;                 /*将栈顶结点赋值给p */
    S->top=S->top->next;        /*使得栈顶指针下移一位，指向后一结点*/
    free(p);                    /*释放结点p*/
    S->count--;
    return OK;
}