//===============================取得其他玩家ID===========================
long StrStrCallAdr ;
long GetOtherNameCall01 = 0x09EDA6E;
long AutoGmLogOut = 00;
void __declspec(naked) GetOtherNameHookSet(){
asm{
mov eax,[ebp-0x24]
mov ecx,[eax+0x000442C]
mov eax,[ebp-0x2C]
mov eax,[eax+0x10]
cmp ecx,[eax+0x00023E0]
je Exit04
push [eax+0x00023E0]
mov ecx,[ebp-0x24]
call dword ptr [GetOtherNameCall01]
mov eax,[ebp-0x2C]
mov eax,[eax+0x10]
mov eax,[eax+0x00023E4]
push ecx
mov ecx,esp
mov [ebp-0x10],esp
push 0xFF
push eax
mov [ecx],ebx
push 0x07F1F53
cmp dword ptr [esp+0x4],00
push edi
mov edi,ecx
je Exit03
push esi
mov esi,[esp+0x10]
push [esp+0xC]
push 0x0422CDD
mov ecx,[esp+0x4]
test ecx,0x003
je Exit02
mov al,[ecx]
pushad
push 0x4D47
push esp
push ecx
call dword ptr [StrStrCallAdr]
add esp,0xc
cmp eax,0x0
popad
je Exit01
cmp [AutoGmLogOut],00
je Exit01
push 00
ret

Exit01:
push 0x0A0EA0E
ret
Exit02:
push 0x0A0EA30
ret
Exit03:
push 0x0422CC3
ret
Exit04:
push 0x007F1EB1
ret
}
}
long GetOtherNameHookSetAdr = (long)GetOtherNameHookSet;
//===========================150.2滾筒無延遲======================================
bool RollItemHookOnOff=00;
void __declspec(naked) RollNoDelay(){
VMProtectBegin("RollNoDelay");
asm{
mov eax,[0x0e1847c]
mov [eax+0x4a4],0xFFFFFFFF
Mov Eax,[Ebp+0x60]
push 0x08EEC63
ret
}
VMProtectEnd();
}
long RollNoDelayAdr=(long)RollNoDelay;

//=========================================================================
// TWMS150.2 全職業攻擊無延遲 by.aaaddress1
long SkillNoDelaySw = 00;
void __declspec(naked) SkillNoAttackDelaySet(){
VMProtectBegin("SkillNoAttackDelaySet");
asm{
cmp [SkillNoDelaySw],00
je ReturnTheNormal
mov [ebp-0x54],01
ReturnTheNormal:
push 0x0926366
ret
}
VMProtectEnd();
}
long SkillNoAttackDelayHookSetAdr=(long)SkillNoAttackDelaySet;
//=========================================================================
long SkillNodelayIcsRet ;
void __declspec(naked) SkillNoAttackDelayHook(){
//VMProtectBegin("_UnlimitedWeapon_asm");
asm{
//cmp dword ptr [esp+0xc],0x07F1E17  //149.1
//je GetTheRedOtherId
Cmp [esp+0x10],0x094D441    //151.2
Je DoubleShootHookIcs
//cmp dword ptr [esp+0x54],0x08EEC15  //150.2 |8B 45 ?? 89 45 ?? 39 5D ?? 74 ?? 8B 45 ?? 8B 88 ?? ?? ?? ??
//je SetRoll

Return:
push [SkillNodelayIcsRet]
ret

DoubleShootHookIcs:
Mov  [Ebp-0x0000224], 1 // 無限標箭彈
Mov  [Ebp-0x0000220], 1 // 雙倍標箭彈
jmp Return

SetRoll:
cmp [RollItemHookOnOff],00
je Return
push [RollNoDelayAdr]
pop [esp+0x54]
jmp Return

GetTheRedOtherId:
push [GetOtherNameHookSetAdr]
pop [esp+0xc]
jmp Return
}
//VMProtectEnd();
}



