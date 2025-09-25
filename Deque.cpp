#include<iostream>
#include <cassert>
using namespace std;


namespace lib{
    template<class T>
    class deque{
        private:
            int start=0;
            int curr_capacity=0;
            T** arr;
            int a=0;
            int sz=0;

            void enlarge(bool front=false){
                curr_capacity=(!curr_capacity?1:2*curr_capacity);
                T** temp=new T*[curr_capacity];
                int new_start=(front?((curr_capacity-sz)/2)+1:(curr_capacity-sz)/2);
                for(int i=0;i<sz;i++){
                    temp[new_start+i]=arr[start+i];
                }
                delete[] arr;
                arr=temp;
                start=new_start;
            }

        public:

            deque(){
                start=0;
                arr=NULL;
                curr_capacity=0;
            }

            deque(int n){
                arr=new T*[n];
                for(int i=0;i<n;i++) arr[i]=new T();
                curr_capacity=n;
                start=0;
                sz=n;
            }
            deque(int n,T x){
                arr=new T*[n];
                for(int i=0;i<n;i++){
                    arr[i]=new T(x);
                }
                start=0;
                curr_capacity=n;
                sz=n;
            }

            ~deque(){this->clear();}

            

            T operator [](int idx){
                if(idx<0 || idx>=sz) return T();
                return *arr[start+idx];
            }

            void push_back(T x){
                if(sz==curr_capacity||start+sz>=curr_capacity) enlarge();
                arr[start+sz]=new T(x);
                sz++;
            }

            void push_front(T x){
                if(start==0||start+sz==curr_capacity) enlarge(true);
                arr[--start]=new T(x);
                sz++;
            }

            void pop_back(){
                if(sz==0){
                    return;
                }
                int end=start+sz-1;
                delete arr[end];
                arr[end]=NULL;
                sz--;
            }

            void pop_front(){
                if(sz==0){
                    return;
                }
                delete arr[start];
                arr[start]=NULL;
                start++;
                sz--;
            }

            T front(){
                return (sz==0?T():*arr[start]);
            }

            T back(){
                int end=start+sz-1;
                return (sz==0?T():*arr[end]);
            }

            int size(){
                return (sz);
            }

            int capacity(){
                return curr_capacity;
            }

            bool empty(){
                return sz==0 ;
            }

            void clear(){
                for(int i=start;i<start+sz;i++){
                    delete arr[i];
                }
                delete[]arr;
                arr=NULL;
                start=0;
                sz=0;
                curr_capacity=0;
            }

            void reserve(int n){
                if(n>curr_capacity){
                    T** temp=new T*[n];
                    for(int i=0;i<sz;i++){
                        temp[i]=arr[start+i];
                    }
                    delete[] arr;
                    arr=temp;
                    start=0;
                    curr_capacity=n;
                }
            }
            void shrink_to_fit(){
                int n=(sz);
                T** temp=new T*[n];
                int idx=0;
                for(int i=start;i<start+sz;i++){
                    temp[idx]=arr[i];
                    idx++;
                }
                delete[] arr;
                arr=temp;
                curr_capacity=(n);
                start=0;
            }

            void resize(int n){
                resize(n,T());
            }

            void resize(int n,T x){
                if(n<sz){
                    for(int i=start+n;i<start+sz;i++) delete arr[i];
                }
                reserve(n);
                T** temp=new T*[n];
                for(int i=sz;i<n;i++) arr[i]=new T(x);
                sz=n;
                start=0;
            }

            void print(){
                if(!this->empty()){
                    for(int i=start;i<start+sz;i++){
                        cout<<"Index: "<<i<<" value: "<<*arr[i]<<endl;
                    }
                }
                cout<<"Size: "<<this->size()<<endl;
                cout<<"Capacity: "<<curr_capacity<<endl;
                cout<<endl;
            }
    };
}




int main(){
    lib::deque<int>d(3,5);
    // lib::deque<int>da(2);
    lib::deque<int>da;
    // lib::deque<int>db();
    da.print();
    da.pop_back();
    da.print();
    da.push_back(3);
    // da.push_back(3);

    da.print();

    da.push_front(5);
    da.print();
    da.pop_front();

    // da.push_back(10);
    // da.push_front(11);
    // da.push_back(100);
    // cout<<da.front()<<endl;
    // cout<<da.back()<<endl;
    // da.pop_front();
    // da.pop_front();
    // da.pop_front();

    da.print();
    da.reserve(10);
    da.print();
    
    da.resize(5,8);
    // da.shrink_to_fit();
    // da.clear();
    cout<<"Empty : "<<da.empty()<<endl;
    da.print();
    // cout<<da[2]<<endl;
    // cout<<db.size()<<endl;
    
    return 0;
}