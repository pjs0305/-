#pragma once

#include "GameObject.h"
#include "Player.h"


class CScene
{
public:
	CScene();
	virtual ~CScene();

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

	virtual void BuildObjects();
	virtual void ReleaseObjects();

	virtual void CheckObjectByObjectCollisions();
	virtual void CheckObjectByWallCollisions();
	void CheckPlayerByWallCollisions();
	void CheckPlayerByEnemyCollisions();
	void CheckObjectByBulletCollisions();

	void CheckPlayerColor();

	virtual void Animate(float fElapsedTime);
	virtual void Render(HDC hDCFrameBuffer, CCamera *pCamera);

	virtual void OnProcessingMouseMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);
	virtual void OnProcessingKeyboardMessage(HWND hWnd, UINT nMessageID, WPARAM wParam, LPARAM lParam);

	void CreateEnemy(int EnemyType);
	void UseItem();
	void Picking();
	void ClearObject();
};

