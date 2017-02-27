#include<bits/stdc++.h>
#define ll long long int
#define pb push_back
#define mp make_pair
using namespace std;


int main()
{
    int width,height;
    cin>>width; // enter the width of the grid
    cin>>height; // enter the height of the grid
    int arr[width+1][height+1][2];
    ll dp[width+1][height+1];
    for(int i=0;i<=width;i++)
    {
        for(int j=0;j<=height;j++)
        {

            dp[i][j] = 0;
            for(int k=0;k<2;k++)
                {
                    if(i==0 && j==0)
                    arr[i][j][k]=0;
                    else if(i==0 && k==1)
                        arr[i][j][k] = 0;
                    else if(j==0 && k==0)
                        arr[i][j][k] = 0;
                    else arr[i][j][k] = 1;
                }
        }
    }
    dp[0][0] = 1;
    cout<<"Enter the length of bad sequence"<<endl;
    int n;
    cin>>n;// enter the length of the bad sequence
    for(int i=1;i<=n;i++)
    {
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        if(c-a==0 && d-b==1)
        {
            arr[c][d][0] = 0;
        }
        else if(c-a==1 && d==b)
        {
            arr[c][d][1] = 0;
        }
        if(c-a==0 && b-d==1)
        {
            arr[a][b][0] = 0;
        }
        else if(a-c==1 && d==b)
        {
            arr[a][b][1] = 0;
        }
    }
    for(int j=0;j<=height;j++)
    {
        for(int i=0;i<=width;i++)
        {
            if(arr[i][j][0] == 1)
            {
                dp[i][j] = dp[i][j-1] + dp[i][j];
            }
            if(arr[i][j][1] == 1)
                dp[i][j]+=dp[i-1][j];
        }
    }

    cout<<dp[width][height]<<endl; // Number of paths to reach the final destination
    return 0;
}
