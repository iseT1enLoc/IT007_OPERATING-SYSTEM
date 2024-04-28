/*######################################
# University of Information Technology #
# IT007 Operating System               #
# <Nguyen Vo Tien Loc>, <22520792>     #
# File: srt.c			       #
######################################*/
#include<stdio.h>
#include<stdbool.h>

int pn[10];
//thêm mảng id để quản lí thứ tự các process
//thêm mảng remain để quản lí thời gian còn lại để hoàn thành công việc của các process
//thêm mảng run lưu thời điểm cuối cùng process được thực thi
int arr[10], bur[10], star[10], finish[10], tat[10], wt[10], id[10], remain[10], i, n, run[10];
int totwt=0, tottat=0, totrp=0;

//Kiểm tra tất cả các tiến trình đã hoàn thành hay chưa
bool chk_remain(){
	for (int i = 0; i<n; i++)
		if (remain[i]>0) return true;
	return false;
}

void main(){
	//Nhập số lượngng processS
	printf("Enter the number of processes:");
	scanf("%d",&n);
	
	/*
	Nhập các thông tin của các process bao gồm:
	+ Tên process thứ i lưu ở pn[i]
	+ Arrival time của process thứ i lưu ở arr[i]
	+ Burst Time của process thứ i lưu ở bur[i]
	*/
	for(i=0;i<n;i++) {
		printf("Enter the Process Name, Arrival Time & Burst Time:");
		scanf("%d%d%d",&pn[i],&arr[i],&bur[i]);
		remain[i] = bur[i];
		id[i] = i;
		star[i] = -1; finish[i] = 0; tat[i] = 0; wt[i] = 0;
		run[i] = arr[i];
	}
	
	//sắp xếp lại các tiến trình theo thứ tự Arrival time tăng dần (chỉ sắp xếp mảng id)
	for (i=0;i<n-1;i++)
		for(int j=i+1;j<n;j++)
			if ((arr[id[i]] > arr[id[j]])||(arr[id[i]] == arr[id[j]] && remain[id[i]] > remain[id[j]]))
			{
				int temp = id[i];
				id[i] = id[j];
				id[j] = temp;
			}
	
	star[id[0]]=arr[id[0]]; //nếu là tiến trình đến đầu tiên thì start = arr
	
	
	/*
	 vòng lặp while dưới đây thực hiện tính toán thời gian process bắt đầu được thực thi (star),
	 thời gian chờ của process (wait), thời gian hoàn thành của process (finish) và thời gian quay vòng (tat)
	*/
	while (chk_remain())
	{
		// tính start_time của một process: là thời điểm process được thực thi lần đầu tiên
		if (star[id[0]] == -1)
			star[id[0]] = run[id[0]];

		int min_gr = 0;
		int min_sm = 0;
		
		/*
		Lệnh if dưới đây xử lí trường hợp khi một process đang thực thi thì có một process
		khác có remain_time ngắn hơn vào hàng đợi ready, làm cho process đang thực thi phải tạm ngưng
		để nhường tài nguyên cho process có remain_time ngắn hơn
		*/
		if (remain[id[0]]>0)
		{
			//vòng lặp for sẽ tìm process được thực thi tiếp theo
			for (int i=1;i<n;i++)
			{
				if (remain[id[i]] > 0)
				{
					if (run[id[i]] < run[id[0]] + remain[id[0]] && run[id[i]] > run[id[0]] && 
					remain[id[i]] < remain[id[0]] - run[id[i]] + run[id[0]]){
						if (min_gr == 0)
							min_gr = i;
						else{
							if ((run[id[min_gr]] > run[id[i]])||(run[id[min_gr]] == run[id[i]] 
							&& remain[id[min_gr]] > remain[id[i]])) 
								min_gr = i;
						}
					}
				
				}
			}
			
			/*
			cập nhật lại remain_time cho process bị ngưng,
			biến run lúc này sẽ lưu thời điểm process bị tạm ngưng.
			*/
			remain[id[0]] = remain[id[0]] - run[id[min_gr]] + run[id[0]]; 
			run[id[0]] = run[id[min_gr]];
			int temp = id[min_gr];
			id[min_gr] = id[0];
			id[0] = temp;
		}
		
		/*
		Lệnh if dưới đây xử lí trường hợp process đã thực thi xong mà không bị ngắt giữa chừng.
		Sau khi thực thi xong thì tìm trong số các process đã ở trong hàng đợi xem process nào có remain_time ngắn nhất
		để cho thực thi tiếp theo
		*/
		if(min_gr == 0){
			//vòng lặp for sẽ tìm process tiếp theo được thực thi
			for (int i=1;i<n;i++)
			{
				if (remain[id[i]] > 0)
				{
					if (run[id[i]] <= run[id[0]] + remain[id[0]]){
						if (min_sm == 0)
							min_sm = i;
						else{
							if (remain[id[min_sm]] > remain[id[i]])
								min_sm = i;
						}
					}
			
				}
			}
			/*
			Vì process thực thi mà không bị ngắt giữa chừng nên nó đã hoàn thành công việc của mình,
			ta cập nhật lại biến remain = 0, biến finish = thời điểm process hoàn thành và biến tat = finish - arr.
			*/
			run[id[0]] += remain[id[0]];
			finish[id[0]] = run[id[0]];
			tat[id[0]] = finish[id[0]] - arr[id[0]];
			remain[id[0]] = 0;
			/*
			ta cũng phải cập nhật lại biến wt của process được thực thi tiếp theo và biến run của process được thực thi tiếp theo
			bằng thời gian process trước kết thúc (biến run lúc này lưu thòi điểm cuối cùng process được thực thi)
			*/
			wt[id[min_sm]] += (finish[id[0]] - run[id[min_sm]]);
			run[id[min_sm]] = finish[id[0]];
			int temp = id[min_sm];
			id[min_sm] = id[0];
			id[0] = temp;
		}
		
		/*
		Lệnh if dưới đây xử lí các trường hợp còn lại (process hoàn thành công việc mà không bị ngắt giữa chừng và trong 
		hàng đợi ready không có bất kì một process nào)
		*/
		if (min_gr == 0 && min_sm == 0)
		{
			int min_run = 0;
			//vòng lặp for sẽ tìm process tiếp theo được thực thi
			for (int i=1; i<n; i++)
				if(remain[id[i]]>0){
					if (min_run == 0) min_run = i;
					else if ((run[id[min_run]] > run[id[i]])||(run[id[min_run]] == run[id[i]] 
							&& remain[id[min_run]] > remain[id[i]])) min_run = i;
				}
			/*
			Vì process thực thi mà không bị ngắt giữa chừng nên nó đã hoàn thành công việc của mình,
			ta cập nhật lại biến remain = 0, biến finish = thời điểm process hoàn thành và biến tat = finish - arr.
			*/
			run[id[0]] += remain[id[0]];
			finish[id[0]] = run[id[0]];
			tat[id[0]] = finish[id[0]] - arr[id[0]];
			remain[id[0]] = 0;
			int temp = id[min_run];
			id[min_run] = id[0];
			id[0] = temp;
		}
	}
	
	
	printf("\nPName\tArrtime\tBurtime\tResponse\tWaiting\tTAT\tFinish");
	for(i=0;i<n;i++) {
		printf("\n%d\t%d\t%d\t%d\t\t%d\t%d\t%d",pn[i],arr[i],bur[i],star[i]-arr[i],wt[i],tat[i],finish[i]);
		totrp+=(star[i]-arr[i]);
		totwt+=wt[i];
		tottat+=tat[i];
	}
	printf("\nAverage response time = %f", (totrp*1.0/n));
	printf("\nAverage waiting time = %f", (totwt*1.0/n));
	printf("\nAverage turnaround time = %f", (tottat*1.0/n));
	printf("\n");
}