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

void InputStudent(LinkList* plist)
{
	char id[20], name[20], class_id[20], sex[10];
	int age;
	printf("请输入学生学号... \n");
	while (getc(stdin) != '\n');
	fgets(id, 20, stdin);
	id[strlen(id) - 1] = '\0';
	printf("请输入学生姓名... \n");
	fgets(name, 20, stdin);
	name[strlen(name) - 1] = '\0';
	printf("请输入学生班级... \n");
	fgets(class_id, 20, stdin);
	class_id[strlen(class_id) - 1] = '\0';
	printf("请输入学生性别... \n");
	fgets(sex, 10, stdin); // woman man // nan nv 
	sex[strlen(sex) - 1] = '\0';
	printf("请输入学生年龄... \n");// age>= 15 && age<=35;
	scanf("%d", &age);
	Student stud;
	strcpy(stud.s_id, id);
	strcpy(stud.s_name, name);
	strcpy(stud.s_class_id, class_id);
	strcpy(stud.s_sex, sex);
	stud.s_age = age;

	Push_Front(plist, stud);
}

void PrintStudent(LinkList* plist)
{
	assert(plist != NULL);
	for (ListNode* p = GetFirst(plist); p != NULL; p = GetNext(p))
	{
		printf("id: %s ", p->data.s_id);
		printf("name: %s ", p->data.s_name);
		printf("class_id: %s ", p->data.s_class_id);
		printf("sex: %s ", p->data.s_sex);
		printf("age: %d \n", p->data.s_age);
	}
	printf("\n-------------------------------------------\n");

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
		case 5:
			PrintStudent(plist);
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
	//LoadFile(&studlist);
	RunMenu(&studlist);
	SaveFile(&studlist);
	DestroyList(&studlist);
	return 0;
}
