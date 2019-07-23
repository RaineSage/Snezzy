#pragma once

#pragma region project include
#include "TexturedEntity.h" 
#pragma endregion

/// <summary>
/// world class
/// </summary>
class GWorld : public CTexturedEntity
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFileName">relative file path name</param>
	GWorld(const char* _pFileName = nullptr)
		: CTexturedEntity(SVector2(), SVector2(), _pFileName) {}

	/// <summary>
	/// destructor
	/// </summary>
	~GWorld() {}
#pragma endregion

#pragma region public function
	/// <summary>
	/// initialize world
	/// </summary>
	void Init();
#pragma endregion
};