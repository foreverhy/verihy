#ifndef SORT_H
#define SORT_H 1
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<random>
#include<algorithm>
namespace verihy{



    namespace shellsort{
    template<typename T>
        void sort(T *array, int start, int end)
        {
            int len = end - start;
            int gap = 1;
            while(gap < len/3) gap = 3*gap + 1;
            while(gap > 0){
                for(int i = start+gap; i < end; ++i){
                    for(int j = i; j-gap>=start && array[j]<array[j-gap]; j-=gap){
                        std::swap(array[j], array[j-gap]);
                    }
                }
                gap /= 3;
            }
        }
    }

    namespace mergesort{

        template<typename T>
            void merge(T *array, T *temp, int low, int high)
            {
                int mid = (low + high) >> 1;
                int i = 0, j = mid-low + 1;
                for(int k = low; k <= high; ++k){
                    if(i + low > mid){
                        array[k] = temp[j++];
                    }else if(j + low > high){
                        array[k] = temp[i++];
                    }else if(temp[i] > temp[j]){
                        array[k] = temp[j++];
                    }else{
                        array[k] = temp[i++];
                    }
                }
            }

        template<typename T>
            void sort(T *array, T *temp, int low, int high)
            {
                if(low >= high){
                    return;
                }
                int mid = (low + high) >> 1;
                sort(array, temp, low, mid);
                sort(array, temp, mid+1, high);
                if(array[mid] <= array[mid+1]){
                    return;
                }
                for(int i = 0; i <= high-low; ++i){
                    temp[i] = array[i+low];
                }
                merge(array, temp, low, high);
                
            }

        template<typename T>
            void sort(T *array, int low, int high)
            {
                int len = high - low ;
                T *temp = new T[len];
                sort(array, temp, low, high - 1);
                delete []temp;
            }

    }

    namespace quicksort{
        template<typename T>
            int partition(T *array, int low, int high)
            {
                int i = low, j = high;
                T v = array[low];
                while(true){
                    for(;array[i] <= v && i < high;++i);
                    for(;array[j] >= v && j > low;--j);
                    if(i >= j)break;
                    std::swap(array[i], array[j]);
                }
                std::swap(array[low], array[j]);
                return j;
            }
        template<typename T>
            void quick_sort(T *array, int low, int high)
            {
                if(low >= high){
                    return;
                }
                int mid = partition(array, low, high);
                quick_sort(array, low, mid - 1);
                quick_sort(array, mid + 1, high);
            }
        template<typename T>
            void sort(T *array, int low, int high)
            {
                std::srand(std::time(0));
                std::mt19937 rd(std::rand());
                std::shuffle(array+low, array+high, rd);
                quick_sort(array, low, high-1);

            }
    }
}



#endif
