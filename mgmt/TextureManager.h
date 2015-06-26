/*
 * TextureManager.h
 *
 *  Created on: 24.06.2015
 *      Author: HAUSWALD, Tom
 */

#ifndef MGMT_TEXTUREMANAGER_H_
#define MGMT_TEXTUREMANAGER_H_

#include "ResourceManager.h"
#include "../graphics/GLTexture.h"

namespace fuel
{
	/**
	 * Manages loaded textures.
	 */
	class TextureManager : public ResourceManager<std::string, GLTexture>
	{
	public:
		/**
		 * Loads a texture from the designated file.
		 *
		 * @param key
		 * 		Resource key.
		 *
		 * @param filename
		 * 		Texture file name.
		 */
		void add(const std::string &key, const std::string &filename)
		{
			m_resources.insert(std::make_pair(key, std::make_shared<GLTexture>(filename)));
		}
	};
}

#endif /* MGMT_TEXTUREMANAGER_H_ */
