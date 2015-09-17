#include <iostream>
#include <Windows.h>
#include <SetupAPI.h>
#include <stdio.h>
#include <tchar.h>
#include <cfgmgr32.h>

#pragma comment (lib, "Setupapi.lib")

using namespace std;

**/
учусь пользоваться Git
**/
**/
новое изменение
**/
lalalalalala

int main()
{ 
	HDEVINFO DeviceInfoSet;
	_SP_DEVINFO_DATA DeviceInfoData;
	DWORD DeviceIndex, dwPropertyRegDataType, dwSize;
	TCHAR szDesc[1024], szHardwareIDs[4096], ms[10];
	CONFIGRET status;
	TCHAR szDeviceInstanceID [MAX_DEVICE_ID_LEN];

	DeviceInfoSet = SetupDiGetClassDevs(
		NULL,
		TEXT("PCI"),
		NULL,
		DIGCF_PRESENT|DIGCF_ALLCLASSES);

	if(DeviceInfoSet == INVALID_HANDLE_VALUE)
	{
		return 1;
	}

	ZeroMemory(&DeviceInfoData, sizeof(SP_DEVINFO_DATA));
	DeviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	DeviceIndex = 0;

	while (SetupDiEnumDeviceInfo(
		DeviceInfoSet,
		DeviceIndex,
		&DeviceInfoData)) 
	{
		DeviceIndex ++;

		if (SetupDiGetDeviceRegistryProperty (DeviceInfoSet, &DeviceInfoData, SPDRP_DEVICEDESC,
			&dwPropertyRegDataType, (BYTE*)szDesc,
			sizeof(szDesc),   // The size, in bytes
			&dwSize))
			_tprintf (TEXT("    Device ID: \"%s\"\n"), szDesc);

		if (SetupDiGetDeviceRegistryProperty (DeviceInfoSet, &DeviceInfoData, SPDRP_MFG,
			&dwPropertyRegDataType, (BYTE*)szHardwareIDs,
			sizeof(szHardwareIDs),    // The size, in bytes
			&dwSize))
			_tprintf (TEXT("    Vendor ID: \"%s\"\n"), szHardwareIDs);
		if (SetupDiGetDeviceRegistryProperty (DeviceInfoSet, &DeviceInfoData, SPDRP_HARDWAREID,
			&dwPropertyRegDataType, (BYTE*)szHardwareIDs,
			sizeof(szHardwareIDs),    // The size, in bytes
			&dwSize)) /*{
				LPCTSTR pszId;
				_tprintf (TEXT("    Hardware IDs:\n"));
				for (pszId=szHardwareIDs;
					*pszId != TEXT('\0') && pszId + dwSize/sizeof(TCHAR) <= szHardwareIDs + ARRAYSIZE(szHardwareIDs);
					pszId += lstrlen(pszId)+1) {

						_tprintf (TEXT("        \"%s\"\n"), pszId);
				}
		}*/
						for(int i = 0; i < 4; i++)
				{
					ms[i] = szHardwareIDs[i + 8];
					ms[i + 1] = TEXT('\0');
				}
				_tprintf (TEXT("    Device ID: \"0x%s\"\n"), ms);
			    for(int i = 0; i < 4; i++)
				{
					ms[i] = szHardwareIDs[i + 17];
					ms[i + 1] = TEXT('\0');
				}
				_tprintf (TEXT("    Vendor ID: \"0x%s\"\n\n"), ms);
	}
	cout << "Number:" << DeviceIndex << endl;
	system("pause");
	if (DeviceInfoSet)
	{
		SetupDiDestroyDeviceInfoList(DeviceInfoSet);
	}
	return 0;
}