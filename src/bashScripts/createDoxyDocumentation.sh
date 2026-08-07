#!/bin/bash
#
#
#Function: builds the target and creates a documentation of the code
#Author: Bomm, Konstantin
#
#

cd ../../build
cmake ../bitCoinDataReader 
make docs
scp -r html /mnt/c/Users/Konst/Desktop


