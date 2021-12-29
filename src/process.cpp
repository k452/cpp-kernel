#include <iostream>
#include <chrono>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>
#include <ctime>
#include <random>

using namespace std;

vector<int> numList(8, 20000000);

vector<string> fizzBuzz(int num)
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

  return arr;
}

void singleProcess()
{
  // 時間計測開始
  std::chrono::system_clock::time_point start, end;
  start = std::chrono::system_clock::now();

  cout << "1プロセス" << endl;

  // プロセス複製
  pid_t pid = fork();

  if (pid == -1) // fork()失敗
  {
    perror("fork");
    exit(EXIT_FAILURE);
  }
  else if (pid > 0) // 親プロセス
  {
    wait(nullptr);
  }
  else // 子プロセス
  {
    for (int i = 0; i < numList.size(); i++)
    {
      cout << "要素数：" << fizzBuzz(numList[i]).size() << endl;
    }
    exit(EXIT_SUCCESS);
  }

  // 時間計測終了
  end = std::chrono::system_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  // 時間出力
  cout << "所要時間：" << elapsed << "ミリ秒" << endl;
  cout << "" << endl;
}

void doubleProcess()
{
  // 時間計測開始
  std::chrono::system_clock::time_point start, end;
  start = std::chrono::system_clock::now();

  cout << "2プロセス" << endl;

  for (int i = 0; i < numList.size(); i += 4)
  {
    // プロセス複製
    pid_t pid = fork();

    if (pid == -1) // fork()失敗
    {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    else if (pid > 0) // 親プロセス
    {
      wait(nullptr);
    }
    else // 子プロセス
    {
      cout << "要素数：" << fizzBuzz(numList[i]).size() << endl;
      cout << "要素数：" << fizzBuzz(numList[i + 1]).size() << endl;
      cout << "要素数：" << fizzBuzz(numList[i + 2]).size() << endl;
      cout << "要素数：" << fizzBuzz(numList[i + 3]).size() << endl;
      exit(EXIT_SUCCESS);
    }
  }

  // 時間計測終了
  end = std::chrono::system_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  // 時間出力
  cout << "所要時間：" << elapsed << "ミリ秒" << endl;
  cout << "" << endl;
}

void fourthProcess()
{
  // 時間計測開始
  std::chrono::system_clock::time_point start, end;
  start = std::chrono::system_clock::now();

  cout << "4プロセス" << endl;

  for (int i = 0; i < numList.size(); i += 2)
  {
    // プロセス複製
    pid_t pid = fork();

    if (pid == -1) // fork()失敗
    {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    else if (pid > 0) // 親プロセス
    {
      wait(nullptr);
    }
    else // 子プロセス
    {
      cout << "要素数：" << fizzBuzz(numList[i]).size() << endl;
      cout << "要素数：" << fizzBuzz(numList[i + 1]).size() << endl;
      exit(EXIT_SUCCESS);
    }
  }

  // 時間計測終了
  end = std::chrono::system_clock::now();
  double elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

  // 時間出力
  cout << "所要時間：" << elapsed << "ミリ秒" << endl;
  cout << "" << endl;
}

void eighthProcess()
{
  // 時間計測開始
  std::chrono::system_clock::time_point start, end;
  start = std::chrono::system_clock::now();

  cout << "8プロセス" << endl;

  for (int i = 0; i < numList.size(); i++)
  {
    // プロセス複製
    pid_t pid = fork();

    if (pid == -1) // fork()失敗
    {
      perror("fork");
      exit(EXIT_FAILURE);
    }
    else if (pid > 0) // 親プロセス
    {
      wait(nullptr);
    }
    else // 子プロセス
    {
      cout << "要素数：" << fizzBuzz(numList[i]).size() << endl;
      exit(EXIT_SUCCESS);
    }
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
  singleProcess();
  doubleProcess();
  fourthProcess();
  eighthProcess();

  return 0;
}