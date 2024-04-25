#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

void bubble(int *, int);
void swap(int &, int &);


void bubble(int *a, int n)
{
    for(  int i = 0;  i < n;  i++ )
     {  	 
   	 int first = i % 2; 	 

   	 #pragma omp parallel for shared(a,first)
   	 for(  int j = first;  j < n-1;  j += 2  )
   	   {  	 
   		 if(  a[ j ]  >  a[ j+1 ]  )
   		  {  	 
     			 swap(  a[ j ],  a[ j+1 ]  );
   		  }  	 
   		   }  	 
     }
}


void swap(int &a, int &b)
{
    int temp;
    temp=a;
    a=b;
    b=temp;

}

int main(){
    int *a,n;
    cout<<"\nEnter size of Array : ";
    cin>>n;
    a=new int[n];
    cout<<"\nEnter elements : \n";
    for(int i=0;i<n;i++)
    {
   	 cin>>a[i];
    }
    
    bubble(a,n);
    
    cout<<"\nSorted array is : \n";
    for(int i=0;i<n;i++)
    {
   	 cout<<a[i]<<endl;
    }
    return 0;
}

