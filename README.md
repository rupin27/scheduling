# scheduling
The goal of this project was to implement four different scheduling algorithms in a scheduling simulator. In particular, I worked on implementing:
<pre>
Firt-In, First-Out (FIFO)
Shortest Job First (SJF)
Shortest Time to Completion First (STCF)
Round Robin (RR)
</pre>
The files inside the workloads directory describe a workload of processes and their start time and execution duration. The definition is two integers per line:
<pre>
  0 100
  10 10
  10 10
</pre>
The first integer is the start time and the second integer is how long the process needs to run (the duration).

The CPU scheduling functions take a priority queue of processes ordered by their arrival time and return a list of processes ordered by their completion time. In addition, the processes that are returned have their first_run and completion fields filled in. Atime slice of 1 time unit has been assumed for the round robin scheduler and all processes are added to the end of the process queue upon arrival.

# Running the Code:
After compiling the code using <b>make<b> command, you can run the test executable.
