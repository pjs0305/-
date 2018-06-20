#pragma once

#include "Mesh.h"
#include "Camera.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CGameObject
{
public:
	CGameObject(CMesh *pMesh);
	CGameObject();
	virtual ~CGameObject();

public:
	bool							m_bActive = true;
	
	CMesh							*m_pMesh = NULL;
    XMFLOAT4X4						m_xmf4x4World;    

	BoundingOrientedBox				m_xmOOBB;

	CGameObject*					m_pObjectCollided = NULL;

	DWORD							m_dwColor;

	XMFLOAT3						m_xmf3MovingDirection;
	float							m_fMovingSpeed;
	float							m_fMovingRange;

	XMFLOAT3						m_xmf3RotationAxis;
	float							m_fRotationSpeed;

	bool							m_Delete = false;
public:
	void SetMesh(CMesh *pMesh) { m_pMesh = pMesh; if (pMesh) pMesh->AddRef(); }
	void SetColor(DWORD dwColor) { m_dwColor = dwColor; }
	void SetPosition(float x, float y, float z);
	void SetPosition(XMFLOAT3& xmf3Position);

	void SetMovingDirection(XMFLOAT3& xmf3MovingDirection) { m_xmf3MovingDirection = Vector3::Normalize(xmf3MovingDirection); }
	void SetMovingSpeed(float fSpeed) { m_fMovingSpeed = fSpeed; }
	void SetMovingRange(float fRange) { m_fMovingRange = fRange; }

	void SetRotationAxis(XMFLOAT3& xmf3RotationAxis) { m_xmf3RotationAxis = Vector3::Normalize(xmf3RotationAxis); }
	void SetRotationSpeed(float fSpeed) { m_fRotationSpeed = fSpeed; }

	void MoveStrafe(float fDistance=1.0f);
	void MoveUp(float fDistance=1.0f);
	void MoveForward(float fDistance=1.0f);
	void Move(XMFLOAT3& vDirection, float fSpeed);

	void Rotate(float fPitch=10.0f, float fYaw=10.0f, float fRoll=10.0f);
	void Rotate(XMFLOAT3& xmf3Axis, float fAngle);

	XMFLOAT3 GetPosition();
	XMFLOAT3 GetLook();
	XMFLOAT3 GetUp();
	XMFLOAT3 GetRight();

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera *pCamera);
};

class CEnemyObject : public CGameObject
{
public:
	CEnemyObject();
	virtual ~CEnemyObject();

	bool						m_bBlowingUp = false;

	XMFLOAT4X4					m_pxmf4x4Transforms[EXPLOSION_DEBRISES];

	float						m_fElapsedTimes = 0.0f;
	float						m_fDuration = 3.0f;
	float						m_fExplosionSpeed = 10.0f;
	float						m_fExplosionRotation = 720.0f;

	CGameObject					*m_pTarget = NULL;
	float						m_MoveTime = 0.0f;
	bool						m_DropItem = false;

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera *pCamera);
	void SetDrop() { m_DropItem = true; }

	void SetTarget(CGameObject* Target) { m_pTarget = Target; }
public:
	static CMesh				*m_pExplosionMesh;
	static XMFLOAT3				m_pxmf3SphereVectors[EXPLOSION_DEBRISES];

	static void PrepareExplosion();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CBulletObject : public CGameObject
{
public:
	CBulletObject();
	virtual ~CBulletObject();

	float							m_ElapsedTime = 0.0f;
	float							m_LifeTime = 1.0f;

	static		CMesh				*m_pBulletMesh;

	virtual void Animate(float fElapsedTime);
	void SetBulletLifeTime(float T) { m_LifeTime = T; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CBossObject : public CEnemyObject
{
public:
	CBossObject();
	virtual ~CBossObject();

	CBulletMesh					*pObjectBulletMesh = NULL;
	std::vector<CBulletObject*>	m_vbObjects;

	float						m_ShotTime = 0.0f;
	bool						m_ShotEnable = true;

	static		CMesh			*m_pBossMesh;

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera *pCamera);
	void CreateEnemyBullet();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CWallsObject : public CGameObject
{
public:
	CWallsObject();
	virtual ~CWallsObject();

public:
	XMFLOAT4					m_pxmf4WallPlanes[6];
};

