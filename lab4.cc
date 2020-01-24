#include <iostream>
#include<bits/stdc++.h>
using namespace std;
void doFifo(int tmp,vector<int> fifo){
string out;
stringstream ss;
ss << tmp;
        if(tmp < 10){
        out='0';
        out+=ss.str();
        }else{
        out=ss.str();
        }
        cout<<out<<"     ";
        for(int i=0;i<fifo.size();i++){
                string frames;
                ss.str("");
                ss.clear();
                ss<<fifo[i];
                if(fifo[i] < 10){
                frames=ss.str();
                frames+='0';
                reverse(frames.begin(),frames.end());
                }else{
                frames=ss.str();
                }
                cout<<frames<<' ';
        }
        cout<<endl;
}
void doClock(int tmp,vector<pair<int,int>> clck){
string out;
stringstream ss;
ss << tmp;
        if(tmp < 10){
        out='0';
        out+=ss.str();
        }else{
        out=ss.str();
        }
        cout<<out<<"     ";
        for(int i=0;i<clck.size();i++){
                string frames;
                ss.str("");
                ss.clear();
                ss<<clck[i].first;
                if(clck[i].first < 10){
                frames=ss.str();
                frames+='0';
                reverse(frames.begin(),frames.end());
                }else{
                frames=ss.str();
                }
                cout<<frames<<' ';
        }
        cout<<endl;
}
void faultFifo(int tmp,vector<int> fifo){
string out;
stringstream ss;
ss << tmp;
        if(tmp < 10){
        out='0';
        out+=ss.str();
        }else{
        out=ss.str();
        }
        cout<<out<<' '<<"F"<<"   ";
        for(int i=0;i<fifo.size();i++){
                string frames;
                ss.str("");
                ss.clear();
                ss<<fifo[i];
                if(fifo[i] < 10){
                frames=ss.str();
                frames+='0';
                reverse(frames.begin(),frames.end());
                }else{
                frames=ss.str();
                }
                cout<<frames<<' ';
        }
        cout<<endl;
}
void faultClock(int tmp,vector<pair<int,int>> clck){
string out;
stringstream ss;
ss << tmp;
        if(tmp < 10){
        out='0';
        out+=ss.str();
        }else{
        out=ss.str();
        }
        cout<<out<<' '<<"F"<<"   ";
        for(int i=0;i<clck.size();i++){
                string frames;
                ss.str("");
                ss.clear();
                ss<<clck[i].first;
                if(clck[i].first < 10){
                frames=ss.str();
                frames+='0';
                reverse(frames.begin(),frames.end());
                }else{
                frames=ss.str();
                }
                cout<<frames<<' ';
        }
        cout<<endl;
}
void fifo(vector<int> input, int sCurr,int fCnt){
cout<<"Replacement Policy = FIFO"<<endl<<"-------------------------------------"<<endl<<"Page   Content of Frames"<<endl<<"----   -----------------"<<endl;
vector<int> fifo;
for(int i=0;i<input.size();i++){
     if(fifo.size()<sCurr){
            if(find(fifo.begin(),fifo.end(),input[i])==fifo.end()){
        fifo.push_back(input[i]);
            doFifo(input[i],fifo);
            }else{
            doFifo(input[i],fifo);
            }
     }else{
     if(find(fifo.begin(),fifo.end(),input[i])==fifo.end()){
        fifo[(fCnt%sCurr)]=input[i];
        fCnt++;
        faultFifo(input[i],fifo);
     }else{
     doFifo(input[i],fifo);
     }
     }
}
cout<<"-------------------------------------"<<endl<<"Number of page faults = "<<fCnt<<endl;
}
void optimal(vector<int>input,int sCurr,int fCnt){
cout<<"Replacement Policy = OPTIMAL"<<endl<<"-------------------------------------"<<endl<<"Page   Content of Frames"<<endl<<"----   -----------------"<<endl;
vector<int> optimal;
for(int i=0;i<input.size();i++){
     if(optimal.size()<sCurr){
            if(find(optimal.begin(),optimal.end(),input[i])==optimal.end()){
        optimal.push_back(input[i]);
            doFifo(input[i],optimal);
            }else{
            doFifo(input[i],optimal);
            }
     }else{
     if(find(optimal.begin(),optimal.end(),input[i])==optimal.end()){
        int maxInd=-1,tmpInd=-1,flag=1;
        for(int j=0;j<optimal.size();j++){
            auto it=find((input.begin()+(i+1)),input.end(),optimal[j]);
            if(it==input.end()){
                maxInd=j;
                flag=0;
                break;
            }else{
            tmpInd=max(tmpInd,(it-input.begin()));
            }
        }
        if(flag)maxInd=(find(optimal.begin(),optimal.end(),input[tmpInd])-optimal.begin());
        optimal[maxInd]=input[i];
        fCnt++;
        faultFifo(input[i],optimal);
     }else{
      doFifo(input[i],optimal);
     }
     }

}
cout<<"-------------------------------------"<<endl<<"Number of page faults = "<<fCnt<<endl;
}
void lru(vector<int> input,int sCurr,int fCnt){
cout<<"Replacement Policy = LRU"<<endl<<"-------------------------------------"<<endl<<"Page   Content of Frames"<<endl<<"----   -----------------"<<endl;
vector<int> LRU;
for(int i=0;i<input.size();i++){
     if(LRU.size()<sCurr){
            if(find(LRU.begin(),LRU.end(),input[i])==LRU.end()){
        LRU.push_back(input[i]);
            doFifo(input[i],LRU);
            }else{
            doFifo(input[i],LRU);
            }
     }else{
     if(find(LRU.begin(),LRU.end(),input[i])==LRU.end()){
        int minInd=INT_MAX,tmpInd=INT_MAX,flag=1;
        for(int j=0;j<LRU.size();j++){
            auto it=find((input.rbegin()+(input.size()-(i+1))),input.rend(),LRU[j]);
            if(it==input.rend()){
                minInd=j;
                flag=0;
                break;
            }else{
                int hmm=(input.size()-(it-(input.rbegin())))-1;
            tmpInd=min(tmpInd,hmm);
            }
        }
        if(flag)minInd=(find(LRU.begin(),LRU.end(),input[tmpInd])-LRU.begin());
        LRU[minInd]=input[i];
        fCnt++;
        faultFifo(input[i],LRU);
     }else{
      doFifo(input[i],LRU);
     }
     }

}
cout<<"-------------------------------------"<<endl<<"Number of page faults = "<<fCnt<<endl;
}
void clck(vector<int>input,int sCurr,int fCnt){
cout<<"Replacement Policy = CLOCK"<<endl<<"-------------------------------------"<<endl<<"Page   Content of Frames"<<endl<<"----   -----------------"<<endl;
vector<pair<int,int>> clck;
int sInd=0;
for(int i=0;i<input.size();i++){
     if(clck.size()<sCurr){
            int fnd=0,fInd=-1;
            for(int j=0;j<clck.size();j++){
                if(clck[j].first==input[i]){
                    fnd=1;
                    fInd=j;
                    break;
                }
            }
           if(!fnd){
            clck.push_back(make_pair(input[i],1));
            sInd++;
            sInd%=sCurr;
            doClock(input[i],clck);
            }else{
            clck[fInd].second=1;
            doClock(input[i],clck);
            }
     }else{
         int fnd=0,fInd=-1;
     for(int j=0;j<clck.size();j++){
                if(clck[j].first==input[i]){
                    fnd=1;
                    fInd=j;
                    break;
                }
            }
     if(!fnd){
    while(1){
    if(clck[sInd].second==0){
        clck[sInd]=make_pair(input[i],1);
        fCnt++;
        sInd++;
        sInd%=clck.size();
        faultClock(input[i],clck);
        break;
    }else{
    clck[sInd].second=0;
    sInd++;
    sInd%=sCurr;
    }
}
     }else{
     clck[fInd].second=1;
     doClock(input[i],clck);
     }
     }
}
cout<<"-------------------------------------"<<endl<<"Number of page faults = "<<fCnt<<endl;
}

int main()
{
int sCurr,fCnt=0,tmp;
string type;
cin>>sCurr>>type;
vector<int>input;
while(1){
    int tmp;
    cin>>tmp;
    if(tmp != -1){
        input.push_back(tmp);
    }else break;
}
if(type.compare("FIFO")==0){
fifo(input,sCurr,fCnt);
}else if(type.compare("OPTIMAL")==0){
optimal(input,sCurr,fCnt);
}else if(type.compare("LRU")==0){
lru(input,sCurr,fCnt);
}else if(type.compare("CLOCK")==0){
clck(input,sCurr,fCnt);
}
    return 0;
}
