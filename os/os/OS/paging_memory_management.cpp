#include "paging_memory_management.h"
#include <iomanip>

// ҳ����ṹ��
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
	// ���캯��
	PagingMemory(int memorySize, int pageSize) {
		this->memorySize = memorySize;
		this->pageSize = pageSize;
		numFrames = memorySize / pageSize;
		frames.resize(numFrames, false);
	}
	// �����ڴ�
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
			std::cout << "�ڴ治�㣬�޷�Ϊ���� " << processName << " �����ڴ档" << std::endl;
			for (int frame : allocatedFrames) {
				frames[frame] = false;
			}
		}
		else {
			for (int i = 0; i < numPages; i++) {
				pageTable.push_back({ i, allocatedFrames[i], processName });
			}
			std::cout << "���� " << processName << " ���ڴ��ѷ���ɹ��������� " << numPages << " ҳ��" << std::endl;
		}
	}
	// �����ڴ�
	void deallocateMemoryPaging() {
		std::cout << "$ ������Ҫ�ͷŵ���ҵ����";
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
			std::cout << "��ҵ " << processName << " ���ڴ��ѻ��ա�" << std::endl;
		}
		else {
			std::cout << "δ�ҵ���ҵ " << processName << "���޷����ա�" << std::endl;
		}
	}
	// ��ַת��
	void translateAddress() {
		int logicalAddress;
		std::cout << "�������߼���ַ��";
		std::cin >> logicalAddress;
		int pageNumber = logicalAddress / pageSize;
		int offset = logicalAddress % pageSize;
		if (pageNumber >= pageTable.size() || pageTable[pageNumber].frameNumber == -1) {
			std::cout << "��ַת��ʧ�ܣ���Ч���߼���ַ��ҳδ���䡣" << std::endl;
			return;
		}
		int frameNumber = pageTable[pageNumber].frameNumber;
		int physicalAddress = frameNumber * pageSize + offset;
		std::cout << "�߼���ַ " << logicalAddress
			<< " ת��Ϊ�����ַ��" << physicalAddress
			<< " ��֡�ţ�" << frameNumber << "��ƫ������" << offset << "��" << std::endl;
	}
	// ��ʾҳ��
	void displayPageTable() {
		std::cout << std::left << std::setw(10) << "ҳ��" << std::setw(10) << "֡��" << std::setw(15) << "��ҵ��" << std::endl;
		std::cout << "----------------------------------------" << std::endl;
		for (const auto& entry : pageTable) {
			std::cout << std::left << std::setw(10) << entry.pageNumber
				<< std::setw(10) << (entry.frameNumber == -1 ? "δ����" : std::to_string(entry.frameNumber))
				<< std::setw(15) << (entry.processName.empty() ? "��" : entry.processName)
				<< std::endl;
		}
	}
	// ��ʾ����֡
	void displayFreeFrames() {
		std::cout << "����֡�б�" << std::endl;
		for (int i = 0; i < numFrames; i++) {
			if (!frames[i]) {
				std::cout << "֡�� " << i << std::endl;
			}
		}
		if (frames.end() == std::find(frames.begin(), frames.end(), false)) {
			std::cout << "û�п���֡��" << std::endl;
		}
	}
};

// ȫ�ַ�ҳ�ڴ�������ʵ����
PagingMemory pagingMemory(1024, 64); // �������ڴ� 1024 �ֽڣ�ÿҳ 64 �ֽڣ��ɰ����޸�

// �����ڴ溯��ʵ��
void allocateMemoryPaging(const std::string& processName, int processSize) {
	pagingMemory.allocateMemoryPaging(processName, processSize);
}

// �����ڴ溯��ʵ��
void deallocateMemoryPaging() {
	pagingMemory.deallocateMemoryPaging();
}

// ��ַת������ʵ��
void translateAddress() {
	pagingMemory.translateAddress();
}

// ��ʾҳ����ʵ��
void displayPageTable() {
	pagingMemory.displayPageTable();
}

// ��ʾ����֡����ʵ��
void displayFreeFrames() {
	pagingMemory.displayFreeFrames();
}