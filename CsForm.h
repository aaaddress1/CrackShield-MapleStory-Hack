//---------------------------------------------------------------------------

#ifndef CsFormH
#define CsFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
//---------------------------------------------------------------------------
class TCrackShieldMainForm : public TForm
{
__published:	// IDE-managed Components
	TLabel *Status;
	TButton *RecSave;
	TPageControl *PageControl;
	TTabSheet *TabSheet1;
	TGroupBox *HurtSetGroup;
	TCheckBox *NoHurt;
	TCheckBox *ZeroHurt;
	TCheckBox *HurtHalf;
	TGroupBox *ArrestGroup;
	TCheckBox *Arrest;
	TCheckBox *Reach180;
	TGroupBox *BaseFuction;
	TCheckBox *StopMob;
	TCheckBox *DoubleShoot;
	TCheckBox *SuperSkill;
	TCheckBox *RollNodelay;
	TCheckBox *MobNoAttackCB;
	TCheckBox *FinalAttackNodelay;
	TCheckBox *AutoPick;
	TCheckBox *MobLr;
	TCheckBox *StupidMob;
	TCheckBox *Fullsw;
	TCheckBox *WalkSpeedUp;
	TGroupBox *HpMpProtect;
	TCheckBox *HpProtect;
	TEdit *HpSetCount;
	TComboBox *HpKeyCombo;
	TCheckBox *MpProtect;
	TEdit *MpSetCount;
	TComboBox *MpKeyCombo;
	TTabSheet *TabSheet2;
	TGroupBox *LevUpModeGroup;
	TLabel *Tip1;
	TRadioButton *VacLevUp;
	TRadioButton *FullMapLevUp;
	TRadioButton *KikiLevUp;
	TCheckBox *FarGo;
	TEdit *BlockPickTime;
	TGroupBox *KeyGroup;
	TCheckBox *KeyCb1;
	TEdit *KeyBlcokTime1;
	TComboBox *ComboBoxKey1;
	TCheckBox *KeyCb2;
	TEdit *KeyBlcokTime2;
	TComboBox *ComboBoxKey2;
	TCheckBox *KeyCb3;
	TEdit *KeyBlcokTime3;
	TComboBox *ComboBoxKey3;
	TCheckBox *KeyCb4;
	TEdit *KeyBlcokTime4;
	TComboBox *ComboBoxKey4;
	TCheckBox *KeyCb5;
	TEdit *KeyBlcokTime5;
	TComboBox *ComboBoxKey5;
	TCheckBox *KeyCb6;
	TEdit *KeyBlcokTime6;
	TComboBox *ComboBoxKey6;
	TCheckBox *KeyCb7;
	TEdit *KeyBlcokTime7;
	TComboBox *ComboBoxKey7;
	TCheckBox *KeyCb8;
	TEdit *KeyBlcokTime8;
	TComboBox *ComboBoxKey8;
	TTabSheet *TabSheet3;
	TListBox *BlackItemList;
	TLabel *ItemFocusStatus;
	TButton *AddBlackItem;
	TButton *DeleteOne;
	TButton *ClearList;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall NoHurtClick(TObject *Sender);
	void __fastcall ZeroHurtClick(TObject *Sender);
	void __fastcall HurtHalfClick(TObject *Sender);
	void __fastcall ArrestClick(TObject *Sender);
	void __fastcall SuperSkillClick(TObject *Sender);
	void __fastcall RollNodelayClick(TObject *Sender);
	void __fastcall MobNoAttackCBClick(TObject *Sender);
	void __fastcall FinalAttackNodelayClick(TObject *Sender);
	void __fastcall AutoPickClick(TObject *Sender);
	void __fastcall MobLrClick(TObject *Sender);
	void __fastcall RegKeyBoardHook();
	void __fastcall StupidMobClick(TObject *Sender);
	void __fastcall FullswClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall WalkSpeedUpClick(TObject *Sender);
	void __fastcall StopMobClick(TObject *Sender);
	void __fastcall HpSetCountChange(TObject *Sender);
	void __fastcall MpSetCountChange(TObject *Sender);
	void __fastcall HpKeyComboChange(TObject *Sender);
	void __fastcall MpKeyComboChange(TObject *Sender);
	void __fastcall RecSaveClick(TObject *Sender);
	void __fastcall KeyCb1Click(TObject *Sender);
	void __fastcall KeyCb2Click(TObject *Sender);
	void __fastcall KeyCb3Click(TObject *Sender);
	void __fastcall KeyCb4Click(TObject *Sender);
	void __fastcall KeyCb5Click(TObject *Sender);
	void __fastcall KeyCb6Click(TObject *Sender);
	void __fastcall KeyCb7Click(TObject *Sender);
	void __fastcall KeyCb8Click(TObject *Sender);
	void __fastcall KeyBlcokTime1Change(TObject *Sender);
	void __fastcall KeyBlcokTime2Change(TObject *Sender);
	void __fastcall KeyBlcokTime3Change(TObject *Sender);
	void __fastcall KeyBlcokTime4Change(TObject *Sender);
	void __fastcall KeyBlcokTime5Change(TObject *Sender);
	void __fastcall KeyBlcokTime6Change(TObject *Sender);
	void __fastcall KeyBlcokTime7Change(TObject *Sender);
	void __fastcall KeyBlcokTime8Change(TObject *Sender);
	void __fastcall ComboBoxKey1Change(TObject *Sender);
	void __fastcall ComboBoxKey2Change(TObject *Sender);
	void __fastcall ComboBoxKey3Change(TObject *Sender);
	void __fastcall ComboBoxKey4Change(TObject *Sender);
	void __fastcall ComboBoxKey5Change(TObject *Sender);
	void __fastcall ComboBoxKey6Change(TObject *Sender);
	void __fastcall ComboBoxKey7Change(TObject *Sender);
	void __fastcall ComboBoxKey8Change(TObject *Sender);
	void __fastcall FarGoClick(TObject *Sender);
	void __fastcall FullMapLevUpClick(TObject *Sender);
	void __fastcall VacLevUpClick(TObject *Sender);
	void __fastcall KikiLevUpClick(TObject *Sender);
	void __fastcall Reach180Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TCrackShieldMainForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCrackShieldMainForm *CrackShieldMainForm;
//---------------------------------------------------------------------------
#endif
