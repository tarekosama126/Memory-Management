#include<iostream>
#include<fstream>
#include <vector>
#include<string.h>
#include <bits/stdc++.h>

using namespace std;
int buffer_size;
vector<int>buffer;
vector<int>bit;
string type;
vector<int> pages;
string convert(int x)
{
    if(x<=9)
    {
        return "0"+to_string(x);
    }
    else
    {
        return to_string(x);
    }
}
void init_bit()
{
    for(int i=0; i<buffer_size; i++)
    {
        bit.push_back(-1);
    }
}
void init_buffer()
{
    for(int i=0; i<buffer_size; i++)
    {
        buffer.push_back(-1);
    }
}
void print_start(string type)
{
    cout<<"Replacement Policy = "<<type<<endl;
    cout<<"-------------------------------------"<<endl;
    cout<<"Page   Content of Frames"<<endl;
    cout<<"----   -----------------"<<endl;
}
void print_End(int fault)
{
    cout<<"-------------------------------------"<<endl;
    cout<<"Number of page faults = "<<fault<<endl;
}
void print_buffer()
{
    for(int q=0; q<buffer_size; q++)
    {
        if(buffer[q]== -1)
        {
            cout<<"";
        }
        else
        {
            cout<<convert(buffer[q])<<" ";
        }
    }
}
bool search_FIFO(int value)
{
    for(int i=0; i<buffer_size; i++)
    {
        if(buffer[i]==value)
        {
            return true;
        }
    }
    return false;
}
int actions_FIFO(int pointer,int value_x)
{
    if(search_FIFO(value_x)==true && buffer[pointer]==-1)
    {
        return 1;
    }
    else if(buffer[pointer]==-1)
    {
        return 0 ;
    }
    else if(search_FIFO(value_x)==true)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}
void Engine_FIFO(int size_array)
{
    init_buffer();
    print_start(type);
    int i = 0;
    int pointer = 0;
    int fault = 0;
    while(i<size_array)
    {
        int y = pages[i];
        int x = actions_FIFO(pointer,y);
        if(x==0)
        {
            buffer[pointer] = y;
            pointer = (pointer+1)%buffer_size;
            cout<<convert(y)<<"     ";
            print_buffer();
            cout<<endl;
        }
        else if(x==2)
        {
            buffer[pointer] = y;
            pointer = (pointer+1)%buffer_size;
            fault++;
            cout<<convert(y)<<" F"<<"   ";
            print_buffer();
            cout<<endl;
        }
        else
        {
            cout<<convert(y)<<"     ";
            print_buffer();
            cout<<endl;
        }
        i++;
    }
    print_End(fault);
}
bool search_for_negative_one()
{
    for(int i=0; i<buffer_size; i++)
    {
        if(buffer[i]==-1)
        {
            return true;
        }
    }
    return false;
}
int index_for_negative_one()
{
    for(int i=0; i<buffer_size; i++)
    {
        if(buffer[i]==-1)
        {
            return i;
        }
    }
    return -1;
}
bool search_OPTIMAL(int value)
{
    for(int i=0; i<buffer_size; i++)
    {
        if(buffer[i] == value)
        {
            return true;
        }
    }
    return false;
}
int actions_OPTIMAL(int value)
{
    if(search_OPTIMAL(value)==false && search_for_negative_one() == true)
    {
        return 0;
    }
    else if(search_OPTIMAL(value)==false && search_for_negative_one()==false)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}
int update_optimal(int index,int size_array)
{
    int pointer,max_pointer = 0,flag,j  ;
    for(int i=0; i<buffer_size; i++)
    {
        flag = 0;
        int yt = buffer[i];
        for( j=index; j<size_array; j++)
        {
            if(pages.at(j) == yt)
            {
                flag = 1;
                break;
            }
        }
        if(flag==0)
        {
            return i;
        }
        else
        {
            if(max_pointer < j )
            {
                max_pointer=j;
                pointer = i;
            }
        }
    }
    return pointer;
}
int index_in_buffer(int value)
{
    for(int i=0; i<buffer_size; i++)
    {
        if(buffer[i] == value)
        {
            return i;
        }
    }
    return -1;
}
int update_LRU(int index,int size_array)
{
    int pointer,min_pointer = 1000;
    int flag = 0,j;
    for(int i=0; i<buffer_size; i++)
    {
        int yt = buffer[i];
        for(j=index-1; j>=0; j--)
        {
            if(pages.at(j) == yt )
            {
                flag = 1;
                break;
            }
        }
        if(min_pointer > j)
        {
            min_pointer=j;
            pointer=i;
        }
    }
    return pointer;
}
void Engine_optimal(int size_array)
{
    init_buffer();
    print_start(type);
    int pointer = 0;
    int i=0;
    int fault = 0 ;
    while(i<size_array)
    {
        int y = pages.at(i);
        int x = actions_OPTIMAL(y);
        if(x==0)
        {
            pointer = index_for_negative_one();
            buffer[pointer] = y;
            cout<<convert(y)<<"     ";
            print_buffer();
            cout<<endl;
        }
        else if(x==1)
        {
            pointer = update_optimal(i,size_array);
            buffer[pointer] = y;
            fault++;
            cout<<convert(y)<<" F"<<"   ";
            print_buffer();
            cout<<endl;
        }
        else
        {
            cout<<convert(y)<<"     ";
            print_buffer();
            cout<<endl;
        }
        i++;

    }
    print_End(fault);
}
void Engine_LRU(int size_array)
{
    init_buffer();
    print_start(type);
    int pointer = 0;
    int i=0;
    int fault = 0 ;
    while(i<size_array)
    {
        int y = pages.at(i);
        int x = actions_OPTIMAL(y);
        if(x==0)
        {
            pointer = index_for_negative_one();
            buffer[pointer] = y;
            cout<<convert(y)<<"     ";
            print_buffer();
            cout<<endl;
        }
        else if(x==1)
        {
            pointer = update_LRU(i,size_array);
            buffer[pointer] = y;
            fault++;
            cout<<convert(y)<<" F"<<"   ";
            print_buffer();
            cout<<endl;
        }
        else
        {
            cout<<convert(y)<<"     ";
            print_buffer();
            cout<<endl;
        }
        i++;

    }
    print_End(fault);
}
void Engine_CLOCK(int size_array)
{
    init_buffer();
    init_bit();
    print_start(type);
    int Clock_pointer = 0;
    int i=0;
    int fault = 0;
    while(i<size_array)
    {
        int y = pages.at(i);
        if(search_OPTIMAL(y)==false && search_for_negative_one()== true)
        {
            buffer[Clock_pointer]=y;
            bit[Clock_pointer]=1;
            Clock_pointer=(Clock_pointer+1) % buffer_size;
            cout<<convert(y)<<"     ";
            print_buffer();
            cout<<endl;
        }
        else if(search_OPTIMAL(y)==false)
        {
            while(bit[Clock_pointer]==1)
            {
                bit[Clock_pointer]=0;
                Clock_pointer=(Clock_pointer+1) % buffer_size;
            }
            buffer[Clock_pointer]=y;
            bit[Clock_pointer]=1;
            Clock_pointer=(Clock_pointer+1) % buffer_size;
            fault++;
            cout<<convert(y)<<" F"<<"   ";
            print_buffer();
            cout<<endl;
        }
        else if(search_OPTIMAL(y)==true)
        {
            int index = index_in_buffer(y);
            bit[index] =1;
            cout<<convert(y)<<"     ";
            print_buffer();
            cout<<endl;
        }
        i++;
    }
    print_End(fault);
}
void executor(int size_array)
{
    if(type == "FIFO")
    {
        Engine_FIFO(size_array);
    }
    else if(type == "OPTIMAL")
    {
        Engine_optimal(size_array);
    }
    else if(type == "LRU")
    {
        Engine_LRU(size_array);
    }
    else if(type == "CLOCK")
    {
        Engine_CLOCK(size_array);
    }
}
int getsize()
{
    int enter = -2;
    while(enter!=-1)
    {
        cin>>enter;
        pages.push_back(enter);
    }
    return pages.size()-1;
}
int Informations()
{
    cin>>buffer_size;
    cin>>type;
    return getsize();
}
int main()
{
    int size_array = Informations();
    //system("clear");
    executor(size_array);
    return 0;
}

