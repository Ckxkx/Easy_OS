#include "process_management.h"

// 作业控制块结构体
struct jcb {
	char name[10];
	char state;
	int ts;
	int tb;
	int tc;
	float ti;
	float wi;
	int ntime;
	int priority;
	struct jcb* link;
} *p, * q, * head = NULL;
typedef struct jcb JCB;

int n = 0, time_1 = 0;
float eti = 0, ewi = 0;

// 初始化作业数据
void initial() {
	int i;
	std::cout << "\n$ 输入作业数量\n";
	std::cin >> n;
	std::cout << "输入\nname\tts\tntime\tpriority\n";
	for (i = 0; i < n; i++) {
		p = (JCB*)malloc(sizeof(JCB));
		std::cin >> p->name >> p->ts >> p->ntime >> p->priority;
		p->state = 'W';
		p->link = NULL;
		if (head == NULL) {
			head = q = p;
		}
		else {
			q->link = p;
			q = p;
		}
	}
}

// 打印作业信息
void print(JCB* pr) {
	JCB* p;
	std::cout << "\ntime=" << time << "\n";
	std::cout << "name\tstate\tts\tntime\tpriority\ttb\ttc\tti\twi\n";
	std::cout << pr->name << "\t" << pr->state << "\t" << pr->ts << "\t" << pr->ntime << "\t" << pr->priority << "\t" << pr->tb << "\t" << pr->tc << "\t" << pr->ti << "\t" << pr->wi << "\n";
	p = head;
	do {
		if (p->state == 'W') {
			std::cout << p->name << "\t" << p->state << "\t" << p->ts << "\t" << p->ntime << "\t" << p->priority << "\n";
		}
		p = p->link;
	} while (p != NULL);
	p = head;
	do {
		if (p->state == 'F') {
			std::cout << p->name << "\t" << p->state << "\t" << p->ts << "\t" << p->ntime << "\t" << p->priority << "\t" << p->tb << "\t" << p->tc << "\t" << p->ti << "\t" << p->wi << "\n";
		}
		p = p->link;
	} while (p != NULL);
}

// 计算并打印平均周转时间和带权周转时间
void last() {
	eti /= n;
	ewi /= n;
	std::cout << "\neti=" << eti << "\tewi=" << ewi << "\n";
}

// 运行作业，更新状态和时间
void running(JCB* p) {
	p->tb = time_1;
	p->state = 'R';
	p->tc = p->tb + p->ntime;
	p->ti = (float)(p->tc - p->ts);
	p->wi = (float)(p->ti / p->ntime);
	eti += p->ti;
	ewi += p->wi;
	print(p);
	time_1 += p->ntime;
	p->state = 'F';
	std::cout << "\n" << p->name << " 已完成！\n按任意键继续...\n";
	std::getchar();
}

// 先来先服务调度算法
void fcfs() {
	JCB* min;
	int i, iden;
	for (i = 0; i < n; i++) {
		p = min = head;
		iden = 1;
		do {
			if (p->state == 'W' && p->ts <= time_1) {
				if (iden) {
					min = p;
					iden = 0;
				}
				else if (p->ts < min->ts || (p->ts == min->ts && p->priority > min->priority)) {
					min = p;
				}
			}
			p = p->link;
		} while (p != NULL);
		if (iden) {
			i--;
			std::cout << "\ntime=" << time << ":\t没有提交的作业...等待...\n";
			time_1++;
			if (time_1 > 100) {
				std::cout << "\n运行时间过长...错误\n";
				std::exit(1);
			}
		}
		else {
			running(min);
		}
	}
}

// 最短作业优先调度算法
void sjf() {
	JCB* min;
	int i, iden;
	for (i = 0; i < n; i++) {
		p = min = head;
		iden = 1;
		do {
			if (p->state == 'W' && p->ts <= time_1) {
				if (iden) {
					min = p;
					iden = 0;
				}
				else if (p->ntime < min->ntime || (p->ntime == min->ntime && p->priority > min->priority)) {
					min = p;
				}
			}
			p = p->link;
		} while (p != NULL);
		if (iden) {
			i--;
			std::cout << "\ntime=" << time << ":\t没有提交的作业...等待...\n";
			time_1++;
			if (time_1 > 100) {
				std::cout << "\n运行时间过长...错误\n";
				std::exit(1);
			}
		}
		else {
			running(min);
		}
	}
}

// 优先级调度算法
void priority_scheduling() {
	JCB* min;
	int i, iden;
	for (i = 0; i < n; i++) {
		p = min = head;
		iden = 1;
		do {
			if (p->state == 'W' && p->ts <= time_1) {
				if (iden) {
					min = p;
					iden = 0;
				}
				else if (p->priority > min->priority) {
					min = p;
				}
			}
			p = p->link;
		} while (p != NULL);
		if (iden) {
			i--;
			std::cout << "\ntime=" << time << ":\t没有提交的作业...等待...\n";
			time_1++;
			if (time_1 > 100) {
				std::cout << "\n运行时间过长...错误\n";
				std::exit(1);
			}
		}
		else {
			running(min);
		}
	}
}

	// 选择调度算法并运行作业
	void runjcb(int m) {
		std::cout << "\n\n开始运行作业，使用算法 " << m << ".\n";
		switch (m) {
		case 1: fcfs(); break;
		case 2: sjf(); break;
		case 3: priority_scheduling(); break;
		default:
			std::cout << "\n运行作业错误...\n";
			std::exit(1);
		}
	}

	// 主函数中进程管理的初始化和调度算法选择
	void start() {
		int m;
		std::cout << "-------------------------------------\n";
		std::cout << "\t  进入基本进程管理 \n";
		std::cout << "-------------------------------------\n";
		std::cout << "\n$ 选择算法\n1.FCFS\n2.SJF\n3.优先级调度\n";
		std::cin >> m;
		initial();
		if (1 <= m && m <= 3) {
			runjcb(m);
		}
		else {
			std::cout << "\n选择错误！请重试...\n";
			start();
		}
		last();
	}
	