#include "stdafx.h"
#include "SceneDev1.h"
#include "SpriteGo.h"
#include "CloudGo.h"
#include "Tree.h"
#include "Player.h"
#include "TextGo.h"
#include "UiScore.h"
#include "UiTimebar.h"

SceneDev1::SceneDev1() : Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	std::cout << "SceneDev1::Init()" << std::endl;

	GameObject* obj = AddGo(new SpriteGo("graphics/background.png"));
	obj->sortingLayer = SortingLayers::Background;
	obj->sortingOrder = -1;
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 1920 / 2, 1080 / 2 });

	for (int i = 0; i < 3; ++i)
	{
		CloudGo* cloud = AddGo(new CloudGo("graphics/cloud.png"));
		cloud->sortingLayer = SortingLayers::Background;
		cloud->sortingOrder = 0;
	}

	TEXTURE_MGR.Load("graphics/tree.png");
	TEXTURE_MGR.Load("graphics/branch.png");
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/rip.png");
	TEXTURE_MGR.Load("graphics/axe.png");

	tree = AddGo(new Tree("Tree"));
	player = AddGo(new Player("Player"));


	centerMsg = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Center Message"));
	centerMsg->sortingLayer = SortingLayers::UI;

	uiScore = AddGo(new UiScore("fonts/KOMIKAP_.ttf", "Ui Score"));
	uiTimer = AddGo(new UiTimebar("Ui Timer"));

	Scene::Init();

	tree->SetPosition({ 1920.f / 2, 1080.f - 200.f });
	player->SetPosition({ 1920.f / 2, 1080.f - 200.f });

	centerMsg->text.setCharacterSize(100);
	centerMsg->text.setFillColor(sf::Color::White);
	centerMsg->SetPosition({ 1920.f / 2.f, 1080.f / 2.f });

	uiScore->text.setCharacterSize(75);
	uiScore->text.setFillColor(sf::Color::White);
	uiScore->SetPosition({ 30.f, 30.f });
	
	uiTimer->Set({ 500.f, 100.f }, sf::Color::Red);
	uiTimer->SetOrigin(Origins::ML);
	uiTimer->SetPosition({ 1920.f / 2.f - 250.f, 1080.f - 100.f });
}

void SceneDev1::Enter()
{
	TEXTURE_MGR.Load("graphics/background.png");
	TEXTURE_MGR.Load("graphics/cloud.png");
	TEXTURE_MGR.Load("graphics/tree.png");
	TEXTURE_MGR.Load("graphics/branch.png");
	TEXTURE_MGR.Load("graphics/log.png");
	TEXTURE_MGR.Load("graphics/player1.png");
	TEXTURE_MGR.Load("graphics/player2.png");
	TEXTURE_MGR.Load("graphics/player3.png");
	TEXTURE_MGR.Load("graphics/player4.png");
	TEXTURE_MGR.Load("graphics/rip.png");
	TEXTURE_MGR.Load("graphics/axe.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Load("sound/chop.wav");
	SOUNDBUFFER_MGR.Load(sbIdDeath);
	SOUNDBUFFER_MGR.Load(sbIdTimeOut);

	sfxDeath.setBuffer(SOUNDBUFFER_MGR.Get(sbIdDeath));
	sfxTimeOut.setBuffer(SOUNDBUFFER_MGR.Get(sbIdTimeOut));

	player->SetSceneGame(this);
	player->SetTexIdPlayer(PLAYER_MGR.GetCharacterTexId(1));
	Scene::Enter();

	SetStatus(Status::Awake);
}

void SceneDev1::Exit()
{
	std::cout << "SceneDev1::Exit()" << std::endl;

	player->SetSceneGame(nullptr);
	tree->ClearEffectLog();

	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/cloud.png");
	TEXTURE_MGR.Unload("graphics/background.png");
	TEXTURE_MGR.Unload("graphics/tree.png");
	TEXTURE_MGR.Unload("graphics/branch.png");
	TEXTURE_MGR.Unload("graphics/log.png");
	TEXTURE_MGR.Unload("graphics/player1.png");
	TEXTURE_MGR.Unload("graphics/player2.png");
	TEXTURE_MGR.Unload("graphics/player3.png");
	TEXTURE_MGR.Unload("graphics/player4.png");
	TEXTURE_MGR.Unload("graphics/rip.png");
	TEXTURE_MGR.Unload("graphics/axe.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Unload("sound/chop.wav");
	SOUNDBUFFER_MGR.Unload("sound/death.wav");
	SOUNDBUFFER_MGR.Unload("sound/out_of_time.wav");

}

void SceneDev1::Update(float dt)
{ 
	Scene::Update(dt);


	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev2);
	}

	switch (currentStatus)
	{
	case SceneDev1::Status::Awake:
		UpdateAwake(dt);
		break;
	case SceneDev1::Status::Game:
		UpdateGame(dt);
		break;
	case SceneDev1::Status::GameOver:
		UpdateGameOver(dt);
		break;
	case SceneDev1::Status::Pause:
		UpdatePause(dt);
		break;
	}
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneDev1::SetCenterMessage(const std::string& msg)
{
	centerMsg->text.setString(msg);
	centerMsg->SetOrigin(Origins::MC);
}

void SceneDev1::SetVisibleCenterMessage(bool visible)
{
	centerMsg->SetActive(visible);
}

void SceneDev1::SetScore(int score)
{
	this->score = score;
	uiScore->SetScore(this->score);
}

void SceneDev1::SetStatus(Status newStatus)
{
	Status prevStatus = currentStatus;
	currentStatus = newStatus;

	switch (currentStatus)
	{
	case SceneDev1::Status::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("Press Enter To Start!!");
		score = 0;
		timer = gameTime;
		SetScore(score);
		uiTimer->SetValue(1.f);
		break;
	case SceneDev1::Status::Game:
		if (prevStatus == Status::GameOver)
		{
			score = 0;
			timer = gameTime;

			SetScore(score);
			uiTimer->SetValue(1.f);

			player->Reset();
			tree->Reset();
			player->SetWin(false);
		}
		if (prevStatus == Status::Awake)
			player->SetWin(false);
		FRAMEWORK.SetTimeScale(1.f);
		SetVisibleCenterMessage(false);
		break;
	case SceneDev1::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		break;
	case SceneDev1::Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("PAUSE! ESC TO RESUME!");
		break;
	}
}

void SceneDev1::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SceneDev1::UpdateGame(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Pause);
		return;
	}

	timer = Utils::Clamp(timer - dt, 0.f, gameTime);
	uiTimer->SetValue(timer / gameTime);
	if (timer <= 0.f)
	{
		sfxTimeOut.play();

		player->OnDie();
		SetCenterMessage("Time Over!");
		SetStatus(Status::GameOver);
		return;
	}
}

void SceneDev1::UpdateGameOver(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SceneDev1::UpdatePause(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Game);
	}
}

void SceneDev1::OnChop(Sides side, bool is1P)
{
	Sides branchSide = tree->Chop(side);
	if (player->GetSide() == branchSide)
	{
		sfxDeath.play();

		player->OnDie();
		SetCenterMessage("You Die!");
		SetStatus(Status::GameOver);
	}
	else
	{
		SetScore(score + 100);
		timer += 1.f;
	}
}
