#include "ImageLoader.h"

namespace WoS
{
ImageLoader &ImageLoader::GetInstance()
{
	static ImageLoader imageLoader;
	return imageLoader;
}
} // namespace WoS
