#include<iostream>
using namespace std;


namespace lib{
    template<class T>
    class deque{
        public:
            int start=-1,end=-1;
            int curr_capacity=0;
            T** arr;
            int a=0;
            int sz=0;

            deque(){}
            deque(int n){
                arr=new T*[n];
                for(int i=0;i<n;i++) arr[i]=new T();
                curr_capacity=n;
            }
            deque(int n,T x){
                arr=new T*[n];
                for(int i=0;i<n;i++){
                    auto temp=new T;
                    *temp=x;
                    arr[i]=temp;
                }
                start=0;
                end=n-1;
                curr_capacity=n;
            }

            void enlarge(){
                curr_capacity=2*curr_capacity;
                if(curr_capacity==0) curr_capacity=2;
                T** temp=new T*[curr_capacity];
                int new_start=((curr_capacity)/2)-1;
                int temp_idx=start;
                for(int i=new_start;i<new_start+(end-start+1);i++){
                    temp[i]=arr[temp_idx];
                    temp_idx++;
                }
                delete[] arr;
                arr=temp;
                end=new_start+(end-start);
                start=new_start;
            }

            T operator [](int idx){
                return *arr[start+idx];
            }

            void push_back(T x){
                if(end+1<=curr_capacity-1){
                    auto temp = new T;
                    *temp=x;
                    arr[end+1]=temp;
                    end++;
                }
                else{
                    enlarge();
                    push_back(x);
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
                    push_front(x);
                }
                sz++;
            }

            void pop_back(){
                delete arr[end];
                arr[end]=NULL;
                end--;
                sz--;
            }

            void pop_front(){
                delete arr[start];
                arr[start]=NULL;
                start++;
                sz--;
            }

            T front(){
                return *arr[start];
            }
            T back(){
                return *arr[end];
            }

            int size(){
                return (end-start+1);
            }
            int capacity(){
                return curr_capacity;
            }
            bool empty(){
                return end<start || end<0 ;
            }
            void clear(){
                for(int i=start;i<=end;i++){
                    delete arr[i];
                    arr[i]=NULL;
                }
                start=end=-1;
                sz=0;
            }
            void reserve(int n){
                if(n>curr_capacity){
                    T** temp=new T[n];
                    for(int i=0;i<curr_capacity;i++){
                        temp[i]=arr[i];
                    }
                    delete[] arr;
                    arr=temp;
                    curr_capacity=n;
                }
                sz=n;
            }
            void shrink_to_fit(){
                int n=(end-start+1);
                T** temp=new T[n];
                int idx=0;
                for(int i=start;i<=end;i++){
                    temp[idx]=arr[i];
                    idx++;
                }
                delete[] arr;
                arr=temp;
                curr_capacity=(n);
                start=0;
                end=n-1;
            }
            // void resize(int n)

    };
}




int main(){
    lib::deque<int>d(3,5);
    cout<<d[2]<<endl;
    d.push_back(6);
    d.pop_front();
    d.pop_front();
    d.pop_front();
    cout<<d[0]<<endl;
    return 0;
}