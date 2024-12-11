#pragma once
#ifndef PROCESS_MANAGEMENT_H
#define PROCESS_MANAGEMENT_H
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

#include <iostream>
#include <cstdlib>

struct jcb;

// º¯ÊýÉùÃ÷
void initial();
void print(jcb* pr);
void last();
void running(jcb* p);
void fcfs();
void sjf();
void priority_scheduling();
void runjcb(int m);
void start();

#endif