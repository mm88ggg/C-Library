#pragma once
#define MAXBOOK 1000000
#define _ERROR_INIT_BUFFER "缓冲区未初始化"
#define _ERROR_SIZE_BUFFER "缓冲区空间不足"
#define _NOT_FOUND_BOOK "未找到相关搜索结果"

#include"Book.h"
#include"User.h"
#include"file.h"
#include<stdlib.h>
#include<string.h>

extern char infobuf[MAXBOOK];//这是用来存储 char * getinfo_XXX() 函数返回值的文本缓冲区

char* bookFilePush(const BookStock *bookStock);//本函数将所有书籍的主要信息保存到本地的bookFile.txt文件内
											//保存完成返回一个提示"更新bookFile.txt文件成功!\r\n"字符串头指针

int bookFilePop(BookStock * bookStock);//本函数从文件bookFile.txt中读取书籍信息并进行添加书的操作,注意newBook.txt需要提前建好
				//如果文件打开失败返回0，成功返回添加书的数量

//int bookFilePrint();//打印bookFile.txt里的内容，如果文件无法打开返回0，可以打开返回1,⚠本函数仅做测试用途！

char * userFilePush(UserStock * userStock);//本函数将所有书籍的主要信息保存到本地的userFile.txt文件内
										//保存完成返回一个提示"更新userFile.txt文件成功!\r\n"字符串头指针

int userFilePop(UserStock * userStock, BookStock* bookStock);//本函数从文件userFile.txt中读取书籍信息并进行添加书的操作,注意newBook.txt需要提前建好
				//如果文件打开失败返回0，成功返回添加书的数量

//int userFilePrint(); //打印userFile.txt里的内容，如果文件无法打开返回0，可以打开返回1⚠本函数仅做测试用途！

char* getinfo_searchBooks_group(int _returnVal_Search_amount, Book** books);
//此函数用于返回搜索的文本信息，且返回的文本信息是一本或若干本书的信息！
//缓冲区空间不足或未初始化使返回相应的错误提示文本
//第一个参数“ _returnVal_Search_amount(搜索到的书的数量)”为函数search_name()或intelligentSearch_name()或searchBooks_type()或searchSameBooks_id()的返回值
//第二个参数“Book** books”为存储了搜索到的书的缓冲区指针

char* getinfo_searchBook_single(Book *_returnVal_Search_Book);
//此函数用于返回搜索的文本信息，且返回的文本信息只有特定的一本书！
//缓冲区空间不足或未初始化使返回相应的错误提示文本
//其参数“Book *_returnVal_Search_Book”为函数“searchBook_id()”的返回值

char* getinfo_finduser(UserNode returnVal_finduser);
//此函数用于返回搜索的文本信息，且返回的文本信息只有特定的一个用户！
//缓冲区空间不足或未初始化使返回相应的错误提示文本
//其参数“UserNode returnVal_finduser”为函数“finduser()”的返回值

char* getinfo_UserRepRank(UserNode* returnVal_rankUserByReputation, UserStock * userstock);
//此函数返回值为按reputation降序排名用户的文本信息头指针

char* getWarning(const char * warningString);//用于返回提示或警告性文本字符串的头指针