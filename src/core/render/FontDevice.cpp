#include "FontDevice.h"

FontDevice& FontDevice::GetInstance()
{
	static FontDevice instance;
	return instance;
}

FT_Library FontDevice::GetLibrary() const
{
	return _library;
}

FontDevice::FontDevice()
{
	if (FT_Init_FreeType(&_library)) {

	}
}

FontDevice::~FontDevice()
{
	if (FT_Done_FreeType(_library)) {

	}
}
