#pragma once
#include "Scene.h"
class Tree;
class Player;
class TextGo;
class UiScore;
class UiTimebar;
class UiSkillBar;
class SpriteGo;
class UiPlayerOne;
class UiPlayerTwo;
class LocalGameScene :
    public Scene
{
public:
	enum class Status
	{
		Awake,
		Game,
		GameOver,
		Pause,
	};

	enum class Players {
		Player1,
		Player2
	};
protected:
	Status currentStatus = Status::Awake;
	const int playerNum = 2;
	std::vector<Tree*> trees;
	std::vector<Player*> players;
	UiPlayerOne* uiPlayerOne;
	UiPlayerTwo* uiPlayerTwo;
	float timer[2] = { 0.f,0.f };

	TextGo* centerMsg;
	std::vector <UiTimebar*> uiTimer;

	float gameTime = 10.f;

	sf::Sound sfxDeath;
	sf::Sound sfxTimeOut;

	std::string sbIdDeath = "sound/death.wav";
	std::string sbIdTimeOut = "sound/out_of_time.wav";

	Status prevStatus = Status::Awake;
	int skillCount[2] = { 0,0 };
	std::vector<UiSkillBar*> skillBar;
	std::vector<SpriteGo*> stun;
	float stunning[2] = { 0.f, 0.f };
	const float stunTime = 3.f;
public:
	LocalGameScene();
	~LocalGameScene() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	void SetCenterMessage(const std::string& msg);
	void SetVisibleCenterMessage(bool visible);

	void SetScore(int score);

	void SetStatus(Status newStatus);
	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdateGameOver(float dt);
	void UpdatePause(float dt);

	void OnChop(Sides side, bool is1P) override;
	void DoSkill(bool is1P) override;
};



