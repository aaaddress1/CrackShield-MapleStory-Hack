#pragma hdrstop
#include <windows.h>
#include <vcl.h>
#include <mmsystem.h>
#define JMP(from, to) (int)(((int)to - (int)from) - 5);
//---------------------------------------------------------------------------

bool PebIsDebuggedApproach(){
char result = 0;
__asm{
mov eax, fs:[30h]
mov al, BYTE PTR [eax + 2]
mov result, al
}
return result != 0;
}
bool PebNtGlobalFlagsApproach(){
int result = 0;
__asm{
mov eax, fs:[30h]
mov eax, [eax + 68h]
and eax, 0x70
mov result, eax
}
return (result != 0);
}


String HexEncode(AnsiString Str) {
	unsigned char *s = Str.c_str();
	int l = strlen(s);
	char *result = new char[l << 1 + 1];
	for (int i = 0; i < l; i++) {
		sprintf(result+i*2, "%.2X", s[i]);
	}
	String R = result;
	delete result;
	return R;
}

long GetVkCodeByString(String StringName){
long GetKeyCode = NULL;
	if (StringName=="A")
		GetKeyCode = ('A');
	else if (StringName=="B")
		GetKeyCode = ('B');
	else if (StringName=="C")
		GetKeyCode = ('C');
	else if (StringName=="D")
		GetKeyCode = ('D');
	else if (StringName=="E")
		GetKeyCode = ('E');
	else if (StringName=="F")
		GetKeyCode = ('F');
	else if (StringName=="G")
		GetKeyCode = ('G');
	else if (StringName=="H")
		GetKeyCode = ('H');
	else if (StringName=="I")
		GetKeyCode = ('I');
	else if (StringName=="J")
		GetKeyCode = ('J');
	else if (StringName=="K")
		GetKeyCode = ('K');
	else if (StringName=="L")
		GetKeyCode = ('L');
	else if (StringName=="M")
		GetKeyCode = ('M');
	else if (StringName=="N")
		GetKeyCode = ('N');
	else if (StringName=="O")
		GetKeyCode = ('O');
	else if (StringName=="P")
		GetKeyCode = ('P');
	else if (StringName=="Q")
		GetKeyCode = ('Q');
	else if (StringName=="R")
		GetKeyCode = ('R');
	else if (StringName=="S")
		GetKeyCode = ('S');
	else if (StringName=="T")
		GetKeyCode = ('T');
	else if (StringName=="U")
		GetKeyCode = ('U');
	else if (StringName=="V")
		GetKeyCode = ('V');
	else if (StringName=="W")
		GetKeyCode = ('W');
	else if (StringName=="X")
		GetKeyCode = ('X');
	else if (StringName=="Y")
		GetKeyCode = ('Y');
	else if (StringName=="Z")
		GetKeyCode = ('Z');
	else if (StringName=="Ctrl")
		GetKeyCode = (VK_CONTROL);
	else if (StringName=="Alt")
		GetKeyCode = (VK_MENU);
	else if (StringName=="Shift")
		GetKeyCode = (VK_SHIFT);
	else if (StringName=="End")
		GetKeyCode = (VK_END);
	else if (StringName=="Delete")
		GetKeyCode = (VK_DELETE);
	else if (StringName=="Insert")
		GetKeyCode = (VK_INSERT);
	else if (StringName=="Page Up")
		GetKeyCode = (VK_PRIOR);
	else if (StringName=="Page Down")
		GetKeyCode = (VK_NEXT);
	else if (StringName=="Home")
		GetKeyCode = (VK_HOME);
	else if (StringName=="Space")
		GetKeyCode = (VK_SPACE);
	else if (StringName=="F1")
		GetKeyCode = (VK_F1);
	else if (StringName=="F2")
		GetKeyCode = (VK_F2);
	else if (StringName=="F3")
		GetKeyCode = (VK_F3);
	else if (StringName=="F4")
		GetKeyCode = (VK_F4);
	else if (StringName=="F5")
		GetKeyCode = (VK_F5);
	else if (StringName=="F6")
		GetKeyCode = (VK_F6);
	else if (StringName=="F7")
		GetKeyCode = (VK_F7);
	else if (StringName=="F8")
		GetKeyCode = (VK_F8);
	else if (StringName=="F9")
		GetKeyCode = (VK_F9);
	else if (StringName=="F10")
		GetKeyCode = (VK_F10);
	else if (StringName=="F11")
		GetKeyCode = (VK_F11);
	else if (StringName=="F12")
		GetKeyCode = (VK_F12);
	else if (StringName=="Up")
		GetKeyCode = (VK_UP);
	else if (StringName=="Left")
		GetKeyCode = (VK_LEFT);
	else if (StringName=="Down")
		GetKeyCode = (VK_DOWN);
	return GetKeyCode;
}


void MEMwrite(PVOID address, void* val, int bytes)
 {
	DWORD d, ds;
	VirtualProtect(address, bytes, PAGE_EXECUTE_READWRITE, &d);
	memcpy(address, val, bytes);
	VirtualProtect(address,bytes,d,&ds);
 }


int GetValue(int Adr)
{
try {
return *(DWORD*)(Adr)   ;
} catch (...) {
return 0                 ;
}
}

void Delay(unsigned int mSec )
{
unsigned int StartTime,CheckTime;
StartTime=timeGetTime();
do
	{
	 CheckTime=timeGetTime();
	 Sleep(100);
	 Application->ProcessMessages();
	}
while ( ( CheckTime - StartTime ) <= mSec ) ;
}


long MakeKeyLParam(unsigned int Key, unsigned int Flag)
{
	if (Flag == WM_KEYUP) {
		return 0xC000001 + (MapVirtualKey(Key, 0) % 0x100) * 0x10000;
	} else {
		return 0x0000001 + (MapVirtualKey(Key, 0) % 0x100) * 0x10000;
	}
}
void PressKey(HWND handle,DWORD Key,bool UpAndDown){
	PostMessage(handle,WM_KEYDOWN,Key,MakeKeyLParam(Key,WM_KEYDOWN));
	if (UpAndDown) {PostMessage(handle,WM_KEYUP,Key,MakeKeyLParam(Key,WM_KEYUP));}
}


bool WritePointer(DWORD BaseAddress, DWORD Offset, DWORD Value)
{
	try{
		*(DWORD*)(*(DWORD*)(BaseAddress) + Offset) = Value;
		return true;
	} catch(...) {
		return false;
	}
}

DWORD ReadPointer(DWORD BaseAddress, DWORD Offset)
{
	try{
		return *(DWORD*)(*(DWORD*)(BaseAddress) + Offset);
	} catch(...) {
		return 0;
	}
}

DWORD GetThreadIDByProcssID(DWORD dwProcessID)
{
	DWORD dwThreadID = 0;
	THREADENTRY32 te32 = {sizeof(te32)};
	HANDLE hThreadSnap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD,dwProcessID);
	if( Thread32First( hThreadSnap, &te32) )
	{
		do{
			if( dwProcessID == te32.th32OwnerProcessID && te32.th32ThreadID != GetCurrentThreadId())//?里新加了te32.th32ThreadID != GetCurrentThreadId()遍??程?不用?前?程,要不一?呼不出界面
			{
				dwThreadID = te32.th32ThreadID;
				break;
			}
		}while( Thread32Next( hThreadSnap, &te32) );
	}

	return dwThreadID;
}


void WriteValue(long adr,int value){
	DWORD OldProtection;
	VirtualProtect((LPVOID)adr,0x4,PAGE_EXECUTE_READWRITE, &OldProtection);
	*(int*)(adr)=value;
	VirtualProtect((LPVOID)adr,0x4,OldProtection, &OldProtection);
}

void AsmJump(const DWORD lpAddress, LPCVOID Function, unsigned Nops)
{
	DWORD OldProtection;
	VirtualProtect((LPVOID)lpAddress,10,PAGE_EXECUTE_READWRITE, &OldProtection);
	*(LPBYTE)lpAddress = 0xE9;
	*(LPDWORD)(lpAddress + 1) = JMP(lpAddress, Function);
	if ((bool)Nops)
		memset(((LPBYTE)lpAddress + 5), 0x90, Nops);
	VirtualProtect((LPVOID)lpAddress,10,OldProtection, &OldProtection);
}

void Jump(unsigned long ulAddress, void* Function, unsigned long ulNops){
try {
*(unsigned char*)ulAddress = 0xE9;
*(unsigned long*)(ulAddress + 1) = JMP(ulAddress, Function);
memset((void*)(ulAddress + 5), 0x90, ulNops);
} catch (...) {}
}

// 利用物品編號取得物品名稱  150.2
DWORD GetItemNameCall = 0x0594c1f;       //e8 ? ? ? ? c6 45 ? ? be 00 10 00 00
char* __declspec(naked) __stdcall GetItemNameByItemId(DWORD ItemId)
{
VMProtectBegin("GetItemNameByItemId");
__asm
{
push ebp
mov ebp,esp
push ecx // tmpMem
push ebx
push ecx
push edi
mov ebx,[ebp+0x08]
mov ecx,[0x0e181e4] //8b 35 ?? ?? ?? ?? 89 75 ec 3b f3 0f 84
push ebx
lea eax,[ebp-0x04]
push eax
xor edi,edi
call dword ptr [GetItemNameCall]
mov eax,[ebp-0x04]
pop edi
pop ecx
pop ebx
mov esp,ebp
pop ebp
ret 0x0004
}
VMProtectEnd();
}

//===================================================================
void PrintStr(String ShowStr,int PrintColor){
VMProtectBegin("PrintStr");//151.2
//00:白色 01:綠色 02:粉紅色 03:橘色 04:淺粉紅 05:淺綠 06:灰色
//07:黃色 08:淺黃色 09:藍色 0A:灰白底黑字 0B:淺粉紅 0C:灰藍底藍字
char * ShowPrint = AnsiString(ShowStr).c_str();
try{
	if(*(long*)0x0E92358 == 0)return;
	long ShowTextCall= 0x089812D; //8b 0d ? ? ? ? 50 e8 ? ? ? ? c9 c3
	__asm{
		Push 0
		Push 0
		Push 0
		Push -1
		Push PrintColor
		Push &ShowPrint
		mov ecx,[0x0E92358]
		Call dword ptr [ShowTextCall]
	}
}
catch(...){}
VMProtectEnd();
}
//==========================按鍵handle get =================================

class Data{
public:
HWND hwnd;
DWORD PID;
String ClassName;
};

bool CALLBACK MyEnumProc(HWND   hwnd,   LPARAM   lParam   ){
	DWORD tempPID,i;
	char tempClassName[1000];
	Data *Correct = (Data*)lParam;
	GetWindowThreadProcessId(hwnd, &tempPID);
	GetClassNameA(hwnd,tempClassName, 1000);
	if(Correct -> PID != tempPID)
	return 1;
	if(strcmp(AnsiString(Correct->ClassName).c_str(),tempClassName))
	return 1;
	Correct -> hwnd = hwnd;
	return 0;
}

HWND PIDGetHWND(DWORD MyPID){
	 Data Correct;
	 Correct.PID = MyPID;
	 Correct.ClassName = "MapleStoryClass";
	 Correct.hwnd = 0;
	 EnumWindows((WNDENUMPROC)MyEnumProc, (LPARAM)&Correct);
	 return Correct.hwnd;
}
//=========================================================================

