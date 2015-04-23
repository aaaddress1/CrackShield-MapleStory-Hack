// TWMS151.2 KIKI
long KiKiTelePortSw;
long KiKiXY[2];
void __declspec(naked) KiKiTelePortHook(){
VMProtectBegin("KiKiTelePortHook");
asm{
cmp [KiKiTelePortSw],ebx
je NoKiKi
mov [esi+0x67A4],ebx
mov ebx,[ebp-0x8]
sub ebx,3000
mov [esi+0x0067B4],ebx
mov ebx,[KiKiXY+0x0]
mov [esi+0x67A4],ebx
mov ebx,[KiKiXY+0x4]
mov [esi+0x67A8],ebx
xor ebx,ebx
cmp [LevUpMode],02
je KiKiMain
mov [KiKiTelePortSw],ebx
KiKiMain:
push 0x0969D90
ret
NoKiKi:
push 0x096A085
ret
}
VMProtectEnd();
}
