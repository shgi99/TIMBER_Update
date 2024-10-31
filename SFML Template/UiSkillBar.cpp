#include "stdafx.h"
#include "UiSkillBar.h"

UiSkillBar::UiSkillBar(const std::string& name)
	:GameObject(name)
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = -1;
}

void UiSkillBar::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	shape.setPosition(pos);
}

void UiSkillBar::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	shape.setScale(scale);
}

void UiSkillBar::SetOrigin(Origins preset)
{
	originPreset = preset;
	Utils::SetOrigin(shape, preset);
}

void UiSkillBar::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	shape.setOrigin(newOrigin);
}

void UiSkillBar::Reset()
{
	SetValue(0.f);
}

void UiSkillBar::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void UiSkillBar::Set(const sf::Vector2f size, const sf::Color& color)
{
	shape.setSize(size);
	shape.setFillColor(color);
	SetValue(0.f);
}

void UiSkillBar::SetValue(int value)
{
	shape.setSize({ value * 30.f, 30.f });
}
