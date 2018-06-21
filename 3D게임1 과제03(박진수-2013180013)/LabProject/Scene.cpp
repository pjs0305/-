#include "stdafx.h"
#include "Scene.h"

CScene::CScene()
{
	m_pd3dPipelineState = NULL;
	m_pd3dGraphicsRootSignature = NULL;
}

CScene::~CScene()
{
}

bool CScene::OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	//::GetCursorPos(&m_ptCursorPos);
	//::GetWindowRect(hWnd, &m_wndRect);
	//Picking();

	return false;
}

bool CScene::OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam)
{
	//switch (nMessageID)
	//{
	//	case WM_KEYDOWN:
	//	{
	//		switch (wParam)
	//		{
	//		case 'Z':
	//			if (m_pPlayer->m_ItemEnable && m_pPlayer->m_NumItem > 0)
	//			{
	//				UseItem();
	//				m_pPlayer->m_ItemEnable = false;
	//			}
	//			break;
	//		}
	//	case WM_KEYUP:
	//	{			
	//		if (!m_pPlayer->m_ItemEnable)
	//		m_pPlayer->m_ItemEnable = true;
	//		break;
	//	}
	//	default:
	//		break;
	//	}
	//}

	return false;
}

void CScene::BuildObjects(ID3D12Device *pd3dDevice)
{
//// 벽 생성
//float fHalfWidth = 45.0f, fHalfHeight = 45.0f, fHalfDepth = 500.0f;
//pWallCubeMesh = new CWallMesh(fHalfWidth * 2.0f, fHalfHeight * 2.0f, fHalfDepth * 2.0f, 10);
//pWallCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

//m_pWallsObject = new CWallsObject();
//m_pWallsObject->SetPosition(0.0f, 0.0f, 0.0f);
//m_pWallsObject->SetMesh(pWallCubeMesh);
//m_pWallsObject->SetColor(RGB(0, 0, 0));
//m_pWallsObject->m_pxmf4WallPlanes[0] = XMFLOAT4(+1.0f, 0.0f, 0.0f, fHalfWidth);
//m_pWallsObject->m_pxmf4WallPlanes[1] = XMFLOAT4(-1.0f, 0.0f, 0.0f, fHalfWidth);
//m_pWallsObject->m_pxmf4WallPlanes[2] = XMFLOAT4(0.0f, +1.0f, 0.0f, fHalfHeight);
//m_pWallsObject->m_pxmf4WallPlanes[3] = XMFLOAT4(0.0f, -1.0f, 0.0f, fHalfHeight);
//m_pWallsObject->m_pxmf4WallPlanes[4] = XMFLOAT4(0.0f, 0.0f, +1.0f, fHalfDepth);
//m_pWallsObject->m_pxmf4WallPlanes[5] = XMFLOAT4(0.0f, 0.0f, -1.0f, fHalfDepth);

//CEnemyObject::PrepareExplosion();
//m_vObjects.reserve(200);

//// 적 큐브 메쉬
//pObjectCubeMesh = new CCubeMesh(3.0f, 3.0f, 3.0f);
//pObjectCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(2.0f, 2.0f, 2.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

//// 보스 생성
//CCubeMesh *pBossCubeMesh = new CCubeMesh(15.0f, 15.0f, 15.0f);
//pBossCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(7.5f, 7.5f, 7.5f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

//m_Boss = new CBossObject();
//m_Boss->SetMesh(pBossCubeMesh);

//m_Boss->SetPosition(0.0f, 0.0f, 480.0f);
//m_Boss->SetRotationAxis(XMFLOAT3(1.0f, 1.0f, 1.0f));
//m_Boss->SetRotationSpeed(500.0f);
//m_Boss->SetTarget(m_pPlayer);

	////////////////////////////////////////////////////////////////////// New

	//루트 시그너쳐를 생성한다. 
	D3D12_ROOT_SIGNATURE_DESC d3dRootSignatureDesc;
	::ZeroMemory(&d3dRootSignatureDesc, sizeof(D3D12_ROOT_SIGNATURE_DESC));
	d3dRootSignatureDesc.NumParameters = 0;
	d3dRootSignatureDesc.pParameters = NULL;
	d3dRootSignatureDesc.NumStaticSamplers = 0;
	d3dRootSignatureDesc.pStaticSamplers = NULL;
	d3dRootSignatureDesc.Flags =
		D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	ID3DBlob *pd3dSignatureBlob = NULL;
	ID3DBlob *pd3dErrorBlob = NULL;
	::D3D12SerializeRootSignature(&d3dRootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1,
		&pd3dSignatureBlob, &pd3dErrorBlob);
	pd3dDevice->CreateRootSignature(0, pd3dSignatureBlob->GetBufferPointer(),
		pd3dSignatureBlob->GetBufferSize(), __uuidof(ID3D12RootSignature), (void
			**)&m_pd3dGraphicsRootSignature);
	if (pd3dSignatureBlob) pd3dSignatureBlob->Release();
	if (pd3dErrorBlob) pd3dErrorBlob->Release();

	//정점 셰이더와 픽셀 셰이더를 생성한다. 
	ID3DBlob *pd3dVertexShaderBlob = NULL;
	ID3DBlob *pd3dPixelShaderBlob = NULL;
	UINT nCompileFlags = 0;
#if defined(_DEBUG)
	nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
	D3DCompileFromFile(L"Shader.hlsl", NULL, NULL, "VSMain", "vs_5_1", nCompileFlags, 0,
		&pd3dVertexShaderBlob, NULL);
	D3DCompileFromFile(L"Shader.hlsl", NULL, NULL, "PSMain", "ps_5_1", nCompileFlags, 0,
		&pd3dPixelShaderBlob, NULL);

	//래스터라이저 상태를 설정한다. 
	D3D12_RASTERIZER_DESC d3dRasterizerDesc;
	::ZeroMemory(&d3dRasterizerDesc, sizeof(D3D12_RASTERIZER_DESC));
	d3dRasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
	d3dRasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
	d3dRasterizerDesc.FrontCounterClockwise = FALSE;
	d3dRasterizerDesc.DepthBias = 0;
	d3dRasterizerDesc.DepthBiasClamp = 0.0f;
	d3dRasterizerDesc.SlopeScaledDepthBias = 0.0f;
	d3dRasterizerDesc.DepthClipEnable = TRUE;
	d3dRasterizerDesc.MultisampleEnable = FALSE;
	d3dRasterizerDesc.AntialiasedLineEnable = FALSE;
	d3dRasterizerDesc.ForcedSampleCount = 0;
	d3dRasterizerDesc.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;

	//블렌드 상태를 설정한다. 
	D3D12_BLEND_DESC d3dBlendDesc;
	::ZeroMemory(&d3dBlendDesc, sizeof(D3D12_BLEND_DESC));
	d3dBlendDesc.AlphaToCoverageEnable = FALSE;
	d3dBlendDesc.IndependentBlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].BlendEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].LogicOpEnable = FALSE;
	d3dBlendDesc.RenderTarget[0].SrcBlend = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlend = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOp = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].SrcBlendAlpha = D3D12_BLEND_ONE;
	d3dBlendDesc.RenderTarget[0].DestBlendAlpha = D3D12_BLEND_ZERO;
	d3dBlendDesc.RenderTarget[0].BlendOpAlpha = D3D12_BLEND_OP_ADD;
	d3dBlendDesc.RenderTarget[0].LogicOp = D3D12_LOGIC_OP_NOOP;
	d3dBlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

	//그래픽 파이프라인 상태를 설정한다. 
	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	d3dPipelineStateDesc.pRootSignature = m_pd3dGraphicsRootSignature;
	d3dPipelineStateDesc.VS.pShaderBytecode = pd3dVertexShaderBlob->GetBufferPointer();
	d3dPipelineStateDesc.VS.BytecodeLength = pd3dVertexShaderBlob->GetBufferSize();
	d3dPipelineStateDesc.PS.pShaderBytecode = pd3dPixelShaderBlob->GetBufferPointer();
	d3dPipelineStateDesc.PS.BytecodeLength = pd3dPixelShaderBlob->GetBufferSize();
	d3dPipelineStateDesc.RasterizerState = d3dRasterizerDesc;
	d3dPipelineStateDesc.BlendState = d3dBlendDesc;
	d3dPipelineStateDesc.DepthStencilState.DepthEnable = FALSE;
	d3dPipelineStateDesc.DepthStencilState.StencilEnable = FALSE;
	d3dPipelineStateDesc.InputLayout.pInputElementDescs = NULL;
	d3dPipelineStateDesc.InputLayout.NumElements = 0;
	d3dPipelineStateDesc.SampleMask = UINT_MAX;
	d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	d3dPipelineStateDesc.NumRenderTargets = 1;
	d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dPipelineStateDesc.SampleDesc.Count = 1;
	d3dPipelineStateDesc.SampleDesc.Quality = 0;
	pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc,
		__uuidof(ID3D12PipelineState), (void **)&m_pd3dPipelineState);
	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();
}

void CScene::ReleaseObjects()
{
/*if (CEnemyObject::m_pExplosionMesh) 
	CEnemyObject::m_pExplosionMesh->Release();

if (CBulletObject::m_pBulletMesh)
	CBulletObject::m_pBulletMesh->Release();

for (auto& Object : m_vObjects) 
	if (Object) delete Object;

for (auto& Bullet : m_pPlayer->m_vbObjects)
	if (Bullet) delete Bullet;

if (m_Boss)
{
	for (const auto& Bullet : m_Boss->m_vbObjects)
		if (Bullet) delete Bullet;

	delete m_Boss;
}

if (m_pWallsObject) delete m_pWallsObject;*/

	////////////////////////////////////// New
	if (m_pd3dGraphicsRootSignature) m_pd3dGraphicsRootSignature->Release();
	if (m_pd3dPipelineState) m_pd3dPipelineState->Release();
}

// 충돌 체크
void CScene::CheckObjectByObjectCollisions() // 적끼리의 충돌
{
	for (const auto& Object : m_vObjects) Object->m_pObjectCollided = NULL;

	for (UINT i = 0; i < m_vObjects.size(); i++)
	{
		for (UINT j = (i + 1); j < m_vObjects.size(); j++)
		{
			if (m_vObjects[i]->m_xmOOBB.Intersects(m_vObjects[j]->m_xmOOBB))
			{
				m_vObjects[i]->m_pObjectCollided = m_vObjects[j];
				m_vObjects[j]->m_pObjectCollided = m_vObjects[i];
			}
		}
	}

	for (const auto& Object : m_vObjects)
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
}

void CScene::CheckObjectByBulletCollisions() // 플레이어 총알과의 충돌
{
	for (auto& Bullet : m_pPlayer->m_vbObjects)
	{
		if (m_Boss) // 보스
		{
			if (!m_Boss->m_bBlowingUp && Bullet->m_xmOOBB.Contains(m_Boss->m_xmOOBB))
			{
				if (m_pPlayer->m_Target == m_Boss)
					m_pPlayer->m_Target = NULL;

				Bullet->m_Delete = m_Boss->m_bBlowingUp = true;
				for (auto& Object : m_vObjects)
					Object->m_bBlowingUp = true;
				m_CreateEnemyEable = false;
				break;
			}
		}

		for (auto& Object : m_vObjects) { // 적
			if (!Object->m_bBlowingUp && Bullet->m_xmOOBB.Contains(Object->m_xmOOBB))
			{
				if (Object->m_DropItem)
					m_pPlayer->AddItem();

				if (m_pPlayer->m_Target == Object)
					m_pPlayer->m_Target = NULL;

				Bullet->m_Delete = Object->m_bBlowingUp = true;
				return;
			}
		}
	}
}

void CScene::CheckObjectByWallCollisions() // 객체의 벽 충돌
{
	for (const auto& Object : m_vObjects) // 적 객체의 벽 충돌
	{
		ContainmentType containType = m_pWallsObject->m_xmOOBB.Contains(Object->m_xmOOBB);
		switch (containType)
		{
			case DISJOINT:
			{
				int nPlaneIndex = -1;
				for (int j = 0; j < 6; j++)
				{
					PlaneIntersectionType intersectType = Object->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
					if (intersectType == BACK)
					{
						nPlaneIndex = j;
						break;
					}
				}
				if (nPlaneIndex != -1)
				{
					XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
					XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&Object->m_xmf3MovingDirection), xmvNormal);
					XMStoreFloat3(&Object->m_xmf3MovingDirection, xmvReflect);
				}
				break;
			}
			case INTERSECTS:
			{
				int nPlaneIndex = -1;
				for (int j = 0; j < 6; j++)
				{
					PlaneIntersectionType intersectType = Object->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
					if (intersectType == INTERSECTING)
					{
						nPlaneIndex = j;
						break;
					}
				}
				if (nPlaneIndex != -1)
				{
					XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
					XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&Object->m_xmf3MovingDirection), xmvNormal);
					XMStoreFloat3(&Object->m_xmf3MovingDirection, xmvReflect);
				}
				break;
			}
			case CONTAINS:
				break;
		}
	}

	for (const auto& Bullet : m_pPlayer->m_vbObjects) // 플레이어 총알의 벽 충돌
	{
		ContainmentType containType = m_pWallsObject->m_xmOOBB.Contains(Bullet->m_xmOOBB);
		switch (containType)
		{
		case DISJOINT:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = Bullet->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
				if (intersectType == BACK)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&Bullet->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&Bullet->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case INTERSECTS:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = Bullet->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
				if (intersectType == INTERSECTING)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&Bullet->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&Bullet->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case CONTAINS:
			break;
		}
	}

	for (const auto& Bullet : m_Boss->m_vbObjects) // 보스 총알의 벽 충돌
	{
		ContainmentType containType = m_pWallsObject->m_xmOOBB.Contains(Bullet->m_xmOOBB);
		switch (containType)
		{
		case DISJOINT:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = Bullet->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
				if (intersectType == BACK)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&Bullet->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&Bullet->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case INTERSECTS:
		{
			int nPlaneIndex = -1;
			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = Bullet->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));
				if (intersectType == INTERSECTING)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMVECTOR xmvNormal = XMVectorSet(m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y, m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z, 0.0f);
				XMVECTOR xmvReflect = XMVector3Reflect(XMLoadFloat3(&Bullet->m_xmf3MovingDirection), xmvNormal);
				XMStoreFloat3(&Bullet->m_xmf3MovingDirection, xmvReflect);
			}
			break;
		}
		case CONTAINS:
			break;
		}
	}
}

void CScene::CheckPlayerByWallCollisions() // 플레이어와 벽 충돌
{
	ContainmentType containType = m_pWallsObject->m_xmOOBB.Contains(m_pPlayer->m_xmOOBB);

	switch (containType)
	{
		case DISJOINT: // 내부에 없을 경우
		{
			int nPlaneIndex = -1;

			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = m_pPlayer->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));

				if (intersectType == BACK)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMFLOAT3 xmvNormal = XMFLOAT3(
					m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x,
					m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y,
					m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z);

				XMFLOAT3 xmf3Shift = XMFLOAT3(0, 0, 0);
				xmf3Shift = Vector3::Add(xmf3Shift, xmvNormal, 0.5f);
				m_pPlayer->Move(xmf3Shift, true);

				m_pPlayer->SetColor(RGB(255, 0, 0));
			}
			break;
		}
		case INTERSECTS: // 겹칠 경우
		{
			int nPlaneIndex = -1;

			for (int j = 0; j < 6; j++)
			{
				PlaneIntersectionType intersectType = m_pPlayer->m_xmOOBB.Intersects(XMLoadFloat4(&m_pWallsObject->m_pxmf4WallPlanes[j]));

				if (intersectType == INTERSECTING)
				{
					nPlaneIndex = j;
					break;
				}
			}
			if (nPlaneIndex != -1)
			{
				XMFLOAT3 xmvNormal = XMFLOAT3(
					m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].x,
					m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].y,
					m_pWallsObject->m_pxmf4WallPlanes[nPlaneIndex].z);

				XMFLOAT3 xmf3Shift = XMFLOAT3(0, 0, 0);
				xmf3Shift = Vector3::Add(xmf3Shift, xmvNormal, 0.5f);
				m_pPlayer->Move(xmf3Shift, true);

				m_pPlayer->SetColor(RGB(255, 0, 0));
			}
		}
	}
}

void CScene::CheckPlayerByEnemyCollisions() // 플레이어와 적 충돌
{
	for (const auto& Object : m_vObjects)
	{
		if(!Object->m_bBlowingUp && Object->m_xmOOBB.Intersects(m_pPlayer->m_xmOOBB))
		{
			//ClearObject();
			break;
		}
	}

	if (m_Boss)
	{
		for (const auto& Bullet : m_Boss->m_vbObjects)
		{
			if (m_pPlayer->m_xmOOBB.Intersects(Bullet->m_xmOOBB))
			{
				Bullet->m_Delete = true;
				ClearObject();
				break;
			}
		}

		if (!m_Boss->m_bBlowingUp && m_pPlayer->m_xmOOBB.Intersects(m_Boss->m_xmOOBB))
		{
			ClearObject();
		}
	}
}
///////////

void CScene::CheckPlayerColor()
{
	for (const auto& Object : m_vObjects)
	{
		XMFLOAT3 ObjectPosition = Vector3::Subtract(Object->GetPosition(), m_pPlayer->GetPosition(), false);
		float Angle = Vector3::DotProduct(m_pPlayer->m_xmf3Look, Vector3::Normalize(ObjectPosition));

		if (!Object->m_bBlowingUp && (Angle < 0))
		{
			m_pPlayer->SetColor(RGB(255, 178, 245));
			return;
		}
	}

	if(m_pPlayer->m_NumItem > 0)
		m_pPlayer->SetColor(RGB(0, 255, 0));
	else
		m_pPlayer->SetColor(RGB(0, 255, 255));
}

void CScene::CreateEnemy(int EnemyType)
{
	std::random_device rd;
	std::uniform_int_distribution<int> Cuid(0, 2);
	std::uniform_int_distribution<int> Duid(0, 7);
	std::uniform_int_distribution<int> XYuid(-20, 20);
	
	m_vObjects.emplace_back( new CEnemyObject );
	
	m_vObjects.back()->SetMesh(pObjectCubeMesh);

	// 적 타입 결정
	if(EnemyType == 0) // 일반 적
		m_vObjects.back()->SetColor( m_color[Cuid(rd) ]);
	else { // 특수 적
		m_vObjects.back()->SetDrop();
		m_vObjects.back()->SetColor(m_color[3]);
	}

	XMFLOAT3 pPosition = m_pPlayer->GetPosition();
	float CreatePosion = pPosition.z + 100;
	if (CreatePosion > 950)
		CreatePosion = 900;
	
	m_vObjects.back()->SetPosition(XYuid(rd), XYuid(rd), CreatePosion);

	m_vObjects.back()->SetRotationAxis(XMFLOAT3(1, 0, 1));
	m_vObjects.back()->SetRotationSpeed(360.0f);

	m_vObjects.back()->SetMovingDirection( m_direction[Duid(rd)]);
	m_vObjects.back()->SetMovingSpeed(5.5f);

	m_vObjects.back()->SetTarget(m_pPlayer);
}

void CScene::ClearObject()
{
	m_vObjects.clear();

	m_pPlayer->m_vbObjects.clear();
		
	if (m_pPlayer->m_Target)
		m_pPlayer->m_Target = NULL;

	if (m_Boss)
	{
		m_Boss->m_vbObjects.clear();
	}

	m_pPlayer->SetPosition(0.0, 0.0, -450.0f);
	m_CommonEnemyCreatetime = 0.0f;
	m_SpecialEnemyCreatetime = 0.0f;
}

void CScene::UseItem()
{
	for (const auto& Object : m_vObjects)
	{
		if (!Object->m_bBlowingUp)
		{
			XMFLOAT3 EPosition = Object->GetPosition();
			XMFLOAT3 PPosition = m_pPlayer->GetPosition();

			if (abs(EPosition.z - PPosition.z) < 30)
			{
				if (Object->m_DropItem)
					m_pPlayer->AddItem();
				Object->m_bBlowingUp = true;
			}
		}
	}
	m_pPlayer->SubItem();
}

void CScene::Picking()
{
	float Screenx = (2.0f * (m_ptCursorPos.x - m_wndRect.left) / m_wndRect.right) - 1;
	float Screeny = (-2.0f * (m_ptCursorPos.y - 34 - m_wndRect.top) / m_wndRect.bottom) + 1;

	XMVECTOR Camera = XMVectorSet(
		Screenx / m_pPlayer->m_pCamera->m_xmf4x4Projection._11,
		Screeny / m_pPlayer->m_pCamera->m_xmf4x4Projection._22,
		1.0f, 1.0f);

	XMMATRIX CameraCoor = XMLoadFloat4x4(&m_pPlayer->m_pCamera->m_xmf4x4View);

	for (const auto& Object : m_vObjects)
	{
		Object->m_xmOOBB.Transform(Object->m_xmOOBB, CameraCoor);
		XMStoreFloat4(&Object->m_xmOOBB.Orientation, XMQuaternionNormalize(XMLoadFloat4(&Object->m_xmOOBB.Orientation)));
	}

	m_Boss->m_xmOOBB.Transform(m_Boss->m_xmOOBB, CameraCoor);
	XMStoreFloat4(&m_Boss->m_xmOOBB.Orientation, XMQuaternionNormalize(XMLoadFloat4(&m_Boss->m_xmOOBB.Orientation)));

	XMVECTOR CameraOrigin = XMVectorSet(0, 0, 0, 0);
	float Dist;

	for (const auto& Object : m_vObjects)
	{
		if (!Object->m_bBlowingUp &&  Object->m_xmOOBB.Intersects(CameraOrigin, Camera, Dist)) {
			m_pPlayer->m_Target = Object;
			return;
		}
	}

	if (!m_Boss->m_bBlowingUp && m_Boss->m_xmOOBB.Intersects(CameraOrigin, Camera, Dist)) {
		m_pPlayer->m_Target = m_Boss;
		return;
	}

	m_pPlayer->m_Target = NULL;
}

bool CScene::ProcessInput()
{
	return(false);
}

void CScene::AnimateObjects(float fElapsedTime)
{
	//if (m_CreateEnemyEable)
	//{
	//	m_CommonEnemyCreatetime += fElapsedTime;
	//	m_SpecialEnemyCreatetime += fElapsedTime;

	//	if (m_CommonEnemyCreatetime > 1) // 일반 적 생성
	//	{
	//		CreateEnemy(0);
	//		m_CommonEnemyCreatetime -= 1;
	//	}

	//	if (m_SpecialEnemyCreatetime > 10) // 특수 적 생성
	//	{
	//		CreateEnemy(1);
	//		m_SpecialEnemyCreatetime -= 10;
	//	}
	//}

	//// 오브젝트 삭제
	//for (auto& i = m_vObjects.begin(); i != m_vObjects.end();)
	//{
	//	if ((*i)->m_Delete)
	//	{
	//		i = m_vObjects.erase(i);
	//	}
	//	else
	//		i++;
	//}

	//m_pPlayer->Animate(fElapsedTime);

	//// 애니메이트
	//m_pPlayer->Animate(fElapsedTime);
	//m_pWallsObject->Animate(fElapsedTime);

	//for (const auto& Object : m_vObjects)
	//	Object->Animate(fElapsedTime);

	//if (m_Boss)
	//	m_Boss->Animate(fElapsedTime);

	//// 플레이어 색깔 설정
	//CheckPlayerColor();
	//
	//// 충돌 체크
	//CheckPlayerByWallCollisions();
	//CheckPlayerByEnemyCollisions();

	//CheckObjectByObjectCollisions();
	//CheckObjectByBulletCollisions();
	//CheckObjectByWallCollisions();
}

void CScene::Render(ID3D12GraphicsCommandList *pd3dCommandList)
{
//m_pWallsObject->Render(hDCFrameBuffer, pCamera);

//for (const auto& Object : m_vObjects) Object->Render(hDCFrameBuffer, pCamera);

//if(m_Boss) m_Boss->Render(hDCFrameBuffer, pCamera);

	//그래픽 루트 시그너쳐를 설정한다. 
	pd3dCommandList->SetGraphicsRootSignature(m_pd3dGraphicsRootSignature);

	//파이프라인 상태를 설정한다. 
	pd3dCommandList->SetPipelineState(m_pd3dPipelineState);

	//프리미티브 토폴로지(삼각형 리스트)를 설정한다. 
	pd3dCommandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//정점 3개를 사용하여 렌더링한다. 
	pd3dCommandList->DrawInstanced(3, 1, 0, 0);
}
