#include "stdafx.h"
#include "Scene.h"


CScene::CScene()
{
	//m_pd3dPipelineState = NULL;
}


CScene::~CScene()
{
}

void CScene::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	//그래픽 루트 시그너쳐를 생성한다. 
	m_pd3dGraphicsRootSignature = CreateGraphicsRootSignature(pd3dDevice);

	m_nShaders = 1;
	m_pShaders = new CObjectsShader[m_nShaders];
	m_pShaders[0].CreateShader(pd3dDevice, m_pd3dGraphicsRootSignature);
	m_pShaders[0].BuildObjects(pd3dDevice, pd3dCommandList);
}

void CScene::ReleaseObjects()
{
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();

	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].ReleaseShaderVariables();
		m_pShaders[i].ReleaseObjects();
	}
	if (m_pShaders) delete[] m_pShaders;
}

bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	return(false);
}

bool CScene::ProcessInput(UCHAR *pKeysBuffer)
{
	return(false);
}

void CScene::AnimateObjects(float fTimeElapsed)
{
	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].AnimateObjects(fTimeElapsed);
	}

	CheckCollisions();
}

void CScene::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	pCamera->SetViewportsAndScissorRects(pd3dCommandList);

	//그래픽 루트 시그너쳐를 파이프라인에 연결(설정)한다. 
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	if (pCamera) pCamera->UpdateShaderVariables(pd3dCommandList);

	//씬을 렌더링하는 것은 씬을 구성하는 게임 객체(셰이더를 포함하는 객체)들을 렌더링하는 것이다. 
	for (int i = 0; i < m_nShaders; i++)
	{
		m_pShaders[i].Render(pd3dCommandList, pCamera);
	}
}

void CScene::ReleaseUploadBuffers()
{
	for (int i = 0; i < m_nShaders; i++) m_pShaders[i].ReleaseUploadBuffers();
}

ID3D12RootSignature *CScene::GetGraphicsRootSignature()
{
	return(m_pd3dGraphicsRootSignature);
}

ID3D12RootSignature *CScene::CreateGraphicsRootSignature(ID3D12Device *pd3dDevice)	
{
	//매개변수가 없는 루트 시그너쳐를 생성한다. 
	ID3D12RootSignature *pd3dGraphicsRootSignature = NULL;

	D3D12_ROOT_PARAMETER pd3dRootParameters[2];
	pd3dRootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[0].Constants.Num32BitValues = 16;
	pd3dRootParameters[0].Constants.ShaderRegister = 0;
	pd3dRootParameters[0].Constants.RegisterSpace = 0;
	pd3dRootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
	pd3dRootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
	pd3dRootParameters[1].Constants.Num32BitValues = 32;
	pd3dRootParameters[1].Constants.ShaderRegister = 1;
	pd3dRootParameters[1].Constants.RegisterSpace = 0;
	pd3dRootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;

	D3D12_ROOT_SIGNATURE_FLAGS d3dRootSignatureFlags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS |
		D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = _countof(pd3dRootParameters);
	d3dRootSignatureDesc.pParameters = pd3dRootParameters;
	d3dRootSignatureDesc.NumStaticSamplers = 0;
	d3dRootSignatureDesc.pStaticSamplers = NULL;
	d3dRootSignatureDesc.Flags = d3dRootSignatureFlags;

	ID3DBlob *pd3dSignatureBlob = NULL;
	ID3DBlob *pd3dErrorBlob = NULL;
	::D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1,
		&pd3dSignatureBlob, &pd3dErrorBlob);
	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(),
		pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void
			**)&pd3dGraphicsRootSignature);
	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();

	return(pd3dGraphicsRootSignature);
}

// 충돌 체크
void CScene::CheckCollisions()
{
	CheckObjectByWallCollisions();
	CheckObjectByObjectCollisions();
}

void CScene::CheckObjectByWallCollisions() // 객체의 벽 충돌
{
	for (const auto& Object : m_pShaders->m_vEnemyObject) // 적 객체의 벽 충돌
	{
		ContainmentType containType = m_pShaders->m_pWallObjects->m_xmOOBB.Contains(Object->m_xmOOBB);

		switch (containType)
		{
		case DISJOINT:
		case INTERSECTS:
		{
			int nPlaneIndex = -1;

			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = Object->m_xmOOBB.Intersects(XMLoadFloat4(&m_pShaders->m_pWallObjects->m_pxmf4WallPlanes[j]));

				if (intersectType == INTERSECTING || intersectType == BACK)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pShaders->m_pWallObjects->m_pxmf4WallPlanes[nPlaneIndex].x,
					m_pShaders->m_pWallObjects->m_pxmf4WallPlanes[nPlaneIndex].y,
					m_pShaders->m_pWallObjects->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);

				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&Object->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&Object->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		}
	}


	for (const auto& Bullet : m_pShaders->m_vPlayerBullet) // 적 객체의 벽 충돌
	{
		ContainmentType containType = m_pShaders->m_pWallObjects->m_xmOOBB.Contains(Bullet->m_xmOOBB);

		switch (containType)
		{
		case DISJOINT:
		case INTERSECTS:
		{
			int nPlaneIndex = -1;

			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = Bullet->m_xmOOBB.Intersects(XMLoadFloat4(&m_pShaders->m_pWallObjects->m_pxmf4WallPlanes[j]));

				if (intersectType == INTERSECTING || intersectType == BACK)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pShaders->m_pWallObjects->m_pxmf4WallPlanes[nPlaneIndex].x,
					m_pShaders->m_pWallObjects->m_pxmf4WallPlanes[nPlaneIndex].y,
					m_pShaders->m_pWallObjects->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);

				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&Bullet->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&Bullet->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		}
	}

	ContainmentType containType = m_pShaders->m_pWallObjects->m_xmOOBB.Contains(m_pPlayer->m_xmOOBB);
	switch (containType)
	{
	case DISJOINT:
	case INTERSECTS:
	{
		int nPlaneIndex = -1;
		for (int j = 0; j < 6; j++)
		{
			PlaneIntersectionType intersectType = m_pPlayer->m_xmOOBB.Intersects(XMLoadFloat4(&m_pShaders->m_pWallObjects->m_pxmf4WallPlanes[j]));

			if (intersectType == INTERSECTING || intersectType == BACK)
			{
				nPlaneIndex = j;
				break;
			}
		}
		if (nPlaneIndex != -1)
		{
			XMFLOAT3 xmvNormal = XMFLOAT3(
				m_pShaders->m_pWallObjects->m_pxmf4WallPlanes[nPlaneIndex].x,
				m_pShaders->m_pWallObjects->m_pxmf4WallPlanes[nPlaneIndex].y,
				m_pShaders->m_pWallObjects->m_pxmf4WallPlanes[nPlaneIndex].z);

			XMFLOAT3 xmf3Shift = XMFLOAT3(0, 0, 0);
			xmf3Shift = Vector3::Add(xmf3Shift, xmvNormal, 2.f);
			m_pPlayer->Move(xmf3Shift, true);
		}
		break;
	}
	}
}

void CScene::CheckObjectByObjectCollisions() // 오브젝트끼리의 충돌
{
	for (const auto& Object : m_pShaders->m_vEnemyObject) Object->m_pObjectCollided = NULL;

	for (UINT i = 0; i < m_pShaders->m_vEnemyObject.size(); i++)
	{
		for (UINT j = (i + 1); j < m_pShaders->m_vEnemyObject.size(); j++)
		{
			if (m_pShaders->m_vEnemyObject[i]->m_xmOOBB.Intersects(m_pShaders->m_vEnemyObject[j]->m_xmOOBB) )
			{
				m_pShaders->m_vEnemyObject[i]->m_pObjectCollided = m_pShaders->m_vEnemyObject[j];
				m_pShaders->m_vEnemyObject[j]->m_pObjectCollided = m_pShaders->m_vEnemyObject[i];
			}
		}
	}

	for (const auto& Object : m_pShaders->m_vEnemyObject)
	{
		if (Object->m_pObjectCollided)
		{
			XMFLOAT3 xmf3MovingDirection = Object->m_xmf3MovingDirection;
			float fMovingSpeed = Object->m_fMovingSpeed;
			Object->m_xmf3MovingDirection = Object->m_pObjectCollided->m_xmf3MovingDirection;
			Object->m_fMovingSpeed = Object->m_pObjectCollided->m_fMovingSpeed;
			Object->m_pObjectCollided->m_xmf3MovingDirection = xmf3MovingDirection;
			Object->m_pObjectCollided->m_fMovingSpeed = fMovingSpeed;
			Object->m_pObjectCollided->m_pObjectCollided = NULL;
			Object->m_pObjectCollided = NULL;
		}
	}

	for (const auto& Bullet : m_pShaders->m_vPlayerBullet)
	{
		for (const auto& Object : m_pShaders->m_vEnemyObject)
		{
			if (Object->m_xmOOBB.Intersects(Bullet->m_xmOOBB))
			{
				Object->m_bBlowingUp = TRUE;
				Bullet->m_Delete = TRUE;
			}
		}
	}
}