#include <iostream>
#include <ctime>
#include <cmath>
#include <clocale>

using namespace std;

bool isPrime(int n) {
  if ((n % 2 == 0 && n != 2) || n == 1) return false;

  for (int d = 3; d <= (int)(sqrt(n)); d += 2) {
    if (n % d == 0) {
      return false;
    }
  }
  return true;
}

int* getPrimesDumb(int N) {
  int *primes = new int[N];
  for (int i = 2, index = 0; i < N; i++) {
    if (isPrime(i)) {
      primes[index] = i;
      index++;
    }
  }
  return primes;
}

int* sieveOfEratosthenes(int N) {
  bool *sieve = new bool[N];

  sieve[0] = false;
  sieve[1] = false;
  for (int i = 2; i < N; i++) {
    sieve[i] = true;
  }

  for (int i = 2; i <= sqrt(N); i++) {
    if (!sieve[i]) continue;

    for (int j = i * i; j < N; j += i) {
      sieve[j] = false;
    }
  }

  int *primes = new int[N];
  for (int i = 0, index = 0; i < N; i++) {
    if (!sieve[i]) continue;

    primes[index] = i;
    index++;
  }

  delete [] sieve;

  return primes;
}

// n - number of primes
int getRange(int n) {
  int primesCounter = 0;
  int i = 0;

  while (primesCounter < n) {
    if (isPrime(i)) primesCounter++;
    i++;
  }

  return i;
}

int main() {
  setlocale(LC_ALL, "rus");

  int a;
  int b;

  cout << "������� ���������� ������ ������� �����, ������� �� ������� �����������, ����� ������: ";
  cin >> a >> b;

  int *primes = a > b ? sieveOfEratosthenes(getRange(a)) : sieveOfEratosthenes(getRange(b));

  cout << "��������� ���������� ����� " << primes[a - 1] * primes[b - 1] << endl;

  int N = 0;
  cout << "������� ����� �� �������� ������� ������ ������� �����: ";
  cin >> N;

  int numberOfTests = 1;
  cout << "������� ��� ���������� ��������� �����: ";
  cin >> numberOfTests;

  clock_t start = clock();
  for (int i = 0; i < numberOfTests; i++) {
    delete [] getPrimesDumb(N);
  }
  clock_t end = clock();
  float dumbAverage = ((float)(end - start)) / numberOfTests / CLOCKS_PER_SEC;

  start = clock();
  for (int i = 0; i < numberOfTests; i++) {
    sieveOfEratosthenes(N);
  }
  end = clock();
  float eratosthenesAverage = ((float)(end - start)) / numberOfTests / CLOCKS_PER_SEC;

  cout << "��� ���������� ���� ������� ����� �� ���������� �� 0 �� " << N <<
    " ����� �������� ���� ��������� ����� ����������� ��������� � ������� " << dumbAverage << " ������ " <<
    "� � ������� ������ ���������� ����� " << eratosthenesAverage << " ������";

  delete [] primes;

  return 0;
}
