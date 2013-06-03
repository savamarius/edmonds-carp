// Win32Project1.cpp : Defines the entry point for the application.
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

#include<fstream>
#include<cstring>
	char szFileName[MAX_PATH] = "";
int nod_dest,nr_noduri;
int nod1,nod2,cap,legaturi[MAX_PATH][3],poz=0;

typedef struct celula{
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

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);



INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;	
char matr_adiacenta[1000][1000],nr_matr=0;


BOOL CALLBACK nrnoduri(HWND hdlg, UINT message, WPARAM wParam,
LPARAM lParam);
BOOL CALLBACK delatastatura(HWND hdlg, UINT message, WPARAM wParam,
LPARAM lParam);

BOOL CALLBACK muchii(HWND hdlg, UINT message, WPARAM wParam,
LPARAM lParam);

void prand_noduri(HWND hWnd)
	
{

	DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_NRNODURI), hWnd,
(DLGPROC)nrnoduri, NULL);
	

}

void pmuchii(HWND hWnd)
	
{

	DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_ADAUGAREMUCHIE), hWnd,
(DLGPROC)muchii, NULL);
	

}


void pCREARETASTATURA(HWND hWnd)
	
{

	DialogBoxParam(hInst, MAKEINTRESOURCE(IDCREARETASTATURA), hWnd,
(DLGPROC)delatastatura, NULL);
	

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

 void bfs(){
      v=(celula*)malloc(sizeof(celula));
	 v->nod=1;
	 v->next=0; 
	 q=v; 
	 tata[1]=-1; 
	 ok=0;
      memset(viz,0,sizeof(viz)); 
	  viz[1]=1;
     while (v!=0) {
           for (lista p=graf[v->nod];p; p=p->next){
               if (viz[p->nod]==0&&cost[v->nod][p->nod]>0) 
			   { if (p->nod!=n) 
			   {aux=(celula*)malloc(sizeof(celula)); 
			   aux->nod=p->nod; 
			   q->next=aux; 
			   q=aux; 
			   q->next=0;} 
			   tata[p->nod]=v->nod;
			   viz[p->nod]=1;}
                if (viz[n]==1)
				{ok=1; 
				update(); 
				viz[n]=0; }
                }
           v=v->next;
     }
}
          
 



 //functie cu citirea din fisier
void Edmonds_Karp(HWND hdlg){


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
    int ii,x,c,y; fscanf(in,"%d%d",&n,&mm);
    for (ii=1; ii<=mm; ++ii) {
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
    while (ok==1) bfs();
   char msg[30];   sprintf(msg," fluxul maxim este %d  \n",flow);
   MessageBox(hdlg,msg,"Success",MB_OK);
   fclose(in);
}

//////////////
///////////
/////////////
///////////
/////////////
////////////
/////////////////
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
							MessageBox(hdlg,"1","bn",MB_OK);

    FILE*in=fopen(szFileName,"w");
	fprintf(in," ");
	int bState;
	MessageBox(hdlg,"2","bn",MB_OK);
	int nr_noduri1=(int)GetDlgItemInt(hdlg,IDC_EDIT2,&bState,true);
	MessageBox(hdlg,"3","bn",MB_OK);
	  int nr_muchii=0;
	    for(int q=1;q<=nr_noduri1;q++)
			for(int q1=1;q1<=nr_noduri1;q1++)
				if(q1>q)
				{rand_cap[q][q1]=rand()%30;nr_muchii++;}
				else rand_cap[q][q1]=0;
				MessageBox(hdlg,"4","bn",MB_OK);
				fprintf(in,"%d %d \n ",nr_noduri,nr_muchii);
				MessageBox(hdlg,"5","bn",MB_OK);
			for(int q=1;q<=nr_noduri1;q++)
			   for(int q1=1;q1<=nr_noduri1;q1++)
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
			/*scanf("%d %d %d",&nod1,&nod2,&cap);
			fprintf(in," %d %d %d \n",nod1,nod2,cap);
*/
			//printf("doresti sa mai adaugi legaturi?\n 1->NU 0->DA");
		     legaturi[poz][0]=nod1;
	         legaturi[poz][1]=nod2;
	         legaturi[poz][2]=cap;
	 
	 
	}


void scriere_doc(HWND hdlg){


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


// sfarsitul codului

//Procedurile de fereastră a casetelor de dialog

BOOL CALLBACK nrnoduri(HWND hdlg, UINT message, WPARAM wParam,
LPARAM lParam)
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
	

	case IDOK: //S-a apăsat OK
//Functie care citeste un întreg dintr-o casetă
//de text
		
		rand_list(hdlg);
	
		
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



BOOL CALLBACK muchii(HWND hdlg, UINT message, WPARAM wParam,
LPARAM lParam)
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
	

	case IDOK: //S-a apăsat OK
//Functie care citeste un întreg dintr-o casetă
//de text
		
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




BOOL CALLBACK delatastatura(HWND hdlg, UINT message, WPARAM wParam,
LPARAM lParam)
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
//Functie care citeste un întreg dintr-o casetă
//de text

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





















//sfarsit proceduri

// Global Variables:
							// current instance



int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WIN32PROJECT1, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32PROJECT1));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+12);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WIN32PROJECT1);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, "Edmonds-Karp", CS_BYTEALIGNWINDOW|CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS,
      CW_USEDEFAULT, CW_USEDEFAULT,600, 600, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//




//void functie()
//{char szFileName[MAX_PATH];
//	HWND hwnd;
//GetModuleFileName(hInstance, szFileName, MAX_PATH);
//MessageBox(hwnd, szFileName, "This program is:", MB_OK | MB_ICONINFORMATION);
//
//}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


	////////////////////////////////

	//declaratii nu toate iti trebuie
int wmId, wmEvent,ii=0;
	PAINTSTRUCT ps;
	

//////////////////////////////



	
	//PAINTSTRUCT ps;

	HPEN bluePen; 
	HGDIOBJ oldPen;
	HFONT font;
	//HDC hdc;
	static HWND hButton;
				HDC hdc,hdc2;
	LPCSTR Y;
	HICON hicon, hicon_sm;
	HWND d1=NULL, d2=NULL, d3=NULL;
   // HDC hDC;
	OPENFILENAME fon;

	switch (message)
	{
		case WM_CREATE:
      
       hButton = CreateWindow( "button", "RANDOM",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                0, 160, 
                110, 20,
                hWnd, (HMENU) 14,
                hInst, NULL );

	   hButton = CreateWindow( "button", "Start",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                0, 10, 
                70, 20,
                hWnd, (HMENU) 1,
                hInst, NULL );

	   hButton = CreateWindow( "button", "Creare",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                0, 40, 
                130, 20,
                hWnd, (HMENU) 8,
                hInst, NULL );

	   hButton = CreateWindow( "button", "Reinitializare",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                0, 70, 
                130, 20,
                hWnd, (HMENU) 9,
                hInst, NULL );
	
		
		

		hButton = CreateWindow( "button", "Help!",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                0, 100, 
                70, 20,
                hWnd, (HMENU) 5,
                hInst, NULL );

		hButton = CreateWindow( "button", "Exit",
                WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON ,
                0 , 130, 
                70, 20,
                hWnd, (HMENU) 6,
                hInst, NULL );

      break;


	  hdc=GetDC(hWnd);
// funcţii de desenare
ReleaseDC(hWnd,hdc);

	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{

		case 14:

			prand_noduri(hWnd);

			break;
		case 1:
			Edmonds_Karp(hWnd);
		
			break;

		case 9:
			
			

			MessageBox(hWnd,"Reinitializare realizata cu succes!","Succes!",MB_OK);

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

			pCREARETASTATURA(hWnd);



			break;


		case 2:
			////////////////


	               if (szFileName)
					   char szFileName[MAX_PATH] = "";
	//
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
													



			////////////////
			//creare_matrice(szFileName,hWnd);
			char cuvant[100];
			sprintf(cuvant,"%s %d","ana are mere",4);
			MessageBox(hWnd,cuvant,"Success",MB_OK);
			break;

		case 5:
			
			
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			
			
			break;
		case 6:
			DestroyWindow(hWnd);
			break;
		case BUTTON_ID:

			


			
			
			//MessageBox(0,cuvant_out(),"INFORMATII",0);//functie pentru buton
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		////////////////////
		EndPaint(hWnd, &ps);
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
