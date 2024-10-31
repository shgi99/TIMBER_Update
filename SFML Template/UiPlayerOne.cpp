#include "stdafx.h"
#include "UiPlayerOne.h"

UiPlayerOne::UiPlayerOne(const std::string& name) : GameObject(name)
{
	sortingLayer = SortingLayers::UI;
}

void UiPlayerOne::Init()
{
	GameObject::Init();
	spriteKeyW.setTexture(TEXTURE_MGR.Get(texIdKeyW));
	SetOrigin(Origins::MC);
	spriteKeyW.setPosition(position);
	spriteKeyW.setScale({ 5.f, 5.f });
	spriteKeyA.setTexture(TEXTURE_MGR.Get(texIdKeyA));
	spriteKeyA.setPosition({ position.x - 80.f, position.y + 80.f });
	spriteKeyA.setScale({ 5.f, 5.f });
	spriteKeyD.setTexture(TEXTURE_MGR.Get(texIdKeyD));
	spriteKeyD.setScale({ 5.f, 5.f });
	spriteKeyD.setPosition({ position.x + 80.f, position.y + 80.f });
}

void UiPlayerOne::Release()
{
}

void UiPlayerOne::Reset()
{
	GameObject::Reset();
	spriteKeyW.setTexture(TEXTURE_MGR.Get(texIdKeyW), true);
	spriteKeyA.setTexture(TEXTURE_MGR.Get(texIdKeyA), true);
	spriteKeyD.setTexture(TEXTURE_MGR.Get(texIdKeyD), true);
	SetOrigin(Origins::MC);
	spriteKeyW.setPosition(position);
	spriteKeyW.setScale({ 5.f, 5.f });
	spriteKeyA.setPosition({ position.x - 80.f, position.y + 80.f });
	spriteKeyA.setScale({ 5.f, 5.f });
	spriteKeyD.setScale({ 5.f, 5.f });
	spriteKeyD.setPosition({ position.x + 80.f, position.y + 80.f });
}

void UiPlayerOne::Update(float dt)
{
	GameObject::Update(dt);
}

void UiPlayerOne::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	window.draw(spriteKeyA);
	window.draw(spriteKeyD);
	if (PLAYER_MGR.GetCharacterTexId(2) != "")
	{
		window.draw(spriteKeyW);
	}
}



