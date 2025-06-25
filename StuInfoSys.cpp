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
	printf("学号:  ");
	while (getc(stdin) != '\n');
	fgets(id, 20, stdin);
	id[strlen(id) - 1] = '\0';
	for (ListNode* p = GetFirst(plist); p != NULL; p = GetNext(p))
	{
		if (strcmp(p->data.s_id, id) == 0)
		{
			printf("该学号已存在，不能重复录入！\n");
			return;
		}
	}
	printf("姓名:  ");
	fgets(name, 20, stdin);
	name[strlen(name) - 1] = '\0';
	printf("班级:  ");
	fgets(class_id, 20, stdin);
	class_id[strlen(class_id) - 1] = '\0';
	printf("性别:  ");
	fgets(sex, 10, stdin); 
	if (strcmp(sex, "男\n") != 0 || strcmp(sex, "女\n") != 0)
	{
		printf("性别只能是男或女，请重新输入\n\n");
		return;
	}
	sex[strlen(sex) - 1] = '\0';
	printf("年龄:  ");
	scanf("%d", &age);
	if (age < 15 || age>35)
	{
		printf("年龄不能小于15岁或大于35岁，请重新输入\n\n");
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
		printf("保存失败");
	}
}

void PrintStudent(LinkList* plist)
{
	assert(plist != NULL);
	printf("\n----------------------------------------------\n\n");
	printf("学号\t\t姓名\t班级\t性别\t年龄\n");
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
	printf("学生学号: ");
	while (getc(stdin) != '\n');
	fgets(id, 20, stdin);
	id[strlen(id) - 1] = '\0';
	for (ListNode* p = GetFirst(plist); p != NULL; p = GetNext(p))
	{
		if (strcmp(p->data.s_id, id) == 0)
		{
			printf("学号: %s\n", p->data.s_id);
			printf("姓名: %s\n", p->data.s_name);
			printf("班级: %s\n", p->data.s_class_id);
			printf("性别: %s\n", p->data.s_sex);
			printf("年龄: %d\n", p->data.s_age);
			return;
		}
	}
	printf("未找到学号为 %s 的学生信息\n", id);
}

void Search_byName(LinkList* plist)
{
	assert(plist != NULL);
	char name[20];
	printf("学生姓名: ");
	while (getc(stdin) != '\n');
	fgets(name, 20, stdin);
	name[strlen(name) - 1] = '\0';
	bool found = false;
	for (ListNode* p = GetFirst(plist); p != NULL; p = GetNext(p))
	{
		if (strcmp(p->data.s_name, name) == 0)
		{
			printf("学号: %s\n", p->data.s_id);
			printf("姓名: %s\n", p->data.s_name);
			printf("班级: %s\n", p->data.s_class_id);
			printf("性别: %s\n", p->data.s_sex);
			printf("年龄: %d\n", p->data.s_age);
			found = true;
		}
	}
	if (!found)
	{
		printf("未找到姓名为 %s 的学生信息\n", name);
	}
}

void SearchStu(LinkList* plist)
{
	assert(plist != NULL);
	int select = 0;
	printf("==========查询学生信息==========\n");
	printf("| 1. 按学号查询                  |\n");
	printf("| 2. 按姓名查询                  |\n");
	printf("| 0. 返回上一级                  |\n");	
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
		printf("选择错误，请重新选择 .... \n");
		break;
	}
}

void RunMenu(LinkList* plist)
{
	assert(plist != NULL);
	int select = 0;
	do
	{
		printf("==========学生信息管理系统==========\n");
		printf("| 1. 录入学生信息                  |\n");
		printf("| 2. 查询学生信息                  |\n");
		printf("| 3. 修改已有学生信息              |\n");
		printf("| 4. 统计学生信息                  |\n");
		printf("| 5. 输出全部学生信息              |\n");
		printf("| 0. 退出系统                      |\n");
		printf("====================================\n");
		printf("请选择 .... ");
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
				printf("学生信息为空，请先录入学生信息\n");
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
			printf("选择错误 ，请重新选择  .... \n");
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
