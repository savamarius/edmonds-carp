﻿// Win32Project1.cpp : Defines the entry point for the application.
//
#define _CRT_SECURE_NO_DEPRECATE
//inceputul codului
#include<conio.h>
#include <comdef.h>
#include <stdlib.h>
#include <stdio.h>
#include "Resource.h"
#include "stdafx.h"
#include "Win32Project1.h"
#include <commdlg.h>
#include <windows.h>
#include<time.h>
#include<fstream>
#include<cstring>
char szFileName[MAX_PATH] = "";
int nod_dest,nr_noduri;
int nod1,nod2,cap,legaturi[MAX_PATH][3],poz=0;
float mem_timp[5];
int cont_timp=1;
void Paint(HWND hwnd);
clock_t begin,end;
int time_spent;
float tmp;
HWND Grafic[10];
typedef struct celula
{
	int nod;
	celula *next;
}*lista;
lista graf[1001],v,q,aux; // graful memorat  ca vectori de liste si variabile auxiliare
int cost[1001][1001],tata[1001],n,mm,flow; //m=nr de muchii   n= valoarea nodului tinta
bool ok,viz[1001]; //variabile  in care se tine minte daca a fost parcurs sau nu un anumit nod
 // functie cu rol de a updata valoarea fluxului


//#include "definitions.h"
#define BUTTON_ID      1001
#define MAX_LOADSTRING 100
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;	
RECT		drawrect,wndrect;
HDC			hDC;

char matr_adiacenta[1000][1000],nr_matr=0;

BOOL CALLBACK nrnoduri(HWND hdlg, UINT message, WPARAM wParam,LPARAM lParam);
BOOL CALLBACK delatastatura(HWND hdlg, UINT message, WPARAM wParam,LPARAM lParam);
BOOL CALLBACK muchii(HWND hdlg, UINT message, WPARAM wParam,LPARAM lParam);

void Paint_Grafic(HWND hwnd);
void prand_noduri(HWND hWnd)
{
	DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_NRNODURI), hWnd,(DLGPROC)nrnoduri, NULL);
}
void pmuchii(HWND hWnd)
{
	DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_ADAUGAREMUCHIE), hWnd,(DLGPROC)muchii, NULL);
}
void pCREARETASTATURA(HWND hWnd)
{
	DialogBoxParam(hInst, MAKEINTRESOURCE(IDCREARETASTATURA), hWnd,(DLGPROC)delatastatura, NULL);
}
///////////////////////////////////////////////functiile pentru flux
void update(){
     int nod=n,min=100000;
     while (tata[nod]!=-1){
           if (cost[tata[nod]][nod]<min) 
			   min=cost[tata[nod]][nod];
           nod=tata[nod];
           }
     nod=n; flow+=min;
     while (tata[nod]!=-1){
           cost[tata[nod]][nod]-=min;
           cost[nod][tata[nod]]+=min;
           nod=tata[nod];
           }
}
 //parcurgearea grafului 
void bfs()
{
     v=(celula*)malloc(sizeof(celula));
	 v->nod=1;
	 v->next=0; 
	 q=v; 
	 tata[1]=-1; 
	 ok=0;
     memset(viz,0,sizeof(viz)); 
	 viz[1]=1;
     while (v!=0) {
           for (lista p=graf[v->nod];p; p=p->next)
		   {
               if (viz[p->nod]==0&&cost[v->nod][p->nod]>0) 
			   {
				   if (p->nod!=n) 
					 {
						  aux=(celula*)malloc(sizeof(celula)); 
						  aux->nod=p->nod; 
						  q->next=aux; 
						  q=aux; 
						  q->next=0;
				     } 
					 tata[p->nod]=v->nod;
					 viz[p->nod]=1;
			   }
                if (viz[n]==1)
				{
					ok=1; 
				    update(); 
				    viz[n]=0; 
				}
           }
      v=v->next;
     }
}
          
//functie cu citirea din fisier
void Edmonds_Karp(HWND hdlg)
{
	HDC hdc;
	OPENFILENAME fon;
	hdc=GetDC(hdlg);
	ZeroMemory(&fon,sizeof(fon));
	fon.lStructSize = sizeof(fon);
	fon.hwndOwner = hdlg;
	fon.lpstrFilter =TEXT("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
	fon.lpstrFile =szFileName;
	fon.nMaxFile = MAX_PATH;
	fon.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	fon.lpstrDefExt =TEXT("txt");
	GetOpenFileName(&fon);
	FILE*in=fopen(szFileName,"r+");
		//  FILE*in=fopen("in.txt","r");
 // FILE* out=fopen("out.txt","r+");
	begin=clock();
	int ii,x,c,y; fscanf(in,"%d%d",&n,&mm);
	for (ii=1; ii<=mm; ++ii) 
	{
		fscanf(in,"%d%d%d",&x,&y,&c); cost[x][y]=c;
		v=(celula*)malloc(sizeof(celula));
		v->nod=y;
		v->next=graf[x]; 
		graf[x]=v;
		v=(celula*)malloc(sizeof(celula));
		v->nod=x;
		v->next=graf[y];
		graf[y]=v;
	}
		ok=1;
		while (ok==1) 
			bfs();
		end=clock();
		 char msg[30];   
		 sprintf(msg," fluxul maxim este %d  \n",flow);
		 MessageBox(hdlg,msg,"Success",MB_OK);
		 fclose(in);
}

/////////////
//functie de crearea aleatoare a matrici de vecini impreuna cu capacitatile lor
void rand_list(HWND hdlg)
{
	int rand_cap[MAX_PATH][MAX_PATH];
	HDC hdc;
	OPENFILENAME fon;
	hdc=GetDC(hdlg);
	ZeroMemory(&fon,sizeof(fon));
	fon.lStructSize = sizeof(fon);
	fon.hwndOwner = hdlg;
	fon.lpstrFilter =TEXT("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
	fon.lpstrFile =szFileName;
	fon.nMaxFile = MAX_PATH;
	fon.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	fon.lpstrDefExt =TEXT("txt");
	GetOpenFileName(&fon);
//	MessageBox(hdlg,"1","bn",MB_OK);
	 FILE*in=fopen(szFileName,"w");
	fprintf(in," ");
	int bState;
	//MessageBox(hdlg,"2","bn",MB_OK);
	int nr_noduri1=(int)GetDlgItemInt(hdlg,IDC_EDIT2,&bState,true);
	//MessageBox(hdlg,"3","bn",MB_OK);
	 int nr_muchii=0;
	 for(int q=1;q<=nr_noduri1;q++)
		for(int q1=1;q1<=nr_noduri1;q1++)
			if(q1>q)
			{
				rand_cap[q][q1]=rand()%30;nr_muchii++;}
			else 
				rand_cap[q][q1]=0;
		//	MessageBox(hdlg,"4","bn",MB_OK);
			fprintf(in,"%d %d \n ",nr_noduri1,nr_muchii);
			//	MessageBox(hdlg,"5","bn",MB_OK);
			for(int q=1;q<=nr_noduri1;q++)
			   for(int q1=1;q1<=nr_noduri1;q1++)
	               if(q1>q)   
					 fprintf(in,"%d %d %d \n",q,q1,rand_cap[q][q1]);
	fclose(in);
}
//functie creare graf de la tastatura
void creare_de_la_tast(HWND hdlg)
{
	int bState;
	//printf(" nodul 1,nodul 2, capacitatea");
	nod1= (int)GetDlgItemInt(hdlg,IDC_EDIT1,&bState,true);
	nod2= (int)GetDlgItemInt(hdlg,IDC_EDIT2,&bState,true);
	 cap=(int)GetDlgItemInt(hdlg,IDC_EDIT3,&bState,true);
	///scanf("%d %d %d",&nod1,&nod2,&cap);
	//fprintf(in," %d %d %d \n",nod1,nod2,cap);
	//printf("doresti sa mai adaugi legaturi?\n 1->NU 0->DA");
	legaturi[poz][0]=nod1;
	legaturi[poz][1]=nod2;
	legaturi[poz][2]=cap;
}
void scriere_doc(HWND hdlg)
{
	HDC hdc;
	OPENFILENAME fon;
	hdc=GetDC(hdlg);
	ZeroMemory(&fon,sizeof(fon));
	fon.lStructSize = sizeof(fon);
	fon.hwndOwner = hdlg;
	fon.lpstrFilter =TEXT("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
	fon.lpstrFile =szFileName;
	fon.nMaxFile = MAX_PATH;
	fon.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	fon.lpstrDefExt =TEXT("txt");
	GetOpenFileName(&fon);
	FILE*f=fopen(szFileName,"r+");
	fprintf(f,"%d %d \n",nod_dest,nr_noduri);
	for (int ii=0;ii<poz;ii++)
		fprintf(f,"%d %d %d\n",legaturi[ii][0],legaturi[ii][1],legaturi[ii][2]);
}

void reinitializare(char*fisier,HWND hdlg)
{
	HDC hdc;
	OPENFILENAME fon;
	hdc=GetDC(hdlg);
	ZeroMemory(&fon,sizeof(fon));
	fon.lStructSize = sizeof(fon);
	fon.hwndOwner = hdlg;
	fon.lpstrFilter =TEXT("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
	fon.lpstrFile =szFileName;
	fon.nMaxFile = MAX_PATH;
	fon.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	fon.lpstrDefExt =TEXT("txt");
	GetOpenFileName(&fon);
	FILE*f=fopen(szFileName,"w");
	fprintf(f," ");
	fclose(f);

//	de incercat ce provoaca crashul------------
//nod_dest=NULL,nr_noduri=NULL;
//nod1=NULL,nod2=NULL,cap=NULL,poz=0;
//
// graf[1001]=NULL,v=NULL,q=NULL,aux=NULL; // graful memorat  ca vectori de liste si variabile auxiliare
//tata[1001]=NULL,n=NULL,mm=NULL,flow=NULL; //m=nr de muchii   n= valoarea nodului tinta
// ok=NULL,viz[1001]=NULL;
//
//
}
void afisare_grafice(HWND hWnd)
{ //HDC hdc;
//
//PAINTSTRUCT ps;
//	hdc = BeginPaint(hWnd, &ps);
//	
//
//	int poz_i=220;
//	
//	for(int j=0;j<cont_timp;j++)
//	{
//	
//	//Rectangle(hdc, 200,20,1223,650);
//	Rectangle(hdc, 220,600,poz_i+50,600-mem_timp[j]*100);
//	for(int j1=220;j1<=600;j1++)
//			 for (int j2=poz_i+50;j2<600-mem_timp[j];j2++)
//				 SetPixel( hdc, j1, j2,RGB(222,0,100));
//	poz_i+=50;
//	
//	}
//		EndPaint(hWnd, &ps);

	HDC hdc; //contextul grafic
	PAINTSTRUCT ps;
	RECT rect; //Obiect dreptunghi
	hdc = BeginPaint(hWnd, &ps); //Obţinerea contextului grafic
	GetClientRect(hWnd,&rect); //Obţinerea suprafeţei de desenare
	//Scrierea unui text în fereastră
	DrawText(hdc,"Primul program",-1,&rect,DT_CENTER|DT_VCENTER);
	EndPaint(hWnd, &ps);
}
// sfarsitul codului
//Procedurile de fereastră a casetelor de dialog


BOOL CALLBACK nrnoduri(HWND hdlg, UINT message, WPARAM wParam,LPARAM lParam)
{
	//int bState;
	static int ok_cancel=TRUE; //stabileste dacă s-a închis cu OK sau
	//Cancel
	switch (message)
	{
		case WM_DESTROY:
			EndDialog(hdlg,ok_cancel);
		return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam))
		{
			case IDOK: //S-a apăsat OK
		//Functie care citeste un întreg dintr-o casetă	de text
				rand_list(hdlg);
				ok_cancel=TRUE;
				//Functia care duce la încheierea dialogulu
				EndDialog(hdlg, true);
			break;
			case IDCANCEL: //S-a apăsat Cancel
				ok_cancel=FALSE;
				EndDialog(hdlg, false);
			break;
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK muchii(HWND hdlg, UINT message, WPARAM wParam,LPARAM lParam)
{
	//int bState;
	static int ok_cancel=TRUE; //stabileste dacă s-a închis cu OK sau
	//Cancel
	switch (message)
	{
		case WM_DESTROY:
			EndDialog(hdlg,ok_cancel);
		return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDOK: //S-a apăsat OK
					//Functie care citeste un întreg dintr-o casetă	de text
					creare_de_la_tast(hdlg);
					ok_cancel=TRUE;
					//Functia care duce la încheierea dialogului
					EndDialog(hdlg, true);
				break;
				case IDCANCEL: //S-a apăsat Cancel
					ok_cancel=FALSE;
					EndDialog(hdlg, false);
				break;
			}
			return TRUE;
		}
	return FALSE;
}

BOOL CALLBACK delatastatura(HWND hdlg, UINT message, WPARAM wParam,LPARAM lParam)
{
	int bState;
	static int ok_cancel=TRUE; //stabileste dacă s-a închis cu OK sau
	//Cancel
	switch (message)
	{
		case WM_DESTROY:
			EndDialog(hdlg,ok_cancel);
		return TRUE;
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDC_BUTTON1:
				pmuchii(hdlg);
		
				   poz++;

				break;
				case IDC_BUTTON2:
					nod_dest=(int)GetDlgItemInt(hdlg,IDC_EDIT2,&bState,true);
				break;
				case IDC_BUTTON3:
					 nr_noduri=(int)GetDlgItemInt(hdlg,IDC_EDIT3,&bState,true);
				break;
				case IDOK: //S-a apăsat OK
					//Functie care citeste un întreg dintr-o casetă de text
					//creare_de_la_tast();
					scriere_doc(hdlg);
					ok_cancel=TRUE;
					//Functia care duce la încheierea dialogului
					EndDialog(hdlg, true);
				break;
				case IDCANCEL: //S-a apăsat Cancel
					ok_cancel=FALSE;
					EndDialog(hdlg, false);
				break;
			}
			return TRUE;
		}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//sfarsit proceduri

// Global Variables:
							// current instance

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine, int nCmdShow)
{
	// TODO: Place code here.
	MSG msg={};

	// Initialize global strings
//	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	 const wchar_t CLASS_NAME[]  = L"Sample Window Class"; //crearea unei clase in clasa windows
	WNDCLASS wc = { };
	wc.style			= CS_HREDRAW|CS_VREDRAW;
	wc.lpfnWndProc		= WndProc;
	wc.hInstance		= hInstance;
	wc.lpszClassName	= szWindowClass;
	wc.hIcon			= LoadIcon(NULL,IDI_SHIELD);// imi incarca un bmp in stanga sus ca iconita
	wc.hCursor			= LoadCursor(NULL, IDC_HAND);
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+2);
	wc.lpszMenuName = NULL;
	RegisterClass(&wc);
	hInst = hInstance; // Store instance handle in our global variable
	HWND  hWnd = CreateWindowEx(0,						// Optional window styles.
						szWindowClass,					  // Window class. clasa din care face parte fereastra
						"Edmonds-Karp Alghorithm",		 // Window text// textul pe care l vreau afisat in taskbar
						WS_OVERLAPPEDWINDOW|CS_BYTEALIGNWINDOW|WS_BORDER,			 // Window style
						 // Size and position
						  0, 0,1350, 720, // primele doua sunt x, y din stanga sus...iar urmatoareale latimea si inaltimea
						 NULL,// Parent window  
						  NULL, // Menu
						  hInstance,// Instance handle
						  NULL); // Additional application data
	// Test if the window was created successfully
	if (hWnd==NULL)
   {
	   MessageBox(NULL, TEXT("Window could not be opened!"),szWindowClass, MB_ICONERROR);
      return 0;
   }
   ShowWindow(hWnd, SW_MAXIMIZE);
   UpdateWindow(hWnd);

   hDC = GetDC(hWnd);
   Paint(hWnd);
	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)>0)
	{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
	}
	return 0;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//////////////////////////////////////////////////////////////////////////
//void functie()
//{char szFileName[MAX_PATH];
//	HWND hwnd;
//GetModuleFileName(hInstance, szFileName, MAX_PATH);
//MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
//
//}
void timp_edmonds_carp(HWND hWnd)
{
	if(cont_timp<=7)
	{
	Edmonds_Karp(hWnd);
	//MessageBox(hWnd,"1","check",MB_OK);
	char timp[10];
	tmp=(float)(end-begin)/CLOCKS_PER_SEC;
	mem_timp[cont_timp]=tmp;
	cont_timp++;
	sprintf(timp,"%f ",tmp);
	MessageBox(hWnd,timp,"TIMP",MB_OK);
	}
	else
		MessageBox(hWnd,"Ati depasit numarul maxim de 7 comparatii\nApasati reinitializare","Warning",MB_OK);
	//sprintf(timp,"%s",time_spent);
	//MessageBox(hWnd,"3","check",MB_OK);
	//	MessageBox(hWnd,timp,"Timp",MB_OK);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT  rect = { 110,110, 200, 200};
	int wmId=0, wmEvent=0;
	HWND hButton1=NULL,hButton2=NULL,hButton3=NULL,hButton4=NULL,hButton5=NULL,hButton6=NULL,hButton7=NULL;
	HDC hdc=NULL;
	PAINTSTRUCT ps;
	HBRUSH      brLogBrush;
	 LOGBRUSH    LogBrush;
	OPENFILENAME fon;
	static POINT p1;
	static POINT p2;
	switch (message)
	{
		//functie pentru desenarea pe suprafata de lucru a diferitelor elemente de grafica
		case WM_LBUTTONDOWN:
				
		p1.x=LOWORD(lParam);
		p1.y=HIWORD(lParam);
		
		if (p1.x<690 && p1.x>10 && p1.y>240 && p1.y<675)
				{

		HWND Grafic= CreateWindowEx( NULL,"button", "" ,
				WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
				p1.x,p1.y, 
				20,20,
				hWnd, NULL,
				hInst, NULL );
		hdc=GetDC(hWnd); //Obtinerea contextului grafic
	//	Ellipse(hdc,p2.x-8,p2.y-8,p2.x+8,p2.y+8);
	//	MoveToEx(hdc,p2.x,p2.y,NULL);
	//	LineTo(hdc,p1.x,p1.y);
		
		p2=p1;
		ReleaseDC(hWnd,hdc); }//Eliberarea contextului grafic
		return 0;
		
	
		case WM_CREATE:
			GetClientRect(hWnd,&wndrect);	
			hButton2 = CreateWindowEx( NULL,"button", "Random",
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
						wndrect.left+10 , wndrect.top+130, 
						130, 25,
						hWnd, (HMENU) 14,
						hInst, NULL );
			 hButton1 = CreateWindowEx( NULL,"BUTTON", "Start",
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON  ,
						wndrect.left+10,wndrect.top+ 10, 
						130, 25,
						hWnd, (HMENU) 1,
						hInst, NULL );

			 hButton3 = CreateWindowEx(NULL, "button", "Creare",
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
						wndrect.left+10, wndrect.top+40, 
						130, 25,
						hWnd, (HMENU) 8,
						hInst, NULL );

			 hButton4 = CreateWindowEx(NULL, "button", "Reinitializare",
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
						wndrect.left+10, wndrect.top+70, 
						130, 25,
						hWnd, (HMENU) 9,
						hInst, NULL );
	
			hButton5 = CreateWindowEx(NULL, "button", "Help!",
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
						wndrect.left+10, wndrect.top+100, 
						130, 25,
						hWnd, (HMENU) 5,
						hInst, NULL );

			hButton6 = CreateWindowEx( NULL,"button", "Grafic",
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
						wndrect.left+10, wndrect.top+160, 
						130, 25,
						hWnd, (HMENU) 25,
						hInst, NULL );

			hButton7 = CreateWindowEx( NULL,"button", "Exit",
						WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
						wndrect.left+10, wndrect.top+190, 
						130, 25,
						hWnd, (HMENU) 6,
						hInst, NULL );
		break;
			case WM_COMMAND:
				wmId    = LOWORD(wParam);
				wmEvent = HIWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
				case 14:
					prand_noduri(hWnd);   //functie ce creaza random nodurile si legaturile dintre ele intr-un graf orientat
				break;
				case 1:
					timp_edmonds_carp(hWnd);
				break;
				case 9:
					reinitializare(szFileName,hWnd);
					
				break;
				case 7:
				 if (szFileName)
				 {
					char szFileName[MAX_PATH] = "";
				 }
				hdc=GetDC(hWnd);
				ZeroMemory(&fon,sizeof(fon));
				fon.lStructSize = sizeof(fon);
				fon.hwndOwner = hWnd;
				fon.lpstrFilter =TEXT("Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0");
				fon.lpstrFile =szFileName;
				fon.nMaxFile = MAX_PATH;
				fon.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
				fon.lpstrDefExt =TEXT("txt");
				GetOpenFileName(&fon);
				break;
				case 8:
					pCREARETASTATURA(hWnd);//functie folosita la crearea arborelui de la tastatura
				break;
				case 5:
					DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
				case 6:
					PostQuitMessage(0);
				break;
				case 25:
					Paint_Grafic(hWnd);
				break;
				default:
					return DefWindowProc(hWnd, message, wParam, lParam);
				}
				break;
		case WM_PAINT:
				
				hdc=BeginPaint(hWnd,&ps);
				GetClientRect(hWnd,&rect);
				LogBrush.lbStyle = BS_HATCHED;
				 LogBrush.lbColor = RGB(255, 0, 255);
				LogBrush.lbHatch = HS_DIAGCROSS;
				brLogBrush = CreateBrushIndirect(&LogBrush);
			    SelectObject(hdc, brLogBrush);
				Rectangle(hdc, 0, 0, 150,230);
				int jj,jjj;
				for( jj=0;jj<700;jj++)
					for( jjj=0;jjj<300;jjj++)
					{
						Sleep(0.2);
						SetPixel(hdc, jj, jjj, RGB(255,53,246));
					}
				for( jj=701;jj<1360;jj++)
					for( jjj=0;jjj<500;jjj++)
					{
						Sleep(0.6);
						SetPixel(hdc, jj, jjj, RGB(255,53,246));
					}
				DeleteObject(brLogBrush);
				
				
				
				EndPaint(hWnd,&ps);
				
			//////////////////pentru desenare
				break;
		case WM_ACTIVATE:
			Paint(hWnd);
			break;
		case WM_DESTROY:
				PostQuitMessage(0);
			break;
		default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		case WM_INITDIALOG:
			return (INT_PTR)TRUE;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
			{
				EndDialog(hDlg, LOWORD(wParam));
				return (INT_PTR)TRUE;
			}
			break;
	}
	return (INT_PTR)FALSE;
}
void Paint(HWND hwnd)
{
	RECT wndrect;
	GetClientRect(hwnd,&wndrect);
	drawrect.bottom = wndrect.bottom ;
	drawrect.left	= wndrect.left + 700;
	drawrect.right	= wndrect.right;
	drawrect.top	= wndrect.top ;
	FrameRect(hDC,&drawrect,CreateSolidBrush(0xffffff));
	drawrect.bottom = wndrect.bottom - 1;
	drawrect.left	= wndrect.left + 699;
	drawrect.right	= wndrect.right -1;
	drawrect.top	= wndrect.top +1;
	FrameRect(hDC,&drawrect,CreateSolidBrush(0xffffff));
	drawrect.bottom = 230;
	drawrect.left	= NULL;
	drawrect.right	= wndrect.left + 700;
	drawrect.top	= NULL;
	FrameRect(hDC,&drawrect,CreateSolidBrush(0xffffff));
	drawrect.bottom = 231;
	drawrect.left	= NULL;
	drawrect.right	= wndrect.left + 700;
	drawrect.top	= NULL;
	FrameRect(hDC,&drawrect,CreateSolidBrush(0xffffff));
}

void Paint_Grafic(HWND hwnd)
{
	char nume[10];
	/*HPEN pen;
	PAINTSTRUCT ps;
	HDC hdc=NULL;
	hdc=BeginPaint(hwnd,&ps);
	pen=CreatePen(PS_SOLID,2,RGB(0,0,255));
	SelectObject(hdc,pen);
	Rectangle(hdc,0,600,100,0);
	Rectangle(hdc,poz_i+50,,poz_i+150,600-tmp*100);
	EndPaint(hwnd,&ps);
	*/
	//calculare coeficient inmultire
	float coeficient=0;
	float timp_maxim=0;
	for(int yy=0;yy<=cont_timp;yy++)
		if(timp_maxim<mem_timp[yy])
			timp_maxim=mem_timp[yy];
	coeficient=400/(timp_maxim*100)*100*1.6;
	for(int q=1;q<=cont_timp;q++)
			DestroyWindow(Grafic[q]);
	for(int kkk=1;kkk<=cont_timp;kkk++)
		{sprintf(nume,"Bar %d",kkk);
	
	for(int kappa=1;kappa<100;kappa++)
			Grafic[kkk]= CreateWindowEx( NULL,"button", nume ,
							WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
							701,(kkk-1)*100+5, 
							mem_timp[kkk]*coeficient,100,
							hwnd, NULL,
							hInst, NULL );
	
	}
}