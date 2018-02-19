; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CFFTView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "FFT.h"
LastPage=0

ClassCount=6
Class1=CFFTApp
Class2=CFFTDoc
Class3=CFFTView
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=CFilterParaDlg
Resource3=IDD_DIALOG1

[CLS:CFFTApp]
Type=0
HeaderFile=FFT.h
ImplementationFile=FFT.cpp
Filter=N

[CLS:CFFTDoc]
Type=0
HeaderFile=FFTDoc.h
ImplementationFile=FFTDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CFFTDoc

[CLS:CFFTView]
Type=0
HeaderFile=FFTView.h
ImplementationFile=FFTView.cpp
Filter=C
BaseClass=CScrollView
VirtualFilter=VWC
LastObject=CFFTView


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_GAUSS_FILTER




[CLS:CAboutDlg]
Type=0
HeaderFile=FFT.cpp
ImplementationFile=FFT.cpp
Filter=D

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
Command9=ID_FFT
Command10=ID_IFFT
Command11=ID_CHANGE_FD
Command12=ID_BUTTERWORTH_FILTER
Command13=ID_GAUSS_FILTER
CommandCount=13

[DLG:IDD_DIALOG1]
Type=1
Class=CFilterParaDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552

[CLS:CFilterParaDlg]
Type=0
HeaderFile=FilterParaDlg.h
ImplementationFile=FilterParaDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CFilterParaDlg

