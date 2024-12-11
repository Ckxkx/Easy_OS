#include <iostream>
#include "process_management.h"
#include "device_io_management.h"
#include "dynamic_memory_management.h"
#include "paging_memory_management.h"
#include "file_system_management.h"


int main() {
	extern Task* spoolingQueue;
	std::cout << "  $ 是否进入操作系统? (y/n) ";
	std::cout << std::endl;
	std::cout << "  $ 请输入您的选择：";
	char choice;
	std::cin >> choice;
	if (choice == 'y') {
		while (true) {
			std::cout << "-------------------------------------\n";
			std::cout << "\t  OS 操作系统主界面 \n";
			std::cout << "-------------------------------------\n";
			std::cout << "\t1. 基本进程管理\n";
			std::cout << "\t2. 设备管理与基本 I/O\n";
			std::cout << "\t3. 文件系统设计\n";
			std::cout << "\t4. 命令行接口 (ls, cat)\n";
			std::cout << "\t5. 退出 OS 操作系统\n";
			std::cout << std::endl;
			std::cout << " $ 请选择操作: ";
			int option;
			std::cin >> option;
			std::cout << std::endl;
			switch (option) {
			case 1:
				start();
				break;
			case 2: {
				MouseDevice* mouseDevice = mouse_device_init();
				mouse_device_open(mouseDevice);
				// 模拟生成任务
				std::cout << "生成任务队列...\n";
				srand(static_cast<unsigned int>(time(nullptr)));
				for (int i = 0; i < 3; ++i) {
					int dataSize = rand() % 100 + 1;
					int priority = rand() % 10;
					enqueue(&spoolingQueue, i + 1, dataSize, priority);
				}
				// 启动 SPOOLING 系统
				spoolingSystem();
				// 模拟鼠标操作
				mouse_move(mouseDevice, 100, 200);
				// 关闭设备
				mouse_device_close(mouseDevice);
				free(mouseDevice);
				break;
			}
			case 3: {
				bool exitFileSys = false;  // 新增标志变量
				while (!exitFileSys) {
					std::cout << "\n-------------------------------------\n";
					std::cout << "\t动态分区内存管理模拟系统\n";
					std::cout << "-------------------------------------\n";
					std::cout << "\t1. 分配内存\n";
					std::cout << "\t2. 回收内存\n";
					std::cout << "\t3. 显示分区信息\n";
					std::cout << "\t0. 退出\n";
					std::cout << "\t$ 请选择操作：";
					int choice;
					std::cin >> choice;
					switch (choice) {
					case 1: {
						std::string processName;
						int processSize;
						std::cout << "\t请输入进程名和进程大小（单位：字节）：" << std::endl;
						std::cin >> processName >> processSize;
						allocateMemory(processName, processSize);
						break;
					}
					case 2: {
						std::string processName;
						std::cout << "\t请输入要释放的进程名：" << std::endl;
						std::cin >> processName;
						deallocateMemory(processName);
						break;
					}
					case 3:
						displayPartitions();
						break;
					case 0:
						std::cout << "\t已返回主界面。\n";
						exitFileSys = true;  // 修改此处，设置标志变量为 true 以退出外层循环
						break;
					default:
						std::cout << "\t无效选择，请重新输入。\n";
					}
				}
				break;  // 跳出外层 case 3 的循环体
			}
			case 4: {
				while (true) {
					std::cout << "-------------------------------------\n";
					std::cout << "\t  命令行接口 \n";
					std::cout << "-------------------------------------\n";
					std::cout << "\t$ 请输入命令 (ls, cat, 或 exit 返回主界面): ";
					std::string command;
					std::cin >> command;
					if (command == "ls") {
						std::string path;
						std::cout << "\t请输入目录路径: ";
						std::cin >> path;
						listDirectory(path);
					}
					else if (command == "cat") {
						std::string path;
						std::cout << "\t请输入文件路径: ";
						std::cin >> path;
						readFile(path);
					}
					else if (command == "exit") {
						break;
					}
					else {
						std::cout << "无效命令\n";
					}
				}
				break;
			}
			case 5:
				std::cout << "$ 已为您退出操作系统，期待下次再见！\n";
				return 0;
			default:
				std::cout << "\t$ 无效选择，请重新输入。\n";
			}
		}
	}
	else {
		std::cout << std::endl;
		std::cout << "$ 已为您退出操作系统，期待下次再见！\n";
	}
	return 0;
}