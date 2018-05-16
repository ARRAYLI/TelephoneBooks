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

FILE  *fp = NULL;         // �ļ���ָ��

int total = 0;            // �����ܹ��ж�����ϵ��

						  // �绰����Ϣ�ṹ��

typedef struct _TelBooks
{
	char name[NAME];                     //   ����
	char WorkUnit[WORK_UNIT];            //   ������λ
	char telphone[TEL];					 //   �绰����
	char email[EMAIL];					 //   email
	char LineFeed;                       //   ����
										 //	struct _TelBooks *next;              //   ָ����
}TelBooks/*, *PTelBooks*/;

TelBooks Users[LEN];

// ��ʼ������

void InitData()
{
	int i;
	for (i = 0; i<LEN; i++)
	{
		// ������л�����
		memset(&(Users[i]), 0x00, sizeof(TelBooks));
	}
}

// ��ʾ�˵�

void printMenu(void)
{
	printf("======================= �绰�� ============================\n");
	printf("\n\t\t 1����ӵ绰����\n\n");
	printf("\t\t 2��ɾ���绰����\n\n");
	printf("\t\t 3����ʾ���е绰����\n\n");
	printf("\t\t 4���޸Ĺ���\n\n");
	printf("\t\t 5���绰��������\n\n");
	printf("\t\t 6����������ѯ�绰����\n\n");
	printf("\t\t 7���˳�����\n\n");
	printf("\t\t 8����ʾ�绰�������˵�\n\n");
	printf("\t\t 9��ɾ��������ϵ��\n\n");
	printf("\n======================= �绰�� ============================\n\n");

	printf("��ѡ��˵����е绰��������\n\n\n\n");
}

// ����µ���ϵ��

void AddUser(void)
{
	TelBooks newUser;

	// ��׷�ӷ�ʽ���ļ�
	fp = fopen(fileName, "a+");
	if (NULL == fp)
	{
		printf("�� %s ����\n", fileName);
		return;
	}

	// ����½���ϵ������

	memset(&newUser, 0x00, sizeof(newUser));

	printf("��������ϵ�˵����� ��\n");
	//gets(temp.name);
	scanf("%s", newUser.name);
	printf("��������ϵ�˵Ĺ�����λ ��\n");
	//	gets(temp.WorkUnit);
	scanf("%s", newUser.WorkUnit);
	printf("��������ϵ�˵� Tel ��\n");
	//	gets(temp.telphone);
	scanf("%s", newUser.telphone);
	printf("��������ϵ�˵� emial ��\n");
	//	gets(temp.email);
	scanf("%s", newUser.email);

	// ���з�
	newUser.LineFeed = '\n';

	// ���ļ���д������

	fwrite(&newUser, sizeof(newUser), 1, fp);

	// ��ϵ������ 1
	//total++;

	// �ر��ļ�
	fclose(fp);
}

// ���绰����ɾ����ϵ����Ϣ
//
//     ɾ����ϵ�˵�ĳ����ϵ��˼���ǣ�
//     �Ȱ��ļ��е�������Ϣ���뵽�ṹ�������У�������Ҫɾ������ϵ����Ϣ�������ṹ���ж��룬Ȼ������д���ļ���

void DelUser(char *telphone)
{
	//int len=0, i=0;
	int i = 0;
	int total = 0;             // ��¼�ṹ���б�������ϵ�˵ĸ���
	TelBooks DelUser;
	int size = sizeof(DelUser);
	memset(&DelUser, 0x00, sizeof(DelUser));

	// ��ֻ����ʽ���ļ�

	fp = fopen(fileName, "r");
	if (NULL == fp)
	{
		printf("�� %s ����\n", fileName);
		return;
	}

	//	 len = getTotalUser();          // ��ȡ�ܵ���ϵ������

	// ��ʼ����ϵ�˽ṹ������
	InitData();

	// �����ݲ�д�뵽�ṹ��������

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

	// �ر��ļ�
	fclose(fp);

	// ���´��ģ����ѽṹ���е���Ϣд���ļ�


	// ��ֻд�ķ�ʽ���ļ�
	fp = fopen(fileName, "w+");
	if (NULL == fp)
	{
		printf("�� %s ����\n", fileName);
		return;
	}

	// ���ļ���д������
	for (i = 0; i<total; i++)
	{
		fwrite(&Users[i], sizeof(TelBooks), 1, fp);
	}

	// �ر��ļ�
	fclose(fp);

}

// ɾ��������ϵ��

void Del_All_Users(void)
{
	// ��ֻд�ķ�ʽ���ļ�
	fp = fopen(fileName, "w+");
	if (NULL == fp)
	{
		printf("�� %s ����\n", fileName);
		return;
	}
	// �ر��ļ�
	fclose(fp);
}

// ��ʾ���б���ĵ绰����

void showAllUsers(void)
{
	// ��ֻ����ʽ���ļ�

	fp = fopen(fileName, "r");
	if (NULL == fp)
	{
		printf("�� %s ����\n", fileName);
		return;
	}

	TelBooks temp;
	memset(&temp, 0x00, sizeof(temp));

	// �����ļ�ָ��ָ���ļ��ײ�
	fseek(fp, 0, SEEK_SET);

	while (fread(&temp, sizeof(temp), 1, fp) != 0)
	{
		printf("%s\t%s\t%s\t%s%c", temp.name, temp.WorkUnit, temp.telphone, temp.email, temp.LineFeed);

	}
	fclose(fp);
}

// �޸���Ϣ����

void modifyInfo(TelBooks *modifyUser)
{
	TelBooks temp = *modifyUser;
	char ch;
	printf("�Ƿ���Ҫ�޸���ϵ�� %s �������� Y/y --- �ǣ�N/n --- �� \n", modifyUser->name);
	//scanf("%c",&ch);

	ch = getchar();
	getchar();                   // �ѻس����� getchar() ��

								 // ˢ�±�׼���뻺����
								 //fflush(stdin);

								 //getchar();                   // �ѻس����� getchar() ��
	if (ch == 'Y' || ch == 'y')
	{
		memset(temp.name, 0x00, sizeof(temp.name));
		printf("�������޸ĺ��������\n");
		scanf("%s", temp.name);
	}
	getchar();                   // �ѻس����� getchar() ��
	printf("�Ƿ���Ҫ�޸���ϵ�� %s �Ĺ�����λ�� Y/y --- �ǣ�N/n --- �� \n", modifyUser->name);
	//scanf("%c", &ch);
	//

	ch = getchar();
	getchar();                   // �ѻس����� getchar() ��

								 // ˢ�±�׼���뻺����
								 //fflush(stdin);
	if (ch == 'Y' || ch == 'y')
	{
		memset(temp.WorkUnit, 0x00, sizeof(temp.WorkUnit));
		printf("�������޸ĺ�Ĺ�����λ��\n");
		scanf("%s", temp.WorkUnit);
	}
	getchar();                   // �ѻس����� getchar() ��

	printf("�Ƿ���Ҫ�޸���ϵ�� %s �� Tel �� Y/y --- �ǣ�N/n --- �� \n", modifyUser->name);
	//scanf("%c", &ch);
	ch = getchar();
	getchar();                   // �ѻس����� getchar() ��

	if (ch == 'Y' || ch == 'y')
	{
		memset(temp.telphone, 0x00, sizeof(temp.telphone));
		printf("�������޸ĺ�� Tel��\n");
		scanf("%s", temp.telphone);
	}
	getchar();                   // �ѻس����� getchar() ��
	printf("�Ƿ���Ҫ�޸���ϵ�� %s �� email �� Y/y --- �ǣ�N/n --- �� \n", modifyUser->name);
	//scanf("%c", &ch);
	//getchar();                   // �ѻس����� getchar() ��
	ch = getchar();
	getchar();                   // �ѻس����� getchar() ��
								 // ˢ�±�׼���뻺����
								 //	fflush(stdin);

	if (ch == 'Y' || ch == 'y')
	{
		memset(temp.email, 0x00, sizeof(temp.email));
		printf("�������޸ĺ��  emial��\n");
		scanf("%s", temp.email);
	}
	memset(modifyUser, 0x00, sizeof(TelBooks));
	*modifyUser = temp;
}

// �޸���ϵ����Ϣ
// ˼��:�Ȱ�������ϵ�˵���Ϣ���뵽��ϵ�˵���Ϣ�ṹ���У�Ȼ���ڽṹ���н����޸ģ�Ȼ������д�뵽�ļ���
void ModifyUser(char *name)
{
	int i = 0;
	int total = 0;             // ��¼�ṹ���б�������ϵ�˵ĸ���
	TelBooks modifyUser;
	int size = sizeof(modifyUser);
	memset(&modifyUser, 0x00, sizeof(modifyUser));

	// ��ֻ����ʽ���ļ�

	fp = fopen(fileName, "r");
	if (NULL == fp)
	{
		printf("�� %s ����\n", fileName);
		return;
	}

	//	 len = getTotalUser();          // ��ȡ�ܵ���ϵ������

	// ��ʼ����ϵ�˽ṹ������
	InitData();

	// �����ݲ�д�뵽�ṹ��������

	while (fread(&modifyUser, sizeof(TelBooks), 1, fp) != 0)
	{
		Users[i] = modifyUser;
		memset(&modifyUser, 0x00, sizeof(TelBooks));
		i++;
		total++;
	}

	// �ر��ļ�
	fclose(fp);

	// �ڽṹ�������н��б�����Ѱ�Ҹ�����������ϵ��

	for (i = 0; i<total; i++)
	{
		// ����ҵ�Ҫ�޸ĵ���ϵ�˵���Ϣ�������ϵ�˽�����Ϣ�޸ģ�Ȼ���˳�ѭ��
		if (strcmp(name, Users[i].name) == 0)
		{
			modifyInfo(&Users[i]);
			break;
		}
	}

	// ���´��ģ����ѽṹ���е���Ϣд���ļ�

	// ��ֻд�ķ�ʽ���ļ�
	fp = fopen(fileName, "w+");
	if (NULL == fp)
	{
		printf("�� %s ����\n", fileName);
		return;
	}

	// ���ļ���д������
	for (i = 0; i<total; i++)
	{
		fwrite(&Users[i], sizeof(TelBooks), 1, fp);
	}

	// �ر��ļ�
	fclose(fp);

}

// ��ѯ����

void FindUser(void)
{
	// ��ֻ����ʽ���ļ�

	fp = fopen(fileName, "r");
	if (NULL == fp)
	{
		printf("�� %s ����\n", fileName);
		return;
	}

	TelBooks findUser;                       // �����ѯ��ϵ�˵Ļ���������   
	int index = -1;                          // ����һ��  index ����������ѡ���ǰ� ������ѯ�绰���룬���ǰ� �绰�����ѯ��ϵ�˵���Ϣ
	char findContext[NAME] = "";             // ����һ����ѯ���ݵı���������ʲô����

											 // �����������������
	memset(&findUser, 0x00, sizeof(findUser));
	// index = 1 ��ʾ �����������ҵ绰����

	printf("�����룺\n0 ------ ��ʾ�����������ҵ绰����\n1 ------ ��ʾ���绰��������ѯ��ϵ����Ϣ\n");
	scanf("%d", &index);

	// �����ļ�ָ��Ϊ�ļ��ײ�
	fseek(fp, 0, SEEK_SET);
	if (index == 0)     // ������ �����ҵ绰����
	{
		printf("������Ҫ��ѯ�绰��������\n");
		scanf("%s", findContext);
		while ((fread(&findUser, sizeof(findUser), 1, fp) != EOF) && (strcmp(findContext, findUser.name) != 0));

		printf("%d\n", strcmp(findContext, findUser.name));
		printf("%s\t%s\t%s\t%s\t%c", findUser.name, findUser.WorkUnit, findUser.telphone, findUser.email, findUser.LineFeed);
		if ((strcmp(findContext, findUser.name) == 0))           // ��ʾ�����������ҵ���Ӧ�ĵ绰����
		{

			// ��ʾ�绰���뵽��Ļ
			printf("%s �ĵ绰�����ǣ� %s\n", findUser.name, findUser.telphone);
		}
		else   // ��ʾû���ҵ绰����
		{
			printf("�ڵ绰����û���ҵ�����Ϊ %s �ĵ绰����!!!\n", findContext);
		}
	}
	else if (index == 1)
	{
		printf("������Ҫ��ѯ�ĵ绰���룺\n");
		scanf("%s", findContext);
		while ((fread(&findUser, sizeof(findUser), 1, fp) != EOF) && (strcmp(findContext, findUser.telphone) != 0));


		printf("%d\n", strcmp(findContext, findUser.telphone));
		printf("%s\t%s\t%s\t%s\t%c", findUser.name, findUser.WorkUnit, findUser.telphone, findUser.email, findUser.LineFeed);

		if ((strcmp(findContext, findUser.telphone) == 0))           // ��ʾ����绰������ҵ���Ӧ����ϵ������
		{
			// ��ʾ��ϵ����������Ļ
			printf("�绰����Ϊ %s ����ϵ�˵�����Ϊ �� %s\n", findUser.telphone, findUser.name);
		}
		else   // ��ʾû���ҵ绰����
		{
			printf("�ڵ绰����û���ҵ��绰Ϊ %s ����ϵ��!!\n", findContext);
		}
	}
	else
	{
		memset(findContext, 0x00, sizeof(findContext));
		return;
	}
	memset(findContext, 0x00, sizeof(findContext));

	// �ر��ļ�
	fclose(fp);
}


// �����绰����ѯ�ܹ��ж�����ϵ��

int getTotalUser(void)
{
	// ��ֻ����ʽ���ļ�

	fp = fopen(fileName, "r");
	if (NULL == fp)
	{
		printf("�� %s ����\n", fileName);
		return 0;
	}

	int total = 0;   // ͳ���ܹ��ж�����ϵ��
	TelBooks temp;   // �����绰���������� 

					 // �����ļ�ָ�룬ָ���ļ��Ŀ�ʼ����
	fseek(fp, 0, SEEK_SET);

	while (fread(&temp, sizeof(temp), 1, fp) != 0)
	{
		total++;
	}

	// �ر��ļ�
	fclose(fp);
	return total;
}

// ���绰��������

void sort_by_telphone(int len)
{
	// �Զ���ʽ���ļ�
	fp = fopen(fileName, "r");
	if (NULL == fp)
	{
		printf("�� %s ����\n", fileName);
		return;
	}

	TelBooks temp;

	int i = 0, j = 0;

	// �����ļ�ָ�룬ָ���ļ��Ŀ�ʼ����
	fseek(fp, 0, SEEK_SET);

	memset(&temp, 0x00, sizeof(temp));
	// ��������ϵ�˵���Ϣ����  TelBooks Users[LEN] �ṹ�������У��ٽ���ð������

	while (fread(&temp, sizeof(temp), 1, fp) != 0)
	{
		Users[i] = temp;
		i++;
	}

	// ����ϵ�˽���ð������Ȼ��д���ļ�,��С��������

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

	// ��ֻд�ķ�ʽ���ļ�
	fp = fopen(fileName, "w");
	if (NULL == fp)
	{
		printf("�� %s ����\n", fileName);
		return;
	}

	// �������Ľ��д���ļ���
	for (i = 0; i<len; i++)
	{
		if (strcmp(Users[i].name, "") == 0)
		{
			//	�����ݣ������ļ���д����
			continue;
		}
		fwrite(&(Users[i]), sizeof(TelBooks), 1, fp);
	}

	fclose(fp);
}

// ��������������

void sort_by_name(int len)
{
	// �Զ���ʽ���ļ�
	fp = fopen(fileName, "r");
	if (NULL == fp)
	{
		printf("�� %s ����\n", fileName);
		return;
	}

	TelBooks temp;

	int i = 0, j = 0;

	// �����ļ�ָ�룬ָ���ļ��Ŀ�ʼ����
	fseek(fp, 0, SEEK_SET);

	memset(&temp, 0x00, sizeof(temp));
	// ��������ϵ�˵���Ϣ����  TelBooks Users[LEN] �ṹ�������У��ٽ���ð������

	while (fread(&temp, sizeof(temp), 1, fp) != 0)
	{
		Users[i] = temp;
		i++;
	}

	// ����ϵ�˽���ð������Ȼ��д���ļ�,��С��������

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

	// ��ֻд�ķ�ʽ���ļ�
	fp = fopen(fileName, "w");
	if (NULL == fp)
	{
		printf("�� %s ����\n", fileName);
		return;
	}

	// �������Ľ��д���ļ���
	for (i = 0; i<len; i++)
	{
		if (strcmp(Users[i].name, "") == 0)
		{
			//	�����ݣ������ļ���д����
			continue;
		}
		fwrite(&(Users[i]), sizeof(TelBooks), 1, fp);
	}

	fclose(fp);
}

// ����

void sort(int flag)
{
	int len = getTotalUser();              // ��ȡ�ܵ���ϵ������ 

										   // ��� flag = 0 �Ļ����Ե绰����������򣻷��򣬰���������
	if (flag == 0)
	{
		sort_by_telphone(len);
	}
	else
	{
		sort_by_name(len);
	}
}


// ����ĸ�������ģ�����

void Operate_TelBook()
{
	int menu;          // ����˵�ѡ��
	char ch;           // ��ʾ�Ƿ��������  Y/y ------ ��������  N/n ------ �˳�����
	InitData();
	printMenu();

	scanf("%d", &menu);

	while (EVER_EXEC)
	{
		switch (menu)
		{
			// ����µ���ϵ����Ϣ
		case ADD_USER:
		{	AddUser();
		break;
		}
		// ���绰����ɾ����ϵ����Ϣ
		case DEL_USER:
		{
			char name[NAME] = "";
			printf("������Ҫɾ�����˵ĵ绰���룺\n");
			scanf("%s", name);
			DelUser(name);
		}	break;
		// ��ʾ�绰����������ϵ�˵���Ϣ
		case SHOW_ALL_USERS:
		{
			showAllUsers();
			break;
		}
		// �������޸���ϵ�˵���Ϣ
		case MODIFY_USER:
		{
			char name[NAME] = "";
			printf("������Ҫ�޸���Ϣ���˵�������\n");
			scanf("%s", name);
			ModifyUser(name);
			break;
		}
		// ���򣨰���������򰴵绰��������
		case SORT_USERS:
		{
			int flag = 0;
			printf("������Ҫѡ������򷽷���0 --------- ���绰��������  !0 ------------- ����ϵ����������\n");
			scanf("%d", &flag);
			sort(flag);
			break;
		}
		// ������ϵ�ˣ����������һ򰴵绰���ң�
		case FIND_USER:
		{
			FindUser();
			break;
		}
		// �˳�����
		case EXIT:
			exit(0);
			break;
		case SHOW_MENU:
			printMenu();
			break;
			// ɾ�������û�
		case DEL_ALL_USERS:

			break;
		default:
			break;
		}
		printf("\n�����Ƿ���������绰��:  Y/y --- ��    N/n ---  ��\n");
		getchar();         // ���˻س�����
		ch = getchar();    // ����ѡ��
		getchar();         // ���� �س�
		if (ch == 'N' || ch == 'n')
		{
			// ����ѭ�����˳�����
			break;
		}
		else if (ch == 'Y' || ch == 'y')
		{
			printf("������˵�ѡ�\n");
			scanf("%d", &menu);
		}
		else
		{
			printf("����������������������!!!\n");
			while (EVER_EXEC)
			{
				printf("\n�����Ƿ���������绰��:  Y/y --- ��    N/n ---  ��\n");
				//getchar();         // ���˻س�����
				ch = getchar();    // ����ѡ��
				getchar();         // ���� �س�
				if (ch == 'Y' || ch == 'y')
				{
					printf("������˵�ѡ�\n");
					scanf("%d", &menu);
					getchar();         // ���� �س�
									   // ����ѭ��
					break;
				}
				else if (ch == 'N' || ch == 'n')
				{
					// ����ѭ�����˳�����
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
	// ��ʼ�绰�������в���
	Operate_TelBook();

	return 0;
}

