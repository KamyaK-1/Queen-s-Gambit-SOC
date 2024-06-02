#include<iostream>
#include<vector>
#include<map>
#include<set>
using namespace std;
int main()
{
    map<multiset<int>,bool> mp;
    mp[{1}]=1;mp[{2}]=1;mp[{3}]=1;mp[{4}]=1;mp[{5}]=1;mp[{6}]=1;mp[{7}]=1;
    for (int i = 1; i<=7 ; i++)
    {
    
        for (int j = i ; j<=7 ; j++)
        {
            if (i==1)
            {
                mp[{i,j}]=false ;
                for (int k = 1; k<j ; k++)
                {
                    if (!mp[{1,k}])
                    {
                        mp[{i,j}]=1;
                        break;
                    }
                }

            }
            else
            {
                mp[{i,j}] = false;
                for (int k = 1; k<j ; k++)
                {
                    if (!mp[{i,k}])
                    {
                        mp[{i,j}]=1;
                        break;
                    }
                }
                for (int k = 1 ; k < i ; k++)
                {
                    if (!mp[{k,j}])
                    {
                        mp[{i,j}]=1;
                        break;
                    }
                }
            }
        }
    }
    for (int i = 1 ; i <=7 ; i++)
    {
        for (int j = i ; j<=7 ; j++)
        {
            for (int k = j ; k<=7  ; k++)
            {
                
                mp[{i,j,k}]=!mp[{i,j}] || !mp[{i,k}] || !mp[{j,k}];
                if (i==2 && j == 5 && k==6)
                {
                    if (!mp[{i,j}])
                    {
                        cout << i << j << endl;
                    }
                    if (!mp[{i,k}])
                    {
                        cout << i << k << endl;
                    }
                    if (!mp[{j,k}])
                    {
                        cout << j << k << endl;
                    }
                }
                for (int t = 1; t < i ; t++)
                {
                    if (!mp[{t,j,k}])
                    {
                        if (i==2 && j == 5 && k==6)
                        {
                            cout << t << " " << j << " " << k << endl;
                        }
                        mp[{i,j,k}]=1;
                        break;
                    }
                }
                for (int t = 1; t < j ; t++)
                {
                    if (!mp[{i,t,k}])
                    {
                        if (i==2 && j == 5 && k==6)
                        {
                            cout << i << " " << t << " " << k << endl;
                        }
                        mp[{i,j,k}]=1;
                        break;
                    }
                }
                for (int t = 1; t < k ; t++)
                {
                    if (!mp[{i,j,t}])
                    {
                        if (i==2 && j == 5 && k==6)
                        {
                            cout << i << " " << j << " " << t << endl;
                        }
                        mp[{i,j,k}]=1;
                        break;
                    }
                }
            }
        }
    }
    for (int i = 1 ; i <=7 ; i++)
    {
        for (int j = i ; j<=7 ; j++)
        {
            for (int k = j ; k<=7  ; k++)
            {
                for (int a = k ; a<= 7 ; a++)
                {
                    mp[{i,j,k,a}]=!mp[{i,j,k}] || !mp[{i,k,a}] || !mp[{j,k,a}] || !mp[{i,j,a}];
                    if (i==1 && j==3 && k==5 && a==6)
                        {
                            if (!mp[{i,j,k}])
                            {
                                cout << i << j << k;
                            }
                            if (!mp[{i,k,a}])
                            {
                                cout << i << k << a;
                            }
                            if (!mp[{i,j,a}])
                            {
                                cout << i << j << a;
                            }
                            if (!mp[{j,k,a}])
                            {
                                cout << j << k << a;
                            }
                        }
                    for (int t = 1; t < i && !mp[{i,j,k,a}] ; t++)
                    {
                        if (!mp[{t,j,k,a}])
                        {
                            if (i==1 && j==3 && k==5 && a==6)
                            {
                                cout << t << " " << j << " " << k << " " << a << endl;
                            }
                            mp[{i,j,k,a}]=1;
                            break;
                        }
                    }
                    for (int t = 1; t < j && !mp[{i,j,k,a}]; t++)
                    {
                        if (!mp[{i,t,k,a}])
                        {
                            if (i==1 && j==3 && k==5 && a==6)
                            {
                                cout << t << " " << j << " " << k << " " << a << endl;
                            }
                            mp[{i,j,k,a}]=1;
                            break;
                        }
                    }
                    for (int t = 1; t < k && !mp[{i,j,k,a}] ; t++)
                    {
                        if (!mp[{i,j,t,a}])
                        {
                            if (i==1 && j==3 && k==5 && a==6)
                            {
                                cout << t << " " << j << " " << k << " " << a << endl;
                            }
                            mp[{i,j,k,a}]=1;
                            break;
                        }
                    }
                    for (int t = 1; t < a && !mp[{i,j,k,a}] ; t++)
                    {
                        if (!mp[{i,j,k,t}])
                        {
                            if (i==1 && j==3 && k==5 && a==6)
                            {
                                cout << t << " " << j << " " << k << " " << a << endl;
                            }
                            mp[{i,j,k,a}]=1;
                            break;
                        }
                    }
                }
            }
        }
    }
    cout << mp[{3,5,7}];
    cout << mp[{2,4,5}];
}