

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int remaining_time;
};

void printGanttChart(const vector<int>& timeline) {
    cout << "\nGantt Chart:\n|";
    int prev = -1;
    for (int id : timeline) {
        if (id != prev) {
            cout << " P" << id << " |";
            prev = id;
        }
    }
    cout << "\n";
}

void printTable(const vector<Process>& processes) {
    int total_waiting = 0, total_turnaround = 0;
    cout << "\nID    Arrival  Burst    Completion  Waiting   Turnaround\n";
    for (const auto& p : processes) {
        cout << p.id << "\t" << p.arrival_time << "\t" << p.burst_time << "\t"
             << p.completion_time << "\t\t" << p.waiting_time << "\t" << p.turnaround_time << "\n";
        total_waiting += p.waiting_time;
        total_turnaround += p.turnaround_time;
    }
    cout << "\nAverage Waiting Time: " << (float)total_waiting / processes.size() << "\n";
    cout << "Average Turnaround Time: " << (float)total_turnaround / processes.size() << "\n";
}

void FCFS(vector<Process>& processes) {
    int time = 0;
    vector<int> timeline;

    for (auto& p : processes) {
        if (time < p.arrival_time)
            time = p.arrival_time;
        timeline.push_back(p.id);
        p.completion_time = time + p.burst_time;
        p.turnaround_time = p.completion_time - p.arrival_time;
        p.waiting_time = p.turnaround_time - p.burst_time;
        time = p.completion_time;
    }

    cout << "\nFCFS Scheduling:\n";
    printTable(processes);
    printGanttChart(timeline);
}

void SJF(vector<Process>& processes, bool preemptive) {
    int time = 0, completed = 0;
    vector<int> timeline;
    for (auto& p : processes) p.remaining_time = p.burst_time; //for preemptive

    while (completed != processes.size()) {
        int min_burst = INT_MAX, shortest = -1;
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 &&
                processes[i].remaining_time < min_burst) { //Among all arrived and not-yet-finished processes, pick the one with the smallest remaining time
                min_burst = processes[i].remaining_time;
                shortest = i;
            }
        }
        if (shortest == -1) {//no process, ideal
            time++;
            continue;
        }

        if (timeline.empty() || timeline.back() != processes[shortest].id)
            timeline.push_back(processes[shortest].id);

        if (preemptive) {
            processes[shortest].remaining_time--;
            time++;
            if (processes[shortest].remaining_time == 0) {
                processes[shortest].completion_time = time;
                processes[shortest].turnaround_time = time - processes[shortest].arrival_time;
                processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
                completed++;
            }
        } else {
            time += processes[shortest].remaining_time;
            processes[shortest].remaining_time = 0;
            processes[shortest].completion_time = time;
            processes[shortest].turnaround_time = time - processes[shortest].arrival_time;
            processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
            completed++;
        }
    }

    cout << "\nSJF Scheduling (" << (preemptive ? "Preemptive" : "Non-Preemptive") << "):\n";
    printTable(processes);
    printGanttChart(timeline);
}

void RoundRobin(vector<Process>& processes, int quantum) {
    int time = 0, remaining = processes.size(), i = 0;
    vector<int> timeline;
    for (auto& p : processes) p.remaining_time = p.burst_time;

    while (remaining > 0) {// until all processes gets completed
        if (processes[i].arrival_time <= time && processes[i].remaining_time > 0) { //if process is ready
            if (timeline.empty() || timeline.back() != processes[i].id)
                timeline.push_back(processes[i].id);

            int exec = min(quantum, processes[i].remaining_time);// choose min between quanta and burst time
            processes[i].remaining_time -= exec;
            time += exec;

            if (processes[i].remaining_time == 0) { //do changes if process is completed
                remaining--;
                processes[i].completion_time = time;
                processes[i].turnaround_time = time - processes[i].arrival_time;
                processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
            }
        }
        i = (i + 1) % processes.size(); //moving Circularly in process sequence
    }

    cout << "\nRound Robin Scheduling (Quantum = " << quantum << "):\n";
    printTable(processes);
    printGanttChart(timeline);
}

void PriorityScheduling(vector<Process>& processes, bool preemptive) {
    int time = 0, completed = 0;
    vector<int> timeline;
    for (auto& p : processes) p.remaining_time = p.burst_time;

    while (completed != processes.size()) {
        int min_priority = INT_MAX, highest_priority = -1;
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].arrival_time <= time && processes[i].remaining_time > 0 &&
                processes[i].priority < min_priority) {
                min_priority = processes[i].priority;
                highest_priority = i;
            }
        }

        if (highest_priority == -1) {
            time++;
            continue;
        }

        if (timeline.empty() || timeline.back() != processes[highest_priority].id)
            timeline.push_back(processes[highest_priority].id);

        if (preemptive) {
            processes[highest_priority].remaining_time--;
            time++;
            if (processes[highest_priority].remaining_time == 0) {
                processes[highest_priority].completion_time = time;
                processes[highest_priority].turnaround_time = time - processes[highest_priority].arrival_time;
                processes[highest_priority].waiting_time = processes[highest_priority].turnaround_time - processes[highest_priority].burst_time;
                completed++;
            }
        } else {
            time += processes[highest_priority].remaining_time;
            processes[highest_priority].remaining_time = 0;
            processes[highest_priority].completion_time = time;
            processes[highest_priority].turnaround_time = time - processes[highest_priority].arrival_time;
            processes[highest_priority].waiting_time = processes[highest_priority].turnaround_time - processes[highest_priority].burst_time;
            completed++;
        }
    }

    cout << "\nPriority Scheduling (" << (preemptive ? "Preemptive" : "Non-Preemptive") << "):\n";
    printTable(processes);
    printGanttChart(timeline);
}

int main() {
    int n, choice, quantum;
    bool preemptive;

    while (true) {
        cout << "\nChoose Scheduling Algorithm:\n";
        cout << "1. FCFS\n2. SJF\n3. Round Robin\n4. Priority Scheduling\n5. Exit\n";
        cin >> choice;

        if (choice == 5) break;

        cout << "Enter number of processes: ";
        cin >> n;

        vector<Process> processes(n);
        for (int i = 0; i < n; i++) {
            cout << "\nEnter Process ID: ";
            cin >> processes[i].id;
            cout << "Enter Arrival Time: ";
            cin >> processes[i].arrival_time;
            cout << "Enter Burst Time: ";
            cin >> processes[i].burst_time;
            if (choice == 4) {
                cout << "Enter Priority: ";
                cin >> processes[i].priority;
            }
        }

        if (choice == 2 || choice == 4) {
            int mode;
            cout << "Choose Mode: 1. Preemptive  2. Non-Preemptive\n";
            cin >> mode;
            preemptive = (mode == 1);
        }

        if (choice == 3) {
            cout << "Enter Time Quantum: ";
            cin >> quantum;
        }

        switch (choice) {
            case 1: FCFS(processes); break;
            case 2: SJF(processes, preemptive); break;
            case 3: RoundRobin(processes, quantum); break;
            case 4: PriorityScheduling(processes, preemptive); break;
            default: cout << "Invalid choice!\n";
        }
    }

    return 0;
}
