#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneDev1.h"
#include "SceneDev2.h"
#include "LocalGameScene.h"
#include "SceneTitle.h"
#include "SceneChooseGameMode.h"
#include "SceneChooseCharacterOne.h"
#include "SceneChooseCharacterTwo.h"
void SceneMgr::Init()
{
	scenes.push_back(new SceneTitle());
	scenes.push_back(new SceneChooseGameMode());
	scenes.push_back(new SceneChooseCharacterOne());
	scenes.push_back(new SceneChooseCharacterTwo());
	scenes.push_back(new SceneDev1());	
	scenes.push_back(new SceneDev2());
	scenes.push_back(new LocalGameScene());
	for (auto scene : scenes)
	{
		scene->Init();
	}

	currentScene = startScene;
	scenes[(int)currentScene]->Enter();
}

void SceneMgr::Release()
{
	for (auto scene : scenes)
	{
		scene->Release();
		delete scene;
	}
	scenes.clear();
}

void SceneMgr::ChangeScene(SceneIds id)
{
	nextScene = id;
}

void SceneMgr::Update(float dt)
{
	scenes[(int)currentScene]->Update(dt);
}

void SceneMgr::LateUpdate(float dt)
{
	scenes[(int)currentScene]->LateUpdate(dt);
}

void SceneMgr::OnPreDraw()
{
	scenes[(int)currentScene]->OnPreDraw();
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	OnPreDraw();
	scenes[(int)currentScene]->Draw(window);
	OnPostDraw();
}

void SceneMgr::OnPostDraw()
{
	scenes[(int)currentScene]->OnPostDraw();
	if (nextScene != SceneIds::None)
	{
		scenes[(int)currentScene]->Exit();
		currentScene = nextScene;
		nextScene = SceneIds::None;
		scenes[(int)currentScene]->Enter();
	}
}
