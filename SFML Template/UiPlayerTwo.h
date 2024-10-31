#pragma once
#include "GameObject.h"
class UiPlayerTwo : public GameObject
{
protected:
	sf::Sprite spriteKeyLeft;
	sf::Sprite spriteKeyRight;
	sf::Sprite spriteKeyUp;

	std::string texIdKeyLeft = "graphics/keyLeft.png";
	std::string texIdKeyRight = "graphics/keyRight.png";
	std::string texIdKeyUp = "graphics/keyUp.png";
public:
	UiPlayerTwo(const std::string& name = "");
	virtual ~UiPlayerTwo() = default;

	void Init() override;
	void Release() override;
	void Reset()  override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window)  override;
};

