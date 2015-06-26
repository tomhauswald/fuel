/*
 * IComponent.h
 *
 *  Created on: 24.06.2015
 *      Author: HAUSWALD, Tom
 */

#ifndef CORE_GAMECOMPONENT_H_
#define CORE_GAMECOMPONENT_H_

#include <memory>
#include <map>
#include <functional>

namespace fuel
{
	class GameComponent
	{
	private:
		// Parent component
		std::shared_ptr<GameComponent> m_pParent;

		// Child components
		std::map<std::string, std::shared_ptr<GameComponent>> m_pChildren;

	public:
		/**
		 * Returns the parent component
		 */
		inline std::shared_ptr<GameComponent> &getParent(void){ return m_pParent; }

		/**
		 * Returns the child with the given name.
		 *
		 * @param name
		 * 		Child name.
		 */
		inline std::shared_ptr<GameComponent> &getChild(const std::string &name){ return m_pChildren[name]; }

		/**
		 * Perform the specified closure on all child components.
		 *
		 * @param closure
		 * 		Lambda expression to perform.
		 */
		inline void forEachChild(const std::function<void (GameComponent &child)> &closure)
		{
			// Iterate over all children
			for(auto &child : m_pChildren)
			{
				closure(*child.second);
			}
		}

		/**
		 * Updates this game component and all its children.
		 * This is called each frame.
		 *
		 * @param dt
		 * 		Time passed since last frame in seconds.
		 */
		virtual void update(float dt);

		/**
		 * Renders this game component and all its children.
		 * This is called each frame.
		 */
		virtual void render(void);

		/**
		 * Renders any overlays that need to be drawn after
		 * all fullscreen effects have been performed.
		 */
		virtual void gui(void);

		/**
		 * Destroys all children.
		 */
		virtual ~GameComponent(void);
	};
}

#endif /* CORE_GAMECOMPONENT_H_ */
