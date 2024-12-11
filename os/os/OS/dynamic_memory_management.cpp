#include "dynamic_memory_management.h"
#include <iomanip>

// �����ṹ��
struct Partition {
	int partitionID;
	int startAddress;
	int size;
	std::string processName;
	bool allocated;
};

class DynamicMemory {
private:
	std::vector<Partition> partitions;
	int totalMemory;
	int nextPartitionID;
public:
	// ���캯��
	DynamicMemory(int memorySize) {
		totalMemory = memorySize;
		nextPartitionID = 1;
		partitions.push_back({ 0, 0, memorySize, "", false });
	}
	// �����ڴ�
	void allocateMemory(const std::string& processName, int processSize) {
		int bestIndex = -1;
		int bestSize = INT_MAX;
		for (int i = 0; i < partitions.size(); i++) {
			if (!partitions[i].allocated && partitions[i].size >= processSize) {
				int remainingSize = partitions[i].size - processSize;
				if (remainingSize < bestSize) {
					bestSize = remainingSize;
					bestIndex = i;
				}
			}
		}
		if (bestIndex == -1) {
			std::cout << "�ڴ治�㣬�޷�Ϊ���� " << processName << " �����ڴ档" << std::endl;
		}
		else {
			auto& bestPartition = partitions[bestIndex];
			int remainingSize = bestPartition.size - processSize;
			bestPartition.allocated = true;
			bestPartition.processName = processName;
			bestPartition.size = processSize;
			bestPartition.partitionID = nextPartitionID++;
			if (remainingSize > 0) {
				Partition newPartition = { 0, bestPartition.startAddress + processSize, remainingSize, "", false };
				partitions.insert(partitions.begin() + bestIndex + 1, newPartition);
			}
			std::cout << "���� " << processName << " ����ɹ�����С " << processSize << std::endl;
		}
	}
	// �����ڴ�
	void deallocateMemory(const std::string& processName) {
		bool found = false;
		for (auto& partition : partitions) {
			if (partition.allocated && partition.processName == processName) {
				partition.allocated = false;
				partition.processName = "";
				partition.partitionID = 0;
				found = true;
				std::cout << "���� " << processName << " ���ڴ��ѻ��գ���ʼ��ַ " << partition.startAddress << "����С " << partition.size << " �ֽڣ���" << std::endl;
			}
		}
		if (!found) {
			std::cout << "δ�ҵ����� " << processName << "���޷������ڴ档" << std::endl;
		}
		else {
			mergePartitions();
		}
	}
	// �ϲ����ڿ��з���
	void mergePartitions() {
		for (auto it = partitions.begin(); it != partitions.end() - 1; ) {
			auto next = it + 1;
			if (!it->allocated && !next->allocated && it->startAddress + it->size == next->startAddress) {
				it->size += next->size;
				partitions.erase(next);
			}
			else {
				++it;
			}
		}
	}
	// ��ʾ������Ϣ
	void displayPartitions() {
		std::cout << std::left << std::setw(10) << "���� ID" << std::setw(15) << "��ʼ��ַ" << std::setw(10) << "��С" << std::setw(15) << "״̬" << std::setw(15) << "������" << std::endl;
		std::cout << "-------------------------------------------------------------------------" << std::endl;
		for (const auto& partition : partitions) {
			std::cout << std::left << std::setw(10) << (partition.partitionID == 0 ? "����" : std::to_string(partition.partitionID))
				<< std::setw(15) << partition.startAddress
				<< std::setw(10) << partition.size
				<< std::setw(15) << (partition.allocated ? "�ѷ���" : "����")
				<< std::setw(15) << (partition.processName.empty() ? "��" : partition.processName)
				<< std::endl;
		}
	}
};

// ȫ�ֶ�̬�ڴ�������ʵ����
DynamicMemory dynamicMemory(1024); // �����ʼ���ڴ�Ϊ 1024 �ֽڣ��ɸ���ʵ�������޸�

// �����ڴ溯��ʵ��
void allocateMemory(const std::string& processName, int processSize) {
	dynamicMemory.allocateMemory(processName, processSize);
}

// �����ڴ溯��ʵ��
void deallocateMemory(const std::string& processName) {
	dynamicMemory.deallocateMemory(processName);
}

// �ϲ���������ʵ��
void mergePartitions() {
	dynamicMemory.mergePartitions();
}

// ��ʾ��������ʵ��
void displayPartitions() {
	dynamicMemory.displayPartitions();
}