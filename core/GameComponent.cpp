/*
 * GameComponent.cpp
 *
 *  Created on: 24.06.2015
 *      Author: HAUSWALD, Tom
 */

#include "GameComponent.h"
#include <iostream>

namespace fuel
{
	using namespace std;

	void GameComponent::update(float dt)
	{
		cout << "GameComponent::update(float dt)" << endl;
		forEachChild([dt](GameComponent &child)
		{
			child.update(dt);
		});
	}

	void GameComponent::render(void)
	{

		forEachChild([](GameComponent &child)
		{
			child.render();
		});
	}

	void GameComponent::gui(void)
	{
		forEachChild([](GameComponent &child)
		{
			child.gui();
		});
	}

	GameComponent::~GameComponent(void)
	{
		forEachChild([](GameComponent &child)
		{
			delete &child;
		});
	}
}


