#include "process_management.h"

// ��ҵ���ƿ�ṹ��
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

// ��ʼ����ҵ����
void initial() {
	int i;
	std::cout << "\n$ ������ҵ����\n";
	std::cin >> n;
	std::cout << "����\nname\tts\tntime\tpriority\n";
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

// ��ӡ��ҵ��Ϣ
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

// ���㲢��ӡƽ����תʱ��ʹ�Ȩ��תʱ��
void last() {
	eti /= n;
	ewi /= n;
	std::cout << "\neti=" << eti << "\tewi=" << ewi << "\n";
}

// ������ҵ������״̬��ʱ��
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
	std::cout << "\n" << p->name << " ����ɣ�\n�����������...\n";
	std::getchar();
}

// �����ȷ�������㷨
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
			std::cout << "\ntime=" << time << ":\tû���ύ����ҵ...�ȴ�...\n";
			time_1++;
			if (time_1 > 100) {
				std::cout << "\n����ʱ�����...����\n";
				std::exit(1);
			}
		}
		else {
			running(min);
		}
	}
}

// �����ҵ���ȵ����㷨
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
			std::cout << "\ntime=" << time << ":\tû���ύ����ҵ...�ȴ�...\n";
			time_1++;
			if (time_1 > 100) {
				std::cout << "\n����ʱ�����...����\n";
				std::exit(1);
			}
		}
		else {
			running(min);
		}
	}
}

// ���ȼ������㷨
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
			std::cout << "\ntime=" << time << ":\tû���ύ����ҵ...�ȴ�...\n";
			time_1++;
			if (time_1 > 100) {
				std::cout << "\n����ʱ�����...����\n";
				std::exit(1);
			}
		}
		else {
			running(min);
		}
	}
}

	// ѡ������㷨��������ҵ
	void runjcb(int m) {
		std::cout << "\n\n��ʼ������ҵ��ʹ���㷨 " << m << ".\n";
		switch (m) {
		case 1: fcfs(); break;
		case 2: sjf(); break;
		case 3: priority_scheduling(); break;
		default:
			std::cout << "\n������ҵ����...\n";
			std::exit(1);
		}
	}

	// �������н��̹���ĳ�ʼ���͵����㷨ѡ��
	void start() {
		int m;
		std::cout << "-------------------------------------\n";
		std::cout << "\t  ����������̹��� \n";
		std::cout << "-------------------------------------\n";
		std::cout << "\n$ ѡ���㷨\n1.FCFS\n2.SJF\n3.���ȼ�����\n";
		std::cin >> m;
		initial();
		if (1 <= m && m <= 3) {
			runjcb(m);
		}
		else {
			std::cout << "\nѡ�����������...\n";
			start();
		}
		last();
	}
	