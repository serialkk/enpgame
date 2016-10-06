#pragma once
#include "GBasisLib_0.h"
#include "GModelViewCamera.h"
#include "GObject.h"

//속성:디버깅:명령->C:\Program Files\Autodesk\3ds Max 2016\3dsmax.exe
class Sample : public GBasisLib_0
{
public:
	GGbsObj		m_tbsobj;
	GObject     m_tObj;
	shared_ptr<GModelViewCamera >		m_pMainCamera;
	D3DXMATRIX m_matWorld;
public:	
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	int			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	//--------------------------------------------------------------------------------------
	// 변경된 클라이언트 영역를 재설정을 위한 소멸 및 생성
	//--------------------------------------------------------------------------------------
	HRESULT		CreateResource();
	HRESULT		DeleteResource();	
	void		AddObject();
public:
	Sample(void);
	virtual ~Sample(void);
};
