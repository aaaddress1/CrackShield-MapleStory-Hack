//150.2 人物本值流
bool HurtLessIcsSW;
bool MobNoAttack;
void __declspec(naked) HumTempControl(){
VMProtectBegin("HumTempControl");
asm{
cmp dword ptr [esp+0x00],0x09238DE
je HurtHalf
cmp dword ptr [esp+0x58],0x0613F50
je MobNoAttackMain

Back:
push 0x08F9CC7
ret

MobNoAttackMain:
cmp [MobNoAttack],00
je  Back
mov [esp+0x58],0x061414A
jmp Back

HurtHalf:
cmp [HurtLessIcsSW],00
je  Back
Mov Eax, [Ebp+0x58]
Shr Eax, 1
Sub [Ebp+0x58], Eax
jmp Back
}
VMProtectEnd();
}

