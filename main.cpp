#include<bits/stdc++.h>
#include <chrono>
#include<math.h>
using namespace std;
static std::random_device rand_dev;
static std::mt19937 generator(rand_dev()); //A Mersenne Twister pseudo-random generator of 32-bit numbers
long n=pow(10,7),dimension=100;
long temp,dis;
int flag;
float random_num_generator()
{
    float range_from=-100,range_to= 100;
    std::uniform_real_distribution<float>  distr(range_from, range_to);
    return distr(generator) ;
}
bool cmp(vector<float> a,vector<float> b)
{
    if(a[dimension]<b[dimension])return 1;
    return 0;
}
bool comp(pair<float,long> a,pair<float,long> b)
{

    if(a.first<b.first)return 1;
    return 0;
}

int main()
{
    vector<vector<float>> data(n,vector<float> (dimension+1)); //declaration of vector of size 10^7*100
    for(long i=0;i<n;i++)
    {
        float odis=0;
        for(long int j=0;j<dimension;j++)
        {
            data[i][j]=random_num_generator();
            odis+=pow(data[i][j],2);
        }
        data[i][dimension]=odis;
    }
    sort(data.begin(),data.end(),cmp);

//save  to binary file
/*
    ifstream input__file;
    input__file.open("data1.bin",ios::binary);
    for(auto i:data)
    {
        for(auto j:i)(input__file)>>j;
    }
    //data.clear();
    input__file.close();
*/
    //  Start Timers
    long int u=100;
    while(u--){
        cout<<"Query no. "<<100-u<<endl;
        vector<float> query(dimension);
        float odis=0;
        for(long int i=0;i<dimension;i++){
                query[i]=random_num_generator();
                cout<<query[i]<<" ";
                odis+=pow(query[i],2);
        }

        std::chrono::time_point<std::chrono::system_clock> start, end1,end2;
        start = std::chrono::system_clock::now();
        long int limit=100*25*25;
        priority_queue<pair<float,long>> q;
        long int co=0;
        for(long int i=0;i<data.size();i++)
        {
            dis=0;
            flag=0;
            if(odis-data[i][dimension]>limit)continue;
            if(data[i][dimension]-odis>limit)break;;
            for(long int j=0;j<dimension;j++)
            {
                temp=(data[i][j]-query[j]);
                dis+=temp*temp;
                if(q.size()==10&& dis>q.top().first){

                        flag=1;
                        break;
                }
            }
            if(flag)continue;
            if(q.size()<=10)q.push(make_pair(dis,i));
            if(q.size()>10)q.pop();
        }
        map<long,int> res;
        while(!q.empty())
        {
            res[q.top().second]++;;
            cout<<q.top().second<<".."<<q.top().first<<endl;
            q.pop();
        }
        end1 = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end1 - start;
        cout << "\n Elapsed Wall Time = " << elapsed_seconds.count() << endl;
        q=priority_queue <pair<float,long>>();
        for(long int i=0;i<data.size();i++)
        {
            dis=0;
            flag=0;
            for(long int j=0;j<dimension;j++)
            {
                temp=(data[i][j]-query[j]);
                dis+=temp*temp;
                if(q.size()==10&& dis>q.top().first){

                        flag=1;
                        break;
                }
            }
            if(flag)continue;
            if(q.size()<=10)q.push(make_pair(dis,i));
            if(q.size()>10)q.pop();
        }
        vector<long> res_bf;
        int match=0;
        while(!q.empty())
        {
            if(res[q.top().second])match++;
            cout<<q.top().second<<".."<<q.top().first<<endl;
            q.pop();
        }
        end2 = std::chrono::system_clock::now();
        elapsed_seconds = end2 - end1;
        cout << "\n Elapsed Wall Time = " << elapsed_seconds.count() << endl<<match<<endl;
        cout<<"--------------------------------\n";
    }
	return 0;
}
