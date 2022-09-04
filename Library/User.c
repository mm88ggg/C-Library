#include"User.h"
#include <Windows.h>

char infobuf_u[MAXUSER] = { 0 };//��ʾ���ı�������User.hר��

int days[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
int mont(int n) {
	if ((n % 4 == 0 && n % 100 != 0) || n % 400 == 0) return 0;
	else return 1;
}

UserStock* initializeUserStock() {
	UserStock* userstock = (UserStock*)malloc(sizeof(UserStock));
	userstock->teacher = (UserNode)malloc(sizeof(struct User));
	userstock->student = (UserNode)malloc(sizeof(struct User));

	userstock->teacher->user_next = NULL;
	userstock->student->user_next = NULL;
	memset(userstock->_user_p_array, 0, sizeof(userstock->_user_p_array));
	userstock->total_num = 0;
	return userstock;
}
//��userstock���г�ʼ���������ڴ档


int usercreate(UserStock* userstock, const char* account, const char* passwd, const char* info, const char* name, UserType type)
{
	UserNode p = (UserNode)malloc(sizeof(struct User));//���г�ʼ��
	if (p == NULL) return 0;
	strcpy(p->account, account);
	strcpy(p->passwd, passwd);
	strcpy(p->info, info);
	strcpy(p->name, name);
	p->state = type;
	p->cnt = 0;
	p->reputation = 0;
	p->borrowedbook = (booknode)malloc(sizeof(struct bookborrowed));
	p->borrowedbook->nextbook = NULL;
	p->user_next = NULL;
	//��ʼ�����


	//���û���ӽ�userstock��
	UserNode head;
	if (type == _stu)
		head = userstock->student;
	else
		head = userstock->teacher;

	p->user_next = head->user_next;
	head->user_next = p;
	userstock->_user_p_array[userstock->total_num++] = head->user_next;
	return 1;
}



const char * borrowbook(BookStock* bookStock, const char* id, const char* account, UserStock* userstock, UserType type) {
	Book* p = NULL;
	p = searchBook_id(bookStock, id);//��ͼ���������
	if (!p)
	{
		return "��Ǹ��������δ��¼��ͼ��\r\n";
	}
	if (p->state == s_borrowed) {
		return "��Ǹ����ͼ���Ѿ������\r\n";
	}


	//���û���������
	UserNode w = NULL;
	switch (type)
	{
	case _stu:
		w = finduser(account, userstock);
		if (!w)
		{
			return "��������˻�������\r\n";
		}
		if (w->cnt == 10)
		{
			return "��Ǹ���������鼮�����Ѵ����ޣ���黹����н���\r\n";
		}
		break;
	case _teacher:
		w = finduser(account, userstock);
		if (!w)
		{
			return "��������˻�������\r\n";
		}
		if (w->cnt == 20)
		{
			return "��Ǹ���������鼮�����Ѵ����ޣ���黹����н���\r\n";
		}
		break;
	default:
		return "��Ǹ����������˻�������\r\n";
	}

	//�����������鼮��ӵ��û��ѽ����鼮������

	p->state = s_borrowed;
	strcpy(p->personId, account);
	++(*p->brdNumber);//ͬʱ�޸ĸ���Ŀ���������ѽ��������
	--(*p->currNumber);

	booknode head = w->borrowedbook;
	booknode v = head;
	booknode toadd = (booknode)malloc(sizeof(struct bookborrowed));
	toadd->bookp = p;

	time_t timep;//��ȡ��ǰʱ�䣬�ԶԽ����鼮ʱ����м�¼
	struct tm* dates;
	time(&timep);
	dates = gmtime(&timep);
	//printf("asdfasdf%dasdfsadf\n", dates->tm_mon);
	//int nowdate = dayTest(dates->tm_mday, 1 + dates->tm_mon, 1900 + dates->tm_year);
	toadd->endDates = toadd->beginDates = *dates;
	toadd->nextbook = NULL;


	//����Ӧ�黹ʱ���Ƿ����
	int enddate = dayTest(dates->tm_mday, 1 + dates->tm_mon, 1900 + dates->tm_year) + 30;
	int addYear = (enddate) / (ifLeapYear(1900 + dates->tm_year) ? 367 : 366);
	enddate %= (ifLeapYear(1900 + dates->tm_year) ? 367 : 366);
	enddate += enddate == 0;
	toadd->endDates.tm_year += addYear;

	int A[2];
	reversedatetransform(A, toadd->endDates.tm_year + 1900, enddate);
	toadd->endDates.tm_mon = A[0] - 1;
	toadd->endDates.tm_mday = A[1];


	//���鼮��ͷ�巨����
	toadd->nextbook = head->nextbook;
	head->nextbook = toadd;

	w->cnt++;
	w->reputation++;//w�Ƕ���ָ�룬���ߵ�����������
	return "���ѳɹ������鼮\r\n";
}


UserNode finduser(const char* account, UserStock* userstock)
{
	UserNode head;
	head = userstock->student;
	UserNode p = head;
	while (p->user_next)
	{
		if (strcmp(p->user_next->account, account) == 0)
			return p->user_next;
		p = p->user_next;
	}

	head = userstock->teacher;
	p = head;
	while (p->user_next)
	{
		if (strcmp(p->user_next->account, account) == 0)
			return p->user_next;
		p = p->user_next;
	}
	return NULL;
}
int isTimeOver(struct tm* b, struct tm* e) {
	if (b->tm_year > e->tm_year)return 1;
	if (b->tm_year == e->tm_year && b->tm_mon > e->tm_mon)return 1;
	if (b->tm_mon == e->tm_mon && b->tm_year == e->tm_year && b->tm_mday > e->tm_mday)return 1;
	return 0;
}

const char * returnbook(BookStock* bookStock, const char* bookid, const char* account, UserStock* userstock, UserType type)
{
	Book* p = NULL;
	p = searchBook_id(bookStock, bookid);//��������ͼ��
	if (!p)
	{
		return "��Ǹ���������������\r\n";
	}
	UserNode w = NULL;
	w = finduser(account, userstock);//���û���������
	if (w == NULL)
	{
		return "�������������˻�\r\n";
	}

	p->state = s_instock;//�޸��鼮��ǰ״̬
	(p->personId)[0] = '\0';
	booknode head = w->borrowedbook;
	booknode v = head;
	while (v->nextbook)//��������Ѱ���鼮
	{
		if (strcmp(v->nextbook->bookp->id, bookid) == 0)
		{
			time_t timep;
			struct tm* dates;
			time(&timep);
			dates = gmtime(&timep);


			Book* booked[10];
			w->cnt--;
			++(*p->currNumber);
			--(*p->brdNumber);
			if (!isTimeOver(dates, &v->nextbook->endDates))//�ж��Ƿ����ڹ黹
			{
				w->reputation++;
				booknode x = v->nextbook;
				v->nextbook = v->nextbook->nextbook;
				free(x);

				return "���ڹ涨ʱ���ڳɹ��黹�鼮\r\n";
			}
			else
			{
				w->reputation -= 2;
				booknode x = v->nextbook;
				v->nextbook = v->nextbook->nextbook;
				free(x);
				return "�������ĵ�ͼ�����ڹ黹������ɷ���100Ԫ\r\n";
			}
		}
	}
	return 0;
}

const char * showrest(const char * account, UserStock * userstock, UserType type, struct bookborrowed ** array, int maxsize) {
	UserNode h = finduser(account, userstock);//��Ѱ�û�
	booknode w;
	if (h != NULL)
		w = h->borrowedbook;
	else
	{
		//printf("δ�ҵ����û�\n");
		return "δ�ҵ����û�\r\n";
	}
	time_t timep;
	struct tm* p;
	time(&timep);
	p = gmtime(&timep);//��ȡ��ǰʱ��
	int cnt = 0;
	//int borrowdate;
	memset(infobuf_u, 0, sizeof(infobuf_u));
	if (h->cnt == 0) {
		strcat_s(infobuf_u, MAXUSER, "���޽����κ��鼮��\r\n");
		return infobuf_u;
	}
	//printf("���ѽ��ĵ��鼮��Ϣ����\n");
	strcat_s(infobuf_u, MAXUSER, "���ѽ��ĵ��鼮��Ϣ����\r\n");
	while (w->nextbook && cnt < maxsize)//��������ͼ�鲢�鿴�Ƿ����ڡ�
	{
		array[cnt++] = w->nextbook;


		if (isTimeOver(p, &w->nextbook->endDates))
		{

			strcat_s(infobuf_u, MAXUSER, "�������ĵ�ͼ��:��");
			strcat_s(infobuf_u, MAXUSER, w->nextbook->bookp->name);
			strcat_s(infobuf_u, MAXUSER, "��(");
			strcat_s(infobuf_u, MAXUSER, w->nextbook->bookp->id);
			strcat_s(infobuf_u, MAXUSER, ")");
			strcat_s(infobuf_u, MAXUSER, "�����ڣ��뾡��黹\r\n");
		}
		else
		{

			strcat_s(infobuf_u, MAXUSER, "�������ĵ�ͼ��:��");
			strcat_s(infobuf_u, MAXUSER, w->nextbook->bookp->name);
			strcat_s(infobuf_u, MAXUSER, "��(");
			strcat_s(infobuf_u, MAXUSER, w->nextbook->bookp->id);
			strcat_s(infobuf_u, MAXUSER, ")");
			char tmp[110] = { 0 };

			strcat_s(infobuf_u, MAXUSER, "����"); strcat_s(infobuf_u, MAXUSER, itoa(1900 + w->nextbook->endDates.tm_year, tmp, 10));
			strcat_s(infobuf_u, MAXUSER, "��"); strcat_s(infobuf_u, MAXUSER, itoa(w->nextbook->endDates.tm_mon + 1, tmp, 10));
			strcat_s(infobuf_u, MAXUSER, "��"); strcat_s(infobuf_u, MAXUSER, itoa(w->nextbook->endDates.tm_mday, tmp, 10));
			strcat_s(infobuf_u, MAXUSER, "��ǰ�黹\r\n");
		}
		w = w->nextbook;
	}
	return infobuf_u;
}

const char* renewalbook(const char* account, UserStock* userstock, const char* id, UserType type)
{
	memset(infobuf_u, 0, sizeof(infobuf_u));
	UserNode p = finduser(account, userstock);
	booknode w = p->borrowedbook;

	time_t timep;
	struct tm* tt;
	time(&timep);
	tt = gmtime(&timep);
	while (w->nextbook)
	{
		if (strcmp(w->nextbook->bookp->id, id) == 0)
		{
			if (isTimeOver(tt, &w->nextbook->endDates))
			{

				strcat_s(infobuf_u, MAXUSER, "�������ĵ�ͼ��:��");
				strcat_s(infobuf_u, MAXUSER, w->nextbook->bookp->name);
				strcat_s(infobuf_u, MAXUSER, "��(");
				strcat_s(infobuf_u, MAXUSER, w->nextbook->bookp->id);
				strcat_s(infobuf_u, MAXUSER, ")");
				strcat_s(infobuf_u, MAXUSER, "�����ڣ��뾡��黹\r\n");
				strcat_s(infobuf_u, MAXUSER, "����ʧ��\r\n");
				return infobuf_u;
			}
			int enddate = dayTest(w->nextbook->endDates.tm_mday, 1 + w->nextbook->endDates.tm_mon, 1900 + w->nextbook->endDates.tm_year) + 30;//��ͼ����Ӧ�黹ʱ��������ʮ�죬�����ʱ���ƣ�����������ʱ����ʼʱ���滻�����ϴε�enddates
			int addYear = (enddate) / (ifLeapYear(1900 + w->nextbook->endDates.tm_year) ? 367 : 366);
			enddate %= (ifLeapYear(1900 + w->nextbook->endDates.tm_year) ? 367 : 366);
			enddate += enddate == 0;
			w->nextbook->endDates.tm_year += addYear;
			int A[2];
			reversedatetransform(A, w->nextbook->endDates.tm_year + 1900, enddate);
			w->nextbook->endDates.tm_mon = A[0] - 1;
			w->nextbook->endDates.tm_mday = A[1];
			//w->nextbook->date += daynum;

			strcat_s(infobuf_u, MAXUSER, "���ѳɹ�����ͼ��30��");
			return infobuf_u;
		}
		w = w->nextbook;
	}
	strcat_s(infobuf_u, MAXUSER, "����ʧ��\r\n");
	return infobuf_u;
}

int deleteuser(const char* account, UserStock* userstock) {
	UserNode w = userstock->student;
	while (w->user_next) {
		if (strcmp(w->user_next->account, account) == 0)
		{
			for (int i = 0; i < userstock->total_num; i++)
			{
				if (userstock->_user_p_array[i] == w->user_next)
				{
					for (int j = i; j < userstock->total_num; j++)
					{
						userstock->_user_p_array[j] = userstock->_user_p_array[j + 1];
					}
				}
			}
			userstock->total_num--;
			UserNode todel_stu = w->user_next;
			w->user_next = w->user_next->user_next;
			free(todel_stu);
			//
			return 1;
		}
		w = w->user_next;
	}

	UserNode l = userstock->teacher;
	while (l->user_next) {
		if (strcmp(l->user_next->account, account) == 0)
		{
			for (int i = 0; i < userstock->total_num; i++)
			{
				if (userstock->_user_p_array[i] == l->user_next)
				{
					for (int j = i; j < userstock->total_num; j++)
					{
						userstock->_user_p_array[j] = userstock->_user_p_array[j + 1];
					}
				}
			}
			userstock->total_num--;
			UserNode todel_teacher = l->user_next;
			l->user_next = l->user_next->user_next;
			free(todel_teacher);
			//printf("�û�ɾ���ɹ�\n");
			return 1;
		}
		l = l->user_next;
	}
	//printf("�û�ɾ��ʧ��\n");
	return 0;
}

int datetransform(int y, int m, int d, int n) {
	int mon[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31 ,30, 31, 30, 31 };

	if (mont(y)) mon[2] = 28;
	else mon[2] = 29;
	for (int i = 1; i <= n; i++) {
		d += 1;
		if (d > mon[m]) {
			d = d - mon[m];
			m++;
			if (m > 12) {
				y++;
				m = 1;
				if (mont(y))
					continue;
				mon[2] = 29;
			}
		}
	}
	return dayTest(d, m, y);
}

int dayTest(int day, int month, int year) {
	int  sum = 0, leap;
	int month2[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	for (int i = 0; i < month - 1; i++)
		sum += month2[i];
	sum = sum + day;
	leap = ifLeapYear(year);
	if (leap == 1 && month > 2) {
		sum++;
	}
	return sum;
}

int ifLeapYear(int year) {
	return (year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0));
}

void reversedatetransform(int* w, int year, int date) {
	int i;
	int month1[12] = { 31,29,31,30,31,30,31,31,30,31,30,31 };
	int month2[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (date > 366)
	{
		//printf("�������\n");
		return;
	}
	int a = ifLeapYear(year);
	if (a)
		for (i = 0; i < 12; i++) {
			if (date <= month1[i]) break;
			date = date - month1[i];
		}
	else
		for (i = 0; i < 12; i++) {
			if (date <= month2[i]) break;
			date = date - month2[i];
		}
	w[0] = i + 1;
	w[1] = date;
}


int user_rep_cmp(const void* a, const void* b)
{
	return (*(UserNode*)b)->reputation - (*(UserNode*)a)->reputation;
}

UserNode* rankUserByReputation(UserStock* userstock)
{
	qsort(userstock->_user_p_array, userstock->total_num, sizeof(userstock->_user_p_array[0]), user_rep_cmp);
	return userstock->_user_p_array;
}