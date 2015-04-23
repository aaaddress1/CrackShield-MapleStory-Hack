//150.2 csx攻擊不停

long AttackNoStopCall01 = 0x097f1d9;
long AttackNoStopCall02 = 0x04ea7d0;
void __declspec(naked) CsxAttackNoStop(){
asm{
push ebp
mov ebp,esp
push ebx
push esi
mov esi,[ebp+0x8]
xor ebx,ebx
push edi
mov ecx,[0x0e1cff0]
call dword ptr [AttackNoStopCall01]
mov [ebp+0x8],eax
fild dword ptr [ebp+0x8]
mov edi,[ebp+0xc]
fdiv qword ptr [0x0c0dc60]
fstp qword ptr [ebp+0x34]
fld qword ptr [esi+0x3C]
push ecx
fsub qword ptr [esi+0x1C]
push ecx
fmul qword ptr [ebp+0x34]
fadd qword ptr [esi+0x1C]
fstp qword ptr [esp]
call dword ptr [AttackNoStopCall02] //人物cs實體位置寫入
pop ecx
pop ecx
Push Eax
Mov Eax, [0x0E1847C]
Cmp Esi, [Eax+0x2368]
Jne CSXReturn
Mov Eax, [Eax+0x618C]
Cmp Eax, 50
Jl  CSXReturn
Add [Esp], 0x0F
CSXReturn:
Pop Eax
push 0x097F28A
ret
}
}

//============================遊戲虛擬XY攔截150.2=============================
/*怪物XY*/
long SetNewCsXY_CallAdr = 0x0426BFC;
long FullMapAttackSw=false;
void __declspec(naked) SetNewMobXY(){
VMProtectBegin("SetNewMobXY");
asm{
lea ecx,[esi+0x0000634]
cmp [FullMapAttackSw],00
je BackToNormal
push 0x06149FD
push esi
push edi
mov edi,[esp+0xc]
mov esi,[LoginX] //X
mov [edi],esi
push [edi]
mov esi,ecx
lea ecx,[esi+0Xc]
call dword ptr [SetNewCsXY_CallAdr]
mov ecx,[LoginY]//Y
mov [edi+0x4],ecx
push 0x0431471
ret

BackToNormal:
push 0x06149F8
ret
}
VMProtectEnd();
}

/*ByPass 怪物XY偵測*/
long ByPassGameMobXY__HookCallAdr = 0x042717E;
void __declspec(naked) ByPassSetMobXY__DcHookSet(){
VMProtectBegin("ByPassSetMobXY__DcHookSet");
asm{
lea ecx,[esi+0x0000634]
push 0x0614AFD
push esi
mov esi,ecx
push edi
lea ecx,[esi+0xc]
call dword ptr [ByPassGameMobXY__HookCallAdr]
mov edi,[esp+0xc]
mov [edi],ecx
mov eax,[edi]
mov ecx,esi
call dword ptr [ByPassGameMobXY__HookCallAdr]
mov [edi+0x4],0x1
mov eax,[edi+0x4]
db 0x5F
db 0x5E
db 0xC2
db 0x04
db 0x00
}
VMProtectEnd();
}

//==================================================================

