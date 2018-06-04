#include "Chams.h"
#include "offsets.h"
#include "SDK.h"
#include "Interfaces.h"
#include <sstream>
//make place for ph

void InitKeyValues(KeyValues* keyValues, char* name)
{
	DWORD dwFunction = (DWORD)Offsets::Functions::KeyValues_KeyValues;
	__asm
	{
		push name
			mov ecx, keyValues
			call dwFunction
	}
}


void LoadFromBuffer(KeyValues* keyValues, char const *resourceName, const char *pBuffer)
{
	DWORD dwFunction = (DWORD)Offsets::Functions::KeyValues_LoadFromBuffer;

	__asm
	{
		push 0
			push 0
			push 0
			push pBuffer
			push resourceName
			mov ecx, keyValues
			call dwFunction
	}
}


void InitKeyValues(KeyValues* keyValues, const char* name)
{
	static DWORD sig1;
	if (!sig1)
	{
		sig1 = Utilities::Memory::FindPatternV2("client.dll", "68 ? ? ? ? 8B C8 E8 ? ? ? ? 89 45 FC EB 07 C7 45 ? ? ? ? ? 8B 03 56");
		sig1 += 7;
		sig1 = sig1 + *reinterpret_cast<PDWORD_PTR>(sig1 + 1) + 5;
	}

	static auto function = (void(__thiscall*)(KeyValues*, const char*))sig1;
	function(keyValues, name);

}

void LoadFromBuffer2(KeyValues* keyValues, char const* resourceName, const char* pBuffer)
{
	static DWORD offset;
	if (!offset) offset = Utilities::Memory::FindPatternV2("client.dll", "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04");
	static auto function = (void(__thiscall*)(KeyValues*, char const*, const char*, void*, const char*, void*))offset;
	function(keyValues, resourceName, pBuffer, 0, 0, 0);
}


IMaterial *CreateMaterial(bool shouldIgnoreZ, bool isLit, bool isWireframe) 
{
	static int created = 0;

	static const char tmp[] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$flat\" \"1\"\
		\n\t\"$nocull\" \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\" \"0\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"%i\"\
        \n}\n"
	};

	char* baseType = (isLit == true ? "VertexLitGeneric" : "UnlitGeneric");
	char material[512];
	sprintf_s(material, sizeof(material), tmp, baseType, (shouldIgnoreZ) ? 1 : 0, (isWireframe) ? 1 : 0);

	char name[512];
	sprintf_s(name, sizeof(name), "#avoz_%i.vmt", created);
	++created;
	// bullet trace with  .pcf editing?

	KeyValues* keyValues = (KeyValues*)malloc(sizeof(KeyValues));
	InitKeyValues(keyValues, baseType);
	LoadFromBuffer(keyValues, name, material);

	IMaterial *createdMaterial = Interfaces::MaterialSystem->CreateMaterial(name, keyValues);
	createdMaterial->IncrementReferenceCount();

	return createdMaterial;
}
CMaterialSystem* g_MaterialSystem;
IMaterial* CreateMaterial(std::string type, std::string texture, bool ignorez, bool nofog, bool model, bool nocull, bool halflambert)
{
	static int number = 0;
	std::stringstream materialData;
	materialData << "\"" + type + "\"\n"
		"{\n"
		"\t\"$basetexture\" \"" + texture + "\"\n"
		"\t\"$ignorez\" \"" + std::to_string(ignorez) + "\"\n"
		"\t\"$envmap\" \"" + "" + "\"\n"
		"\t\"$nofog\" \"" + std::to_string(nofog) + "\"\n"
		"\t\"$model\" \"" + std::to_string(model) + "\"\n"
		"\t\"$nocull\" \"" + std::to_string(nocull) + "\"\n"
		"\t\"$selfillum\" \"" + "1" + "\"\n"
		"\t\"$halflambert\" \"" + std::to_string(halflambert) + "\"\n"
		"\t\"$znearer\" \"" + "0" + "\"\n"
		"\t\"$flat\" \"" + "1" + "\"\n"
		"}\n" << std::flush;

	std::string materialName = "material_" + std::to_string(number) + ".vmt";
	KeyValues* keyValues = new KeyValues(materialName.c_str());
	number++;
	InitKeyValues(keyValues, type.c_str());
	LoadFromBuffer2(keyValues, materialName.c_str(), materialData.str().c_str());

	return g_MaterialSystem->CreateMaterial(materialName.c_str(), keyValues);
}
void ForceMaterial(Color color, IMaterial* material, bool useColor, bool forceMaterial)
{
	if (useColor)
	{
		float temp[3] =
		{
			color.r(),
			color.g(),
			color.b()
		};

		temp[0] /= 255.f;
		temp[1] /= 255.f;
		temp[2] /= 255.f;


		float alpha = color.a();

		Interfaces::RenderView->SetBlend(1.0f);
		Interfaces::RenderView->SetColorModulation(temp);
	}

	if (forceMaterial)
		Interfaces::ModelRender->ForcedMaterialOverride(material);
	else
		Interfaces::ModelRender->ForcedMaterialOverride(NULL);

}

