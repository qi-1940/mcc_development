#include<stdio.h>
int fun(int in)
{
    int result;
    result  = 0;
    int i1;
    i1 = 0;
    int i2;
    i2 = 1;
    if(in==0)
    {
        result=0;
        return result;
    }
    if(in==1)
    {
        result=1;
        return result;
    }
    while(in>1)
    {
        result = i1  + i2;
        i1 = i2;
        i2 = result;
        in = in-1;
    }
    return result;
}
int main(void)
{
    printf("%d",fun(7));
    return 0;
}