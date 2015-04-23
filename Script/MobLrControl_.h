//MobLrControl TWMS151.2
bool MobLROnOff=00;
long NextX;
void __declspec(naked) MobLR(){
VMProtectBegin("MobLR");
asm{
Push Eax
cmp [MobLROnOff],0
je Return
Cmp  [Ecx+0x0002A8], 01
Je   Control
Cmp  [Ecx+0x0002A8], 03
Je   Control
Jmp  Return

Control:
and  [Ecx+0x0000FC], 00000000
Mov  Eax, [NextX]
sub eax,10
inc [Ecx+0x0000FC]
Cmp  [Ecx+0x0006A4], Eax
Jl   Return
sub [Ecx+0x0000FC],02
Cmp  [Ecx+0x0006A4], Eax
Jg   Return
Return:
cmp [LevUpMode],02
je StartKiKiHum
TrueNormalAdr:
Pop  Eax
Push 0x09C3A30		// 55 8B EC 51 53 56 57 FF 75 08
Ret

StartKiKiHum:
cmp [ecx+0x2a8],01
je StartMain
cmp [ecx+0x2a8],03
je StartMain
jmp TrueNormalAdr
StartMain:
mov eax,[ecx+0x6a4]
sub eax,32
mov [KiKiXY+0x0],eax
mov eax,[ecx+0x6a8]
mov [KiKiXY+0x4],eax
mov [KiKiTelePortSw],01
jmp TrueNormalAdr
}
VMProtectEnd();
}




