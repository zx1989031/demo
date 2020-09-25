#include <stdio.h>

typedef char VertextType; //顶点 
typedef int Edgetype; //边集数组
#define MAXVEX 9
#define INFINITY 65535



typedef struct
{
    VertextType Vers[MAXVEX];
    Edgetype arc[MAXVEX][MAXVEX];
}MGraph;


int main(MGraph *G) {
    printf("hello world!\n\n");
    int a[9][9] = {
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
    
    int i,j;
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            G->arc[i][j] = a[i][j];   
        }
    }

    printf("%d",G->arc[0][0]);
}