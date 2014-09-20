#! /usr/bin/env python
# coding:utf-8

class MergeSort(object):
    @staticmethod
    def sort(array, low, high):
        temp = [x for x in array[low:high]]
        MergeSort.merge_sort(array, temp, low, high-1)

    @staticmethod
    def merge_sort(array, temp, low, high):
        if low >= high:
            return
        mid = (low + high)/2
        MergeSort.merge_sort(array,temp,  low, mid)
        MergeSort.merge_sort(array,temp,  mid+1, high)
        if array[mid] <= array[mid+1]:
            return
        temp = [x for x in array[low:high+1]]
        i = 0
        j = mid - low + 1
        for k in xrange(low, high + 1):
            if i > mid - low:
                array[k] = temp[j]
                j += 1
            elif j > high - low:
                array[k] = temp[i]
                i += 1
            elif temp[i] > temp[j]:
                array[k] = temp[j]
                j += 1
            else:
                array[k] = temp[i]
                i += 1

        


