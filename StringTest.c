#include <stdio.h>
#include <iostream>


//通过计算返回子串的next 数组
void get_next(String T,int *next)
{
    int i,j;
    i = 1;
    j=0;
    nexxt[1] = 0;
    while(i<T[0])
    {
        if(j==0 || T[i]==T[j])
        {
            ++i;
            ++j;
            next[i] = j;
        }else{
            j = next[t];
        }
    }
}

int Index_KMP(String S,String T, int pos)
{
    int i = pos;
    int j = 1;
    int next[255];
    get_next(T,next);
    while(i<=S[0] && j<=T[0])
    {
        if(j==0 || S[i] ==T[j])
        {
            ++i;
            ++j;
        } else{
            j = next(j);
        }
    }
    if(j>T[0])
        return i-T[0];
    else   
        return 0;
}



int main(){
    String a = "abcdef";
    String b = "abc";
}