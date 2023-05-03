/*
Copyright (C) 2022 Bien Pham

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

In addition, as a special exception, the author gives permission
to link the code of this program with VGUI library developed by
Valve, L.L.C ("Valve"). You must obey the GNU General Public License
in all respects for all of the code used other than VGUI library.
If you modify this file, you may extend this exception to your
version of the file, but you are not obligated to do so. If
you do not wish to do so, delete this exception statement
from your version.
*/
#include <locale.h>
#include <crtlib.h>
#include "VGui2Interfaces.h"
#include "KeyValues.h"

static IKeyValues *keyValuesInterface;
static IFileSystem *fileSystemInterface;

IKeyValues *keyvalues()
{
	return keyValuesInterface;
}

namespace vgui2
{
static IVGui *vguiInterface;
static ILocalize *localizeInterface;
static IPanel *panelInterface;
static ISurface *surfaceInterface;
static ISchemeManager *schemeManagerInterface;
static ISystem *systemInterface;
static IInput *inputInterface;
static IInputInternal *inputInternalInterface;
static char moduleName[256];

IVGui *ivgui()
{
	return vguiInterface;
}

ILocalize *localize()
{
	return localizeInterface;
}

IFileSystem *filesystem()
{
	return fileSystemInterface;
}

IPanel *ipanel()
{
	return panelInterface;
}

ISurface *surface()
{
	return surfaceInterface;
}

ISchemeManager *scheme()
{
	return schemeManagerInterface;
}

ISystem *system()
{
	return systemInterface;
}

IInput *input()
{
	return inputInterface;
}

IInputInternal *inputinternal()
{
	return inputInternalInterface;
}

bool InitializeVGui2Interfaces( const char *_moduleName, CreateInterfaceFn *factories, int factoryCount )
{
	Q_strncpy( moduleName, _moduleName, sizeof( moduleName ));

	setlocale( LC_ALL, "" );
	setlocale( LC_CTYPE, "" );
	setlocale( LC_MONETARY, "" );
	setlocale( LC_NUMERIC, "" );

	struct
	{
		void **ptr;
		const char *iface;
	} interfaces[] =
	{
	{ (void **)&keyValuesInterface, KEYVALUES_INTERFACE_VERSION },
	{ (void **)&vguiInterface, VGUI_IVGUI_INTERFACE_VERSION },
	{ (void **)&localizeInterface, VGUI_LOCALIZE_INTERFACE_VERSION },
	{ (void **)&fileSystemInterface, FILESYSTEM_INTERFACE_VERSION },
	{ (void **)&panelInterface, VGUI_PANEL_INTERFACE_VERSION },
	{ (void **)&surfaceInterface, VGUI_SURFACE_INTERFACE_VERSION },
	{ (void **)&schemeManagerInterface, VGUI_SCHEME_INTERFACE_VERSION },
	{ (void **)&systemInterface, VGUI_SYSTEM_INTERFACE_VERSION },
	{ (void **)&inputInterface, VGUI_INPUT_INTERFACE_VERSION },
	{ (void **)&inputInternalInterface, VGUI_INPUT_INTERFACE_VERSION },
	};

	if( factoryCount <= 0 )
	{
		for( int i = 0; i < sizeof( interfaces ) / sizeof( interfaces[0] ); i++ )
			*interfaces[i].ptr = nullptr;

		return false;
	}

	for( int i = 0; i < factoryCount; ++i )
	{
		for( int j = 0; j < sizeof( interfaces ) / sizeof( interfaces[0] ); j++ )
		{
			if( *interfaces[j].ptr == nullptr )
				*interfaces[j].ptr = factories[i]( interfaces[j].iface, nullptr );
		}
	}

	for( int i = 0; i < sizeof( interfaces ) / sizeof( interfaces[0] ); i++ )
	{
		if( *interfaces[i].ptr == nullptr )
			return false;
	}

	vguiInterface->Init( factories, factoryCount );
	keyValuesInterface->RegisterSizeofKeyValues( sizeof( KeyValues ));

	return true;
}

const char *GetModuleName()
{
	return moduleName;
}
} // namespace vgui2
