#include "ThreadSafeSinglyLinkedList.h"
#include <thread>
#include <mutex>
#include <iostream>

std::mutex mt; // for locking cout to avoid both threads printing at the same time

void thread1work(CLL::ThreadSafeSinglyLinkedList<int>& lst){
    lst.add_front(10);
    lst.add_front(30);
    lst.add_front(50);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::unique_lock<std::mutex> lk(mt);
    std::cout<<"displaying list by thread1"<<std::endl;
    lst.display_list();
    lk.unlock();
    

    if(lst.erase(30)){
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<30<<" found and deleted by thread1"<<std::endl;
    }
    else{
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<30<<" not found by thread1"<<std::endl;
    };

    if(lst.erase(60)){
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<60<<" found and deleted by thread1"<<std::endl;
    }
    else{
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<60<<" not found by thread1"<<std::endl;
    };

    return ;
}


void thread2work(CLL::ThreadSafeSinglyLinkedList<int>& lst){
    lst.add_front(20);
    lst.add_front(40);
    lst.add_front(60);
    std::this_thread::sleep_for(std::chrono::milliseconds(300));


    if(lst.erase(60)){
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<60<<" found and deleted by thread2"<<std::endl;
    }
    else{
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<60<<" not found by thread2"<<std::endl;
    };

    if(lst.erase(30)){
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<30<<" found and deleted by thread2"<<std::endl;
    }
    else{
        std::unique_lock<std::mutex> lk(mt);
        std::cout<<30<<" not found by thread2"<<std::endl;
    };

    lst.erase_tail();
    std::unique_lock<std::mutex> lk(mt);
    std::cout<<"tail element removed by thread2"<<std::endl;
    lk.unlock();
    std::cout<<"displaying list by thread2"<<std::endl;
    lst.display_list();
    

    return;
}

int main(){

    
    CLL::ThreadSafeSinglyLinkedList<int> lst;

    std::thread thread1(thread1work,std::ref(lst));
    std::thread thread2(thread2work,std::ref(lst));

    thread1.join();
    thread2.join();
    return 0;
}