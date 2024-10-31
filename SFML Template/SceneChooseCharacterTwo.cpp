#include "stdafx.h"
#include "SceneChooseCharacterTwo.h"
#include "SpriteGo.h"
#include "TextGo.h"

SceneChooseCharacterTwo::SceneChooseCharacterTwo() : Scene(SceneIds::ChooseCharacter2P)
{
}

void SceneChooseCharacterTwo::Init()
{
	GameObject* title = AddGo(new SpriteGo("graphics/title.png", "Title"));
	title->sortingLayer = SortingLayers::Background;
	title->sortingOrder = -1;
	title->SetScale({ 1.9f, 1.9f });
	title->SetOrigin(Origins::MC);
	title->SetPosition({ 1920 / 2, 1080 / 2 });

	TextGo* guideMsg = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Guide Message"));
	guideMsg->sortingLayer = SortingLayers::UI;
	guideMsg->text.setCharacterSize(100);
	guideMsg->text.setFillColor(sf::Color(50, 205, 50));
	guideMsg->text.setOutlineColor(sf::Color(139, 69, 19));
	guideMsg->text.setOutlineThickness(10);
	guideMsg->SetPosition({ 1920.f / 2, 100.f });
	guideMsg->SetOrigin(Origins::MC);
	guideMsg->text.setString("Choose 2 Character !!");

	for (int i = 0; i < _countof(texCharacter); i++)
	{
		texCharacter[i] = AddGo(new SpriteGo("graphics/player" + std::to_string(i + 1) + ".png", "Player"));
		texCharacter[i]->SetOrigin(Origins::BC);
		texCharacter[i]->SetPosition({ 1920.f / 2 + (300.f * (i - 1) - 150.f), 1080.f / 2 });
		posTexId.push_back(std::make_pair(texCharacter[i]->GetPosition(), "graphics/player" + std::to_string(i + 1) + ".png"));
	}
	for (int i = 0; i < _countof(arrows); i++)
	{
		arrows[i] = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Arrow"));
		arrows[i]->sortingLayer = SortingLayers::UI;
		arrows[i]->text.setCharacterSize(100);
		arrows[i]->text.setOutlineThickness(10);
		arrows[i]->SetOrigin(Origins::MC);
		arrows[i]->text.setString("-->");
		arrows[i]->text.setRotation(270.f - (180.f * i));
	}
	arrows[0]->SetPosition({ posTexId[0].first.x, posTexId[0].first.y + 100.f });
	arrows[0]->text.setFillColor(sf::Color(50, 205, 50));
	arrows[0]->text.setOutlineColor(sf::Color(139, 69, 19));
	arrows[1]->SetPosition({ posTexId[0].first.x, posTexId[0].first.y - 300.f });
	arrows[1]->text.setFillColor(sf::Color(139, 69, 19));
	arrows[1]->text.setOutlineColor(sf::Color(50, 205, 50));
	Scene::Init();
}

void SceneChooseCharacterTwo::Enter()
{
	TEXTURE_MGR.Load("graphics/title.png");
	TEXTURE_MGR.Load("graphics/player1.png");
	TEXTURE_MGR.Load("graphics/player2.png");
	TEXTURE_MGR.Load("graphics/player3.png");
	TEXTURE_MGR.Load("graphics/player4.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	Scene::Enter();
}

void SceneChooseCharacterTwo::Exit()
{
	TEXTURE_MGR.Unload("graphics/title.png");
	TEXTURE_MGR.Unload("graphics/player1.png");
	TEXTURE_MGR.Unload("graphics/player2.png");
	TEXTURE_MGR.Unload("graphics/player3.png");
	TEXTURE_MGR.Unload("graphics/player4.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	Scene::Exit();
}

void SceneChooseCharacterTwo::Release()
{
	Scene::Release();
}

void SceneChooseCharacterTwo::Update(float dt)
{
	if(!isChoosePlayerOne)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			if (arrowOneIdx < 3)
			{
				arrowOneIdx++;
				arrows[0]->SetPosition(posTexId[arrowOneIdx].first);
				arrows[0]->text.move({ 0.f, 100.f });
			}
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			if (arrowOneIdx > 0)
			{
				arrowOneIdx--;
				arrows[0]->SetPosition(posTexId[arrowOneIdx].first);
				arrows[0]->text.move({ 0.f, 100.f });
			}
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		PLAYER_MGR.SetCharacterTexId(1, posTexId[arrowOneIdx].second);
		isChoosePlayerOne = !isChoosePlayerOne;
		if (isChoosePlayerOne)
		{
			arrows[0]->text.setFillColor(sf::Color::Cyan);
		}
		else
		{
			arrows[0]->text.setFillColor(sf::Color(50, 205, 50));
		}
	}

	if(!isChoosePlayerTwo)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::D))
		{
			if (arrowTwoIdx < 3)
			{
				arrowTwoIdx++;
				arrows[1]->SetPosition(posTexId[arrowTwoIdx].first);
				arrows[1]->text.move({ 0.f, -300.f });
			}
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::A))
		{
			if (arrowTwoIdx > 0)
			{
				arrowTwoIdx--;
				arrows[1]->SetPosition(posTexId[arrowTwoIdx].first);
				arrows[1]->text.move({ 0.f, -300.f });
			}
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		PLAYER_MGR.SetCharacterTexId(2, posTexId[arrowTwoIdx].second);
		isChoosePlayerTwo = !isChoosePlayerTwo;
		if (isChoosePlayerTwo)
		{
			arrows[1]->text.setFillColor(sf::Color::Cyan);
		}
		else
		{
			arrows[1]->text.setFillColor(sf::Color(139, 69, 19));
		}
	}
	if (isChoosePlayerOne && isChoosePlayerTwo)
	{
		// æ¿ √º¿Œ¡ˆ
	}
}

void SceneChooseCharacterTwo::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
