#include <iostream>
#include <ctime>
#include <random>
#include <chrono>

using namespace std;

int main()
{
  // 時間計測開始
  std::chrono::system_clock::time_point start, end;
  start = std::chrono::system_clock::now();

  // 乱数シード
  std::srand(time(NULL));

  // ループ回数
  const int TIMES = 10000000;

  // ループ実行
  int result = rand();
  for (int i = 0; i < TIMES; i++)
  {
    result ^= rand();
    result <<= 1;
    result >>= 1;
    result ^= rand();
  }

  // 時間計測終了
  end = std::chrono::system_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  // 時間出力
  cout << "所要時間：" << elapsed << "ミリ秒" << endl;
  return 0;
}