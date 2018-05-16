#define  _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>

#define NAME 64 
#define WORK_UNIT 128
#define TEL  20
#define  EMAIL 20
#define  ADD_USER 1
#define  DEL_USER 2
#define  SHOW_ALL_USERS 3
#define  MODIFY_USER 4 
#define  SORT_USERS 5
#define  FIND_USER 6
#define  EXIT     7
#define  SHOW_MENU 8
#define  EVER_EXEC 1
#define   DEL_ALL_USERS 9
#define  fileName "TelBooks.txt"
#define  LEN  1024

FILE  *fp = NULL;         // 文件流指针

int total = 0;            // 计算总共有多少联系人

						  // 电话簿信息结构体

typedef struct _TelBooks
{
	char name[NAME];                     //   人名
	char WorkUnit[WORK_UNIT];            //   工作单位
	char telphone[TEL];					 //   电话号码
	char email[EMAIL];					 //   email
	char LineFeed;                       //   换行
										 //	struct _TelBooks *next;              //   指针域
}TelBooks/*, *PTelBooks*/;

TelBooks Users[LEN];

// 初始化数据

void InitData()
{
	int i;
	for (i = 0; i<LEN; i++)
	{
		// 清空所有缓存区
		memset(&(Users[i]), 0x00, sizeof(TelBooks));
	}
}

// 显示菜单

void printMenu(void)
{
	printf("======================= 电话簿 ============================\n");
	printf("\n\t\t 1、添加电话号码\n\n");
	printf("\t\t 2、删除电话号码\n\n");
	printf("\t\t 3、显示所有电话号码\n\n");
	printf("\t\t 4、修改功能\n\n");
	printf("\t\t 5、电话号码排序\n\n");
	printf("\t\t 6、按条件查询电话号码\n\n");
	printf("\t\t 7、退出程序\n\n");
	printf("\t\t 8、显示电话簿操作菜单\n\n");
	printf("\t\t 9、删除所有联系人\n\n");
	printf("\n======================= 电话簿 ============================\n\n");

	printf("请选择菜单进行电话簿操作：\n\n\n\n");
}

// 添加新的联系人

void AddUser(void)
{
	TelBooks newUser;

	// 以追加方式打开文件
	fp = fopen(fileName, "a+");
	if (NULL == fp)
	{
		printf("打开 %s 出错\n", fileName);
		return;
	}

	// 清空新建联系人数据

	memset(&newUser, 0x00, sizeof(newUser));

	printf("请输入联系人的姓名 ：\n");
	//gets(temp.name);
	scanf("%s", newUser.name);
	printf("请输入联系人的工作单位 ：\n");
	//	gets(temp.WorkUnit);
	scanf("%s", newUser.WorkUnit);
	printf("请输入联系人的 Tel ：\n");
	//	gets(temp.telphone);
	scanf("%s", newUser.telphone);
	printf("请输入联系人的 emial ：\n");
	//	gets(temp.email);
	scanf("%s", newUser.email);

	// 换行符
	newUser.LineFeed = '\n';

	// 向文件中写入数据

	fwrite(&newUser, sizeof(newUser), 1, fp);

	// 联系人数加 1
	//total++;

	// 关闭文件
	fclose(fp);
}

// 按电话号码删除联系人信息
//
//     删除联系人的某个联系人思想是：
//     先把文件中的所有信息读入到结构体数组中，若遇到要删除的联系人信息，则不往结构体中读入，然后重新写入文件中

void DelUser(char *telphone)
{
	//int len=0, i=0;
	int i = 0;
	int total = 0;             // 记录结构体中保留的联系人的个数
	TelBooks DelUser;
	int size = sizeof(DelUser);
	memset(&DelUser, 0x00, sizeof(DelUser));

	// 以只读方式打开文件

	fp = fopen(fileName, "r");
	if (NULL == fp)
	{
		printf("打开 %s 出错\n", fileName);
		return;
	}

	//	 len = getTotalUser();          // 获取总的联系人数量

	// 初始化联系人结构体数组
	InitData();

	// 读数据并写入到结构体数组中

	while (fread(&DelUser, sizeof(TelBooks), 1, fp) != 0)
	{
		if (strcmp(telphone, DelUser.telphone) == 0)
		{
			continue;
		}
		else
		{
			Users[i] = DelUser;
			memset(&DelUser, 0x00, sizeof(TelBooks));
			i++;
		}
		total++;
	}

	// 关闭文件
	fclose(fp);

	// 重新打开文，并把结构体中的信息写入文件


	// 以只写的方式打开文件
	fp = fopen(fileName, "w+");
	if (NULL == fp)
	{
		printf("打开 %s 出错\n", fileName);
		return;
	}

	// 给文件中写入数据
	for (i = 0; i<total; i++)
	{
		fwrite(&Users[i], sizeof(TelBooks), 1, fp);
	}

	// 关闭文件
	fclose(fp);

}

// 删除所有联系人

void Del_All_Users(void)
{
	// 以只写的方式打开文件
	fp = fopen(fileName, "w+");
	if (NULL == fp)
	{
		printf("打开 %s 出错\n", fileName);
		return;
	}
	// 关闭文件
	fclose(fp);
}

// 显示所有保存的电话号码

void showAllUsers(void)
{
	// 以只读方式打开文件

	fp = fopen(fileName, "r");
	if (NULL == fp)
	{
		printf("打开 %s 出错\n", fileName);
		return;
	}

	TelBooks temp;
	memset(&temp, 0x00, sizeof(temp));

	// 设置文件指针指向文件首部
	fseek(fp, 0, SEEK_SET);

	while (fread(&temp, sizeof(temp), 1, fp) != 0)
	{
		printf("%s\t%s\t%s\t%s%c", temp.name, temp.WorkUnit, temp.telphone, temp.email, temp.LineFeed);

	}
	fclose(fp);
}

// 修改信息函数

void modifyInfo(TelBooks *modifyUser)
{
	TelBooks temp = *modifyUser;
	char ch;
	printf("是否需要修改联系人 %s 的姓名： Y/y --- 是，N/n --- 否 \n", modifyUser->name);
	//scanf("%c",&ch);

	ch = getchar();
	getchar();                   // 把回车读入 getchar() 中

								 // 刷新标准输入缓冲区
								 //fflush(stdin);

								 //getchar();                   // 把回车读入 getchar() 中
	if (ch == 'Y' || ch == 'y')
	{
		memset(temp.name, 0x00, sizeof(temp.name));
		printf("请输入修改后的姓名：\n");
		scanf("%s", temp.name);
	}
	getchar();                   // 把回车读入 getchar() 中
	printf("是否需要修改联系人 %s 的工作单位： Y/y --- 是，N/n --- 否 \n", modifyUser->name);
	//scanf("%c", &ch);
	//

	ch = getchar();
	getchar();                   // 把回车读入 getchar() 中

								 // 刷新标准输入缓冲区
								 //fflush(stdin);
	if (ch == 'Y' || ch == 'y')
	{
		memset(temp.WorkUnit, 0x00, sizeof(temp.WorkUnit));
		printf("请输入修改后的工作单位：\n");
		scanf("%s", temp.WorkUnit);
	}
	getchar();                   // 把回车读入 getchar() 中

	printf("是否需要修改联系人 %s 的 Tel ： Y/y --- 是，N/n --- 否 \n", modifyUser->name);
	//scanf("%c", &ch);
	ch = getchar();
	getchar();                   // 把回车读入 getchar() 中

	if (ch == 'Y' || ch == 'y')
	{
		memset(temp.telphone, 0x00, sizeof(temp.telphone));
		printf("请输入修改后的 Tel：\n");
		scanf("%s", temp.telphone);
	}
	getchar();                   // 把回车读入 getchar() 中
	printf("是否需要修改联系人 %s 的 email ： Y/y --- 是，N/n --- 否 \n", modifyUser->name);
	//scanf("%c", &ch);
	//getchar();                   // 把回车读入 getchar() 中
	ch = getchar();
	getchar();                   // 把回车读入 getchar() 中
								 // 刷新标准输入缓冲区
								 //	fflush(stdin);

	if (ch == 'Y' || ch == 'y')
	{
		memset(temp.email, 0x00, sizeof(temp.email));
		printf("请输入修改后的  emial：\n");
		scanf("%s", temp.email);
	}
	memset(modifyUser, 0x00, sizeof(TelBooks));
	*modifyUser = temp;
}

// 修改联系人信息
// 思想:先把所有联系人的信息读入到联系人的信息结构体中，然后在结构体中进行修改，然后重新写入到文件中
void ModifyUser(char *name)
{
	int i = 0;
	int total = 0;             // 记录结构体中保留的联系人的个数
	TelBooks modifyUser;
	int size = sizeof(modifyUser);
	memset(&modifyUser, 0x00, sizeof(modifyUser));

	// 以只读方式打开文件

	fp = fopen(fileName, "r");
	if (NULL == fp)
	{
		printf("打开 %s 出错\n", fileName);
		return;
	}

	//	 len = getTotalUser();          // 获取总的联系人数量

	// 初始化联系人结构体数组
	InitData();

	// 读数据并写入到结构体数组中

	while (fread(&modifyUser, sizeof(TelBooks), 1, fp) != 0)
	{
		Users[i] = modifyUser;
		memset(&modifyUser, 0x00, sizeof(TelBooks));
		i++;
		total++;
	}

	// 关闭文件
	fclose(fp);

	// 在结构体数组中进行遍历，寻找复合条件的联系人

	for (i = 0; i<total; i++)
	{
		// 如果找到要修改的联系人的信息，则对联系人进行信息修改，然后，退出循环
		if (strcmp(name, Users[i].name) == 0)
		{
			modifyInfo(&Users[i]);
			break;
		}
	}

	// 重新打开文，并把结构体中的信息写入文件

	// 以只写的方式打开文件
	fp = fopen(fileName, "w+");
	if (NULL == fp)
	{
		printf("打开 %s 出错\n", fileName);
		return;
	}

	// 给文件中写入数据
	for (i = 0; i<total; i++)
	{
		fwrite(&Users[i], sizeof(TelBooks), 1, fp);
	}

	// 关闭文件
	fclose(fp);

}

// 查询功能

void FindUser(void)
{
	// 以只读方式打开文件

	fp = fopen(fileName, "r");
	if (NULL == fp)
	{
		printf("打开 %s 出错\n", fileName);
		return;
	}

	TelBooks findUser;                       // 定义查询联系人的缓冲区变量   
	int index = -1;                          // 定义一个  index 变量来进行选择是按 人名查询电话号码，还是按 电话号码查询联系人的信息
	char findContext[NAME] = "";             // 定义一个查询内容的变量，即按什么查找

											 // 给换缓冲区变量清空
	memset(&findUser, 0x00, sizeof(findUser));
	// index = 1 表示 按人名来查找电话号码

	printf("请输入：\n0 ------ 表示按人名来查找电话号码\n1 ------ 表示按电话号码来查询联系人信息\n");
	scanf("%d", &index);

	// 设置文件指针为文件首部
	fseek(fp, 0, SEEK_SET);
	if (index == 0)     // 按人名 来查找电话号码
	{
		printf("请输入要查询电话的人名：\n");
		scanf("%s", findContext);
		while ((fread(&findUser, sizeof(findUser), 1, fp) != EOF) && (strcmp(findContext, findUser.name) != 0));

		printf("%d\n", strcmp(findContext, findUser.name));
		printf("%s\t%s\t%s\t%s\t%c", findUser.name, findUser.WorkUnit, findUser.telphone, findUser.email, findUser.LineFeed);
		if ((strcmp(findContext, findUser.name) == 0))           // 表示输入姓名后，找到对应的电话号码
		{

			// 显示电话号码到屏幕
			printf("%s 的电话号码是： %s\n", findUser.name, findUser.telphone);
		}
		else   // 表示没有找电话号码
		{
			printf("在电话簿中没有找到姓名为 %s 的电话号码!!!\n", findContext);
		}
	}
	else if (index == 1)
	{
		printf("请输入要查询的电话号码：\n");
		scanf("%s", findContext);
		while ((fread(&findUser, sizeof(findUser), 1, fp) != EOF) && (strcmp(findContext, findUser.telphone) != 0));


		printf("%d\n", strcmp(findContext, findUser.telphone));
		printf("%s\t%s\t%s\t%s\t%c", findUser.name, findUser.WorkUnit, findUser.telphone, findUser.email, findUser.LineFeed);

		if ((strcmp(findContext, findUser.telphone) == 0))           // 表示输入电话号码后，找到对应的联系人姓名
		{
			// 显示联系人姓名到屏幕
			printf("电话号码为 %s 的联系人的姓名为 ： %s\n", findUser.telphone, findUser.name);
		}
		else   // 表示没有找电话号码
		{
			printf("在电话簿中没有找到电话为 %s 的联系人!!\n", findContext);
		}
	}
	else
	{
		memset(findContext, 0x00, sizeof(findContext));
		return;
	}
	memset(findContext, 0x00, sizeof(findContext));

	// 关闭文件
	fclose(fp);
}


// 遍历电话簿查询总共有多少联系人

int getTotalUser(void)
{
	// 以只读方式打开文件

	fp = fopen(fileName, "r");
	if (NULL == fp)
	{
		printf("打开 %s 出错\n", fileName);
		return 0;
	}

	int total = 0;   // 统计总共有多少联系人
	TelBooks temp;   // 遍历电话簿缓存数据 

					 // 设置文件指针，指向文件的开始部分
	fseek(fp, 0, SEEK_SET);

	while (fread(&temp, sizeof(temp), 1, fp) != 0)
	{
		total++;
	}

	// 关闭文件
	fclose(fp);
	return total;
}

// 按电话号码排序

void sort_by_telphone(int len)
{
	// 以读方式打开文件
	fp = fopen(fileName, "r");
	if (NULL == fp)
	{
		printf("打开 %s 出错\n", fileName);
		return;
	}

	TelBooks temp;

	int i = 0, j = 0;

	// 设置文件指针，指向文件的开始部分
	fseek(fp, 0, SEEK_SET);

	memset(&temp, 0x00, sizeof(temp));
	// 把所有联系人的信息读入  TelBooks Users[LEN] 结构体数组中，再进行冒泡排序

	while (fread(&temp, sizeof(temp), 1, fp) != 0)
	{
		Users[i] = temp;
		i++;
	}

	// 对联系人进行冒泡排序，然后写入文件,从小到大排序

	for (i = 0; i<len - 1; i++)
	{
		for (j = 0; j<len - i - 1; j++)
		{
			TelBooks t;
			if (strcmp(Users[j].telphone, Users[j + 1].telphone)>0)
			{
				t = Users[j];
				Users[j] = Users[j + 1];
				Users[j + 1] = t;
			}
		}
	}
	fclose(fp);

	// 以只写的方式打开文件
	fp = fopen(fileName, "w");
	if (NULL == fp)
	{
		printf("打开 %s 出错\n", fileName);
		return;
	}

	// 把排序后的结果写入文件中
	for (i = 0; i<len; i++)
	{
		if (strcmp(Users[i].name, "") == 0)
		{
			//	空数据，不往文件中写数据
			continue;
		}
		fwrite(&(Users[i]), sizeof(TelBooks), 1, fp);
	}

	fclose(fp);
}

// 按姓名号码排序

void sort_by_name(int len)
{
	// 以读方式打开文件
	fp = fopen(fileName, "r");
	if (NULL == fp)
	{
		printf("打开 %s 出错\n", fileName);
		return;
	}

	TelBooks temp;

	int i = 0, j = 0;

	// 设置文件指针，指向文件的开始部分
	fseek(fp, 0, SEEK_SET);

	memset(&temp, 0x00, sizeof(temp));
	// 把所有联系人的信息读入  TelBooks Users[LEN] 结构体数组中，再进行冒泡排序

	while (fread(&temp, sizeof(temp), 1, fp) != 0)
	{
		Users[i] = temp;
		i++;
	}

	// 对联系人进行冒泡排序，然后写入文件,从小到大排序

	for (i = 0; i<len - 1; i++)
	{
		for (j = 0; j<len - i - 1; j++)
		{
			TelBooks t;
			if (strcmp(Users[j].name, Users[j + 1].name)>0)
			{
				t = Users[j];
				Users[j] = Users[j + 1];
				Users[j + 1] = t;
			}
		}
	}
	fclose(fp);

	// 以只写的方式打开文件
	fp = fopen(fileName, "w");
	if (NULL == fp)
	{
		printf("打开 %s 出错\n", fileName);
		return;
	}

	// 把排序后的结果写入文件中
	for (i = 0; i<len; i++)
	{
		if (strcmp(Users[i].name, "") == 0)
		{
			//	空数据，不往文件中写数据
			continue;
		}
		fwrite(&(Users[i]), sizeof(TelBooks), 1, fp);
	}

	fclose(fp);
}

// 排序

void sort(int flag)
{
	int len = getTotalUser();              // 获取总的联系人数量 

										   // 如果 flag = 0 的话，以电话号码进行排序；否则，按姓名排序
	if (flag == 0)
	{
		sort_by_telphone(len);
	}
	else
	{
		sort_by_name(len);
	}
}


// 程序的各个功能模块操作

void Operate_TelBook()
{
	int menu;          // 定义菜单选项
	char ch;           // 表示是否继续操作  Y/y ------ 继续操作  N/n ------ 退出程序
	InitData();
	printMenu();

	scanf("%d", &menu);

	while (EVER_EXEC)
	{
		switch (menu)
		{
			// 添加新的联系人信息
		case ADD_USER:
		{	AddUser();
		break;
		}
		// 按电话号码删除联系人信息
		case DEL_USER:
		{
			char name[NAME] = "";
			printf("请输入要删除的人的电话号码：\n");
			scanf("%s", name);
			DelUser(name);
		}	break;
		// 显示电话簿中所有联系人的信息
		case SHOW_ALL_USERS:
		{
			showAllUsers();
			break;
		}
		// 按姓名修改联系人的信息
		case MODIFY_USER:
		{
			char name[NAME] = "";
			printf("请输入要修改信息的人的姓名：\n");
			scanf("%s", name);
			ModifyUser(name);
			break;
		}
		// 排序（按姓名排序或按电话号码排序）
		case SORT_USERS:
		{
			int flag = 0;
			printf("请输入要选择的排序方法：0 --------- 按电话号码排序  !0 ------------- 按联系人姓名排序\n");
			scanf("%d", &flag);
			sort(flag);
			break;
		}
		// 查找联系人（按人名查找或按电话查找）
		case FIND_USER:
		{
			FindUser();
			break;
		}
		// 退出程序
		case EXIT:
			exit(0);
			break;
		case SHOW_MENU:
			printMenu();
			break;
			// 删除所有用户
		case DEL_ALL_USERS:

			break;
		default:
			break;
		}
		printf("\n请问是否继续操作电话簿:  Y/y --- 是    N/n ---  否\n");
		getchar();         // 过滤回车或换行
		ch = getchar();    // 读入选项
		getchar();         // 读入 回车
		if (ch == 'N' || ch == 'n')
		{
			// 跳出循环，退出程序
			break;
		}
		else if (ch == 'Y' || ch == 'y')
		{
			printf("请输入菜单选项：\n");
			scanf("%d", &menu);
		}
		else
		{
			printf("您的输入有误，请重新输入!!!\n");
			while (EVER_EXEC)
			{
				printf("\n请问是否继续操作电话簿:  Y/y --- 是    N/n ---  否\n");
				//getchar();         // 过滤回车或换行
				ch = getchar();    // 读入选项
				getchar();         // 读入 回车
				if (ch == 'Y' || ch == 'y')
				{
					printf("请输入菜单选项：\n");
					scanf("%d", &menu);
					getchar();         // 读入 回车
									   // 跳出循环
					break;
				}
				else if (ch == 'N' || ch == 'n')
				{
					// 跳出循环，退出程序
					break;
				}
				else
				{
					continue;
				}
			}
		}
	}
}

int main(void)
{
	// 开始电话簿的所有操作
	Operate_TelBook();

	return 0;
}

