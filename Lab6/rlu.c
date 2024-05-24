#include<stdio.h>
void printArray(int arr[10][100],int cols,int rows,int rs[25]){
	printf("\n");
	
	int c,r;
	//for(c=0;c<cols;++c) printf("%d\t",rs[c]);
	printf("\n");
	//first print the table value
	for(r=0;r<rows;++r){
		for(c=0;c<cols;++c){
			if(arr[r][c]!=-1) printf("%d\t",arr[r][c]);
			else printf(" \t");
		}
		printf("\n");
	}
	//print "*" in final rows
	for(c=0;c<cols;++c)
		if(arr[rows][c]==0) printf("*\t");
		else printf(" \t");
	printf("\n");
}
void main()
{
    int i,j,k,min,rs[25],m[10],count[10],flag[25],n,f,pf=0,next=0;
    printf("Enter the length of the reference string --");
    scanf("%d",&n);
    printf("Enter the reference string -- ");
    for(i=0;i<n;i++)
    {
        scanf("%d",&rs[i]);
        flag[i]=0;
    }
    printf("Enter the number of frames -- ");
    scanf("%d",&f);
    
    for(i=0;i<f+1;i++)// the last rows of m is equal to -1;
    {
        count[i]=0;
        m[i]=-1;
    }
    
printf("\nThe Page Replacement process is -- \n");
int final_array[10][100];
int iarray = 0;

for(i=0;i<n;i++)//traverse through all the page ref
{
    for(j=0;j<f;j++)//traver vertical
    {
        if(m[j]==rs[i])//if exists(re[i] in previous rows)
        {
            flag[i]=1;//check flag[i]
            count[j]=next;//count at position j vertically
            next++;
            m[f]=-1;
            break;
        }
    }
    if(flag[i]==0)//if not exists(re[i] in previouse rows)
    {
    	m[f]=0;//if page fault then the last row check 0;
        if(i<f)//in case element is within the first frame size 
        {
            m[i]=rs[i]; //change m[i]
            count[i]=next;//count is to track the farest element
            next++;
        }
        else
        {
            min=0;
            for(j=0;j<f;j++)//traverse vertically
            	if(count[min] > count[j]) min=j;//find the least refrequently used element
            m[min]=rs[i];//change m to rs[i] at position in which the value is least recently used
            count[min]=next;
            next++;
        }
        pf++;
    }
    for(j=0;j<f+1;j++) final_array[j][iarray]=m[j];
   ++iarray;
   
}
printArray(final_array,n,f,rs);
printf("\nThe number of page faults using LRU are %d",pf);

}