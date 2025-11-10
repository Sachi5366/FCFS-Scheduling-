/* FCFS Scheduling - simple, non-preemptive
   Input: number of processes, arrival times, burst times
   Output: waiting times, turnaround times, average WT and TAT
*/
#include <stdio.h>

int main() {
    int n, i;
    printf("Number of processes: ");
    scanf("%d", &n);

    int at[n], bt[n], ct[n], tat[n], wt[n];
    // at = arrival time, bt = burst time, ct = completion time
    for (i = 0; i < n; i++) {
        printf("P%d Arrival time: ", i+1);
        scanf("%d", &at[i]);
        printf("P%d Burst time: ", i+1);
        scanf("%d", &bt[i]);
    }

    // FCFS assumes processes sorted by arrival time.
    // We'll sort by arrival time (stable). Simple selection sort.
    for (i = 0; i < n-1; i++) {
        int min = i, j;
        for (j = i+1; j < n; j++)
            if (at[j] < at[min]) min = j;
        if (min != i) {
            // swap arrival
            int t = at[i]; at[i] = at[min]; at[min] = t;
            // swap burst
            t = bt[i]; bt[i] = bt[min]; bt[min] = t;
        }
    }

    int time = 0; // current time
    float total_wt = 0, total_tat = 0;
    for (i = 0; i < n; i++) {
        if (time < at[i]) time = at[i]; // CPU waits if no process arrived
        ct[i] = time + bt[i];
        tat[i] = ct[i] - at[i];         // turnaround = completion - arrival
        wt[i] = tat[i] - bt[i];         // waiting = turnaround - burst
        time = ct[i];                   // advance time
        total_wt += wt[i];
        total_tat += tat[i];
    }

    printf("\nP#\tAT\tBT\tCT\tTAT\tWT\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], ct[i], tat[i], wt[i]);

    printf("\nAverage TAT = %.2f\nAverage WT = %.2f\n", total_tat/n, total_wt/n);
    return 0;
}
