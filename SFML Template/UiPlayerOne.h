#pragma once
#include "GameObject.h"
class UiPlayerOne : public GameObject
{
protected:
	sf::Sprite spriteKeyW;
	sf::Sprite spriteKeyA;
	sf::Sprite spriteKeyD;

	std::string texIdKeyW = "graphics/keyW.png";
	std::string texIdKeyA = "graphics/keyA.png";
	std::string texIdKeyD = "graphics/keyD.png";
public:
	UiPlayerOne(const std::string& name = "");
	virtual ~UiPlayerOne() = default;

	void Init() override;
	void Release() override;
	void Reset()  override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window)  override;
};

