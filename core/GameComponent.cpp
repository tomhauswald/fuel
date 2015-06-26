/*
 * GameComponent.cpp
 *
 *  Created on: 24.06.2015
 *      Author: HAUSWALD, Tom
 */

#include "Game.h"
#include "GameComponent.h"
#include <iostream>

namespace fuel
{
	using namespace std;

	void GameComponent::update(Game &game, float dt)
	{
		for(auto &child : m_pChildren)
			child.second->update(game, dt);
	}

	void GameComponent::render(Game &game)
	{
		for(auto &child : m_pChildren)
			child.second->render(game);
	}

	void GameComponent::gui(Game &game)
	{
		for(auto &child : m_pChildren)
			child.second->gui(game);
	}
}


