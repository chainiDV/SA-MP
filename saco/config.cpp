//----------------------------------------------------------
//
// SA:MP Multiplayer Modification For GTA:SA
// Copyright 2004-2022 SA:MP team
//
//----------------------------------------------------------

#include "main.h"

//----------------------------------------------------------

CConfig::CConfig(char * szFileName)
{
	for(int i=0; i!=MAX_CONFIG_ENTRIES;i++)
	{
		memset(&m_Entries[i], 0, sizeof(CONFIG_ENTRY));
		m_bEntrySlotState[i] = FALSE;
	}

	iNumEntries=0;

	if(szFileName && strlen(szFileName))
	{
		strcpy(m_szFileName, szFileName);

		ReadConfigFile();
	}
}

//----------------------------------------------------------

CConfig::~CConfig()
{
	for(int i=0; i != MAX_CONFIG_ENTRIES; i++)
	{
		if(m_bEntrySlotState[i])
		{
			if(m_Entries[i].szValue)
				free(m_Entries[i].szValue);
		}

		m_bEntrySlotState[i] = FALSE;
	}
}

//----------------------------------------------------------

void CConfig::RecalcEntrySize()
{
	int iNewSize=0;
	for(int i=0; i<MAX_CONFIG_ENTRIES; i++)
	{
		if(m_bEntrySlotState[i])
		{
			iNewSize=i;
		}
	}
	iNumEntries=iNewSize+1;
}

//----------------------------------------------------------

int CConfig::FindEntry(char *szSearchName)
{
	int i=0;

	strlwr(szSearchName);

	if(iNumEntries <= 0) {
		return (-1);
	}

	while(i < iNumEntries)
	{
		if(m_bEntrySlotState[i] &&
			!strcmp(szSearchName, m_Entries[i].szName))
		{
			return i;
		}
		i++;
	}

	return (-1);
}

//----------------------------------------------------------

BOOL CConfig::IsValid(char *szDirectiveName)
{
	return FindEntry(szDirectiveName) >= 0;
}

//----------------------------------------------------------

int CConfig::AddEntry(char *szDirectiveName)
{
	int i;
	for(i=0; i < MAX_CONFIG_ENTRIES; i++)
	{
		if(!m_bEntrySlotState[i]) break;
	}
	if(i==MAX_CONFIG_ENTRIES) return (-1);

	if(strlen(szDirectiveName) <= MAX_DIRECTIVE_NAME)
	{
		strlwr(szDirectiveName);

		CONFIG_ENTRY* pEntry = &m_Entries[i];
		strcpy(pEntry->szName, szDirectiveName);
		pEntry->bReadOnly = FALSE;
		pEntry->DataType = CONFIG_DATATYPE_NONE;
		
		m_bEntrySlotState[i] = TRUE;

		RecalcEntrySize();
		return i;
	}
	return (-1);
}

//----------------------------------------------------------

int CConfig::GetInt(char *szDirectiveName)
{
	int iArrayIndex = FindEntry(szDirectiveName);
	if(iArrayIndex >= 0)
	{
		CONFIG_ENTRY* pEntry = &m_Entries[iArrayIndex];
		if(pEntry->DataType == CONFIG_DATATYPE_INT)
		{
			return pEntry->iValue;
		}
	}
	return 0;
}

//----------------------------------------------------------

char* CConfig::GetString(char *szDirectiveName)
{
	int iArrayIndex = FindEntry(szDirectiveName);
	if(iArrayIndex >= 0)
	{
		CONFIG_ENTRY* pEntry = &m_Entries[iArrayIndex];
		if(pEntry->DataType == CONFIG_DATATYPE_STRING)
		{
			return pEntry->szValue;
		}
	}
	return NULL;
}

//----------------------------------------------------------

float CConfig::GetFloat(char *szDirectiveName)
{
	int iArrayIndex = FindEntry(szDirectiveName);
	if(iArrayIndex >= 0)
	{
		CONFIG_ENTRY* pEntry = &m_Entries[iArrayIndex];
		if(pEntry->DataType == CONFIG_DATATYPE_FLOAT)
		{
			return pEntry->fValue;
		}
	}
	return 0.0f;
}

//----------------------------------------------------------

BOOL CConfig::RemoveEntry(char *szDirectiveName)
{
	int iArrayIndex = FindEntry(szDirectiveName);
	if (iArrayIndex < 0) {
		return FALSE;
	}

	CONFIG_ENTRY* pEntry = &m_Entries[iArrayIndex];
	if(pEntry->szValue)
		free(pEntry->szValue);
	memset(pEntry, 0, sizeof(CONFIG_ENTRY));
	m_bEntrySlotState[iArrayIndex] = FALSE;

	RecalcEntrySize();
	return TRUE;
}

//----------------------------------------------------------

CONFIG_ENTRY* CConfig::GetEntry(char *szDirectiveName)
{
	int iArrayIndex = FindEntry(szDirectiveName);
	if (iArrayIndex >= 0)
	{
		return &m_Entries[iArrayIndex];
	}
	return NULL;
}

//----------------------------------------------------------

CONFIG_ENTRY* CConfig::GetEntryAtIndex(int iIndex)
{
	if (iIndex >= 0 && iIndex < MAX_CONFIG_ENTRIES)
	{
		if (m_bEntrySlotState[iIndex])
		{
			return &m_Entries[iIndex];
		}
	}
	return NULL;
}

//----------------------------------------------------------

CONFIG_DATATYPE DetermineDataType(char *szData)
{
	if(szData && strlen(szData)) {
		if(szData[0] == '"' && szData[strlen(szData)-1] == '"')
			return CONFIG_DATATYPE_STRING;
		else if(strchr(szData,'.') != NULL)
			return CONFIG_DATATYPE_FLOAT;
		else
			return CONFIG_DATATYPE_INT;
	}
	return CONFIG_DATATYPE_NONE;
}

//----------------------------------------------------------

int CConfig::WriteConfigFile()
{
	FILE *fWriteFile = fopen(m_szFileName,"w");

	if(!fWriteFile) {
		OutputDebugString("Failed to open config file for writing.");
		return 0;
	}

	for(int i=0; i!=MAX_CONFIG_ENTRIES; i++)
	{
		if(m_bEntrySlotState[i])
		{
			switch(m_Entries[i].DataType)
			{
				case CONFIG_DATATYPE_INT:
					fprintf(fWriteFile,"%s=%d\n",m_Entries[i].szName,m_Entries[i].iValue);
					break;

				case CONFIG_DATATYPE_STRING:
					if(m_Entries[i].szValue) {
						fprintf(fWriteFile, "%s=\"%s\"\n", m_Entries[i].szName, m_Entries[i].szValue);
					}
					break;

				case CONFIG_DATATYPE_FLOAT:
					fprintf(fWriteFile,"%s=%f\n",m_Entries[i].szName,m_Entries[i].fValue);
					break;
			}
		}
	}

	fclose(fWriteFile);

	return 1;
}

//----------------------------------------------------------

BOOL CConfig::SetInt(char *szDirectiveName, int iDirectiveData, BOOL bReadOnly)
{
	int iArrayIndex = FindEntry(szDirectiveName);
	if(iArrayIndex < 0)
	{
		iArrayIndex = AddEntry(szDirectiveName);
		if(iArrayIndex < 0)
		{
			return FALSE;
		}
	}

	CONFIG_ENTRY* pEntry = &m_Entries[iArrayIndex];

	if(bReadOnly)
	{
		pEntry->bReadOnly = TRUE;
	}
	else if(pEntry->bReadOnly)
	{
		return FALSE;
	}

	pEntry->iValue = iDirectiveData;
	pEntry->DataType = CONFIG_DATATYPE_INT;

	WriteConfigFile();
	return TRUE;
}

//----------------------------------------------------------

BOOL CConfig::SetString(char *szDirectiveName, char *szDirectiveData, BOOL bReadOnly)
{
	int iArrayIndex = FindEntry(szDirectiveName);
	if(iArrayIndex < 0)
	{
		iArrayIndex = AddEntry(szDirectiveName);
		if(iArrayIndex < 0)
		{
			return FALSE;
		}
	}

	CONFIG_ENTRY* pEntry = &m_Entries[iArrayIndex];

	if(bReadOnly)
	{
		pEntry->bReadOnly = TRUE;
	}
	else if(pEntry->bReadOnly)
	{
		return FALSE;
	}

	pEntry->DataType = CONFIG_DATATYPE_STRING;
	if(pEntry->szValue)
		free(pEntry->szValue);
	pEntry->szValue = (char*)calloc(1,strlen(szDirectiveData)+1);
	strcpy(pEntry->szValue,szDirectiveData);

	WriteConfigFile();
	return TRUE;
}

//----------------------------------------------------------

BOOL CConfig::SetFloat(char *szDirectiveName, float fDirectiveData, BOOL bReadOnly)
{
	int iArrayIndex = FindEntry(szDirectiveName);
	if(iArrayIndex < 0)
	{
		iArrayIndex = AddEntry(szDirectiveName);
		if(iArrayIndex < 0)
		{
			return FALSE;
		}
	}

	CONFIG_ENTRY* pEntry = &m_Entries[iArrayIndex];

	if(bReadOnly)
	{
		pEntry->bReadOnly = TRUE;
	}
	else if(pEntry->bReadOnly)
	{
		return FALSE;
	}

	pEntry->fValue = fDirectiveData;
	pEntry->DataType = CONFIG_DATATYPE_FLOAT;

	WriteConfigFile();
	return TRUE;
}

//----------------------------------------------------------

void CConfig::AddConfigEntry(char * szName, char * szData)
{
	unsigned int uiLen;

	switch(DetermineDataType(szData))
	{
		case CONFIG_DATATYPE_INT:
			SetInt(szName,atol(szData));
			break;

		case CONFIG_DATATYPE_STRING:
			uiLen = strlen(szData);
			strncpy(szData,szData+1,uiLen-1);
			szData[uiLen-2]='\0';
			SetString(szName,szData);
			break;

		case CONFIG_DATATYPE_FLOAT:
			SetFloat(szName,atof(szData));
			break;
	}
}

//----------------------------------------------------------

int CConfig::ReadConfigFile()
{
	char	szReadBuffer[MAX_CONFIG_STRSIZE];
	char	szDirectiveName[MAX_CONFIG_STRSIZE];
	char	szDirectiveData[MAX_CONFIG_STRSIZE];

	char	*szReadPtr;
	int		iDirectiveLength;
	int		iDirectiveDataLength;

	FILE	*fReadFile = fopen(m_szFileName,"r");

	if(!fReadFile) {
		OutputDebugString("Failed to read config file.");
		return 0;
	}

	while(!feof(fReadFile)) {
		fgets(szReadBuffer,MAX_CONFIG_STRSIZE,fReadFile);
		szReadPtr = szReadBuffer;
		iDirectiveLength = 0;
		iDirectiveDataLength = 0;

		while(*szReadPtr == ' ' || *szReadPtr == '\t') szReadPtr++;

		if( *szReadPtr == '\0' || *szReadPtr == ';' || 
			*szReadPtr == '\n' || *szReadPtr == '[' ) {

			continue;
		}

		while( *szReadPtr != '\0' && 
			 *szReadPtr != ' ' &&
			 *szReadPtr != '=' &&
			 *szReadPtr != '\n' &&
			 *szReadPtr != '\t' &&
			 *szReadPtr != ';' ) {
			szDirectiveName[iDirectiveLength] = toupper(*szReadPtr);
			iDirectiveLength++;
			szReadPtr++;
		}

		if(iDirectiveLength == 0) {
			continue;
		}

		szDirectiveName[iDirectiveLength] = '\0';

		while(*szReadPtr == ' ' || *szReadPtr == '\t') szReadPtr++;

		if(*szReadPtr != '=') {
			continue;
		}

		*szReadPtr++;

		while(*szReadPtr == ' ' || *szReadPtr == '\t') szReadPtr++;

		while( *szReadPtr != '\0' && 
			 *szReadPtr != '\n') {
			szDirectiveData[iDirectiveDataLength] = *szReadPtr;
			iDirectiveDataLength++;
			szReadPtr++;
		}

		if(iDirectiveDataLength == 0) {
			continue;
		}

		szDirectiveData[iDirectiveDataLength] = '\0';

		iDirectiveDataLength--;
		while(szDirectiveData[iDirectiveDataLength] == ' '  ||
			  szDirectiveData[iDirectiveDataLength] == '\t' ||
			  szDirectiveData[iDirectiveDataLength] == '\r')
		{
			szDirectiveData[iDirectiveDataLength] = '\0';
			iDirectiveDataLength--;
		}

		AddConfigEntry(szDirectiveName,szDirectiveData);
	}

	fclose(fReadFile);
	return 1;
}

//----------------------------------------------------------
