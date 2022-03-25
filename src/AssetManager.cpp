#include "AssetManager.h"

namespace Blink
{
	void Blink::AssetManager::LoadTexture(std::string name, std::string filePath)
	{
		sf::Texture tex;
		if (tex.loadFromFile(filePath))
		{
			this->textures[name] = tex;
		}
	}

	sf::Texture& Blink::AssetManager::GetTexture(std::string name)
	{
		return this->textures.at(name);
	}

	void Blink::AssetManager::LoadFont(std::string name, std::string filePath)
	{
		sf::Font fnt;
		if (fnt.loadFromFile(filePath))
		{
			this->fonts[name] = fnt;
		}
	}

	sf::Font& Blink::AssetManager::GetFont(std::string name)
	{
		return this->fonts.at(name);
	}
}
