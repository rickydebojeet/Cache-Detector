# Cache Detector
This repository deals with caches and its hierarchy. Built for Programming assignment of Computer Architecture for Performance and Security.
The repository contains three programs that does 3 seperate tasks.

## Task 1: Finding Cache sizes
The program measures the size of each level of cache of your system. It generates a plot by observing which the values can be found out. Most of the modern systems have three levels of cache (L1 to L3) with sizes ranging from few KBs to MBs. 
> **_NOTE:_**  The prefetcher must be turned off to get perfect results.

### Usage
Go to the `task1\code\` folder and run the following command:
```bash
bash run-script.sh
```

## Task 2: Finding Cache sizes in a simulator
This program is almost same, but is run through a micro-architectural simulator called ChampSim. Please use [this](https://github.com/rickydebojeet/ChampSim) version of Champsim for this task. The program determines the size of L1D, L2C, and the last-level cache(LLC, a.k.a. L3C). This is done by using variations of a program that accesses an array of a specific size, say 16KB, 32KB, or 64KB, and then observing the instruction per cycle (IPC) difference. If at a specific array size, there is an IPC drop, it means the previous array size was the size of the cache. Going from 1KB to 8MB, you will first get the size of L1D, then L2, and finally LLC.

To set up the simulator you can follow the documentation of the ChampSim Simulator.
### Usage
Go to the `task2\code\` folder and run the following command:
```bash
gcc cache-code-task2.c
```
Copy the `generate-traces.sh` in pin directory and adjust the script as per needed and run the following command:
```bash
bash generate-traces.g
```
Copy the `champsim-builder.sh` in ChampSim directory and adjust the script as per needed and run the following command:
```bash
bash champsim-builder.sh
```
Go to the `task2\code\` folder and run the following command:
```bash
bash analysis-script.sh
```

## Bonus: Finding Cache sizes
The program measures the size of cache block of your system. It generates a plot by observing which the value can be found out.
> **_NOTE:_**  The prefetcher must be turned off to get perfect results.

### Usage
Go to the `bonus\code\` folder and run the following command:
```bash
bash block-runner.sh
```
