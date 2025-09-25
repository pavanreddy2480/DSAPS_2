#include<iostream>
using namespace std;

namespace lib{
    template<class T>
    class priority_queue{
        public:
            int end=0;
            int sz=0;
            vector<T>v;
            priority_queue(){
                v.resize(200005,0);
            };
            int size(){
                return sz;
            }
            T top(){
                return v[0];
            }
            void pop(){
                swap(v[0],v[--end]);
                push_down(0);
                sz--;
            }
            void push_down(int idx){
                if(idx>=end) return;
                int a=2*idx+1;
                int b=2*idx+2;
                if(a>=end && b>=end) return;
                if(a<end && b>=end){
                    if(v[a]>v[idx]){
                        swap(v[idx],v[a]);
                        return;
                    }
                }
                else{
                    if(v[a]>v[idx]||v[b]>v[idx]){
                        if(v[a]>v[b]){
                            swap(v[idx],v[a]);
                            push_down(a);
                        }
                        else{
                            swap(v[idx],v[b]);
                            push_down(b);
                        }
                    }
                }
            }

            bool empty(){
                return sz==0;
            }
            void push(T x){
                v[end++]=x;
                push_up(end-1);
                sz++;
            }
            void push_up(int idx){
                if(idx==0) return;
                int par=(idx-1)/2;
                if(v[par]<v[idx]){
                    swap(v[par],v[idx]);
                    push_up(par);
                }
            }
    };
};


int main(){
    lib::priority_queue<int>pq;
    
    return 0;
}