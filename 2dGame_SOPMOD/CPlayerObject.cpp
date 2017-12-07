#include "stdafx.h"
#include "hoxy_Header.h"

#include "CPlayerObject.h"
#include "CScreenDib.h"
#include "CSpriteDib.h"

//CPlayerObject::CPlayerObject(CHAR hp)
//	: _chHP(hp), _bPlayerCharacter(false)
//{
//	SetDirection(dfDIR_LEFT);
//	SetObjectType(e_OBJECT_TYPE::eTYPE_PLAYER);
//}

CPlayerObject::CPlayerObject(CHAR hp, bool bPlayer, int dir)
	: _chHP(hp), _bPlayerCharacter(bPlayer)
{
	SetDirection(dir);
	SetObjectType(e_OBJECT_TYPE::eTYPE_PLAYER);
}

CPlayerObject::~CPlayerObject()
{
}

bool CPlayerObject::Action(void)
{
	// 다음 프레임으로 애니메이션
	NextFrame();
	ActionProc();

	// TODO : 여기서 보낼까?
	return false;
}

bool CPlayerObject::Draw(void)
{
	// 계속 전역 객체 참조하지 말고 로컬로 포인터 받아서 쓴다.
	CScreenDib* pLocalScDib = &g_ScreenDib;
	CSpriteDib* pLocalSpDib = &g_SpriteDib;

	// 실제 이미지 시작점, 너비, 높이, 피치 - 필수 4가지 - 나중에 드로우에 항상 이 정보 전달
	// 출력 버퍼 포인터 및 정보 얻음
	BYTE* bypDest = pLocalScDib->GetDibBuffer();
	int iDestWidth = pLocalScDib->GetWidth();
	int iDestHeight = pLocalScDib->GetHeight();
	int iDestPitch = pLocalScDib->GetPitch();

	// 그림자
	pLocalSpDib->DrawSprite50(e_SPRITE::eSHADOW,
		GetCurX(), GetCurY(), bypDest, iDestWidth, iDestHeight, iDestPitch);

	// 플레이어
	if (_bPlayerCharacter)
	{
		pLocalSpDib->DrawSpriteRed(GetSprite(),
			GetCurX(), GetCurY(), bypDest, iDestWidth, iDestHeight, iDestPitch);
	}
	else
	{
		pLocalSpDib->DrawSprite(GetSprite(),
			GetCurX(), GetCurY(), bypDest, iDestWidth, iDestHeight, iDestPitch);
	}

	// HP게이지
	pLocalSpDib->DrawSprite(e_SPRITE::eGUAGE_HP,
		GetCurX() - 35, GetCurY() + 9, bypDest, iDestWidth, iDestHeight, iDestPitch, GetHP());

	return true;
}

// TODO : 액션이 바뀔때 체크
void CPlayerObject::ActionProc(void)
{
	switch (_dwActionCur)
	{
		// 공격은 마저 처리
	case dfACTION_ATTACK1:
	case dfACTION_ATTACK2:
	case dfACTION_ATTACK3:
	{
		if (isEndFrame())
		{
			// 기본동작으로 돌아감
			SetActionStand();

			// 입력 초기화
			_dwActionInput = dfACTION_STAND;
		}
	}
	break;
	default:
	{
		// 사용자 입력 처리
		InputActionProc();
	}
	break;
	}
}

int CPlayerObject::GetDirection(void)
{
	return _iDirCur;
}

// HP는 CHAR
CHAR CPlayerObject::GetHP(void)
{
	return _chHP;
}

bool CPlayerObject::isPlayer(void)
{
	return _bPlayerCharacter;
}

void CPlayerObject::SetDirection(int param)
{
	_iDirOld = _iDirCur;
	_iDirCur = param;
}

void CPlayerObject::SetHP(CHAR param)
{
	_chHP = param;
}

DWORD CPlayerObject::GetActionCur(void)
{
	return _dwActionCur;
}

// 입력 처리
void CPlayerObject::InputActionProc()
{
	switch (_dwActionInput)
	{
	case dfACTION_MOVE_LL:
	{
		SetPosition(_iCurX - dfSPEED_PLAYER_X, _iCurY);
		SetDirection(dfDIR_LEFT);
		SetActionMove(_dwActionInput);
	}
	break;
	case dfACTION_MOVE_LU:
	{
		SetPosition(_iCurX - dfSPEED_PLAYER_X, _iCurY - dfSPEED_PLAYER_Y);
		SetDirection(dfDIR_LEFT);
		SetActionMove(_dwActionInput);
	}
	break;
	case dfACTION_MOVE_UU:
	{
		SetPosition(_iCurX, _iCurY - dfSPEED_PLAYER_Y);
		SetActionMove(_dwActionInput);
	}
	break;
	case dfACTION_MOVE_RU:
	{
		SetPosition(_iCurX + dfSPEED_PLAYER_X, _iCurY - dfSPEED_PLAYER_Y);
		SetDirection(dfDIR_RIGHT);
		SetActionMove(_dwActionInput);
	}
	break;
	case dfACTION_MOVE_RR:
	{
		SetPosition(_iCurX + dfSPEED_PLAYER_X, _iCurY);
		SetDirection(dfDIR_RIGHT);
		SetActionMove(_dwActionInput);
	}
	break;
	case dfACTION_MOVE_RD:
	{
		SetPosition(_iCurX + dfSPEED_PLAYER_X, _iCurY + dfSPEED_PLAYER_Y);
		SetDirection(dfDIR_RIGHT);
		SetActionMove(_dwActionInput);
	}
	break;
	case dfACTION_MOVE_DD:
	{
		SetPosition(_iCurX, _iCurY + dfSPEED_PLAYER_Y);
		SetActionMove(_dwActionInput);
	}
	break;
	case dfACTION_MOVE_LD:
	{
		SetPosition(_iCurX - dfSPEED_PLAYER_X, _iCurY + dfSPEED_PLAYER_Y);
		SetDirection(dfDIR_LEFT);
		SetActionMove(_dwActionInput);
	}
	break;
	case dfACTION_ATTACK1:
	{
		SetActionAttack1();
	}
	break;
	case dfACTION_ATTACK2:
	{
		SetActionAttack2();
	}
	break;
	case dfACTION_ATTACK3:
	{
		SetActionAttack3();
	}
	break;
	case dfACTION_STAND:
	{
		// 기본 입력은 스탠드이다.
		SetActionStand();
	}
	break;
	}

	//_dwActionInput = dfACTION_STAND;
	//SetActionStand();
}

void CPlayerObject::SetActionAttack1(void)
{
	_dwActionOld = _dwActionCur;
	_dwActionCur = dfACTION_ATTACK1;

	// 방향설정
	int nowDir = GetDirection();
	if (nowDir == dfDIR_LEFT)
	{
		//SetDirection(dfDIR_LEFT);
		SetSprite(e_SPRITE::ePLAYER_ATTACK1_L01, e_SPRITE::ePLAYER_ATTACK1_L_MAX, dfDELAY_ATTACK1);
	}
	else
	{
		//SetDirection(dfDIR_RIGHT);
		SetSprite(e_SPRITE::ePLAYER_ATTACK1_R01, e_SPRITE::ePLAYER_ATTACK1_R_MAX, dfDELAY_ATTACK1);
	}
}

void CPlayerObject::SetActionAttack2(void)
{
	_dwActionOld = _dwActionCur;
	_dwActionCur = dfACTION_ATTACK2;

	int nowDir = GetDirection();
	if (nowDir == dfDIR_LEFT)
	{
		//SetDirection(dfDIR_LEFT);
		SetSprite(e_SPRITE::ePLAYER_ATTACK2_L01, e_SPRITE::ePLAYER_ATTACK2_L_MAX, dfDELAY_ATTACK2);
	}
	else
	{
		//SetDirection(dfDIR_RIGHT);
		SetSprite(e_SPRITE::ePLAYER_ATTACK2_R01, e_SPRITE::ePLAYER_ATTACK2_R_MAX, dfDELAY_ATTACK2);
	}
}

void CPlayerObject::SetActionAttack3(void)
{
	_dwActionOld = _dwActionCur;
	_dwActionCur = dfACTION_ATTACK3;

	int nowDir = GetDirection();
	if (nowDir == dfDIR_LEFT)
	{
		//SetDirection(dfDIR_LEFT);
		SetSprite(e_SPRITE::ePLAYER_ATTACK3_L01, e_SPRITE::ePLAYER_ATTACK3_L_MAX, dfDELAY_ATTACK3);
	}
	else
	{
		//SetDirection(dfDIR_RIGHT);
		SetSprite(e_SPRITE::ePLAYER_ATTACK3_R01, e_SPRITE::ePLAYER_ATTACK3_R_MAX, dfDELAY_ATTACK3);
	}
}

void CPlayerObject::SetActionMove(DWORD action)
{
	// 원래 걷기 동작이 아니었거나, 방향이 바뀐 경우라면
	// 이동 스프라이트로 새로 바꿔준다.
	if (!(dfACTION_MOVE_LL <= _dwActionCur && dfACTION_MOVE_LD >= _dwActionCur) || _iDirOld != _iDirCur)
	{
		//SetDirection(_iDirCur);

		if (dfDIR_LEFT == GetDirection())
		{
			SetSprite(ePLAYER_MOVE_L01, ePLAYER_MOVE_L_MAX, dfDELAY_MOVE);
		}
		else
		{
			SetSprite(ePLAYER_MOVE_R01, ePLAYER_MOVE_R_MAX, dfDELAY_MOVE);
		}
	}

	//wcout << L"Set Action Move" << endl;
	_dwActionCur = action;
}

void CPlayerObject::SetActionStand(void)
{
	_dwActionOld = _dwActionCur;
	_dwActionCur = dfACTION_STAND;

	if (_dwActionCur == _dwActionOld)
	{
		return;
	}

	if (_iDirCur == dfDIR_LEFT)
	{
		SetSprite(e_SPRITE::ePLAYER_STAND_L01, e_SPRITE::ePLAYER_STAND_L_MAX, dfDELAY_STAND);
	}
	else
	{
		SetSprite(e_SPRITE::ePLAYER_STAND_R01, e_SPRITE::ePLAYER_STAND_R_MAX, dfDELAY_STAND);
	}
}