#include<conio.h>
#include<stdio.h>
#define max 20

void main()
{
    int arr[max],i,y,n,k;
    
    printf("Enter size of array");
    scanf("%d",&n);

    printf("Enter values of array:");

    for(i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    printf("Sorting");

    for(k=1; k<=n;k++)
    {

        y=arr[k];

        for(i=k-1; i>=0 && y<x[i];i--)
        {
            x[i+1]=x[i];
            x[i]=y;
        }
    }

    printf("Ans");

    for(i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }

    
}


