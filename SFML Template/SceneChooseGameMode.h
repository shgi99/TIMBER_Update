#pragma once
#include "Scene.h"
#include "UiTimebar.h"
class TextGo;
class SceneChooseGameMode : public Scene
{
protected:
	UiTimebar* chooseBox[2];
	TextGo* arrow = nullptr;
	bool isTwoPlayer = false;
public:
	SceneChooseGameMode();
	virtual ~SceneChooseGameMode() = default;

	 void Init() override;
	 void Release() override;
	 void Update(float dt) override;
	 void Enter() override;
	 void Exit() override;

	 void Draw(sf::RenderWindow& window);

	bool IsTwoPlayer() const { return isTwoPlayer; }
	void SetTwoPlayer(bool choice);
};

