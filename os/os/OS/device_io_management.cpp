#include "device_io_management.h"
#include <windows.h>

// ����豸�ṹ��
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

// ����ṹ��
struct Task {
	int id;
	int dataSize;
	int priority;
	struct Task* next;
};

Task* spoolingQueue = NULL;

// ��ʼ������豸
MouseDevice* mouse_device_init() {
	std::cout << "-------------------------------------\n";
	std::cout << "\t�����豸����ͻ���I/O   \n";
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

// ������豸
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

// �ر�����豸
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

// ģ������ƶ�����
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

// ������񵽶���
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

// �Ӷ�����ȡ������
Task* dequeue(Task** head) {
	if (*head == NULL) return NULL;
	Task* temp = *head;
	*head = (*head)->next;
	return temp;
}

// ģ���豸���ݴ���
int transferData(int taskId, int dataSize) {
	std::cout << "[���ݴ���] ���ڴ������� " << taskId << " ������ (" << dataSize << " KB)...\n";
	Sleep(500);
	// ģ�� 10% �Ĵ�����
	if (rand() % 10 < 1) {
		std::cout << "[�������] ���� " << taskId << " �����ݴ���ʧ�ܣ�\n";
		return 0;
	}
	std::cout << "[����ɹ�] ���� " << taskId << " �����ݴ�����ɣ�\n";
	return 1;
}

// �жϴ���
void handleInterrupt(Task* task) {
	std::cout << "[�жϴ���] �������� " << task->id << " �Ĵ���...\n";
	Sleep(500000);
	std::cout << "[����ָ�] ���� " << task->id << " ���������´�����ɣ�\n";
}

// SPOOLING ϵͳ���߼�
void spoolingSystem() {
	Task* currentTask;
	while ((currentTask = dequeue(&spoolingQueue)) != NULL) {
		if (!transferData(currentTask->id, currentTask->dataSize)) {
			handleInterrupt(currentTask);
		}
		free(currentTask);
	}
}