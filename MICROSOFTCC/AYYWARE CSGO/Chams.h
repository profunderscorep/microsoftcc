#pragma once
#include "SDK.h"

void InitKeyValues(KeyValues* keyValues, char* name);

void InitKeyValues(KeyValues* keyValues, const char* name);

void LoadFromBuffer(KeyValues* keyValues, char const *resourceName, const char *pBuffer);

void LoadFromBuffer2(KeyValues* keyValues, char const* resourceName, const char* pBuffer);

void ForceMaterial(Color color, IMaterial* material, bool useColor = true, bool forceMaterial = true);

IMaterial *CreateMaterial(bool shouldIgnoreZ, bool isLit = true, bool isWireframe = false);

IMaterial* CreateMaterial(std::string type, std::string texture, bool ignorez, bool nofog, bool model, bool nocull, bool halflambert);