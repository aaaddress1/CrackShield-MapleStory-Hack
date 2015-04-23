//ndfa    150.2
long NodelayHookCallO1 =  0x042189f;
long NodelayUseID =00;
long NDFASW = 00;
long NodelayFinalSkillIcsRet = 00;

void __declspec(naked) OverAttackNodelay(){
VMProtectBegin("OverAttackNodelay");
asm{
mov eax,[eax+0x4]
lea ecx,[ebp-0x10]
mov [ebp-0x8],eax
call NodelayHookCallO1
xor edi,edi
push [NodelayUseID]
pop [esi+0x5F54]
push 0x0939D8F
ret
}
VMProtectEnd();
}

long SetNodelayHookAdr = (long)OverAttackNodelay;

void __declspec(naked) NodelayFinalSkillHook(){
#ifdef VMProtectSDK
VMProtectBegin("_RecvPacketHook");
#endif
asm{
cmp [esp+0x24],0x0939D7F  //8b 40 04 8d 4d f0 89 45 f8 e8 ?? ?/ ?/ ?? 33 ff  [2/2]
jne Return
cmp [NDFASW],00
je  Return
push [SetNodelayHookAdr]
pop [esp+0x24]
Return:
Jmp dword ptr [NodelayFinalSkillIcsRet]
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}


