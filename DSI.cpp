#include<iostream>
 using namespace std;

void print(int a[],int lo,int hi)
{
    cout << endl;
    for(int i=lo;i<=hi;i++)
        cout << a[i] << " ";
    cout << endl;
}
                                                   //selection sort
void selection_sort(int a[],int lo,int hi)
{
    for(int i=lo;i<hi;i++)
        for(int j=i+1;j<=hi;j++)
            if(a[j]<a[i])
                {
                    int tmp=a[i];
                    a[i]=a[j];
                    a[j]=tmp;
                }
}
void selection_sort_index(int a[],int lo,int hi)
{
    for(int i=lo;i<hi;i++)
    {
        int minIndex=i;
        for(int j=i+1;j<=hi;j++)
            if(a[j]<a[minIndex])
                minIndex=j;
        if(minIndex!=i)
                {
                    int tmp=a[i];
                    a[i]=a[minIndex];
                    a[minIndex]=tmp;
                }
    }
}
void selection_sort_recursive(int a[],int lo,int hi)
{
    if(lo<hi)
    {
        int minIndex=lo;
        for(int j=lo+1;j<=hi;j++)
            if(a[j]<a[minIndex])
                minIndex=j;
        if(minIndex!=lo)
                {
                    int tmp=a[lo];
                    a[lo]=a[minIndex];
                    a[minIndex]=tmp;
                }
        selection_sort_recursive(a,lo+1,hi);
    }
}


int main()
{   
    int b[100], n;
    cin>>n;
    for (int i=0; i<n; i++) cin>>b[i];
    cout << "Before sorting:" << endl;
    print(b,0,n-1);
    selection_sort(b,0,n-1);
    cout << "After sorting:" << endl;
    print(b,0,n-1);
    return(0);
}