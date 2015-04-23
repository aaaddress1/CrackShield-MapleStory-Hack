//149.2 幻影迴避率調整
bool ControlHunUnP_IcsHookSw = false;
long ControlHunUnP_HookSetCall = 0x06D8C54;

void __declspec(naked) ControlHunUnP_HookSet(){
VMProtectBegin("ControlHunUnP");
__asm
{
mov [ebp+0X5c], 20
push [ebp+0X5C]
mov ecx,[ebp+0X08]
call ControlHunUnP_HookSetCall
mov eax,65
mov ecx,eax
push 0x091BB41
ret
}
VMProtectEnd();
}
long ControlHunUnP_Adr = (long)ControlHunUnP_HookSet;
long ControlHunUnPIcsRet;
bool NoCardCrazyCoolTimeOnOff = false;

void __declspec(naked) ControlHunUnP_IcsHook(){
#ifdef VMProtectSDK
VMProtectBegin("ControlHunUnP_IcsHook");
#endif
__asm
{
cmp dword ptr [esp+0x1c],0x091BB28
je HunInUnP
cmp dword ptr [esp+0x1c],0x091959B
je NoCardCrazyCoolTime
jmp BackToHook

NoCardCrazyCoolTime:
cmp [NoCardCrazyCoolTimeOnOff],00
je  BackToHook
mov [esp+0x1c],0x0919B52         // Hook Adr 下第一個跳轉點
jmp BackToHook

HunInUnP:
cmp [ControlHunUnP_IcsHookSw],00
je   BackToHook
push [ControlHunUnP_Adr]
pop [esp+0x1c]
BackToHook:
push [ControlHunUnPIcsRet]
ret
}
#ifdef VMProtectSDK
VMProtectEnd();
#endif
}


