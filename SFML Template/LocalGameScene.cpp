#include "stdafx.h"
#include "LocalGameScene.h"
#include "SpriteGo.h"
#include "CloudGo.h"
#include "Tree.h"
#include "Player.h"
#include "TextGo.h"
#include "UiScore.h"
#include "UiTimebar.h"

LocalGameScene::LocalGameScene() : Scene(SceneIds::Dev1)
{
}

void LocalGameScene::Init()
{

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

	SOUNDBUFFER_MGR.Load(sbIdDeath);
	SOUNDBUFFER_MGR.Load(sbIdTimeOut);
	for(int i = 0 ; i < playerNum ; i++)
	{
		trees.push_back(AddGo(new Tree("Tree")));
		players.push_back(AddGo(new Player("Player")));
		uiTimer.push_back(AddGo(new UiTimebar("Ui Timer")));
		uiTimer[i]->Set({500.f, 100.f}, sf::Color::Red);
		uiTimer[i]->SetOrigin({-50.f,0.f});
		uiTimer[i]->SetPosition({1920.f / 2.f, 100.f});
	}
	uiTimer[(int)Players::Player1]->SetScale({ -1.f,1.f });
	trees[(int)Players::Player1]->SetPosition({ 1920.f / 4, 1080.f - 200.f });
	players[(int)Players::Player1]->SetPosition({ 1920.f / 4, 1080.f - 200.f });
	trees[(int)Players::Player2]->SetPosition({ 1920 - 1920.f / 4, 1080.f - 200.f });
	players[(int)Players::Player2]->SetPosition({ 1920 - 1920.f / 4, 1080.f - 200.f });
	players[(int)Players::Player2]->SetFlag(false);
	centerMsg = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Center Message"));
	centerMsg->sortingLayer = SortingLayers::UI;

	

	Scene::Init();


	centerMsg->text.setCharacterSize(100);
	centerMsg->text.setFillColor(sf::Color::White);
	centerMsg->SetPosition({ 1920.f / 2.f, 1080.f / 2.f });

}

void LocalGameScene::Enter()
{
	TEXTURE_MGR.Load("graphics/background.png");
	TEXTURE_MGR.Load("graphics/cloud.png");
	TEXTURE_MGR.Load("graphics/tree.png");
	TEXTURE_MGR.Load("graphics/branch.png");
	TEXTURE_MGR.Load("graphics/log.png");
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/rip.png");
	TEXTURE_MGR.Load("graphics/axe.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Load("sound/chop.wav");
	SOUNDBUFFER_MGR.Load(sbIdDeath);
	SOUNDBUFFER_MGR.Load(sbIdTimeOut);

	sfxDeath.setBuffer(SOUNDBUFFER_MGR.Get(sbIdDeath));
	sfxTimeOut.setBuffer(SOUNDBUFFER_MGR.Get(sbIdTimeOut));

	for (int i = 0; i < playerNum; i++)
	{
		players[i]->SetSceneGame(this);
	}
	Scene::Enter();

	SetStatus(Status::Awake);
}

void LocalGameScene::Exit()
{
	std::cout << "LocalGameScene::Exit()" << std::endl;
	for (int i = 0; i < playerNum; i++)
	{
		players[i]->SetSceneGame(nullptr);
		trees[i]->ClearEffectLog();
	}

	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/cloud.png");
	TEXTURE_MGR.Unload("graphics/background.png");
	TEXTURE_MGR.Unload("graphics/tree.png");
	TEXTURE_MGR.Unload("graphics/branch.png");
	TEXTURE_MGR.Unload("graphics/log.png");
	TEXTURE_MGR.Unload("graphics/player.png");
	TEXTURE_MGR.Unload("graphics/rip.png");
	TEXTURE_MGR.Unload("graphics/axe.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Unload("sound/chop.wav");
	SOUNDBUFFER_MGR.Unload("sound/death.wav");
	SOUNDBUFFER_MGR.Unload("sound/out_of_time.wav");

}

void LocalGameScene::Update(float dt)
{
	Scene::Update(dt);

	switch (currentStatus)
	{
	case LocalGameScene::Status::Awake:
		UpdateAwake(dt);
		break;
	case LocalGameScene::Status::Game:
		UpdateGame(dt);
		break;
	case LocalGameScene::Status::GameOver:
		UpdateGameOver(dt);
		break;
	case LocalGameScene::Status::Pause:
		UpdatePause(dt);
		break;
	}
}

void LocalGameScene::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void LocalGameScene::SetCenterMessage(const std::string& msg)
{
	centerMsg->text.setString(msg);
	centerMsg->SetOrigin(Origins::MC);
}

void LocalGameScene::SetVisibleCenterMessage(bool visible)
{
	centerMsg->SetActive(visible);
}


void LocalGameScene::SetStatus(Status newStatus)
{
	prevStatus = currentStatus;
	currentStatus = newStatus;

	switch (currentStatus)
	{
	case LocalGameScene::Status::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("Press Enter To Start!!");
		for(int i = 0 ; i < playerNum ; i++)
		{
			timer[i] = gameTime;
			uiTimer[i]->SetValue(1.f);
		}
		break;
	case LocalGameScene::Status::Game:
		if (prevStatus == Status::GameOver)
		{
			for(int i = 0 ; i < playerNum ; i++)
			{
				timer[i] = gameTime;
				uiTimer[i]->SetValue(1.f);
				players[i]->Reset();
				trees[i]->Reset();
			}
		}
		FRAMEWORK.SetTimeScale(1.f);
		SetVisibleCenterMessage(false);
		break;
	case LocalGameScene::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		break;
	case LocalGameScene::Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("PAUSE! ESC TO RESUME!");
		break;
	}
}

void LocalGameScene::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void LocalGameScene::UpdateGame(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Pause);
		return;
	}
	for(int i = 0 ; i < playerNum ; i++)
	{
		timer[i] = Utils::Clamp(timer[i] - dt, 0.f, gameTime);
		uiTimer[i]->SetValue(timer[i] / gameTime);
		if (timer[i] <= 0.f)
		{
			sfxTimeOut.play();

			players[i]->OnDie();
			players[i != (int)Players::Player1 ? 0 : 1]->SetWin(true);
			SetCenterMessage("Player " + std::to_string(i != (int)Players::Player1 ? 1 : 2) + " Win!!!");
			SetStatus(Status::GameOver);
			return;
		}
	}
}

void LocalGameScene::UpdateGameOver(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void LocalGameScene::UpdatePause(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Game);
	}
}

void LocalGameScene::OnChop(Sides side, bool is1P)
{
	if (is1P)
	{
		Sides branchSide = trees[(int)Players::Player1]->Chop(side);
		if (players[(int)Players::Player1]->GetSide() == branchSide)
		{
			sfxDeath.play();
			timer[(int)Players::Player1] -= 1.f;
			if (skillCount[(int)Players::Player1] > 0)
				skillCount[(int)Players::Player1] -= 1;
		}
		else
		{
			timer[(int)Players::Player1] += 0.3f;
			skillCount[(int)Players::Player1] += 1;
			if (skillCount[(int)Players::Player1] < 10)
				skillCount[(int)Players::Player1] += 1;
			else if (skillCount[(int)Players::Player1] >= 10)
			{
				skillCount[(int)Players::Player1] = 0;
				players[(int)Players::Player1]->SetFever(true);
			}
		}
	}
	else
	{
		Sides branchSide = trees[(int)Players::Player2]->Chop(side);
		if (players[(int)Players::Player2]->GetSide() == branchSide)
		{
			sfxDeath.play();
			timer[(int)Players::Player2] -= 1.f;
			if (skillCount[(int)Players::Player2] > 0)
				skillCount[(int)Players::Player2] -= 1;
		}
		else
		{
			timer[(int)Players::Player2] += 0.3f;
			if (skillCount[(int)Players::Player2] < 10)
				skillCount[(int)Players::Player2] += 1;
			else if (skillCount[(int)Players::Player2] >= 10)
			{
				skillCount[(int)Players::Player2] = 0;
				players[(int)Players::Player2]->SetFever(true);
			}
		}
	}
}

void LocalGameScene::DoSkill(bool is1P)
{
	if (is1P)
	{
		players[(int)Players::Player2]->SetStun(true);
	}
	else
	{
		players[(int)Players::Player1]->SetStun(true);
	}
}