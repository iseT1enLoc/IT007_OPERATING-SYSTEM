#include<stdio.h> 
int i, j, k, f, pf=0, count=0, rs[25], m[10], n; 
int min,k,next=0,count_fre[10],flag[25];
int iarray = 0;
int future[100];
//function to print the final array;
void printArray(int arr[10][100],int cols,int rows,int rs[25],int page_fault){
	printf("\n");
	printf("\n---------------Page Replacement Algorithm---------------\n"); 
	int c,r;
	for(c=0;c<cols;++c) printf("%d\t",rs[c]);
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
	printf("Number Of Page Fault: %d\n",page_fault);
}
void FIFO(){
	 int final_array[10][100];
	 for(i=0;i<n;i++)//traverse each page request 
	 { 
		 for(k=0;k<f;k++) //at each page traverse vertical to check if the current in m array has rs[i] then break
		 { 
			 if(m[k]==rs[i]) 
			 break; 
		  } 
		 if(k==f) //in case k equal to F that mean there are page fault
		 { 
			 m[count++]=rs[i];
			 pf++; 
			 m[f]=0; 
		 } else m[f]=-1;
		 for(j=0;j<f+1;j++) final_array[j][iarray]=m[j];
		
		++iarray;
		
	 	 if(count==f) count=0;//reassign the position of the longest element in string
	 } 	
	 printArray(final_array,n,f,rs,pf);
}
void RLU(){
int final_array[10][100];
for(i=0;i<n;i++)//traverse through all the page ref
{
    for(j=0;j<f;j++)//traver vertical
    {
        if(m[j]==rs[i])//if exists(re[i] in previous rows)
        {
            flag[i]=1;//check flag[i]
            count_fre[j]=next;//count at position j vertically
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
            count_fre[i]=next;//count is to track the farest element
            next++;
        }
        else
        {
            min=0;
            for(j=0;j<f;j++)//traverse vertically
            	if(count_fre[min] > count_fre[j]) min=j;//find the least refrequently used element
            m[min]=rs[i];//change m to rs[i] at position in which the value is least recently used
            count_fre[min]=next;
            next++;
        }
        pf++;
    }
    for(j=0;j<f+1;j++) final_array[j][iarray]=m[j];
   ++iarray;
   
}
	printArray(final_array,n,f,rs,pf);
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
void OTP(){
	int final_array[10][100];
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
	 printArray(final_array,n,f,rs,pf);
}
void main() {
	 printf("-----------------Page Replacement ALgorithm---------------\n");
	 printf("1. Default referenced sequence\n");
	 printf("2. Manual input sequence\n");
	 printf("Your choice is (1,2): ");
	 int option;
	 scanf("%d",&option);
	 
	 switch(option){
	 	case 1:
	 		//specified value enter
	 		 n=11;
			 rs[0]=1;rs[1] =3;rs[2]= 5;rs[3] =2;rs[4] =0;
			 rs[5] =4;rs[6] =6;rs[7] = 2;rs[8] = 7;rs[9]=9;rs[10]=2;
			 for(i=0;i<n;++i) flag[i]=0;
			 break;
		case 2:
			//length enter
			 printf("\n Enter the length of reference string -- "); 
			 scanf("%d",&n); 
			 printf("\n Enter the reference string -- "); 
	 
			 //specified value enter
			 for(i=0;i<n;i++){
			 	scanf("%d",&rs[i]); 
			 	flag[i]=0;
			 }			 
	 }
	 printf("---------Page Replacement ALgorithm------------\n");
	 printf("\nInput pages frame:  ");
	  scanf("%d",&f); 
	 for(i=0;i<f+1;i++){
	 	count_fre[i]=0;
	 	m[i]=-1;//assign -1 for all number in m
	 } 
	 
	 
	 printf("\n1.FIFO Algorithm.\n2.OTP Algorithm.\n3.RLU Algorithm. \n");
	 int opt;
	 printf("\nYour choice: ");
	 scanf("%d",&opt);
	 switch(opt){
	 	case 1:
	 		FIFO();
	 		break;
	 	case 2:
	 		OTP();
	 		break;
	 	case 3:
	 		RLU();
	 		break;
	 }
	 
}
