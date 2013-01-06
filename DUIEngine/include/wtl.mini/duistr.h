/********************************************************************
	created:	2013/01/06
	created:	6:1:2013   16:42
	filename: 	duistr.h
	author:		Huang Jianxiong
	
	purpose:	
*********************************************************************/
#pragma once

#include <yvals.h>
#include <wchar.h>

namespace DuiEngine
{

template<class _Elem>
struct DUI_EXP char_traits
{	// properties of a string or stream element
	typedef _Elem char_type;

	static void  assign(_Elem& _Left, const _Elem& _Right)
	{	// assign an element
		_Left = _Right;
	}

	static int compare(const _Elem * _First1,const _Elem * _First2)
	{
		return wcscmp(_First1,_First2);
	}

	static int compareNoCase(const _Elem * _First1,const _Elem * _First2)
	{
		return wcsicmp(_First1,_First2);
	}
	
	static void strupr(_Elem * pstr)
	{

	}

	static void strlwr(_Elem * pstr)
	{

	}

	static bool  eq(const _Elem& _Left, const _Elem& _Right)
	{	// test for element equality
		return (_Left == _Right);
	}

	static size_t  length(_In_z_ const _Elem *_First)
	{	// find length of null-terminated sequence
		//		_DEBUG_POINTER(_First);
		if(!_First) return 0;
		size_t _Count;
		for (_Count = 0; !eq(*_First, _Elem()); ++_First)
			++_Count;
		return (_Count);
	}

	
	static _Elem * copy(_Out_cap_(_Count) _Elem *_First1,
		_In_count_(_Count) const _Elem *_First2, size_t _Count)
	{	// copy [_First1, _First1 + _Count) to [_First2, ...)
		// assume there is enough space in the destination buffer
		return _Copy_s(_First1, _Count, _First2, _Count);
	}

	static _Elem * _Copy_s(_Out_cap_(_Dest_size) _Elem *_First1, size_t _Dest_size,
		_In_count_(_Count) const _Elem *_First2, size_t _Count)
	{	// copy [_First1, _First1 + _Count) to [_First2, ...)
		//		_DEBUG_POINTER(_First1);
		//		_DEBUG_POINTER(_First2);
		_Elem *_Next = _First1;
		for (; 0 < _Count; --_Count, ++_Next, ++_First2)
			assign(*_Next, *_First2);
		*_Next=0;
		return (_First1);
	}

	static const _Elem * find(_In_count_(_Count) const _Elem *_First,
		size_t _Count, const _Elem& _Ch)
	{	// look for _Ch in [_First, _First + _Count)
		//		_DEBUG_POINTER(_First);
		for (; 0 < _Count; --_Count, ++_First)
			if (eq(*_First, _Ch))
				return (_First);
		return (0);
	}

	static const _Elem * find(const _Elem *_First1,const _Elem *_First2)
	{
		return (0);
	}

	static const _Elem *findchr(const _Elem * _First1,	_Elem ch)
	{
		_Elem *Ret=0,*p=_First1;
		while(*p)
		{
			if(eq(*p,ch))
			{
				Ret=p;
			}
			p++;
		}
		return Ret;
	}

	static _Elem * assign(_Out_cap_(_Count) _Elem *_First,
		size_t _Count, _Elem _Ch)
	{	// assign _Count * _Ch to [_First, ...)
		//		_DEBUG_POINTER(_First);
		_Elem *_Next = _First;
		for (; 0 < _Count; --_Count, ++_Next)
			assign(*_Next, _Ch);
		return (_First);
	}

	static BOOL IsBadStringPtr(const _Elem * pstr,int cchMax)
	{
		return FALSE;
	}

	static int wvsprintf(_Elem * lpOutput,
		const _Elem * lpFmt,
		va_list & arglist
		)
	{
		return 0;
	}
};

// STRUCT char_traits<wchar_t>
template<> struct DUI_EXP char_traits<wchar_t>
{	// properties of a string or stream wchar_t element
	typedef wchar_t _Elem;
	typedef _Elem char_type;	// for overloads

	static void  assign(_Elem& _Left, const _Elem& _Right)
	{	// assign an element
		_Left = _Right;
	}

	static int compare(const _Elem * _First1,const _Elem * _First2)
	{
		return wcscmp(_First1,_First2);
	}

	static int compareNoCase(const _Elem * _First1,const _Elem * _First2)
	{
		return _wcsicmp(_First1,_First2);
	}

	static void strupr(_Elem * pstr)
	{
		_wcsupr(pstr);
	}

	static void strlwr(_Elem * pstr)
	{
		_wcslwr(pstr);
	}

	static bool  eq(const _Elem& _Left, const _Elem& _Right)
	{	// test for element equality
		return (_Left == _Right);
	}

	static size_t  length(_In_z_ const _Elem *_First)
	{	// find length of null-terminated sequence
		//		_DEBUG_POINTER(_First);
		if(!_First) return 0;
		return (::wcslen(_First));
	}

	
		static _Elem * copy(_Out_cap_(_Count) _Elem *_First1, _In_count_(_Count) const _Elem *_First2,
		size_t _Count)
	{	// copy [_First1, _First1 + _Count) to [_First2, ...)
		// assume there is enough space in the destination buffer
		return _Copy_s(_First1, _Count, _First2, _Count);
	}

	static _Elem * _Copy_s(_Out_cap_(_Size_in_words) _Elem *_First1, size_t _Size_in_words, _In_count_(_Count) const _Elem *_First2,
		size_t _Count)
	{	// copy [_First1, _First1 + _Count) to [_First2, ...)
		//		_DEBUG_POINTER(_First1);
		//		_DEBUG_POINTER(_First2);
		_CRT_SECURE_WMEMCPY(_First1, _Size_in_words, _First2, _Count);
		return _First1;
	}

	static const _Elem * find(_In_count_(_Count) const _Elem *_First, size_t _Count,
		const _Elem& _Ch)
	{	// look for _Ch in [_First, _First + _Count)
		//		_DEBUG_POINTER(_First);
		return ((const _Elem *)::wmemchr(_First, _Ch, _Count));
	}

	static const _Elem * find(const _Elem *_First1,const _Elem *_First2)
	{
		return ::wcsstr(_First1,_First2);
	}

	static const _Elem *findchr(const _Elem * _First1,	_Elem ch)
	{
		return ::wcsrchr(_First1,ch);
	}

	static _Elem * assign(_Out_cap_(_Count) _Elem *_First, size_t _Count, _Elem _Ch)
	{	// assign _Count * _Ch to [_First, ...)
		//		_DEBUG_POINTER(_First);
		return ((_Elem *)::wmemset(_First, _Ch, _Count));
	}

	static BOOL IsBadStringPtr(const _Elem * pstr,int cchMax)
	{
		return ::IsBadStringPtrW(pstr,cchMax);;
	}

	static int wvsprintf(_Elem * lpOutput,
		const _Elem * lpFmt,
		va_list & arglist
		)
	{
		return ::wvsprintfW(lpOutput,lpFmt,arglist);
	}
};


// STRUCT char_traits<char> (FROM <string>)
template<> struct DUI_EXP char_traits<char>
{	// properties of a string or stream char element
	typedef char _Elem;
	typedef _Elem char_type;

	static void  assign(_Elem& _Left, const _Elem& _Right)
	{	// assign an element
		_Left = _Right;
	}

	static int compare(const _Elem * _First1,const _Elem * _First2)
	{
		return ::strcmp(_First1,_First2);
	}

	static int compareNoCase(const _Elem * _First1,const _Elem * _First2)
	{
		return ::_stricmp(_First1,_First2);
	}

	static void strupr(_Elem * pstr)
	{
		::_strupr(pstr);
	}

	static void strlwr(_Elem * pstr)
	{
		::_strlwr(pstr);
	}

	static bool  eq(const _Elem& _Left, const _Elem& _Right)
	{	// test for element equality
		return (_Left == _Right);
	}

	static size_t  length(_In_z_ const _Elem *_First)
	{	// find length of null-terminated string
		//		_DEBUG_POINTER(_First);
		if(!_First) return 0;
		return (::strlen(_First));
	}

	
		static _Elem * copy(_Out_cap_(_Count) _Elem *_First1, _In_count_(_Count) const _Elem *_First2,
		size_t _Count)
	{	// copy [_First1, _First1 + _Count) to [_First2, ...)
		// assume there is enough space in the destination buffer
		return _Copy_s(_First1, _Count, _First2, _Count);
	}

	static _Elem * _Copy_s(_Out_cap_(_Size_in_bytes) _Elem *_First1, size_t _Size_in_bytes, _In_count_(_Count) const _Elem *_First2,
		size_t _Count)
	{	// copy [_First1, _First1 + _Count) to [_First2, ...)
		//		_DEBUG_POINTER(_First1);
		//		_DEBUG_POINTER(_First2);
		_CRT_SECURE_MEMCPY(_First1, _Size_in_bytes, _First2, _Count);
		_First1[_Count]=0;
		return _First1;
	}

	static const _Elem * find(_In_count_(_Count) const _Elem *_First, size_t _Count,
		const _Elem& _Ch)
	{	// look for _Ch in [_First, _First + _Count)
		//		_DEBUG_POINTER(_First);
		return ((const _Elem *)::memchr(_First, _Ch, _Count));
	}

	static const _Elem * find(const _Elem *_First1,const _Elem *_First2)
	{
		return ::strstr(_First1,_First2);
	}
	
	static const _Elem *findchr(const _Elem * _First1,	_Elem ch)
	{
		return ::strrchr(_First1,ch);
	}

	static _Elem * assign(_Out_cap_(_Count) _Elem *_First, size_t _Count, _Elem _Ch)
	{	// assign _Count * _Ch to [_First, ...)
		//		_DEBUG_POINTER(_First);
		return ((_Elem *)::memset(_First, _Ch, _Count));
	}

	static BOOL IsBadStringPtr(const _Elem * pstr,int cchMax)
	{
		return ::IsBadStringPtrA(pstr,cchMax);;
	}

	static int wvsprintf(_Elem * lpOutput,
		const _Elem * lpFmt,
		va_list & arglist
		)
	{
		return ::wvsprintfA(lpOutput,lpFmt,arglist);
	}
};


template<class _Elem,class _Traits=char_traits<_Elem>>
class DUI_EXP CDuiString
{
public:
	enum { MAX_LOCAL_STRING_LEN = 63 };

	CDuiString() : m_pstr(m_szBuffer),m_nLength(0)
	{
		m_szBuffer[0] = '\0';
	}

	CDuiString(const _Elem ch) : m_pstr(m_szBuffer),m_nLength(0)
	{
		m_szBuffer[0] = ch;
		m_szBuffer[1] = '\0';
	}

	CDuiString(const _Elem * lpsz, int nLen=-1) : m_pstr(m_szBuffer),m_nLength(0)
	{      
		if(nLen==-1) nLen=_Traits::length(lpsz);
		DUIASSERT(!_Traits::IsBadStringPtr(lpsz,nLen) || lpsz==NULL);
		m_szBuffer[0] = '\0';
		Assign(lpsz, nLen);
	}

	CDuiString(const CDuiString& src) : m_pstr(m_szBuffer),m_nLength(0)
	{
		m_szBuffer[0] = '\0';
		Assign(src.m_pstr);
	}

	~CDuiString()
	{
		if( m_pstr != m_szBuffer ) free(m_pstr);
	}

	int GetLength() const
	{ 
		return m_nLength; 
	}

	operator const _Elem *() const 
	{ 
		return m_pstr; 
	}

	void Append(const _Elem * pstr,int nCount=-1)
	{
		if(nCount<0) nCount=_Traits::length(pstr);

		DUIASSERT(!_Traits::IsBadStringPtr(pstr,nCount));

		if( nCount + GetLength() >= MAX_LOCAL_STRING_LEN ) {
			if( m_pstr == m_szBuffer ) {
				m_pstr = static_cast<_Elem *>(malloc((nCount +GetLength()+ 1) * sizeof(_Elem)));
				_Traits::copy(m_pstr,m_szBuffer,GetLength());
			}
			else {
				m_pstr = static_cast<_Elem *>(realloc(m_pstr, (nCount +GetLength()+ 1) * sizeof(_Elem)));
			}
			_Traits::copy(m_pstr+GetLength(),pstr,nCount);
		}
		else {
			if( m_pstr != m_szBuffer ) {
				free(m_pstr);
				m_pstr = m_szBuffer;
			}
			_Traits::copy(m_pstr+GetLength(),pstr,nCount);
		}
		m_nLength+=nCount;
		m_pstr[m_nLength]=0;
	}

	void Assign(const _Elem * pstr, int cchMax=-1)
	{
		if(cchMax<0) cchMax=_Traits::length(pstr);

		if( cchMax < MAX_LOCAL_STRING_LEN ) {
			if( m_pstr != m_szBuffer ) {
				free(m_pstr);
				m_pstr = m_szBuffer;
			}
		}
		else if( cchMax > GetLength() || m_pstr == m_szBuffer ) {
			if( m_pstr == m_szBuffer ) m_pstr = NULL;
			m_pstr = static_cast<_Elem *>(realloc(m_pstr, (cchMax + 1) * sizeof(_Elem)));
		}
		_Traits::copy(m_pstr,pstr,cchMax);
		m_pstr[cchMax]=0;
		m_nLength=cchMax;
	}

	bool IsEmpty() const 
	{ 
		return m_nLength==0; 
	}

	void Empty() 
	{ 
		if( m_pstr != m_szBuffer ) free(m_pstr);
		m_pstr = m_szBuffer;
		m_szBuffer[0] = '\0'; 
		m_nLength=0;
	}

	const _Elem * GetData() const
	{
		return m_pstr;
	}

	_Elem GetAt(int nIndex) const
	{
		return m_pstr[nIndex];
	}

	_Elem operator[] (int nIndex) const
	{ 
		return m_pstr[nIndex];
	}   

	const CDuiString& operator=(const CDuiString& src)
	{      
		Assign(src);
		return *this;
	}

	const CDuiString& operator=(const _Elem * lpStr)
	{      
		if ( lpStr )
		{
			DUIASSERT(!_Traits::IsBadStringPtr(lpStr,-1));
			Assign(lpStr);
		}
		else
		{
			Empty();
		}
		return *this;
	}

	const CDuiString& operator+=(const _Elem * lpStr)
	{
		Append(lpStr);
		return *this;
	}

	const CDuiString& operator=(const _Elem ch)
	{
		Empty();
		m_szBuffer[0] = ch;
		m_szBuffer[1] = '\0';
		m_nLength=1;
		return *this;
	}

	CDuiString operator+(const CDuiString& src) const
	{
		CDuiString sTemp = *this;
		sTemp.Append(src);
		return sTemp;
	}

	CDuiString operator+(const _Elem & ch) const
	{
		CDuiString sTemp = *this;
		sTemp.Append(&ch,1);
		return sTemp;
	}

	CDuiString operator+(const _Elem * lpStr) const
	{
		if ( lpStr )
		{
			CDuiString sTemp = *this;
			sTemp.Append(lpStr);
			return sTemp;
		}

		return *this;
	}

	const CDuiString& operator+=(const CDuiString& src)
	{      
		Append(src);
		return *this;
	}

	const CDuiString& operator+=(const _Elem ch)
	{      
		Append(&ch,1);
		return *this;
	}

	bool operator == (const _Elem * str) const { return (Compare(str) == 0); };
	bool operator != (const _Elem * str) const { return (Compare(str) != 0); };
	bool operator <= (const _Elem * str) const { return (Compare(str) <= 0); };
	bool operator <  (const _Elem * str) const { return (Compare(str) <  0); };
	bool operator >= (const _Elem * str) const { return (Compare(str) >= 0); };
	bool operator >  (const _Elem * str) const { return (Compare(str) >  0); };

	void SetAt(int nIndex, _Elem ch)
	{
		DUIASSERT(nIndex>=0 && nIndex<GetLength());
		_Traits::assign(m_pstr[nIndex],ch);
	}

	int Compare(const _Elem * lpsz) const 
	{ 
		return _Traits::compare(m_pstr,lpsz);
	}

	int CompareNoCase(const _Elem * lpsz) const 
	{ 
		return _Traits::compareNoCase(m_pstr,lpsz);
	}

	void MakeUpper() 
	{ 
		_Traits::strupr(m_pstr);
	}

	void MakeLower() 
	{ 
		_Traits::strlwr(m_pstr);
	}

	CDuiString Left(int iLength) const
	{
		if( iLength < 0 ) iLength = 0;
		if( iLength > GetLength() ) iLength = GetLength();
		return CDuiString(m_pstr, iLength);
	}

	CDuiString Mid(int iPos, int iLength=-1) const
	{
		if( iLength < 0 ) iLength = GetLength() - iPos;
		if( iPos + iLength > GetLength() ) iLength = GetLength() - iPos;
		if( iLength <= 0 ) return CDuiString();
		return CDuiString(m_pstr + iPos, iLength);
	}

	CDuiString Right(int iLength) const
	{
		int iPos = GetLength() - iLength;
		if( iPos < 0 ) {
			iPos = 0;
			iLength = GetLength();
		}
		return CDuiString(m_pstr + iPos, iLength);
	}

	int Find(_Elem ch, int iPos = 0) const
	{
		DUIASSERT(iPos>=0 && iPos<=GetLength());
		if( iPos != 0 && (iPos < 0 || iPos >= GetLength()) ) return -1;
		const _Elem * p= _Traits::find(m_pstr + iPos, GetLength()-iPos, ch);
		if( p == NULL ) return -1;
		return (int)(p - m_pstr);
	}

	int Find(const _Elem * pstrSub, int iPos = 0) const
	{
		DUIASSERT(!_Traits::IsBadStringPtr(pstrSub,-1));
		DUIASSERT(iPos>=0 && iPos<=GetLength());
		if( iPos != 0 && (iPos < 0 || iPos > GetLength()) ) return -1;
		const _Elem * p = _Traits::find(m_pstr + iPos, pstrSub);
		if( p == NULL ) return -1;
		return (int)(p - m_pstr);
	}

	int ReverseFind(_Elem ch) const
	{
		const _Elem * p = _Traits::findchr(m_pstr, ch);
		if( p == NULL ) return -1;
		return (int)(p - m_pstr);
	}

	int Replace(const _Elem * pstrFrom, const _Elem * pstrTo)
	{
		CDuiString sTemp;
		int nCount = 0;
		int iPos = Find(pstrFrom);
		if( iPos < 0 ) return 0;
		int cchFrom = (int) _Traits::length(pstrFrom);
		int cchTo = (int) _Traits::length(pstrTo);
		while( iPos >= 0 ) {
			sTemp = Left(iPos);
			sTemp += pstrTo;
			sTemp += Mid(iPos + cchFrom);
			Assign(sTemp);
			iPos = Find(pstrFrom, iPos + cchTo);
			nCount++;
		}
		return nCount;
	}

	int Format(const _Elem * pstrFormat, ...)
	{
		CDuiString sFormat = pstrFormat;
		// Do ordinary printf replacements
		// NOTE: Documented max-length of wvsprintf() is 1024
		_Elem szBuffer[1025] = { 0 };
		va_list argList;
		va_start(argList, pstrFormat);
		int iRet = _Traits::wvsprintf(szBuffer, sFormat, argList);
		va_end(argList);
		Assign(szBuffer);
		return iRet;
	}

	int SmallFormat(const _Elem * pstrFormat, ...)
	{
		CDuiString sFormat = pstrFormat;
		_Elem szBuffer[64] = { 0 };
		va_list argList;
		va_start(argList, pstrFormat);
		int iRet = _Traits::wvsprintf(szBuffer, sFormat, argList);
		va_end(argList);
		Assign(szBuffer);
		return iRet;
	}
protected:
	_Elem * m_pstr;
	int		m_nLength;
	_Elem m_szBuffer[MAX_LOCAL_STRING_LEN + 1];
};

	template<class _Elem,class _Traits>
	bool __CLRCALL_OR_CDECL operator==(const _Elem * _Left, const CDuiString<_Elem,_Traits> & _Right)
	{	// test for NTCS vs. string equality
		return (_Right.Compare(_Left)==0);
	}

	template<class _Elem,class _Traits>
	bool __CLRCALL_OR_CDECL operator!=(const _Elem * _Left, const CDuiString<_Elem,_Traits> & _Right)
	{	// test for NTCS vs. string equality
		return (_Right.Compare(_Left)!=0);
	}
	template<class _Elem,class _Traits>
	bool __CLRCALL_OR_CDECL operator<=(const _Elem * _Left, const CDuiString<_Elem,_Traits> & _Right)
	{	// test for NTCS vs. string equality
		return (_Right.Compare(_Left)<=0);
	}
	template<class _Elem,class _Traits>
	bool __CLRCALL_OR_CDECL operator<(const _Elem * _Left, const CDuiString<_Elem,_Traits> & _Right)
	{	// test for NTCS vs. string equality
		return (_Right.Compare(_Left)<0);
	}

	template<class _Elem,class _Traits>
	bool __CLRCALL_OR_CDECL operator>=(const _Elem * _Left, const CDuiString<_Elem,_Traits> & _Right)
	{	// test for NTCS vs. string equality
		return (_Right.Compare(_Left)>=0);
	}
	template<class _Elem,class _Traits>
	bool __CLRCALL_OR_CDECL operator>(const _Elem * _Left, const CDuiString<_Elem,_Traits> & _Right)
	{	// test for NTCS vs. string equality
		return (_Right.Compare(_Left)>0);
	}

#ifndef CP_ACP
#define CP_ACP 0
#endif//CP_ACP

class DUI_EXP CDuiStrCpCvt{
public:
	static CDuiString<char> CvtW2A(const CDuiString<wchar_t> & str,unsigned int cp=CP_ACP)
	{
		char szBuf[1024];
		int nRet=WideCharToMultiByte(cp,0,str,str.GetLength(),szBuf,1024,NULL,NULL);
		if(nRet>0) return CDuiString<char>(szBuf,nRet);
		if(GetLastError()==ERROR_INSUFFICIENT_BUFFER)
		{
			int nRet=WideCharToMultiByte(cp,0,str,str.GetLength(),NULL,0,NULL,NULL);
			if(nRet>0)
			{
				char *pBuf=new char[nRet];
				WideCharToMultiByte(cp,0,str,str.GetLength(),pBuf,nRet,NULL,NULL);
				CDuiString<char> strRet(pBuf,nRet);
				delete []pBuf;
				return strRet;
			}
		}
		return "";
	}

	static CDuiString<wchar_t> CvtA2W(const CDuiString<char> & str,unsigned int cp=CP_ACP)
	{
		wchar_t szBuf[1024];
		int nRet=MultiByteToWideChar(cp,0,str,str.GetLength(),szBuf,1024);
		if(nRet>0)
		{
			return CDuiString<wchar_t>(szBuf,nRet);
		}
		if(GetLastError()==ERROR_INSUFFICIENT_BUFFER)
		{
			int nRet=MultiByteToWideChar(cp,0,str,str.GetLength(),NULL,0);
			if(nRet>0)
			{
				wchar_t *pBuf=new wchar_t[nRet];
				MultiByteToWideChar(cp,0,str,str.GetLength(),pBuf,nRet);
				CDuiString<wchar_t> strRet(pBuf,nRet);
				delete []pBuf;
				return strRet;
			}
		}
		return L"";
	}

	static CDuiString<char> CvtA2A(const CDuiString<char> & str,unsigned int cp=CP_ACP)
	{
		if(cp==CP_ACP)
			return str;
		CDuiString<wchar_t> strw=CvtA2W(str,cp);
		return CvtW2A(strw);
	}

	static CDuiString<wchar_t> CvtW2W(const CDuiString<wchar_t> &str,unsigned int cp=CP_ACP)
	{
		return str;
	}

};

}//end of namespace DuiEngine

#ifndef NO_DUISTR

typedef DuiEngine::CDuiString<char> CStringA;
typedef DuiEngine::CDuiString<wchar_t> CStringW;

#ifdef UNICODE
typedef  CStringW CString;
#else
typedef  CStringA CString;
#endif // UNICODE

typedef CString CStringT;

#define CA2W DuiEngine::CDuiStrCpCvt::CvtA2W
#define CW2A DuiEngine::CDuiStrCpCvt::CvtW2A
#define CA2A DuiEngine::CDuiStrCpCvt::CvtA2A
#define CW2W DuiEngine::CDuiStrCpCvt::CvtW2W

#ifdef UNICODE
#define CA2T CA2W
#define CT2A CW2A
#define CW2T CW2W
#define CT2W CW2W
#else
#define CA2T CA2A
#define CT2A CA2A
#define CW2T CW2A
#define CT2W CA2W
#endif // UNICODE

#endif //NO_DUISTR