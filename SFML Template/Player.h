#pragma once
#include "GameObject.h"

class SceneDev1;

class Player : public GameObject
{
protected:
	sf::Sound sfxChop;


	sf::Sprite spritePlayer;
	sf::Sprite spriteAxe;
	sf::Sprite spriteRip;

	std::string sbIdChop = "sound/chop.wav";
	std::string texIdPlayer = "graphics/player.png";
	std::string texIdAxe = "graphics/axe.png";
	std::string texIdRip = "graphics/rip.png";

	Sides side = Sides::Right;

	sf::Vector2f localPosPlayer[3] = { { -300.f, 0.f },  { 300.f, 0.f },  { 0.f, 0.f } };
	sf::Vector2f localPosAxe = { 0.f, -70.f };
	sf::Vector2f localRipAxe = { 0.f, 0.f };
	sf::Vector2f originAxe = { -65.f, 0.f };

	bool isAlive = true;
	bool isChppoing = false;
	bool is1P = true;
	bool isWin = false;
	bool isFever = false;
	bool isStun = false;
	Scene* sceneGame = nullptr;

	float stunning = 0.f;
	const float stunTime = 3.f;
public:
	Player(const std::string& name = "");
	//Player(const std::string& texId, const std::string& name = "");
	virtual ~Player() = default;

	Sides GetSide() const { return side; }
	void SetSide(Sides s);
	void OnDie();

	void SetTexIdPlayer(const std::string texId) { texIdPlayer = texId; }
	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset()  override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window)  override;

	void SetSceneGame(Scene* scene);
	void SetFlag(bool is1P) { this->is1P = is1P; }
	void SetWin(bool isWin) { this->isWin = isWin; }
	void SetFever(bool isFever) { this->isFever = isFever; }
	void DoSkill();
	void SetStun(bool isStun);
};

