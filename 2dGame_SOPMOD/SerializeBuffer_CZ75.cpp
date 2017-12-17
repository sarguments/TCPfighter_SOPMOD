#include "stdafx.h"
#include "hoxy_Header.h"
#include "SerializeBuffer_CZ75.h"

CPacket::CPacket()
	:_bufferSize(en_PACKET::eBUFFER_DEFAULT)
{
	_buffer = (char*)malloc(_bufferSize);

	// TODO : 디버깅용
	memset(_buffer, 0x00, _bufferSize);
}

CPacket::CPacket(int iBufferSize)
	: _bufferSize(iBufferSize)
{
	_buffer = (char*)malloc(_bufferSize);

	// TODO : 디버깅용
	memset(_buffer, 0x00, _bufferSize);
}

CPacket::~CPacket()
{
	Release();
}

void CPacket::Release(void)
{
	free(_buffer);
	Clear();
}

void CPacket::Clear(void)
{
	_front = 0;
	_rear = 0;
}

int CPacket::MoveRearPos(int iSize)
{
	_rear += iSize;
	_dataSize += iSize;

	// TODO : 리턴값 의미?

	return iSize;
}

int CPacket::MoveFrontPos(int iSize)
{
	_front += iSize;
	_dataSize -= iSize;

	return iSize;
}

int CPacket::GetData(char * chpDest, int iSize)
{
	int toCopySize = iSize;

	// TODO : 예외?
	if (toCopySize > _dataSize)
	{
		toCopySize = -1;
		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
	}

	char* pSource = _buffer + _front;
	memcpy(chpDest, pSource, toCopySize);

	MoveFrontPos(toCopySize);

	return toCopySize;
}

int CPacket::PutData(char * chpSrc, int iSrcSize)
{
	int toCopySize = iSrcSize;
	int freeSize = _bufferSize - _rear;

	// TODO : 예외?
	if (toCopySize > freeSize)
	{
		toCopySize = -1;
		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
	}

	char* pDest = _buffer + _rear;
	memcpy_s(pDest, _bufferSize, chpSrc, toCopySize);

	MoveRearPos(toCopySize);

	return toCopySize;
}

CPacket & CPacket::operator<<(BYTE byValue)
{
	int toCopySize = sizeof(BYTE);
	int freeSize = _bufferSize - _rear;
	if (toCopySize > freeSize)
	{
		//toCopySize = freeSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pDest = _buffer + _rear;

	*((BYTE*)pDest) = byValue;

	//memcpy_s(pDest, _bufferSize, &byValue, toCopySize);

	MoveRearPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator<<(char chValue)
{
	int toCopySize = sizeof(char);
	int freeSize = _bufferSize - _rear;
	if (toCopySize > freeSize)
	{
		//toCopySize = freeSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pDest = _buffer + _rear;

	*((char*)pDest) = chValue;

	//memcpy_s(pDest, _bufferSize, &byValue, toCopySize);

	MoveRearPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator<<(short shValue)
{
	int toCopySize = sizeof(short);
	int freeSize = _bufferSize - _rear;
	if (toCopySize > freeSize)
	{
		//toCopySize = freeSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pDest = _buffer + _rear;

	*((short*)pDest) = shValue;

	//memcpy_s(pDest, _bufferSize, &byValue, toCopySize);

	MoveRearPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator<<(WORD wValue)
{
	int toCopySize = sizeof(WORD);
	int freeSize = _bufferSize - _rear;
	if (toCopySize > freeSize)
	{
		//toCopySize = freeSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pDest = _buffer + _rear;

	*((WORD*)pDest) = wValue;

	//memcpy_s(pDest, _bufferSize, &byValue, toCopySize);

	MoveRearPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator<<(int iValue)
{
	int toCopySize = sizeof(int);
	int freeSize = _bufferSize - _rear;
	if (toCopySize > freeSize)
	{
		//toCopySize = freeSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pDest = _buffer + _rear;

	*((int*)pDest) = iValue;

	//memcpy_s(pDest, _bufferSize, &byValue, toCopySize);

	MoveRearPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator<<(DWORD dwValue)
{
	int toCopySize = sizeof(DWORD);
	int freeSize = _bufferSize - _rear;
	if (toCopySize > freeSize)
	{
		//toCopySize = freeSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pDest = _buffer + _rear;

	*((DWORD*)pDest) = dwValue;

	//memcpy_s(pDest, _bufferSize, &byValue, toCopySize);

	MoveRearPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator<<(float fValue)
{
	int toCopySize = sizeof(float);
	int freeSize = _bufferSize - _rear;
	if (toCopySize > freeSize)
	{
		//toCopySize = freeSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pDest = _buffer + _rear;

	*((float*)pDest) = fValue;

	//memcpy_s(pDest, _bufferSize, &byValue, toCopySize);

	MoveRearPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator<<(__int64 iValue)
{
	int toCopySize = sizeof(__int64);
	int freeSize = _bufferSize - _rear;

	if (toCopySize > freeSize)
	{
		//toCopySize = freeSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pDest = _buffer + _rear;

	*((__int64*)pDest) = iValue;

	//memcpy_s(pDest, _bufferSize, &byValue, toCopySize);

	MoveRearPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator<<(double dValue)
{
	int toCopySize = sizeof(double);
	int freeSize = _bufferSize - _rear;

	// TODO : 예외?
	if (toCopySize > freeSize)
	{
		//toCopySize = freeSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);

		// TODO : 크래쉬 내려고 함
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pDest = _buffer + _rear;

	*((double*)pDest) = dValue;

	//memcpy_s(pDest, _bufferSize, &byValue, toCopySize);

	MoveRearPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator>>(BYTE & byValue)
{
	int toCopySize = sizeof(BYTE);
	if (toCopySize > _dataSize)
	{
		//toCopySize = _dataSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pSource = _buffer + _front;
	byValue = *((BYTE*)pSource);

	MoveFrontPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator>>(char & chValue)
{
	int toCopySize = sizeof(char);
	if (toCopySize > _dataSize)
	{
		//toCopySize = _dataSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pSource = _buffer + _front;
	chValue = *((char*)pSource);

	MoveFrontPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator>>(short & shValue)
{
	int toCopySize = sizeof(short);
	if (toCopySize > _dataSize)
	{
		//toCopySize = _dataSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
		CPacket* pTemp = nullptr;
		return *pTemp;
	}
	char* pSource = _buffer + _front;
	shValue = *((short*)pSource);

	MoveFrontPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator>>(WORD & wValue)
{
	int toCopySize = sizeof(WORD);
	if (toCopySize > _dataSize)
	{
		//toCopySize = _dataSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pSource = _buffer + _front;
	wValue = *((WORD*)pSource);

	MoveFrontPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator>>(int & iValue)
{
	int toCopySize = sizeof(int);
	if (toCopySize > _dataSize)
	{
		//toCopySize = _dataSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pSource = _buffer + _front;
	iValue = *((int*)pSource);

	MoveFrontPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator>>(DWORD & dwValue)
{
	int toCopySize = sizeof(DWORD);
	if (toCopySize > _dataSize)
	{
		//toCopySize = _dataSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pSource = _buffer + _front;
	dwValue = *((DWORD*)pSource);

	MoveFrontPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator>>(float & fValue)
{
	int toCopySize = sizeof(float);
	if (toCopySize > _dataSize)
	{
		//toCopySize = _dataSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pSource = _buffer + _front;
	fValue = *((float*)pSource);

	MoveFrontPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator>>(__int64 & iValue)
{
	int toCopySize = sizeof(__int64);
	if (toCopySize > _dataSize)
	{
		toCopySize = _dataSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pSource = _buffer + _front;
	iValue = *((__int64*)pSource);

	MoveFrontPos(toCopySize);

	return *this;
}

CPacket & CPacket::operator>>(double & dValue)
{
	int toCopySize = sizeof(double);

	// TODO : 예외?
	if (toCopySize > _dataSize)
	{
		//toCopySize = _dataSize;

		CCmdStart::CmdDebugText(L"Serialize Buffer Error!", false);

		// TODO : 크래쉬 내려고 함
		CPacket* pTemp = nullptr;
		return *pTemp;
	}

	char* pSource = _buffer + _front;
	dValue = *((double*)pSource);

	MoveFrontPos(toCopySize);

	return *this;
}