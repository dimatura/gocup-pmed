#!/bin/bash
./pmedian demandas1.txt coordenadas1.txt | tee -a prob1.log
./pmedian demandas2.txt coordenadas2.txt | tee -a prob2.log
./pmedian demandas3.txt coordenadas3.txt | tee -a prob3.log
./pmedian demandas4.txt coordenadas4.txt | tee -a prob4.log
