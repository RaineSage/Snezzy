#pragma once

#pragma region system include
#include <string>
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

/// <summary>
/// get parent directory of path
/// </summary>
/// <param name="_path">path</param>
/// <param name="_depth">depth to go back in folders</param>
/// <returns>parent directory as string</returns>
string GetParentDirectory(string _path, int _depth = 1);

/// <summary>
/// get complete asset path
/// </summary>
/// <param name="_pPath">path</param>
/// <param name="_depth">depth to go back in folders</param>
/// <returns>complete asset path as string</returns>
string GetAssetPath(const char* _pPath, int _depth);