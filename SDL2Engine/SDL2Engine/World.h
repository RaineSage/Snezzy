#pragma once

#include <string>

#pragma region project include
#include "TexturedEntity.h" 
#pragma endregion

using namespace std;

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

private:
#pragma region private function
	string LoadWorldFromImage(const char* _pFileName);
#pragma endregion

};