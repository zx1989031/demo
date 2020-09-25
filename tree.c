#include <stdio.h>
//树的双新表示法结点结构定义
#define MAX_TREE_SIZE 100
#define OK 0

typedef int Status;
typedef int TElemType; //树结点的数据类型，目前暂定为整型
typedef struct PINode //结点结构
{
    TElemType data; //结点数据
    int parent ;    //双亲位置
}PTNode;

typedef struct
{
    PTNode nodess[MAX_TREE_SIZE];
    int r,n;
}PTree;

//树的孩子表示法结构定义
#define MAX_TREE_SIZE 100
typedef struct CTNode{
    int child;
    struct CTNode *next;
}*ChildPtr;

typedef struct{
    TElemType data;
    ChildPtr firstchild;
}CTBox;

typedef struct{
    CTBox nodes[MAX_TREE_SIZE];
    int r,n
}CTree;

//树的孩子兄弟表示法结构定义
typedef struct CSNode
{
    TElemType data;
    struct CSNode *firstchild, *rightsib;
}CSNode,*CSTree;


//二叉树的二叉链表结点结构定义
typedef struct BiTNode
{
    TElemType data;
    struct BiTnode *lchild,*rchild 
}BiTNode,*BiTree;


//二叉树的前序遍历递归算法
void PreOrderTraverse(BiTree T)
{
    if(T==NULL)
        return;
    printf("%c",T->data);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}

//二叉树的中序遍历递归算法
void InOrderTraverse(BiTree T)
{
    if(T==NULL)
        return;
    InOrderTraverse(T->lchild);
    printf("%c",T->data);
    InOrderTraverse(T->rchild);
}

//二叉树的后序遍历递归算法
void PostOrderTraverse(BiTree T)
{
    if(T==NULL)
        return;
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    printf("%c",T->data);
}

//按前序八二叉树中结点的值(一个字符)
//表示空树，构造二叉链表表示二又漂亮树T
void CreateBiTree(BiTree *T)
{
    TElemType ch;
    scanf("%c",&ch);
    if(ch=='#')
        *T=NULL;
    else
    {
        *T=(BiTree)malloc(sizeof(BiTNode));
        if(!*T)
            exit(0);
        (*T)->data=ch;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
    }
    
}

// 二叉树的二叉线索存储结构定义
typedef enum {Link,Thread} PointerTag;
typedef struct BiThrNode
{
    TElemType data;
    struct BitThrNode *lchild, *rchild;
    PointerTag LTag;
    PointerTag RTag;
}BitThrNode,*BiThrTree;


BiThrTree pre;
void InThreading(BiThrTree p)
{
    if(p)
    {
        InThreading(p->lchild);     //递归左子树线索化
        if(!p->lchild){             //没有左孩子
            p->LTag=Thread;         // 有驱线索
            p->lchild=pre;          //左孩子指针指向前驱
        }
        if(!pre->rchild){            //前驱没有右孩子
            pre->RTag = Thread;     //后继线索
            pre->rchild = p;         //前驱右孩子掼针指向后继
        }
        pre = p;                    //保持pre指向p的前驱
        InThreading(p->rchild);      //递归右子树线索wx
    }
}

//T指向头结点，并没有结点左链lchild 指向根结点，头结点右链rchild 指向中序遍历的
//最后一个结点，中序遍历二叉线索链表表示的二叉树T
Status InOrderTraverse_Thr(BiThrTree T)
{
    BiThrTree p;
    p = T->lchild;
    while(p !=T){
        while(p->LTag==Link)
            p=p->lchild;
        printf("%c",p->data);
        while(p->RTag==Thread && p->rchild !=T){
            p = p->rchild;
            printf("%c",p->data);
        }
        p = p->rchild;
    }
    return OK;
}