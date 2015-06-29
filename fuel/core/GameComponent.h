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
	class Game;

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
		inline std::shared_ptr<GameComponent> getParent(void){ return m_pParent; }

		/**
		 * Returns the child with the given name.
		 *
		 * @param name
		 * 		Child name.
		 */
		inline std::shared_ptr<GameComponent> getChild(const std::string &name){ return m_pChildren[name]; }

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
		 * Adds a child to this game component.
		 *
		 * @param name
		 * 		Name of the child for later referral.
		 *
		 * @param child
		 * 		Child object.
		 */
		inline void addChild(const std::string &name, std::shared_ptr<GameComponent> child)
		{
			std::shared_ptr<GameComponent> gc(child);
			m_pChildren.insert({name, gc});
		}

		/**
		 * Updates this game component and all its children.
		 * This is called each frame.
		 *
		 * @param game
		 * 		Parent game.
		 *
		 * @param dt
		 * 		Time passed since last frame in seconds.
		 */
		virtual void update(Game &game, float dt);

		/**
		 * Renders the geometry of this game component and all its children.
		 * This is called each frame.
		 *
		 * @param game
		 * 		Parent game.
		 */
		virtual void geometryPass(Game &game);

		/**
		 * Renders the fullscreen passes of this game component and all its children.
		 * This is called each frame after the geometry passes.
		 *
		 * @param game
		 * 		Parent game.
		 */
		virtual void fullscreenPass(Game &game);

		/**
		 * Renders any overlays that need to be drawn after
		 * all fullscreen effects have been performed.
		 *
		 * @param game
		 * 		Parent game.
		 */
		virtual void guiPass(Game &game);

		/**
		 * Destroys all children.
		 */
		virtual ~GameComponent(void) = default;
	};
}

#endif /* CORE_GAMECOMPONENT_H_ */
