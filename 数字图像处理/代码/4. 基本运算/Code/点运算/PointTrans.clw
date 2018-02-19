; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPointTransView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PointTrans.h"
LastPage=0

ClassCount=6
Class1=CPointTransApp
Class2=CPointTransDoc
Class3=CPointTransView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CDlgHistogram
Resource3=IDD_HISTOGRAM

[CLS:CPointTransApp]
Type=0
HeaderFile=PointTrans.h
ImplementationFile=PointTrans.cpp
Filter=N
LastObject=CPointTransApp

[CLS:CPointTransDoc]
Type=0
HeaderFile=PointTransDoc.h
ImplementationFile=PointTransDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CPointTransDoc

[CLS:CPointTransView]
Type=0
HeaderFile=PointTransView.h
ImplementationFile=PointTransView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=CPointTransView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_EQUALIZE




[CLS:CAboutDlg]
Type=0
HeaderFile=PointTrans.cpp
ImplementationFile=PointTrans.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=ID_HISTOGRAM
Command10=ID_LINETRANS
Command11=ID_EQUALIZE
CommandCount=11

[DLG:IDD_HISTOGRAM]
Type=1
Class=CDlgHistogram
ControlCount=1
Control1=IDOK,button,1342242817

[CLS:CDlgHistogram]
Type=0
HeaderFile=dlghistogram.h
ImplementationFile=dlghistogram.cpp
BaseClass=CDialog
LastObject=CDlgHistogram

