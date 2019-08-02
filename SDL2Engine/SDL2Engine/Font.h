#pragma once

#pragma region system include
#include <SDL_ttf.h>
#include <string>
#pragma endregion

#pragma region project include
#include "Color.h"
#include "Helper.h"
#pragma endregion

/// <summary>
/// font class
/// </summary>
class CFont
{
public:
#pragma region constructor
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_pFileName">font file name</param>
	CFont(const char* _pFileName, int _size = 12)
	{
		std::string file = GetAssetPath(_pFileName, 4);

		m_pFile = file.c_str();

		m_size = _size;

		m_pFont = TTF_OpenFont(m_pFile, m_size);
	}
#pragma endregion

#pragma region destructor
	/// <summary>
	/// destructor
	/// </summary>
	~CFont()
	{
		TTF_CloseFont(m_pFont);
	}
#pragma endregion

#pragma region public inline function
	/// <summary>
	/// get size of font
	/// </summary>
	/// <returns>size of font</returns>
	inline int GetSize() { return m_size; }

	/// <summary>
	/// set size of font
	/// </summary>
	/// <param name="_size">size to set</param>
	inline void SetSize(int _size)
	{
		m_size = _size;
		m_pFont = TTF_OpenFont(m_pFile, m_size);
	}

	/// <summary>
	/// get sdl font
	/// </summary>
	/// <returns>sdl font</returns>
	inline TTF_Font* GetFont() { return m_pFont; };
#pragma endregion

private:
#pragma region private primitive variable
	/// <summary>
	/// size of font
	/// </summary>
	int m_size;

	/// <summary>
	/// file name of font
	/// </summary>
	const char* m_pFile;
#pragma endregion

#pragma region private variable
	/// <summary>
	/// sdl font
	/// </summary>
	TTF_Font* m_pFont;
#pragma endregion
};