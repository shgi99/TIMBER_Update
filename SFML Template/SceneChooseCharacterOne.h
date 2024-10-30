#pragma once
#include "Scene.h"
class SceneChooseCharacterOne :
    public Scene
{
protected:
public:
	SceneChooseCharacterOne();
	virtual ~SceneChooseCharacterOne() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

