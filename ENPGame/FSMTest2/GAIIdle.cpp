#include "_stdafx.h"

GAIIdle * GAIIdle::pInstance_ = 0;

bool GAIIdle::Init(int iMyIndex)
{

	pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE");
	m_pZombie = make_shared<GZombie>();
	m_pZombie->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);
	//GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_IDLE");

	//g_pMain->m_CharNZomb[0]->Set(pChar0,
	//	pChar0->m_pBoneObject,
	//	pChar0->m_pBoneObject->m_Scene.iFirstFrame,
	//	pChar0->m_pBoneObject->m_Scene.iLastFrame);
	return true;
}
bool GAIIdle::Frame(int iMyIndex)
{
	m_pZombie->Frame();

	TimeCount += g_fSecPerFrame;
	if (TimeCount > 7.0f)
		g_pMain->m_Zomb[iMyIndex]->m_pCurrentSeq = g_pMain->m_Zomb[iMyIndex]->m_GameSeq[G_AI_MOVE];
	return true;
}
bool GAIIdle::Render()
{

	return true;
}
bool GAIIdle::Release()
{
	return true;
}
HRESULT GAIIdle::CreateResource()
{
	HRESULT hr;

	return S_OK;
}
HRESULT GAIIdle::DeleteResource()
{
	HRESULT hr = S_OK;
	if (g_pImmediateContext) g_pImmediateContext->ClearState();
	return S_OK;
}
GAIIdle::GAIIdle()
{
	pInstance_ = 0;
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&Trans);
	D3DXMatrixIdentity(&Rotation);
}


GAIIdle::~GAIIdle()
{
}
int GAIIdle::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;
}

