/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  NppSnippets - Code Snippets plugin for Notepad++                       //
//  Copyright (C) 2010-2016 Frank Fesevur                                  //
//                                                                         //
//  This program is free software; you can redistribute it and/or modify   //
//  it under the terms of the GNU General Public License as published by   //
//  the Free Software Foundation; either version 2 of the License, or      //
//  (at your option) any later version.                                    //
//                                                                         //
//  This program is distributed in the hope that it will be useful,        //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of         //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           //
//  GNU General Public License for more details.                           //
//                                                                         //
//  You should have received a copy of the GNU General Public License      //
//  along with this program; if not, write to the Free Software            //
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.              //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "Options.h"
#include "NPP/PluginInterface.h"
#include "NppSnippets.h"
#include "Version.h"

/////////////////////////////////////////////////////////////////////////////
// Strings used in the ini file

static WCHAR s_szOptions[]			= L"Options";
static WCHAR s_szShow[]				= L"Show";
static WCHAR s_szToolbarIcon[]		= L"ToolbarIcon";
static WCHAR s_szVersion[]			= L"Version";
static WCHAR s_szDBPath[]			= L"DBPath";
static WCHAR s_szDBFile[]			= L"DBFile";

/////////////////////////////////////////////////////////////////////////////
// Constructor: read the settings

Options::Options() : NppOptions()
{
	// First make sure the paths are empty
	_szPrevVersion[0] = 0;
	_szDBFile[0] = 0;

	// Read the settings from the file
	Read();
}

/////////////////////////////////////////////////////////////////////////////
// Destructor: write the settings

Options::~Options()
{
	Write();
}

/////////////////////////////////////////////////////////////////////////////
// Write the options to the ini-file

void Options::Write()
{
	WriteBool(s_szOptions, s_szShow, showConsoleDlg);
	WriteBool(s_szOptions, s_szToolbarIcon, toolbarIcon);
	WriteString(s_szOptions, s_szVersion, VERSION_NUMBER_WSTR);
}

/////////////////////////////////////////////////////////////////////////////
// Read the options from the ini-file

void Options::Read()
{
	showConsoleDlg = GetBool(s_szOptions, s_szShow, true);
	toolbarIcon = GetBool(s_szOptions, s_szToolbarIcon, true);
	GetString(s_szOptions, s_szVersion, _szPrevVersion, MAX_PATH, L"");

	// Did the user specify a special path for the database?
	GetString(s_szOptions, s_szDBFile, _szDBFile, MAX_PATH, L"");
	if (wcslen(_szDBFile) == 0)
	{
		// Try the old name of this entry
		GetString(s_szOptions, s_szDBPath, _szDBFile, MAX_PATH, L"");
	}
}
