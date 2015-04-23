//WalkFast  TWMS150
bool WalkSpeedUpOnOff;
long FakeTime;
void __declspec(naked) WalkSpeedUp(){
VMProtectBegin("WalkSpeedUp");
asm{
cmp [esp], 0x093271C // 8B 83 ?? 00 00 00 8B 4D ?? 83 C0
jne Back
cmp [WalkSpeedUpOnOff],00
je  Back
add esp, 0x4
push esi
mov esi,7

SpeedChk:
test esi,esi
je Normal

dec esi
push esi
push ecx
push eax
call dword ptr [eax]
pop eax
pop ecx
pop esi
jmp SpeedChk

Normal:
pop esi
push 0x093271C
ret

Back:
push 0x0097C472
ret
}
VMProtectEnd();
}

void __declspec(naked) FakeWalkTime(){
VMProtectBegin("FakeWalkTime");
asm{
add eax, [FakeTime]
add [FakeTime], 0x00001FE
pushad
push 0x10A4474
push 0x106f0c6
ret
}
VMProtectEnd();
}

	   /*
//============================強制發人物包===================================
long HumPackageMode =00;
void __declspec(naked) ForceSendHumPackageHook(){
VMProtectBegin("ForceSendHumPackageHook");
asm{
cmp [HumPackageMode],00
je BackToNormal
mov [HumPackageMode],00
cmp [HumPackageMode],01
mov eax,01
je BackToNormal
mov eax,00
BackToNormal:
push 0X00EF9FA6
ret
}
VMProtectEnd();
}
						   */
