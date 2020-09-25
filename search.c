#include <stdio.h>
#include <cstdlib>

int Sequential_Search2(int *a,int n,int key)
{
    int i;
    a[0] = key;     //设置a[0] 为关键字值，我们称之为 哨兵
    i = n;
    while(a[i] !=key){
        i--;
    }
    return i; //返回0则说明查找失败
}

//折半查找
int Binary_Search(int *a,int n,int key)
{
    int low,high,mid;
    low = 1;
    high = n;
    while(low<=high)
    {
        mid = (low+high)/2;
        if(key<a[mid]){
            high = mid-1;
        }else if(key>a[mid]){
            low = mid+1;
        }else{
            return mid;
        }
    }
    return 0;
}


//插值查找
int Binary_Search02(int *a,int n,int key)
{
    int low,high,mid;
    low = 1;
    high = n;
    while(low<=high)
    {
        mid = low+(high-low)*(key-a[low])/(a[high]-a[low]);
        if(key<a[mid]){
            high = mid-1;
        }else if(key>a[mid]){
            low = mid+1;
        }else{
            return mid;
        }
    }
    return 0;
}

//生成指定长度斐波那契数组
// int getF(int n){
//     int F[n];
//     int i = 0;
//     while(i<n){
//         if(i==0){
//             F[i] = 0;
//         }else if(i==1){
//             F[i] = 1;
//         }else{
//             F[i] = F[i-1]+F[i-2];
//         }
//     }
//     return F;
// }

//斐波那契查找
int Fibonacci_Search(int *a ,int n, int key)
{
    int low,high,mid,i,k;
    low = 1;                                //定义最低下标为记录首位
    high = n;                               //定义最高下标为记录末位
    k = 0;
    int F[11] = {0,1,1,2,3,5,8,13,21,34,55}; //计算n位于斐波那契数列的位置
    while(n>F[k]-1){                        
        k++;
    }
    for(i=n;i<F[k]-1;i++){                 //将不满的数值补全
        a[i] = a[n];
    }

    while(low<=high){
        mid = low+F[k-1]-1;                //计算当前分隔的下标
        if(key<a[mid]){                    //若查找记录小于当前分隔记录
            high = mid-1;                  //最高下标调整 到分隔下标mid-1处
            k = k-1;                       //斐波那契数列一标减一位
        }else if(key>a[mid]){              //若查找记录大于当前分隔记录
            low = mid+1;                    //最低下标调整到分隔一标mid+1处
            k = k-2;                        //斐波那契数列一标减两位
        }else{
            if(mid<=n){
                return mid;              //若相等则说明mid即为查找到的位置
            }else{
                return n;               //若mid>0说明是补全数值，返回n
            }
        }
    }
    return 0;
}

#define FALSE 0;
#define TRUE 0;
typedef int Status;
typedef struct BiTNode{
    int data;
    struct BiTNode *lchild, *rchild;
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

//弟归查找二叉排序树T中是否存在
//指针f指向T的双亲，其初始调用值为 NULL
//若查找成功，则指针p指向该数据元素结点并返回true
//否则指针p指向查找路径上的访问的最后一个结点并返回FALSE

Status SearchBST(BiTree T,int key,BiTree f, BiTree *p)
{
    if(!T){
        *p = f;
        return FALSE;
    }else if(key ==T->data){
        *p = T;
        return TRUE;
    }else if(key<T->data){
        return SearchBST(T->lchild,key,T,p);
    }else{
        return SearchBST(T->rchild,key,T,p);
    }
}


//当前二叉排序树T中不存在关键字等于key的数据元素对
//插入key并返回TRUE 否则返回FALSE
Status InsertBST(BiTree *T,int key)
{
    BiTree p,s;
    if(!SearchBST(*T,key,NULL,&p)){
        s = (BiTree) malloc (sizeof(BiTNode));
        s->data = key;
        s->lchild = s->rchild = NULL;
        if(!p){
            *T = s;
        }else if(key<p->data){
            p->lchild = s;        
        }else{
            p->rchild = s;
        }
        return TRUE;
    }else{
        return FALSE;
    }
}

//创建一个二叉权
void createBST(){
    int i;
    int a[10] = {62,88,58,47,35,73,51,99,37,93};
    BiTree T = NULL;
    for(i=0;i<10;i++){
        InsertBST(&T,a[i]);
    }

    PreOrderTraverse(T);
}

//树的左右，及双亲指针的重合概念。只前有问题的是在这吧。
//指向某个key值的当前指针是自己的指针，也是他的双新的左或右指针
//要修改自已双亲的左或右指针，就是修改自已指针指向的值

//如图 8-6-13 删除结点 p 47时 (取左)
//1,找到结点 s 37 修改58的左结点 即当前指针的值为 p->data =  s->data ,当前左右指针不变
//2 修改 q 右节点指针为 s的左指针 即 q->lchild = s->lchild 释放 s内存空间

//找某个结点的值替换要删除结点的值，并修正替换后指针的变化
Status Delete(BiTree *p){
    BiTree q,s;
    if((*p)->rchild==NULL){
        q=*p;*p = (*p)->lchild;free(q); // p为指向当前查找到的key的指针。即为双亲的左或右指针
                                        //右空时,把当前地址的左指针指向的值改当前查找到的指针指向的值
                                        //释放当前值占用的空间
    }else if((*p)->lchild==NULL){
        q = *p; *p = (*p)->rchild;free(q); 
    }else{
        q = *p;s = (*p)->lchild;
        while (s->rchild)           //转左 然后向右到尽头
        {
            q=s;s = s->rchild;
        }
        (*p)->data = s ->data;      // s指向被删结点的直接前驱
        if(q!=*p){
            q->rchild = s->lchild;   //重接q的右子树
        }else{      
            q->lchild = s->lchild;    //重接q的左子树
        }
        free(s);   
    }
    return TRUE;
}

//取右
Status DeleteRight(BiTree *p){
    BiTree q,s;
    if((*p)->rchild==NULL){
        q=*p;*p = (*p)->lchild;free(q); // p为指向当前查找到的key的指针。即为双亲的左或右指针
                                        //右空时,把当前地址的左指针指向的值改当前查找到的指针指向的值
                                        //释放当前值占用的空间
    }else if((*p)->lchild==NULL){
        q = *p; *p = (*p)->rchild;free(q); 
    }else{
        q = *p;s = (*p)->rchild;
        while (s->lchild)           //转左 然后向右到尽头
        {
            q=s;s = s->lchild;
        }
        (*p)->data = s ->data;      // s指向被删结点的直接前驱
        if(q!=*p){
            q->lchild = s->rchild;   //重接q的右子树
        }else{      
            q->rchild = s->rchild;    //重接q的左子树
        }
        free(s);   
    }
    return TRUE;
}


//若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据结点，并返回TRUE，否则返回FALSE
Status DeleteBSF(BiTree *T,int key){
    if(!*T){
        return FALSE;
    }else{
        if(key == (*T)->data){
            return Delete(T);
        }else if(key<(*T)->data){
            return DeleteBSF(&(*T)->lchild,key);
        }else{
            return DeleteBSF(&(*T)->rchild,key);
        }
    }
}

//二叉树的二叉链表结点结构定义
typedef struct BiTode{
    int data;                           //结点数据
    int bf;                             //结点平衡因子
    struct BiTnode *lchild,*rchild;
}BiTNode,*BiTree;

//对以p为根的二叉排序树作右旋处理
//处理之后P指向新的树根结点，即旋转处理的左子树的根结点
void R_Rotate(BiTree *P){
    BiTree L;
    L = (*P)->lchild;               //L指向P的左子树根结点
    (*P)->lchild = L->rchild;       //L的右子树挂接为P的左子树
    L->rchild = (*P);               
    *P = L;                         //P指向新的根结点
}

//对以P为根的二叉排序树作左旋处理
//处理之后P指向新的树根结点，即旋转处理之前的右子树的根结点
void L_Rotate(BiTree *P)
{
    BiTree R;
    R = (*P)->rchild;               //R指向P的右子树根结点
    (*P)->rchild = R->lchild;       //R的左子树挂接为P的右子树
    R->lchild = (*P);
    *P = R;                         //P指向新的根结点
}

#define LH +1 //左高
#define EH 0  // 等高
#define RH -1 // 右高
//对以指针T所指结点为根的二叉树作左平衡树旋转处理
//本算法结束时，指针T指向新的根结点
void LeftBalance(BiTree *T)
{
    BiTree L,Lr;
    L = (*T)->lchild;
    switch(L->bf){
        case LH:
            (*T)->bf  = L->bf=EH;
            R_Rotate(T);
            break;
        case RH:
            Lr = L->rchild;
            switch (Lr->bf)
            {
            case LH:
                (*T) -> bf = RH;
                L->bf = EH;
                break;
            case EH:
                (*T) ->bf = L->bf = EH;
            case RH:
                (*T) ->bf=EH;
                L->bf = LH;
                break;
            }
            Lr->bf = EH;
            L_Rotate(&(*T)->lchild);  //对T的左子树作右旋平衡处理

            R_Rotate(T);             // 对T作右放平衡处理
    }
}


// 若在平衡二叉排序树T中不存在和e有相同关键字的结点，则插入一个
//数据元素为e的新结点并返回 1 否则返回0 若因插入而使二叉排序树
//失去平衡，则作平衡旋转处理，布尔变量taller反映T长高与否

Status InsertAVL(BiTree *T,int e ,Status *taller){
    if(!*T){
        //插入新结点，树长高，置taller 为true
        *T = (BiTree) malloc (sizeof(BiTNode));
        (*T)->data = e;
        (*T)->lchild = (*T)->rchild = NULL;
        (*T)->bf=EH;
        *taller = TRUE;
    }else{
        if(e==(*T)->data){
            *taller = FALSE;  //树中已存在和e有相同关键字的地点，则不再插入
            return FALSE;
        }
        if(e<(*T)->data){
            //应继续在T的左子树中进行搜索
            if(!InsertAVL(&(*T)->lchild,e,taller)){
                return FALSE;
            }
            if(taller){
                switch ((*T)->bf)
                {
                    case LH:
                        LeftBalance(T);
                        *taller=FALSE;
                        break;
                    
                    case EH:
                        (*T)->bf = LH;
                        *taller = TRUE;
                        break;
                    case RH:
                        (*T)->bf = EH;
                        *taller = FALSE;
                        break;
                }
            }

        }else{
            //应继续在T的右子树中进行搜索
            if(!InsertAVL(&(*T)->rchild,e,taller)){
                return FALSE;
            }
            if(*taller){
                switch ((*T)->bf)
                {
                    case LH:
                        (*T)->bf = EH;
                        *taller=FALSE;
                        break;
                    case EH:
                        (*T)->bf = RH;
                        *taller = TRUE;
                        break;
                    case RH:
                        RightBalance(T); //方法未实现
                        *taller = FALSE;
                        break;
                }
            }
        }
    }
}



int main(){
    int a[11] = {0,1,16,24,35,47,59,62,73,88,99};
    // printf(" %d ",Binary_Search(a,10,62));
    // printf(" %d ",Binary_Search02(a,10,62));
    // printf(" %d ",Fibonacci_Search(a,10,62));

    createBST();

    int i;
    int a[10] = {3,2,1,4,5,6,7,10,9,8};
    BiTree T = NULL;
    Status taller;
    for(i = 0;i<10;i++){
        InsertAVL(&T,a[i],&taller);
    }

}