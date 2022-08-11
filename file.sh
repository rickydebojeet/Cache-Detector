#!/bin/bash
TRACE_DIR='/mnt/c/Users/Munawira/Documents/Morrigan/paper-47-AE/traces'
# list of all considered workloads
BENCHMARKS='
srv_575
srv_743
srv_551
srv_526
srv_73
srv_706
srv_128
srv_194
srv_287
srv_764
srv_617
srv_276
srv_364
srv_408
srv_669
srv_426
srv_715
srv_504
srv_771
srv_48
srv_222
srv_255
srv_225
srv_41
srv_259
srv_32
srv_641
srv_582
srv_702
srv_21
srv_442
srv_61
srv_495
srv_727
srv_537
srv_540
srv_85
srv_12
srv_207
srv_s7
srv_s69
srv_s0
srv_s10
srv_s61
srv_s60'

CHAMPSIM_DIR="/mnt/c/Users/Munawira/Documents/Morrigan/paper-47-AE/ChampSim-SC"

BENCHMARKS_DIR="/mnt/c/Users/Munawira/Documents/Morrigan/paper-47-AE/ChampSim-SC/traces"

DESTINATION_FOLDER='Statistics'
MORRIGAN_BINARY='
nobuild1-hashed_perceptron-FNLMMA-ipcp-ipcp-lru-1core
morriganPTbuild2-hashed_perceptron-no-no-no-lru-1core
morriganPTbuild3-hashed_perceptron-FNLMMA-ipcp-ipcp-lru-1core
nobuild4-hashed_perceptron-no-no-no-lru-1core'

for i in ${MORRIGAN_BINARY}; do
    mkdir -p ${DESTINATION_FOLDER}/${i}
        for j in ${BENCHMARKS}; do
             (./bin/${i} -warmup_instructions 30000000 -simulation_instructions 30000000  -traces ${TRACE_DIR}/${j}.champsimtrace.xz) &> ${DESTINATION_FOLDER}/${i}/${j}.txt &
                
        done
done

#for i in ${MORRIGANBINARY}; do
 #   mkdir -p ${DESTINATION_FOLDER}/${i}

  #      for j in ${BENCHMARKS}; do
   #         (./bin/${i} -warmup_instructions 1000000 -simulation_instructions 1000000  -traces ${TRACE_DIR}/${j}.champsimtrace.xz) &> ${DESTINATION_FOLDER}/${i}/sim_${i}_${j}.txt

    #    done
#done        
