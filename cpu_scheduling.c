//Name: Caden-Gamer14 
//Date: 3/03/2025 
//File: process_program.c

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

//Creates a struct for the necessary int variables 
typedef struct {

    int process_id; 

    int arrival_time; 

    int burst_time; 

    int remaining_time; 

    int waiting_time; 

    int turnaround_time; 

    int is_completed; 

} Process; 

//Creates the variable n of type int to store the number of processes 
int n; 

//Creates the findNextProcess method of type int to find the process index with the shortest time remaining 
int findNextProcess(Process proc[], int current_time) {

    int min_time = INT_MAX; 
    
    int index = -1; 

    //Creates a for loop to go through the arrival time and current time to complete the different processes 
    for (int i = 0; i < n; i++) {

        if (proc[i].arrival_time <= current_time && !proc[i].is_completed && proc[i].remaining_time < min_time) {

            min_time = proc[i].remaining_time; 
            
            //Assigns index to i 
            index = i; 

        }
    }

    //Returns the index value 
    return index; 

}

//Creates the sjf method of type void taking in a Process 
void sjf(Process proc[]) {

    int current_time = 0; 

    int completed = 0; 

    //Creates a while loop to iterate through the completed aspects 
    while (completed != n) {

        //Assigns index to the process currently running 
        int index = findNextProcess(proc, current_time); 

        //Creates an if statement to see how many processes are remaining 
        if (index != -1) {

            proc[index].remaining_time--; 

            //Increments the current time 
            current_time++; 

            //Creates a second if statement to see how much time is left, continuing calculations 
            if (proc[index].remaining_time == 0) {

                //Sees the amount of completed processes 
                proc[index].is_completed = 1; 

                //Increments he completed variable 
                completed++; 

                //Assigns the index process with the turnaround time to the calculations of current time, subtracting the arrival time 
                proc[index].turnaround_time = current_time - proc[index].arrival_time; 

                //Assigns the index process with the waiting time to the calculations of turnaround time, subtracting the burst time  
                proc[index].waiting_time = proc[index].turnaround_time - proc[index].burst_time; 

            }
        
        //Creates an else statement to increment the current time 
        } else {

            current_time++; 

        }
    }
}

//Creates the calculateWaitingTimeAndExecutionOrder method of type void, taking in a Process 
void calculateWaitingTimeAndExecutionOrder(Process proc[], int quantum) {

    //Creates the necessary variables 
    int doneVar;

    int current_time = 0; 

    int i; 

    //The executionVar variable is used for how many times the executions run 
    int executionVar[1000];

    int indexVar = 0; 

    //Creates a do while clause 
    do {

        doneVar = 1; 

        //Creates a for loop to go through the processes to see if any are pending 
        for (i = 0; i < n; i++) {

            if (proc[i].remaining_time > 0) {

                doneVar = 0;
                
                //Creates an if statement to continue after the pending process 
                if (proc[i].remaining_time > quantum) {

                    current_time += quantum; 

                    proc[i].remaining_time -= quantum; 

                //Creates an else statement to further the processes in order to complete them 
                } else {

                    //Calculates through the remaining time 
                    current_time += proc[i].remaining_time; 

                    //Uses the waiting time to perform calculations of current time subtracting the arrival and burst times 
                    proc[i].waiting_time = current_time - proc[i].arrival_time - proc[i].burst_time; 

                    //Uses the turnaround time to perform calculations of current time subtracting the arrival time 
                    proc[i].turnaround_time = current_time - proc[i].arrival_time; 

                    //Finishes the execution of the processes 
                    executionVar[indexVar++] = proc[i].process_id; 

                    //Finishes completing the processes 
                    proc[i].remaining_time = 0;

                }
            }
        }
    } while (!doneVar); 

    //Printf statement for the execution order 
    printf("Execution Order: "); 

    for (int j = 0; j < indexVar; j++) {

        printf("%d ", executionVar[j]); 

    } 

    printf("\n"); 

}

//Creates the roundRobin method of type void, taking in a Process and an int 
void roundRobin(Process proc[], int quantum) {

    //Creates a for loop to establish the times for each aspect of the process 
    for (int i = 0; i < n; i++) {

        //Establishes the remaining time 
        proc[i].remaining_time = proc[i].burst_time; 

        //Establishes the waiting time 
        proc[i].waiting_time = 0;

        //Establishes the turnaround time 
        proc[i].turnaround_time = 0; 

        //Establishes if the processes are done 
        proc[i].is_completed = 0;

    } 

    //Uses the calculateWaitingTimeAndExecutionOrder method 
    calculateWaitingTimeAndExecutionOrder(proc, quantum); 

} 

//Creates the printProcesses method of type void and takes in a Process 
void printProcesses(Process proc[]) {

    //Uses a printf method to print out each process 
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n"); 

    for (int i = 0; i < n; i++) {

        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].process_id, proc[i].arrival_time, proc[i].burst_time, proc[i].waiting_time, proc[i].turnaround_time); 

    }
} 

int main() {

    //Creates the size of the first process 
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}}; 

    //Performs necessary calculations 
    n = sizeof(proc) / sizeof(proc[0]); 

    //Printf statement for organization 
    printf("SJF Algorithm:\n"); 

    //Creates a for loop to establish the times for the remaining time and sees if the processes are done 
    for (int i = 0; i < n; i++) {

        proc[i].remaining_time = proc[i].burst_time; 

        proc[i].is_completed = 0; 

    }

    //Uses the sjf method 
    sjf(proc); 

    //Uses the printProcesses method 
    printProcesses(proc); 

    //Creates the size of the round robin process 
    Process proc_rr[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}}; 

    //Performs necessary calculations for the number of processes 
    n = sizeof(proc_rr) / sizeof(proc_rr[0]);

    //Creates the variable quantum of type int for the time quantum of the round robin scheduling 
    int quantum = 4;

    printf("\nRR Algorithm:\n"); 

    //Uses the roundRobin method 
    roundRobin(proc_rr, quantum); 

    //Uses the printProcesses method 
    printProcesses(proc_rr); 

    return 0; 

}