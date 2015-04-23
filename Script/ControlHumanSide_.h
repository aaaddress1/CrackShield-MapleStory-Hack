//ControlHumanSide  TWMS151 .2
long PeoPleSide= 00;
bool ControlPeopleSideOnOff=00;
void __declspec(naked) ControlHumanSideHook(){
VMProtectBegin("ControlHumanSideHook");
asm{
cmp [ControlPeopleSideOnOff],00
je Back
push [PeoPleSide]
pop [ecx+0X00000DC] //°Ê§@
Back:
mov eax,[ecx+0x00000DC]
ret
}
VMProtectEnd();
}





