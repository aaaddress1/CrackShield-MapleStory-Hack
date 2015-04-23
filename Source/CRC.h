//151.2
void __declspec(naked) FuckHS(){
VMProtectBegin("FuckHS");
__asm{
Mov dword ptr [0x0A4A226], 0x02B0EC81

Push Eax

// Lea Eax, [Ebp+18]
Mov Eax, Ebp
Inc Eax
Add Eax, 0x16
Sub Eax, 0xFFFFFFFF

And [Eax], 0xFF7FFFFF // 關閉多開檢測Mask
Pop Eax
// 還原
Mov word ptr [0x0A4A226+0x4], 0

Push 0x0A4A226
Ret
}
VMProtectEnd();
}

void FuckChecking() {
try {VMProtectBegin("FuckChecking");
	Jump(0x0A4A226, FuckHS, 1);       // 89 8D ?? ?? FF FF C7 85 ?? ?? FF FF ?? ?? FF FF 8B 55
	EnableMultiMS();
VMProtectEnd();
} catch (...) {ExitProcess(NULL);asm{push 64;ret}}
}
