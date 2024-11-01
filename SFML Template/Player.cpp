#include "stdafx.h"
#include "Player.h"
#include "SceneDev1.h"	

Player::Player(const std::string& name) : GameObject(name)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Player::SetSide(Sides s)
{
	side = s;

	if (side == Sides::Left)
	{
		SetScale({ -1.f, 1.f });
	}
	else if (side == Sides::Right)
	{
		SetScale({ 1.f, 1.f });
	}

	sf::Vector2f newPos = position + localPosPlayer[(int)s];
	spritePlayer.setPosition(newPos);
	spriteAxe.setPosition(newPos + localPosAxe);
	spriteRip.setPosition(newPos + localRipAxe);
	spriteBind.setPosition(newPos);
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	SetSide(side);
}

void Player::OnDie()
{
	isAlive = false;
	isChppoing = false;
}

void Player::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	spritePlayer.setScale(this->scale);

	sf::Vector2f axeScale = this->scale;
	axeScale.x *= -1.f;
	spriteAxe.setScale(axeScale);

	sf::Vector2f axeRip = this->scale;
	axeRip.x = abs(axeScale.x);
	spriteRip.setScale(axeRip);

	spriteBind.setScale({1.f,1.f});
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (preset != Origins::Custom)
	{
		origin = Utils::SetOrigin(spritePlayer, preset);
	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	spritePlayer.setOrigin(origin);
}

void Player::Init()
{
	spritePlayer.setTexture(TEXTURE_MGR.Get(texIdPlayer));
	SetOrigin(Origins::BC);

	spriteAxe.setTexture(TEXTURE_MGR.Get(texIdAxe));
	spriteAxe.setOrigin(originAxe);

	spriteRip.setTexture(TEXTURE_MGR.Get(texIdRip));
	Utils::SetOrigin(spriteRip, Origins::BC);

	spriteBind.setTexture(TEXTURE_MGR.Get(texIdBind));
	Utils::SetOrigin(spriteBind, Origins::BC);
}

void Player::Reset()
{
	sfxChop.setBuffer(SOUNDBUFFER_MGR.Get(sbIdChop));

	spritePlayer.setTexture(TEXTURE_MGR.Get(texIdPlayer));
	spriteAxe.setTexture(TEXTURE_MGR.Get(texIdAxe));
	spriteRip.setTexture(TEXTURE_MGR.Get(texIdRip));
	spriteBind.setTexture(TEXTURE_MGR.Get(texIdBind), true);
	spriteBind.setOrigin({ 75.f,192.f });

	isAlive = true;
	isChppoing = false;
	isWin = true;
	isStun = false;
	SetPosition(position);
	SetScale({ 1.f, 1.f });
	SetSide(Sides::Right);
}


void Player::Release()
{
}


void Player::Update(float dt)
{
	if (isStun)
	{
		stunning += dt;
		if (stunning >= stunTime)
		{
			isStun = false;
			stunning = 0.f;
		}
	}
	if (!isAlive || isWin || isStun)
		return;
	if(is1P)
	{
		if (isFever && InputMgr::GetKeyDown(sf::Keyboard::W))
		{
			DoSkill();
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::A))
		{
			isChppoing = true;
			SetSide(Sides::Left);
			sceneGame->OnChop(Sides::Left,is1P);
			sfxChop.play();
		}

		if (InputMgr::GetKeyUp(sf::Keyboard::A))
		{
			isChppoing = false;
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::D))
		{
			isChppoing = true;
			SetSide(Sides::Right);
			sceneGame->OnChop(Sides::Right, is1P);
			sfxChop.play();
		}

		if (InputMgr::GetKeyUp(sf::Keyboard::D))
		{
			isChppoing = false;
		}
	}
	else
	{
		if (isFever && InputMgr::GetKeyDown(sf::Keyboard::Up))
		{
			DoSkill();
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			isChppoing = true;
			SetSide(Sides::Left);
			sceneGame->OnChop(Sides::Left, is1P);
			sfxChop.play();
		}

		if (InputMgr::GetKeyUp(sf::Keyboard::Left))
		{
			isChppoing = false;
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			isChppoing = true;
			SetSide(Sides::Right);
			sceneGame->OnChop(Sides::Right, is1P);
			sfxChop.play();
		}

		if (InputMgr::GetKeyUp(sf::Keyboard::Right))
		{
			isChppoing = false;
		}
	}
}

void Player::Draw(sf::RenderWindow& window)
{


	if (isAlive)
	{
		window.draw(spritePlayer);
		if (isChppoing)
		{
			window.draw(spriteAxe);
		}	
		if (isStun)
		{
			window.draw(spriteBind);
		}
	}
	else
	{
		window.draw(spriteRip);
	}
}

void Player::SetSceneGame(Scene* scene)
{
	sceneGame = scene;
}

void Player::DoSkill()
{
	sceneGame->DoSkill(is1P);
}

void Player::SetStun(bool isStun)
{
	this->isStun = isStun;
	stunning = 0.f;
}
