#ifndef LIBRARY_USER_H
#define LIBRARY_USER_H
#define MAXUSER 1000000

#include"Book.h"

#include <time.h>

typedef enum {
	_stu, _teacher
} UserType;
//用于区分用户类型


typedef struct bookborrowed {
	Book* bookp;//指向借阅的图书
	struct bookborrowed* nextbook;//指向下一本书
	struct tm beginDates;//本书借阅的起始时间
	struct tm endDates;//本书应归还的时间
}*booknode;
//用于储存用户借阅的图书


typedef struct User { //带有空的头指针
	char account[15];//登录账号
	char passwd[20];//登录密码
	booknode borrowedbook;
	int cnt;//记录已借阅图书数量
	char info[15];//班级学号
	char name[20];//姓名
	int reputation;//记录用户的信誉分，方便对用户进行评估
	struct User* user_next;//指向链表中的下一名用户

	UserType state;//teacher or student
}User, *UserNode;
//用于储存用户信息的结构体



typedef struct UserStock {
	UserNode teacher;
	UserNode student;
	UserNode _user_p_array[MAXUSER];
	int total_num;
} UserStock;
//用于存储所有用户，包括老师与学生，方便对人数进行统计等。



UserStock* initializeUserStock();

//用于创建用户,返回0时创建失败，返回1时创建成功。
int usercreate(UserStock* userstock, const char* account, const char* passwd, const char* info, const char* name, UserType state);

//用于借阅书籍,返回提示字符串头指针，如：“借书成功”
const char * borrowbook(BookStock* bookStock, const char* id, const char* account, UserStock* userstock, UserType type);

//用于归还书籍，返回返回提示字符串头指针，如：“还书成功”。
const char * returnbook(BookStock* bookStock, const char* bookid, const char* account, UserStock* userstock, UserType type);

//用于寻找用户，成功找到时返回指向该用户指针，若失败则返回NULL。
UserNode finduser(const char* account, UserStock* userstock);

//用于列举某用户尚未归还图书。
const char * showrest(const char* account, UserStock* userstock, UserType type, struct bookborrowed** array, int maxsize);

//用于续借图书,返回提示字符串头指针，如：“成功续借X书30天”。
const char * renewalbook(const char* account, UserStock* userstock, const char* id, UserType type);

//输入账户后删除用户
int deleteuser(const char* account, UserStock* userstock);

//y为当前年份，m为当前月份，d为当前天，计算n天后的日期返回这是一年中的第多少天
int datetransform(int y, int m, int d, int n);

//计算某日期是某某年中的第几天
int dayTest(int day, int month, int year);

//判断某年是否是闰年
int ifLeapYear(int year);

//用于计算某年中的第多少天是几月几号，并将结果储存在数组w中返回
void reversedatetransform(int* w, int year, int date);

//比较用户的信誉积分函数,以便调用qsort()
int user_rep_cmp(const void* a, const void* b);

//给用户按信誉积分从高到低排序，与file.h中的函数getinfo_UserRepRank()配合使用
UserNode* rankUserByReputation(UserStock* userstock);

#endif //LIBRARY_USER_H