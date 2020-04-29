#include "Hitable.h"

Hitable::Hitable(Material* material)
	: material(material)
{
}

Material* Hitable::GetMaterial() const
{
	return material;
}