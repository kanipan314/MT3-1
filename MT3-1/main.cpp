#include <Novice.h>
#include <math.h>

const char kWindowTitle[] = "学籍番号";

struct Vector3
{
	float x;
	float y;
	float z;
};

static const int kColumnwindth = 60;
static const int kRowwindth = 60;

void VectorScreenPrint(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnwindth, y, "%.02f", vector.y);
	Novice::ScreenPrintf(x + kColumnwindth * 2, y, "%.02f", vector.z);
	Novice::ScreenPrintf(x + kColumnwindth * 3, y, "%s", label);
}

Vector3 Add(Vector3 v1, Vector3 v2) {
	Vector3 answer;
	answer.x = v1.x + v2.x;
	answer.y = v1.y + v2.y;
	answer.z = v1.z + v2.z;
	return answer;
}

Vector3 Substrct(Vector3 v1, Vector3 v2) {
	Vector3 answer;
	answer.x = v1.x - v2.x;
	answer.y = v1.y - v2.y;
	answer.z = v1.z - v2.z;
	return answer;
}

Vector3 Multiply(float scalar, Vector3 v2) {
	Vector3 answer;
	answer.x = scalar * v2.x;
	answer.y = scalar * v2.y;
	answer.z = scalar * v2.z;
	return answer;
}

float Dot(Vector3 v1, Vector3 v2) {
	float answer = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return answer;
}

float Length(Vector3 v) {
	float answer = 0;
	answer = v.x * v.x + v.y * v.y + v.z * v.z;
	answer = powf(answer, 0.5f);
	return answer;
}

Vector3 Normalize(Vector3 v) {

	Vector3 answer ;
	answer.x = v.x / powf((v.x * v.x + v.y * v.y + v.z * v.z), 0.5f);
	answer.y = v.y / powf((v.x * v.x + v.y * v.y + v.z * v.z), 0.5f);
	answer.z = v.z / powf((v.x * v.x + v.y * v.y + v.z * v.z), 0.5f);

	return answer;
}
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Vector3 v1 = { 1.0f,3.0f,-5.0f };
	Vector3 v2 = { 4.0f,-1.0f,2.0f };
	float k = { 4.0f };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Vector3 resultAdd = Add(v1, v2);
		Vector3 resultSub = Substrct(v1, v2);
		Vector3 resultMul = Multiply(k, v1);
		float resultDot = Dot(v1, v2);
		float resultLength = Length(v1);
		Vector3 resultNormalize = Normalize(v2);


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		VectorScreenPrint(0, 0, resultAdd, "	:Add");
		VectorScreenPrint(0, kRowwindth, resultSub, "	:Sub");
		VectorScreenPrint(0, kRowwindth * 2, resultMul, "		*Multiply");
		Novice::ScreenPrintf(0, kRowwindth * 3, "%0.2f	: Dot", resultDot);
		Novice::ScreenPrintf(0, kRowwindth * 4, "%0.2f	: Length", resultLength);
		VectorScreenPrint(0, kRowwindth * 5, resultNormalize, "	:Normalize");


		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
