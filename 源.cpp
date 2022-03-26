#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<conio.h> 
#define OK 1 
#define FALSE 0 
#define ERROR -1 
#define Maxx 50
#define DAI 5   //��¼�����������һ�� 
typedef int status;
int man = 0, woman = 0, all_life_expe = 0, peo = 0, com_peo = 0;
typedef struct
{
	int num;//���Ӹ��� 
	char name[10];
	int sex;
	int birthday;
	int death_day;
	char education[20];
	char work[20];
	int dai;  //�ڼ��� 
}DataType;
DataType node[Maxx];


typedef struct TNode
{
	DataType data;//������ 
	struct TNode* nextstr[10];//ָ����,ָ���� 
	struct TNode* parent;//ָ����,ָ���� 
}PedTNode, * PedTree;//������


void Menu();//������ײ˵� 
void CreatePedTree(PedTree Tree);//�������� 
void AddChildInfor(PedTree Tree);//�����Ů����Ϣ
bool SearchPedTree(PedTree Tree, char Name[], PedTree* DrawTree);//�����в���
void ChangeInfor(PedTree Tree);//�޸ļ�����Ϣ
void _delbt(PedTree Tree);//�ݹ����ɾ�����ڼ����еı���
PedTree delbt(PedTree Tree, char* name);//ɾ��������Ϊname�ĳ�Ա�Լ�������
void FindInfor(PedTree Tree);//��������Ϊname�ĳ�Ա
void OutAllPedTree(PedTree Tree);//�������������Ϣ
void OutOneInfor(PedTree Tree);//�ݹ����ʵ�������������
void input_file(PedTree Tree);//���ļ��е���
void CreateNewPedTreeNode(PedTree Tree, int* k);//��������,�ݹ���� 
void CreatePedTree(PedTree Tree, int k);//����Pedigree��
void Statistics();	//ͳ��
void output_file(PedTree Tree);
void _output_file(PedTree Tree, FILE* fp);


char Name[Maxx][Maxx], Education[Maxx][Maxx], Work[Maxx][Maxx];
int  Num[Maxx], Sex[Maxx], Birthday[Maxx], Deathday[Maxx], Dai[Maxx], Flag = 0;

int main() {
	char choice;
	char name1[Maxx];
	system("color 1f");
	PedTNode TreeNode;
	PedTree Tree = &TreeNode;
	while (1)
	{
		fflush(stdin);//������̻����� 
		system("cls");
		Menu();
		printf("\n");
		printf("\t\t����ѡ��:");
		choice = getchar();
		switch (choice)
		{
		case '1':
			CreatePedTree(Tree);//�������� 
			break;
		case '2':
			AddChildInfor(Tree);//�����Ů����Ϣ
			break;
		case '3':
			ChangeInfor(Tree);//�޸ļ�����Ϣ
			break;
		case '4':
			printf("\n\t\t�������ɾ����Ա��������");//ɾ��������Ϊname�ĳ�Ա�Լ�������
			scanf("%s", name1);
			Tree = delbt(Tree, name1);
			break;
		case '5':
			OutAllPedTree(Tree);//�������������Ϣ
			break;
		case '6':
			FindInfor(Tree);//����ĳ���ĳ�Ա
			break;
		case '7':
			input_file(Tree);//���ļ��е���
			break;
		case '8':
			output_file(Tree);//������ļ�
			break;
		case '9':
			Statistics();//ͳ��
			break;
		case '0':
			return 0;//�˳�
		}
	}
}
void Menu()
{
	printf("\n\t\t------------------���׹���ϵͳ-----------------\n\n");  //˵���ô����ʵ�ֹ���
	printf("\t\t* * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t*                                           *\n");
	printf("\t\t*         ������Ϣ����˵�                  *\n");
	printf("\t\t*                                           *\n");
	printf("\t\t*          1:�������ף����ȣ�               *\n");
	printf("\t\t*          2:����µļ�ͥ��Ա               *\n");
	printf("\t\t*          3:�޸�ĳ���˵���Ϣ               *\n");
	printf("\t\t*          4:ɾ����Ϊname�ĳ�Ա             *\n");
	printf("\t\t*          5:�������������Ϣ               *\n");
	printf("\t\t*          6:����ĳ���˵���Ϣ               *\n");
	printf("\t\t*          7:���ļ��е���                   *\n");
	printf("\t\t*          8:������ļ�                     *\n");
	printf("\t\t*          9:ͳ�Ƽ�����Ϣ                   *\n");
	printf("\t\t*          0:�˳���������                   *\n");
	printf("\t\t*                                           *\n");
	printf("\t\t* * * * * * * * * * * * * * * * * * * * * * *\n");
}


void CreatePedTree(PedTree Tree)//�������� 
{
	printf("\n\t\t������Ҫ��ӵ����ȵ�������");
	fflush(stdin);//������̻�����
	scanf("%s", Tree->data.name);
	printf("\n\t\t������������ȵ��Ա�1�У�-1Ů����");
	fflush(stdin);//������̻�����  
	scanf("%d", &Tree->data.sex);
	printf("\n\t\t������Ҫ��ӵ����ȵĳ������ڣ�");
	fflush(stdin);//������̻�����
	scanf("%d", &Tree->data.birthday);
	printf("\n\t\t������Ҫ��ӵ����ȵ��������ڣ�δ����д0����");
	fflush(stdin);//������̻�����
	scanf("%d", &Tree->data.death_day);
	printf("\n\t\t������Ҫ��ӵ����ȵ�ѧ����");
	fflush(stdin);//������̻�����
	scanf("%s", Tree->data.education);
	printf("\n\t\t������Ҫ��ӵ����ȵĹ�����");
	fflush(stdin);//������̻�����
	scanf("%s", Tree->data.work);
	Tree->data.num = 0;
	Tree->parent = NULL;
	if (Tree->data.death_day != 0) {
		all_life_expe += int((Tree->data.death_day - Tree->data.birthday) / 10000);
		com_peo++;
	}	//�������ڼ���������/10000�õ���������
	if (Tree->data.sex == 1) {
		man++;
	}
	else if (Tree->data.sex == -1)
	{
		woman++;
	}
	printf("\n\n\t\t- - - - ���׽���ɹ�- - - - - \n");
	printf("\n\t\t�������������");
	fflush(stdin);
	getch();
}


void AddChildInfor(PedTree Tree)//�����Ů����Ϣ 
{
	fflush(stdin);//������̻����� 
	system("cls");
	char Name[20];
	PedTree TempTree = NULL;
	printf("\n\t\t������Ҫ�����Ů�ĸ�ĸ�����֣�");
	scanf("%s", Name);
	/*if((TempTree=SearchPedTree(Tree,Name))==NULL)*/
	if (SearchPedTree(Tree, Name, &TempTree))//�����в��� 
	{
		PedTree ChildTree;
		int num = TempTree->data.num;
		TempTree->nextstr[num] = (PedTree)malloc(sizeof(PedTNode));//��ĸָ���� 
		ChildTree = TempTree->nextstr[num];
		if (!ChildTree)
		{
			printf("\t\t�ڴ治��!\n");
			exit(1);
		}
		printf("\n\t\t������Ҫ��ӵ���Ů��������");
		fflush(stdin);//������̻�����
		scanf("%s", ChildTree->data.name);
		printf("\n\t\t�����������Ů���Ա�1�У�-1Ů����");
		fflush(stdin);//������̻�����  
		scanf("%d", &ChildTree->data.sex);
		printf("\n\t\t������Ҫ��ӵ���Ů�ĳ������ڣ�");
		fflush(stdin);//������̻�����
		scanf("%d", &ChildTree->data.birthday);
		printf("\n\t\t������Ҫ��ӵ���Ů���������ڣ�δ����д0����");
		fflush(stdin);//������̻�����
		scanf("%d", &ChildTree->data.death_day);
		printf("\n\t\t������Ҫ��ӵ���Ů��ѧ����");
		fflush(stdin);//������̻�����
		scanf("%s", ChildTree->data.education);
		printf("\n\t\t������Ҫ��ӵ���Ů�Ĺ�����");
		scanf("%s", ChildTree->data.work);
		fflush(stdin);//������̻�����
		ChildTree->data.dai = TempTree->data.dai + 1;
		(TempTree->data.num)++;//��ĸ��������1 
		ChildTree->parent = TempTree;//����ָ��ĸ
		ChildTree->data.num = 0;
		if (ChildTree->data.death_day != 0) {
			all_life_expe += int((ChildTree->data.death_day - ChildTree->data.birthday) / 10000);
			com_peo++;
		}	//�������ڼ���������/10000�õ���������
		if (ChildTree->data.sex == 1) {
			man++;
		}
		else if (ChildTree->data.sex == -1)
		{
			woman++;
		}
		printf("\n\n\t\t- - - - ��Ů��Ϣ��ӳɹ�- - - - - \n");
	}
	else {
		printf("\n\n\t\t�����ڸø�ĸ��\n");
	}
	fflush(stdin);//������̻����� 
	printf("\n\t\t�������������");
	getch();
}


bool SearchPedTree(PedTree Tree, char Name[], PedTree* DrawTree)//�����в��� 
{
	if (Tree == NULL) {
		return false;
	}
	if (strcmp(Tree->data.name, Name) == 0)
	{
		*DrawTree = Tree;
		return true;
	}
	else
	{
		for (int i = 0; i < Tree->data.num; i++)
		{
			if (SearchPedTree(Tree->nextstr[i], Name, DrawTree))
				return true;
		}
		return false;
	}
}


void ChangeInfor(PedTree Tree)//�޸ļ�����Ϣ 
{
	fflush(stdin);//������̻����� 
	system("cls");
	char Name[20];
	char choice;// 
	int tempch;
	char TempName[20];
	int TempData1;
	int TempData2;
	char TempData3[20];
	char TempData4[20];
	PedTree TempTree;
	printf("\n\t\t������Ҫ�޸��˵�������");
	scanf("%s", Name);
	if (SearchPedTree(Tree, Name, &TempTree))
	{
		PedTree TempParent = TempTree->parent;
		fflush(stdin);//������̻����� 
		system("cls");
		printf("\n\t\t������Ҫ�޸��˵�������������Ҫ�޸�����0��\n\t\t");
		scanf("%s", TempName);
		if (strcmp(TempName, "0") != 0)
			strcpy(TempTree->data.name, TempName);
		fflush(stdin);//������̻�����
		printf("\n\t\t������Ҫ�޸��˵��Ա𣺣�1�У�-1Ů��\n\t\t");
		scanf("%d", &tempch);
		if (tempch != '0')
			TempTree->data.sex = tempch;
		if (Tree->data.sex == 1) {
			man++;
			woman--;
		}
		else if (Tree->data.sex == -1)
		{
			woman++;
			man--;
		}
		fflush(stdin);//������̻����� 
		printf("\n\t\t������Ҫ�޸��˵ĳ������ڣ�������Ҫ�޸�����0��\n\t\t");
		scanf("%d", &TempData1);
		if (TempData1 != 0)
			TempTree->data.birthday = TempData1;
		printf("\n\t\t������Ҫ�޸��˵��������ڣ�������Ҫ�޸�����0��\n\t\t");
		scanf("%d", &TempData2);
		if (TempData2 != 0)
			TempTree->data.death_day = TempData2;
		printf("\n\t\t������Ҫ�޸��˵�ѧ����������Ҫ�޸�����0��\n\t\t");
		scanf("%s", TempData3);
		if (strcmp(TempData3, "0") != 0)
			strcpy(TempTree->data.education, TempData3);
		fflush(stdin);//������̻�����	
		printf("\n\t\t������Ҫ�޸��˵Ĺ�����������Ҫ�޸�����0��\n\t\t");
		scanf("%s", TempData4);
		if (strcmp(TempData4, "0") != 0)
			strcpy(TempTree->data.work, TempData4);
		printf("\n\t\t----****---***---��Ϣ�޸ĳɹ�---***----****-----");
		fflush(stdin);//������̻����� 
		printf("\n\t\t�������������");
		getch();
	}
	else
		printf("\n\t\t�Ҳ�����Ҫ���ҵ��ˣ�\n");
	fflush(stdin);//������̻����� 
	printf("\n\t\t�������������");
	getch();
}

void _delbt(PedTree Tree) {
	if (strcmp(Tree->data.name, "0") != 0)
	{
		if (Tree->data.sex == 1) {
			man--;
		}
		else if (Tree->data.sex == -1)
		{
			woman--;
		}
	}
	for (int i = 0; i < Tree->data.num; i++)
	{
		if (((Tree->nextstr[i])->data.sex) == 1)
			man--;
		else if (((Tree->nextstr[i])->data.sex) == -1)
			woman--;
	}
	for (int j = 0; j < Tree->data.num; j++)
		_delbt(Tree->nextstr[j]);
}
PedTree delbt(PedTree Tree, char* name)//ɾ��������Ϊname�ĳ�Ա�Լ�������
{
	PedTree TempTree = NULL;
	int i;
	if (SearchPedTree(Tree, name, &TempTree))
	{
		if (strcmp(TempTree->data.name, "0") != 0)
			if (TempTree->data.sex == 1) {
				man--;
			}
			else if (TempTree->data.sex == -1)
			{
				woman--;
			}
		for (int i = 0; i < TempTree->data.num; i++)
		{	
			if (((TempTree->nextstr[i])->data.sex) == 1)
				man--;
			else if (((TempTree->nextstr[i])->data.sex) == -1)
				woman--;
		}
		for (int j = 0; j < TempTree->data.num; j++)
			_delbt(TempTree->nextstr[j]);
		delete TempTree;
		TempTree = NULL;
		printf("\n\t\tɾ���ɹ�");
		fflush(stdin);//������̻����� 
		printf("\n\t\t�������������");
		getch();
		return Tree;
	}
	else
	{
		printf("\n\n\t\t----*----*----*----*----*----*----*----*----*----*----\n\n");
		printf("\t\t***�ü���ͼ��û��%s����˵���Ϣ��ȷ���Ƿ�������ȷ***\n\n", name);
		printf("\t\t----*----*----*----*----*----*----*----*----*----*----\n\n");
		fflush(stdin);//������̻����� 
		printf("\n\t\t�������������");
		getch();
		return Tree;
	}
}


void FindInfor(PedTree Tree)//��������Ϊname�ĳ�Ա
{
	fflush(stdin);//������̻����� 
	system("cls");
	char Name[20];
	char choice;// 
	int tempch;
	char TempName[20];
	char TempData[20];
	int n;
	PedTree TempTree;
	printf("\n\t\t������Ҫ�����˵�������");
	scanf("%s", Name);
	if (SearchPedTree(Tree, Name, &TempTree))
	{
		//PedTree TempParent = TempTree->parent;
		system("cls");
		printf("\n\t\t----****---***---�����˵���Ϣ---***----****-----");
		printf("\n\t\t�����˵�������%s\n\t\t", TempTree->data.name);
		printf("\n\t\t�����˵��Ա�%d\n\t\t", TempTree->data.sex);
		printf("\n\t\t�����˵ĳ������ڣ�%d\n\t\t", TempTree->data.birthday);
		printf("\n\t\t�����˵���������:%d\n\t\t", TempTree->data.death_day);
		printf("\n\t\t�����˵�ѧ����%s\n\t\t", TempTree->data.education);
		printf("\n\t\t�����˵Ĺ�����%s\n\t\t", TempTree->data.work);
		printf("\n\t\t----****---***---��Ϣչʾ���---***----****-----");
		fflush(stdin);//������̻����� 
		printf("\n\t\t�������������");
		getch();
	}
	else {
		printf("\n\t\t�Ҳ�����Ҫ���ҵ��ˣ�\n");
		fflush(stdin);//������̻����� 
		printf("\n\t\t�������������");
		getch();
	}
}


void OutAllPedTree(PedTree Tree)//�������������Ϣ 
{
	fflush(stdin);//������̻����� 
	system("cls");
	printf("\n\n\t\t����������Ҫ����Ϣ���£�\n");
	printf("\n\t\t---***---***---***---***---***---***---\n");
	if (strlen(Tree->data.name) < 10) {
		if (strcmp(Tree->data.name, "0") != 0)
			printf("\t\t������%s  ", Tree->data.name);
	}
	for (int i = 0; i < Tree->data.num; i++)
	{
		if (strlen(Tree->nextstr[i]->data.name) < 10) {
			printf("\t\t��%d����Ů��������%s  ", i + 1, (Tree->nextstr[i])->data.name);
			if (((Tree->nextstr[i])->data.sex) == 1)
				printf("�Ա���\n");
			else if (((Tree->nextstr[i])->data.sex) == -1)
				printf("�Ա�Ů\n");
		}
	}
	for (int j = 0; j < Tree->data.num; j++)
		OutOneInfor(Tree->nextstr[j]);
	fflush(stdin);//������̻����� 
	printf("\n\t\t�������������");
	getch();
}

void OutOneInfor(PedTree Tree)//�ݹ����ʵ�������������
{
	if (strcmp(Tree->data.name, "0") != 0)
	{
		if (strlen(Tree->data.name) < 10) {
			printf("\n\t\t---***---***---***---***---***---***---\n");
			printf("\t\t������%s  ", Tree->data.name);
		}
	}
	for (int i = 0; i < Tree->data.num; i++)
	{
		if (strlen(Tree->nextstr[i]->data.name) < 10) {
			if (strcmp((Tree->nextstr[i])->data.name, "0") != 0)
				printf("\t\t��%d����Ů��������%s  ", i + 1, (Tree->nextstr[i])->data.name);
			if (((Tree->nextstr[i])->data.sex) == 1)
				printf("�Ա���\n");
			else if (((Tree->nextstr[i])->data.sex) == -1)
				printf("�Ա�Ů\n");
		}
	}
	printf("\n");
	for (int j = 0; j < Tree->data.num; j++)
		OutOneInfor(Tree->nextstr[j]);
}

void input_file(PedTree Tree) {		//�����ļ�
	FILE* fp;
	int i = 0;
	fp = fopen("C:/Users/jkl13/Desktop/����1.txt", "r");
	if (fp == NULL)
	{
		printf("can not open file\n");
		exit(0);
	}
	while (i < Maxx) {
		fscanf(fp, "%d%s%d%d%d%s%s%d\n", &node[i].num, &node[i].name, &node[i].sex, &node[i].birthday,
			&node[i].death_day, &node[i].education, &node[i].work, &node[i].dai);
		if (node[i].death_day != 0) {
			all_life_expe += int((node[i].death_day - node[i].birthday) / 10000);
			com_peo++;
		}	//�������ڼ���������/10000�õ���������
		if (node[i].sex == 1) {
			man++;
		}
		else if(node[i].sex == -1)
		{
			woman++;
		}
		i++;
	}
	fclose(fp);
	CreatePedTree(Tree, 0);
}

void CreatePedTree(PedTree Tree, int k)//����Pedigree�� 
{
	fflush(stdin);//������̻����� 
	system("cls");
	Tree->data = node[k];
	k++;
	Tree->parent = NULL;

	for (int i = 0; i < Tree->data.num; i++)
	{
		printf("\n");
		PedTree ChildTree = (PedTree)malloc(sizeof(PedTNode));
		if (!ChildTree)
		{
			printf("Insufficient Memory!\n");
			exit(-1);
		}
		Tree->nextstr[i] = ChildTree;//ָ����Ů 
		ChildTree->data = node[k];
		k++;
		ChildTree->parent = Tree;//������ָ��ĸ 
		CreateNewPedTreeNode(ChildTree, &k);
	}
	fflush(stdin);//������̻����� 
	printf("\n\n\t\t- - - - ���׽���ɹ�- - - - - \n");
	printf("\n\t\t�������������");
	getch();
}

void CreateNewPedTreeNode(PedTree Tree, int* k)//��������,�ݹ���� 
{
	for (int i = 0; i < Tree->data.num; i++)
	{
		printf("\n");
		PedTree ChildTree = (PedTree)malloc(sizeof(PedTNode));
		if (!ChildTree)
		{
			printf("\t\tInsufficient Memory!\n");
			exit(1);
		}
		Tree->nextstr[i] = ChildTree;//ָ����Ů 
		ChildTree->data = node[*k];
		(*k)++;
		ChildTree->parent = Tree;//������ָ��ĸ 
		CreateNewPedTreeNode(ChildTree, k);
	}
}

void Statistics() {		//ͳ��
	double aver_life_expe;
	aver_life_expe = all_life_expe / com_peo;
	printf("ƽ������Ϊ��%.2lf\t", aver_life_expe);
	printf("��Ů����Ϊ��%d��%d\n", man, woman);
	fflush(stdin);//������̻����� 
	printf("\n\t\t�������������");
	getch();
}

void _output_file(PedTree Tree, FILE* fp) {
	fprintf(fp, "%d %s %d %d %d %s %s %d\n", Tree->data.num,Tree->data.name, Tree->data.sex,
		Tree->data.birthday, Tree->data.death_day, Tree->data.education, Tree->data.work, Tree->data.num);
	for (int i = 0; i < Tree->data.num; i++) {
		if (Tree->nextstr[i] != NULL)		_output_file(Tree->nextstr[i], fp);
	}
}

void output_file(PedTree Tree) {		//�����ļ�
	FILE* fp;
	if ((fp = fopen("C:/Users/jkl13/Desktop/����.txt", "a")) == NULL) {
		printf("cannot open file\n");
		return;
	}
	_output_file(Tree, fp);
	printf("����ɹ�!\n");
	fflush(stdin);//������̻����� 
	printf("\n\t\t�������������");
	getch();
	fclose(fp);
	fp = NULL;
	free(fp);
}