#pragma once
#include "duiwnd.h"
#include "DuiRichEdit.h"
#include "DuiDropDownList.h"

namespace DuiEngine
{

#define IDC_CB_EDIT	-100

struct CBITEM
{
	CDuiStringT strText;
	int iIcon;
	LPARAM lParam;
};

class CDuiComboBox;

class CComboEdit:public CDuiEdit
{
public:
	CComboEdit(CDuiComboBox *pOwner);
	virtual ~CComboEdit(){}

protected:
	void OnMouseHover(WPARAM wParam, CPoint ptPos);
	
	void OnMouseLeave();

	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	virtual LRESULT DuiNotify(LPNMHDR pnms);

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_MOUSEHOVER(OnMouseHover)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
		MSG_WM_KEYDOWN(OnKeyDown)
	DUIWIN_END_MSG_MAP()
};

class DUI_EXP CDuiComboBox 
	: public CDuiWindow
	, public CDuiDropDownListOwner
{
	DUIOBJ_DECLARE_CLASS_NAME(CDuiComboBox, "combobox")

public:
	CDuiComboBox(void);
	virtual ~CDuiComboBox(void);

	int SetCurSel(int iSel);

	int GetCurSel();

	BOOL GetItemInfo(int iItem,CBITEM *pCbItem);

	LPARAM GetItemData(int iItem) const;

	int SetItemData(int iItem, LPARAM lParam);

	int InsertItem(int iPos,LPCTSTR pszText,int iIcon,LPARAM lParam);

	BOOL DeleteItem(int iItem);

	BOOL DeleteAllItem();

	int GetWindowText(LPTSTR lpString, int nMaxCount );
	
	BOOL SetWindowText(LPCTSTR strText);

	virtual LRESULT DuiNotify(LPNMHDR pnms);

	void DropDown();
	void CloseUp();

	CDuiDropDownListBase *GetDropDownList(){return m_pListBox;}
protected:

	HWND GetHostHwnd();
	CDuiWindow* GetWindow();
	int  GetListItemCount();
	LPCTSTR	GetListItemText(int nItem);
	int GetListItemIcon(int nItem);
	int GetListCurSel();
	int GetAnimateTime();
	void OnDropDownListClose();

protected:

	void GetDropBtnRect(LPRECT prc);
	virtual BOOL LoadChildren(pugi::xml_node xmlNode);	
	virtual void GetTextRect(LPRECT pRect);

	void OnPaint(CDCHandle dc);
	void OnLButtonDown(UINT nFlags,CPoint pt);
	void OnLButtonUp(UINT nFlags,CPoint pt);
	void OnLButtonDbClick(UINT nFlags,CPoint pt);
	void OnMouseMove(UINT nFlags,CPoint pt);
	void OnMouseLeave();
	void OnKeyDown( TCHAR nChar, UINT nRepCnt, UINT nFlags );
	void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

	UINT OnGetDuiCode();
	BOOL IsTabStop();

	DUIWIN_DECLARE_ATTRIBUTES_BEGIN()
		DUIWIN_INT_ATTRIBUTE("dropdown", m_bDropdown, FALSE)
		DUIWIN_INT_ATTRIBUTE("dropheight", m_nDropHeight, FALSE)
		DUIWIN_INT_ATTRIBUTE("cursel", m_iCurSel, FALSE)
		DUIWIN_SKIN_ATTRIBUTE("btnskin", m_pSkinBtn, FALSE)
		DUIWIN_INT_ATTRIBUTE("itempanel", m_bItemPanel, FALSE)
		DUIWIN_INT_ATTRIBUTE("animtime", m_iAnimTime, FALSE)
	DUIWIN_DECLARE_ATTRIBUTES_END()

	DUIWIN_BEGIN_MSG_MAP()
		MSG_WM_PAINT(OnPaint)
		MSG_WM_LBUTTONDOWN(OnLButtonDown)		
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_LBUTTONDBLCLK(OnLButtonDbClick)
		MSG_WM_MOUSEMOVE(OnMouseMove)
		MSG_WM_MOUSELEAVE(OnMouseLeave)
		MSG_WM_KEYDOWN(OnKeyDown) 
		MSG_WM_CHAR(OnChar)
	DUIWIN_END_MSG_MAP()

protected:

	CDuiRichEdit *m_pEdit;
	CDuiDropDownListBase  *m_pListBox;
	pugi::xml_document m_xmlListStyle;
	CDuiSkinBase *m_pSkinBtn;
	DWORD		  m_dwBtnState;
	
	BOOL m_bDropdown;
	BOOL m_bItemPanel;
	int  m_nDropHeight;
	int	m_iCurSel;
	int  m_iAnimTime;	

    CDuiArray<CBITEM> m_arrCbItem;

};

}//namespace