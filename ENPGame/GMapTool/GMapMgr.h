#pragma once

#include "GMapGroup.h"
#include "GInput.h"

class GMapGroup;

class GMapMgr
{
public:
	GObjData* m_pObjSelected;

	vector<shared_ptr<GMapGroup>>	m_vecMapGroup;

	//vector<GGbsObj*>	m_vecObj;

	//GTileMap		m_HeightMap;





public:


	//--------------------------------------------------------------------------------------
	// ��
	//--------------------------------------------------------------------------------------
	//GCreateMapDlg GCreateDlg;
	//GSaveMapDlg GSaveDlg;




	bool			m_bDebugRender;




	bool			Init();
	bool			Frame(GInput* pInput = NULL,GCamera* pCamera = NULL);
	bool			Render(GCamera* pCamera);
	bool			Release();
	HRESULT			CreateResource();
	HRESULT			DeleteResource();



	GMapMgr();
	virtual ~GMapMgr();
};

