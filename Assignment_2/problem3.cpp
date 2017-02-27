#include <iostream>
#include <vector>
using namespace std;
int search(vector<int> &tail,int i,int j,int e)
{
 int m;
 while(i+1<j)
  {
    m=i+(j-i)/2;

    if(e<=tail[m])
     j=m;
    else
     i=m;
  }
 return j;
}
int lis(int*a,int i,int n)
  {

    int length=1,k;
    vector<int> tail(n,0);
    tail[0]=a[i];
    if(n==0)
      return 0;

    i=(i+1)%n;
    k=0;
    for(int j=i;k<n;j=(j+1)%n)
      {

        if(a[j]<tail[0])
            tail[0]=a[j];

        else if(a[j]>tail[length-1])
            tail[length++]=a[j];

        else
          {
            tail[search(tail,-1,length-1,a[j])]=a[j];
          }
    k++;
   }

  return length;
}

int main()
  {
    cout<<"Enter the number of test cases"<<endl;
    int t;
    cin>>t;
    while(t--)
      {
        int n,i,max=0,val;
        cout<<"Enter the number of guests invited in the party"<<endl;
        cin>>n;
        int*a=new int[n];
        for(i=0;i<n;i++)
          cin>>a[i];

        for(i=0;i<n;i++)
          {
            val=lis(a,i,n);

            if(max<val)
                max=val;
          }
    cout<<max<<endl;
  }

 return 0;
}
