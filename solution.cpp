#include<iostream>
#include<algorithm>
using namespace std;

struct node {
  char pname[50];
  int bt;
  int at;
  int wt;
  float priority = 0;
}
a[50];

// This function inserts the process name, arrival time, and burst time into the array.
void insert(int n) {
  int i;
  for (i = 0; i < n; i++) {
    cin >> a[i].pname;
    cin >> a[i].at;
    cin >> a[i].bt;
    a[i].priority = 0;
    a[i].wt = -a[i].at;
  }
}

// These functions sort the processes by burst time, arrival time, and priority.
bool btSort(node a, node b) {
  return a.bt < b.bt;
}

bool atSort(node a, node b) {
  return a.at < b.at;
}

bool prioritySort(node a, node b) {
  return a.priority > b.priority;
}

// This function displays the process scheduling results, including the matrix for process name, arrival time, burst time, completion time, turn around time, waiting time, and response time.
void disp(int n) {
  sort(a, a + n, btSort);
  sort(a, a + n, atSort);
  int ttime = 0, i;
  int j, tArray[n];
  for (i = 0; i < n; i++) {
    j = i;
    cout << "\n";
    while (a[j].at <= ttime && j != n) {
      j++;
    }

    cout << "Time " << ttime << ":" << "\n";

    for (int q = i; q < j; q++) {
      a[q].wt = ttime - a[q].at;
      a[q].priority = (float)(a[q].wt + a[q].bt) / (float) a[q].bt;
      cout << "  P" << q + 1 << ", " << "Priority = " << a[q].priority << "\n";
    }
    sort(a + i, a + j, prioritySort);
    tArray[i] = ttime;
    cout << endl;
    ttime += a[i].bt;

  }
  tArray[i] = ttime;

  float averageWaitingTime = 0;
  float averageResponseTime = 0;
  float averageTAT = 0;
  cout << "\n";
  cout << "P.Name  AT\tBT\tCT\tTAT\tWT\tRT\n";
  for (i = 0; i < n; i++) {
    cout << 'P' << a[i].pname << "\t";
    cout << a[i].at << "\t";
    cout << a[i].bt << "\t";
    cout << tArray[i + 1] << "\t";
    cout << tArray[i] - a[i].at + a[i].bt << "\t";
    averageTAT += tArray[i] - a[i].at + a[i].bt;
    cout << a[i].wt << "\t";
    averageWaitingTime += tArray[i] - a[i].at;
    cout << tArray[i] - a[i].at << "\t";
    averageResponseTime += tArray[i] - a[i].at;
    cout << "\n";
  }
  cout << "\n";
  cout << "\nGantt Chart\n";
  for (i = 0; i < n; i++) {
    cout << "|  P" << a[i].pname << "   ";
  }
  cout << "\n";
  for (i = 0; i < n + 1; i++) {
    cout << tArray[i] << "\t";
  }
  cout << "\n";
  cout << "\n";
  cout << "Average Response time: " << (float) averageResponseTime / (float) n << endl;
  cout << "Average Waiting time: " << (float) averageWaitingTime / (float) n << endl;
  cout << "Average TA time: " << (float) averageTAT / (float) n << endl;

}

// The main() function reads the number of processes and calls the insert() and disp() functions.
int main() {
  int nop, choice, i;
  cout << "Enter number of processes\n";
  cin >> nop;
  insert(nop);
  disp(nop);
  return 0;
}