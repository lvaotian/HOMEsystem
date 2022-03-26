#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<conio.h> 
#define OK 1 
#define FALSE 0 
#define ERROR -1 
#define Maxx 50
#define DAI 5   //记录该宗族的最新一代 
typedef int status;
int man = 0, woman = 0, all_life_expe = 0, peo = 0, com_peo = 0;
typedef struct
{
	int num;//孩子个数 
	char name[10];
	int sex;
	int birthday;
	int death_day;
	char education[20];
	char work[20];
	int dai;  //第几代 
}DataType;
DataType node[Maxx];


typedef struct TNode
{
	DataType data;//数据域 
	struct TNode* nextstr[10];//指针域,指向孩子 
	struct TNode* parent;//指针域,指向父亲 
}PedTNode, * PedTree;//家谱树


void Menu();//输出家谱菜单 
void CreatePedTree(PedTree Tree);//创建祖先 
void AddChildInfor(PedTree Tree);//添加子女的信息
bool SearchPedTree(PedTree Tree, char Name[], PedTree* DrawTree);//在树中查找
void ChangeInfor(PedTree Tree);//修改家谱信息
void _delbt(PedTree Tree);//递归调用删除其在家谱中的比例
PedTree delbt(PedTree Tree, char* name);//删除掉名字为name的成员以及其子孙
void FindInfor(PedTree Tree);//查找名字为name的成员
void OutAllPedTree(PedTree Tree);//输出整个家谱信息
void OutOneInfor(PedTree Tree);//递归调用实现输出整个家谱
void input_file(PedTree Tree);//从文件中导入
void CreateNewPedTreeNode(PedTree Tree, int* k);//创建孩子,递归调用 
void CreatePedTree(PedTree Tree, int k);//创建Pedigree树
void Statistics();	//统计
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
		fflush(stdin);//清除键盘缓冲区 
		system("cls");
		Menu();
		printf("\n");
		printf("\t\t请您选择:");
		choice = getchar();
		switch (choice)
		{
		case '1':
			CreatePedTree(Tree);//创建祖先 
			break;
		case '2':
			AddChildInfor(Tree);//添加子女的信息
			break;
		case '3':
			ChangeInfor(Tree);//修改家谱信息
			break;
		case '4':
			printf("\n\t\t请输入待删除人员的姓名：");//删除掉名字为name的成员以及其子孙
			scanf("%s", name1);
			Tree = delbt(Tree, name1);
			break;
		case '5':
			OutAllPedTree(Tree);//输出整个家谱信息
			break;
		case '6':
			FindInfor(Tree);//查找某个的成员
			break;
		case '7':
			input_file(Tree);//从文件中导入
			break;
		case '8':
			output_file(Tree);//保存进文件
			break;
		case '9':
			Statistics();//统计
			break;
		case '0':
			return 0;//退出
		}
	}
}
void Menu()
{
	printf("\n\t\t------------------家谱管理系统-----------------\n\n");  //说明该代码的实现功能
	printf("\t\t* * * * * * * * * * * * * * * * * * * * * * *\n");
	printf("\t\t*                                           *\n");
	printf("\t\t*         家谱信息管理菜单                  *\n");
	printf("\t\t*                                           *\n");
	printf("\t\t*          1:创建家谱（祖先）               *\n");
	printf("\t\t*          2:添加新的家庭成员               *\n");
	printf("\t\t*          3:修改某个人的信息               *\n");
	printf("\t\t*          4:删除名为name的成员             *\n");
	printf("\t\t*          5:输出整个家谱信息               *\n");
	printf("\t\t*          6:查找某个人的信息               *\n");
	printf("\t\t*          7:从文件中导入                   *\n");
	printf("\t\t*          8:保存进文件                     *\n");
	printf("\t\t*          9:统计家谱信息                   *\n");
	printf("\t\t*          0:退出整个程序                   *\n");
	printf("\t\t*                                           *\n");
	printf("\t\t* * * * * * * * * * * * * * * * * * * * * * *\n");
}


void CreatePedTree(PedTree Tree)//创建祖先 
{
	printf("\n\t\t请输入要添加的祖先的姓名：");
	fflush(stdin);//清除键盘缓冲区
	scanf("%s", Tree->data.name);
	printf("\n\t\t请输入添加祖先的性别（1男，-1女）：");
	fflush(stdin);//清除键盘缓冲区  
	scanf("%d", &Tree->data.sex);
	printf("\n\t\t请输入要添加的祖先的出生日期：");
	fflush(stdin);//清除键盘缓冲区
	scanf("%d", &Tree->data.birthday);
	printf("\n\t\t请输入要添加的祖先的死亡日期（未死亡写0）：");
	fflush(stdin);//清除键盘缓冲区
	scanf("%d", &Tree->data.death_day);
	printf("\n\t\t请输入要添加的祖先的学历：");
	fflush(stdin);//清除键盘缓冲区
	scanf("%s", Tree->data.education);
	printf("\n\t\t请输入要添加的祖先的工作：");
	fflush(stdin);//清除键盘缓冲区
	scanf("%s", Tree->data.work);
	Tree->data.num = 0;
	Tree->parent = NULL;
	if (Tree->data.death_day != 0) {
		all_life_expe += int((Tree->data.death_day - Tree->data.birthday) / 10000);
		com_peo++;
	}	//死亡日期减出生日期/10000得到寿命长度
	if (Tree->data.sex == 1) {
		man++;
	}
	else if (Tree->data.sex == -1)
	{
		woman++;
	}
	printf("\n\n\t\t- - - - 家谱建造成功- - - - - \n");
	printf("\n\t\t按任意键继续：");
	fflush(stdin);
	getch();
}


void AddChildInfor(PedTree Tree)//添加子女的信息 
{
	fflush(stdin);//清除键盘缓冲区 
	system("cls");
	char Name[20];
	PedTree TempTree = NULL;
	printf("\n\t\t请输入要添加子女的父母的名字：");
	scanf("%s", Name);
	/*if((TempTree=SearchPedTree(Tree,Name))==NULL)*/
	if (SearchPedTree(Tree, Name, &TempTree))//在树中查找 
	{
		PedTree ChildTree;
		int num = TempTree->data.num;
		TempTree->nextstr[num] = (PedTree)malloc(sizeof(PedTNode));//父母指向孩子 
		ChildTree = TempTree->nextstr[num];
		if (!ChildTree)
		{
			printf("\t\t内存不足!\n");
			exit(1);
		}
		printf("\n\t\t请输入要添加的子女的姓名：");
		fflush(stdin);//清除键盘缓冲区
		scanf("%s", ChildTree->data.name);
		printf("\n\t\t请输入添加子女的性别（1男，-1女）：");
		fflush(stdin);//清除键盘缓冲区  
		scanf("%d", &ChildTree->data.sex);
		printf("\n\t\t请输入要添加的子女的出生日期：");
		fflush(stdin);//清除键盘缓冲区
		scanf("%d", &ChildTree->data.birthday);
		printf("\n\t\t请输入要添加的子女的死亡日期（未死亡写0）：");
		fflush(stdin);//清除键盘缓冲区
		scanf("%d", &ChildTree->data.death_day);
		printf("\n\t\t请输入要添加的子女的学历：");
		fflush(stdin);//清除键盘缓冲区
		scanf("%s", ChildTree->data.education);
		printf("\n\t\t请输入要添加的子女的工作：");
		scanf("%s", ChildTree->data.work);
		fflush(stdin);//清除键盘缓冲区
		ChildTree->data.dai = TempTree->data.dai + 1;
		(TempTree->data.num)++;//父母孩子数加1 
		ChildTree->parent = TempTree;//孩子指向父母
		ChildTree->data.num = 0;
		if (ChildTree->data.death_day != 0) {
			all_life_expe += int((ChildTree->data.death_day - ChildTree->data.birthday) / 10000);
			com_peo++;
		}	//死亡日期减出生日期/10000得到寿命长度
		if (ChildTree->data.sex == 1) {
			man++;
		}
		else if (ChildTree->data.sex == -1)
		{
			woman++;
		}
		printf("\n\n\t\t- - - - 子女信息添加成功- - - - - \n");
	}
	else {
		printf("\n\n\t\t不存在该父母！\n");
	}
	fflush(stdin);//清除键盘缓冲区 
	printf("\n\t\t按任意键继续：");
	getch();
}


bool SearchPedTree(PedTree Tree, char Name[], PedTree* DrawTree)//在树中查找 
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


void ChangeInfor(PedTree Tree)//修改家谱信息 
{
	fflush(stdin);//清除键盘缓冲区 
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
	printf("\n\t\t请输入要修改人的姓名：");
	scanf("%s", Name);
	if (SearchPedTree(Tree, Name, &TempTree))
	{
		PedTree TempParent = TempTree->parent;
		fflush(stdin);//清除键盘缓冲区 
		system("cls");
		printf("\n\t\t请输入要修改人的姓名：（不需要修改输入0）\n\t\t");
		scanf("%s", TempName);
		if (strcmp(TempName, "0") != 0)
			strcpy(TempTree->data.name, TempName);
		fflush(stdin);//清除键盘缓冲区
		printf("\n\t\t请输入要修改人的性别：（1男，-1女）\n\t\t");
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
		fflush(stdin);//清除键盘缓冲区 
		printf("\n\t\t请输入要修改人的出生日期：（不需要修改输入0）\n\t\t");
		scanf("%d", &TempData1);
		if (TempData1 != 0)
			TempTree->data.birthday = TempData1;
		printf("\n\t\t请输入要修改人的死亡日期：（不需要修改输入0）\n\t\t");
		scanf("%d", &TempData2);
		if (TempData2 != 0)
			TempTree->data.death_day = TempData2;
		printf("\n\t\t请输入要修改人的学历：（不需要修改输入0）\n\t\t");
		scanf("%s", TempData3);
		if (strcmp(TempData3, "0") != 0)
			strcpy(TempTree->data.education, TempData3);
		fflush(stdin);//清除键盘缓冲区	
		printf("\n\t\t请输入要修改人的工作：（不需要修改输入0）\n\t\t");
		scanf("%s", TempData4);
		if (strcmp(TempData4, "0") != 0)
			strcpy(TempTree->data.work, TempData4);
		printf("\n\t\t----****---***---信息修改成功---***----****-----");
		fflush(stdin);//清除键盘缓冲区 
		printf("\n\t\t按任意键继续：");
		getch();
	}
	else
		printf("\n\t\t找不到你要查找的人！\n");
	fflush(stdin);//清除键盘缓冲区 
	printf("\n\t\t按任意键继续：");
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
PedTree delbt(PedTree Tree, char* name)//删除掉名字为name的成员以及其子孙
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
		printf("\n\t\t删除成功");
		fflush(stdin);//清除键盘缓冲区 
		printf("\n\t\t按任意键继续：");
		getch();
		return Tree;
	}
	else
	{
		printf("\n\n\t\t----*----*----*----*----*----*----*----*----*----*----\n\n");
		printf("\t\t***该家谱图中没有%s这个人的信息请确认是否输入正确***\n\n", name);
		printf("\t\t----*----*----*----*----*----*----*----*----*----*----\n\n");
		fflush(stdin);//清除键盘缓冲区 
		printf("\n\t\t按任意键继续：");
		getch();
		return Tree;
	}
}


void FindInfor(PedTree Tree)//查找名字为name的成员
{
	fflush(stdin);//清除键盘缓冲区 
	system("cls");
	char Name[20];
	char choice;// 
	int tempch;
	char TempName[20];
	char TempData[20];
	int n;
	PedTree TempTree;
	printf("\n\t\t请输入要查找人的姓名：");
	scanf("%s", Name);
	if (SearchPedTree(Tree, Name, &TempTree))
	{
		//PedTree TempParent = TempTree->parent;
		system("cls");
		printf("\n\t\t----****---***---查找人的信息---***----****-----");
		printf("\n\t\t查找人的姓名：%s\n\t\t", TempTree->data.name);
		printf("\n\t\t查找人的性别：%d\n\t\t", TempTree->data.sex);
		printf("\n\t\t查找人的出生日期：%d\n\t\t", TempTree->data.birthday);
		printf("\n\t\t查找人的死亡日期:%d\n\t\t", TempTree->data.death_day);
		printf("\n\t\t查找人的学历：%s\n\t\t", TempTree->data.education);
		printf("\n\t\t查找人的工作：%s\n\t\t", TempTree->data.work);
		printf("\n\t\t----****---***---信息展示完毕---***----****-----");
		fflush(stdin);//清除键盘缓冲区 
		printf("\n\t\t按任意键继续：");
		getch();
	}
	else {
		printf("\n\t\t找不到你要查找的人！\n");
		fflush(stdin);//清除键盘缓冲区 
		printf("\n\t\t按任意键继续：");
		getch();
	}
}


void OutAllPedTree(PedTree Tree)//输出整个家谱信息 
{
	fflush(stdin);//清除键盘缓冲区 
	system("cls");
	printf("\n\n\t\t整个家谱主要的信息如下：\n");
	printf("\n\t\t---***---***---***---***---***---***---\n");
	if (strlen(Tree->data.name) < 10) {
		if (strcmp(Tree->data.name, "0") != 0)
			printf("\t\t姓名：%s  ", Tree->data.name);
	}
	for (int i = 0; i < Tree->data.num; i++)
	{
		if (strlen(Tree->nextstr[i]->data.name) < 10) {
			printf("\t\t第%d个子女的姓名：%s  ", i + 1, (Tree->nextstr[i])->data.name);
			if (((Tree->nextstr[i])->data.sex) == 1)
				printf("性别：男\n");
			else if (((Tree->nextstr[i])->data.sex) == -1)
				printf("性别：女\n");
		}
	}
	for (int j = 0; j < Tree->data.num; j++)
		OutOneInfor(Tree->nextstr[j]);
	fflush(stdin);//清除键盘缓冲区 
	printf("\n\t\t按任意键继续：");
	getch();
}

void OutOneInfor(PedTree Tree)//递归调用实现输出整个家谱
{
	if (strcmp(Tree->data.name, "0") != 0)
	{
		if (strlen(Tree->data.name) < 10) {
			printf("\n\t\t---***---***---***---***---***---***---\n");
			printf("\t\t姓名：%s  ", Tree->data.name);
		}
	}
	for (int i = 0; i < Tree->data.num; i++)
	{
		if (strlen(Tree->nextstr[i]->data.name) < 10) {
			if (strcmp((Tree->nextstr[i])->data.name, "0") != 0)
				printf("\t\t第%d个子女的姓名：%s  ", i + 1, (Tree->nextstr[i])->data.name);
			if (((Tree->nextstr[i])->data.sex) == 1)
				printf("性别：男\n");
			else if (((Tree->nextstr[i])->data.sex) == -1)
				printf("性别：女\n");
		}
	}
	printf("\n");
	for (int j = 0; j < Tree->data.num; j++)
		OutOneInfor(Tree->nextstr[j]);
}

void input_file(PedTree Tree) {		//导入文件
	FILE* fp;
	int i = 0;
	fp = fopen("C:/Users/jkl13/Desktop/家谱1.txt", "r");
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
		}	//死亡日期减出生日期/10000得到寿命长度
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

void CreatePedTree(PedTree Tree, int k)//创建Pedigree树 
{
	fflush(stdin);//清除键盘缓冲区 
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
		Tree->nextstr[i] = ChildTree;//指向子女 
		ChildTree->data = node[k];
		k++;
		ChildTree->parent = Tree;//将孩子指向父母 
		CreateNewPedTreeNode(ChildTree, &k);
	}
	fflush(stdin);//清除键盘缓冲区 
	printf("\n\n\t\t- - - - 家谱建造成功- - - - - \n");
	printf("\n\t\t按任意键继续：");
	getch();
}

void CreateNewPedTreeNode(PedTree Tree, int* k)//创建孩子,递归调用 
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
		Tree->nextstr[i] = ChildTree;//指向子女 
		ChildTree->data = node[*k];
		(*k)++;
		ChildTree->parent = Tree;//将孩子指向父母 
		CreateNewPedTreeNode(ChildTree, k);
	}
}

void Statistics() {		//统计
	double aver_life_expe;
	aver_life_expe = all_life_expe / com_peo;
	printf("平均寿命为：%.2lf\t", aver_life_expe);
	printf("男女比例为：%d：%d\n", man, woman);
	fflush(stdin);//清除键盘缓冲区 
	printf("\n\t\t按任意键继续：");
	getch();
}

void _output_file(PedTree Tree, FILE* fp) {
	fprintf(fp, "%d %s %d %d %d %s %s %d\n", Tree->data.num,Tree->data.name, Tree->data.sex,
		Tree->data.birthday, Tree->data.death_day, Tree->data.education, Tree->data.work, Tree->data.num);
	for (int i = 0; i < Tree->data.num; i++) {
		if (Tree->nextstr[i] != NULL)		_output_file(Tree->nextstr[i], fp);
	}
}

void output_file(PedTree Tree) {		//导入文件
	FILE* fp;
	if ((fp = fopen("C:/Users/jkl13/Desktop/家谱.txt", "a")) == NULL) {
		printf("cannot open file\n");
		return;
	}
	_output_file(Tree, fp);
	printf("保存成功!\n");
	fflush(stdin);//清除键盘缓冲区 
	printf("\n\t\t按任意键继续：");
	getch();
	fclose(fp);
	fp = NULL;
	free(fp);
}