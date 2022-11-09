# include <Siv3D.hpp> // OpenSiv3D v0.6.5

void Main()
{
	class Player {

	public:

		//座標
		Vec2 pos = { 300,300 };

		//慣性
		double inertia = 0;



		//更新用の関数（引数はデルタタイム）
		void update(double d_time) {

			double speed = 20 * d_time;

			if (KeyLeft.pressed()) {
				inertia -= speed;
			}
			else if (KeyRight.pressed()) {
				inertia += speed;
			}

			//左右のキー入力がされていない
			else {

				//慣性の絶対値が0以上
				if (inertia > 0 or inertia < 0) {

					//慣性にかける値
					double v = 80 * d_time;

					//0.95以下にしたいが、これを使うとフレームと変わらなくなってしまう
					if (v > 0.95) {
						v = 0.95;
					}

					//慣性にかける
					inertia *= v;
				}
			}

			//慣性の上限
			if (inertia > 10) {
				inertia = 10;
			}
			else if (inertia < -10) {
				inertia = -10;
			}

			//慣性の分移動する
			pos.x += inertia;
		}



		void draw() const{
			RectF rect(pos.x, pos.y, 100, 100);
			rect.draw(Palette::White);

			//数値を表示
			ClearPrint();

			Print << U"pos::" << pos;
			Print << U"ine::" << inertia;
		}

	};



	Player player;

	while (System::Update())
	{
		double d_time = Scene::DeltaTime();

		player.update(d_time);
		player.draw();
	}
}

