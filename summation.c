#include <stdio.h>
void sum01(){
    int i,sum =0,n=100;

    for(i=1;i<=n;i++){
        sum = sum+i;
    }
    printf("%d",sum);  
}

void sum02(){
    int i,sum =0,n=100;
    sum = (1+n)*n/2;
    printf("%d",sum); 
}


void count(){
    int count = 1,n = 1000;
    while(count<n){
        count = count*2;
    }
}

int main(){
    int i,sum =0,n=100;
    for(i=1;i<=n;i++){
        sum = sum+i;
    }
    printf("%d",sum);  


    sum01();
    sum02();
}