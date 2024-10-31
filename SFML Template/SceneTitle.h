#pragma once
#include "Scene.h"
class SceneTitle : public Scene
{
protected:
public:
	SceneTitle();
	virtual ~SceneTitle() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Release() override;
	void Draw(sf::RenderWindow& window) override;
};

