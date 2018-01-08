#!/bin/bash
clear
g++ *.cpp -o SensAirServer -L./lib/ -lpistache -I./ @"g++ options.txt" -pthread -lpthread
