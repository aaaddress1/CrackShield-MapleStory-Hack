//HumanLr  TWMS150.2
long IcsAttackLrRet;
bool AutoPickOnOff,LrOnOff;
long PickFakeTime,NowPickCount,UserXY[2],NextLrX;

void __declspec(naked) MyAutoLR(){
/*攔截XY,自動撿物*/
VMProtectBegin("MyAutoLR");
asm{
	pushad
	lea edx,[UserXY]
	Push edx
	mov ecx,[0x0e1847c]
	add ecx,04
	call GameGetHumXY_Call
	cmp [AutoPickOnOff],00
	je EndPickUp
	mov [NowPickCount],00
	Pick:
	inc [NowPickCount]
	Mov  Ecx, [PickFakeTime]
	Mov  Eax, [0x0E1CFF0]
	Add  [Eax+0x1C], Ecx
	lea edx,[UserXY]
	push edx
	mov ecx,[0x0E20510]
	Call PickItemAdr
	Mov  Ecx, [PickFakeTime]
	Mov  Eax, [0x0E1CFF0]
	Sub  [Eax+0x1C], Ecx
	Add  [PickFakeTime], 0x1E
	Mov  Eax, [0x0e181e0]
	cmp [Eax+0x20DC],00
	je EndPickUp
	And [Eax+0x20DC],00
	cmp [NowPickCount],15
	jl Pick
	EndPickUp:
	popad
}
VMProtectEnd();
/*人物左右*/
asm{
cmp [LrOnOff],1
jne BackToTrueControl
ControlLr:
cmp [LrOnOff],00
je BackToTrueControl
Mov [Ebp-04], 0
push eax
mov eax,[NextLrX]
sub eax,08
cmp eax,[UserXY]
Mov [Ebp-04], 1
jg  BackToSetLr
add eax,16
cmp eax,[UserXY]
Mov [Ebp-04],-1
jl  BackToSetLr
mov [Ebp-04], 0
BackToSetLr:
pop eax
push 0x09898BF
ret
BackToTrueControl:
push 0x09895EC
ret

}
}

long MyAutoLRAdr=(long)MyAutoLR;
void __declspec(naked) HumLrIcsHook(){
asm{
cmp [esp], 0x09895EC
jne BackToSub
push [MyAutoLRAdr]
pop [esp]
BackToSub:
jmp IcsAttackLrRet
}
}


///////////////////////////////////////////////////////////
//151.2
long PickNodcICSret ;
void __declspec(naked) PickNoDc(){
VMProtectBegin("PickNoDc");
asm{
cmp [esp],0x04F8620  //85 c0 74 07 39 5d 08
jne PtInRectB_______k
xor eax,eax
inc eax
ret 0X00c
PtInRectB_______k:
jmp dword ptr [ PickNodcICSret]
}
VMProtectEnd();
}



