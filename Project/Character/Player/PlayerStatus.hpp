#pragma once

// プレイヤーステータス

// 最大HP
constexpr int		Player_initMaxHP = 100;

constexpr float		Player_WallMove = 1.0f;

// スピード
constexpr float		PLAYER_SPEED = 3.0f;

// 最大スピード
constexpr float		PLAYER_MAXSPEED = 10.0f;

// ジャンプ初速
constexpr float		PLAYER_JUMP = -10.0f;
// 攻撃時の横幅
constexpr int		PLAYER_ATTACKWIDTH = 30;
// 当たり判定減衰幅
constexpr int		PLAYER_RECTDECREASE = 12;

// HP回復量
constexpr float		ADD_HP = 0.05f;// * 10000


// 弾の発射限界数
constexpr int		PLAYERSHOT_COUNT = 2;
// 弾の発射間隔
constexpr int		PlayerShot_Wait = 20;