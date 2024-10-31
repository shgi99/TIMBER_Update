#include "stdafx.h"
#include "SceneChooseGameMode.h"
#include "SpriteGo.h"
#include "TextGo.h"

SceneChooseGameMode::SceneChooseGameMode() : Scene(SceneIds::ChooseGameMode)
{
}

void SceneChooseGameMode::Init()
{

	GameObject* title = AddGo(new SpriteGo("graphics/title.png", "Title"));
	title->sortingLayer = SortingLayers::Background;
	title->sortingOrder = -1;
	title->SetScale({ 1.9f, 1.9f });
	title->SetOrigin(Origins::MC);
	title->SetPosition({ 1920 / 2, 1080 / 2 });

	chooseBox[0] = AddGo(new UiTimebar("Choose Box 1"));
	chooseBox[0]->Set({ 400.f, 600.f }, sf::Color(50, 205, 50));
	chooseBox[0]->SetOrigin(Origins::MC);
	chooseBox[0]->SetPosition({1920.f / 2 - 300.f, 1080.f / 2});

	chooseBox[1] = AddGo(new UiTimebar("Choose Box 2"));
	chooseBox[1]->Set({ 400.f, 600.f }, sf::Color(139, 69, 19));
	chooseBox[1]->SetOrigin(Origins::MC);
	chooseBox[1]->SetPosition({ 1920.f / 2 + 300.f, 1080.f / 2 });

	TextGo* guideMsg = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Guide Message"));
	guideMsg->sortingLayer = SortingLayers::UI;
	guideMsg->text.setCharacterSize(100);
	guideMsg->text.setFillColor(sf::Color(50, 205, 50));
	guideMsg->text.setOutlineColor(sf::Color(139, 69, 19));
	guideMsg->text.setOutlineThickness(10);
	guideMsg->SetOrigin(Origins::MC);
	guideMsg->SetPosition({ 1920.f / 2.f, 100.f });
	guideMsg->text.setString("Please Choose The Game Mode !!");

	GameObject* CharacterOne[2];
	for (int i = 0; i < _countof(CharacterOne); i++)
	{
		CharacterOne[i] = AddGo(new SpriteGo("graphics/player1.png", "Player"));
		CharacterOne[i]->SetOrigin(Origins::BC);
	}
	CharacterOne[0]->SetPosition({ 1920.f / 2 - 300.f, 1080.f / 2 + 100.f });
	CharacterOne[1]->SetPosition({ 1920.f / 2 + 400.f, 1080.f / 2 + 300.f });

	GameObject* CharacterTwo = AddGo(new SpriteGo("graphics/player2.png", "Player"));
	CharacterTwo->SetOrigin(Origins::BC);
	CharacterTwo->SetScale({ -1.f, 1.f });
	CharacterTwo->SetPosition({ 1920.f / 2 + 200.f, 1080.f / 2 - 100.f });

	TextGo* versus = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Guide Message"));
	versus->sortingLayer = SortingLayers::UI;
	versus->text.setCharacterSize(150);
	versus->text.setFillColor(sf::Color::Red);
	versus->text.setOutlineColor(sf::Color::Black);
	versus->text.setOutlineThickness(10);
	versus->SetOrigin(Origins::MC);
	versus->SetPosition({ 1920.f / 2 + 320.f, 1080.f / 2});
	versus->text.setString("VS");

	arrow = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Arrow"));
	arrow->sortingLayer = SortingLayers::UI;
	arrow->text.setCharacterSize(100);
	arrow->text.setFillColor(sf::Color(50, 205, 50));
	arrow->text.setOutlineColor(sf::Color(139, 69, 19));
	arrow->text.setOutlineThickness(10);
	arrow->SetOrigin(Origins::MC);
	arrow->text.setString("-->");
	arrow->text.setRotation(270.f);
	arrow->SetPosition({ 1920.f / 2 - 300.f, 1080.f / 2 + 400.f});
	isTwoPlayer = false;
	Scene::Init();
}

void SceneChooseGameMode::Release()
{
	Scene::Release();
}

void SceneChooseGameMode::Update(float dt)
{
	if (!IsTwoPlayer())
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			arrow->text.move({ 600.f, 0.f });
			isTwoPlayer = true;
		}
	}
	else
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			arrow->text.move({ -600.f, 0.f });
			isTwoPlayer = false;
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneIds::Title);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		if (!IsTwoPlayer())
		{
			SCENE_MGR.ChangeScene(SceneIds::ChooseCharacter1P);
		}
		else
		{
			SCENE_MGR.ChangeScene(SceneIds::ChooseCharacter2P);
		}
	}
	Scene::Update(dt);
}

void SceneChooseGameMode::Enter()
{
	TEXTURE_MGR.Load("graphics/title.png");
	TEXTURE_MGR.Load("graphics/player1.png");
	TEXTURE_MGR.Load("graphics/player2.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	Scene::Enter();
}

void SceneChooseGameMode::Exit()
{
	TEXTURE_MGR.Unload("graphics/title.png");
	TEXTURE_MGR.Unload("graphics/player1.png");
	TEXTURE_MGR.Unload("graphics/player2.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	Scene::Exit();
}

void SceneChooseGameMode::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneChooseGameMode::SetTwoPlayer(bool choice)
{
	isTwoPlayer = choice;
}
