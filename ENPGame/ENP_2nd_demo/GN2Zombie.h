#pragma once
class GN2Zombie : public GZombie
{
public:
	//D3DXMATRIX m_matZombie;

	//virtual bool		Init();
	//virtual bool		Set(GCharacter* pChar, GBoneObj* pBone,
	//	float fStart, float fEnd);
	//virtual void		SetBoneMatrices(vector<D3DXMATRIX>* pList);
	virtual bool		Frame();
	//virtual bool		Render(ID3D11DeviceContext*    pContext);
	//virtual void		SetActionFrame(int iStart, int iEnd, int iCharacterMatrixIndex = -1, int iModelMatrixIndex = -1);
	//virtual HRESULT		CreateConstantBuffer();

	GN2Zombie();
	virtual ~GN2Zombie();
};

