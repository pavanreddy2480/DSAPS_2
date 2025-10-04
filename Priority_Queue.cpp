#include<iostream>
using namespace std;

namespace lib {
  class priority_queue {
  private:
    int*arr;
    int sz;
    int cap;
    bool isMin;
    void swap(int&a,int&b){
      int t=a;
      a=b;
      b=t;
    }
    void heapify_up(int i){
      if(i==0) return;
      int p=(i-1)/2;
      bool c=isMin?(arr[i]<arr[p]):(arr[i]>arr[p]);
      if(c){
        swap(arr[i],arr[p]);
        heapify_up(p);
      }
    }
    void heapify_down(int i){
      int l=2*i+1,r=2*i+2,t=i;
      if(l<sz){
        bool c=isMin?(arr[l]<arr[t]):(arr[l]>arr[t]);
        if(c) t=l;
      }
      if(r<sz){
        bool c=isMin?(arr[r]<arr[t]):(arr[r]>arr[t]);
        if(c) t=r;
      }
      if(t!=i){
        swap(arr[i],arr[t]);
        heapify_down(t);
      }
    }
    void resize(){
      int old=cap;
      cap=(cap==0?1:cap*2);
      int*tmp=new int[cap];
      for(int i=0;i<old;i++) tmp[i]=arr[i];
      delete[]arr;
      arr=tmp;
    }
  public:
    priority_queue(bool m=false):arr(NULL),sz(0),cap(0),isMin(m){}
    ~priority_queue(){delete[]arr;}
    void push(int x){
      if(sz==cap) resize();
      arr[sz]=x;
      sz++;
      heapify_up(sz-1);
    }
    void pop(){
      if(empty()) return;
      arr[0]=arr[sz-1];
      sz--;
      if(!empty()) heapify_down(0);
    }
    int top(){
      if(empty()) return 0;
      return arr[0];
    }
    int size(){return sz;}
    bool empty(){return sz==0;}
  };

  class median_finder {
  private:
    priority_queue mx,mn;
    int*lazy;
    void balance(){
      while(!mx.empty()&&lazy[mx.top()]>0){
        lazy[mx.top()]--;
        mx.pop();
      }
      while(!mn.empty()&&lazy[mn.top()]>0){
        lazy[mn.top()]--;
        mn.pop();
      }
      if(mx.size()>mn.size()+1){
        mn.push(mx.top());
        mx.pop();
      }
      else if(mn.size()>mx.size()){
        mx.push(mn.top());
        mn.pop();
      }
    }
  public:
    median_finder():mx(false),mn(true){lazy=new int[100001]();}
    ~median_finder(){delete[]lazy;}
    void add(int x){
      if(mx.empty()||x<=mx.top()) mx.push(x);
      else mn.push(x);
      balance();
    }
    void rem(int x){lazy[x]++;}
    double median(){
      balance();
      if(mx.empty()&&mn.empty()) return 0.0;
      if(mx.size()==mn.size()) return ((double)mx.top()+mn.top())/2.0;
      return (double)mx.top();
    }
  };
}

int main(){
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int n,d;
  cin>>n>>d;
  int*sales=new int[n];
  for(int i=0;i<n;i++) cin>>sales[i];
  lib::median_finder win,tot;
  int cnt=0;
  for(int i=0;i<n;i++){
    if(i>=d){
      double mt=win.median(),mtot=tot.median();
      if(sales[i]>=mt+mtot) cnt++;
    }
    tot.add(sales[i]);
    win.add(sales[i]);
    if(i>=d) win.rem(sales[i-d]);
  }
  cout<<cnt<<"\n";
  delete[]sales;
  return 0;
}