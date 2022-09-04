#include "File.h"
#include <windows.h>

LRESULT CALLBACK WndProcStart(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcLog(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcReg(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcisAdmin(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcAdmin(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcAddBook(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcUser(HWND, UINT, WPARAM, LPARAM);

WNDCLASS wndclassStart; //��ʼ����
WNDCLASS wndclassLog; //��¼����
WNDCLASS wndclassReg; //ע�ᴰ��
WNDCLASS wndclassisAdmin; //����Ա��֤����
WNDCLASS wndclassAdmin; //����Ա����
WNDCLASS wndclassAddBook; //����鼮����
WNDCLASS wndclassUser; //�û����黹�鴰��

HWND hwndStart;
HWND hwndLog;
HWND hwndReg;
HWND hwndisAdmin;
HWND hwndAdmin;
HWND hwndAddBook;
HWND hwndUser;

int iCmdS;
static TCHAR szClassName[] = TEXT("ͼ�����ϵͳ");

BookStock* bookStock;
UserStock* userStock;

User* nowUser;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) {
	userStock = initializeUserStock();
	bookStock = initBookStock();
	/*insertBook(bookStock, "10000001000001", "�ߵ���ѧ���ϣ�", "ͬ�ô�ѧ��ѧϵ", "�ߵȽ���������", "20140704", 38.2);
	insertBook(bookStock, "10000001000002", "�ߵ���ѧ���ϣ�", "ͬ�ô�ѧ��ѧϵ", "�ߵȽ���������", "20140704", 38.2);
	insertBook(bookStock, "10000001000003", "�ߵ���ѧ���ϣ�", "ͬ�ô�ѧ��ѧϵ", "�ߵȽ���������", "20140704", 38.2);
	insertBook(bookStock, "10000002000001", "�ߵ���ѧ���£�", "ͬ�ô�ѧ��ѧϵ", "�ߵȽ���������", "20140704", 38.2);
	insertBook(bookStock, "10000003000001", "��ɢ��ѧ����Ӧ��", "Kenneth H. Rosen", "��е��ҵ������", "20201003", 139.0);
	insertBook(bookStock, "30000001000001", "����һ��Ϊʲô��ô˧", "��ѧ��", "��ѧ��������", "2021519", 100);*/
	bookFilePop(bookStock);
	userFilePop(userStock, bookStock);

	iCmdS = iCmdShow;
	HWND hwnd;
	MSG msg;

	wndclassStart.style = CS_HREDRAW | CS_VREDRAW;
	wndclassStart.lpfnWndProc = WndProcStart;
	wndclassStart.cbClsExtra = 0; 
	wndclassStart.cbWndExtra = 0;
	wndclassStart.hInstance = hInstance;
	wndclassStart.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclassStart.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassStart.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclassStart.lpszMenuName = NULL;
	wndclassStart.lpszClassName = szClassName;
	RegisterClass(&wndclassStart);

	wndclassLog.style = CS_HREDRAW | CS_VREDRAW;
	wndclassLog.lpfnWndProc = WndProcLog;
	wndclassLog.cbClsExtra = 0;
	wndclassLog.cbWndExtra = 0;
	wndclassLog.hInstance = hInstance;
	wndclassLog.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclassLog.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassLog.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclassLog.lpszMenuName = NULL;
	wndclassLog.lpszClassName = TEXT("��¼");
	RegisterClass(&wndclassLog);

	wndclassReg.style = CS_HREDRAW | CS_VREDRAW;
	wndclassReg.lpfnWndProc = WndProcReg;
	wndclassReg.cbClsExtra = 0;
	wndclassReg.cbWndExtra = 0;
	wndclassReg.hInstance = hInstance;
	wndclassReg.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclassReg.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassReg.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclassReg.lpszMenuName = NULL;
	wndclassReg.lpszClassName = TEXT("ע��");
	RegisterClass(&wndclassReg);

	wndclassisAdmin.style = CS_HREDRAW | CS_VREDRAW;
	wndclassisAdmin.lpfnWndProc = WndProcisAdmin;
	wndclassisAdmin.cbClsExtra = 0;
	wndclassisAdmin.cbWndExtra = 0;
	wndclassisAdmin.hInstance = hInstance;
	wndclassisAdmin.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclassisAdmin.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassisAdmin.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclassisAdmin.lpszMenuName = NULL;
	wndclassisAdmin.lpszClassName = TEXT("����Ա��֤");
	RegisterClass(&wndclassisAdmin);

	wndclassAdmin.style = CS_HREDRAW | CS_VREDRAW;
	wndclassAdmin.lpfnWndProc = WndProcAdmin;
	wndclassAdmin.cbClsExtra = 0;
	wndclassAdmin.cbWndExtra = 0;
	wndclassAdmin.hInstance = hInstance;
	wndclassAdmin.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclassAdmin.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassAdmin.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclassAdmin.lpszMenuName = NULL;
	wndclassAdmin.lpszClassName = TEXT("����Ա");
	RegisterClass(&wndclassAdmin);

	wndclassAddBook.style = CS_HREDRAW | CS_VREDRAW;
	wndclassAddBook.lpfnWndProc = WndProcAddBook;
	wndclassAddBook.cbClsExtra = 0;
	wndclassAddBook.cbWndExtra = 0;
	wndclassAddBook.hInstance = hInstance;
	wndclassAddBook.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclassAddBook.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassAddBook.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclassAddBook.lpszMenuName = NULL;
	wndclassAddBook.lpszClassName = TEXT("����鼮");
	RegisterClass(&wndclassAddBook);

	wndclassUser.style = CS_HREDRAW | CS_VREDRAW;
	wndclassUser.lpfnWndProc = WndProcUser;
	wndclassUser.cbClsExtra = 0;
	wndclassUser.cbWndExtra = 0;
	wndclassUser.hInstance = hInstance;
	wndclassUser.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclassUser.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclassUser.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclassUser.lpszMenuName = NULL;
	wndclassUser.lpszClassName = TEXT("�û�");
	RegisterClass(&wndclassUser);

	hwndStart = hwnd = CreateWindow(szClassName,TEXT("ͼ�����ϵͳ"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		830, 550, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);  
		DispatchMessage(&msg);  
	}

	bookFilePush(bookStock);
	userFilePush(userStock);
	return msg.wParam;
}

LRESULT CALLBACK WndProcStart(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	int wmId, wmEvent;
	HDC hdc;  
	PAINTSTRUCT ps;

	static RECT rect;
	static HFONT hFont, hFont1, hFont2;
	static HBRUSH hBrush;

	static HWND hLog;
	static HWND hReg;
	static HWND hExit;
	static HWND hisAdmin;
	static HMENU hMenu;

	switch (message) {
	case WM_CREATE:
		//���ùرհ�ť
		hMenu = GetSystemMenu(hwnd, FALSE);
		int nCloseItem = GetMenuItemCount(hMenu) - 1;
		int nCloseItemID = GetMenuItemID(hMenu, nCloseItem);
		EnableMenuItem(hMenu, nCloseItemID, MF_GRAYED);

		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		hFont = CreateFont(-14, -7, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY, FF_DONTCARE, TEXT("΢���ź�"));
		hFont1 = CreateFont(-100, -33, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY, FF_DONTCARE, TEXT("�����п�"));
		hFont2 = CreateFont(-25, -12, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY, FF_DONTCARE, TEXT("΢���ź�"));

		hLog = CreateWindow(TEXT("button"), TEXT("��¼"), WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT
			, 348, 230, 100, 50, hwnd, (HMENU)4, wndclassStart.hInstance, NULL);
		SendMessage(hLog, WM_SETFONT, (WPARAM)hFont2, NULL);

		hLog = CreateWindow(TEXT("button"), TEXT("ע��"), WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT
			, 348, 300, 100, 50, hwnd, (HMENU)3, wndclassStart.hInstance, NULL);
		SendMessage(hLog, WM_SETFONT, (WPARAM)hFont2, NULL);

		hLog = CreateWindow(TEXT("button"), TEXT("�˳�"), WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT
			, 348, 370, 100, 50, hwnd, (HMENU)2, wndclassStart.hInstance, NULL);
		SendMessage(hLog, WM_SETFONT, (WPARAM)hFont2, NULL);

		hisAdmin = CreateWindow(TEXT("button"), TEXT("����Ա���"), WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT
			, 1, 490, 100, 20, hwnd, (HMENU)1, wndclassStart.hInstance, NULL);
		SendMessage(hisAdmin, WM_SETFONT, (WPARAM)hFont, NULL);

		return 0;

	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		switch (wmId) {
		case 1:
			hwndisAdmin = CreateWindow(TEXT("����Ա��֤"), TEXT("ͼ�����ϵͳ"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
				291, 100, NULL, NULL, wndclassStart.hInstance, NULL);
			MessageBox(NULL, TEXT("���������Ա����"), TEXT("��������"), NULL);
			ShowWindow(hwndisAdmin, iCmdS);
			UpdateWindow(hwndisAdmin);
			break;

		case 2:
			PostQuitMessage(0);
			break;

		case 3:
			hwndReg = CreateWindow(TEXT("ע��"), TEXT("ͼ�����ϵͳ"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
				400, 400, NULL, NULL, wndclassStart.hInstance, NULL);
			ShowWindow(hwndReg, iCmdS);
			UpdateWindow(hwndReg);
			DestroyWindow(hwnd);
			break;

		case 4:
			hwndLog = CreateWindow(TEXT("��¼"), TEXT("ͼ�����ϵͳ"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
				350, 250, NULL, NULL, wndclassStart.hInstance, NULL);
			ShowWindow(hwndLog, iCmdS);
			UpdateWindow(hwndLog);
			DestroyWindow(hwnd);
			break;
		}

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SelectObject(hdc, hFont1);
		SelectObject(hdc, hBrush);

		//Rectangle(hdc, 0, 0, 2000, 1000);
		TextOut(hdc, 80, 55, TEXT("ͼ�����ϵͳ"), 12);

		MoveToEx(hdc, 0, 180, NULL);
		LineTo(hdc, 1000, 180);

		//SelectObject(hdc, hFont2);
		//TextOut(hdc, 370, 230, TEXT("��¼"), 4);
		//TextOut(hdc, 370, 280, TEXT("ע��"), 4);
		//TextOut(hdc, 370, 330, TEXT("�˳�"), 4);

		EndPaint(hwnd, &ps);
		return 0;

	case WM_LBUTTONDOWN:

		return 0;

	case WM_DESTROY:
		DeleteObject(hBrush);
		DeleteObject(hFont1);
		DeleteObject(hFont2);
		DestroyWindow(hwnd);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProcLog(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static HFONT hFont;
	static HWND hLabUsername;  //��̬�ı����û���
	static HWND hLabPassword;  //��̬�ı�������
	static HWND hEditUsername;  //�����ı������
	static HWND hEditPassword;  //���������
	static HWND hBtnLogin;  //��¼��ť
	static HWND hBtnBack;  //���ذ�ť
	static HMENU hMenu;

	static char acc[50];
	static char passwd[50];

	switch (message) {
	case WM_CREATE:
		//���ùرհ�ť
		hMenu = GetSystemMenu(hwnd, FALSE);
		int nCloseItem = GetMenuItemCount(hMenu) - 1;
		int nCloseItemID = GetMenuItemID(hMenu, nCloseItem);
		EnableMenuItem(hMenu, nCloseItemID, MF_GRAYED);

		hFont = CreateFont(-14, -7, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY, FF_DONTCARE, TEXT("΢���ź�"));
		//������̬�ı���ؼ�--�û���
		hLabUsername = CreateWindow(TEXT("static"), TEXT("�û�����"), WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
			0 , 20, 70, 26, hwnd, (HMENU)1, wndclassLog.hInstance, NULL);
		//������̬�ı���ؼ�--����
		hLabPassword = CreateWindow(TEXT("static"), TEXT("���룺"),
			WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT, 0, 56, 70, 26,
			hwnd, (HMENU)2, wndclassLog.hInstance, NULL
		);
		//���������ı���ؼ�
		hEditUsername = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			80, 20, 200, 26,
			hwnd, (HMENU)3, wndclassLog.hInstance, NULL
		);
		//�������������
		hEditPassword = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD | ES_AUTOHSCROLL,80, 56, 200, 26,
			hwnd, (HMENU)4, wndclassLog.hInstance, NULL);
		//������ť�ؼ�
		hBtnLogin = CreateWindow(TEXT("button"), TEXT("��¼"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			80, 92, 200, 30, hwnd, (HMENU)5, wndclassLog.hInstance, NULL
		);
		hBtnBack = CreateWindow(TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			80, 132, 200, 30, hwnd, (HMENU)6, wndclassLog.hInstance, NULL
		);
		//�������ÿؼ�������
		SendMessage(hLabUsername, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hLabPassword, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditUsername, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditPassword, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnLogin, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnBack, WM_SETFONT, (WPARAM)hFont, NULL);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 5:
			GetWindowText(hEditPassword, passwd, 50);
			GetWindowText(hEditUsername, acc, 50);
			nowUser = finduser(acc, userStock);
			if (!nowUser || strcmp(nowUser->passwd, passwd)) {
				MessageBox(hwnd, TEXT("�û������������"), NULL, MB_OK);
				break;
			} else {
				hwndUser = CreateWindow(TEXT("�û�"), TEXT("ͼ�����ϵͳ"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
					1280, 800, NULL, NULL, wndclassStart.hInstance, NULL);
				ShowWindow(hwndUser, iCmdS);
				UpdateWindow(hwndUser);
				DestroyWindow(hwnd);
			}

			/*hwndUser = CreateWindow(TEXT("�û�"), TEXT("ͼ�����ϵͳ"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
				1280, 800, NULL, NULL, wndclassStart.hInstance, NULL);
			ShowWindow(hwndUser, iCmdS);
			UpdateWindow(hwndUser);
			DestroyWindow(hwnd);*/

			DestroyWindow(hwndLog);
			break;
		case 6:
			hwndStart = CreateWindow(szClassName, TEXT("ͼ�����ϵͳ"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
				830, 550, NULL, NULL, wndclassStart.hInstance, NULL);
			ShowWindow(hwndStart, iCmdS);
			UpdateWindow(hwndStart);
			DestroyWindow(hwndLog);
			break;
		}
		return 0;

	case WM_DESTROY:
		DeleteObject(hFont);
		DestroyWindow(hwnd);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProcReg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static HFONT hFont;
	static HWND hLabUsername;  //��̬�ı����û���
	static HWND hLabPassword;  //��̬�ı�������
	static HWND hLabPasswordAgain;  //��̬�ı����ٴ���������
	static HWND hLabId;  //ѧ��
	static HWND hLabName;  //����
	static HWND hEditUsername;  //�����ı������
	static HWND hEditPassword;  //���������
	static HWND hEditPasswordAgain;  //�ٴ����������
	static HWND hEditId;
	static HWND hEditName;
	static HWND hBtnReg;  //ע�ᰴť
	static HWND hBtnBack;  //���ذ�ť
	static HMENU hMenu;

	//һ�鵥ѡ��ť
	static HWND labType;  //��̬�ı���--���
	static HWND radioStu;  //��ѡ��ť--ѧ��
	static HWND radioTea;  //��ѡ��ť--��ʦ

	static UserType ut;
	static char id[50];
	static char name[50];
	static char passwd[50];
	static char passwdA[50];
	static char usrName[50];

	switch (message) {
	case WM_CREATE:
		//���ùرհ�ť
		hMenu = GetSystemMenu(hwnd, FALSE);
		int nCloseItem = GetMenuItemCount(hMenu) - 1;
		int nCloseItemID = GetMenuItemID(hMenu, nCloseItem);
		EnableMenuItem(hMenu, nCloseItemID, MF_GRAYED);

		hFont = CreateFont(-14, -7, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY, FF_DONTCARE, TEXT("΢���ź�")
		);
		//������̬�ı���ؼ�--�û���
		hLabUsername = CreateWindow(TEXT("static"), TEXT("�û�����"), WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
			0, 20, 100, 26, hwnd, (HMENU)1, wndclassLog.hInstance, NULL
		);
		//������̬�ı���ؼ�--����
		hLabPassword = CreateWindow(TEXT("static"), TEXT("���룺"),
			WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT, 0, 56, 100, 26,
			hwnd, (HMENU)2, wndclassLog.hInstance, NULL
		);
		//������̬�ı���ؼ�--�ٴ���������
		hLabPasswordAgain = CreateWindow(TEXT("static"), TEXT("ȷ�����룺"),
			WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT, 0, 92, 100, 26,
			hwnd, (HMENU)7, wndclassLog.hInstance, NULL
		);
		//���������ı���ؼ�
		hEditUsername = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			110, 20, 200, 26,
			hwnd, (HMENU)3, wndclassLog.hInstance, NULL
		);
		//�������������
		hEditPassword = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD | ES_AUTOHSCROLL, 110, 56, 200, 26,
			hwnd, (HMENU)4, wndclassLog.hInstance, NULL
		);
		//�����ٴ����������
		hEditPasswordAgain = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD | ES_AUTOHSCROLL, 110, 92, 200, 26,
			hwnd, (HMENU)8, wndclassLog.hInstance, NULL
		);
		//������ť�ؼ�
		hBtnReg = CreateWindow(TEXT("button"), TEXT("ע��"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			110, 240, 200, 30, hwnd, (HMENU)5, wndclassLog.hInstance, NULL
		);
		hBtnBack = CreateWindow(TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			110, 276, 200, 30, hwnd, (HMENU)6, wndclassLog.hInstance, NULL
		);
		hLabId = CreateWindow(TEXT("static"), TEXT("ѧ�ţ�"),
			WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT, 0, 128, 100, 26,
			hwnd, (HMENU)9, wndclassLog.hInstance, NULL
		);
		hEditId = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 110, 128, 200, 26,
			hwnd, (HMENU)10, wndclassLog.hInstance, NULL
		);
		hLabName = CreateWindow(TEXT("static"), TEXT("������"),
			WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT, 0, 164, 100, 26,
			hwnd, (HMENU)11, wndclassLog.hInstance, NULL
		);
		hEditName = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 110, 164, 200, 26,
			hwnd, (HMENU)12, wndclassLog.hInstance, NULL
		);
		labType = CreateWindow(TEXT("static"), TEXT("���ǣ�"),
			WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT, 0, 200, 100, 26,
			hwnd, (HMENU)13, wndclassLog.hInstance, NULL
		);
		radioStu = CreateWindow(
			TEXT("button"), TEXT("ѧ��"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON /*��ѡ��ť*/ | WS_GROUP,
			130, 200, 50, 26,
			hwnd, (HMENU)14, wndclassLog.hInstance, NULL
		);
		radioTea = CreateWindow(
			TEXT("button"), TEXT("��ʦ"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON /*��ѡ��ť*/,
			220, 200, 50, 26,
			hwnd, (HMENU)15, wndclassLog.hInstance, NULL
		);
		//�������ÿؼ�������
		SendMessage(hLabUsername, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditUsername, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditPassword, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnReg, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnBack, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditPasswordAgain, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hLabPasswordAgain, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hLabId, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hLabPassword, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditId, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hLabName, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditName, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(labType, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(radioStu, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(radioTea, WM_SETFONT, (WPARAM)hFont, NULL);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 6:
			hwndStart = CreateWindow(szClassName, TEXT("ͼ�����ϵͳ"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
				830, 550, NULL, NULL, wndclassStart.hInstance, NULL);
			ShowWindow(hwndStart, iCmdS);
			UpdateWindow(hwndStart);
			DestroyWindow(hwndReg);
			break;

		case 14:
		case 15:
			ut = LOWORD(wParam) - 14;
			break;

		case 5:
			GetWindowText(hEditPassword, passwd, 50);
			GetWindowText(hEditPasswordAgain, passwdA, 50);
			if (strcmp(passwd, passwdA)) {
				MessageBox(hwnd, TEXT("�����������벻һ��"), NULL, MB_OK);
			} else {
				GetWindowText(hEditId, id, 50);
				GetWindowText(hEditName, name, 50);
				GetWindowText(hEditUsername, usrName, 50);

				if (finduser(usrName, userStock)) {
					MessageBox(0, TEXT("�û����Ѵ���"), 0, 0);
					return 0;
				}
				usercreate(userStock, usrName, passwd, id, name, ut);
				MessageBox(hwnd, TEXT("ע��ɹ���"), TEXT("�ɹ�"), MB_OK);
				hwndStart = CreateWindow(szClassName, TEXT("ͼ�����ϵͳ"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
					830, 550, NULL, NULL, wndclassStart.hInstance, NULL);
				ShowWindow(hwndStart, iCmdS);
				UpdateWindow(hwndStart);
				DestroyWindow(hwndReg);
			}
			break;
		}
		return 0;

	case WM_DESTROY:
		DeleteObject(hFont);
		DestroyWindow(hwnd);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProcisAdmin(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static HWND hBtn;
	static HWND hEditPassword;
	static HFONT hFont;
	static char passwd[50];

	switch (message) {
	case WM_CREATE:

		hFont = CreateFont(-14, -7, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY, FF_DONTCARE, TEXT("΢���ź�"));
		hEditPassword = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_PASSWORD | ES_AUTOHSCROLL, 5, 15, 200, 26,
			hwnd, (HMENU)8, wndclassLog.hInstance, NULL);
		hBtn = CreateWindow(TEXT("button"), TEXT("ȷ��"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			210, 15, 60, 26, hwnd, (HMENU)5, wndclassLog.hInstance, NULL
		);
		SendMessage(hBtn, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditPassword, WM_SETFONT, (WPARAM)hFont, NULL);

		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 5:
			GetWindowText(hEditPassword, passwd, 50);
			if (strcmp(passwd, "zycnb")) {
				MessageBox(hwnd, TEXT("�������"), NULL, MB_OK);
				DestroyWindow(hwnd);
				return 0;
			}
			hwndAdmin = CreateWindow(TEXT("����Ա"), TEXT("ͼ�����ϵͳ"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
				1280, 800, NULL, NULL, wndclassStart.hInstance, NULL);
			ShowWindow(hwndAdmin, iCmdS);
			UpdateWindow(hwndAdmin);
			DestroyWindow(hwnd);
			DestroyWindow(hwndStart);
			break;
		}
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProcAdmin(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static HWND hBtnBack;
	static HWND hBtnExit;
	static HWND hBtnSearchBook;
	static HWND hBtnListBook;
	static HWND hBtnDelBook;
	static HWND hBtnAddBook;
	static HWND hBtnListUser;
	static HWND hBtnDelUser;
	static HWND hBtnListUserBook;
	static HWND hEditText;
	static HWND hEditUser;
	static HWND hEditSearch;
	static HWND radioName;
	static HWND radioInte;
	static HWND radioBook;
	static HWND radioPeriodical;
	static HWND radioPress;
	static HWND radioAll;
	static HFONT hFont;
	static HFONT hFont2;
	static HMENU hMenu;
	static HWND hGroupRange;
	static HWND hGroupMethod;

	HDC hdc;
	PAINTSTRUCT ps;

	static TCHAR ws[100];
	static CHAR s[100];
	static int bookType;
	static int method;
	static int num;
	static Book *books[1000000];
	static char account[100];

	switch (message) {
	case WM_CREATE:
		//���ùرհ�ť
		hMenu = GetSystemMenu(hwnd, FALSE);
		int nCloseItem = GetMenuItemCount(hMenu) - 1;
		int nCloseItemID = GetMenuItemID(hMenu, nCloseItem);
		EnableMenuItem(hMenu, nCloseItemID, MF_GRAYED);

		hFont = CreateFont(-14, -7, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY, FF_DONTCARE, TEXT("΢���ź�"));

		hFont2 = CreateFont(-18, -9, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY, FF_DONTCARE, TEXT("����"));

		Book* bookss[10];
		int nums = searchBooks_type(bookStock, bookss, 10, bt_all);

		hEditText = CreateWindow(TEXT("edit"), TEXT(getinfo_searchBooks_group(nums, bookss)),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_READONLY | ES_MULTILINE
			| WS_VSCROLL | WS_HSCROLL, 5, 15, 1000, 700,
			hwnd, (HMENU)8, wndclassLog.hInstance, NULL);

		hEditUser = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOVSCROLL | ES_AUTOHSCROLL
			, 1077, 410, 170, 25,
			hwnd, (HMENU)33, wndclassLog.hInstance, NULL);

		hEditSearch = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOVSCROLL | ES_AUTOHSCROLL
			, 1070, 15, 170, 25,
			hwnd, (HMENU)9, wndclassLog.hInstance, NULL);
		
		hBtnBack = CreateWindow(TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1060, 615, 60, 26, hwnd, (HMENU)5, wndclassLog.hInstance, NULL
		);
		hBtnExit = CreateWindow(TEXT("button"), TEXT("�˳�"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1140, 615, 60, 26, hwnd, (HMENU)40, wndclassLog.hInstance, NULL
		);
		hBtnListBook = CreateWindow(TEXT("button"), TEXT("�г��鼮"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1050, 330, 170, 26, hwnd, (HMENU)50, wndclassLog.hInstance, NULL
		);
		hBtnSearchBook = CreateWindow(TEXT("button"), TEXT("�����鼮"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1050, 240, 170, 26, hwnd, (HMENU)6, wndclassLog.hInstance, NULL
		);
		hBtnDelBook = CreateWindow(TEXT("button"), TEXT("ɾ���鼮(���)"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1050, 270, 170, 26, hwnd, (HMENU)7, wndclassLog.hInstance, NULL
		);
		hBtnAddBook = CreateWindow(TEXT("button"), TEXT("����鼮"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1050, 300, 170, 26, hwnd, (HMENU)30, wndclassLog.hInstance, NULL
		);
		hBtnListUser = CreateWindow(TEXT("button"), TEXT("�о��û�"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1050, 450, 170, 26, hwnd, (HMENU)31, wndclassLog.hInstance, NULL
		);
		hBtnDelUser = CreateWindow(TEXT("button"), TEXT("ɾ���û�(�˺�)"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1050, 480, 170, 26, hwnd, (HMENU)32, wndclassLog.hInstance, NULL
		);
		hBtnListUserBook = CreateWindow(TEXT("button"), TEXT("�о��û������б�(�˺�)"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1050, 510, 170, 26, hwnd, (HMENU)333, wndclassLog.hInstance, NULL
		);

		hGroupMethod = CreateWindow(
			TEXT("button"), TEXT("������ʽ"),
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			1010, 150, 250, 70,
			hwnd, (HMENU)20, wndclassLog.hInstance, NULL
		);
		radioName = CreateWindow(
			TEXT("button"), TEXT("��ͨ����"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON /*��ѡ��ť*/ | WS_GROUP,
			1050, 180, 77, 26,
			hwnd, (HMENU)14, wndclassLog.hInstance, NULL
		);
		radioInte = CreateWindow(
			TEXT("button"), TEXT("��������"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON /*��ѡ��ť*/,
			1150, 180, 77, 26,
			hwnd, (HMENU)15, wndclassLog.hInstance, NULL
		);

		hGroupRange = CreateWindow(
			TEXT("button"), TEXT("������Χ"),
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			1010, 60, 250, 70,
			hwnd, (HMENU)20, wndclassLog.hInstance, NULL
		);
		radioBook = CreateWindow(
			TEXT("button"), TEXT("�鼮"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON | WS_GROUP/*��ѡ��ť*/ ,
			1020, 90, 50, 26,
			hwnd, (HMENU)21, wndclassLog.hInstance, NULL
		);
		radioPeriodical = CreateWindow(
			TEXT("button"), TEXT("�ڿ�"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON /*��ѡ��ť*/,
			1080, 90, 50, 26,
			hwnd, (HMENU)22, wndclassLog.hInstance, NULL
		);
		radioPress = CreateWindow(
			TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON /*��ѡ��ť*/,
			1140, 90, 50, 26,
			hwnd, (HMENU)23, wndclassLog.hInstance, NULL
		);
		radioAll = CreateWindow(
			TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON /*��ѡ��ť*/,
			1200, 90, 50, 26,
			hwnd, (HMENU)24, wndclassLog.hInstance, NULL
		);


		SendMessage(hEditText, WM_SETFONT, (WPARAM)hFont2, NULL);
		SendMessage(hBtnBack, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(radioInte, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(radioName, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(radioBook, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(radioPeriodical, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(radioPress, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(radioAll, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hGroupMethod, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hGroupRange, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnAddBook, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnDelBook, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnDelUser, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnListUser, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnSearchBook, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnExit, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnListBook, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditSearch, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditUser, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnListUserBook, WM_SETFONT, (WPARAM)hFont, NULL);

		SendMessage(radioAll, WM_LBUTTONDOWN, 24, NULL);
		SendMessage(radioAll, WM_LBUTTONUP, 24, NULL);
		SendMessage(radioInte, WM_LBUTTONDOWN, 15, NULL);
		SendMessage(radioInte, WM_LBUTTONUP, 15, NULL);

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 14:
		case 15:
			method = LOWORD(wParam);
			break;

		case 21:
		case 22:
		case 23:
		case 24:
			bookType = LOWORD(wParam);
			break;

		case 5:
			hwndStart = CreateWindow(szClassName, TEXT("ͼ�����ϵͳ"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
				830, 550, NULL, NULL, wndclassStart.hInstance, NULL);
			ShowWindow(hwndStart, iCmdS);
			UpdateWindow(hwndStart);
			DestroyWindow(hwnd);
			break;

		case 6:
			GetWindowText(hEditSearch, s, 100);
			//WcharToChar(s, ws);

			switch (method) {
			case 14:
				num = search_name(bookStock, s, books, 10000000, bookType - 21);
				break;

			case 15:
				if (strlen(s) < 4)
					num = intelligentSearch_name(bookStock, s, books, 1000000, bookType - 21, 1);
				else
					num = intelligentSearch_name(bookStock, s, books, 1000000, bookType - 21, 4);
				break;
			}
			SetWindowText(hEditText, getinfo_searchBooks_group(num, books));
			break;

		case 7:
			GetWindowText(hEditSearch, s, 100);
			if (deleteBook(bookStock, s)) {
				MessageBox(hwnd, TEXT("ɾ���ɹ�"), TEXT("ɾ���ɹ�"), MB_OK);
				num = searchBooks_type(bookStock, books, 1000000, bookType - 21);
				SetWindowText(hEditText, getinfo_searchBooks_group(num, books));
			} else {
				MessageBox(hwnd, TEXT("ɾ��ʧ��"), NULL, MB_OK);
			}

			break;

		case 30:
			hwndAddBook = CreateWindow(TEXT("����鼮"), TEXT("ͼ�����ϵͳ"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
				400, 400, NULL, NULL, wndclassStart.hInstance, NULL);
			ShowWindow(hwndAddBook, iCmdS);
			UpdateWindow(hwndAddBook);
			break;

		case 31:
			SetWindowText(hEditText, getinfo_UserRepRank(rankUserByReputation(userStock), userStock));

			break;

		case 32:
			GetWindowText(hEditUser, account, 100);
			UserNode uu = finduser(account, userStock);
			if (!uu) {
				MessageBox(hwnd, TEXT("�޴��û���ɾ��ʧ��"), NULL, MB_OK);
				break;
			}
			if (uu->cnt) {
				MessageBox(hwnd, TEXT("�û�����δ�����飬ɾ��ʧ��"), NULL, MB_OK);
				break;
			}
			if (deleteuser(account, userStock)) {
				MessageBox(hwnd, TEXT("ɾ���ɹ�"), TEXT("�ɹ�"), MB_OK);
				SetWindowText(hEditText, getinfo_UserRepRank(rankUserByReputation(userStock), userStock));
			} else {
				MessageBox(hwnd, TEXT("ɾ��ʧ��"), NULL, MB_OK);
			}
			break;

		case 333:
			GetWindowText(hEditUser, account, 100);
			UserNode h = finduser(account, userStock);
			booknode w;
			if (h != NULL) {
				w = h->borrowedbook;
			}
			else {
				MessageBox(hwnd, TEXT("δ�ҵ����û�"), 0, 0);
				return 0;
			}
			infobuf[0] = 0;
			if (h->cnt == 0) {
				strcat_s(infobuf, MAXUSER, "�޽����κ��鼮��\r\n");
				SetWindowText(hEditText, infobuf);
				return 0;
			}
			strcat_s(infobuf, MAXUSER, "�ѽ��ĵ��鼮��Ϣ����\r\n");
			while (w->nextbook)
			{
				strcat_s(infobuf, MAXUSER, "��");
				strcat_s(infobuf, MAXUSER, w->nextbook->bookp->name);
				strcat_s(infobuf, MAXUSER, "��(");
				strcat_s(infobuf, MAXUSER, w->nextbook->bookp->id);
				strcat_s(infobuf, MAXUSER, ")");
				char tmp[110] = { 0 };
				strcat_s(infobuf, MAXUSER, "��"); strcat_s(infobuf, MAXUSER, itoa(1900 + w->nextbook->endDates.tm_year, tmp, 10));
				strcat_s(infobuf, MAXUSER, "��"); strcat_s(infobuf, MAXUSER, itoa(w->nextbook->endDates.tm_mon + 1, tmp, 10));
				strcat_s(infobuf, MAXUSER, "��"); strcat_s(infobuf, MAXUSER, itoa(w->nextbook->endDates.tm_mday, tmp, 10));
				strcat_s(infobuf, MAXUSER, "��ǰ�黹\r\n");
				
				w = w->nextbook;
			}
			SetWindowText(hEditText, infobuf);
			break;

		case 50:
			num = searchBooks_type(bookStock, books, 1000000, bookType - 21);
			SetWindowText(hEditText, getinfo_searchBooks_group(num, books));
			break;

		case 40:
			PostQuitMessage(0);
			break;
		}

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SelectObject(hdc, hFont);

		TextOut(hdc, 1020, 15, TEXT("������:"), 7);
		TextOut(hdc, 1015, 410, TEXT("�����û�:"), 9);

		EndPaint(hwnd, &ps);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProcAddBook(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static HFONT hFont;
	static HWND hLabBookId;  //����
	static HWND hLabBookName;  //����
	static HWND hLabBookAu;  //����
	static HWND hLabPress;  //������
	static HWND hLabDate;  //����

	static HWND hEditBookId;  
	static HWND hEditBookName; 
	static HWND hEditBookAu; 
	static HWND hEditPress;
	static HWND hEditDate;

	static HWND hBtnAdd;  //��Ӱ�ť
	static HWND hBtnBack;  //���ذ�ť
	static HMENU hMenu;

	static HWND hLabPrice;  
	static HWND hEditPrice;

	static char id[20];
	static char name[100];
	static char au[50];
	static char press[50];
	static char date[10];
	static char pri[20];
	static double price;
	
	char* res;

	switch (message) {
	case WM_CREATE:
		//���ùرհ�ť
		hMenu = GetSystemMenu(hwnd, FALSE);
		int nCloseItem = GetMenuItemCount(hMenu) - 1;
		int nCloseItemID = GetMenuItemID(hMenu, nCloseItem);
		EnableMenuItem(hMenu, nCloseItemID, MF_GRAYED);

		hFont = CreateFont(-14, -7, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY, FF_DONTCARE, TEXT("΢���ź�")
		);
		
		hLabBookId = CreateWindow(TEXT("static"), TEXT("��ţ�"), WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT,
			0, 20, 100, 26, hwnd, (HMENU)1, wndclassLog.hInstance, NULL
		);
	
		hLabBookName = CreateWindow(TEXT("static"), TEXT("������"),
			WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT, 0, 56, 100, 26,
			hwnd, (HMENU)2, wndclassLog.hInstance, NULL
		);
		
		hLabBookAu = CreateWindow(TEXT("static"), TEXT("���ߣ�"),
			WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT, 0, 92, 100, 26,
			hwnd, (HMENU)7, wndclassLog.hInstance, NULL
		);

		hLabDate = CreateWindow(TEXT("static"), TEXT("���ڣ�"),
			WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT, 0, 164, 100, 26,
			hwnd, (HMENU)7, wndclassLog.hInstance, NULL
		);
		
		hEditBookId = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL,
			110, 20, 200, 26,
			hwnd, (HMENU)3, wndclassLog.hInstance, NULL
		);
		
		hEditBookName = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 110, 56, 200, 26,
			hwnd, (HMENU)4, wndclassLog.hInstance, NULL
		);
		
		hEditBookAu = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 110, 92, 200, 26,
			hwnd, (HMENU)8, wndclassLog.hInstance, NULL
		);
		//������ť�ؼ�
		hBtnAdd = CreateWindow(TEXT("button"), TEXT("���"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			110, 240, 200, 30, hwnd, (HMENU)5, wndclassLog.hInstance, NULL
		);
		hBtnBack = CreateWindow(TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			110, 276, 200, 30, hwnd, (HMENU)6, wndclassLog.hInstance, NULL
		);
		hLabPress = CreateWindow(TEXT("static"), TEXT("�����磺"),
			WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT, 0, 128, 100, 26,
			hwnd, (HMENU)9, wndclassLog.hInstance, NULL
		);
		hEditPress = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 110, 128, 200, 26,
			hwnd, (HMENU)10, wndclassLog.hInstance, NULL
		);
		hEditDate = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 110, 164, 200, 26,
			hwnd, (HMENU)12, wndclassLog.hInstance, NULL
		);
		hLabPrice = CreateWindow(TEXT("static"), TEXT("�۸�"),
			WS_CHILD | WS_VISIBLE | SS_CENTERIMAGE | SS_RIGHT, 0, 200, 100, 26,
			hwnd, (HMENU)13, wndclassLog.hInstance, NULL
		);
		hEditPrice = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL, 110, 200, 200, 26,
			hwnd, (HMENU)14, wndclassLog.hInstance, NULL
		);
		
		//�������ÿؼ�������
		SendMessage(hLabBookId, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditBookId, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditBookName, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnAdd, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnBack, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditBookAu, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hLabBookAu, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hLabPress, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hLabBookName, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditPress, WM_SETFONT, (WPARAM)hFont, NULL);
		//SendMessage(hLabName, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditDate, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hLabPrice, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditPrice, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hLabDate, WM_SETFONT, (WPARAM)hFont, NULL);
		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 5:
			GetWindowText(hEditBookId, id, 20);
			GetWindowText(hEditBookName, name, 100);
			GetWindowText(hEditBookAu, au, 50);
			GetWindowText(hEditDate, date, 10);
			GetWindowText(hEditPress, press, 50);
			GetWindowText(hEditPrice, pri, 20);
			price = atof(pri);
			res = insertBook(bookStock, id, name, au, press, date, price);
			MessageBox(hwnd, TEXT(res), TEXT("���"), MB_OK);
		case 6:
			DestroyWindow(hwnd);
			break;
		}
		return 0;

	case WM_DESTROY:
		DeleteObject(hFont);
		DestroyWindow(hwnd);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LRESULT CALLBACK WndProcUser(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	static HWND hBtnListMyBook;
	static HWND hBtnBorrow;
	static HWND hBtnReturn;
	static HWND hBtnRenewal;
	static HWND hBtnListUser;
	static HWND hBtnBack;
	static HWND hBtnExit;
	static HWND hBtnSearchBook;
	static HWND hBtnListBook;
	static HWND hEditText;
	static HWND hEditSearch;
	static HWND radioName;
	static HWND radioInte;
	static HWND radioBook;
	static HWND radioPeriodical;
	static HWND radioPress;
	static HWND radioAll;
	static HFONT hFont;
	static HFONT hFont2;
	static HMENU hMenu;
	static HWND hGroupRange;
	static HWND hGroupMethod;

	HDC hdc;
	PAINTSTRUCT ps;

	static TCHAR ws[100];
	static CHAR s[100];
	static int bookType;
	static int method;
	static int num;
	static Book *books[1000000];
	static char account[100];

	static struct bookborrowed* bs[50];

	switch (message) {
	case WM_CREATE:
		//���ùرհ�ť
		hMenu = GetSystemMenu(hwnd, FALSE);
		int nCloseItem = GetMenuItemCount(hMenu) - 1;
		int nCloseItemID = GetMenuItemID(hMenu, nCloseItem);
		EnableMenuItem(hMenu, nCloseItemID, MF_GRAYED);

		hFont = CreateFont(-14, -7, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY, FF_DONTCARE, TEXT("΢���ź�"));

		hFont2 = CreateFont(-18, -9, 0, 0, 400, 0, 0, 0, DEFAULT_CHARSET, OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,
			DEFAULT_QUALITY, FF_DONTCARE, TEXT("����"));

		hEditText = CreateWindow(TEXT("edit"), TEXT(showrest(nowUser, userStock, nowUser->state, bs, 50)),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOVSCROLL | ES_AUTOHSCROLL | ES_READONLY | ES_MULTILINE
			| WS_VSCROLL | WS_HSCROLL, 5, 15, 1000, 700,
			hwnd, (HMENU)8, wndclassLog.hInstance, NULL);

		hEditSearch = CreateWindow(TEXT("edit"), TEXT(""),
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOVSCROLL | ES_AUTOHSCROLL
			, 1070, 15, 170, 25,
			hwnd, (HMENU)9, wndclassLog.hInstance, NULL);

		hBtnBack = CreateWindow(TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1060, 615, 60, 26, hwnd, (HMENU)5, wndclassLog.hInstance, NULL
		);
		hBtnExit = CreateWindow(TEXT("button"), TEXT("�˳�"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1140, 615, 60, 26, hwnd, (HMENU)40, wndclassLog.hInstance, NULL
		);
		hBtnListBook = CreateWindow(TEXT("button"), TEXT("�г��鼮"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1050, 270, 170, 26, hwnd, (HMENU)50, wndclassLog.hInstance, NULL
		);
		hBtnSearchBook = CreateWindow(TEXT("button"), TEXT("�����鼮"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1050, 240, 170, 26, hwnd, (HMENU)6, wndclassLog.hInstance, NULL
		);

		hBtnListMyBook = CreateWindow(TEXT("button"), TEXT("�г��ҽ���鼮"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1050, 370, 170, 26, hwnd, (HMENU)51, wndclassLog.hInstance, NULL
		);
		hBtnBorrow = CreateWindow(TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1050, 400, 170, 26, hwnd, (HMENU)52, wndclassLog.hInstance, NULL
		);
		hBtnReturn = CreateWindow(TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1050, 430, 170, 26, hwnd, (HMENU)53, wndclassLog.hInstance, NULL
		);
		hBtnRenewal = CreateWindow(TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1050, 460, 170, 26, hwnd, (HMENU)54, wndclassLog.hInstance, NULL
		);

		hBtnListUser = CreateWindow(TEXT("button"), TEXT("�û�����"),
			WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT,
			1050, 500, 170, 26, hwnd, (HMENU)55, wndclassLog.hInstance, NULL
		);

		hGroupMethod = CreateWindow(
			TEXT("button"), TEXT("������ʽ"),
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			1010, 150, 250, 70,
			hwnd, (HMENU)20, wndclassLog.hInstance, NULL
		);
		radioName = CreateWindow(
			TEXT("button"), TEXT("��ͨ����"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON /*��ѡ��ť*/ | WS_GROUP,
			1050, 180, 77, 26,
			hwnd, (HMENU)14, wndclassLog.hInstance, NULL
		);
		radioInte = CreateWindow(
			TEXT("button"), TEXT("��������"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON /*��ѡ��ť*/,
			1150, 180, 77, 26,
			hwnd, (HMENU)15, wndclassLog.hInstance, NULL
		);

		hGroupRange = CreateWindow(
			TEXT("button"), TEXT("������Χ"),
			WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
			1010, 60, 250, 70,
			hwnd, (HMENU)20, wndclassLog.hInstance, NULL
		);
		radioBook = CreateWindow(
			TEXT("button"), TEXT("�鼮"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON | WS_GROUP/*��ѡ��ť*/,
			1020, 90, 50, 26,
			hwnd, (HMENU)21, wndclassLog.hInstance, NULL
		);
		radioPeriodical = CreateWindow(
			TEXT("button"), TEXT("�ڿ�"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON /*��ѡ��ť*/,
			1080, 90, 50, 26,
			hwnd, (HMENU)22, wndclassLog.hInstance, NULL
		);
		radioPress = CreateWindow(
			TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON /*��ѡ��ť*/,
			1140, 90, 50, 26,
			hwnd, (HMENU)23, wndclassLog.hInstance, NULL
		);
		radioAll = CreateWindow(
			TEXT("button"), TEXT("����"),
			WS_CHILD | WS_VISIBLE | BS_LEFT | BS_AUTORADIOBUTTON /*��ѡ��ť*/,
			1200, 90, 50, 26,
			hwnd, (HMENU)24, wndclassLog.hInstance, NULL
		);


		SendMessage(hEditText, WM_SETFONT, (WPARAM)hFont2, NULL);
		SendMessage(hBtnBack, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(radioInte, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(radioName, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(radioBook, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(radioPeriodical, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(radioPress, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(radioAll, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hGroupMethod, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hGroupRange, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnSearchBook, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnExit, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnListBook, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hEditSearch, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnListMyBook, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnListUser, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnBorrow, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnRenewal, WM_SETFONT, (WPARAM)hFont, NULL);
		SendMessage(hBtnReturn, WM_SETFONT, (WPARAM)hFont, NULL);

		SendMessage(radioAll, WM_LBUTTONDOWN, 24, NULL);
		SendMessage(radioAll, WM_LBUTTONUP, 24, NULL);
		SendMessage(radioInte, WM_LBUTTONDOWN, 15, NULL);
		SendMessage(radioInte, WM_LBUTTONUP, 15, NULL);

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 14:
		case 15:
			method = LOWORD(wParam);
			break;

		case 21:
		case 22:
		case 23:
		case 24:
			bookType = LOWORD(wParam);
			break;

		case 5:
			hwndStart = CreateWindow(szClassName, TEXT("ͼ�����ϵͳ"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
				830, 550, NULL, NULL, wndclassStart.hInstance, NULL);
			ShowWindow(hwndStart, iCmdS);
			UpdateWindow(hwndStart);
			DestroyWindow(hwnd);
			break;

		case 6:
			GetWindowText(hEditSearch, s, 100);
			//WcharToChar(s, ws);

			switch (method) {
			case 14:
				num = search_name(bookStock, s, books, 10000000, bookType - 21);
				break;

			case 15:
				if (strlen(s) < 4)
					num = intelligentSearch_name(bookStock, s, books, 1000000, bookType - 21, 1);
				else
					num = intelligentSearch_name(bookStock, s, books, 1000000, bookType - 21, 4);
				break;
			}
			SetWindowText(hEditText, getinfo_searchBooks_group(num, books));
			break;

		case 7:
			GetWindowText(hEditSearch, s, 100);
			if (deleteBook(bookStock, s)) {
				MessageBox(hwnd, TEXT("ɾ���ɹ�"), TEXT("ɾ���ɹ�"), MB_OK);
				num = searchBooks_type(bookStock, books, 1000000, bookType - 21);
				SetWindowText(hEditText, getinfo_searchBooks_group(num, books));
			}
			else {
				MessageBox(hwnd, TEXT("ɾ��ʧ��"), NULL, MB_OK);
			}

			break;

		case 50:
			num = searchBooks_type(bookStock, books, 1000000, bookType - 21);
			SetWindowText(hEditText, getinfo_searchBooks_group(num, books));
			break;

		case 40:
			PostQuitMessage(0);
			break;

		case 51:
			SetWindowText(hEditText, showrest(nowUser, userStock, nowUser->state, bs, 50));
			break;

		case 52:
			GetWindowText(hEditSearch, s, 100);
			MessageBox(hwnd, TEXT(borrowbook(bookStock, s, nowUser->account, userStock, nowUser->state)), TEXT("����"), MB_OK);
			SetWindowText(hEditText, showrest(nowUser, userStock, nowUser->state, bs, 50));
			break;

		case 53:
			GetWindowText(hEditSearch, s, 100);
			MessageBox(hwnd, TEXT(returnbook(bookStock, s, nowUser->account, userStock, nowUser->state)), TEXT("����"), MB_OK);
			SetWindowText(hEditText, showrest(nowUser, userStock, nowUser->state, bs, 50));

			break;

		case 54:
			GetWindowText(hEditSearch, s, 100);
			MessageBox(hwnd, TEXT(renewalbook(nowUser->account, userStock, s, nowUser->state)), TEXT("����"), MB_OK);
			SetWindowText(hEditText, showrest(nowUser, userStock, nowUser->state, bs, 50));

			break;

		case 55:
			SetWindowText(hEditText, getinfo_UserRepRank(rankUserByReputation(userStock), userStock));
			break;

		}

		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		SelectObject(hdc, hFont);

		TextOut(hdc, 1020, 15, TEXT("������:"), 7);

		EndPaint(hwnd, &ps);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}