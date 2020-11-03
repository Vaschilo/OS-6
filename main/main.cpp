#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>
using namespace std;


class Store
{
private: 
    int num;
public:
    Store() { this->num = 100; }
    Store(int num) { this->num = num; }
    bool consume() 
    {
        this_thread::sleep_for(chrono::milliseconds(20));
        if (this->num > 0)
        {
            this->num -= 1;
            return true;
        }
        return false;
    }
    void produse() { this_thread::sleep_for(chrono::milliseconds(50)); this->num += 1; }
    int GetNum() { return this->num; }
};

void consumer(Store& store)
{
    while (1)
    {
        if (store.consume()) cout << "\tI will buy\ton store " << store.GetNum() << endl;
        else cout << " ignore\ton store " << store.GetNum() << endl;
    }
}

void produser(Store& store)
{
    while (1)
    {
        store.produse();
        cout << "Prodused\ton store " << store.GetNum() << endl;
    }
}

int main()
{
    Store st(50);

    thread tr(consumer, std::ref(st));
    tr.detach();
    thread tr2(consumer, std::ref(st));
    tr2.detach();
    thread tr3(consumer, std::ref(st));
    tr3.detach();

    thread tr4(produser, std::ref(st));
    tr4.detach();

    this_thread::sleep_for(chrono::milliseconds(1000));
    
    return 0;
}