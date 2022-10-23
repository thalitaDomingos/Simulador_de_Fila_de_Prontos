#include <stdio.h>
#include <conio.h>
#include <stdlib.h>


struct process_struct
{
	int pid;
	int at;       // Arrival Time
	int bt;       // CPU Burst time
	int ct, wt, tat, rt, start_time; // Completion, waiting, turnaround, response time
} ps[100];        // Array of structure to store the info of each process.


int findmax(int a, int b)
{
	return a > b ? a : b;
}


void FCFS(void)
{
	int n;
	printf("\nFCFS!!!\n");
	printf("\nTotal number of process in the system: ");
	scanf("%d", &n);
	float sum_wt = 0;

	printf("\n");
	for(int i = 0; i < n; i++)
	{
		printf("Enter Process %d Arrival Time: ", i);
		scanf("%d", &ps[i].at);
		ps[i].pid = i ;
	}

	printf("\n");
	for(int i = 0; i < n; i++)
	{
		printf("Enter Process %d Burst Time: ", i);
		scanf("%d", &ps[i].bt);
	}


	// Calculations
	for(int i = 0; i < n; i++)
	{
		ps[i].start_time = (i == 0) ? ps[i].at : findmax(ps[i].at, ps[i - 1].ct);
		ps[i].ct =  ps[i].start_time + ps[i].bt;
		ps[i].tat = ps[i].ct - ps[i].at;
		ps[i].wt = ps[i].tat - ps[i].bt;
		sum_wt += ps[i].wt;
	}


	// Output
	printf("\nProcess No.\tBurst Time\tWaiting Time\n");

	for(int i = 0; i < n; i++)
		printf("%d\t\t%d\t\t%d\n", ps[i].pid, ps[i].bt, ps[i].wt);

	printf("\nAverage Turn Around Time: %f ", sum_wt / n);
	printf("\n");
}


void roundRobin(void)
{

	// Initlialize the variable name
	int i, NOP, sum = 0, count = 0, y, quant, wt = 0, at[10], bt[10], temp[10];
	float avg_wt;

	printf("\nROUND ROBIN!!!\n");
	printf("\nTotal number of process in the system: ");
	scanf("%d", &NOP);
	y = NOP; // Assign the number of process to variable y


	// Use for loop to enter the details of the process like Arrival time and the Burst Time
	for(i = 0; i < NOP; i++)
	{
		printf("\nProcess[%d]\n", i + 1);
		printf("Arrival time is: ");  // Accept arrival time
		scanf("%d", &at[i]);
		printf("Burst time is: ");    // Accept the Burst time
		scanf("%d", &bt[i]);
		temp[i] = bt[i];              // store the burst time in temp array
	}


	// Accept the Time qunat
	printf("\nEnter the Time Quantum for the process: ");
	scanf("%d", &quant);

	// Display the process No, burst time, Turn Around Time and the waiting time
	printf("\n Process No \t     Burst Time \t    Waiting Time ");


	for(sum = 0, i = 0; y != 0; )
	{
		if(temp[i] <= quant && temp[i] > 0) // define the conditions
		{
			sum = sum + temp[i];
			temp[i] = 0;
			count = 1;
		}

		else if(temp[i] > 0)
		{
			temp[i] = temp[i] - quant;
			sum = sum + quant;
		}

		if(temp[i] == 0 && count == 1)
		{
			y--; // decrement the process no.
			printf("\nProcess No[%d] \t\t %d\t\t\t %d", i + 1, bt[i], sum - at[i] - bt[i]);
			wt = wt + sum - at[i] - bt[i];
			count = 0;
		}

		if (i == NOP - 1)
			i = 0;

		else if (at[i + 1] <= sum)
			i++;

		else
			i = 0;
	}


	// represents the average waiting time and Turn Around time
	avg_wt = wt * 1.0 / NOP;
	printf("\n\nAverage Turn Around Time: %f", avg_wt);
	printf("\n");
	getch();
}


int main()
{
	int numProcess;

	printf("Enter 1 - Round Robin");
	printf("\nEnter 2 - FCFS\n\n");

	do
	{
		printf("Selection: ");
		scanf("%d", &numProcess);
	}
	while (!(numProcess == 1 | numProcess == 2));

	if (numProcess == 1)
		roundRobin();
	else
		FCFS();
}
