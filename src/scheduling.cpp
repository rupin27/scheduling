#include <scheduling.h>
#include <string.h>
#include <fstream>
#include <iostream>
#include <queue>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>

using namespace std;

pqueue_arrival read_workload(string filename) {
  pqueue_arrival workload;
  ifstream strm;
  if(strm.is_open()) {
    cout << "Error: Open file";
    exit(1);
  }
  if (strm.fail()) {
    cout << "Error: Not exist";
  }
  strm.open(filename);
  if(strm.peek() == ifstream::traits_type::eof()){
    cout << "Error: Empty file";
    exit(1);
    }
  string str;
  while (getline(strm, str)) {
    Process p;
    char* strArr = new char[str.length() + 1];
    strcpy(strArr, str.c_str());
    char* tkn = strtok(strArr, " ");
    int i = 0;
    while(tkn != NULL) {
      if(i == 0){
        p.arrival = atoi(tkn);
      }
      else if(i == 1){
        p.duration = atoi(tkn);
      }
      i++;
      tkn = strtok(NULL, " ");
    }
    workload.push(p);
  }
  return workload;
}

void show_workload(pqueue_arrival workload) {
  pqueue_arrival xs = workload;
  cout << "Workload:" << endl;
  while (!xs.empty()) {
    Process p = xs.top();
    cout << '\t' << p.arrival << ' ' << p.duration << endl;
    xs.pop();
  }
}

void show_processes(list<Process> processes) {
  list<Process> xs = processes;
  cout << "Processes:" << endl;
  while (!xs.empty()) {
    Process p = xs.front();
    cout << "\tarrival=" << p.arrival << ", duration=" << p.duration
         << ", first_run=" << p.first_run << ", completion=" << p.completion
         << endl;
    xs.pop_front();
  }
}

list<Process> fifo(pqueue_arrival workload) {
  list<Process> samp;
  int i = 0;
  i = workload.top().arrival;
  while (!workload.empty()) {
    Process p = workload.top(); 
    workload.pop();
    p.first_run = i;
    p.completion = i + p.duration;
    i = p.completion;
    samp.push_back(p);
  }     
  return samp;
}

list<Process> sjf(pqueue_arrival workload) {
  list<Process> samp;
  pqueue_duration space;
  int i = 0;
  i = workload.top().arrival;
  while (!workload.empty() || !space.empty()) {
    while(!workload.empty() && workload.top().arrival <= i){
      Process q = workload.top();
      space.push(q);
      workload.pop();
    } 
    Process p = space.top();
    space.pop();
    p.first_run = i;
    p.completion = i + p.duration;
    i = p.completion;
    samp.push_back(p);
    }
  return samp;
}

list<Process> stcf(pqueue_arrival workload) {
  list<Process> samp; 
  pqueue_duration space;
  int i = 0;
  i = workload.top().arrival;
  while (!workload.empty() && workload.top().arrival == i){
    Process p = workload.top();
    p.first_run = -1;
    space.push(p);
    workload.pop();
  } 
  while (!space.empty()) {
    Process p = space.top();
    space.pop();
    if (p.first_run == -1){
      p.first_run = i;
    }
    p.duration = p.duration - 1;
    i += 1; 
    if (p.duration == 0) {
      p.completion = i;
      samp.push_back(p);
    } 
    else { 
      space.push(p);
    }
    while (!workload.empty() && workload.top().arrival == i){
      Process p = workload.top();
      p.first_run = -1;  
      space.push(p);
      workload.pop();
    }
  }
  return samp;
}

list<Process> rr(pqueue_arrival workload) {
  list<Process> samp;
  list<Process> newSamp;
  int i = 0;
  i = workload.top().arrival;
  while (!workload.empty() && workload.top().arrival == i){
    Process p = workload.top();
    p.first_run = -1;
    newSamp.push_back(p);
    workload.pop();
  } 

  while (!newSamp.empty()){
    Process p = newSamp.front();
    newSamp.pop_front();
    if (p.first_run == -1) {
      p.first_run = i;
    }
    p.duration = p.duration - 1;
    i += 1;

    if (p.duration == 0) {
      p.completion = i;
      samp.push_back(p);
    } 
    else { 
      newSamp.push_back(p);
    }
  }
  return samp;
}

float avg_turnaround(list<Process> processes) {
  float val = 0;
  float size = (float) processes.size();
  while(!processes.empty()){
    Process p = processes.front();
    processes.pop_front();
    float diff = (float) p.completion -(float) p.arrival;
    val += diff; 
  }
  return val / size;
}

float avg_response(list<Process> processes) {
  float val = 0;
  float size = (float) processes.size(); 
  while(!processes.empty()){
    Process p = processes.front();
    processes.pop_front();
    float diff = (float) p.first_run - (float) p.arrival;
    val += diff;
  }
  return val/size;
}

void show_metrics(list<Process> processes) {
  float avg_t = avg_turnaround(processes);
  float avg_r = avg_response(processes);
  show_processes(processes);
  cout << '\n';
  cout << "Average Turnaround Time: " << avg_t << endl;
  cout << "Average Response Time:   " << avg_r << endl;
}
