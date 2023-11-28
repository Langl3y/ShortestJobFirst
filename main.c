#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

// Process structure to store process information
typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int finish_time;
    int waiting_time;
    int turnaround_time;
} Process;

// Function to print process information
void print_process(Process process) {
    printf("PID: %d\tArrival Time: %d\tBurst Time: %d\tStart Time: %d\tFinish Time: %d\tWaiting Time: %d\tTurnaround Time: %d\n",
           process.pid, process.arrival_time, process.burst_time, process.start_time, process.finish_time, process.waiting_time, process.turnaround_time);
}

// Function to sort processes by arrival time
void sort_by_arrival(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// Function to calculate average waiting time
float calculate_average_waiting_time(Process processes[], int n) {
    int total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
    }
    return (float)total_waiting_time / n;
}

// Function to calculate average turnaround time
float calculate_average_turnaround_time(Process processes[], int n) {
    int total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_turnaround_time += processes[i].turnaround_time;
    }
    return (float)total_turnaround_time / n;
}

// Function to simulate SJF scheduling algorithm
void sjf_scheduling(Process processes[], int n) {
    sort_by_arrival(processes, n);

    int current_time = 0;
    int terminated_processes = 0;

    while (terminated_processes < n) {
        int shortest_job = -1;
        int shortest_burst_time = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].burst_time < shortest_burst_time && processes[i].finish_time == 0) {
                shortest_job = i;
                shortest_burst_time = processes[i].burst_time;
            }
        }

        if (shortest_job != -1) {
            Process* current_process = &processes[shortest_job];
            current_process->start_time = current_time;
            current_process->finish_time = current_time + current_process->burst_time;
            current_process->waiting_time = current_process->start_time - current_process->arrival_time;
            current_process->turnaround_time = current_process->finish_time - current_process->arrival_time;
            terminated_processes++;
            current_time = current_process->finish_time;
        } else {
            current_time++;
        }
    }
}

// Function to generate random processes with arrival time and burst time
void generate_processes(Process processes[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        processes[i].arrival_time = rand() % 21;
        processes[i].burst_time = rand() % 11 + 2;
        processes[i].start_time = 0;
        processes[i].finish_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }
}

// Test the SJF scheduling algorithm
void test_sjf_scheduling(int num_processes) {
    Process processes[num_processes];
    generate_processes(processes, num_processes);

    printf("Processes:\n");
    for (int i = 0; i < num_processes; i++) {
        print_process(processes[i]);
    }
    printf("\n");

    sjf_scheduling(processes, num_processes);

    printf("SJF Scheduling:\n");
    for (int i = 0; i < num_processes; i++) {
        print_process(processes[i]);
    }
    printf("\n");

    float average_waiting_time = calculate_average_waiting_time(processes, num_processes);
    float average_turnaround_time = calculate_average_turnaround_time(processes, num_processes);

    printf("Average Waiting Time: %.2f\n", average_waiting_time);
    printf("Average Turnaround Time: %.2f\n", average_turnaround_time);
    printf("\n");
}

int main() {
    printf("Test Case 1:\n");
    test_sjf_scheduling(5);

    printf("Test Case 2:\n");
    test_sjf_scheduling(5);

    printf("Test Case 3:\n");
    test_sjf_scheduling(5);

    return 0;
}