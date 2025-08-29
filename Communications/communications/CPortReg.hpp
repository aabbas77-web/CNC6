// Borland C++ Builder
// Copyright (c) 1995, 1999 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'CPortReg.pas' rev: 5.00

#ifndef CPortRegHPP
#define CPortRegHPP

#pragma delphiheader begin
#pragma option push -w-
#pragma option push -Vx
#include <Menus.hpp>	// Pascal unit
#include <Classes.hpp>	// Pascal unit
#include <DsgnIntf.hpp>	// Pascal unit
#include <SysInit.hpp>	// Pascal unit
#include <System.hpp>	// Pascal unit

//-- user supplied -----------------------------------------------------------

namespace Cportreg
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TComLibraryEditor;
class PASCALIMPLEMENTATION TComLibraryEditor : public Dsgnintf::TComponentEditor 
{
	typedef Dsgnintf::TComponentEditor inherited;
	
public:
	virtual AnsiString __fastcall GetVerb(int Index);
	virtual int __fastcall GetVerbCount(void);
	virtual void __fastcall ExecuteVerb(int Index);
	virtual void __fastcall PrepareItem(int Index, const Menus::TMenuItem* AItem);
public:
	#pragma option push -w-inl
	/* TComponentEditor.Create */ inline __fastcall virtual TComLibraryEditor(Classes::TComponent* AComponent
		, Dsgnintf::_di_IFormDesigner ADesigner) : Dsgnintf::TComponentEditor(AComponent, ADesigner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TComLibraryEditor(void) { }
	#pragma option pop
	
};


class DELPHICLASS TComPortEditor;
class PASCALIMPLEMENTATION TComPortEditor : public TComLibraryEditor 
{
	typedef TComLibraryEditor inherited;
	
public:
	virtual void __fastcall ExecuteVerb(int Index);
	virtual AnsiString __fastcall GetVerb(int Index);
	virtual int __fastcall GetVerbCount(void);
	virtual void __fastcall PrepareItem(int Index, const Menus::TMenuItem* AItem);
	virtual void __fastcall Edit(void);
public:
	#pragma option push -w-inl
	/* TComponentEditor.Create */ inline __fastcall virtual TComPortEditor(Classes::TComponent* AComponent
		, Dsgnintf::_di_IFormDesigner ADesigner) : TComLibraryEditor(AComponent, ADesigner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TComPortEditor(void) { }
	#pragma option pop
	
};


class DELPHICLASS TComTerminalEditor;
class PASCALIMPLEMENTATION TComTerminalEditor : public TComLibraryEditor 
{
	typedef TComLibraryEditor inherited;
	
public:
	virtual void __fastcall ExecuteVerb(int Index);
	virtual AnsiString __fastcall GetVerb(int Index);
	virtual int __fastcall GetVerbCount(void);
	virtual void __fastcall PrepareItem(int Index, const Menus::TMenuItem* AItem);
	virtual void __fastcall Edit(void);
public:
	#pragma option push -w-inl
	/* TComponentEditor.Create */ inline __fastcall virtual TComTerminalEditor(Classes::TComponent* AComponent
		, Dsgnintf::_di_IFormDesigner ADesigner) : TComLibraryEditor(AComponent, ADesigner) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TObject.Destroy */ inline __fastcall virtual ~TComTerminalEditor(void) { }
	#pragma option pop
	
};


class DELPHICLASS TComPortProperty;
class PASCALIMPLEMENTATION TComPortProperty : public Dsgnintf::TStringProperty 
{
	typedef Dsgnintf::TStringProperty inherited;
	
public:
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
	virtual void __fastcall GetValues(Classes::TGetStrProc Proc);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TComPortProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : Dsgnintf::TStringProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TComPortProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TComFontProperty;
class PASCALIMPLEMENTATION TComFontProperty : public Dsgnintf::TClassProperty 
{
	typedef Dsgnintf::TClassProperty inherited;
	
public:
	virtual void __fastcall Edit(void);
	virtual Dsgnintf::TPropertyAttributes __fastcall GetAttributes(void);
protected:
	#pragma option push -w-inl
	/* TPropertyEditor.Create */ inline __fastcall virtual TComFontProperty(const Dsgnintf::_di_IFormDesigner 
		ADesigner, int APropCount) : Dsgnintf::TClassProperty(ADesigner, APropCount) { }
	#pragma option pop
	
public:
	#pragma option push -w-inl
	/* TPropertyEditor.Destroy */ inline __fastcall virtual ~TComFontProperty(void) { }
	#pragma option pop
	
};


class DELPHICLASS TComCat;
class PASCALIMPLEMENTATION TComCat : public Dsgnintf::TPropertyCategory 
{
	typedef Dsgnintf::TPropertyCategory inherited;
	
public:
	#pragma option push -w-inl
	/* virtual class method */ virtual AnsiString __fastcall Name() { return Name(__classid(TComCat)); }
		
	#pragma option pop
	/*         class method */ static AnsiString __fastcall Name(TMetaClass* vmt);
	#pragma option push -w-inl
	/* virtual class method */ virtual AnsiString __fastcall Description() { return Description(__classid(TComCat)
		); }
	#pragma option pop
	/*         class method */ static AnsiString __fastcall Description(TMetaClass* vmt);
public:
	#pragma option push -w-inl
	/* TPropertyCategory.Create */ inline __fastcall TComCat(void) : Dsgnintf::TPropertyCategory() { }
	#pragma option pop
	#pragma option push -w-inl
	/* TPropertyCategory.Destroy */ inline __fastcall virtual ~TComCat(void) { }
	#pragma option pop
	
};


class DELPHICLASS TComPacketCat;
class PASCALIMPLEMENTATION TComPacketCat : public Dsgnintf::TPropertyCategory 
{
	typedef Dsgnintf::TPropertyCategory inherited;
	
public:
	#pragma option push -w-inl
	/* virtual class method */ virtual AnsiString __fastcall Name() { return Name(__classid(TComPacketCat)
		); }
	#pragma option pop
	/*         class method */ static AnsiString __fastcall Name(TMetaClass* vmt);
	#pragma option push -w-inl
	/* virtual class method */ virtual AnsiString __fastcall Description() { return Description(__classid(TComPacketCat)
		); }
	#pragma option pop
	/*         class method */ static AnsiString __fastcall Description(TMetaClass* vmt);
public:
	#pragma option push -w-inl
	/* TPropertyCategory.Create */ inline __fastcall TComPacketCat(void) : Dsgnintf::TPropertyCategory(
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TPropertyCategory.Destroy */ inline __fastcall virtual ~TComPacketCat(void) { }
	#pragma option pop
	
};


class DELPHICLASS TComAsciiSetupCat;
class PASCALIMPLEMENTATION TComAsciiSetupCat : public Dsgnintf::TPropertyCategory 
{
	typedef Dsgnintf::TPropertyCategory inherited;
	
public:
	#pragma option push -w-inl
	/* virtual class method */ virtual AnsiString __fastcall Name() { return Name(__classid(TComAsciiSetupCat)
		); }
	#pragma option pop
	/*         class method */ static AnsiString __fastcall Name(TMetaClass* vmt);
	#pragma option push -w-inl
	/* virtual class method */ virtual AnsiString __fastcall Description() { return Description(__classid(TComAsciiSetupCat)
		); }
	#pragma option pop
	/*         class method */ static AnsiString __fastcall Description(TMetaClass* vmt);
public:
	#pragma option push -w-inl
	/* TPropertyCategory.Create */ inline __fastcall TComAsciiSetupCat(void) : Dsgnintf::TPropertyCategory(
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TPropertyCategory.Destroy */ inline __fastcall virtual ~TComAsciiSetupCat(void) { }
	#pragma option pop
	
};


class DELPHICLASS TComPacketEventsCat;
class PASCALIMPLEMENTATION TComPacketEventsCat : public Dsgnintf::TPropertyCategory 
{
	typedef Dsgnintf::TPropertyCategory inherited;
	
public:
	#pragma option push -w-inl
	/* virtual class method */ virtual AnsiString __fastcall Name() { return Name(__classid(TComPacketEventsCat)
		); }
	#pragma option pop
	/*         class method */ static AnsiString __fastcall Name(TMetaClass* vmt);
	#pragma option push -w-inl
	/* virtual class method */ virtual AnsiString __fastcall Description() { return Description(__classid(TComPacketEventsCat)
		); }
	#pragma option pop
	/*         class method */ static AnsiString __fastcall Description(TMetaClass* vmt);
public:
	#pragma option push -w-inl
	/* TPropertyCategory.Create */ inline __fastcall TComPacketEventsCat(void) : Dsgnintf::TPropertyCategory(
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TPropertyCategory.Destroy */ inline __fastcall virtual ~TComPacketEventsCat(void) { }
	#pragma option pop
	
};


class DELPHICLASS TComTerminalCat;
class PASCALIMPLEMENTATION TComTerminalCat : public Dsgnintf::TPropertyCategory 
{
	typedef Dsgnintf::TPropertyCategory inherited;
	
public:
	#pragma option push -w-inl
	/* virtual class method */ virtual AnsiString __fastcall Name() { return Name(__classid(TComTerminalCat)
		); }
	#pragma option pop
	/*         class method */ static AnsiString __fastcall Name(TMetaClass* vmt);
	#pragma option push -w-inl
	/* virtual class method */ virtual AnsiString __fastcall Description() { return Description(__classid(TComTerminalCat)
		); }
	#pragma option pop
	/*         class method */ static AnsiString __fastcall Description(TMetaClass* vmt);
public:
	#pragma option push -w-inl
	/* TPropertyCategory.Create */ inline __fastcall TComTerminalCat(void) : Dsgnintf::TPropertyCategory(
		) { }
	#pragma option pop
	#pragma option push -w-inl
	/* TPropertyCategory.Destroy */ inline __fastcall virtual ~TComTerminalCat(void) { }
	#pragma option pop
	
};


//-- var, const, procedure ---------------------------------------------------
extern PACKAGE void __fastcall Register(void);

}	/* namespace Cportreg */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Cportreg;
#endif
#pragma option pop	// -w-
#pragma option pop	// -Vx

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// CPortReg
