#include<bits/stdc++.h>
using namespace std;




void Input_Sequence(int n,int a[] , int dp[][2])
    {

        for(int i=1;i<=n;i++)
        {
            cin>>a[i];
            dp[i][0] = dp[i][1] = 1;
        }
    }
int longestZigZag(int n,int a[],int dp[][2])
    {

        for(int i=1;i<=n;i++)
          {
         for(int j=1;j<i;j++)
           {
            if(a[j] < a[i])
            {
                dp[i][1] = max(dp[j][0] + 1,dp[i][1]);
            }
            else if(a[j]>a[i])
            {
                dp[i][0] = max(dp[j][1] + 1,dp[i][0]);
            }
          }
         }
      int ans =1;
      for(int i=1;i<=n;i++)
       {
        ans = max(ans,max(dp[i][0],dp[i][1]));
       }
      return ans;
    }



int main()
{
    int n;  // enter the size of the sequence
    cin>>n;
    int a[n+1];
    int dp[n+1][2];
    Input_Sequence(n,a,dp); // enter the sequence
    cout<<longestZigZag(n,a,dp)<<endl; // length of the longest ZigZag sequence
    return 0;
}
