#include "ImageLoader.h"

namespace TGX
{
ImageLoader &ImageLoader::GetInstance()
{
	static ImageLoader imageLoader;
	return imageLoader;
}
} // namespace TGX
