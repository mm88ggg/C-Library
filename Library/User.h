#ifndef LIBRARY_USER_H
#define LIBRARY_USER_H
#define MAXUSER 1000000

#include"Book.h"

#include <time.h>

typedef enum {
	_stu, _teacher
} UserType;
//���������û�����


typedef struct bookborrowed {
	Book* bookp;//ָ����ĵ�ͼ��
	struct bookborrowed* nextbook;//ָ����һ����
	struct tm beginDates;//������ĵ���ʼʱ��
	struct tm endDates;//����Ӧ�黹��ʱ��
}*booknode;
//���ڴ����û����ĵ�ͼ��


typedef struct User { //���пյ�ͷָ��
	char account[15];//��¼�˺�
	char passwd[20];//��¼����
	booknode borrowedbook;
	int cnt;//��¼�ѽ���ͼ������
	char info[15];//�༶ѧ��
	char name[20];//����
	int reputation;//��¼�û��������֣�������û���������
	struct User* user_next;//ָ�������е���һ���û�

	UserType state;//teacher or student
}User, *UserNode;
//���ڴ����û���Ϣ�Ľṹ��



typedef struct UserStock {
	UserNode teacher;
	UserNode student;
	UserNode _user_p_array[MAXUSER];
	int total_num;
} UserStock;
//���ڴ洢�����û���������ʦ��ѧ�����������������ͳ�Ƶȡ�



UserStock* initializeUserStock();

//���ڴ����û�,����0ʱ����ʧ�ܣ�����1ʱ�����ɹ���
int usercreate(UserStock* userstock, const char* account, const char* passwd, const char* info, const char* name, UserType state);

//���ڽ����鼮,������ʾ�ַ���ͷָ�룬�磺������ɹ���
const char * borrowbook(BookStock* bookStock, const char* id, const char* account, UserStock* userstock, UserType type);

//���ڹ黹�鼮�����ط�����ʾ�ַ���ͷָ�룬�磺������ɹ�����
const char * returnbook(BookStock* bookStock, const char* bookid, const char* account, UserStock* userstock, UserType type);

//����Ѱ���û����ɹ��ҵ�ʱ����ָ����û�ָ�룬��ʧ���򷵻�NULL��
UserNode finduser(const char* account, UserStock* userstock);

//�����о�ĳ�û���δ�黹ͼ�顣
const char * showrest(const char* account, UserStock* userstock, UserType type, struct bookborrowed** array, int maxsize);

//��������ͼ��,������ʾ�ַ���ͷָ�룬�磺���ɹ�����X��30�족��
const char * renewalbook(const char* account, UserStock* userstock, const char* id, UserType type);

//�����˻���ɾ���û�
int deleteuser(const char* account, UserStock* userstock);

//yΪ��ǰ��ݣ�mΪ��ǰ�·ݣ�dΪ��ǰ�죬����n�������ڷ�������һ���еĵڶ�����
int datetransform(int y, int m, int d, int n);

//����ĳ������ĳĳ���еĵڼ���
int dayTest(int day, int month, int year);

//�ж�ĳ���Ƿ�������
int ifLeapYear(int year);

//���ڼ���ĳ���еĵڶ������Ǽ��¼��ţ������������������w�з���
void reversedatetransform(int* w, int year, int date);

//�Ƚ��û����������ֺ���,�Ա����qsort()
int user_rep_cmp(const void* a, const void* b);

//���û����������ִӸߵ���������file.h�еĺ���getinfo_UserRepRank()���ʹ��
UserNode* rankUserByReputation(UserStock* userstock);

#endif //LIBRARY_USER_H