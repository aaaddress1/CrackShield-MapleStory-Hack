//===================================無敵時間================================
//Hurt  TWMS151.2
long GodTime ;
bool HurtMode = 1;
bool AutoLoseHpSw = 0;
long AutoLoseHpIcsRet;
long CostHpCount = 01;
void __declspec(naked) GodMode(){
VMProtectBegin("GodMode");
asm{
cmp [esp],0x095AB2D  // 下面ICS點的返回位置 [1/2] e8 ? ? ? ? 85 c0 0f 85 ? ? ? ? 8b 83 ? ? 00 00 83 e0 fe 83 f8 12
je HurtTimeBlockControl
Normal:
push 0x096C5B4
ret

HurtTimeBlockControl:
cmp [HurtMode],00
je  Normal
mov eax,[0x0E92390] // 時間
mov eax,[eax+0x1C]
cmp eax,[GodTime]
jl God
add eax,30000
mov [GodTime],eax
mov eax,[GodTime]
jmp Normal

God:
mov [esp],0x095D082 // 無敵
jmp Normal
}
VMProtectEnd();
}



//150.2 自動掉血
long CostHpCall = 0x00921C61;
void __declspec(naked) AutoLoseHp(){
VMProtectBegin("AutoLoseHp");
asm{
cmp [esp],0x088EF6F
jne Back
cmp [HurtMode],00
je Back
cmp [AutoLoseHpSw],00
je Back
pushad
mov ecx,[0x0E1847C]
push 01
push 01
push 00
push 00
push 00
push 00
push 00
push 00
push 00
push [CostHpCount] // 單次扣血量
call dword ptr [CostHpCall]
popad
Back:
push [AutoLoseHpIcsRet]
ret
}
VMProtectEnd();
}
