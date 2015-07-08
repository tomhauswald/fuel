/*****************************************************************
 * ShaderManager.h
 *****************************************************************
 * Created on: 23.06.2015
 * Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef CORE_SHADERMANAGER_H_
#define CORE_SHADERMANAGER_H_

#include "ResourceManager.h"
#include "../graphics/shaders/GLShaderProgram.h"

namespace fuel
{
	class ShaderManager : public ResourceManager<std::string, GLShaderProgram>
	{
	public:
		/**
		 * Adds a shader program to the list.
		 *
		 * @param key
		 * 		Shader name.
		 * @param vertShaderFile
		 * 		Vertex shader source file.
		 * @param fragShaderFile
		 *		Fragment shader source file.
		 */
		void add(const std::string &key, const std::string &vertShaderFile, const std::string &fragShaderFile)
		{
			m_resources.insert(std::make_pair(key, std::make_shared<GLShaderProgram>()));
			m_resources[key]->setShader(EGLShaderType::VERTEX, 	 vertShaderFile);
			m_resources[key]->setShader(EGLShaderType::FRAGMENT, fragShaderFile);
		}
	};
}


#endif // CORE_SHADERMANAGER_H_
