#define _CRT_SECURE_NO_WARNINGS
#include<assert.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Student
{
	char s_id[20];
	char s_name[20];
	char s_class_id[20];
	char s_sex[10];
	int s_age;
};

typedef struct Student ElemType;

typedef struct ListNode
{
	struct ListNode* next;
	ElemType data;
}ListNode;

typedef struct
{
	ListNode* head;
	int cursize;
}LinkList;

ListNode* Buynode()
{
	ListNode* s = (ListNode*)malloc(sizeof(ListNode));
	if (NULL == s) exit(EXIT_FAILURE);
	memset(s, 0, sizeof(ListNode));
	return s;
}

void Freenode(ListNode* p)
{
	free(p);
}

void InitList(LinkList* plist)
{
	ListNode* s = Buynode();
	plist->head = s; // 
	plist->cursize = 0;
}

int GetSize(const LinkList* plist)
{
	assert(plist != NULL);
	return plist->cursize;
}

bool IsEmpty(const LinkList* plist)
{
	assert(plist != NULL);
	return GetSize(plist) == 0;
}

void ClearList(LinkList* plist)
{
	assert(plist != NULL);
	while (plist->head->next != NULL)
	{
		ListNode* q = plist->head->next; // first data;
		plist->head->next = q->next;
		Freenode(q);
	}
	plist->cursize = 0;
}

void DestroyList(LinkList* plist)
{
	assert(plist != NULL);
	ClearList(plist);
	Freenode(plist->head);
	plist->head = NULL;
}

void Push_Front(LinkList* plist, ElemType val)
{
	assert(plist != NULL);
	ListNode* s = Buynode();
	s->data = val;
	s->next = plist->head->next;
	plist->head->next = s;
	plist->cursize += 1;
}

ListNode* GetFirst(LinkList* plist)
{
	assert(plist != NULL);
	return plist->head->next; // 
}

ListNode* GetNext(ListNode* p)
{
	assert(p != NULL);
	return p->next;
}

bool LoadFile(LinkList* plist)
{
	assert(plist != NULL);
	FILE* fp = fopen("student.txt", "r");
	if (fp == NULL) return false;
	int count = 0;
	fscanf(fp, "%d\n", &count);
	ClearList(plist); 
	for (int i = 0; i < count; ++i)
	{
		Student stud;
		if (fscanf(fp, "%19s %19s %19s %9s %d",
			stud.s_id,
			stud.s_name,
			stud.s_class_id,
			stud.s_sex,
			&stud.s_age) == 5)
		{
			Push_Front(plist, stud);
		}
	}
	fclose(fp);
	return true;
}

bool SaveFile(LinkList* plist);

void InputStudent(LinkList* plist)
{
	char id[20], name[20], class_id[20], sex[10];
	int age;
	printf("ѧ��:  ");
	while (getc(stdin) != '\n');
	fgets(id, 20, stdin);
	id[strlen(id) - 1] = '\0';
	for (ListNode* p = GetFirst(plist); p != NULL; p = GetNext(p))
	{
		if (strcmp(p->data.s_id, id) == 0)
		{
			printf("��ѧ���Ѵ��ڣ������ظ�¼�룡\n");
			return;
		}
	}
	printf("����:  ");
	fgets(name, 20, stdin);
	name[strlen(name) - 1] = '\0';
	printf("�༶:  ");
	fgets(class_id, 20, stdin);
	class_id[strlen(class_id) - 1] = '\0';
	printf("�Ա�:  ");
	fgets(sex, 10, stdin); 
	if (strcmp(sex, "��\n") != 0 || strcmp(sex, "Ů\n") != 0)
	{
		printf("�Ա�ֻ�����л�Ů������������\n\n");
		return;
	}
	sex[strlen(sex) - 1] = '\0';
	printf("����:  ");
	scanf("%d", &age);
	if (age < 15 || age>35)
	{
		printf("���䲻��С��15������35�꣬����������\n\n");
		return;
	}
	Student stud;
	strcpy(stud.s_id, id);
	strcpy(stud.s_name, name);
	strcpy(stud.s_class_id, class_id);
	strcpy(stud.s_sex, sex);
	stud.s_age = age;
	Push_Front(plist, stud);
	if (!SaveFile(plist))
	{
		printf("����ʧ��");
	}
}

void PrintStudent(LinkList* plist)
{
	assert(plist != NULL);
	printf("\n----------------------------------------------\n\n");
	printf("ѧ��\t\t����\t�༶\t�Ա�\t����\n");
	for (ListNode* p = GetFirst(plist); p != NULL; p = GetNext(p))
	{
		printf("%s\t", p->data.s_id);
		printf("%s\t", p->data.s_name);
		printf("%s\t", p->data.s_class_id);
		printf("%s\t", p->data.s_sex);
		printf("%d \n", p->data.s_age);
	}
	printf("\n----------------------------------------------\n\n\n");

}

bool SaveFile(LinkList* plist)
{
	assert(plist != NULL);
	FILE* fp = fopen("student.txt", "w");
	if (NULL == fp) return false;
	fprintf(fp, "%d\n", GetSize(plist));
	for (ListNode* p = GetFirst(plist); p != NULL; p = GetNext(p))
	{
		fprintf(fp, "%s ", p->data.s_id);
		fprintf(fp, "%s ", p->data.s_name);
		fprintf(fp, "%s ", p->data.s_class_id);
		fprintf(fp, "%s ", p->data.s_sex);
		fprintf(fp, "%d \n", p->data.s_age);
	}
	fclose(fp);
	fp = NULL;
	return true;
}

void Search_ByID(LinkList* plist)
{
	assert(plist != NULL);
	char id[20];
	printf("ѧ��ѧ��: ");
	while (getc(stdin) != '\n');
	fgets(id, 20, stdin);
	id[strlen(id) - 1] = '\0';
	for (ListNode* p = GetFirst(plist); p != NULL; p = GetNext(p))
	{
		if (strcmp(p->data.s_id, id) == 0)
		{
			printf("ѧ��: %s\n", p->data.s_id);
			printf("����: %s\n", p->data.s_name);
			printf("�༶: %s\n", p->data.s_class_id);
			printf("�Ա�: %s\n", p->data.s_sex);
			printf("����: %d\n", p->data.s_age);
			return;
		}
	}
	printf("δ�ҵ�ѧ��Ϊ %s ��ѧ����Ϣ\n", id);
}

void Search_byName(LinkList* plist)
{
	assert(plist != NULL);
	char name[20];
	printf("ѧ������: ");
	while (getc(stdin) != '\n');
	fgets(name, 20, stdin);
	name[strlen(name) - 1] = '\0';
	bool found = false;
	for (ListNode* p = GetFirst(plist); p != NULL; p = GetNext(p))
	{
		if (strcmp(p->data.s_name, name) == 0)
		{
			printf("ѧ��: %s\n", p->data.s_id);
			printf("����: %s\n", p->data.s_name);
			printf("�༶: %s\n", p->data.s_class_id);
			printf("�Ա�: %s\n", p->data.s_sex);
			printf("����: %d\n", p->data.s_age);
			found = true;
		}
	}
	if (!found)
	{
		printf("δ�ҵ�����Ϊ %s ��ѧ����Ϣ\n", name);
	}
}

void SearchStu(LinkList* plist)
{
	assert(plist != NULL);
	int select = 0;
	printf("==========��ѯѧ����Ϣ==========\n");
	printf("| 1. ��ѧ�Ų�ѯ                  |\n");
	printf("| 2. ��������ѯ                  |\n");
	printf("| 0. ������һ��                  |\n");	
	printf("=================================\n");
	scanf("%d", &select);
	switch (select)
	{
	case 0:
		return;
	case 1:
		Search_ByID(plist);
		break;
	case 2:
		Search_byName(plist);
		break;
	default:
		printf("ѡ�����������ѡ�� .... \n");
		break;
	}
}

void RunMenu(LinkList* plist)
{
	assert(plist != NULL);
	int select = 0;
	do
	{
		printf("==========ѧ����Ϣ����ϵͳ==========\n");
		printf("| 1. ¼��ѧ����Ϣ                  |\n");
		printf("| 2. ��ѯѧ����Ϣ                  |\n");
		printf("| 3. �޸�����ѧ����Ϣ              |\n");
		printf("| 4. ͳ��ѧ����Ϣ                  |\n");
		printf("| 5. ���ȫ��ѧ����Ϣ              |\n");
		printf("| 0. �˳�ϵͳ                      |\n");
		printf("====================================\n");
		printf("��ѡ�� .... ");
		scanf("%d", &select);
		switch (select)
		{
		case 0: break;
		case 1:
			InputStudent(plist);
			break;
		case 2:
			if (IsEmpty(plist))
			{
				printf("ѧ����ϢΪ�գ�����¼��ѧ����Ϣ\n");
			}
			else
			{
				SearchStu(plist);
			}
			break;
		case 5:
			PrintStudent(plist);
			break;
		default:
			printf("ѡ����� ��������ѡ��  .... \n");
			break;
		}
	} while (select != 0);
}

int main()
{
	LinkList studlist;
	InitList(&studlist);
	LoadFile(&studlist);
	RunMenu(&studlist);
	SaveFile(&studlist);
	DestroyList(&studlist);
	return 0;
}
