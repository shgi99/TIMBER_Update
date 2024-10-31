#include "stdafx.h"
#include "SceneChooseCharacterOne.h"
#include "SpriteGo.h"
#include "TextGo.h"

SceneChooseCharacterOne::SceneChooseCharacterOne() : Scene(SceneIds::ChooseCharacter1P)
{
}

void SceneChooseCharacterOne::Init()
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
	guideMsg->text.setString("Choose Character !!");

	arrow = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Arrow"));
	arrow->sortingLayer = SortingLayers::UI;
	arrow->text.setCharacterSize(100);
	arrow->text.setFillColor(sf::Color(50, 205, 50));
	arrow->text.setOutlineColor(sf::Color(139, 69, 19));
	arrow->text.setOutlineThickness(10);
	arrow->SetOrigin(Origins::MC);
	arrow->text.setString("-->");
	arrow->text.setRotation(270.f);
	arrow->SetPosition({ 1920.f / 2 - 450.f, 1080.f / 2 + 100.f });

	for (int i = 0; i < _countof(texCharacter); i++)
	{
		texCharacter[i] = AddGo(new SpriteGo("graphics/player" + std::to_string(i + 1) + ".png", "Player"));
		texCharacter[i]->SetOrigin(Origins::BC);
		texCharacter[i]->SetPosition({ 1920.f / 2 + (300.f * (i - 1) - 150.f), 1080.f / 2 });
		posTexId.push_back(std::make_pair(texCharacter[i]->GetPosition(), "graphics/player" + std::to_string(i + 1) + ".png"));
	}
	Scene::Init();
}

void SceneChooseCharacterOne::Enter()
{
	TEXTURE_MGR.Load("graphics/title.png");
	TEXTURE_MGR.Load("graphics/player1.png");
	TEXTURE_MGR.Load("graphics/player2.png");
	TEXTURE_MGR.Load("graphics/player3.png");
	TEXTURE_MGR.Load("graphics/player4.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	Scene::Enter();
}

void SceneChooseCharacterOne::Exit()
{
	TEXTURE_MGR.Unload("graphics/title.png");
	TEXTURE_MGR.Unload("graphics/player1.png");
	TEXTURE_MGR.Unload("graphics/player2.png");
	TEXTURE_MGR.Unload("graphics/player3.png");
	TEXTURE_MGR.Unload("graphics/player4.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	Scene::Exit();
}

void SceneChooseCharacterOne::Release()
{
	Scene::Release();
}

void SceneChooseCharacterOne::Update(float dt)
{
	
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		if (arrowIdx < 3)
		{
			arrowIdx++;
			arrow->SetPosition(posTexId[arrowIdx].first);
			arrow->text.move({ 0.f, 100.f });
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		if (arrowIdx > 0)
		{
			arrowIdx--;
			arrow->SetPosition(posTexId[arrowIdx].first);
			arrow->text.move({ 0.f, 100.f });
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		PLAYER_MGR.SetCharacterTexId(1, posTexId[arrowIdx].second);
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}
}

void SceneChooseCharacterOne::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
