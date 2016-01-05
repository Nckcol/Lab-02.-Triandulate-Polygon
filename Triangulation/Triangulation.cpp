// Triangulation.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Triangulation.h"

#define MAX_LOADSTRING 100
#define WIDTH 600
#define HEIGHT 400

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void init()
{

}

void draw(HDC hdc)
{
    GPolygon mainPoly;

    //mainPoly.insert(GPoint(0, 20));
    //mainPoly.insert(GPoint(30, 10));
    //mainPoly.insert(GPoint(10, 0));
    //mainPoly.insert(GPoint(20, -10));
    //mainPoly.insert(GPoint(10, -20));
    //mainPoly.insert(GPoint(0, -10));
    //mainPoly.insert(GPoint(-30, -20));
    //mainPoly.insert(GPoint(0, 10));
    //mainPoly.insert(GPoint(-20, 10));

    //mainPoly.insert(GPoint(-200, 300));
    mainPoly.insert(GPoint(-100, 100));
    mainPoly.insert(GPoint(0, 200));
    //mainPoly.insert(GPoint(0, 300));
    //mainPoly.insert(GPoint(200, 200));
    mainPoly.insert(GPoint(200, 100));
    mainPoly.insert(GPoint(100, -200));
    mainPoly.insert(GPoint(0, 0));
    mainPoly.insert(GPoint(-200, -200));

    list < GPolygon * > * triangles = triangulate(mainPoly);

    for (list<GPolygon *>::iterator triangle = triangles->begin(); triangle != triangles->end(); ++triangle)
    {
        int n = (*triangle)->size();
        GVertex * vertex = (*triangle)->v();
        MoveToEx(hdc, WIDTH/2 + vertex->point().x, HEIGHT/2 + vertex->point().y, NULL);
        
        for (int i = 0; i < n; i++)
        {
            vertex = vertex->ccw();
            LineTo(hdc, WIDTH/2 + vertex->point().x, HEIGHT/2 + vertex->point().y);
        }
    }
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    init();

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TRIANGULATION, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TRIANGULATION));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
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
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TRIANGULATION));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TRIANGULATION);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            draw(hdc);
            EndPaint(hWnd, &ps);
        }
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

list<GPolygon *> *triangulate(GPolygon  &p)
{
    list<GPolygon*> *triangles = new list<GPolygon*>;
    if (p.size() == 3)
        triangles->push_back(&p);
    else {
        findConvexVertex(p);
        GVertex *d = findIntrudingVertex(p);
        if (d == NULL) {     
            GVertex  *c = p.neighbor(CLOCKWISE);
            p.advance(COUNTER_CLOCKWISE);
            GPolygon *q = p.split(c);
            triangles->merge(*triangulate(p));
            triangles->push_back(q);
        }
        else {           
            GPolygon   *q = p.split(d);
            triangles->merge(*triangulate(*q));
            triangles->merge(*triangulate(p));
        }
    }
    return triangles;
}

void findConvexVertex(GPolygon &p)
{
    GVertex *a = p.neighbor(COUNTER_CLOCKWISE);
    GVertex *b = p.v();
    GVertex *c = p.neighbor(CLOCKWISE);
    while (c->classify(*a, *b) != RIGHT) {
        a = b;
        b = p.advance(CLOCKWISE);
        c = p.neighbor(CLOCKWISE);
    }
}

GVertex * findIntrudingVertex(GPolygon &p)
{
    GVertex *a = p.neighbor(COUNTER_CLOCKWISE);
    GVertex *b = p.v();
    GVertex *c = p.advance(CLOCKWISE);
    GVertex *d = NULL;    
    double bestD = -1.0; 
    GEdge ca(c->point(), a->point());
    GVertex *v = p.advance(CLOCKWISE);
    while (v != a) {
        if (pointInTriangle(*v, *a, *b, *c)) {
            double dist = v->distance(ca);
            if (dist > bestD) {
                d = v;
                bestD = dist;
            }
        }
        v = p.advance(CLOCKWISE);
    }
    p.setV(b);
    return d;
}

bool pointInTriangle(GPoint p, GPoint a, GPoint b, GPoint c)
{
    return ((p.classify(a, b) != LEFT) &&
        (p.classify(b, c) != LEFT) &&
        (p.classify(c, a) != LEFT));
}
