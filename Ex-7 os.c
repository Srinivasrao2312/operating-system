#include <stdio.h>

struct Process {
    int process_id;
    int burst_time;
};

void swap(struct Process *xp, struct Process *yp) {
    struct Process temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sortProcesses(struct Process processes[], int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (processes[j].burst_time > processes[j+1].burst_time)
                swap(&processes[j], &processes[j+1]);
}

void findWaitingTime(struct Process processes[], int n, int waiting_time[]) {
    waiting_time[0] = 0;
    for (int i = 1; i < n ; i++)
        waiting_time[i] = processes[i-1].burst_time + waiting_time[i-1];
}

void findTurnAroundTime(struct Process processes[], int n, int waiting_time[], int turn_around_time[]) {
    for (int i = 0; i < n; i++)
        turn_around_time[i] = processes[i].burst_time + waiting_time[i];
}

void findAverageTime(struct Process processes[], int n) {
    int waiting_time[n], turn_around_time[n];
    
    findWaitingTime(processes, n, waiting_time);
    findTurnAroundTime(processes, n, waiting_time, turn_around_time);
    
    float total_waiting_time = 0, total_turn_around_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turn_around_time += turn_around_time[i];
    }
    
    float average_waiting_time = total_waiting_time / n;
    float average_turn_around_time = total_turn_around_time / n;
    
    printf("Average Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turn_around_time);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
    }

    // Sort processes based on burst time
    sortProcesses(processes, n);

    printf("\nGantt Chart:\n");
    for (int i = 0; i < n; i++) {
        printf("| P%d ", processes[i].process_id);
    }
    printf("|\n");

    findAverageTime(processes, n);

    return 0;
}
