#pragma once

class TargetState
{
private:
	int uid = 0;
	float x = 0;
	float y = 0;
	float life = 0;

public:
	TargetState(int _uid, float _x, float _y, float _life) : uid(_uid), x(_x), y(_y), life(_life)
	{
	}

	int GetUid() const
	{
		return uid;
	}
	float GetX() const
	{
		return x;
	}
	float GetY() const
	{
		return y;
	}
	float GetLife() const
	{
		return life;
	}
};
