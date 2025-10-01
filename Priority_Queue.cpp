#include<iostream>
#include<algorithm>

namespace lib{
    template<class T>
    class array{
    public:
        T* a;
        int cap,sz;
        array(){
            a=nullptr;
            cap=sz=0;
        }
        ~array(){
            delete[] a;
        }
        void resize(int n){
            T* b=new T[n];
            for(int i=0;i<sz && i<n;i++) b[i]=a[i];
            delete[] a;
            a=b;
            cap=n;
        }
        T& operator[](int i){
            return a[i];
        }
    };
    template<class T>
    class priority_queue{
    public:
        int sz;
        bool isMax;
        array<T> v;
        priority_queue(bool type=true){
            sz=0;
            v.resize(1);
            isMax=type;
        }
        int size(){
            return sz;
        }
        bool empty(){
            return sz==0;
        }
        T top(){
            return v[0];
        }
        void push(T x){
            if(sz==v.cap) v.resize(std::max(1,2*v.cap));
            v[sz]=x;
            push_up(sz++);
        }
        void pop(){
            std::swap(v[0],v[--sz]);
            push_down(0);
        }
    private:
        bool cmp(T a,T b){
            return isMax?a>b:a<b;
        }
        void push_down(int idx){
            int a=2*idx+1;
            int b=2*idx+2;
            int best=idx;
            if(a<sz&&cmp(v[a],v[best])) best=a;
            if(b<sz&&cmp(v[b],v[best])) best=b;
            if(best!=idx){
                std::swap(v[idx],v[best]);
                push_down(best);
            }
        }
        void push_up(int idx){
            if(idx==0) return;
            int par=(idx-1)/2;
            if(cmp(v[idx],v[par])){
                std::swap(v[idx],v[par]);
                push_up(par);
            }
        }
    };
}

struct Median{
    lib::priority_queue<int> left,right;
    int* freq;
    int maxVal;
    Median(int maxV):left(true),right(false){
        maxVal=maxV;
        freq=new int[maxVal+1]();
    }
    ~Median(){
        delete[] freq;
    }
    void eraseTop(lib::priority_queue<int>&h){
        while(!h.empty()&&freq[h.top()]>0){
            freq[h.top()]--;
            h.pop();
        }
    }
    void insert(int x){
        if(left.empty()||x<=left.top()) left.push(x);
        else right.push(x);
        balance();
    }
    void remove(int x){
        freq[x]++;
        if(!left.empty()&&x<=left.top()) eraseTop(left);
        if(!right.empty()&&x>=right.top()) eraseTop(right);
        balance();
    }
    void balance(){
        eraseTop(left);
        eraseTop(right);
        if(left.size()>right.size()+1){
            right.push(left.top());
            left.pop();
            eraseTop(left);
        }
        if(right.size()>left.size()){
            left.push(right.top());
            right.pop();
            eraseTop(right);
        }
    }
    double get(){
        eraseTop(left);
        eraseTop(right);
        balance();
        if(left.empty()&&right.empty()) return 0.0;
        if(left.size()==right.size()){
            return (left.top()+right.top())/2.0;
        }
        return left.top();
    }
};

int main(){
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n,d;
    std::cin>>n>>d;
    int* sales=new int[n];
    int maxVal=0;
    for(int i=0;i<n;i++){
        std::cin>>sales[i];
        if(sales[i]>maxVal) maxVal=sales[i];
    }
    int ans=0;
    Median trail(maxVal),prefix(maxVal);
    for(int i=0;i<d;i++){
        trail.insert(sales[i]);
        prefix.insert(sales[i]);
    }
    for(int i=d;i<n;i++){
        double med1=trail.get();
        double med2=prefix.get();
        if(sales[i]>=med1+med2){
            ans++;
        }
        prefix.insert(sales[i]);
        trail.insert(sales[i]);
        trail.remove(sales[i-d]);
    }
    std::cout<<ans<<std::endl;
    delete[] sales;
    return 0;
}

