#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define FILE_NAME "CPU_BURST.tobjt"

struct proc
{
	int at,bt,wt,tat;
	char name[4];
};

struct proc initialize(int at,int bt,int name)
{
	struct proc obj;
	obj.bt = bt;
	obj.at = at;
	sprintf(obj.name,"P%d",name+1);

	return obj;
}

int main()
{
	
	FILE *fp = fopen(FILE_NAME,"r");

	if(!fp)
		return -1*printf("FILE OPEN ERROR!\n");

    int d,i,j,count=0;

    int *queue = (int*)malloc(sizeof(int));

    while(EOF != fscanf(fp,"%d ",&d ))
    {
    	printf("%d ",d);
    	queue = (int*)realloc(queue,(count+1)*sizeof(int));
    	queue[count++] = d;
    }
    fclose(fp);
	struct proc P[count];

	for(i=0; i<count; i++)
		P[i] = initialize(0,queue[i],i);

	for(i=1; i<count; i++)
	{
		for(j=0; j<count-i; j++)
		{
			if(P[j].bt>P[j+1].bt)
			{
				struct proc temp = P[j];
				P[j] = P[j+1];
				P[j+1] = temp;
			}
		}
	}
	
	printf("\nOrder : ");

	int elapsed_time=0;
	for(i=0; i<count; i++)
	{
		P[i].wt = elapsed_time;
		P[i].tat= P[i].wt+P[i].bt;
		elapsed_time += P[i].bt;

		printf("%s ",P[i].name);
	}
	for(i=1; i<count; i++)
	{
		for(j=0; j<count-i; j++)
		{
			if(P[j].name[1]>P[j+1].name[1])
			{
				struct proc temp = P[j];
				P[j] = P[j+1];
				P[j+1] = temp;
			}
		}
	}
	printf("\n\n%7s|%8s|%6s|%5s|%s\n","proc","ARRIVAL","BURST","WAIT","TURNAROUND");
	
	int total_wt=0,total_tt=0;
	
	for(i=0; i<count; i++)
	{
		total_wt+=P[i].wt;
		total_tt+=P[i].tat;
		printf("%7s|%8d|%6d|%5d|%9d\n",P[i].name,P[i].at,P[i].bt,P[i].wt,P[i].tat);
	}
	
	printf("\nAverage Waiting Time     : %.2f\n",total_wt*1.0/count);
	printf("\nAverage Turn Around Time : %.2f\n",total_tt*1.0/count);
	
	return 0;
}
