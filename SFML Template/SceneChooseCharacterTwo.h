#pragma once
#include "Scene.h"
class TextGo;
class SceneChooseCharacterTwo :
	public Scene
{
protected:
	TextGo* arrows[2];
	int arrowOneIdx = 0;
	int arrowTwoIdx = 0;
	bool isChoosePlayerOne = false;
	bool isChoosePlayerTwo = false;
	GameObject* texCharacter[4];
	std::vector<std::pair<sf::Vector2f, std::string>> posTexId;
public:
	SceneChooseCharacterTwo();
	virtual ~SceneChooseCharacterTwo() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Release() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

