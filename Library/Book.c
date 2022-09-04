#include "Book.h"

BookStock* initBookStock() {
	BookStock* bookStock = (BookStock*)malloc(sizeof(BookStock));
	bookStock->_for_convenience[0] = bookStock->book = (BookList*)malloc(sizeof(BookList));
	bookStock->_for_convenience[1] = bookStock->press = (BookList*)malloc(sizeof(BookList));
	bookStock->_for_convenience[2] = bookStock->periodical = (BookList*)malloc(sizeof(BookList));

	bookStock->book->diffNext = NULL;
	bookStock->press->diffNext = NULL;
	bookStock->periodical->diffNext = NULL;

	memset(bookStock->_bookMap, 0, sizeof(bookStock->_bookMap));

	return bookStock;
}

int isSameBook(const char* id1, const char* id2) {
	for (int i = 0; i < 8; ++i) {  //根据id的定义判断前8位是否相同
		if (id1[i] != id2[i]) {
			return 0;
		}
	}
	return 1;
}

//用来计算散列值
int _hash(const char* id) {
	int res = 0;
	for (int i = 0; i < 14; ++i) {
		res += id[i] << (i + 1);
	}
	return res % 1000000;
}

const char * insertBook(BookStock* bookStock, const char* id, const char* name, const char* author,
	const char* press, const char* date, double price) {
	if (id[0] < '1' || id[0] > '3') {
		//printf("书编号错误，没有此书类型。");
		return "书编号错误，没有此书类型\r\n";
	}
	//创建要求的书的节点
	BookList* book = (BookList*)malloc(sizeof(BookList));
	book->sameNext = NULL;
	strcpy(book->name, name);
	strcpy(book->id, id);
	strcpy(book->author, author);
	strcpy(book->press, press);
	strcpy(book->date, date);
	book->price = price;
	book->state = s_instock;

	//找到目标链表
	BookList* head = bookStock->_for_convenience[id[0] - '1'];

	BookList* node = head->diffNext;
	int isNotFound = 1;

	//寻找是否有此书，文档中有详细解释
	while (node) {
		if (isSameBook(id, node->id)) {
			book->sumNumber = node->sumNumber;
			book->brdNumber = node->brdNumber;
			book->currNumber = node->currNumber;
			++* book->sumNumber;
			++* book->currNumber;

			book->sameNext = node->sameNext;
			node->sameNext = book;

			isNotFound = 0;
			break;
		}
		node = node->diffNext;
	}

	//没找到书的操作，文档中有详细解释
	if (isNotFound) {
		book->sumNumber = (unsigned*)malloc(sizeof(unsigned));
		*book->sumNumber = 1;
		book->currNumber = (unsigned*)malloc(sizeof(unsigned));
		*book->currNumber = 1;
		book->brdNumber = (unsigned*)malloc(sizeof(unsigned));
		*book->brdNumber = 0;

		BookList* nodeHead = (BookList*)malloc(sizeof(BookList));
		*nodeHead = *book;
		nodeHead->diffNext = head->diffNext;
		head->diffNext = nodeHead;
		nodeHead->sameNext = book;
	}

	int hashVal = _hash(book->id);
	while (bookStock->_bookMap[hashVal % 1000000]) {
		++hashVal;
	}
	bookStock->_bookMap[hashVal % 1000000] = book;
	return "书籍添加成功\r\n";
}

Book* searchBook_id(BookStock* bookStock, const char* id) {
	BookList* head = NULL;
	if (id[0] < '1' || id[0] > '3') {
		//printf("书编号错误，没有此书类型。");
		return NULL;
	}
	//借助散列表通过id查找
	int hashVal = _hash(id);
	while (bookStock->_bookMap[hashVal % 1000000] && strcmp(bookStock->_bookMap[hashVal % 1000000]->id, id)) {
		++hashVal;
	}

	return bookStock->_bookMap[hashVal % 1000000];
}

int next[255] = { 0 };			//kmp的next数组

//求出next数组
static void _getNext(const char* T) {
	next[0] = -1;
	int len = strlen(T) - 1, i = 0, j = -1;
	while (i < len) {
		if (j == -1 || T[i] == T[j]) {
			++i; ++j;
			next[i] = j;
		}
		else {
			j = next[j];
		}
	}
}

//KMP算法
static int _index_KMP(const char* S, const char* T) {
	int i = -1, j = -1, sLen = strlen(S), tLen = strlen(T);
	_getNext(T);
	while (i < sLen && j < tLen) {
		if (j == -1 || S[i] == T[j]) {
			i++; j++;
		}
		else {
			j = next[j];
		}
	}
	return j == tLen ? i - tLen : -1;
}

//遍历函数，下同
static void _sn_helper(const char* name, Book** books, int maxNumber, BookList* head, int* cnt) {
	while (head) {
		BookList* node = head->sameNext;
		while (node) {
			if (~_index_KMP(node->name, name)) {
				books[(*cnt)++] = node;
				if (*cnt >= maxNumber) {
					return;
				}
			}
			node = node->sameNext;
		}
		head = head->diffNext;
	}
}

int search_name(BookStock* bookStock, const char* name, Book** books, int maxNumber, BookType bookType) {
	int cnt = 0;
	BookList* head;
	if (bookType == bt_all) {
		for (int i = 0; i < 3; ++i) {
			head = bookStock->_for_convenience[i]->diffNext;
			_sn_helper(name, books, maxNumber, head, &cnt);
		}
	}
	else {
		head = bookStock->_for_convenience[(int)bookType]->diffNext;
		_sn_helper(name, books, maxNumber, head, &cnt);
	}
	return cnt;
}

//LCS算法（dp）
int _lcsLength(const char* x, const char* y, int m, int n, int maxMatch) {
	int c[50][50] = { 0 };
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (x[i - 1] == y[j - 1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1]) {
				c[i][j] = c[i - 1][j];
			}
			else {
				c[i][j] = c[i][j - 1];
			}
		}
	}
	return c[m][n] >= maxMatch;
}

static void _isn_helper(const char* name, Book** books, int maxNumber, BookList* head, int* cnt, int maxMatch) {
	while (head) {
		BookList* node = head->sameNext;
		while (node) {
			if (_lcsLength(node->name, name, strlen(node->name), strlen(name), maxMatch)) {
				books[(*cnt)++] = node;
				if (*cnt >= maxNumber) {
					return;
				}
			}
			node = node->sameNext;
		}
		head = head->diffNext;
	}
}

int intelligentSearch_name(BookStock* bookStock, const char* name, Book** books, int maxNumber, BookType bookType, int maxMatch) {
	int cnt = 0;
	BookList* head;
	if (bookType == bt_all) {
		for (int i = 0; i < 3; ++i) {
			head = bookStock->_for_convenience[i]->diffNext;
			_isn_helper(name, books, maxNumber, head, &cnt, maxMatch);
		}
	}
	else {
		head = bookStock->_for_convenience[(int)bookType]->diffNext;
		_isn_helper(name, books, maxNumber, head, &cnt, maxMatch);
	}
	return cnt;
}

//与insertBook对称
int deleteBook(BookStock* bookStock, const char* id) {
	int hashVal = _hash(id);
	while (bookStock->_bookMap[hashVal] && strcmp(bookStock->_bookMap[hashVal]->id, id)) {
		++hashVal;
	}
	BookList* book = bookStock->_bookMap[hashVal];

	if (book) {
		BookList* head;
		if (id[0] < '1' || id[0] > '3') {
			return 0;
		}
		else {
			head = bookStock->_for_convenience[id[0] - '1'];
		}

		BookList* node = head->diffNext;
		while (node) {
			if (isSameBook(id, node->id)) {
				if (!(*book->currNumber)) {
					return -1;
				}
				else if (*book->sumNumber == 1) {
					free(book->sumNumber);
					free(book->currNumber);
					free(book->brdNumber);
					free(book);
					head->diffNext = node->diffNext;
					free(node);
					return 1;
				}
				else {
					while (node && node->sameNext != book) {
						node = node->sameNext;
					}
					if (!node) {
						return 0;
					}
					node->sameNext = book->sameNext;
					--* book->sumNumber;
					--* book->currNumber;
					free(book);
					bookStock->_bookMap[hashVal] = NULL;
					return 1;
				}
			}
			head = head->diffNext;
			node = node->diffNext;
		}
		bookStock->_bookMap[hashVal] = NULL;
	}

	return 0;
}

static void _helper_sbt(BookStock* bookStock, Book** books, int maxNumber, BookList* head, int* cnt) {
	while (head) {
		BookList* nodeHead = head->sameNext;
		while (nodeHead) {
			books[(*cnt)++] = nodeHead;
			if (*cnt >= maxNumber) {
				return;
			}
			nodeHead = nodeHead->sameNext;
		}
		head = head->diffNext;
	}
}

int searchBooks_type(BookStock* bookStock, Book** books, int maxNumber, BookType bookType) {
	int cnt = 0;
	if (bookType == bt_all) {
		for (int i = 0; i < 3 && cnt < maxNumber; i++) {
			_helper_sbt(bookStock, books, maxNumber, bookStock->_for_convenience[i]->diffNext, &cnt);
		}
	}
	else {
		_helper_sbt(bookStock, books, maxNumber, bookStock->_for_convenience[(int)bookType]->diffNext, &cnt);
	}
	return cnt;
}

int searchSameBooks_id(BookStock* bookStock, Book** books, int maxNumber, const char* id) {
	if (id[0] > '3' || id[0] < '1') {
		//printf("错误的编号。");
	}
	else {
		BookList* node = bookStock->_for_convenience[id[0] - '1']->diffNext;
		while (node) {
			if (isSameBook(id, node->id)) {
				int cnt = 0;
				node = node->sameNext;
				while (node) {
					books[cnt++] = node;
					if (cnt >= maxNumber) {
						return maxNumber;
					}
					node = node->sameNext;
				}
				return cnt;
			}
			node = node->diffNext;
		}
	}
	return 0;
}
