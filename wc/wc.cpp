#include <stdio.h>
#include <stdlib.h>
#include "func.h"
#define _CRT_SECURE_NO_WARNINGS

int main(int argc,char *argv[])
{
	int choose = 0;
	char com;
	FILE * fp;
	char* func = (char*)malloc(sizeof(char) * 50);

	if (argv[1] != NULL) //从shell打开软件
	{
		fp = fopen(argv[1], "r");
		if (fp == NULL)
		{
			printf("文件打开失败。\n");
			exit(1);
		}
		func = argv[2];
		com = func[1];
	}
	else //直接打开软件
	{
		char fname[100];
		printf("请输入文件名： ");
		scanf("%s", fname);
		fp = fopen(fname, "r");
		if (fp == NULL)
		{
			printf("Failed to open file.\n");
			exit(1);
		}
		getchar();
		puts("输入：q 退出\t w 获取词数\t l 获取行数\t c 获取字符数");
		scanf("%c", &com);
		getchar();
	}
	if (com == 'c')
		choose = 1;
	else if (com == 'w')
		choose = 2;
	else if (com == 'l')
		choose = 3;
	else
		choose = 101;
	while (choose != 100)
	{
		switch (choose)
		{
		case 1:
			GetLetter(fp);
			rewind(fp);
			break;
		case 2:
			GetWord(fp);
			rewind(fp);
			break;
		case 3:
			GetLine(fp);
			rewind(fp);
			break;
		case 101:
			printf("错误输入\n\n");
			while (getchar() != '\n')
				continue;
			break;
		}
		puts("输入：q 退出\t w 获取词数\t l 获取行数\t c 获取字符数");
		scanf("%c",&com);
		getchar();
		if (com == 'c')
			choose = 1;
		else if (com == 'w')
			choose = 2;
		else if (com == 'l')
			choose = 3;
		else if (com == 'q')
			choose = 100;
		else
			choose = 101;
	}
	fclose(fp);
	free(func);
	//quicktest();
	//test();
	system("pause");
	return 0;
}

void quicktest()
{
	FILE * fp;
	fp = fopen("H:/C/test.cpp", "r");
	if (fp == NULL)
	{
		printf("Failed to open file.\n");
		exit(1);

	}
	GetLine(fp);
	rewind(fp);
	GetWord(fp);
	rewind(fp);
	GetLetter(fp);
	fclose(fp);
	
}

void test()
{
	FILE * fp;
	char fname[50];
	printf("Enter the name of the file: ");
	scanf("%s", fname);
	fp = fopen(fname, "r");
	if (fp == NULL)
	{
		printf("Failed to open file.\n");
		exit(1);

	}
	GetLine(fp);
	rewind(fp);
	GetWord(fp);
	rewind(fp);
	GetLetter(fp);
	fclose(fp);
}

void GetLine(FILE *f)
{
	int letter = 0, line = 0;
	int mark = 0;
	while (!feof(f))
	{
		letter = fgetc(f);
		if (letter == '\n') //换行行数+1
			line++;
	}
	printf("共有行数 %d\n\n", line);
}

void GetWord(FILE *f)
{
	int letter = 0, word = 0;
	int mark = 0;
	while (!feof(f))
	{
		letter = fgetc(f);
		if ((letter >= 'a'&&letter <= 'z') || (letter >= 'A'&&letter <= 'Z') || letter == '_')
		{
			if (mark == 0)
				mark = 1; //标记为字符串
		}
		else if (letter == '.') //防止头文件和浮点数的'.'被误判
		{
			if (mark == 0 || mark == 1)
				continue;
		}
		else
		{
			if (mark == 1) //当前为非字符串且前面为字符串视为字符串结束
			{
				word++;
				mark = 0;
			}
			else 
				continue;
		}
	}
	printf("共有词数 %d\n\n", word);
}

void GetLetter(FILE *f)
{
	int letter = 0, num = 0;
	while (!feof(f))
	{
		letter = fgetc(f);
		if (letter == '\n') //除换行标记外均视为字符
			continue;
		num++;
	}
	printf("共有字符数 %d\n\n", num);
}