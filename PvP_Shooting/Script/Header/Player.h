
#ifndef PLAYER_H
#define PLAYER_H

// プレイヤーに関する変数や処理を管理する
class Player {
public:
	// コンストラクタ
	Player();

	// デストラクタ
	~Player();

	// 移動
	static void Move();

	// 描画
	static void Draw();

private:
	static int pos_x;
	static int pos_y;
	static int speed;
};

#endif // !PLAYER_H
