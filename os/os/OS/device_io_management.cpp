#include "device_io_management.h"
#include <windows.h>

// 鼠标设备结构体
struct MouseDevice {
	int status;
	int is_idle;
	int x;
	int y;
	int button_state;
	char buffer[100];
	int buffer_size;
	int error_code;
};

// 任务结构体
struct Task {
	int id;
	int dataSize;
	int priority;
	struct Task* next;
};

Task* spoolingQueue = NULL;

// 初始化鼠标设备
MouseDevice* mouse_device_init() {
	std::cout << "-------------------------------------\n";
	std::cout << "\t进入设备管理和基本I/O   \n";
	std::cout << "-------------------------------------\n";
	MouseDevice* device = (MouseDevice*)malloc(sizeof(MouseDevice));
	if (device == NULL) {
		perror("Memory allocation failed for device");
		return NULL;
	}
	device->status = 0;
	device->is_idle = 1;
	device->x = 0;
	device->y = 0;
	device->button_state = 0;
	device->buffer_size = 0;
	memset(device->buffer, 0, sizeof(device->buffer));
	device->error_code = 0;
	std::cout << "Mouse device initialized.\n";
	return device;
}

// 打开鼠标设备
int mouse_device_open(MouseDevice* device) {
	if (device == NULL) return -1;
	if (device->status == 1) {
		std::cout << "Mouse device is already open.\n";
		return 0;
	}
	device->status = 1;
	device->is_idle = 1;
	std::cout << "Mouse device opened.\n";
	return 0;
}

// 关闭鼠标设备
int mouse_device_close(MouseDevice* device) {
	if (device == NULL) return -1;
	if (device->status == 0) {
		std::cout << "Mouse device is already closed.\n";
		return 0;
	}
	device->status = 0;
	device->is_idle = 1;
	device->x = 0;
	device->y = 0;
	device->button_state = 0;
	device->buffer_size = 0;
	memset(device->buffer, 0, sizeof(device->buffer));
	device->error_code = 0;
	std::cout << "Mouse device closed.\n";
	return 0;
}

// 模拟鼠标移动操作
int mouse_move(MouseDevice* device, int new_x, int new_y) {
	if (device == NULL || device->status == 0) {
		std::cout << "Mouse device is not open or invalid.\n";
		return -1;
	}
	device->x = new_x;
	device->y = new_y;
	std::cout << "Mouse moved to (" << new_x << ", " << new_y << ")\n";
	return 0;
}

// 添加任务到队列
void enqueue(Task** head, int id, int dataSize, int priority) {
	Task* newTask = (Task*)malloc(sizeof(Task));
	newTask->id = id;
	newTask->dataSize = dataSize;
	newTask->priority = priority;
	newTask->next = NULL;
	if (*head == NULL) {
		*head = newTask;
	}
	else {
		Task* temp = *head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newTask;
	}
}

// 从队列中取出任务
Task* dequeue(Task** head) {
	if (*head == NULL) return NULL;
	Task* temp = *head;
	*head = (*head)->next;
	return temp;
}

// 模拟设备数据传输
int transferData(int taskId, int dataSize) {
	std::cout << "[数据传输] 正在传输任务 " << taskId << " 的数据 (" << dataSize << " KB)...\n";
	Sleep(500);
	// 模拟 10% 的错误率
	if (rand() % 10 < 1) {
		std::cout << "[传输错误] 任务 " << taskId << " 的数据传输失败！\n";
		return 0;
	}
	std::cout << "[传输成功] 任务 " << taskId << " 的数据传输完成！\n";
	return 1;
}

// 中断处理
void handleInterrupt(Task* task) {
	std::cout << "[中断处理] 处理任务 " << task->id << " 的错误...\n";
	Sleep(500000);
	std::cout << "[错误恢复] 任务 " << task->id << " 的数据重新传输完成！\n";
}

// SPOOLING 系统主逻辑
void spoolingSystem() {
	Task* currentTask;
	while ((currentTask = dequeue(&spoolingQueue)) != NULL) {
		if (!transferData(currentTask->id, currentTask->dataSize)) {
			handleInterrupt(currentTask);
		}
		free(currentTask);
	}
}