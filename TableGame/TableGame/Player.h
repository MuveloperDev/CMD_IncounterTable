#pragma once
#include "TableGame.h"

class Player
{
public:
	Player(__int32 InTableSizeX, __int32 InTableSizeY);
	~Player();
	void Awake();
	void Start();
	void Update();
	void Render();
	__int32 GetPosX();
	__int32 GetPosY();
	const wchar_t GetShape() const;
	void Test();
	void InitCurrentBattleInput();
	PlayerInputBattleMode GetCurrentInputBattleMode();
	void PrintPlayerStatus(bool InisFrame);
public:
	__int32 GetHp() const;
	__int32 GetMaxHp() const;
	__int32 GetAttackDamage() const;
	__int32 GetGold() const;

	void SetHp(__int32 InDamage);
	void SetAttackDamage(__int32 InAddDamage);
	void SetGold(__int32 InAddGold);
	void SetPosX(__int32 InX);
	void SetPosY(__int32 InY);
private:
	enum Dir
	{
		Right,
		Left,
		Up,
		Down
	};
	void Initialize();
	void Move();
	void BattleInput();
	__int32 _maxHp;
	__int32 _hp;
	__int32 _attackDamge;
	__int32 _gold;

	const wchar_t _shape;
	__int32 _posX;
	__int32 _posY;
	bool isKeyDown;
	const __int32 _TABLE_SIZE_X;
	const __int32 _TABLE_SIZE_Y;
	PlayerInputBattleMode _CURRENTINPUT;
};

