#!/bin/bash
SIZE='
10
11
12
13
14
15
16
17
18
19
20
21
22
23
'

CHAMPSIM_DIR=""
TRACE_DIR=""
DESTINATION='data'

mkdir -p ${DESTINATION}

for i in ${SIZE}; do
    (./run_champsim.sh bimodal-no-no-no-no-lru-1core 1 1 ${i}.champsimtrace.xz)
done