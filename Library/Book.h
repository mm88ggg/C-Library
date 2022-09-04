#ifndef LIBRARY_BOOK_H
#define LIBRARY_BOOK_H

#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

typedef enum {
	bt_book, bt_periodical, bt_press, bt_all
} BookType;

typedef enum {
	s_borrowed, s_instock
} BookState;

typedef struct BookList {
	char id[20];            //第1位1-3分别表示为书、期刊、报刊，第2-8位表示不同的书种，第9-14位表示相同的书的不同本数
	char name[50];
	char author[30];
	char press[50];
	char date[15];
	unsigned* sumNumber;	//同一本书的总数
	unsigned* currNumber;	//同一本书的库存数
	unsigned* brdNumber;	//同一本书的借出数
	double price;
	BookType bookType;

	BookState state;
	char personId[9];

	struct BookList* diffNext;//不同的下一本书
	struct BookList* sameNext;//相同的下一本书
} BookList, *BLNode, Book;

typedef struct BookStock {
	BLNode book;			//书籍链表
	BLNode periodical;		//期刊链表
	BLNode press;			//报刊链表

	BLNode _for_convenience[3];	//为方便遍历以及id来确定哪个链表而设置
	BLNode _bookMap[1000000];	//查找id的散列表
} BookStock;

/*   初始化链表图书管理系统   */
BookStock* initBookStock();

/*   往图书馆中加入一本书 返回提示性字符串头指针 如：添加成功  */
const char * insertBook(BookStock* bookStock, const char* id, const char* name, const char* author, const char* press, const char* date, double price);

/*   判断是否为同一本书，是返回1，否返回0   */
int isSameBook(const char* id1, const char* id2);

/*   根据id找一本书，找到返回地址，找不到返回NULL   */
Book* searchBook_id(BookStock* bookStock, const char* id);

/*   按名字查找，返回查找数量，查找结果存入books中，参数maxNumber为最大查找数量（数组books范围），bookType指定查找范围   */
int search_name(BookStock* bookStock, const char* name, Book** books, int maxNumber, BookType bookType);

/*   智能查找书的简称，参数同search_name，最后一个maxMatch参数指定最少匹配字节数（一个汉字占2-3个字节）   */
int intelligentSearch_name(BookStock* bookStock, const char* name, Book** books, int maxNumber, BookType bookType, int maxMatch);

/*   从图书馆中删除一本书，返回值1为删除成功，返回值0为删除失败（没有此书）,返回值-1为已借出不可删除   */
int deleteBook(BookStock* bookStock, const char* id);

/*   根据类型查找书，返回查找数量，查找结果存入books中，参数maxNumber为最大查找数量（数组books范围）   */
int searchBooks_type(BookStock* bookStock, Book** books, int maxNumber, BookType bookType);

/*   根据id查找相同书，返回查找数量，查找结果存入books中，参数maxNumber为最大查找数量（数组books范围）   */
int searchSameBooks_id(BookStock* bookStock, Book** books, int maxNumber, const char* id);

#endif //LIBRARY_BOOK_H
