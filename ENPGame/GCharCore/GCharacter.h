#pragma once
#include "GObject.h"

class GCharacter : public GObject
{
public:
	bool			m_bAttack;//공격 모션의 마지막에 true 된다.
	D3DXVECTOR3		m_vMin;
	D3DXVECTOR3		m_vMax;
	bool			m_iAniLoop;
	T_STR			m_szName;
	GBoneObj*		m_pBoneObject;
	int				m_iStartFrame;
	int				m_iLastFrame;
	int				m_iCurrentFrame;	
	float			m_fFrame;
	float			m_fLerpTime;
	D3DXMATRIX		m_pMatrix[255];
	int				m_iMatrixIndex;
	ID3D11Buffer*                       m_pBoneBuffer;
	ID3D11ShaderResourceView*           m_pBoneBufferRV;
public:	
	bool		Init();
	bool		Frame();
	bool		Render(ID3D11DeviceContext*    pContext);
	bool		Release();
	bool		Add(	ID3D11Device* pd3dDevice,
						ID3D11DeviceContext*    pImmediateContext,
						const TCHAR* strSkinFileName, 
						const TCHAR* strSkinShaderName,	
						int		iMatrixIndex	= -1,
						int		iModelMatrixIndex = -1,
						int		iAniLoop = 1,
						D3DXVECTOR3 vMin = D3DXVECTOR3(-1.5f, -1.5f, -1.5f),
						D3DXVECTOR3 vMax = D3DXVECTOR3(1.5f, 1.5f, 1.5f));
	// 모델 리스트들에 매트릭스 인덱스 세싱
	void		SeGModelMaterixID(int iMatrixIndex);
	void		SetMatrix( D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj );
	void		SetActionFrame( int iStart, int iEnd, 
								int iCharacterMatrixIndex = -1,
								int iModelMatrixIndex = -1);
public:
	GCharacter(void);
	virtual ~GCharacter(void);
};


