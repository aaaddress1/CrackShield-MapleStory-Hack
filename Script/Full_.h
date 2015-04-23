// TWMS151.2 ICS Àþ¶¡¶°º¡
// UpdateTime: 2012-08-01
bool FullSw;
void __declspec(naked) FullSetHook()
{
VMProtectBegin("FullSetHook");
asm{
Cmp  [Esp], 0x0976125 // 8B ?? ?? ?? 00 00 2B 08 83 F9 FA
Jne  Back
cmp [FullSw],00
je Back
And  [Esi+0x0007930], 00  // 2B ?? ?? ?? 00 00 6A 1E 59
Back:
push 0x04AC765
ret
}
VMProtectEnd();
}
