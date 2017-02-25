#ifndef _REGISTRY_78FC5EFB_5023_42B3_8152_168077A8FC1D_
#define _REGISTRY_78FC5EFB_5023_42B3_8152_168077A8FC1D_
#include <Shlwapi.h>
#pragma comment(lib,"Shlwapi.lib")

//HKCU (per-user settings)
#define OPT_APP_KEY _T("Software\\T800 Productions\\{ED44EF6A-79B7-4D25-92BD-B4A2C81E001D}")

#define OPT_FAVPANE  0x00000001
#define OPT_FLDRPANE  0x00000002
#define OPT_FOCUS 0x00000004
#define OPT_DEFAULTSETTINGS  0x00000000 //no option active


inline void LoadSettings(DWORD* pdwSettings)
{
	*pdwSettings=OPT_DEFAULTSETTINGS;
	DWORD dwValue;
	DWORD dwType;
	DWORD pcbData=sizeof(DWORD);
	LSTATUS ls=SHGetValue(HKEY_CURRENT_USER, OPT_APP_KEY, _T("Flags"), &dwType, (LPBYTE)(&dwValue), &pcbData);
	if (ls==ERROR_SUCCESS && dwType==REG_DWORD)
		*pdwSettings=dwValue;
}

inline BOOL ApplySettings(DWORD dwSettings)
{
return (ERROR_SUCCESS==SHSetValue(HKEY_CURRENT_USER, OPT_APP_KEY, _T("Flags"), REG_DWORD, (LPCVOID)(&dwSettings), sizeof(DWORD)));
}

#endif//_REGISTRY_78FC5EFB_5023_42B3_8152_168077A8FC1D_
