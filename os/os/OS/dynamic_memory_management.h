#pragma once
#ifndef DYNAMIC_MEMORY_MANAGEMENT_H
#define DYNAMIC_MEMORY_MANAGEMENT_H
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

#include <iostream>
#include <vector>
#include <string>

// �����ṹ��
struct Partition;

// ��������
void allocateMemory(const std::string& processName, int processSize);
void deallocateMemory(const std::string& processName);
void mergePartitions();
void displayPartitions();

#endif