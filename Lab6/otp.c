#include<stdio.h> 

int i, j, k, f, pf=0, count=0, rs[25], m[10], n; 
int min,k,next=0,count_fre[10],flag[25];
int future[100];
int iarray = 0;

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

int helperSearch(int arr[],int start,int end,int*update_element,int e_compare){
    int flag = 0;
	int ii;
    for(ii=start;ii<end;++ii){
		if(arr[ii]==e_compare){
			*update_element = ii;
			flag=1;
			break;
		}
	}
	if(flag==0) *update_element=1000000;
}
void main(){
    int final_array[10][100];
	 //length enter
	 printf("\n Enter the length of reference string -- "); 
	 scanf("%d",&n); printf("\n Enter the reference string -- "); 
	 
	 //specified value enter
	 for(i=0;i<n;i++){
	 	scanf("%d",&rs[i]); 
	 	flag[i]=0;
	 }
	 printf("\n Enter no. of frames -- "); 
	 scanf("%d",&f); 
	 
	 
	 for(i=0;i<f+1;i++){
	 	count_fre[i]=0;
	 	m[i]=-1;//assign -1 for all number in m
		future[i]=-1;
	 } 
	 
	 for(i=0;i<n;++i){// traverse horizontally
	 	for(j=0;j<f;++j){//traverse vertically
	 		if(m[j]==rs[i]){//if exist in last col then only update the future position
	 			flag[i]=1;m[f]=-1;
                helperSearch(rs,i+1,n,&future[j],m[j]);
	 		}
	 	}
	 	if(flag[i]==0){//if not exist
	 	    m[f]=0;
	 		if(i<f){
				m[i] = rs[i];
				helperSearch(rs,i+1,n,&future[i],rs[i]);
	 		}else{
	 			//choose one to replace
	 			min = 0;
                int e;
	 			for(e=1;e<f;++e) 
                    if(future[min]<future[e]) min=e;//find index with farest used
	 			m[min]=rs[i];//replace
	 			//update future
				helperSearch(rs,i+1,n,&future[min],m[min]);
            }
	 		 pf++;
	 	}
	 	for(j=0;j<f+1;j++) final_array[j][iarray]=m[j];//update final array			
   		++iarray;
	 }
	 
	 printArray(final_array,n,f,rs);
	 
	 
	 
}