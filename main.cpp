#include "main.hpp"
#include "windows.h"
CVSPlugin g_VSPlugin;
EXPOSE_SINGLE_INTERFACE_GLOBALVAR(CVSPlugin, IServerPluginCallbacks,INTERFACEVERSION_ISERVERPLUGINCALLBACKS,g_VSPlugin)

CVSPlugin::CVSPlugin() : m_iClientCommandIndex(0)
{
}

CVSPlugin::~CVSPlugin()
{
}

// jnz -> jz
UINT8 patch_a2s[] = { 0x75 };

// xor eax, eax
// ret
UINT8 patch_forcenew[] = { 0x31, 0xc0, 0xc3 };

// cmp eax, eax
// nop
// nop
UINT8 patch_forcenew_inline[] = { 0x39 , 0xc0, 0x90, 0x90 };

void Patch(void* addr, UINT8* arr, int ops) {
	DWORD p;
	VirtualProtect(addr, ops, PAGE_EXECUTE_READWRITE, &p);
	memcpy(addr, arr, ops);
	VirtualProtect(addr, ops, p, &p);
}

bool CVSPlugin::Load(CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory)
{
	HMODULE engine = GetModuleHandle("engine.dll");
	void* topatch_a2s = (char*)engine + 0xAF93;
	void* topatch_forcenew = (char*)engine + 0x1773A0;
	Patch(topatch_a2s, patch_a2s, sizeof(patch_a2s));
	Patch(topatch_forcenew, patch_forcenew, sizeof(patch_forcenew));
	//201773C8
	void* topatch_inline = (char*)engine + 0x1773C8;
	Patch(topatch_inline, patch_forcenew_inline, sizeof(patch_forcenew_inline));
	topatch_inline = (char*)engine + 0x1785C6;
	Patch(topatch_inline, patch_forcenew_inline, sizeof(patch_forcenew_inline));
	topatch_inline = (char*)engine + 0x17873B;
	Patch(topatch_inline, patch_forcenew_inline, sizeof(patch_forcenew_inline));
	return true;
}

void CVSPlugin::Unload(void)
{
}


void CVSPlugin::Pause(void)
{
}

void CVSPlugin::UnPause(void)
{
}

const char* CVSPlugin::GetPluginDescription(void)
{
	return "";
}

void CVSPlugin::LevelInit(char const* pMapName)
{
}

void CVSPlugin::ServerActivate(edict_t* pEdictList, int edictCount, int clientMax)
{
}

void CVSPlugin::GameFrame(bool simulating)
{
}

void CVSPlugin::LevelShutdown(void)
{
}

void CVSPlugin::ClientActive(edict_t* pEntity)
{
}

void CVSPlugin::ClientDisconnect(edict_t* pEntity)
{
}

void CVSPlugin::ClientPutInServer(edict_t* pEntity, char const* playername)
{
}

void CVSPlugin::SetCommandClient(int index)
{
}

void CVSPlugin::ClientSettingsChanged(edict_t* pEdict)
{
}

PLUGIN_RESULT CVSPlugin::ClientConnect(bool* bAllowConnect, edict_t* pEntity, const char* pszName, const char* pszAddress, char* reject, int maxrejectlen)
{
	return PLUGIN_CONTINUE;
}

PLUGIN_RESULT CVSPlugin::ClientCommand(edict_t* pEntity)
{
	return PLUGIN_CONTINUE;
}

PLUGIN_RESULT CVSPlugin::NetworkIDValidated(const char* pszUserName, const char* pszNetworkID)
{
	return PLUGIN_CONTINUE;
}