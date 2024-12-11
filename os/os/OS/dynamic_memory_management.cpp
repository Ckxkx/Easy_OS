#include "dynamic_memory_management.h"
#include <iomanip>

// 分区结构体
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
	// 构造函数
	DynamicMemory(int memorySize) {
		totalMemory = memorySize;
		nextPartitionID = 1;
		partitions.push_back({ 0, 0, memorySize, "", false });
	}
	// 分配内存
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
			std::cout << "内存不足，无法为进程 " << processName << " 分配内存。" << std::endl;
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
			std::cout << "进程 " << processName << " 分配成功，大小 " << processSize << std::endl;
		}
	}
	// 回收内存
	void deallocateMemory(const std::string& processName) {
		bool found = false;
		for (auto& partition : partitions) {
			if (partition.allocated && partition.processName == processName) {
				partition.allocated = false;
				partition.processName = "";
				partition.partitionID = 0;
				found = true;
				std::cout << "进程 " << processName << " 的内存已回收（起始地址 " << partition.startAddress << "，大小 " << partition.size << " 字节）。" << std::endl;
			}
		}
		if (!found) {
			std::cout << "未找到进程 " << processName << "，无法回收内存。" << std::endl;
		}
		else {
			mergePartitions();
		}
	}
	// 合并相邻空闲分区
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
	// 显示分区信息
	void displayPartitions() {
		std::cout << std::left << std::setw(10) << "分区 ID" << std::setw(15) << "起始地址" << std::setw(10) << "大小" << std::setw(15) << "状态" << std::setw(15) << "进程名" << std::endl;
		std::cout << "-------------------------------------------------------------------------" << std::endl;
		for (const auto& partition : partitions) {
			std::cout << std::left << std::setw(10) << (partition.partitionID == 0 ? "空闲" : std::to_string(partition.partitionID))
				<< std::setw(15) << partition.startAddress
				<< std::setw(10) << partition.size
				<< std::setw(15) << (partition.allocated ? "已分配" : "空闲")
				<< std::setw(15) << (partition.processName.empty() ? "无" : partition.processName)
				<< std::endl;
		}
	}
};

// 全局动态内存管理对象实例化
DynamicMemory dynamicMemory(1024); // 假设初始总内存为 1024 字节，可根据实际需求修改

// 分配内存函数实现
void allocateMemory(const std::string& processName, int processSize) {
	dynamicMemory.allocateMemory(processName, processSize);
}

// 回收内存函数实现
void deallocateMemory(const std::string& processName) {
	dynamicMemory.deallocateMemory(processName);
}

// 合并分区函数实现
void mergePartitions() {
	dynamicMemory.mergePartitions();
}

// 显示分区函数实现
void displayPartitions() {
	dynamicMemory.displayPartitions();
}