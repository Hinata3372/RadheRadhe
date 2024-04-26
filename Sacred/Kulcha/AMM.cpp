#include<iostream>
#include<vector>
#include<omp.h>

using namespace std;

void bubbleSort(vector<int>& arr)
{
    bool swapped = true;

    while(swapped)
    {
        swapped = false;

        #pragma omp parallel for
        for(int i = 0 ; i < arr.size() ; i++)
        {
            if(arr[i] > arr[i+1])
            {
                swap(arr[i], arr[i+1]);
                swapped = true;
            }
        }
    }
}

void merge(vector<int>& arr, int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for(int i = 0 ; i < n1 ; i++)
    {
        L[i] = arr[l + i];
    }

    for(int j = 0 ; j < n2 ; j++)
    {
        R[j] = arr[m + 1 + j];
    }

    int i = 0, j = 0, k = l;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            L[i] = arr[k];
            i++;
        }
        else
        {
            R[j] = arr[k];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        L[i] = arr[k];
        i++;
        k++;
    }

    while (j < n2)
    {
        R[j] = arr[k];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int l, int r)
{
    if(l < r)
    {
        int m = l + (r - l)/2;

        #pragma omp multiple sections
        {
            #pragma omp section
            mergeSort(arr, l, m);
            #pragma omp section
            mergeSort(arr, m+1, r);
        }
        merge(arr, l, m, r);
    }
}

int main()
{
    int n;
    cout<<"Enter the size of array : ";
    cin>>n;

    vector<int> arr(n);

    for(int i = 0 ; i < n ; i++)
    {
        cout<<"Enter the "<<i+1<<" element : ";
        cin>>arr[i];
    }

    bubbleSort(arr);
    cout<<"Bubble sort : ";
    for(int num : arr)
    {
        cout<<num<<" ";
    }
    cout<<endl;

    mergeSort(arr, 0, n-1);
    cout<<"Merge sort : ";
    for(int num : arr)
    {
        cout<<num<<" ";
    }
    cout<<endl;
}