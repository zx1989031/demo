#include <stdio.h>
typedef char VertextType;
typedef int EdgeType;
#define MAXVEX 9
#define INFINITY 65535

typedef struct {
    VertextType vexs[MAXVEX];           //顶点表
    EdgeType arc[MAXVEX][MAXVEX];       //邻接矩阵，可看作边表
    int numVertexes,numEdges;
}MGraph;

//建立无向网图的邻接矩阵表示
void CreateMGraph(MGraph *G){
    int i,j,k,w;
    printf("输入顶点数据和边数：\n");
    scanf("%d,%d",&G->numVertexes,&G->numEdges); //输入顶点数和边数
    for(i = 0;i<G->numVertexes;i++)
        scanf(&G->vexs[i]);
    for(i = 0;i<G->numVertexes;i++)
        for(j=0;j<G->numVertexes;j++)
            G->arc[i][j] = INFINITY;
    
    for(k=0;k<G->numEdges;k++){
        printf("输入边（vi,vj）上的下标不，下标j和树 w:\n");
        scanf("%d,%d,%d",&i,&j,&w);
        G->arc[i][j] = w;
        G->arc[j][i] = G->arc[i][j];  //图为无向图，矩阵对称
    }
}

typedef char VertexType;
typedef int EdgeType;

typedef struct EdgeNode{
    int adjvex;
    EdgeType weight;
    struct EdgeNode *next;
}EdgeNode;

typedef struct VertexNode{
    VertextType data;
    EdgeNode *fristedge;
}VertexNode,AdjList[MAXVEX];

typedef struct{
    AdjList adjList;
    int numVertexes,numEdges;
}GraphAdjList;

//建立图的邻接表结构
void CreateALGraph(GraphAdjList *G){
    int i,j,k;
    EdgeNode *e;
    printf("输入顶点数和边数：\n");
    scanf("%d,%d",&G->numVertexes,&G->numEdges);
    for(i=0;i<G->numVertexes;i++){
        scanf(&G->adjList[i].data);
        G->adjList[i].fristedge=NULL;
    }

    for(k=0;k<G->numVertexes;k++){
        printf("输入边（vi,vj）上的顶点序号：\n");
        scanf("%d,%d",&j,&j);
        e = (EdgeNode *)malloc(sizeof(EdgeNode));
        e->adjvex=j;                                 //邻接序号为j
        e->next = G->adjList[i].fristedge;           //将e指针指向当前顶点指向的结点
        G->adjList[i].fristedge=e;
        e=(EdgeNode *)malloc(sizeof(EdgeNode));     //向内存中申请空间 生成边表结点

        e->adjvex=i;                                //邻接序号为i
        e->next = G->adjList[j].fristedge;          //将e指针指向当前顶点指向的结点
        G->adjList[j].fristedge = e;                //将当前顶点的指针指向 e*
    }
}

#define TRUE 1
#define MAX 100
#define FALSE 0
typedef int Boolean;
Boolean visited[MAX];
void DFS(MGraph G,int i){
    int j;
    visited[i] = TRUE;
    printf("%c",G.vexs[i]);

    for(j=0;j<G.numVertexes;j++){
        if(G.arc[i][j] ==1 && !visited[j]){
            DFS(G,j);
        }
    }
}

//邻接矩阵的深度遍历操作
void DFSTraverse(MGraph G){
    int i;
    for(i=0;i<G.numVertexes;i++){
        visited[i] = FALSE;
    }
    for(i=0;i<G.numVertexes;i++){
        if(!visited[i]){
            DFS(G,i);
        }
            
    }
}


//邻接表的深度优先递归算法
void DFSLink(GraphAdjList *GL,int i){
    EdgeNode *p;
    visited[i] = TRUE;
    printf("%c",GL->adjList[i].data);
    p = GL->adjList[i].fristedge;
    while(p){
        if(!visited[p->adjvex])
            DFSLink(GL,p->adjvex);
        p = p->next;
    }
}

// 邻接表的深度遍历操作
void DFSTraverse(GraphAdjList *GL){
    int i;
    for(i=0;i<GL->numVertexes;i++){
        visited[i] = FALSE;
    }
    for(i=0;i<GL->numVertexes;i++){
        if(!visited[i])
            DFSLink(GL,i);
    }
}

//-----------------------------
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define FALSE 0
typedef int Status;
typedef int QElemType;
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
//------------------------------

//邻接矩阵的广度遍历算法
void BFSTraverse(MGraph G)
{
    int i,j;
    SqQueue Q;
    for(i=0;i<G.numVertexes;i++){
        visited[i] = FALSE;
    }
    InitQueue(&Q);

    for(i=0;i<G.numVertexes;i++){
        if(!visited[i]){
            visited[i]=TRUE;
            printf("%c",G.vexs[i]);
            EnQueue(&Q,i);

            while(!QueueEmpty(Q)){
                DeQueue(&Q,&i);

                for(j=0;j<G.numVertexes;j++){
                    if(G.arc[i][j]==1 && !visited[j]){
                        visited[j] =TRUE;
                        printf("%c",G.vexs[j]);
                        EnQueue(&Q,j);
                    }
                }
            }

        }
    }
}


//prim 算法生成最小生成树
void MiniSpanTree_Prim(MGraph G)
{
    int data[9][9] = {
        {1,2,3,4,5,6,7,8,9},
        {1,2,3,4,5,6,7,8,9},
        {1,2,3,4,5,6,7,8,9},
        {1,2,3,4,5,6,7,8,9},
        {1,2,3,4,5,6,7,8,9},
        {1,2,3,4,5,6,7,8,9},
        {1,2,3,4,5,6,7,8,9},
        {1,2,3,4,5,6,7,8,9},
        {1,2,3,4,5,6,7,8,9}
        };

    
    int min,i,j,k;
    int adjvex[MAXSIZE];        //保存相关顶点下标
    int lowcost[MAXSIZE];       //保存相关顶点间边的权值

    lowcost[0] = 0;             //初始化第一个权值为0 即v0加入生成树
                                //lowcost 的值为0 在这里就是此下标的顶点已加入生成树
    adjvex[0] = 0;
    
    for(i=1;i<G.numVertexes;i++){
        lowcost[i] = G.arc[0][i];  //将v0顶点与之有边的权值存入数组
        adjvex[i] = 0;
    }

    for(i=1;i<G.numVertexes;i++){
        min = INFINITY;
        j = 1;k=0;
        while(j<G.numVertexes){
            if(lowcost[j] !=0 && lowcost[j]<min){
                min = lowcost[j];                    //则让当前权值成为最值
                k=j;                                // 将当前最小值的下标存入 k
            }
            j++;
        }
    }
    printf("(%d,%d)",adjvex[k],k);  //打印当前顶点边中权值最小边

    lowcost[k] = 0;                 //将当前顶点的权值设置为0 表示顶点已经完成任务

    for(j=1;j<G.numVertexes;j++)    //循环所有顶点
    {
        if(lowcost[j] !=0 && G.arc[k][j]<lowcost[j])    //若下标为k顶点各边权值小于此前这些顶点未被加入生成树权值
        {
            lowcost[j] = G.arc[k][j];               //将较小值存入
            adjvex[j] =k;                           // 将下标为k的顶点存入adjvex
        }
    }

}


//对边集数组 edge 结构的定义
typedef struct
{
    /* data */
    int begin;
    int end;
    int weight;
}Edge;


//Kruskal 算法生成最小生成树
void MiniSpanTree_Kruskal(MGraph G)
{
    int i,n,m;
    Edge edges[MAXVEX];         //定义边集数组
    int parent[MAXVEX];         //定义一数组用来判断边与边是否形成环路
                                //此处省略将邻接矩阵 G转化为边集数组 edges 并按权由小到大排序代码
    for(i = 0;i<G.numVertexes;i++){
        parent[i]=0;
    }
    for(i=0;i<G.numVertexes;i++){
        n = Find(parent,edges[i].begin);
        m = Find(parent,edges[i].end);
        if(n != m){
            parent[n] = m;      //将此边的结尾顶点放入下标为起点的parent中
                                //表示此顶点已经生成树集合中
            printf("(%d,%d) %d",edges[i].begin,edges[i].end,edges[i].weight);
        }
    }
}

int Find(int *parent,int f)  //查找链接线顶点的尾部下标
{
    while(parent[f]>0){
        f = parent[f];
    }
    return f;
}

#define MAXVEX 9
#define INFINITY 65535
typedef int Pathmatirx[MAXVEX];         //用于存储最短路径下标的数组
typedef int ShortPathTable[MAXVEX];     //用于存储到和各点最短路径的权值和

//P[v] 的值为前驱顶点下标，D[v] 表示v0到v的最短路径长路和。
void ShortestPath_Dijkstra(MGraph G,int v0,Pathmatirx *P,ShortPathTable *D)
{
    int v,w,k,min;
    int final[MAXVEX];
    for(v=0;v<G.numVertexes;v++){
        final[v] = 0;
        (*D)[v] = G.arc[v0][v];
        (*P)[v] = 0;
    }

    (*D)[v0] = 0;
    final[v0] = 1;

    //开始主循环，每次求得v0到某个v顶点的最短路径
    for(v=1;v<G.numVertexes;v++){
        min = INFINITY;
        for(v=0;v<G.numVertexes;w++){
            if(!final[w] && (*D)[w]<min){
                k = w;
                min = (*D)[w];
            }
        }
        final[k] = 1;
        for(w=0;w<G.numVertexes;w++){
            if(!final[w] && (min+G.arc[k][w]<(*D)[w])){
                (*D)[w] = min+ G.arc[k][w];
                (*P)[w] = k;
            }
        }
    }
}

//Floyd 算法 求网图G中各顶点v到其余顶点w最短路径P[v][w]及带权长度D[v][w]
typedef int Pathmatirx[MAXSIZE][MAXSIZE];
typedef int ShortPathTable[MAXSIZE][MAXSIZE];

void ShortestPath_Floyd(MGraph G,Pathmatirx *P,ShortPathTable *D)
{
    int v,w,k;
    for(v=0;v<G.numVertexes;++v){
        for(w=0;w<G.numVertexes;++w){
            (*D)[v][w] = G.arc[v][w];
            (*P)[v][w] = w;
        }
    }
    for(k=0;k<G.numVertexes;++k){
        for(v=0;v<G.numVertexes;++v){
            for(w=0;w<G.numVertexes;++w){
                //如果经过下标为k顶点路径比原两点间路径更短
                //将当前两点间权值设置为更小的一个
                if((*D)[v][w]>(*D)[v][k]+(*D)[k][w]){
                    (*D)[v][w] = (*D)[v][k]+(*D)[k][w];
                    (*P)[v][w] = (*P)[v][k];    //路径设置经过下标为k的顶点
                }
            }
        }
    }
}

//求最短径的显示代码
void getMinShortPath(MGraph G,Pathmatirx *P,ShortPathTable *D){
    int v,w,k;
    for(v=0;v<G.numVertexes;++v){
        for(w=v+1;w<G.numVertexes;w++){
            printf("v%d-v%d weight:%d",v,w,D[v][w]);
            k = P[k][w];
            printf("path: %d",v);
            
            while(k!=w)
            {
                printf("->%d ",k);
                k = P[k][w];
            }
            printf("-> %d\n",w);
        }
    }
    printf("\n");
}

//拓扑排序
typedef struct EdgeNode{
    int adjvex;
    int weight;
    struct EdgeNode *next;
}EdgeNode;

typedef struct VertexNode{
    int in;
    int data;
    EdgeNode *firstedge;
}VertexNode,AdjList[MAXSIZE];

typedef struct{
    AdjList adjList;
    int numVertexes,numEdges;
}GraphAdjList,*GraphAdjList;

// 拓扑排序 若GL无回路，则输出拓扑排序列并返回OK,若有回路返回ERROR
Status TopologicalSort(GraphAdjList GL){
    EdgeNode *e;
    int i,k,gettop;
    int top=0;
    int count=0;
    int *stack;
    stack=(int *)mallock(GL->numVertexes * sizeof(int));
    for(i=0;i<GL->numVertexes;i++){
        if(GL->adjList[i].in==0){
            stack[++top] = i;
        }
    }
    while(top !=0){
        gettop = stack[top--];
        printf("%d->",GL->adjList[gettop].data);
        count++;
        for(e=GL->adjList[gettop].firstedge;e;e=e->next){
            k = e->adjvex;
            if(!(--GL->adjList[k].in)){
                stack[++top] =k;
            }
        }
    }
    if(count<GL->numVertexes)
        return ERROR;
    else
        return OK;
}

int *etv,*ltv;
int *stack2;
int top2;

//拓扑排序，用于关键路径计算
Status TopologicalSort(GraphAdjList GL){
    EdgeNode *e;
    int i,k,gettop;
    int top=0;
    int count=0;
    int *stack;

    stack = (int *)mallock(GL->numVertexes*sizeof(int));
    for(i=0;i<GL->numVertexes;i++){
        if(0==GL->adjList[i].in){
            stack[++top]=i;
        }
        top2=0;
        etv=(int *)mallock(GL->numVertexes*sizeof(int));
        for(i = 0;i<GL->numVertexes;i++){
            etv[i] = 0;
        }
        stack2 = (int *)mallock(GL->numVertexes*sizeof(int));
        while(top !=0){
            gettop = stack[top--];
            count++;
            stack2[++top2] = gettop;
            for(e=GL->adjList[gettop].firstedge;e;e=e->next){
                k = e->adjvex;
                if(!(--GL->adjList[k].in)){
                    stack[++top] = k;
                }
                if(etv[gettop]+e->weight>etv[k]){
                    etv[k] = etv[gettop]+e->weight;
                }
            }
        }
        if(count<GL->numVertexes){
            return ERROR;
        }else{
            return OK;
        }
    }
}