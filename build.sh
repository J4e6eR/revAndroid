#!/bin/bash
# clang++ -Wall -std=c++11 read_nfc.cpp -o test.out -L. -lbinder_ndk -landroid_nfc && LD_LIBRARY_PATH=. ./test.out
clang++ -Wall -std=c++11 read_nfc.cpp -o test.out -L. -lbinder_ndk -l:android.hardware.nfc-V1-ndk.so && LD_LIBRARY_PATH=. ./test.out
