#include<iostream>
using namespace std;


namespace lib{
    template<class T>
    class deque{
        public:
            int start=-1;
            int curr_capacity=0;
            T** arr;
            int a=0;
            int sz=0;

            deque(){
                arr=new T*[1];
                curr_capacity=1;
            }

            deque(int n){
                arr=new T*[n];
                for(int i=0;i<n;i++) arr[i]=new T();
                curr_capacity=n;
                start=0;
                // end=n-1;
                sz=n;
            }
            deque(int n,T x){
                arr=new T*[n];
                for(int i=0;i<n;i++){
                    auto temp=new T;
                    *temp=x;
                    arr[i]=temp;
                }
                start=0;
                // end=n-1;
                curr_capacity=n;
                sz=n;
            }

            void enlarge(){
                curr_capacity=2*curr_capacity;
                if(curr_capacity==0) curr_capacity=2;
                T** temp=new T*[curr_capacity];
                int new_start=((curr_capacity)/2)-1;
                int temp_idx=start;
                for(int i=new_start;i<new_start+(sz);i++){
                    temp[i]=arr[temp_idx];
                    temp_idx++;
                }
                delete[] arr;
                arr=temp;
                // end=new_start+(end-start);
                start=new_start;
            }

            T operator [](int idx){
                return *arr[start+idx];
            }

            void push_back(T x){
                if(start+sz<=curr_capacity-1){
                    auto temp = new T;
                    *temp=x;
                    arr[start+sz]=temp;
                    // end++;
                }
                else{
                    enlarge();
                    auto temp = new T;
                    *temp=x;
                    if(start<0) arr[0]=temp;
                    else arr[start+sz]=temp;
                    // end++;
                }
                sz++;
            }

            void push_front(T x){
                if(start-1>=0){
                    auto temp=new T;
                    *temp=x;
                    arr[start-1]=temp;
                    start--;
                }
                else{
                    enlarge();
                    auto temp=new T;
                    *temp=x;
                    arr[start-1]=temp;
                    start--;
                }
                sz++;
            }

            void pop_back(){
                if(sz==0){
                    cout<<"size is zero : no elements to pop"<<endl;
                    return;
                }
                int end=start+sz-1;
                delete arr[end];
                arr[end]=NULL;
                // end--;
                sz--;
            }

            void pop_front(){
                if(sz==0){
                    cout<<"size is zero : no elements to pop"<<endl;
                    return;
                }
                delete arr[start];
                arr[start]=NULL;
                start++;
                sz--;
            }

            T front(){
                return *arr[start];
            }

            T back(){
                int end=start+sz-1;
                return *arr[end];
            }

            int size(){
                return (sz);
            }

            int capacity(){
                return curr_capacity;
            }

            bool empty(){
                cout<<"size: "<<sz<<endl;
                return sz==0 ;
            }

            void clear(){
                for(int i=start;i<start+sz;i++){
                    delete arr[i];
                    arr[i]=NULL;
                }
                start=-1;
                sz=0;
            }

            void reserve(int n){
                if(n>curr_capacity){
                    T** temp=new T*[n];
                    for(int i=0;i<curr_capacity;i++){
                        temp[i]=arr[i];
                    }
                    delete[] arr;
                    arr=temp;
                    curr_capacity=n;
                }
                // sz=n;
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
                // end=n-1;
            }

            void resize(int n){
                T** temp=new T*[n];
                if(n>sz){
                    int idx=start;
                    for(int i=0;i<sz;i++){
                        temp[i]=arr[idx];
                        idx++;
                    }
                    for(int i=sz;i<n;i++){
                        temp[i]=new T();
                    }
                    sz=n;
                }
                else{
                    int idx=start;
                    for(int i=0;i<n;i++){
                        temp[i]=arr[idx];
                        idx++;
                    }
                    sz=n;
                }
                start=0;
                curr_capacity=n;
                delete[] arr;
                arr=temp;
            }

            void resize(int n,T x){
                T** temp=new T*[n];
                if(n>sz){
                    int idx=start;
                    for(int i=0;i<sz;i++){
                        temp[i]=arr[idx];
                        idx++;
                    }
                    for(int i=sz;i<n;i++){
                        temp[i]=new T();
                        *temp[i]=x;
                    }
                    sz=n;
                }
                else{
                    int idx=start;
                    for(int i=0;i<n;i++){
                        temp[i]=arr[idx];
                        idx++;
                    }
                    sz=n;
                }
                start=0;
                curr_capacity=n;
                delete[] arr;
                arr=temp;
            }

            void print(){
                if(!this->empty()){
                    for(int i=start;i<start+sz;i++){
                        cout<<"Index: "<<i<<" value: "<<*arr[i]<<endl;
                    }
                    cout<<"Size: "<<this->size()<<endl;
                    cout<<"Capacity: "<<curr_capacity<<endl;
                    cout<<endl;
                }
                
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
    // da.resize(5,5);
    // da.shrink_to_fit();
    da.clear();
    cout<<"Empty : "<<da.empty()<<endl;
    da.print();
    // cout<<da[2]<<endl;
    // cout<<db.size()<<endl;
    return 0;
}