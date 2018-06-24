#pragma once

#include "Mesh.h"
#include "Camera.h"

class CShader;

class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();
private:
	int m_nReferences = 0;
public:
	void AddRef() { m_nReferences++; }
	void Release() { if (--m_nReferences <= 0) delete this; }

	XMFLOAT4X4 m_xmf4x4World;
	CMesh *m_pMesh = NULL;
	CShader *m_pShader = NULL;

	BoundingOrientedBox	m_xmOOBB;
	CGameObject* m_pObjectCollided = NULL;
public:
	void ReleaseUploadBuffers();
	virtual void SetMesh(CMesh *pMesh);
	virtual void SetShader(CShader *pShader);
	virtual void Animate(float fTimeElapsed);
	virtual void OnPrepareRender();
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera* pCamera);
public:
	void Rotate(XMFLOAT3& pxmf3Axis, float fAngle);
	void Move(XMFLOAT3& vDirection, float fSpeed);
public:
	//상수 버퍼를 생성한다. 
	virtual void CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList);

	//상수 버퍼의 내용을 갱신한다. 
	virtual void UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList);
	virtual void ReleaseShaderVariables();

	//게임 객체의 월드 변환 행렬에서 위치 벡터와 방향(x-축, y-축, z-축) 벡터를 반환한다. 
	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();

	//게임 객체의 위치를 설정한다.
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3 xmf3Position);

	//게임 객체를 로컬 x-축, y-축, z-축 방향으로 이동한다.
	void MoveStrafe(float fDistance = 1.0f);
	void MoveUp(float fDistance = 1.0f);
	void MoveForward(float fDistance = 1.0f);

	//게임 객체를 회전(x-축, y-축, z-축)한다. 
	void Rotate(float fPitch = 10.0f, float fYaw = 10.0f, float fRoll = 10.0f);

	XMFLOAT3 m_xmf3RotationAxis;
	float m_fRotationSpeed;

	XMFLOAT3 m_xmf3MovingDirection;
	float m_fMovingSpeed;

	bool m_Delete = FALSE;
public:
	void SetRotationSpeed(float fRotationSpeed) { m_fRotationSpeed = fRotationSpeed; }
	void SetRotationAxis(XMFLOAT3 xmf3RotationAxis) { m_xmf3RotationAxis = Vector3::Normalize(xmf3RotationAxis); }

	void SetMovingDirection(XMFLOAT3& xmf3MovingDirection) { m_xmf3MovingDirection = Vector3::Normalize(xmf3MovingDirection); }
	void SetMovingSpeed(float fSpeed) { m_fMovingSpeed = fSpeed; }
};



class CRotatingObject : public CGameObject
{
public:
	CRotatingObject();
	virtual ~CRotatingObject();

	virtual void Animate(float fTimeElapsed);
	virtual void Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera* pCamera);

	bool m_bBlowingUp = FALSE;

	XMFLOAT4X4 m_pxmf4x4Transforms[EXPLOSION_DEBRISES];

	float m_fElapsedTimes = 0.0f;
	float m_fDuration = 2.0f;
	float m_fExplosionSpeed = 50.0f;
	float m_fExplosionRotation = 720.0f;

	static CMesh *m_pExplosionMesh;

	static void PrepareExplosion(CCubeMeshDiffused *pMesh);
	static XMFLOAT3 m_pxmf3SphereVectors[EXPLOSION_DEBRISES];
};


class CBulletObject : public CGameObject
{
public:
	CBulletObject() {};
	virtual ~CBulletObject() {};

	virtual void Animate(float fTimeElapsed);

	float m_fElapsedTimes = 0.0f;
	float m_fDuration = 1.0f;
};

class CWallObject : public CGameObject
{
public:
	CWallObject();
	virtual ~CWallObject();
public:
	XMFLOAT4 m_pxmf4WallPlanes[6];
};