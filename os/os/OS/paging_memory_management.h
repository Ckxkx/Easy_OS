#ifndef PAGING_MEMORY_MANAGEMENT_H
#define PAGING_MEMORY_MANAGEMENT_H
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

#include <iostream>
#include <vector>
#include <string>

// ҳ����ṹ��
struct PageTableEntry;

// ��������
void allocateMemoryPaging(const std::string& processName, int processSize);
void deallocateMemoryPaging();
void translateAddress();
void displayPageTable();
void displayFreeFrames();

#endif