#include <iostream>
#include "process_management.h"
#include "device_io_management.h"
#include "dynamic_memory_management.h"
#include "paging_memory_management.h"
#include "file_system_management.h"


int main() {
	extern Task* spoolingQueue;
	std::cout << "  $ �Ƿ�������ϵͳ? (y/n) ";
	std::cout << std::endl;
	std::cout << "  $ ����������ѡ��";
	char choice;
	std::cin >> choice;
	if (choice == 'y') {
		while (true) {
			std::cout << "-------------------------------------\n";
			std::cout << "\t  OS ����ϵͳ������ \n";
			std::cout << "-------------------------------------\n";
			std::cout << "\t1. �������̹���\n";
			std::cout << "\t2. �豸��������� I/O\n";
			std::cout << "\t3. �ļ�ϵͳ���\n";
			std::cout << "\t4. �����нӿ� (ls, cat)\n";
			std::cout << "\t5. �˳� OS ����ϵͳ\n";
			std::cout << std::endl;
			std::cout << " $ ��ѡ�����: ";
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
				// ģ����������
				std::cout << "�����������...\n";
				srand(static_cast<unsigned int>(time(nullptr)));
				for (int i = 0; i < 3; ++i) {
					int dataSize = rand() % 100 + 1;
					int priority = rand() % 10;
					enqueue(&spoolingQueue, i + 1, dataSize, priority);
				}
				// ���� SPOOLING ϵͳ
				spoolingSystem();
				// ģ��������
				mouse_move(mouseDevice, 100, 200);
				// �ر��豸
				mouse_device_close(mouseDevice);
				free(mouseDevice);
				break;
			}
			case 3: {
				bool exitFileSys = false;  // ������־����
				while (!exitFileSys) {
					std::cout << "\n-------------------------------------\n";
					std::cout << "\t��̬�����ڴ����ģ��ϵͳ\n";
					std::cout << "-------------------------------------\n";
					std::cout << "\t1. �����ڴ�\n";
					std::cout << "\t2. �����ڴ�\n";
					std::cout << "\t3. ��ʾ������Ϣ\n";
					std::cout << "\t0. �˳�\n";
					std::cout << "\t$ ��ѡ�������";
					int choice;
					std::cin >> choice;
					switch (choice) {
					case 1: {
						std::string processName;
						int processSize;
						std::cout << "\t������������ͽ��̴�С����λ���ֽڣ���" << std::endl;
						std::cin >> processName >> processSize;
						allocateMemory(processName, processSize);
						break;
					}
					case 2: {
						std::string processName;
						std::cout << "\t������Ҫ�ͷŵĽ�������" << std::endl;
						std::cin >> processName;
						deallocateMemory(processName);
						break;
					}
					case 3:
						displayPartitions();
						break;
					case 0:
						std::cout << "\t�ѷ��������档\n";
						exitFileSys = true;  // �޸Ĵ˴������ñ�־����Ϊ true ���˳����ѭ��
						break;
					default:
						std::cout << "\t��Чѡ�����������롣\n";
					}
				}
				break;  // ������� case 3 ��ѭ����
			}
			case 4: {
				while (true) {
					std::cout << "-------------------------------------\n";
					std::cout << "\t  �����нӿ� \n";
					std::cout << "-------------------------------------\n";
					std::cout << "\t$ ���������� (ls, cat, �� exit ����������): ";
					std::string command;
					std::cin >> command;
					if (command == "ls") {
						std::string path;
						std::cout << "\t������Ŀ¼·��: ";
						std::cin >> path;
						listDirectory(path);
					}
					else if (command == "cat") {
						std::string path;
						std::cout << "\t�������ļ�·��: ";
						std::cin >> path;
						readFile(path);
					}
					else if (command == "exit") {
						break;
					}
					else {
						std::cout << "��Ч����\n";
					}
				}
				break;
			}
			case 5:
				std::cout << "$ ��Ϊ���˳�����ϵͳ���ڴ��´��ټ���\n";
				return 0;
			default:
				std::cout << "\t$ ��Чѡ�����������롣\n";
			}
		}
	}
	else {
		std::cout << std::endl;
		std::cout << "$ ��Ϊ���˳�����ϵͳ���ڴ��´��ټ���\n";
	}
	return 0;
}