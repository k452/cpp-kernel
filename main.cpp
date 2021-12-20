#include <iostream>
#include <ctime>
#include <random>
#include <chrono>

using namespace std;

const int TIMES = 10000000;
int result = 0;

int main()
{
  std::chrono::system_clock::time_point start, end; // 型は auto で可
  start = std::chrono::system_clock::now();         // 計測開始時間

  std::srand(time(NULL));
  for (int i = 0; i < TIMES; i++)
  {
    result ^= rand();
  }
  end = std::chrono::system_clock::now();                                                      // 計測終了時間
  double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count(); //処理に要した時間をミリ秒に変換
  cout << "所要時間：" << elapsed << "ミリ秒" << endl;
  // cout << hex << result << endl;
  return 0;
}