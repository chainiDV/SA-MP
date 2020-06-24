//----------------------------------------------------------
//
// SA:MP Multiplayer Modification For GTA:SA
// Copyright 2004-2005 SA:MP team
//
// Version: $Id: playerpool.h,v 1.10 2006/04/09 09:54:45 kyeman Exp $
//
//----------------------------------------------------------

#pragma once

//----------------------------------------------------

class CPlayerPool
{
private:

	CLocalPlayer	*m_pLocalPlayer;
	BYTE			m_byteLocalPlayerID;
	DWORD			m_dwLocalPlayerPing;

	bool			m_bPlayerSlotState[MAX_PLAYERS];
	CRemotePlayer	*m_pPlayers[MAX_PLAYERS];
	DWORD			m_dwPlayerPings[MAX_PLAYERS];

	CHAR			m_szPlayerNames[MAX_PLAYERS][MAX_PLAYER_NAME+1];
	CHAR			m_szLocalPlayerName[MAX_PLAYER_NAME+1];	
	
public:
	// Process All CPlayers
	bool Process();

	void SetLocalPlayerName(PCHAR szName) { strcpy_s(m_szLocalPlayerName,szName); };
	PCHAR GetLocalPlayerName() { return m_szLocalPlayerName; };
	PCHAR GetPlayerName(BYTE bytePlayerID) { return m_szPlayerNames[bytePlayerID]; };
	void SetPlayerName(BYTE bytePlayerID, PCHAR szName) {
		strcpy_s(m_szPlayerNames[bytePlayerID], szName);
	}

	CLocalPlayer * GetLocalPlayer() { return m_pLocalPlayer; };
	BYTE FindRemotePlayerIDFromGtaPtr(PED_TYPE * pActor);

	bool New(BYTE bytePlayerID, PCHAR szPlayerName);
	bool Delete(BYTE bytePlayerID, BYTE byteReason);

	CRemotePlayer* GetAt(BYTE bytePlayerID) {
		if(bytePlayerID > MAX_PLAYERS) { return NULL; }
		return m_pPlayers[bytePlayerID];
	};

	// Find out if the slot is inuse.
	bool GetSlotState(BYTE bytePlayerID) {
		if(bytePlayerID > MAX_PLAYERS) { return false; }
		return m_bPlayerSlotState[bytePlayerID];
	};
	
	void SetLocalPlayerID(BYTE byteID) {
		strcpy_s(m_szPlayerNames[byteID],m_szLocalPlayerName);
		m_byteLocalPlayerID = byteID;
	};

	BYTE GetLocalPlayerID() { return m_byteLocalPlayerID; };

	BYTE GetCount();

	void UpdateScore(unsigned short usPlayerId, int iScore)
	{ 
		if (usPlayerId > MAX_PLAYERS - 1)
			return;

		if (usPlayerId == m_byteLocalPlayerID) {
			m_pLocalPlayer->m_iScore = iScore;
		} else {
			if (m_pPlayers[usPlayerId] != NULL)
				m_pPlayers[usPlayerId]->m_iScore = iScore;
		}
	};

	void UpdatePing(BYTE bytePlayerId, DWORD dwPing) { 
		if (bytePlayerId == m_byteLocalPlayerID)
		{
			m_dwLocalPlayerPing = dwPing;
		} else {
			if (bytePlayerId > MAX_PLAYERS-1) { return; }
			m_dwPlayerPings[bytePlayerId] = dwPing;
		}
	};

	int GetLocalPlayerScore() {
		return m_pLocalPlayer->m_iScore;
	};

	// Used in scoreboard.cpp, and array index gets checked by GetSlotState()
	int GetPlayerScore(BYTE bytePlayerId) {
		return m_pPlayers[bytePlayerId]->m_iScore;
	};

	DWORD GetLocalPlayerPing() {
		return m_dwLocalPlayerPing;
	};

	DWORD GetPlayerPing(BYTE bytePlayerId)
	{
		if (bytePlayerId > MAX_PLAYERS-1) { return 0; }
		return m_dwPlayerPings[bytePlayerId];
	};

	void DeactivateAll();

	CPlayerPool();
	~CPlayerPool();
};

//----------------------------------------------------