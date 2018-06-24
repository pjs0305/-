#include "stdafx.h"
#include "GameObject.h"
#include "Shader.h"

CGameObject::CGameObject()
{
	XMStoreFloat4x4(&m_xmf4x4World, XMMatrixIdentity());
}

CGameObject::~CGameObject()
{
	if (m_pMesh) m_pMesh->Release();
	if (m_pShader)
	{
		m_pShader->ReleaseShaderVariables();
		m_pShader->Release();
	}
}

void CGameObject::SetShader(CShader *pShader)
{
	if (m_pShader) m_pShader->Release();

	m_pShader = pShader;

	if (m_pShader) m_pShader->AddRef();
}

void CGameObject::SetMesh(CMesh *pMesh)
{
	if (m_pMesh) m_pMesh->Release();

	m_pMesh = pMesh;

	if (m_pMesh) m_pMesh->AddRef();
}

void CGameObject::ReleaseUploadBuffers()
{
	//���� ���۸� ���� ���ε� ���۸� �Ҹ��Ų��. 
	if (m_pMesh) m_pMesh->ReleaseUploadBuffers();
}

void CGameObject::Animate(float fTimeElapsed)
{
	if (m_fRotationSpeed != 0.0f) CGameObject::Rotate(m_xmf3RotationAxis, m_fRotationSpeed * fTimeElapsed);
	if (m_fMovingSpeed != 0.0f) CGameObject::Move(m_xmf3MovingDirection, m_fMovingSpeed * fTimeElapsed);

	if (m_pMesh)
	{
		m_pMesh->m_xmOOBB.Transform(m_xmOOBB, XMLoadFloat4x4(&m_xmf4x4World));
		XMStoreFloat4(&m_xmOOBB.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_xmOOBB.Orientation)));
	}
}

void CGameObject::OnPrepareRender()
{
}

void CGameObject::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera* pCamera)
{
	OnPrepareRender();

	//��ü�� ������ ���̴� ����(��� ����)�� �����Ѵ�. 
	UpdateShaderVariables(pd3dCommandList);

	if (m_pShader)
	{
		m_pShader->Render(pd3dCommandList, pCamera);
	}

	//���� ��ü�� �޽��� ����Ǿ� ������ �޽��� �������Ѵ�. 
	if (m_pMesh) m_pMesh->Render(pd3dCommandList);
}

void CGameObject::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CGameObject::ReleaseShaderVariables()
{
}

void CGameObject::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_xmf4x4World)));

	//��ü�� ���� ��ȯ ����� ��Ʈ ���(32-��Ʈ ��)�� ���Ͽ� ���̴� ����(��� ����)�� �����Ѵ�. 
	pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0);
}

void CGameObject::SetPosition(float x, float y, float z)
{
	m_xmf4x4World._41 = x;
	m_xmf4x4World._42 = y;
	m_xmf4x4World._43 = z;
}

void CGameObject::SetPosition(XMFLOAT3 xmf3Position)
{
	SetPosition(xmf3Position.x, xmf3Position.y, xmf3Position.z);
}

XMFLOAT3 CGameObject::GetPosition()
{
	return(XMFLOAT3(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43));
}

//���� ��ü�� ���� z-�� ���͸� ��ȯ�Ѵ�. 
XMFLOAT3 CGameObject::GetLook()
{
	return(Vector3::Normalize(XMFLOAT3(m_xmf4x4World._31, m_xmf4x4World._32, m_xmf4x4World._33)));
}

//���� ��ü�� ���� y-�� ���͸� ��ȯ�Ѵ�. 
XMFLOAT3 CGameObject::GetUp()
{
	return(Vector3::Normalize(XMFLOAT3(m_xmf4x4World._21, m_xmf4x4World._22, m_xmf4x4World._23)));
}

//���� ��ü�� ���� x-�� ���͸� ��ȯ�Ѵ�. 
XMFLOAT3 CGameObject::GetRight()
{
	return(Vector3::Normalize(XMFLOAT3(m_xmf4x4World._11, m_xmf4x4World._12, m_xmf4x4World._13)));
}

//���� ��ü�� ���� x-�� �������� �̵��Ѵ�. 
void CGameObject::MoveStrafe(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Right = GetRight();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Right, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

//���� ��ü�� ���� y-�� �������� �̵��Ѵ�. 
void CGameObject::MoveUp(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Up = GetUp();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Up, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

//���� ��ü�� ���� z-�� �������� �̵��Ѵ�. 
void CGameObject::MoveForward(float fDistance)
{
	XMFLOAT3 xmf3Position = GetPosition();
	XMFLOAT3 xmf3Look = GetLook();
	xmf3Position = Vector3::Add(xmf3Position, xmf3Look, fDistance);
	CGameObject::SetPosition(xmf3Position);
}

//���� ��ü�� �־��� ������ ȸ���Ѵ�.
void CGameObject::Rotate(float fPitch, float fYaw, float fRoll)
{
	XMMATRIX mtxRotate = XMMatrixRotationRollPitchYaw(XMConvertToRadians(fPitch), XMConvertToRadians(fYaw), XMConvertToRadians(fRoll));
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

void CGameObject::Rotate(XMFLOAT3& pxmf3Axis, float fAngle)
{
	XMMATRIX mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&pxmf3Axis), XMConvertToRadians(fAngle));
	m_xmf4x4World = Matrix4x4::Multiply(mtxRotate, m_xmf4x4World);
}

void CGameObject::Move(XMFLOAT3& vDirection, float fSpeed)
{
	SetPosition(m_xmf4x4World._41 + vDirection.x * fSpeed, m_xmf4x4World._42 + vDirection.y * fSpeed, m_xmf4x4World._43 + vDirection.z * fSpeed);
}

////////////////////////////////////////////////////////////////////////
XMFLOAT3 CRotatingObject::m_pxmf3SphereVectors[EXPLOSION_DEBRISES];
CMesh *CRotatingObject::m_pExplosionMesh = NULL;

CRotatingObject::CRotatingObject()
{
}

CRotatingObject::~CRotatingObject()
{
}

inline float RandF(float fMin, float fMax)
{
	return(fMin + ((float)rand() / (float)RAND_MAX) * (fMax - fMin));
}

XMVECTOR RandomUnitVectorOnSphere()
{
	XMVECTOR xmvOne = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
	XMVECTOR xmvZero = XMVectorZero();

	while (true)
	{
		XMVECTOR v = XMVectorSet(RandF(-1.0f, 1.0f), RandF(-1.0f, 1.0f), RandF(-1.0f, 1.0f), 0.0f);
		if (!XMVector3Greater(XMVector3LengthSq(v), xmvOne)) return(XMVector3Normalize(v));
	}
}

void CRotatingObject::PrepareExplosion(CCubeMeshDiffused *pMesh)
{
	for (int i = 0; i < EXPLOSION_DEBRISES; i++) XMStoreFloat3(&m_pxmf3SphereVectors[i], ::RandomUnitVectorOnSphere());
	m_pExplosionMesh = pMesh;
}

void CRotatingObject::Animate(float fTimeElapsed)
{
	if (m_bBlowingUp)
	{
		m_fElapsedTimes += fTimeElapsed;
		if (m_fElapsedTimes <= m_fDuration)
		{
			XMFLOAT3 xmf3Position = GetPosition();
			for (int i = 0; i < EXPLOSION_DEBRISES; i++)
			{
				m_pxmf4x4Transforms[i] = Matrix4x4::Identity();
				m_pxmf4x4Transforms[i]._41 = xmf3Position.x + m_pxmf3SphereVectors[i].x * m_fExplosionSpeed * m_fElapsedTimes;
				m_pxmf4x4Transforms[i]._42 = xmf3Position.y + m_pxmf3SphereVectors[i].y * m_fExplosionSpeed * m_fElapsedTimes;
				m_pxmf4x4Transforms[i]._43 = xmf3Position.z + m_pxmf3SphereVectors[i].z * m_fExplosionSpeed * m_fElapsedTimes;
				m_pxmf4x4Transforms[i] = Matrix4x4::Multiply(Matrix4x4::RotationAxis(m_pxmf3SphereVectors[i], m_fExplosionRotation * m_fElapsedTimes), m_pxmf4x4Transforms[i]);

			}
		}
		else
			m_Delete = TRUE;
	}
	else
	{
		CGameObject::Animate(fTimeElapsed);
	}
}

void CRotatingObject::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera* pCamera)
{
	if (m_bBlowingUp)
	{
		for (int i = 0; i < EXPLOSION_DEBRISES; i++)
		{
			XMFLOAT4X4 xmf4x4World;
			XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(&m_pxmf4x4Transforms[i])));

			//��ü�� ���� ��ȯ ����� ��Ʈ ���(32-��Ʈ ��)�� ���Ͽ� ���̴� ����(��� ����)�� �����Ѵ�. 
			pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0);

			if (m_pExplosionMesh)
			{
				m_pExplosionMesh->Render(pd3dCommandList);
			}
		}
	}
	else
	{
		CGameObject::Render(pd3dCommandList, pCamera);
	}
}

///////////////////////////////////////////////////////////

void CBulletObject::Animate(float fTimeElapsed)
{
	if (m_fElapsedTimes > m_fDuration)
	{
		m_Delete = TRUE;
	}
	else
	{
		m_fElapsedTimes += fTimeElapsed;

		CGameObject::Animate(fTimeElapsed);
	}
}

///////////////////////////////////////////////////////////

CWallObject::CWallObject()
{
}

CWallObject::~CWallObject()
{
}