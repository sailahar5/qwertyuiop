#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include <string.h> 
#define PORT 8080 


#include<stdlib.h>

void matrix(int n,int **a)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            a[i][j]=rand()%2;
        }   
    }
    printf("Therefore the matrix is:\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d",a[i][j]);
        }   
        printf("\n");
    }
}

void partity_check(int**a,int *row,int* col,int n)
{
    int i,j;
    row[0]=0;
    col[0]=0;

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            row[i]=row[i]^a[i][j];   
            col[j]=col[j]^a[i][j];   

        }
    }
    printf("row:\n");
    for(i=0;i<n;i++)
    {
        printf("%d",col[i]);
    }
    printf("\n");
    
}
void induction(int x , int y,int**a,int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(i==x && j==y)
            {
                if(a[i][j]==0)
                {
                    a[i][j]=1;
                }
                else
                {
                    a[i][j]=0;
                }
                
            }
        }   
    }
    printf("the error inductiond matrix looks like :\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            printf("%d ",a[i][j]);
        }   
        printf("\n");
    }
    
}
void code_clearence(int**a,int*col,int*row,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        free(a[i]);
    }
    free(a);
}

int main(int argc, char const *argv[]) 
{ 
	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	char *hello = "Hello from client"; 

	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error: \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	

	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed.\n"); 
		return -1; 
	} 
    

    int n,i,j,x,y;
    printf("enter size of matrix: n\n");
    scanf("%d",&n);
    printf("%d\n",n);
    int **a = (int**)malloc(sizeof(int)*n*n);
    for(i=0;i<n;i++)
    {
        int* b=(int *)malloc(sizeof(int)*n);
        a[i]=b;
    }
    
    matrix(n,a);
    printf("enter x-coord to induction error at :\n");
    scanf("%d",&x);
    printf("enter y-coord to induction error at :\n");
    scanf("%d",&y);

    int *col=(int*)malloc(n*sizeof(int));
    int *row=(int*)malloc(n*sizeof(int));

    int* arr=(int*)malloc((n*n+2*n+1)*sizeof(int));

    partity_check(a,row,col,n);
    induction(x,y,a,n);

    int count=0;
    arr[count]=n;
    count++;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            {
            arr[count]=a[i][j];
            count++;
            }   
    }
    i=0;
    while(i<n)
    {
        arr[count]=row[i];
        count++;
        i++;
    }
    i=0;
    while(i<n)
    {
        arr[count]=col[i];
        count++;
        i++;
    }
    for(j=0;j<(count);j++)
        {
            printf("%d ",arr[j]);

        }   

    send(sock,arr,count*sizeof(arr),0);
 
	valread = read( sock , buffer, 1024); 
	printf("%s\n",buffer ); 
	return 0; 

    code_clearence(a,col,row,n);
} 