// Copyright 2020 Burylov Denis <burylov01@mail.ru>

#include <header.hpp>

template <typename T>
inline T const& fun(T const& value) {
  return value;
}

void direct_passage(size_t size_kb) {
  size_t size = size_kb * 256;
  int* arr = new int[size];
  std::mt19937 gen(time(0));
  std::uniform_int_distribution<> uid(0, 32767);
  for (size_t i = 0; i < size; i += 16) arr[i] = uid(gen);
  for (size_t i = 0; i < size; i += 16) fun(arr[i]);
  auto start = std::chrono::steady_clock::now();
  for (size_t j = 0; j < 1000; j++) {
    for (size_t i = 0; i < size; i += 16) fun(arr[i]);
  }
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << size_kb << " kb : " << elapsed_seconds.count() * 1000000 << " ms"
            << std::endl;
  delete[] arr;
}

void back_passage(size_t size_kb) {
  size_t size = size_kb * 256;
  int* arr = new int[size];
  std::mt19937 gen(time(0));
  std::uniform_int_distribution<> uid(0, 32767);
  for (size_t i = 0; i < size; i += 16) arr[i] = uid(gen);
  for (int i = size - 15; i > 0; i -= 16) fun(arr[i]);
  auto start = std::chrono::steady_clock::now();
  for (size_t j = 0; j < 1000; j++) {
    for (int i = size - 15; i > 0; i -= 16) {
      fun(arr[i]);
    }
  }
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << size_kb << " kb : " << elapsed_seconds.count() * 1000000 << " ms"
            << std::endl;
  delete[] arr;
}

void random_passage(size_t size_kb) {
  size_t size = size_kb * 256;
  int* arr = new int[size];
  std::mt19937 gen(time(0));
  std::uniform_int_distribution<> uid(0, 32767);
  for (size_t i = 0; i < size; i += 16) arr[i] = uid(gen);
  for (size_t i = 0; i < size; i += 16) fun(arr[i]);
  auto start = std::chrono::steady_clock::now();
  for (size_t j = 0; j < 1000; j++) {
    for (size_t i = 0; i < size / 16; i++) {
      fun(arr[rand() % (size / 16) * 16]);
    }
  }
  auto end = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  std::cout << size_kb << " kb : " << elapsed_seconds.count() * 1000000 << " ms"
            << std::endl;
  delete[] arr;
}

void direct_() {
  std::cout << "direct:" << std::endl;
  for (size_t i = 64; i <= 4096; i *= 2) {
    direct_passage(i);
  }
  direct_passage(6144);
}

void back_() {
  std::cout << "back:" << std::endl;
  for (size_t i = 64; i <= 4096; i *= 2) {
    back_passage(i);
  }
  back_passage(6144);
}

void random_() {
  std::cout << "random:" << std::endl;
  for (size_t i = 64; i <= 4096; i *= 2) {
    random_passage(i);
  }
  random_passage(6144);
}
