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
	char id[20];            //��1λ1-3�ֱ��ʾΪ�顢�ڿ�����������2-8λ��ʾ��ͬ�����֣���9-14λ��ʾ��ͬ����Ĳ�ͬ����
	char name[50];
	char author[30];
	char press[50];
	char date[15];
	unsigned* sumNumber;	//ͬһ���������
	unsigned* currNumber;	//ͬһ����Ŀ����
	unsigned* brdNumber;	//ͬһ����Ľ����
	double price;
	BookType bookType;

	BookState state;
	char personId[9];

	struct BookList* diffNext;//��ͬ����һ����
	struct BookList* sameNext;//��ͬ����һ����
} BookList, *BLNode, Book;

typedef struct BookStock {
	BLNode book;			//�鼮����
	BLNode periodical;		//�ڿ�����
	BLNode press;			//��������

	BLNode _for_convenience[3];	//Ϊ��������Լ�id��ȷ���ĸ����������
	BLNode _bookMap[1000000];	//����id��ɢ�б�
} BookStock;

/*   ��ʼ������ͼ�����ϵͳ   */
BookStock* initBookStock();

/*   ��ͼ����м���һ���� ������ʾ���ַ���ͷָ�� �磺��ӳɹ�  */
const char * insertBook(BookStock* bookStock, const char* id, const char* name, const char* author, const char* press, const char* date, double price);

/*   �ж��Ƿ�Ϊͬһ���飬�Ƿ���1���񷵻�0   */
int isSameBook(const char* id1, const char* id2);

/*   ����id��һ���飬�ҵ����ص�ַ���Ҳ�������NULL   */
Book* searchBook_id(BookStock* bookStock, const char* id);

/*   �����ֲ��ң����ز������������ҽ������books�У�����maxNumberΪ����������������books��Χ����bookTypeָ�����ҷ�Χ   */
int search_name(BookStock* bookStock, const char* name, Book** books, int maxNumber, BookType bookType);

/*   ���ܲ�����ļ�ƣ�����ͬsearch_name�����һ��maxMatch����ָ������ƥ���ֽ�����һ������ռ2-3���ֽڣ�   */
int intelligentSearch_name(BookStock* bookStock, const char* name, Book** books, int maxNumber, BookType bookType, int maxMatch);

/*   ��ͼ�����ɾ��һ���飬����ֵ1Ϊɾ���ɹ�������ֵ0Ϊɾ��ʧ�ܣ�û�д��飩,����ֵ-1Ϊ�ѽ������ɾ��   */
int deleteBook(BookStock* bookStock, const char* id);

/*   �������Ͳ����飬���ز������������ҽ������books�У�����maxNumberΪ����������������books��Χ��   */
int searchBooks_type(BookStock* bookStock, Book** books, int maxNumber, BookType bookType);

/*   ����id������ͬ�飬���ز������������ҽ������books�У�����maxNumberΪ����������������books��Χ��   */
int searchSameBooks_id(BookStock* bookStock, Book** books, int maxNumber, const char* id);

#endif //LIBRARY_BOOK_H
