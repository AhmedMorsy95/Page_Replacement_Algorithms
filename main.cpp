#include <iostream>
#include <queue>
#include <map>
#include <stdio.h>

using namespace std;



int pages,faults = 0;
string policy;

void solve_fifo(){
   map<int,int>fifo;
   int x,curTime = 0;
   while(1){
       cin>>x;
       if(x == -1)break;
       printf("%02d ",x);
       if(fifo.size() == pages){
           if(fifo.count(x)){
              cout<<"    ";
           }
           else{
              int mn_key = -1 , mn_val = curTime;
              for(map<int,int>::iterator i = fifo.begin();i!=fifo.end();i++){
                 if(i->second < mn_val || mn_key == -1){
                      mn_val = i->second;
                      mn_key = i->first;
                 }
              }
              fifo[x] = curTime;
              fifo.erase(fifo.find(mn_key));
              faults++;
              cout<<"F   ";
           }
       }
       else{
          /// add it if only doesnot exist
          if(!fifo.count(x))
           fifo[x] = curTime;
           cout<<"    ";
       }
        for(map<int,int>::iterator i = fifo.begin();i!=fifo.end();i++)printf("%02d ",i->first);
       cout<<endl;
       curTime++;
   }

}

void solve_lru(){
   /// map keeping last occurrence for each element when it was last used
   map<int,int>lru;
   int x,curTime = 0;
   while(1){
       cin>>x;
       if(x == -1)break;
       printf("%02d ",x);
       if(lru.size() == pages){
           if(lru.count(x)){
              cout<<"    ";
              lru[x] = curTime;
           }
           else{
              int mn_key = -1 , mn_val = curTime;
               for(map<int,int>::iterator i = lru.begin();i!=lru.end();i++){
                 if(i->second < mn_val || mn_key == -1){
                      mn_val = i->second;
                      mn_key = i->first;
                 }
              }
              lru[x] = curTime;
              lru.erase(lru.find(mn_key));
              faults++;
              cout<<"F   ";
           }
       }
       else{
           cout<<"    ";
           lru[x] = curTime;
       }
        for(map<int,int>::iterator i = lru.begin();i!=lru.end();i++)printf("%02d ",i->first);
       cout<<endl;
       curTime++;
   }
}

void solve_clock(){
   vector<pair<int,int> >cur(pages,pair<int,bool>(-1,false));
   int x,idx = 0;
   while(1){
      cin>>x;
      if(x == -1)break;
      printf("%02d ",x);

      bool found = false;
      int t = 0;
      for(int i=0;i<cur.size();i++){
          if(cur[i].first == x) cur[t].second = found = true;
          t++;
      }

      if(found){
         cout<<"    ";
         for(int i=0;i<pages;i++){
            if(cur[i].first == -1)break;
            printf("%02d ",cur[i].first);
         }
         cout<<endl;
         continue;
      }
      if(cur[idx].first != -1){
            faults++;
            cout<<"F   ";
            while(1){
               if(cur[idx].second == false){
                  cur[idx] = make_pair(x,true);
                  idx++;
                  idx %= pages;
                  break;
               }
               cur[idx].second = false;
               idx++;
               idx %= pages;
            }
      }
      else {
        cout<<"    ";
        cur[idx++]=make_pair(x,true);
        idx %= pages;
      }
      for(int i=0;i<pages;i++){
            if(cur[i].first == -1)break;
            printf("%02d ",cur[i].first);
      }
      cout<<endl;
   }
}
int main()
{
     //freopen("test.in","r",stdin);
     cin>>pages>>policy;
     cout<<"Policy = "<<policy<<endl<<"-------------------------------------"<<endl;
     cout<<"Page   Content of Frames"<<endl<<"----   -----------------"<<endl;

     if(policy == "FIFO")
         solve_fifo();

     else if(policy == "LRU")
         solve_lru();

     else if(policy == "CLOCK")
         solve_clock();

     cout<<"-------------------------------------"<<endl;
     cout<<"Number of page faults = "<<faults<<endl;
    return 0;
}

/*
Page
Content of Frames
----   -----------------
05     05
12     05 12
05     05 12
02
--------------------------------
*/
