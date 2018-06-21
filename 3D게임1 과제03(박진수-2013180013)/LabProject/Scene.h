#pragma once

#include "GameObject.h"
#include "Player.h"
#include "Timer.h"

class CScene
{
public:
	CPlayer							*m_pPlayer = NULL;

	std::vector<CEnemyObject*>		m_vObjects;
	CBossObject						*m_Boss = NULL;

	CWallsObject					*m_pWallsObject = NULL;

	float							m_CommonEnemyCreatetime = 0.0f;
	float							m_SpecialEnemyCreatetime = 0.0f;

	CWallMesh						*pWallCubeMesh = NULL;
	CCubeMesh						*pObjectCubeMesh = NULL;

	POINT							m_ptCursorPos;
	RECT							m_wndRect;

	bool							m_CreateEnemyEable = true;

	UINT m_color[4] = { RGB(0,190,0), RGB(200, 120, 190), RGB(0,0,190), RGB(220,0,0)};

	XMFLOAT3 m_direction[7] = { XMFLOAT3(1, 0, 0), XMFLOAT3(1, 1, 0), XMFLOAT3(0, 1, 0),
		XMFLOAT3(0, 1, 1), XMFLOAT3(0, 0, 1), XMFLOAT3(1, 0, 1), XMFLOAT3(1, 1, 1)};


	virtual void CheckObjectByObjectCollisions();
	virtual void CheckObjectByWallCollisions();
	void CheckPlayerByWallCollisions();
	void CheckPlayerByEnemyCollisions();
	void CheckObjectByBulletCollisions();

	void CheckPlayerColor();



	void CreateEnemy(int EnemyType);
	void UseItem();
	void Picking();
	void ClearObject();

	///////////////////////////////// New
	CScene();
	~CScene();
	
	bool OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	bool OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void BuildObjects(ID3D12Device *pd3dDevice);
	void ReleaseObjects();

	bool ProcessInput();
	void AnimateObjects(float fElapsedTime);
	void Render(ID3D12GraphicsCommandList *pd3dCommandList);

	//루트 시그너쳐를 나타내는 인터페이스 포인터이다.
	ID3D12RootSignature *m_pd3dGraphicsRootSignature;
	
	//파이프라인 상태를 나타내는 인터페이스 포인터이다.
	ID3D12PipelineState *m_pd3dPipelineState;
	
};

