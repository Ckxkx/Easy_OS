#pragma once
#ifndef DEVICE_IO_MANAGEMENT_H
#define DEVICE_IO_MANAGEMENT_H
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
//#include <unistd.h>

// 鼠标设备结构体
struct MouseDevice;

// 任务结构体
struct Task;

// 函数声明
MouseDevice* mouse_device_init();
//Task* spoolingQueue = 0;
int mouse_device_open(MouseDevice* device);
int mouse_device_close(MouseDevice* device);
int mouse_move(MouseDevice* device, int new_x, int new_y);
void enqueue(Task** head, int id, int dataSize, int priority);
Task* dequeue(Task** head);
int transferData(int taskId, int dataSize);
void handleInterrupt(Task* task);
void spoolingSystem();

#endif