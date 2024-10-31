#pragma once
#include "Scene.h"
class TextGo;
class SceneChooseCharacterOne :
    public Scene
{
protected:
	TextGo* arrow = nullptr;
	int arrowIdx = 0;
	GameObject* texCharacter[4];
	std::vector<std::pair<sf::Vector2f, std::string>> posTexId;
public:
	SceneChooseCharacterOne();
	virtual ~SceneChooseCharacterOne() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Release() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

