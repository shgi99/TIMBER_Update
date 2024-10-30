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
	guideMsg->SetOrigin(Origins::MC);
	guideMsg->SetPosition({ 1920.f / 2.f, 1080.f / 2.f + 200.f });
	guideMsg->text.setString("Choose Character !!");

	Scene::Init();
}

void SceneChooseCharacterOne::Enter()
{
	TEXTURE_MGR.Load("graphics/title.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	Scene::Enter();
}

void SceneChooseCharacterOne::Exit()
{
	TEXTURE_MGR.Unload("graphics/title.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	Scene::Exit();
}

void SceneChooseCharacterOne::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::ChooseGameMode);
	}
}

void SceneChooseCharacterOne::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
