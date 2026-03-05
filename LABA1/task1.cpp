#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

/// Создание массива 

double *create_random_array(int N, std::default_random_engine& rng) {
    double *array = new double[N];
    std::uniform_int_distribution<unsigned> dstr(0, N);
    for(unsigned idx = 0; idx < N; ++idx){
        array[idx] = dstr(rng);}
    return array;}


int main() {


///Замер времени по N для прогона по каждому элементу

unsigned seed = 0;
std::default_random_engine rng(seed);

int find_N;
double *cur_mas = nullptr;

//Прогоняем по степеням пятерки умноженных на 100  
std::cout << "      Данные для неотсортированного массива (поиск пробегом по каждому элементу): " << std::endl;
    for (int N = 100 ;N <= 100*25*25*25 ;N *= 5) {
        long long total_time = 0;
    cur_mas = create_random_array(N, rng); 
    //смотрим для разных N от 0,1N до N    
    for (int i = 1; i < 101; ++i){
    find_N=(N/100)*i;
    //считаем время
    auto begin = std::chrono::steady_clock::now();
    for (int repeat = 0; repeat < 100; ++repeat) {
        for (int k = 0; k < N; ++k) {
            if (cur_mas[k] == find_N) break;
        }
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    total_time += time_span.count();}
    //выводим результат

    std::cout << "Количество эл-ов: " << N << "  Среднее время (мкс): " << total_time / 10 << std::endl;
    delete[] cur_mas;
    }
    


// Замер времени по N для бинарного поиска    


std::cout << "      Данные для отсортированного массива (бинпоиск): " << std::endl;
    for (int N = 1000 ;N <= 100*25*25*25 ;N *= 5) {
        long long total_time = 0;
    cur_mas = create_random_array(N, rng);
    // Cортируем массив
    std::sort(cur_mas, cur_mas + N); 
    // Смотрим для разных N от 0,001N до N    
    for (int i = 1; i < 1001; ++i){
    find_N=(N/1000)*i;
   
    // Считаем время
    auto begin = std::chrono::steady_clock::now();

    for (int repeat = 0; repeat < 1000; ++repeat) {
        int left = 0;
        int right = N - 1;
        bool found = false;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (cur_mas[mid] == find_N) {
                found = true;
                break;}
                else if (cur_mas[mid] < find_N) {
                left = mid + 1;} 
            else {
                right = mid - 1;}
}
    }
    auto end = std::chrono::steady_clock::now();
    auto time_span =
    std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    total_time += time_span.count();}

    //Выводим результат

    std::cout << "Количество эл-ов: " << N << "  Среднее время (мкс): " << total_time / 10 << std::endl;
    delete[] cur_mas;
    }


return 0;
}

