/* ######################################
# University of Information Technology #
# IT007 Operating System               #
# <Nguyen Vo Tien Loc>, <22520792>     #
# File: sjf.c			       #
######################################*/
#include<stdio.h>

void main(){
	int pn[10];
	//thêm mảng index để quản lí thứ tự các process
	int arr[10], bur[10], star[10], finish[10], tat[10], wt[10], index[10], i, n;
	int totwt=0, tottat=0;
	
	//Nhập số lượngng process
	printf("Enter the number of processes:");
	scanf("%d",&n);
	
	/*
	Nhập các thông tin của các process bao processgồm:
	+ Tên process thứ i lưu ở pn[i]
	+ Arrival time của process thứ i lưu ở arr[i]
	+ Burst Time của process thứ i lưu ở bur[i]
	*/
	for(i=0;i<n;i++) {
		printf("Enter the Process Name, Arrival Time & Burst Time:");
		scanf("%d%d%d",&pn[i],&arr[i],&bur[i]);
		index[i] = i;
	}
	
	//sắp xếp lại các tiến trình theo thứ tự Arrival time tăng dần (chỉ sắp xếp mảng index)
	for (i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
			if ((arr[index[i]] > arr[index[j]])||(arr[index[i]] == arr[index[j]] && bur[index[i]] > bur[index[j]]))
			{
				int temp = index[i];
				index[i] = index[j];
				index[j] = temp;
			}
	
	/*
	 tính toán thời gian process bắt đầu được thực thi (start),
	 thời gian chờ của process (wait), thời gian hoàn thành của
	 process (finish) và thời gian quay vòng (tat)
	*/
	for(i=0;i<n;i++) {
		int ind = index[i];
		if(i==0) {
			star[index[i]]=arr[index[i]]; //nếu là tiến trình đến đầu tiên thì start = arr
			wt[index[i]]=star[index[i]]-arr[index[i]];
			finish[index[i]]=star[index[i]]+bur[index[i]];
			tat[index[i]]=finish[index[i]]-arr[index[i]];
		} else{
			/*
			Vòng lặp for dưới đây chọn ra process có burst time nhỏ nhất để thực thi kế tiếp trong số các process
			vào hàng đợi ready trong lúc process trước đang thực thi (arr[index[k]] <= finish[index[i-1]])
			
			Tên của process được thực thi kế tiếp sẽ được gán vào index[i]
			*/
			for (int k=i; k<n;k++)
				if (arr[index[k]] <= finish[index[i-1]] && bur[index[k]] < bur[index[i]])
				{
					int temp = index[k];
					index[k] = index[i];
					index[i] = temp;
				}
			/*
			 kể từ tiến trình đến thứ 2 trở đi thì start[index[i]] = max(arr[index[i]], finish[index[i-1]])
			*/ 
			if (arr[index[i]] > finish[index[i-1]])
				star[index[i]]=arr[index[i]];
			else star[index[i]]=finish[index[i-1]];
			
			wt[index[i]]=star[index[i]]-arr[index[i]];
			finish[index[i]]=star[index[i]]+bur[index[i]];
			tat[index[i]]=finish[index[i]]-arr[index[i]];
		}
	}
	printf("\nPName\tArrtime\tBurtime\tResponse\tWaiting\tTAT\tFinish");
	for(i=0;i<n;i++) {
		printf("\n%d\t%d\t%d\t%d\t\t%d\t%d\t%d",pn[i],arr[i],bur[i],star[i] - arr[i],wt[i],tat[i],finish[i]);
		totwt+=wt[i];
		tottat+=tat[i];
	}
	printf("\nAverage waiting time = %f", (totwt*1.0/n));
	printf("\nAverage turnaround time = %f", (tottat*1.0/n));
	printf("\n");
}