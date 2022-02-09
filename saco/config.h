//----------------------------------------------------------
//
// SA:MP Multiplayer Modification For GTA:SA
// Copyright 2004-2022 SA:MP team
//
//----------------------------------------------------------

#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_CONFIG_STRSIZE 256
#define MAX_CONFIG_ENTRIES 512

#define MAX_DIRECTIVE_NAME 40

//----------------------------------------------------

enum CONFIG_DATATYPE
{
	CONFIG_DATATYPE_NONE,
	CONFIG_DATATYPE_INT,
	CONFIG_DATATYPE_STRING,
	CONFIG_DATATYPE_FLOAT,
};

//----------------------------------------------------

typedef struct _CONFIG_ENTRY
{
	char szName[MAX_DIRECTIVE_NAME+1];
	BOOL bReadOnly;
	CONFIG_DATATYPE DataType;
	int iValue;
	float fValue;
	char *szValue;
} CONFIG_ENTRY;

//----------------------------------------------------

class CConfig
{
private:
	CONFIG_ENTRY m_Entries[MAX_CONFIG_ENTRIES];
	BOOL m_bEntrySlotState[MAX_CONFIG_ENTRIES];
	char m_szFileName[MAX_PATH+1];
	int iNumEntries;

	void AddConfigEntry(char * szName, char * wsData);

	int ReadConfigFile();
	int WriteConfigFile();

	void RecalcEntrySize();

	int FindEntry(char *szSearchName);
	int AddEntry(char *szDirectiveName);
	BOOL IsValid(char *szDirectiveName);

public:
	CConfig(char * szFileName);
	~CConfig();

	int GetInt(char *szDirectiveName);
	char* GetString(char *szDirectiveName);
	float GetFloat(char *szDirectiveName);

	BOOL SetInt(char *szDirectiveName, int iDirectiveData, BOOL bReadOnly = FALSE);
	BOOL SetString(char *szDirectiveName, char *szDirectiveData, BOOL bReadOnly = FALSE);
	BOOL SetFloat(char *szDirectiveName, float fDirectiveData, BOOL bReadOnly = FALSE);

	BOOL RemoveEntry(char *szDirectiveName);

	CONFIG_ENTRY* GetEntry(char *szDirectiveName);
	CONFIG_ENTRY* GetEntryAtIndex(int iIndex);
};

//----------------------------------------------------
