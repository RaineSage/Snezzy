#pragma region SDL2 include
#include <SDL.h>
#pragma endregion

#pragma region project include
#include "Helper.h"
#pragma endregion

// get parent directory of path
string GetParentDirectory(string _path, int _depth)
{
	// depth higher one
	if (_depth > 1)
		_path = GetParentDirectory(_path, _depth - 1);

	// position of last sub
	size_t pos = _path.find_last_of("\\/");

	// return parent path
	return string::npos == pos ? "" : _path.substr(0, pos);
}

// get complete asset path
string GetAssetPath(const char* _pPath, int _depth)
{
	// get parent path minus bin/platform/configuration
	string path = GetParentDirectory(SDL_GetBasePath(), _depth);

	// append asset and given path
	path.append("/Assets/").append(_pPath);

	// return absolute asset path
	return path;
}