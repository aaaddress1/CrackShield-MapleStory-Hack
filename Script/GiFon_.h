//疾風 150.2
//==================================發包吸怪===========================
bool MobVacSW;
long VacDataSet[3];

void __declspec(naked) MobVacMain(){
VMProtectBegin("MobVacMain");
asm{
cmp [MobVacSW],00
je BackToNormal

cmp [esi+0x4],01
je BackToNormal
cmp [esi+0x2a8],01
je BackToNormal
cmp [esi+0x2a8],03
je BackToNormal
cmp [esi+0x2a8],04
je BackToNormal
VacMain:
pushad
mov eax,esi
mov ebx,eax
mov ecx,ebx
add eax,0x10
add ecx,0x10
mov edi,[eax]
Push 00
Push 00
Push 00
Push 00
Push [VacDataSet+0x8]
Push [VacDataSet+0x4]
Push 06
mov [esi+0x4],01
Call dword ptr [Edi+0x84]
popad

BackToNormal:
push 0x06122A1
ret
}
VMProtectEnd();
}

//==============================150.2物品過濾===========================================//
long BlackList[255];
long ItemBlackListAdr=(long)BlackList;
long NowItemId;
long ItemVisibleShowUpCall=0x0408b13;
long ItemVisibleShowCall01=0x0408b6f;
void __declspec(naked) ItemVisible()
{
asm{
mov eax,[ebp-0x1C]
mov esi,[ebp-0x50]
mov [esi+0x1C],al
cmp eax,0x1
Je HookOr1
cmp eax,0x2
Je HookOr1
xor al,al
Jmp HookOr2
HookOr1:
mov al,0x1
HookOr2:
mov [esi+0x1D],al
mov [esi+0x20],edi
mov edi,[ebp+0x8]
mov ecx,edi
call dword ptr [ItemVisibleShowUpCall]
movzx eax,al
mov ecx,edi
//Xor Eax, Eax //過濾楓幣
mov [esi+0x30],eax
call dword ptr [ItemVisibleShowCall01]
PUSH ESI
MOV ESI,ItemBlackListAdr

Filter:
mov [NowItemId],eax
CMP EAX,0xC350
JLE End
CMP DWORD PTR DS:[ESI],0
Je End
CMP DWORD PTR DS:[ESI],EAX
Je Skip
ADD ESI,0x4
JMP Filter
Skip:
XOR EAX,EAX
End:
POP ESI
MOV ECX,EDI
MOV [ESI+0x34],EAX
push 0x04EF017
ret
}
}
long ItemVisibleHookAdr=(long)ItemVisible;
//==============================151.2怪物變笨===========================================//
bool MobStupidOnOff =00 ;
void __declspec(naked) StupidMobMain(){
VMProtectBegin("MobStupidIcs");
asm{
Xor  Edx, Edx
Mov  Ecx, 0x000EA60
Lea  Ecx, [Esi+0x00002C0]
push  0x09BFE89 // Push Edx
ret
}
VMProtectEnd();
}

long StupidMobAdr=(long)StupidMobMain;
//=======================151.2怪物不擊退============================================//
/*// 0: 怪不動
// 1: 怪退後一點點 (正常值)
// 2: 怪退後很多點
// 3: 怪反方向退到底
// A(以上): 怪退到底
// C: 怪物跳躍**/
void __declspec(naked) SetKbSetting(){
asm{
and [ebp+0x40],00
push 0x062B31E;    //8B CB E8 ?? ?? ?/ ?/ 83 7D 3C 01
ret
}
}
long AdrKBset=(long)SetKbSetting;

//===========================151.2終極百分百===========================================//
void __declspec(naked) OverAttackSet(){
VMProtectBegin("OverAttackSet");
asm{
cmp [NDFASW],00
je BackToNoFinal

mov eax,[ebp+0x10]
mov esi,[ebp-0x0c]
mov ecx,[ebp-0x10]
mov [esi+0x0006770],eax
mov [esi+0x0006774],edi
mov [esi+0x0006778],ecx
mov [NodelayUseID],edi
push 0x092BFB0
ret

BackToNoFinal:
push 0x092BF87
ret
}
VMProtectEnd();
}
long SetFinalAttack100pHookAdr = (long)OverAttackSet;
//==============================151.2怪物移動加速======================================
long MobGoCall = 0x063D6F6;
bool MobGoSuddenlyOnOff;
void __declspec(naked) MobGoSuddenlySet(){
asm{
mov ecx,esi
call dword ptr [MobGoCall]
push 0x063DF88
ret
}
}
long MobGoSetAdr = (long)MobGoSuddenlySet;


//================================================================================//
long MobVacMainAdr = (long)MobVacMain;


void __declspec(naked) GiFonIcsHook(){
VMProtectBegin("GiFonIcsHook");
asm{
	Cmp [Esp+0x24], 0x09BFE74 //151.2 33 d2 b9 60 ea 00 00 f7 f1
	Je Stupid
	Cmp [Esp+0x3c], 0x062B31E//151.2 83 7D ?? 01 75 ?? 8B 4D ?? E8 ?? ?? ?? FF 39
	Je MobKB
	Cmp [esp+0x3c], 0x063DF88//151.2 66 8B 57 04 8B CE
	je MobRunFast
	cmp [esp+0x24], 0x092BF66//151.2 6A 65 59 33 D2 F7 F1 FF 75 E8
	je FinalAttackHook
//	Cmp [Esp+0x6c], 0x04EEFDC//150.2 8B 45 E4 8B 75 B0
//	Je HookItem
	cmp dword ptr [esp+0x3C],0x062CF33//151.2 39 BE ?? ?? ?? ?? 74 20
	je MobVacControl
}
VMProtectEnd();
asm{
BlastBack:
push 0x074B5F1
ret

MobVacControl:
push [MobVacMainAdr]
pop [Esp+0x3c]
Jmp BlastBack

HookItem:
push [ItemVisibleHookAdr]
pop [Esp+0x6c]
Jmp BlastBack

FinalAttackHook:
push [SetFinalAttack100pHookAdr]
pop [Esp+0x24]
Jmp BlastBack

Stupid:
cmp [MobStupidOnOff],00
je BlastBack
push [StupidMobAdr]
pop [Esp+0x24]
Jmp BlastBack

MobRunFast:
cmp [MobGoSuddenlyOnOff],00
je BlastBack
push [MobGoSetAdr]
pop [Esp+0x3c]
Jmp BlastBack

MobKB:
push [AdrKBset]
pop [Esp+0x3c]
Jmp BlastBack
}
}







