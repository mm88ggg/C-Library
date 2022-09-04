#include "File.h"
#include <Windows.h>

char infobuf[MAXBOOK] = {0};

char * bookFilePush(const BookStock* bookStock)
{
	FILE *fp = fopen("bookFile.txt", "w");
	BLNode tmpbook;
	for (int i = 0; i < MAXBOOK; i++)
	{
		tmpbook = bookStock->_bookMap[i];
		if (tmpbook)
		{
			// id, name, author, press, date, price
			fprintf(fp, "%s\n%s\n%s\n%s\n%s\n%lf\n", tmpbook->id, tmpbook->name, tmpbook->author,
				tmpbook->press, tmpbook->date, tmpbook->price);
		}
	}
	fclose(fp);

	return getWarning("更新bookFile.txt文件成功!\r\n");
}

int bookFilePop(BookStock* bookStock)
{

	FILE* fp = fopen("bookFile.txt", "r");
	if (fp == NULL)
	{
		return 0;
	}

	int cnt = 0;
	char* find;//查找换行符
	while (1)
	{
		if (feof(fp))
			break;
		char id[20] = { 0 };
		char name[50] = { 0 };
		char author[30] = { 0 };
		char press[50] = { 0 };
		char date[15] = { 0 };
		double price = 0;
		//fscanf(fp, "%s %s %s %s %s %lf", id, name, author, press, date, &price);
		fgets(id, 20, fp);
		find = strchr(id, '\n');	//strchr():在一个串中查找给定字符的第一个匹配之处
		if (find) { *find = '\0'; }
		fgets(name, 50, fp);
		find = strchr(name, '\n');
		if (find) { *find = '\0'; }
		fgets(author, 30, fp);
		find = strchr(author, '\n');
		if (find) { *find = '\0'; }
		fgets(press, 30, fp);
		find = strchr(press, '\n');
		if (find) { *find = '\0'; }
		fgets(date, 15, fp);
		find = strchr(date, '\n');
		if (find) { *find = '\0'; }
		fscanf(fp, "%lf", &price);
		fgetc(fp);
		insertBook(bookStock, id, name, author, press, date, price);
		cnt++;
	}
	fclose(fp);
	return cnt;
}


/*int bookFilePrint()
{
	FILE* fp = fopen("bookFile.txt", "r");
	if (fp == NULL)
	{
		return 0;
	}
	char tmpline[200] = {};
	char formalline[500] = {};
	while (fgets(tmpline, 200, fp))
	{
		//sprintf(formalline, "%-*s", 200, tmpline);
		//printf("%s", formalline);
		printf("%s", tmpline);
	}
	fclose(fp);
	return 1;
}*/

char* getinfo_searchBooks_group(int ans, Book** books)
{
	memset(infobuf, 0, sizeof(infobuf));
	char num[20] = {0};//用于存储double类型的price转换成的字符串

	if (ans == 0)
	{
		return (char *)_NOT_FOUND_BOOK;
	}

	char bktp[20] = { 0 };
	char bksta[20] = { 0 };

	char title[1000] = { 0 };
	sprintf(title, "%-15s %-10s %-25s %-25s %-25s %-10s %-8s %-8s %-6s %-6s\r\n", "ID", "本书类型", "书籍名", "作者", "出版社", "出版日期", "价格￥", "状态", "馆藏总量", "借出数");
	errno_t rlt;
	rlt = strcat_s(infobuf, MAXBOOK, title);
	if (rlt == EINVAL)
		return (char*)_ERROR_INIT_BUFFER;
	if (rlt == ERANGE)
		return (char*)_ERROR_SIZE_BUFFER;
	for (int i = 0; i < ans; ++i)
	{
		char tmpline[10000] = {0};
		if (books[i]->state == s_instock)
			strcpy(bksta, "未借出\0");
		else
			strcpy(bksta, "已借出\0");

		if (books[i]->id[0] == '1')
			strcpy(bktp, "书籍\0");
		else if (books[i]->id[0] == '2')
			strcpy(bktp, "期刊\0");
		else if (books[i]->id[0] == '3')
			strcpy(bktp, "报刊\0");//ID 本书类型 书籍名 作者 出版社 出版日期 价格 本书状态 此书馆藏总量 已被借出数量
		sprintf(tmpline, "%-15s %-10s %-25s %-25s %-25s %-10s %-8.2lf %-6s %10d %6d\r\n"
			, books[i]->id, bktp, books[i]->name, books[i]->author, books[i]->press, books[i]->date, books[i]->price, bksta, *books[i]->sumNumber, *books[i]->brdNumber);

		rlt = strcat_s(infobuf, MAXBOOK, tmpline);
		if (rlt == EINVAL)
			return (char*)_ERROR_INIT_BUFFER;
		if (rlt == ERANGE)
			return (char*)_ERROR_SIZE_BUFFER;
	}
	rlt = strcat_s(infobuf, MAXBOOK, "\r\n");
	if (rlt == EINVAL)
		return (char*)_ERROR_INIT_BUFFER;
	if (rlt == ERANGE)
		return (char*)_ERROR_SIZE_BUFFER;
	return infobuf;
}

char* getinfo_searchBook_single(Book*ans)
{
	memset(infobuf, 0, sizeof(infobuf));
	if (ans == NULL)
	{
		return (char*)_NOT_FOUND_BOOK;
	}
	else
	{
		char bktp[20] = { 0 };
		char bksta[20] = { 0 };


		if (ans->state == s_instock)
			strcpy(bksta, "未借出\0");
		else
			strcpy(bksta, "已借出\0");

		if (ans->id[0] == '1')
			strcpy(bktp, "书籍\0");
		else if (ans->id[0] == '2')
			strcpy(bktp, "期刊\0");
		else if (ans->id[0] == '3')
			strcpy(bktp, "报刊\0");
		sprintf(infobuf, "ID：%-15s 本书类型：%-4s 书籍名：%-15s 作者:%-10s 出版社：%-15s 出版日期：%-10s 价格：￥%-6.2lf 本书状态：%-6s 此书馆藏总量：%-3d 已被借出数量：%-3d\r\n"
			, ans->id, bktp, ans->name, ans->author, ans->press, ans->date, ans->price, bksta, *ans->sumNumber, *ans->brdNumber);
	}
	return infobuf;
}


char * userFilePush(UserStock* userStock)
{
	FILE* fp = fopen("userFile.txt", "w");
	UserNode uspt = userStock->teacher->user_next;
	UserNode usps = userStock->student->user_next;
	while (uspt)//老师
	{
		//account, passwd, info, name, iden
		fprintf(fp, "%s\n%s\n%s\n%s\n%s\n%d\nbrdBookListStart\n", uspt->account, uspt->passwd, uspt->info, uspt->name, "_teacher", uspt->reputation);
		booknode brdbk = uspt->borrowedbook->nextbook;
		while (brdbk)
		{
			fprintf(fp, "%s\n%d\n%d\n%d\n%d\n%d\n%d\n",
				brdbk->bookp->id, brdbk->beginDates.tm_year, brdbk->beginDates.tm_mon, brdbk->beginDates.tm_mday,
				brdbk->endDates.tm_year, brdbk->endDates.tm_mon, brdbk->endDates.tm_mday);
			brdbk = brdbk->nextbook;
		}
		fprintf(fp, "brdBookListEnd\n");
		uspt = uspt->user_next;
	}
	while (usps)//学生
	{
		fprintf(fp, "%s\n%s\n%s\n%s\n%s\n%d\nbrdBookListStart\n", usps->account, usps->passwd, usps->info, usps->name, "_stu", usps->reputation);
		booknode brdbk = usps->borrowedbook->nextbook;
		while (brdbk)
		{
			fprintf(fp, "%s\n%d\n%d\n%d\n%d\n%d\n%d\n",
				brdbk->bookp->id, brdbk->beginDates.tm_year, brdbk->beginDates.tm_mon, brdbk->beginDates.tm_mday,
				brdbk->endDates.tm_year, brdbk->endDates.tm_mon, brdbk->endDates.tm_mday);
			brdbk = brdbk->nextbook;
		}
		fprintf(fp, "brdBookListEnd\n");
		usps = usps->user_next;
	}
	fclose(fp);

	return getWarning("更新userFile.txt文件成功!\r\n");
}


int userFilePop(UserStock* userStock, BookStock* bookStock)
{
	UserNode userp;

	FILE* fp = fopen("userFile.txt", "r");
	if (fp == NULL)
		return 0;
	int cnt = -1;
	char account[15] = { 0 };//登录账号
	char passwd[20] = { 0 };//登录密码
	char info[15] = { 0 };//班级学号
	char name[20] = { 0 };//姓名
	char iden[20] = { 0 };
	char brdbk_block[20] = { 0 };
	int repu;
	UserType state;//teacher or student
	char* find;
	while (1)
	{
		fgets(account, 15, fp);
		if (feof(fp))
			break;
		find = strchr(account, '\n');
		if (find) { *find = '\0'; }
		fgets(passwd, 20, fp);
		find = strchr(passwd, '\n');
		if (find) { *find = '\0'; }
		fgets(info, 15, fp);
		find = strchr(info, '\n');
		if (find) { *find = '\0'; }
		fgets(name, 20, fp);
		find = strchr(name, '\n');
		if (find) { *find = '\0'; }
		fgets(iden, 20, fp);
		find = strchr(iden, '\n');
		if (find) { *find = '\0'; }
		if (strcmp(iden, "_teacher") == 0)
			state = _teacher;
		else
			state = _stu;
		fscanf(fp, "%d\n", &repu);
		
		fgets(brdbk_block, 20, fp);
		find = strchr(brdbk_block, '\n');
		if (find) { *find = '\0'; }
		usercreate(userStock, account, passwd, info, name, state);
		userp = finduser(account, userStock);
		while (strcmp(brdbk_block, "brdBookListEnd"))
		{
			int cc;
			if ((cc = fgetc(fp)) == 'b') {
				ungetc(cc, fp);
				fgets(brdbk_block, 20, fp);
				find = strchr(brdbk_block, '\n');
				if (find) { *find = '\0'; }
				continue;
			}
			else {
				ungetc(cc, fp);
			}
			char bk_id[20] = { 0 };
			int bgy = 0, bgm = 0, bgd = 0;
			int edy = 0, edm = 0, edd = 0;

			fgets(bk_id, 20, fp);
			find = strchr(bk_id, '\n');
			if (find) { *find = '\0'; }
			fscanf(fp, "%d", &bgy);
			fgetc(fp);
			fscanf(fp, "%d", &bgm);
			fgetc(fp);
			fscanf(fp, "%d", &bgd);
			fgetc(fp);
			fscanf(fp, "%d", &edy);
			fgetc(fp);
			fscanf(fp, "%d", &edm);
			fgetc(fp);
			fscanf(fp, "%d", &edd);
			fgetc(fp);
			/*MessageBox(NULL, bk_id, NULL, NULL);
			MessageBox(NULL, borrowbook(bookStock, bk_id, account, userStock, state), NULL, NULL);*/
			borrowbook(bookStock, bk_id, account, userStock, state);
			
			userp->borrowedbook->nextbook->beginDates.tm_year = bgy;
			userp->borrowedbook->nextbook->beginDates.tm_mon = bgm;
			userp->borrowedbook->nextbook->beginDates.tm_mday = bgd;
			userp->borrowedbook->nextbook->endDates.tm_year = edy;
			userp->borrowedbook->nextbook->endDates.tm_mon = edm;
			userp->borrowedbook->nextbook->endDates.tm_mday = edd;
			
			fgets(brdbk_block, 20, fp);
			find = strchr(brdbk_block, '\n');
			if (find) { *find = '\0'; }
		}
		cnt++;
		userp->reputation = repu;
	}
	fclose(fp);

	return cnt;
}

/*int userFilePrint()
{
	FILE* fp = fopen("userFile.txt", "r");
	if (fp == NULL)
	{
		return 0;
	}
	char tmpline[200] = {};
	char formalline[500] = {};
	while (fgets(tmpline, 200, fp))
	{
		//sprintf(formalline, "%-*s", 200, tmpline);
		//printf("%s", formalline);
		printf("%s", tmpline);
	}
	fclose(fp);
	return 1;
}//⚠本函数仅做测试用途！*/

char* getinfo_finduser(UserNode ans)
{
	memset(infobuf, 0, sizeof(infobuf));

	if (ans == NULL)
	{
		return (char*)_NOT_FOUND_BOOK;
	}
	else
	{
		char iden[10] = { 0 };
		if (ans->state == _stu)
			strcpy(iden, "学生\0");
		else
			strcpy(iden, "老师\0");

		sprintf(infobuf, "用户姓名：%-10s 账号：%-9s 身份：%-4s 学工号：%-10s 已借阅书籍数：%-3d 信誉积分：%-3d\r\n"
			, ans->name, ans->account, iden, ans->info, ans->cnt, ans->reputation);
	}
	return infobuf;
}

char* getinfo_UserRepRank(UserNode* ans, UserStock* userstock)
{
	memset(infobuf, 0, sizeof(infobuf));

	int num = userstock->total_num;
	char title[1000] = { 0 };
	errno_t rlt;
	sprintf(title, "%-20s %-20s %-20s %-20s %-20s %-20s\r\n", "用户姓名", "账号", "身份", "学工号", "已借书籍数", "信誉积分");
	rlt = strcat_s(infobuf, MAXBOOK, title);
	if (rlt == EINVAL)
		return (char*)_ERROR_INIT_BUFFER;
	if (rlt == ERANGE)
		return (char*)_ERROR_SIZE_BUFFER;
	for (int i = 0; i < num; i++)
	{


		char tmpline[10000] = { 0 };
		char iden[10] = { 0 };
		if (ans[i]->state == _stu)
			strcpy(iden, "学生\0");
		else
			strcpy(iden, "老师\0");
		//"用户姓名" ,"账号", "身份", "学工号", "已借书籍数", "信誉积分"
		sprintf(tmpline, "%-20s %-20s %-20s %-20s %10d %18d\r\n"
			, ans[i]->name, ans[i]->account, iden, ans[i]->info, ans[i]->cnt, ans[i]->reputation);

		rlt = strcat_s(infobuf, MAXBOOK, tmpline);
		if (rlt == EINVAL)
			return (char*)_ERROR_INIT_BUFFER;
		if (rlt == ERANGE)
			return (char*)_ERROR_SIZE_BUFFER;
	}
	return infobuf;
}

char* getWarning(const char* str)
{
	memset(infobuf, 0, sizeof(infobuf));
	errno_t rlt;

	rlt = strcat_s(infobuf, MAXBOOK, str);
	if (rlt == EINVAL)
		return (char*)_ERROR_INIT_BUFFER;
	if (rlt == ERANGE)
		return (char*)_ERROR_SIZE_BUFFER;
	return infobuf;
}