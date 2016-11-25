#include "_stdafx.h"
GProjMain* g_pMain;


void		GProjMain::ChangeZombState(int iNum, G_ZOMB_ST state) {

	g_pMain->m_CharNZomb[iNum]->setState(state);

	int iState = state;

	GCharacter* pChar0 = NULL;

	switch (iState) {
	case 	G_ZOMB_ST_WALK: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_IDL);
	}
							break;
	case 	G_ZOMB_ST_IDLE: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_WLK);
	}
							break;
	case 	G_ZOMB_ST_ATTACK: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_ATT);
	}
							  break;
	case 	G_ZOMB_ST_DEAD: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_DIE);
	}
							break;
	case 	G_ZOMB_ST_FOLLOW: {
		pChar0 = I_CharMgr.GetPtr(G_DEFINE_ANI_ZOMB_FLW);
	}
							break;
	}

	g_pMain->m_CharNZomb[iNum]->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);

}
void		GProjMain::ChangeZombState(int iNum, TCHAR* str) {

	//GCharacter* pChar0 = I_CharMgr.GetPtr(str);
	auto pChar0 = I_CharMgr.GetPtr(str);

	 m_CharNZomb[iNum]->Set(pChar0,
		pChar0->m_pBoneObject,
		pChar0->m_pBoneObject->m_Scene.iFirstFrame,
		pChar0->m_pBoneObject->m_Scene.iLastFrame);

	if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_DIE)) {
		 m_CharNZomb[iNum]->setState(G_ZOMB_ST_DEAD);
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_ATT)) {
		 m_CharNZomb[iNum]->setState(G_ZOMB_ST_ATTACK);
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_WLK)) {
		 m_CharNZomb[iNum]->setState(G_ZOMB_ST_WALK);
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_IDL)) {
		 m_CharNZomb[iNum]->setState(G_ZOMB_ST_IDLE);
	}
	else if (0 == _tcscmp(str, G_DEFINE_ANI_ZOMB_FLW)) {
		m_CharNZomb[iNum]->setState(G_ZOMB_ST_FOLLOW);
	}
	else {
		 m_CharNZomb[iNum]->setState(G_ZOMB_ST_IDLE);
	}
}

bool GProjMain::Load()
{
	if (!I_CharMgr.Load(GetDevice(), m_pImmediateContext, _T("CharZombie.gci")))
	{
		return false;
	}

	for (int i = 0;i < G_DEFINE_MAX_AI_ZOMBIE; i++) {
		GCharacter* pChar0 = I_CharMgr.GetPtr(L"ZOMBIE_WALK");

		shared_ptr<GNewZombieMgr> pObjA = make_shared<GNewZombieMgr>();
		pObjA->setState(G_ZOMB_ST_WALK);

		pObjA->Set(pChar0,
			pChar0->m_pBoneObject,
			pChar0->m_pBoneObject->m_Scene.iFirstFrame,
			pChar0->m_pBoneObject->m_Scene.iLastFrame);
		m_CharNZomb.push_back(pObjA);
	}

	return true;
}

bool GProjMain::Init()
{
	I_CharMgr.Init();
	 Load();

	m_fSecondPerFrmae = g_fSecPerFrame;
	//--------------------------------------------------------------------------------------
	// 카메라  행렬 
	//--------------------------------------------------------------------------------------	
	m_pMainCamera = make_shared<GCamera>();

	float fAspectRatio = g_pMain->m_iWindowWidth / (FLOAT)g_pMain->m_iWindowHeight;
	m_pMainCamera->SetProjMatrix(D3DX_PI / 4, fAspectRatio, 0.1f, 100000.0f);
	m_pMainCamera->SetViewMatrix(D3DXVECTOR3(0.0f, 200.0f, -10.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f));
	m_pMainCamera->SetWindow(g_pMain->m_iWindowWidth, g_pMain->m_iWindowHeight);

	SAFE_NEW(m_Box, GBoxShape);
	m_Box->Create(m_pd3dDevice, L"data/shader/box.hlsl", L"data/flagstone.bmp");
	D3DXMatrixIdentity(&m_matBoxWorld);
	D3DXMatrixScaling(&m_matBoxWorld, 10.0f, 10.0f, 10.0f);

	srand(time(NULL));

	for (int i = 0; i < G_DEFINE_MAX_AI_ZOMBIE; i++)
	{
		SAFE_NEW(m_Zomb[i], GNewZombie);
		m_Zomb[i]->m_ZombieWorld._41 = (rand() * 3) % 303;
		m_Zomb[i]->m_ZombieWorld._43 = (rand() * 3) % 303;

		m_Zomb[i]->vZombiePosition.x = m_Zomb[i]->m_ZombieWorld._41;
		m_Zomb[i]->vZombiePosition.y = 0.0f;
		m_Zomb[i]->vZombiePosition.z = m_Zomb[i]->m_ZombieWorld._43;
	}

	

	m_pCurrentSeq->Init();

	return true;
}
bool GProjMain::Frame()
{

	D3DXMATRIX Logic;
	if (I_Input.KeyCheck(DIK_UP) == KEY_HOLD)
	{
		g_pMain->m_matBoxWorld._43 += 30.0f * g_fSecPerFrame;
		Logic._43 = g_pMain->m_matBoxWorld._43;
	}

	if (I_Input.KeyCheck(DIK_DOWN) == KEY_HOLD)
	{
		g_pMain->m_matBoxWorld._43 -= 30.0f * g_fSecPerFrame;
		Logic._43 = g_pMain->m_matBoxWorld._43;
	}

	if (I_Input.KeyCheck(DIK_LEFT) == KEY_HOLD)
	{
		g_pMain->m_matBoxWorld._41 -= 30.0f * g_fSecPerFrame;
		Logic._41 = g_pMain->m_matBoxWorld._41;
	}

	if (I_Input.KeyCheck(DIK_RIGHT) == KEY_HOLD)
	{
		g_pMain->m_matBoxWorld._41 += 30.0f * g_fSecPerFrame;
		Logic._41 = g_pMain->m_matBoxWorld._41;
	}
	for (int i = 0; i < G_DEFINE_MAX_AI_ZOMBIE; i++)
	{
		m_Zomb[i]->vBoxPosition.x = g_pMain->m_matBoxWorld._41;
		m_Zomb[i]->vBoxPosition.y = g_pMain->m_matBoxWorld._42;
		m_Zomb[i]->vBoxPosition.z = g_pMain->m_matBoxWorld._43;
	}
	for (int iChar = 0; iChar < m_CharNZomb.size(); iChar++)
	{
		m_CharNZomb[iChar]->Frame();
	}
	
	m_pMainCamera->Frame();
	m_pCurrentSeq->Frame();

	for (int i = 0; i < G_DEFINE_MAX_AI_ZOMBIE; i++)
	{
		m_Zomb[i]->m_ZombieWorld = m_Rotation[i] * m_Trans[i];
	}
	return true;
}
bool GProjMain::Render()
{
	m_Box->SetMatrix(&m_matBoxWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	m_Box->Render(m_pImmediateContext);
	
	for (int i = 0; i < G_DEFINE_MAX_AI_ZOMBIE; i++)
	{
		m_CharNZomb[i]->SetMatrix(&m_Zomb[i]->m_ZombieWorld, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		m_CharNZomb[i]->Render(m_pImmediateContext);
	}

	m_pCurrentSeq->Render();
	return true;
}
bool GProjMain::Release()
{
	m_pCurrentSeq->Release();
	return true;
}
HRESULT GProjMain::CreateResource()
{
	HRESULT hr;
	if (m_pMainCamera != nullptr)
		m_pMainCamera->SetProjMatrix((float)D3DX_PI * 0.25f,
		m_SwapChainDesc.BufferDesc.Width / (FLOAT)m_SwapChainDesc.BufferDesc.Height, 1.0f, 10000.0f);
	return S_OK;
}
HRESULT GProjMain::DeleteResource()
{
	HRESULT hr;
	if (m_pImmediateContext) m_pImmediateContext->ClearState();
	return S_OK;
}

GProjMain::GProjMain(void)
{
	for (int i = 0; i < G_DEFINE_MAX_AI_ZOMBIE; i++)
	{
		D3DXMatrixIdentity(&m_Rotation[i]);
		D3DXMatrixIdentity(&m_Trans[i]);
	}
	m_GameSeq[G_AI_IDLE] = GAIIdle::CreateInstance();
	m_GameSeq[G_AI_MOVE] = GAIMove::CreateInstance();
	m_GameSeq[G_AI_FOLLOW] = GAIFollow::CreateInstance();
	m_GameSeq[G_AI_ATTACK] = GAIAttack::CreateInstance();
	m_GameSeq[G_AI_DIE] = GAIDie::CreateInstance();
	m_pCurrentSeq = m_GameSeq[G_AI_MOVE];
}

GProjMain::~GProjMain(void)
{

}

int GProjMain::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera != nullptr)
	{
		m_pMainCamera->WndProc(hWnd, msg, wParam, lParam);
	}
	return -1;

}
GCORE_RUN(FSM TEST);
