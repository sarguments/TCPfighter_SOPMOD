#include "stdafx.h"
#include "CEffectObject.h"
#include "CPlayerObject.h"
#include "CScreenDib.h"
#include "CSpriteDib.h"

CEffectObject::CEffectObject()
{
	// TODO : 이펙트 생성자
}

CEffectObject::CEffectObject(DWORD dwAttackID)
	: _bEffectStart(false)
{
	_dwAttackID = dwAttackID;
	SetObjectType(e_OBJECT_TYPE::eTYPE_EFFECT);
	SetSprite(eEFFECT_SPARK_01, eEFFECT_SPARK_04, dfDELAY_EFFECT);

	static int effectNum = 100;
	SetObjectID(effectNum);
	++effectNum;
}

CEffectObject::~CEffectObject()
{
}

bool CEffectObject::Action(void)
{
	// 다음 프레임으로
	NextFrame();

	// 일치하는 아이디를 찾고
	auto iter = std::find_if(g_ObjectList.begin(), g_ObjectList.end(),
		[=](CBaseObject* param) {
		if (param->GetObjectType() == e_OBJECT_TYPE::eTYPE_PLAYER &&
			param->GetObjectID() == _dwAttackID)
		{
			return true;
		}
		return false;
	});

	if (iter == g_ObjectList.end())
	{
		wcout << L"Effect Find FAIL" << endl;
		return false;
	}
	wcout << L"Effect Find : " << (*iter)->GetObjectID() << endl;

	// 어떤 공격인지 판별해서
	int curAction = ((CPlayerObject*)(*iter))->GetActionCur();
	int nowSprite = ((CPlayerObject*)(*iter))->GetSprite();
	//int playerDir = ((CPlayerObject*)(*iter))->GetDirection();

	switch (curAction)
	{
	case dfACTION_ATTACK1:
	{
		// 해당 공격의 이펙트 시작지점에서(GetSprite) 이펙트를 그린다.
		if (nowSprite == ePLAYER_ATTACK1_L02 || nowSprite == ePLAYER_ATTACK1_R02)
		{
			_bEffectStart = true;
		}
	}
	break;
	case dfACTION_ATTACK2:
	{
		if (nowSprite == ePLAYER_ATTACK2_L02 || nowSprite == ePLAYER_ATTACK2_R02)
		{
			_bEffectStart = true;
		}
	}
	break;
	case dfACTION_ATTACK3:
	{
		if (nowSprite == ePLAYER_ATTACK3_L03 || nowSprite == ePLAYER_ATTACK3_R03)
		{
			_bEffectStart = true;
		}
	}
	break;
	}

	// 스프라이가 끝에 도달했으면 삭제
	if (isEndFrame() == true)
	{
		return true;
	}

	return false;
}

bool CEffectObject::Draw(void)
{
	// TODO : 이펙트 그리기 임시

	// 계속 전역 객체 참조하지 말고 로컬로 포인터 받아서 쓴다.
	CScreenDib* pLocalScDib = &g_ScreenDib;
	CSpriteDib* pLocalSpDib = &g_SpriteDib;

	// 실제 이미지 시작점, 너비, 높이, 피치 - 필수 4가지 - 나중에 드로우에 항상 이 정보 전달
	// 출력 버퍼 포인터 및 정보 얻음
	BYTE* bypDest = pLocalScDib->GetDibBuffer();
	int iDestWidth = pLocalScDib->GetWidth();
	int iDestHeight = pLocalScDib->GetHeight();
	int iDestPitch = pLocalScDib->GetPitch();

	// _bEffectStart가 true인걸 그린다.
	if (_bEffectStart == false)
	{
		return false;
	}

	pLocalSpDib->DrawSprite(GetSprite(),
		100 + 20, 100 + 20, bypDest, iDestWidth, iDestHeight, iDestPitch);

	return true;
}