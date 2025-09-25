#include<iostream>
#include<random>
using namespace std;



typedef struct node{
    int val;
    node* lef=nullptr;
    node* rt=nullptr;
    node(int val):val(val){}
}node;

class heap{
    public:
        node* head=nullptr;
        int size=0;

        mt19937 engine;
        uniform_int_distribution<int>dist;

        heap():engine(random_device{}()),dist(1,10){}
        ~heap(){clear(head);}
        
        void push(int a){
            auto temp=new node(a);
            head=merge(head,temp);
            size++;
        }
        void pop(){
            if(!size) return;
            node* a=head->lef;
            node* b=head->rt;
            delete head;
            head=merge(a,b);
            size--;
        }
        node* merge(node* a,node* b){
            if(!a || !b) return (!a?b:a);
            if(a->val<b->val){
                swap(a,b);
            }
            if(dist(engine)&1){
                swap(a->lef,a->rt);
            }
            a->lef=merge(a->lef,b);
            return a;
        }
        int top(){
            return head->val;
        }
        bool empty(){
            return head==nullptr;
        }
        void clear(node* curr){
            if(!curr)return;
            clear(curr->lef);
            clear(curr->rt);
            delete curr;
        }
};

int main() {
    
    // Seed the random number generator. Important for the heap's balance.
    srand(time(0));

    heap myHeap;

    // === Test Case 1: Basic push, top, and pop ===
    cout << "--- Test Case 1: Basic Operations ---" << endl;
    myHeap.push(10);
    myHeap.push(5);
    myHeap.push(20);
    myHeap.push(8);

    cout << "Pushed 10, 5, 20, 8." << endl;
    cout << "Top element should be 20. Actual: " << myHeap.top() << endl;

    myHeap.pop(); // Removes 20
    cout << "Popped. Top element should be 10. Actual: " << myHeap.top() << endl;

    myHeap.pop(); // Removes 10
    cout << "Popped. Top element should be 8. Actual: " << myHeap.top() << endl;

    myHeap.pop(); // Removes 8
    cout << "Popped. Top element should be 5. Actual: " << myHeap.top() << endl;
    cout << "Is heap empty? " << (myHeap.empty() ? "No" : "Yes") << endl; // Should be No

    myHeap.pop(); // Removes 5
    cout << "Popped. Is heap empty now? " << (myHeap.empty() ? "Yes" : "No") << endl; // Should be Yes


    // === Test Case 2: Edge Cases ===
    cout << "\n--- Test Case 2: Edge Cases ---" << endl;
    cout << "Trying to pop from an empty heap:" << endl;
    myHeap.pop(); // Should print an error message and not crash
    cout << "Pushing duplicate values (15, 15, 15)." << endl;
    myHeap.push(15);
    myHeap.push(15);
    myHeap.push(15);
    cout << "Top element should be 15. Actual: " << myHeap.top() << endl;
    myHeap.pop();
    cout << "Popped. Top element should still be 15. Actual: " << myHeap.top() << endl;


    // === Test Case 3: Larger Dataset ===
    cout << "\n--- Test Case 3: Larger Dataset ---" << endl;
    heap bigHeap;
    vector<int> random_nums;
    cout << "Pushing 10 random numbers..." << endl;
    for (int i = 0; i < 10000; ++i) {
        int r = rand() % 100;
        random_nums.push_back(r);
        bigHeap.push(r);
    }

    // Sort the vector in descending order to check against the heap
    sort(random_nums.begin(), random_nums.end(), std::greater<int>());

    bool success = true;
    cout << "Popping all numbers and verifying order:" << endl;
    for (int i = 0; i < 10000; ++i) {
        int expected = random_nums[i];
        int actual = bigHeap.top();
        cout << "Expected: " << expected << ", Got: " << actual << endl;
        if (expected != actual) {
            success = false;
        }
        bigHeap.pop();
    }

    if (success) {
        cout << "Test Passed: All numbers popped in correct descending order." << endl;
    } else {
        cout << "Test Failed: Numbers were not in correct order." << endl;
    }

    return 0;
}