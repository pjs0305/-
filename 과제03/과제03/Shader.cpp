#include "stdafx.h"
#include "Shader.h"
#include "Player.h"
#include "GameObject.h"

extern float PlayerZ;

CShader::CShader()
{
}

CShader::~CShader()
{
	if (m_ppd3dPipelineStates)
	{
		for (int i = 0; i < m_nPipelineStates; i++) if (m_ppd3dPipelineStates[i])
			m_ppd3dPipelineStates[i]->Release();
		delete[] m_ppd3dPipelineStates;
	}
}

D3D12_RASTERIZER_DESC CShader::CreateRasterizerState() //래스터라이저 상태를 설정하기 위한 구조체를 반환한다. 
{
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

	return(d3dRasterizerDesc);
}

D3D12_DEPTH_STENCIL_DESC CShader::CreateDepthStencilState() //깊이-스텐실 검사를 위한 상태를 설정하기 위한 구조체를 반환한다. 
{
	D3D12_DEPTH_STENCIL_DESC d3dDepthStencilDesc;
	::ZeroMemory(&d3dDepthStencilDesc, sizeof(D3D12_DEPTH_STENCIL_DESC));
	d3dDepthStencilDesc.DepthEnable = TRUE;
	d3dDepthStencilDesc.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
	d3dDepthStencilDesc.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
	d3dDepthStencilDesc.StencilEnable = FALSE;
	d3dDepthStencilDesc.StencilReadMask = 0x00;
	d3dDepthStencilDesc.StencilWriteMask = 0x00;
	d3dDepthStencilDesc.FrontFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.FrontFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;
	d3dDepthStencilDesc.BackFace.StencilFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilDepthFailOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilPassOp = D3D12_STENCIL_OP_KEEP;
	d3dDepthStencilDesc.BackFace.StencilFunc = D3D12_COMPARISON_FUNC_NEVER;

	return(d3dDepthStencilDesc);
}

D3D12_BLEND_DESC CShader::CreateBlendState() //블렌딩 상태를 설정하기 위한 구조체를 반환한다. 
{
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

	return(d3dBlendDesc);
}

D3D12_INPUT_LAYOUT_DESC CShader::CreateInputLayout() //입력 조립기에게 정점 버퍼의 구조를 알려주기 위한 구조체를 반환한다. 
{
	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = NULL;
	d3dInputLayoutDesc.NumElements = 0;
	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob) //정점 셰이더 바이트 코드를 생성(컴파일)한다. 
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;

	return(d3dShaderByteCode);
}

D3D12_SHADER_BYTECODE CShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob) //픽셀 셰이더 바이트 코드를 생성(컴파일)한다. 
{
	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = 0;
	d3dShaderByteCode.pShaderBytecode = NULL;

	return(d3dShaderByteCode);
}

D3D12_SHADER_BYTECODE CShader::CompileShaderFromFile(const WCHAR *pszFileName, LPCSTR pszShaderName, LPCSTR pszShaderProfile, ID3DBlob **ppd3dShaderBlob) 
//셰이더 소스 코드를 컴파일하여 바이트 코드 구조체를 반환한다. 
{
	UINT nCompileFlags = 0;
#if defined(_DEBUG)
	nCompileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif

	::D3DCompileFromFile(pszFileName, NULL, NULL, pszShaderName, pszShaderProfile, nCompileFlags, 0, ppd3dShaderBlob, NULL);

	D3D12_SHADER_BYTECODE d3dShaderByteCode;
	d3dShaderByteCode.BytecodeLength = (*ppd3dShaderBlob)->GetBufferSize();
	d3dShaderByteCode.pShaderBytecode = (*ppd3dShaderBlob)->GetBufferPointer();

	return(d3dShaderByteCode);
}

void CShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature) //그래픽스 파이프라인 상태 객체를 생성한다. 
{
	ID3DBlob *pd3dVertexShaderBlob = NULL, *pd3dPixelShaderBlob = NULL;

	D3D12_GRAPHICS_PIPELINE_STATE_DESC d3dPipelineStateDesc;
	::ZeroMemory(&d3dPipelineStateDesc, sizeof(D3D12_GRAPHICS_PIPELINE_STATE_DESC));
	d3dPipelineStateDesc.pRootSignature = pd3dGraphicsRootSignature;
	d3dPipelineStateDesc.VS = CreateVertexShader(&pd3dVertexShaderBlob);
	d3dPipelineStateDesc.PS = CreatePixelShader(&pd3dPixelShaderBlob);
	d3dPipelineStateDesc.RasterizerState = CreateRasterizerState();
	d3dPipelineStateDesc.BlendState = CreateBlendState();
	d3dPipelineStateDesc.DepthStencilState = CreateDepthStencilState();
	d3dPipelineStateDesc.InputLayout = CreateInputLayout();
	d3dPipelineStateDesc.SampleMask = UINT_MAX;
	d3dPipelineStateDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	d3dPipelineStateDesc.NumRenderTargets = 1;
	d3dPipelineStateDesc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3dPipelineStateDesc.DSVFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
	d3dPipelineStateDesc.SampleDesc.Count = 1;
	d3dPipelineStateDesc.Flags = D3D12_PIPELINE_STATE_FLAG_NONE;
	pd3dDevice->CreateGraphicsPipelineState(&d3dPipelineStateDesc,
		__uuidof(ID3D12PipelineState), (void **)&m_ppd3dPipelineStates[0]);

	if (pd3dVertexShaderBlob) pd3dVertexShaderBlob->Release();
	if (pd3dPixelShaderBlob) pd3dPixelShaderBlob->Release();
	if (d3dPipelineStateDesc.InputLayout.pInputElementDescs) delete[]

		d3dPipelineStateDesc.InputLayout.pInputElementDescs;
}

void CShader::CreateShaderVariables(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CShader::UpdateShaderVariables(ID3D12GraphicsCommandList *pd3dCommandList)
{
}

void CShader::UpdateShaderVariable(ID3D12GraphicsCommandList *pd3dCommandList, XMFLOAT4X4 *pxmf4x4World)
{
	XMFLOAT4X4 xmf4x4World;
	XMStoreFloat4x4(&xmf4x4World, XMMatrixTranspose(XMLoadFloat4x4(pxmf4x4World)));
	pd3dCommandList->SetGraphicsRoot32BitConstants(0, 16, &xmf4x4World, 0);
}

void CShader::ReleaseShaderVariables()
{
}

void CShader::OnPrepareRender(ID3D12GraphicsCommandList *pd3dCommandList)
{
	//파이프라인에 그래픽스 상태 객체를 설정한다. 
	if (m_ppd3dPipelineStates[0]) pd3dCommandList->SetPipelineState(m_ppd3dPipelineStates[0]);
}

void CShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	OnPrepareRender(pd3dCommandList);
}


CObjectsShader::CObjectsShader()
{
	CreateTime = 0.f;
}

void CObjectsShader::BuildObjects(ID3D12Device *pd3dDevice, ID3D12GraphicsCommandList *pd3dCommandList)
{
	// 적 메쉬 생성
	float fCWidth = 5.0f, fCHeight = 5.0f, fCDepth = 5.0f;

	pRedCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, fCWidth, fCHeight, fCDepth, COLOR_RED);
	pRedCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fCWidth / 2, fCHeight / 2, fCDepth / 2), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	pGreenCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, fCWidth, fCHeight, fCDepth, COLOR_GREEN);
	pGreenCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fCWidth / 2, fCHeight / 2, fCDepth / 2), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	pBlueCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, fCWidth, fCHeight, fCDepth, COLOR_BLUE);
	pBlueCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fCWidth / 2, fCHeight / 2, fCDepth / 2), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));
	pPinkCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, fCWidth, fCHeight, fCDepth, COLOR_PINK);
	pPinkCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fCWidth / 2, fCHeight / 2, fCDepth / 2), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_pExplosionMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, fCWidth/5, fCHeight / 5, fCDepth / 5);
	CRotatingObject::PrepareExplosion(m_pExplosionMesh);

	// 총알 메쉬 생성
	float fBWidth = 1.0f, fBHeight = 1.0f, fBDepth = 1.0f;
	pBulletCubeMesh = new CCubeMeshDiffused(pd3dDevice, pd3dCommandList, fBWidth, fBHeight, fBDepth, RANDOM_COLOR);
	pBulletCubeMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fBWidth / 2, fBHeight / 2, fBDepth / 2), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	// 벽 메쉬 생성
	float fWWidth = 100.0f, fWHeight = 100.0f, fWDepth = 1000.0f;

	CWallMeshDiffused *pWallMesh = new CWallMeshDiffused(pd3dDevice, pd3dCommandList, fWWidth, fWHeight, fWDepth);
	pWallMesh->SetOOBB(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(fWWidth / 2, fWHeight / 2, fWDepth / 2), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f));

	m_pWallObjects = new CWallObject();
	m_pWallObjects->SetMesh(pWallMesh);

	m_pWallObjects->SetPosition(0.f, 0.f, 0.f);

	m_pWallObjects->m_pxmf4WallPlanes[0] = XMFLOAT4(+1.0f, 0.0f, 0.0f, fWWidth / 2);
	m_pWallObjects->m_pxmf4WallPlanes[1] = XMFLOAT4(-1.0f, 0.0f, 0.0f, fWWidth / 2);
	m_pWallObjects->m_pxmf4WallPlanes[2] = XMFLOAT4(0.0f, +1.0f, 0.0f, fWHeight / 2);
	m_pWallObjects->m_pxmf4WallPlanes[3] = XMFLOAT4(0.0f, -1.0f, 0.0f, fWHeight / 2);
	m_pWallObjects->m_pxmf4WallPlanes[4] = XMFLOAT4(0.0f, 0.0f, +1.0f, fWDepth / 2);
	m_pWallObjects->m_pxmf4WallPlanes[5] = XMFLOAT4(0.0f, 0.0f, -1.0f, fWDepth / 2);
	
	CreateShaderVariables(pd3dDevice, pd3dCommandList);
}

void CObjectsShader::CreateEnemy()
{
	CRotatingObject *pRotatingObject = NULL;
	pRotatingObject = new CRotatingObject();

	int r = rand() % 3;
	switch(r)
	{
	case 0:
		pRotatingObject->SetMesh(pBlueCubeMesh);
		break;
	case 1:
		pRotatingObject->SetMesh(pGreenCubeMesh);
		break;
	case 2:
		pRotatingObject->SetMesh(pPinkCubeMesh);
		break;
	}

	//각 정육면체 객체의 위치를 설정한다. 
	std::uniform_int_distribution<int> uid(-40, 40);
	std::uniform_int_distribution<int> uid2(-1, 1);

	pRotatingObject->SetPosition(uid(dre), uid(gen), PlayerZ + 100);

	pRotatingObject->SetRotationAxis(XMFLOAT3(1.0f, 0.5f, 0));
	pRotatingObject->SetRotationSpeed(180.f);

	pRotatingObject->SetMovingDirection(XMFLOAT3(uid2(dre), uid2(gen), 0.0f));
	pRotatingObject->SetMovingSpeed(10.f);

	m_vEnemyObject.emplace_back(pRotatingObject);
}

void CObjectsShader::CreateBullet(XMFLOAT3 Position, XMFLOAT3 Direction)
{
	CBulletObject *pBulletObject = NULL;
	pBulletObject = new CBulletObject();
	pBulletObject->SetMesh(pBulletCubeMesh);

	pBulletObject->SetPosition(Position);

	pBulletObject->SetRotationAxis(XMFLOAT3(1.0f, 0.5f, 0));
	pBulletObject->SetRotationSpeed(720.f);

	pBulletObject->SetMovingDirection(Direction);
	pBulletObject->SetMovingSpeed(300.f);

	m_vPlayerBullet.emplace_back(pBulletObject);
}

void CObjectsShader::DeleteObject()
{
	for (auto& Object = m_vEnemyObject.begin(); Object != m_vEnemyObject.end(); )
	{
		if ((*Object)->m_Delete)
		{
			(*Object)->ReleaseUploadBuffers();
			delete *Object;

			Object = m_vEnemyObject.erase(Object);

		}
		else
			Object++;
	}

	for (auto& Bullet = m_vPlayerBullet.begin(); Bullet != m_vPlayerBullet.end(); )
	{
		if ((*Bullet)->m_Delete)
		{
			(*Bullet)->ReleaseUploadBuffers();
			delete *Bullet;

			Bullet = m_vPlayerBullet.erase(Bullet);

		}
		else
			Bullet++;
	}
}

D3D12_INPUT_LAYOUT_DESC CObjectsShader::CreateInputLayout()
{
	UINT nInputElementDescs = 2;
	D3D12_INPUT_ELEMENT_DESC *pd3dInputElementDescs = new D3D12_INPUT_ELEMENT_DESC[nInputElementDescs];

	pd3dInputElementDescs[0] = { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };
	pd3dInputElementDescs[1] = { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 };

	D3D12_INPUT_LAYOUT_DESC d3dInputLayoutDesc;
	d3dInputLayoutDesc.pInputElementDescs = pd3dInputElementDescs;
	d3dInputLayoutDesc.NumElements = nInputElementDescs;

	return(d3dInputLayoutDesc);
}

D3D12_SHADER_BYTECODE CObjectsShader::CreateVertexShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shader.hlsl", "VSDiffused", "vs_5_1", ppd3dShaderBlob));
}

D3D12_SHADER_BYTECODE CObjectsShader::CreatePixelShader(ID3DBlob **ppd3dShaderBlob)
{
	return(CShader::CompileShaderFromFile(L"Shader.hlsl", "PSDiffused", "ps_5_1", ppd3dShaderBlob));
}

void CObjectsShader::CreateShader(ID3D12Device *pd3dDevice, ID3D12RootSignature *pd3dGraphicsRootSignature)
{
	m_nPipelineStates = 1;
	m_ppd3dPipelineStates = new ID3D12PipelineState*[m_nPipelineStates];
	CShader::CreateShader(pd3dDevice, pd3dGraphicsRootSignature);
}

void CObjectsShader::ReleaseUploadBuffers()
{
	if (m_pWallObjects)
		m_pWallObjects->ReleaseUploadBuffers();

	if (m_vEnemyObject.size())
	{
		for (const auto& Object : m_vEnemyObject) 
			Object->ReleaseUploadBuffers();
	}

	if (m_vPlayerBullet.size())
	{
		for (const auto& Bullet : m_vPlayerBullet)
		{
			Bullet->ReleaseUploadBuffers();
		}
	}
}

void CObjectsShader::AnimateObjects(float fTimeElapsed)
{
	if (CreateTime > 1.f)
	{
		CreateEnemy();
		CreateTime = 0;
	}
	else
		CreateTime += fTimeElapsed;


	for (const auto& Object : m_vEnemyObject)
	{
		Object->Animate(fTimeElapsed);
	}

	for (const auto& Bullet : m_vPlayerBullet)
	{
		Bullet->Animate(fTimeElapsed);
	}

	if (m_pWallObjects)
		m_pWallObjects->Animate(fTimeElapsed);

	DeleteObject();
}

void CObjectsShader::ReleaseObjects()
{
	if (m_pWallObjects)
		delete m_pWallObjects;

	if (m_vEnemyObject.size())
	{
		for (auto& b = m_vEnemyObject.begin(); b != m_vEnemyObject.end();)
		{
			(*b)->ReleaseUploadBuffers();
			delete *b;

			b = m_vEnemyObject.erase(b);
		}
	}

	if (m_vPlayerBullet.size())
	{
		for (auto& b = m_vPlayerBullet.begin(); b != m_vPlayerBullet.end();)
		{
			(*b)->ReleaseUploadBuffers();
			delete *b;

			b = m_vPlayerBullet.erase(b);
		}
	}
}

void CObjectsShader::Render(ID3D12GraphicsCommandList *pd3dCommandList, CCamera *pCamera)
{
	CShader::Render(pd3dCommandList, pCamera);

	for (const auto& Object : m_vEnemyObject)
	{
		if (Object)
			Object->Render(pd3dCommandList, pCamera);
	}

	for (const auto& Bullet : m_vPlayerBullet)
	{
		if (Bullet)
			Bullet->Render(pd3dCommandList, pCamera);
	}

	if (m_pWallObjects)
	{
		m_pWallObjects->Render(pd3dCommandList, pCamera);
	}
}