#include "BaseObject.h"

BaseObject::BaseObject()
{
	object = NULL;
}
BaseObject::~BaseObject()
{
	if (object != NULL)
		SDL_FreeSurface(object);
}
void  BaseObject::LoadImg(string name)
{
	object = LoadImage(name);
}
void BaseObject::Show(SDL_Surface* des)
{
	if(object!=NULL)
		//ApplySurface(object, des, rect.X(), rect.Y());
	if (object != NULL)
	{
		UINT32 color_key = SDL_MapRGB(object->format, 0xFF, 0xFF, 0xFF);
		//SDL_SetColorKey(object, SDL_SRCCOLORKEY, color_key);
	}
}

