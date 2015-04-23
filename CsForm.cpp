#include <vcl.h>
#pragma hdrstop
#include <Shlobj.h>
#pragma hdrstop
#include "VMProtectSDK.h"
#include <encddecd.hpp>
#include <inifiles.hpp>
#include <tlhelp32.h>
#pragma comment(lib,"VMProtectSDK32.lib")
#include <stdio.h>
#include "CsForm.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TCrackShieldMainForm *Form;String Path;HINSTANCE dllinst;HHOOK KEYHOOK;
long LoginX,LoginY,LoginMap;String GameChactorId;
long NowHp,NowMp;
long HpSettingLim = 500;
long MpSettingLim = 500;
bool RegPass ;
/*自動補血補魔*/
long HpSettingKey = VK_HOME;
long MpSettingKey = VK_END;
/*自動練功設置*/
bool AutoLevUpSw,AutoLevUpLr;
long LastSetWalkTick;
long LrLandFar = 70;
long LrBlockAdditonTime = 15*1000;
long LevUpMode;
/*網路驗證*/
String PcNum;
String HexKey;
String GetTemp;

/*自動按鍵*/
long Key[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G' , 'H' };
long KeySetBlockTime[8] = { 60000 , 60000 , 60000 , 60000 , 60000 , 60000 , 60000 , 60000 };
long KeyTime[8] = { 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 };
bool KeyOnOff[8] = { false , false , false , false , false , false , false , false };
String CrackShieldVer = "破解之盾v1";
#include "\..\Source\Pointer.h"
#include "\..\Source\MyFuction.h"
#include "..\\Script\\XY_Fix.h"
#include "..\\Script\\Full_.h"
#include "..\\Script\\OverAttack_.h"
#include "..\\Script\\ControlHunUnP_.h"
#include "..\\Script\\Hurt_.h"
#include "..\\Script\\Dingua_.h"
#include "..\\Script\\GiFon_.h"
#include "..\\Script\\KiKiTelePort.h"
#include "..\\Script\\HumTempControl_.h"
#include "..\\Script\\DoubleShoot_.h"
#include "..\\Script\\HumanLr_.h"
#include "MultiMs.h"
#include "CRC.h"
#include "..\\Script\\WalkFast_.h"
#include "..\\Script\\ControlHumanSide_.h"
#include "..\\Script\\MobLrControl_.h"
//===============================================================================================//
__fastcall TCrackShieldMainForm::TCrackShieldMainForm(TComponent* Owner)	: TForm(Owner){}
void __fastcall TCrackShieldMainForm::SuperSkillClick(TObject *Sender){SkillNoDelaySw = ((TCheckBox*)Sender)->Checked *12444 ;}
void __fastcall TCrackShieldMainForm::RollNodelayClick(TObject *Sender){RollItemHookOnOff= ((TCheckBox*)Sender)->Checked *5135135;}
void __fastcall TCrackShieldMainForm::MobNoAttackCBClick(TObject *Sender){MobNoAttack = ((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::FinalAttackNodelayClick(TObject *Sender){NDFASW= ((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::AutoPickClick(TObject *Sender){AutoPickOnOff=((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::MobLrClick(TObject *Sender){NextX=UserXY[0];MobLROnOff=((TCheckBox*)Sender)->Checked ;MobGoSuddenlyOnOff=MobLROnOff;}
void __fastcall TCrackShieldMainForm::StupidMobClick(TObject *Sender){MobStupidOnOff =((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::FullswClick(TObject *Sender){FullSw =((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::FormCloseQuery(TObject *Sender, bool &CanClose){CanClose = false; this->Visible = !this->Visible;}
void __fastcall TCrackShieldMainForm::WalkSpeedUpClick(TObject *Sender){WalkSpeedUpOnOff =((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::StopMobClick(TObject *Sender){Freeze_Switch=((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::HpSetCountChange(TObject *Sender){try {HpSettingLim=((TEdit*)Sender)->Text.ToInt() ;} catch (...) {}}
void __fastcall TCrackShieldMainForm::MpSetCountChange(TObject *Sender){try {MpSettingLim=((TEdit*)Sender)->Text.ToInt() ;} catch (...) {}}
void __fastcall TCrackShieldMainForm::HpKeyComboChange(TObject *Sender){HpSettingKey = GetVkCodeByString(((TComboBox*)Sender)->Text);}
void __fastcall TCrackShieldMainForm::MpKeyComboChange(TObject *Sender){MpSettingKey = GetVkCodeByString(((TComboBox*)Sender)->Text);}
void __fastcall TCrackShieldMainForm::HurtHalfClick(TObject *Sender){HurtLessIcsSW =((TCheckBox*)Sender)->Checked ;}
//===========================================================================================//
DWORD WINAPI CallFormProc(LPVOID lpParameter){
Form=new TCrackShieldMainForm(Application);Form->ShowModal();
return true;
}
String GetMyPath() {	String PathStr;	try {wchar_t chModuleDir[260*2] ;GetModuleFileNameW(dllinst, chModuleDir, 260*2);
PathStr = ExtractFilePath(chModuleDir);return PathStr;}
	catch(...) {}return ExtractFilePath(Application->ExeName);
}

int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved){
	if(reason == DLL_PROCESS_ATTACH){
	dllinst = hinst;
	Path = String(GetMyPath());
	CreateThread(NULL,0xFF,CallFormProc,NULL,0,NULL);}
	else if(reason == DLL_PROCESS_DETACH)
	{ExitProcess(NULL);FreeLibrary(dllinst);}
	return true;
}
//=============================================================================================//
void MovHumToXY(int X,int Y){KiKiXY[0]=X;KiKiXY[1]=Y;KiKiTelePortSw = true;}
//===============================================================================================//
DWORD WINAPI AutoRobot(LPVOID lpParameter){
	if (!AutoLevUpSw) {
		if ((*(long*)(*(long*)MapIdPointer[0]+MapIdPointer[1]) == LoginMap)) {
			MovHumToXY(LoginX,LoginY);AutoLevUpSw = true;LrOnOff=true;
			MobLROnOff=true;NextX=LoginX;AutoPickOnOff = true;
			switch (LevUpMode) {
			case 0:FullMapAttackSw=125;
				break;
			case 1:MobVacSW=1254;
				break;
			default:
				break;
			}
		}else{
			PrintStr("[提示]請先於要練功的座標按下[F6]哦!",0x9);
		}
	}else{
	LrOnOff=false;AutoLevUpSw = false;ControlPeopleSideOnOff=false;MobVacSW=false;
	Form->AutoPickClick( Form->AutoPick );FullMapAttackSw=false;
	Form->MobLrClick(Form->MobLr);
	}
}


LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam){
	bool bKeyUp = lParam & (1 << 31);
	if(bKeyUp && nCode == HC_ACTION)
	{
		 switch(wParam)
		{
			case VK_F1:
			Form->Fullsw->Checked = !Form->Fullsw->Checked;break;
			case VK_F2:
			Form->StopMob->Checked = !Form->StopMob->Checked;break;
			case VK_F3:
			Form->WalkSpeedUp->Checked = !Form->WalkSpeedUp->Checked ;break;
			case VK_F4:
			Form->AutoPick->Checked =!Form->AutoPick->Checked ;break;
			case VK_F5:
			Form->Visible  = !Form->Visible ;break;
			case VK_F6:
			Form->RecSaveClick(NULL) ;break;
			case VK_F7:
			CreateThread(NULL,0xFF,AutoRobot,NULL,0,NULL); break;
		}
	}
	return CallNextHookEx(KEYHOOK, nCode, wParam ,lParam);
}
//===============================================================================================//
void __fastcall TCrackShieldMainForm::RegKeyBoardHook(){KEYHOOK = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, dllinst, GetThreadIDByProcssID(GetCurrentProcessId()));}

DWORD WINAPI AutoControl(LPVOID lpParameter){
while (true){
	try {
			for (int i = 0; i < 8; i++) {
				if ((KeyOnOff[i])&&(KeyTime[i]<GetTickCount())&&ReadPointer(SkillActionBase[0],SkillActionBase[1])==-1) {
				Sleep(50);KeyTime[i] = GetTickCount() + KeySetBlockTime[i];
				PressKey(PIDGetHWND(GetCurrentProcessId()),Key[i],false);
			}
		}
	} catch (...) {}

	try {
			if (AutoLevUpSw&&(LevUpMode!=02)) {
				ControlPeopleSideOnOff=true;
				if (LastSetWalkTick+LrBlockAdditonTime<GetTickCount()) {AutoLevUpLr = !AutoLevUpLr;LastSetWalkTick = GetTickCount();}
				if (AutoLevUpLr) {NextLrX = LoginX - LrLandFar;}else{ NextLrX = LoginX + LrLandFar;}
				PeoPleSide = 1 - (UserXY[0]<LoginX);
			}
			if (AutoLevUpSw) {
				if (ReadPointer(MapMobCount[0],MapMobCount[1])>01) {PressKey(PIDGetHWND(GetCurrentProcessId()),VK_CONTROL,true);}
			}
	} catch (...) {}
	Sleep(100);Application->ProcessMessages() ;
}
}
//=============================================================================================//
DWORD WINAPI HandleAllThingBeforeIntoGame(LPVOID lpParameter){
if (!DirectoryExists(Path + "\\Data")){CreateDir(Path + "\\Data");}
	VMProtectBegin("HandleAllThingBeforeIntoGame");
	Form->Caption = CrackShieldVer +"|"+GetTemp;
	//FuckChecking();
	LoadLibrary((Path+"\\CsDt.dll").c_str());
	try {
		MEMwrite((void*)0x0976A2D, (void*)"\x90\x90\x90\x90\x90\x90",6);//151.2輔助技無延遲
		MEMwrite((void*)0x096A57A, (void*)"\x74\x2A", 2); //151.2精靈直接踢  - 75 2a 8d 45 d4
		*(long*)(0x0CF18BC)=(long)GodMode;               //151.2無敵
		*(long*)0x0CF1888 = (long)FullSetHook;           //151.2集氣秒放
		*(long*)(0x0CF5924) = (long)ControlHumanSideHook;   //151.2人物面向
		*(long*)(0x0CF58EC)=0x09B9E3A ;                  //151.2損寫不退
		*(long*)(0x0CF51D8)=(long)MobLR;                  //151.2控怪
		PickNodcICSret = *(long*)0x0E9C594;            //151.2函數撿物不斷
		*(long*)0x0E9C594 = (long)PickNoDc;            //151.2函數撿物不斷   */
		AsmJump( 0x060BBF2,Dingua_Main,1);//151.2 定怪 -39 81 ? ? ? ? 75 ? 39 81 ? ? ? ? 75 ? 39 81 ? ? ? ? 75 ? 83 b9
		//*(long*)(0x0E71014)=(long)GiFonIcsHook  ;         //151.2疾風

		AsmJump( 0x0969D84, KiKiTelePortHook,0);//151.2 KIKITELEPORT
		*(long*)0x0C8A1A4= (long)HumTempControl;      //150.2人物類暫存散發資料控制
	 /*	AsmJump( 0x09259E7,SkillNoAttackDelaySet,0); //150.2 近戰攻擊無延遲
		AsmJump( 0x06149F2,SetNewMobXY,1);//150.2 全圖
		AsmJump( 0x0614AEB, ByPassSetMobXY__DcHookSet,1); //150.2 全圖
		*/
	  /*Jump( 0x10A446E ,FakeWalkTime, 0);//150.2人物走路加速
		*(long*)0x0C8E200 = (long)CsxAttackNoStop;  //150.2 CSX攻擊不停
		*(long*)0x00C8E0B4 = (long)WalkSpeedUp; //150.2 走路加速   */
	} catch (...) {}
	PostMessage(FindWindow(L"StartUpDlgClass",L"MapleStory"),WM_CLOSE,00,00);
	Sleep(5000);
	while (!GetValue(SkillActionBase[0])){Sleep(1000);Application->ProcessMessages();}
	try {
		SkillNodelayIcsRet = *(long*)0x0C71908 ;           //151.2[荒野]雙倍+滾筒+取得其他玩家ID
		*(long*)0x0C71908 = (long)SkillNoAttackDelayHook; //151.2[荒野]雙倍+滾筒+取得其他玩家ID
	  /*AutoLoseHpIcsRet =*(long*)(0x00E25E64);           //150.2自動扣寫
		*(long*)(0x00E25E64)=(long)AutoLoseHp;            //150.2自動扣寫
		IcsAttackLrRet=*(long*)(0x0E25EC0);              //150.2人物左右走
		*(long*)(0x0E25EC0)=(long)HumLrIcsHook;          //150.2人物左右走
		NodelayFinalSkillIcsRet = *(long*)0x0b33098;      //150.2終極攻擊無延遲
		*(long*)0x0b33098 = (long)NodelayFinalSkillHook;  //150.2終極攻擊無延遲
		  */
		GameChactorId = ((char***)0x0e8d7a0)[0][0x20F8 >> 2] + 4;  //151 .2
		PrintStr(GameChactorId+" 歡迎您使用破解之盾[VIP].",0x9);
		PrintStr("官方網站: www.CrackShield.co",0x9);
		Form->RegKeyBoardHook() ;
	} catch (...) {}
	VMProtectEnd();while (ReadPointer(HumActBase[0],HumActBase[1])&0xFFFFFFFE==06){Sleep(500);}
try {
	if (FileExists(Path+"\\Data\\"+GameChactorId+"__Data.txt")){
	TIniFile* ini = new TIniFile(Path + "\\Data\\"+GameChactorId+"__Data.txt");
	for(int i = 0; i < Form->ComponentCount; i++){
		if(Form->Components[i]->ClassNameIs("TEdit"))
		{((TEdit*)Form->Components[i])->Text = ini->ReadString("AutoPerForm", Form->Components[i]->Name, "");
		} else if(Form->Components[i]->ClassNameIs("TCheckBox")){
		((TCheckBox*)Form->Components[i])->Checked = ini->ReadBool("AutoPerForm", Form->Components[i]->Name, false);
		} else if(Form->Components[i]->ClassNameIs("TComboBox")){
		((TComboBox*)Form->Components[i])->ItemIndex = ini->ReadInteger("AutoPerForm", Form->Components[i]->Name, 0);}
	}
	LoginMap=ini->ReadInteger("MoveXY","MapID", 0);
	LoginX=ini->ReadInteger("MoveXY","X", 0);
	LoginY=ini->ReadInteger("MoveXY","Y", 0);
	NextX =ini->ReadInteger("MoveXY","MobNextX", 0);
	NodelayUseID=ini->ReadInteger("NodelaySkillId","ID", 0);
if (*(long*)(*(long*)MapIdPointer[0]+MapIdPointer[1]) == LoginMap) {MovHumToXY(LoginX,LoginY);}
	delete ini;}
} catch (...) {}
CreateThread(NULL,0xFF,AutoControl,NULL,0,NULL);
Form->HpKeyComboChange(Form->HpKeyCombo);Form->MpKeyComboChange(Form->MpKeyCombo);
Form->ComboBoxKey1Change(Form->ComboBoxKey1);Form->ComboBoxKey2Change(Form->ComboBoxKey2);
Form->ComboBoxKey3Change(Form->ComboBoxKey3);Form->ComboBoxKey4Change(Form->ComboBoxKey4);
Form->ComboBoxKey5Change(Form->ComboBoxKey5);Form->ComboBoxKey6Change(Form->ComboBoxKey6);
Form->ComboBoxKey7Change(Form->ComboBoxKey7);Form->ComboBoxKey8Change(Form->ComboBoxKey8);
VMProtectBegin("GameSpyTimer");
while (true){
	try {
		WritePointer(HpMpNoticeBase[0],HpMpNoticeBase[1],20);
		WritePointer(HpMpNoticeBase[0],HpMpNoticeBase[2],20);
		NowHp =ReadPointer(HpMpValueBase[0],HpMpValueBase[1]);
		NowMp =ReadPointer(HpMpValueBase[0],HpMpValueBase[2]);
		Form->Status->Caption = GameChactorId+"您好! \n HP:"+(String)(NowHp)+"  MP:"+(String)(NowMp)+
		"\n 人物座標("+(String)UserXY[0]+","+(String)UserXY[1]+")";
		if ((HpSettingLim>NowHp)&&(Form->HpProtect->Checked))
		{PressKey(PIDGetHWND(GetCurrentProcessId()),HpSettingKey,false);}
		if ((MpSettingLim>NowMp)&&(Form->MpProtect->Checked))
		{PressKey(PIDGetHWND(GetCurrentProcessId()),MpSettingKey,false);}
		if (PebIsDebuggedApproach()|PebNtGlobalFlagsApproach()) {delete Form;ExitProcess(0);}
		} catch (...) {}
		Sleep(500);Application->ProcessMessages();
	}
VMProtectEnd();
}
void __fastcall TCrackShieldMainForm::FormCreate(TObject *Sender){
VMProtectBegin("DllMain");
char myKey[1024] = {0};VMProtectGetCurrentHWID(myKey, sizeof(myKey));PcNum = myKey;
AnsiString Msg;
TStringList * MsgSave = new TStringList();
try {
TStringList * key = new TStringList();key->LoadFromFile(Path+ "CsVIP.dat");
AnsiString LincenseKey = key->Text;VMProtectSetSerialNumber(LincenseKey.c_str());
VMProtectSerialNumberData Serial;VMProtectGetSerialNumberData(&Serial, sizeof(Serial));
	if (Serial.nState == 0) {
		Msg =  Serial.wUserName     ;
		Msg = Serial.wUserName[0] != 0 ? ("授權給:\t" +Msg  + "\n").c_str() : "";
		Msg +="到期時間:\t" +IntToStr((int)Serial.dtExpire.wYear) + "/" + IntToStr((int)Serial.dtExpire.bMonth) + "/" + IntToStr((int)Serial.dtExpire.bDay) + "\n"
		"限制使用時間:\t" + IntToStr((int)Serial.bRunningTime) + "分鐘";
		MsgSave->Add(Msg);MsgSave->SaveToFile(Path+"\\Result.txt");
	} else {Msg = PcNum;MsgSave->Add(Msg);MsgSave->SaveToFile(Path+"\\Result.txt");ExitProcess(NULL);asm{push 00;ret};Application->Terminate();}
} catch (...) {
Msg = PcNum;MsgSave->Add(Msg);MsgSave->SaveToFile(Path+"\\Result.txt");ExitProcess(NULL);asm{push 00;ret};Application->Terminate();
}
this->Status->Caption = "等待進入遊戲中..";CreateThread(NULL,0xFF,HandleAllThingBeforeIntoGame,NULL,0,NULL);
VMProtectEnd();
}
//===============================================================================================//
void __fastcall TCrackShieldMainForm::ArrestClick(TObject *Sender){
try {
	if (741000300!=ReadPointer(MapIdPointer[0],MapIdPointer[1])) {
		MessageBox(0,(L"此功能適用於一百八十天黑洞內。"), L"提示訊息", MB_ICONERROR);((TCheckBox*)Sender)->Checked=false;
	}else if (((TCheckBox*)Sender)->Checked) {
		CostHpCount = 100000;NoHurt->Checked=true;AutoLoseHpSw=true;GodTime=00;
	}else{
		CostHpCount = 01;NoHurtClick(NoHurt);HurtHalfClick(HurtHalf);
	}
} catch (...) {}
}
//===============================================================================================////===============================================================================================//
void __fastcall TCrackShieldMainForm::RecSaveClick(TObject *Sender){
try {
	LoginX=UserXY[0];LoginY=UserXY[1];LoginMap=ReadPointer(MapIdPointer[0],MapIdPointer[1]);
	TIniFile* ini = new TIniFile(Path + "\\Data\\"+GameChactorId+"__Data.txt");
		for(int i = 0; i < ComponentCount; i++){
		if(Components[i]->ClassNameIs("TEdit")){
		ini->WriteString("AutoPerForm", Components[i]->Name, ((TEdit*)Components[i])->Text);
		} else if(Components[i]->ClassNameIs("TCheckBox")){
		ini->WriteBool("AutoPerForm", Components[i]->Name, ((TCheckBox*)Components[i])->Checked);
		} else if(Components[i]->ClassNameIs("TComboBox")){
		ini->WriteInteger("AutoPerForm", Components[i]->Name, ((TComboBox*)Components[i])->ItemIndex);
		}}
		ini->WriteInteger("NodelaySkillId", "ID",NodelayUseID );
		ini->WriteInteger("MoveXY", "X",LoginX );
		ini->WriteInteger("MoveXY", "Y",LoginY );
		ini->WriteInteger("MoveXY", "MapID",LoginMap );
		ini->WriteInteger("MoveXY", "MobNextX",NextX );
	delete ini;
	PrintStr("記錄完成！ 工作座標("+(String)(LoginX)+","+(String)(LoginY)+")",9);
} catch (...) {}
}
//===============================================================================================//
void __fastcall TCrackShieldMainForm::NoHurtClick(TObject *Sender){HurtMode = ((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::ZeroHurtClick(TObject *Sender){AutoLoseHpSw= ((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::KeyCb1Click(TObject *Sender){KeyOnOff[0]=((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::KeyCb2Click(TObject *Sender){KeyOnOff[1]=((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::KeyCb3Click(TObject *Sender){KeyOnOff[2]=((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::KeyCb4Click(TObject *Sender){KeyOnOff[3]=((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::KeyCb5Click(TObject *Sender){KeyOnOff[4]=((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::KeyCb6Click(TObject *Sender){KeyOnOff[5]=((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::KeyCb7Click(TObject *Sender){KeyOnOff[6]=((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::KeyCb8Click(TObject *Sender){KeyOnOff[7]=((TCheckBox*)Sender)->Checked ;}
void __fastcall TCrackShieldMainForm::KeyBlcokTime1Change(TObject *Sender){try {KeySetBlockTime[0] =1000*((TEdit*)Sender)->Text.ToInt();} catch (...) {}}
void __fastcall TCrackShieldMainForm::KeyBlcokTime2Change(TObject *Sender){try {KeySetBlockTime[1] =1000*((TEdit*)Sender)->Text.ToInt();} catch (...) {}}
void __fastcall TCrackShieldMainForm::KeyBlcokTime3Change(TObject *Sender){try {KeySetBlockTime[2] =1000*((TEdit*)Sender)->Text.ToInt();} catch (...) {}}
void __fastcall TCrackShieldMainForm::KeyBlcokTime4Change(TObject *Sender){try {KeySetBlockTime[3] =1000*((TEdit*)Sender)->Text.ToInt();} catch (...) {}}
void __fastcall TCrackShieldMainForm::KeyBlcokTime5Change(TObject *Sender){try {KeySetBlockTime[4] =1000*((TEdit*)Sender)->Text.ToInt();} catch (...) {}}
void __fastcall TCrackShieldMainForm::KeyBlcokTime6Change(TObject *Sender){try {KeySetBlockTime[5] =1000*((TEdit*)Sender)->Text.ToInt();} catch (...) {}}
void __fastcall TCrackShieldMainForm::KeyBlcokTime7Change(TObject *Sender){try {KeySetBlockTime[6] =1000*((TEdit*)Sender)->Text.ToInt();} catch (...) {}}
void __fastcall TCrackShieldMainForm::KeyBlcokTime8Change(TObject *Sender){try {KeySetBlockTime[7] =1000*((TEdit*)Sender)->Text.ToInt();} catch (...) {}}
void __fastcall TCrackShieldMainForm::ComboBoxKey1Change(TObject *Sender){Key[0] = GetVkCodeByString(((TComboBox*)Sender)->Text);}
void __fastcall TCrackShieldMainForm::ComboBoxKey2Change(TObject *Sender){Key[1] = GetVkCodeByString(((TComboBox*)Sender)->Text);}
void __fastcall TCrackShieldMainForm::ComboBoxKey3Change(TObject *Sender){Key[2] = GetVkCodeByString(((TComboBox*)Sender)->Text);}
void __fastcall TCrackShieldMainForm::ComboBoxKey4Change(TObject *Sender){Key[3] = GetVkCodeByString(((TComboBox*)Sender)->Text);}
void __fastcall TCrackShieldMainForm::ComboBoxKey5Change(TObject *Sender){Key[4] = GetVkCodeByString(((TComboBox*)Sender)->Text);}
void __fastcall TCrackShieldMainForm::ComboBoxKey6Change(TObject *Sender){Key[5] = GetVkCodeByString(((TComboBox*)Sender)->Text);}
void __fastcall TCrackShieldMainForm::ComboBoxKey7Change(TObject *Sender){Key[6] = GetVkCodeByString(((TComboBox*)Sender)->Text);}
void __fastcall TCrackShieldMainForm::ComboBoxKey8Change(TObject *Sender){Key[7] = GetVkCodeByString(((TComboBox*)Sender)->Text);}
void __fastcall TCrackShieldMainForm::FarGoClick(TObject *Sender){if (((TCheckBox*)Sender)->Checked) {LrLandFar=150;}else{LrLandFar=70;}}
void __fastcall TCrackShieldMainForm::FullMapLevUpClick(TObject *Sender){LevUpMode = 0;}
void __fastcall TCrackShieldMainForm::VacLevUpClick(TObject *Sender){LevUpMode = 1;}
void __fastcall TCrackShieldMainForm::KikiLevUpClick(TObject *Sender){LevUpMode = 2;}
//=============================================================================================//
void __fastcall TCrackShieldMainForm::Reach180Click(TObject *Sender)
{
*(long*)(*(long*)(0x0E8D7A0)+0x579c) = 00;//151.2 奇幻村脫逃
}


