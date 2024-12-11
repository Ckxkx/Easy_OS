#ifndef PAGING_MEMORY_MANAGEMENT_H
#define PAGING_MEMORY_MANAGEMENT_H
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

#include <iostream>
#include <vector>
#include <string>

// 页表项结构体
struct PageTableEntry;

// 函数声明
void allocateMemoryPaging(const std::string& processName, int processSize);
void deallocateMemoryPaging();
void translateAddress();
void displayPageTable();
void displayFreeFrames();

#endif