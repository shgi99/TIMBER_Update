#include "stdafx.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "TextGo.h"

SceneTitle::SceneTitle() : Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
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
	guideMsg->text.setFillColor(sf::Color (50, 205, 50));
	guideMsg->text.setOutlineColor(sf::Color (139, 69, 19));
	guideMsg->text.setOutlineThickness(10);
	guideMsg->SetOrigin(Origins::MC);
	guideMsg->SetPosition({ 1920.f / 2.f, 1080.f / 2.f + 200.f });
	guideMsg->text.setString("Press Enter To Start !!");

	Scene::Init();
}

void SceneTitle::Enter()
{
	TEXTURE_MGR.Load("graphics/title.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	Scene::Enter();
}

void SceneTitle::Exit()
{
	TEXTURE_MGR.Unload("graphics/title.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	Scene::Exit();
}

void SceneTitle::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::ChooseGameMode);
	}
}

void SceneTitle::Release()
{
	Scene::Release();
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
