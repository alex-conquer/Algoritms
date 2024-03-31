//Реализовать очередь с помощью двух стеков.
//Требования: Очередь должна быть реализована в виде класса. 
//Стек тоже должен быть реализован в виде класса.
#include <iostream>
#include <cassert>
#include <sstream>

class Stack {
public:
    Stack(int n);
    ~Stack();
    int PopStack();
    void PushStack(int data);
    int Size();
    int limit;
    int top;

private:
    int *arr;
};

Stack::Stack(int n) 
{   
    limit = n;
    arr = new int[limit];
    top = -1;
}

Stack::~Stack()
{
    delete[] arr;
}

void Stack::PushStack(int data)
{
    if (top == limit - 1) {
          std::cout<<"NO";
        }
        arr[++top] = data;
}

int Stack::PopStack()
{
    assert(top > -1);
    return arr[top--];
}

int Stack::Size()
{   
    return top;
}

class Queue {
public:    

    Queue(int n);
    ~Queue();

    Queue( Queue& ) = delete;
    Queue& operator=( const Queue& ) = delete;

    int PopFront();
    void PushBack(int data);
    int Size();

private:
     Stack *stack1;
     Stack *stack2;
};

int Queue::Size()
{
    return stack1->Size();
}

Queue::Queue(int n)
{
    stack1 = new Stack(n);
    stack2 = new Stack(n);

}

Queue::~Queue()
{
    stack1->~Stack();
    stack2->~Stack();
}

int Queue::PopFront()
{   
    while (stack1->top!=-1){
        int buffer = stack1->PopStack();
        stack2->PushStack(buffer);
    }
    int FirstElementInQueue = stack2->PopStack();
    while (stack2->top!=-1)
    {
        int buffer = stack2->PopStack();
        stack1->PushStack(buffer);
    }
    return FirstElementInQueue;
}

void Queue::PushBack(int data)
{
    stack1->PushStack(data);
}



int main()
{   
    int n;
    std::cin>>n;
    Queue queue1(n);

    bool result = true;
    int count = 0;
    for (int i = 0; i < n; i++){
        count++;
        int command = 0;
        int data = 0;
        std::cin>>command>>data;
        if ((command==2)&&(queue1.Size()==-1)&&(data!=-1)){
         std::cout<<"NO"<<std::endl;
         return 0;
        }
        else {
        switch( command ) {
            case 2:
                if (( queue1.Size() > -1 )&&(data!=-1)) {
                    result = result && queue1.PopFront() == data;
                } else {
                    result = result && data == -1;
                }
                break;
            case 3:
                 queue1.PushBack( data );
                 break;
            default:
                 assert( false );
           }
	}
    }
std::cout << (result ? "YES" : "NO")<<std::endl;
return 0;
}