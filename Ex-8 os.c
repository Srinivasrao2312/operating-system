#include <stdio.h>

#define MAX_PROCESS 10

struct Process {
    int process_id;
    int burst_time;
    int remaining_time;
};

void roundRobin(struct Process processes[], int n, int time_quantum) {
    int total_time = 0;
    int remaining_processes = n;

    printf("\nRound Robin Schedule:\n");
    printf("Time  | Process\n");
    printf("--------------\n");

    while (remaining_processes > 0) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                int execute_time = (processes[i].remaining_time < time_quantum) ? processes[i].remaining_time : time_quantum;

                printf("%-5d | P%d\n", total_time, processes[i].process_id);

                processes[i].remaining_time -= execute_time;
                total_time += execute_time;

                if (processes[i].remaining_time == 0) {
                    remaining_processes--;
                }
            }
        }
    }
}

void calculateTurnaroundTime(struct Process processes[], int n, int turnaround_time[]) {
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = processes[i].burst_time;
    }
}

void calculateWaitingTime(struct Process processes[], int n, int turnaround_time[], int waiting_time[]) {
    int total_waiting_time = 0;

    for (int i = 0; i < n; i++) {
        waiting_time[i] = turnaround_time[i] - processes[i].burst_time;
        total_waiting_time += waiting_time[i];
    }

    float average_waiting_time = (float)total_waiting_time / n;
    printf("\nAverage Waiting Time: %.2f\n", average_waiting_time);
}

int main() {
    int n, time_quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX_PROCESS) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    struct Process processes[MAX_PROCESS];

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;

        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    int turnaround_time[MAX_PROCESS];
    roundRobin(processes, n, time_quantum);
    calculateTurnaroundTime(processes, n, turnaround_time);
    calculateWaitingTime(processes, n, turnaround_time, processes);

    return 0;
}
