#include "stdafx.h"
#include "UiPlayerTwo.h"

UiPlayerTwo::UiPlayerTwo(const std::string& name) : GameObject(name)
{
	sortingLayer = SortingLayers::UI;
}

void UiPlayerTwo::Init()
{
	GameObject::Init();
	spriteKeyUp.setTexture(TEXTURE_MGR.Get(texIdKeyUp));
	SetOrigin(Origins::MC);
	spriteKeyUp.setPosition(position);
	spriteKeyUp.setScale({ 5.f, 5.f });
	spriteKeyLeft.setTexture(TEXTURE_MGR.Get(texIdKeyLeft));
	spriteKeyLeft.setPosition({ position.x - 80.f, position.y + 80.f });
	spriteKeyLeft.setScale({ 5.f, 5.f });
	spriteKeyRight.setTexture(TEXTURE_MGR.Get(texIdKeyRight));
	spriteKeyRight.setScale({ 5.f, 5.f });
	spriteKeyRight.setPosition({ position.x + 80.f, position.y + 80.f });
}

void UiPlayerTwo::Release()
{
}

void UiPlayerTwo::Reset()
{
	GameObject::Reset();
	spriteKeyUp.setTexture(TEXTURE_MGR.Get(texIdKeyUp), true);
	spriteKeyLeft.setTexture(TEXTURE_MGR.Get(texIdKeyLeft), true);
	spriteKeyRight.setTexture(TEXTURE_MGR.Get(texIdKeyRight), true);
	SetOrigin(Origins::MC);
	spriteKeyUp.setPosition(position);
	spriteKeyUp.setScale({ 5.f, 5.f });
	spriteKeyLeft.setPosition({ position.x - 80.f, position.y + 80.f });
	spriteKeyLeft.setScale({ 5.f, 5.f });
	spriteKeyRight.setScale({ 5.f, 5.f });
	spriteKeyRight.setPosition({ position.x + 60.f, position.y + 80.f });
}

void UiPlayerTwo::Update(float dt)
{
	GameObject::Update(dt);
}

void UiPlayerTwo::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	window.draw(spriteKeyLeft);
	window.draw(spriteKeyRight);
	window.draw(spriteKeyUp);
}
