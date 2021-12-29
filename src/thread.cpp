#include <iostream>
#include <memory>
#include <thread>
#include <vector>
#include <utility>

using namespace std;

vector<int> numList(8, 20000000);

void fizzBuzz(int num)
{
  // 乱数シード
  std::srand(time(NULL));

  vector<string> arr;
  int cnt = 0;

  for (int i = 0; i < num; i++)
  {
    if (num % 3 == 0 && num % 5 == 0)
    {
      arr.push_back("FizzBuzz");
    }
    else if (num % 3 == 0)
    {
      arr.push_back("Fizz");
    }
    else if (num % 5 == 0)
    {
      arr.push_back("Buzz");
    }
    else
    {
      arr.push_back("Other");
    }
  }

  for (int j = 0; j < num; j++)
  {
    if (arr[j] == "FizzBuzz")
    {
      cnt++;
    }
  }

  for (int k = 0; k < cnt; k++)
  {
    cnt ^= rand();
  }

  cout << "要素数：" << arr.size() << endl;

  return;
}

void fizzBuzzSingle()
{
  // 乱数シード
  std::srand(time(NULL));

  for (int x = 0; x < numList.size(); x++)
  {
    vector<string> arr;
    int num = numList[x];
    int cnt = 0;

    for (int i = 0; i < num; i++)
    {
      if (num % 3 == 0 && num % 5 == 0)
      {
        arr.push_back("FizzBuzz");
      }
      else if (num % 3 == 0)
      {
        arr.push_back("Fizz");
      }
      else if (num % 5 == 0)
      {
        arr.push_back("Buzz");
      }
      else
      {
        arr.push_back("Other");
      }
    }

    for (int j = 0; j < num; j++)
    {
      if (arr[j] == "FizzBuzz")
      {
        cnt++;
      }
    }

    for (int k = 0; k < cnt; k++)
    {
      cnt ^= rand();
    }

    cout << "要素数：" << arr.size() << endl;
  }
  return;
}

void doubleWrap(int n)
{
  for (int i = 0; i < 4; i++)
  {
    fizzBuzz(numList[i + n]);
  }
}

void fourthWrap(int n)
{
  for (int i = 0; i < 2; i++)
  {
    fizzBuzz(numList[i + n]);
  }
}

void singleThread()
{
  // 時間計測開始
  std::chrono::system_clock::time_point start, end;
  start = std::chrono::system_clock::now();

  cout << "1スレッド" << endl;

  thread(fizzBuzzSingle).join();

  // 時間計測終了
  end = std::chrono::system_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  // 時間出力
  cout << "所要時間：" << elapsed << "ミリ秒" << endl;
  cout << "" << endl;
}

void doubleThread()
{
  // 時間計測開始
  std::chrono::system_clock::time_point start, end;
  start = std::chrono::system_clock::now();

  cout << "2スレッド" << endl;

  thread{doubleWrap, 0}.join();
  thread{doubleWrap, 4}.join();

  // 時間計測終了
  end = std::chrono::system_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  // 時間出力
  cout << "所要時間：" << elapsed << "ミリ秒" << endl;
  cout << "" << endl;
}

void fourthThread()
{
  // 時間計測開始
  std::chrono::system_clock::time_point start, end;
  start = std::chrono::system_clock::now();

  cout << "4スレッド" << endl;

  vector<thread> threads;

  for (int i = 0; i < numList.size(); i += 2)
  {
    thread{fourthWrap, i}.join();
  }

  // 時間計測終了
  end = std::chrono::system_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  // 時間出力
  cout << "所要時間：" << elapsed << "ミリ秒" << endl;
  cout << "" << endl;
}

int main()
{
  singleThread();
  doubleThread();
  fourthThread();

  return 0;
}