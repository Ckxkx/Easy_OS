#include "paging_memory_management.h"
#include <iomanip>

// 页表项结构体
struct PageTableEntry {
	int pageNumber;
	int frameNumber;
	std::string processName;
};

class PagingMemory {
private:
	std::vector<PageTableEntry> pageTable;
	std::vector<bool> frames;
	int pageSize;
	int memorySize;
	int numFrames;
public:
	// 构造函数
	PagingMemory(int memorySize, int pageSize) {
		this->memorySize = memorySize;
		this->pageSize = pageSize;
		numFrames = memorySize / pageSize;
		frames.resize(numFrames, false);
	}
	// 分配内存
	void allocateMemoryPaging(const std::string& processName, int processSize) {
		int numPages = (processSize + pageSize - 1) / pageSize;
		std::vector<int> allocatedFrames;
		for (int i = 0; i < numFrames && allocatedFrames.size() < numPages; i++) {
			if (!frames[i]) {
				frames[i] = true;
				allocatedFrames.push_back(i);
			}
		}
		if (allocatedFrames.size() < numPages) {
			std::cout << "内存不足，无法为进程 " << processName << " 分配内存。" << std::endl;
			for (int frame : allocatedFrames) {
				frames[frame] = false;
			}
		}
		else {
			for (int i = 0; i < numPages; i++) {
				pageTable.push_back({ i, allocatedFrames[i], processName });
			}
			std::cout << "进程 " << processName << " 的内存已分配成功，共分配 " << numPages << " 页。" << std::endl;
		}
	}
	// 回收内存
	void deallocateMemoryPaging() {
		std::cout << "$ 请输入要释放的作业名：";
		std::string processName;
		std::cin >> processName;
		bool found = false;
		for (auto& entry : pageTable) {
			if (entry.processName == processName && entry.frameNumber != -1) {
				frames[entry.frameNumber] = false;
				entry.frameNumber = -1;
				entry.processName = "";
				found = true;
			}
		}
		if (found) {
			std::cout << "作业 " << processName << " 的内存已回收。" << std::endl;
		}
		else {
			std::cout << "未找到作业 " << processName << "，无法回收。" << std::endl;
		}
	}
	// 地址转换
	void translateAddress() {
		int logicalAddress;
		std::cout << "请输入逻辑地址：";
		std::cin >> logicalAddress;
		int pageNumber = logicalAddress / pageSize;
		int offset = logicalAddress % pageSize;
		if (pageNumber >= pageTable.size() || pageTable[pageNumber].frameNumber == -1) {
			std::cout << "地址转换失败：无效的逻辑地址或页未分配。" << std::endl;
			return;
		}
		int frameNumber = pageTable[pageNumber].frameNumber;
		int physicalAddress = frameNumber * pageSize + offset;
		std::cout << "逻辑地址 " << logicalAddress
			<< " 转换为物理地址：" << physicalAddress
			<< " （帧号：" << frameNumber << "，偏移量：" << offset << "）" << std::endl;
	}
	// 显示页表
	void displayPageTable() {
		std::cout << std::left << std::setw(10) << "页号" << std::setw(10) << "帧号" << std::setw(15) << "作业名" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		for (const auto& entry : pageTable) {
			std::cout << std::left << std::setw(10) << entry.pageNumber
				<< std::setw(10) << (entry.frameNumber == -1 ? "未分配" : std::to_string(entry.frameNumber))
				<< std::setw(15) << (entry.processName.empty() ? "无" : entry.processName)
				<< std::endl;
		}
	}
	// 显示空闲帧
	void displayFreeFrames() {
		std::cout << "空闲帧列表：" << std::endl;
		for (int i = 0; i < numFrames; i++) {
			if (!frames[i]) {
				std::cout << "帧号 " << i << std::endl;
			}
		}
		if (frames.end() == std::find(frames.begin(), frames.end(), false)) {
			std::cout << "没有空闲帧。" << std::endl;
		}
	}
};

// 全局分页内存管理对象实例化
PagingMemory pagingMemory(1024, 64); // 假设总内存 1024 字节，每页 64 字节，可按需修改

// 分配内存函数实现
void allocateMemoryPaging(const std::string& processName, int processSize) {
	pagingMemory.allocateMemoryPaging(processName, processSize);
}

// 回收内存函数实现
void deallocateMemoryPaging() {
	pagingMemory.deallocateMemoryPaging();
}

// 地址转换函数实现
void translateAddress() {
	pagingMemory.translateAddress();
}

// 显示页表函数实现
void displayPageTable() {
	pagingMemory.displayPageTable();
}

// 显示空闲帧函数实现
void displayFreeFrames() {
	pagingMemory.displayFreeFrames();
}