#include <iostream>
#include <algorithm>
#include <sstream>
#include <cassert>

struct ArrayS {
    int *arr;
    int size;
    int currentPos;
public:
    ArrayS() : arr(nullptr), size(0), currentPos(0) {}
};

template <typename T>
int AddToArray(T* &arr1, int size1, ArrayS arr2, int size2)
{   
    int border = size1;
    for (int i = arr2.currentPos; i < arr2.currentPos; i++) {
        arr1[border+i] = arr2.arr[i];
        size1++;
    }
    return size1;
}

template <typename T>
void assignHeap(T* &arr1, int index1, int index2) {
    if (index1 == index2)
        return;

    T temp = arr1[index1];
    arr1[index1] = arr1[index2];
    arr1[index2] = temp;
}

template <typename T>
bool Comparat(const T& a, const T& b) {
    int as = a.arr[a.currentPos];
    int ad = b.arr[b.currentPos];
    return a.arr[a.currentPos] > b.arr[b.currentPos];
}

bool operator<(const ArrayS &a, const ArrayS &b) 
{
    return a.currentPos < b.currentPos;
}

bool CheckTheCurrentPos(const ArrayS &a) 
{
     if (a.currentPos >= a.size) {
        return true;
    }
    else return false;
}

int ExtractMaxElement( ArrayS &a)
{
    if (a.arr == nullptr || a.currentPos < 0 || a.currentPos >= a.size) {
        return 1119999;
    }
    return a.arr[a.currentPos];
}

std::ostream& operator<<(std::ostream &out, const ArrayS &arrayS) {
    for (int i = 0; i < arrayS.size; ++i) {
        out << arrayS.arr[i] << " ";
    }
    return out;
}

template <typename T, bool (*Comparator)(const T&, const T&)>
class Heap
{
public:
    T* heapArray;
    int* exitArray;
    int sizeHeap;
    int exitArraySize;
    Heap();
    ~Heap();
    void Insert(T);
    void LetMeSee(T* arr, int size);
    void Add(T);
    void ExtractMax();
private:
    void SiftUp(T);
    bool IsEmpty();
    void fillTheVoid();
    bool Siftdown(int index);
};

template<typename T, bool (*Comparator)(const T&, const T&)>
bool Heap<T, Comparator>::Siftdown(int index)
{
     int parent = index;
    int leftChild = 2 * parent + 1; // Индекс левого потомка
    int rightChild = 2 * parent + 2; // Индекс правого потомка

    // Проверяем, существует ли левый потомок
    if (leftChild < sizeHeap) {
        // Выбираем потомка с меньшим приоритетом, если он существует
        int minChild = leftChild;
        if (rightChild < sizeHeap && Comparator(heapArray[leftChild], heapArray[rightChild])) {
            minChild = rightChild;
        }
        
        // Сравниваем значение потомка с родителем
        if (Comparator(heapArray[parent], heapArray[minChild])) {
            // Если значение потомка меньше, меняем их местами и вызываем Siftdown для потомка
            std::swap(heapArray[parent], heapArray[minChild]);
            Siftdown(minChild);
        }
    }
    return true;
}

template<typename T, bool (*Comparator)(const T&, const T&)>
bool Heap<T, Comparator>::IsEmpty()
{
    if (sizeHeap>=0) {
        return true;
    } return false;
}

template <typename T, bool (*Comparator)(const T&, const T&)>
Heap<T,Comparator>::Heap(): sizeHeap(0),exitArraySize(0)
{   
    heapArray = new T[0];
    exitArray = new int[0];
}

template <typename T, bool (*Comparator)(const T&, const T&)>
Heap<T,Comparator>::~Heap()
{
    delete[] heapArray;
    delete[] exitArray;
}

template <typename T,bool (*Comparator)(const T&, const T&)>
void Heap<T,Comparator>::Insert(T element)
{   
    Add(element);
    if (sizeHeap>1)
    {
        SiftUp(element);
    }
}

template <typename T, bool (*Comparator)(const T&, const T&)>
void Heap<T,Comparator>::fillTheVoid()
{   
    if (sizeHeap > 0) {
        assignHeap(heapArray, 0, sizeHeap-1);
         sizeHeap--;
    }
}

template <typename T, bool (*Comparator)(const T&, const T&)>
void Heap<T,Comparator>::ExtractMax()
{   
    while (sizeHeap>0) {
    int answer = 0;
        if (IsEmpty()) {
            answer = ExtractMaxElement(heapArray[0]);
        }
        if (answer!=1119999) {
            exitArray[exitArraySize] = answer;
            exitArraySize++;
        }
        heapArray[0].currentPos++;
        if (CheckTheCurrentPos(heapArray[0])) {
            fillTheVoid();
        }
        Siftdown(0);

        // if (sizeHeap == 1) {
        //         exitArraySize = AddToArray(exitArray, exitArraySize, heapArray[0], sizeHeap);
                
        //     }   
        
    }
}

template <typename T, bool (*Comparator)(const T&, const T&)>
void Heap<T,Comparator>::Add(T element)
{
    T* tempArray = new T[sizeHeap + 1];
    for (int i = 0; i <= sizeHeap; ++i) {
        tempArray[i] = heapArray[i];
    }
    
    tempArray[sizeHeap] = element;
    delete [] heapArray;
    heapArray = tempArray;
    sizeHeap++;
}

template <typename T, bool (*Comparator)(const T&, const T&)>
void Heap<T,Comparator>::SiftUp(T element)
{
    int currentIndex = sizeHeap-1;
    while (currentIndex > 0) {
        int parentIndex = (currentIndex - 1) / 2;
        if (Comparator(heapArray[parentIndex], heapArray[currentIndex])) {
            std::swap(heapArray[parentIndex], heapArray[currentIndex]);
            currentIndex = parentIndex;
        } else {
            break;
        }
    }
}

template <typename T, bool (*Comparator)(const T&, const T&)>
void Heap<T, Comparator>::LetMeSee(T* arr, int size)
{   
    for (int i = 0; i < size; i++){
        std::cout<<arr[i]<<std::endl;;
    }
    std::cout<<std::endl;
}


void run(std::istream& input, std::ostream& output) {
    ArrayS arrayS;
    Heap<ArrayS, (Comparat<ArrayS>)> heap;
    int n;
    input >> n;
    for (int i = 0; i < n; i++) {
        int size = 0;
        input >> size;
        int *arr = new int[size];
        for (int j = 0; j < size; j++) {
            input >> arr[j];
        }
        arrayS.size = size;
        arrayS.arr = arr;
        arrayS.currentPos = 0;

        ArrayS copyArrayS = arrayS;
        heap.Insert(copyArrayS);
    }
    heap.ExtractMax();
    for (int i = 0; i < heap.exitArraySize; i++) {
        output << heap.exitArray[i] << " ";
    }
}

void testQueue()
{
  {
    std::stringstream input;
    std::stringstream output;
    input << "3\n"  // Количество массивов
          << "1\n"  // Размер первого массива
          << "6\n"  // Элементы первого массива
          << "2\n"  // Размер второго массива
          << "50 90\n"  // Элементы второго массива
          << "3\n"  // Размер третьего массива
          << "1 10 70\n";  // Элементы третьего массива
    run(input, output);
    assert(output.str() == "1 6 10 50 70 90 ");
  }
  {
    std::stringstream input;
    std::stringstream output;
    input << "2\n"
          << "2\n"
          << "4 8\n"
          << "1\n"
          << "-5\n";
    run(input, output);
    assert(output.str() == "-5 4 8 ");
  }
  {
    std::stringstream input;
    std::stringstream output;
    input << "0\n";
    run(input, output);
    assert(output.str() == "");
  }
  {
    std::stringstream input;
    std::stringstream output;
    input << "7\n"
          << "1\n"
          << "-5\n"
          << "3\n"
          << "-1 3 4\n"
          << "1\n"
          << "111\n"
          << "2\n"
          << "-4 -1\n"
          << "1\n"
          << "2\n"
          << "2\n"
          << "2 3\n"
          << "1\n"
          << "0\n";
    run(input, output);
    assert(output.str() == "-5 -4 -1 -1 0 2 2 3 3 4 111 ");
  }
   {
    std::stringstream input;
    std::stringstream output;
    input << "3\n"
          << "2\n"
          << "5 5\n"
          << "3\n"
          << "5 5 5\n"
          << "4\n"
          << "5 5 5 5\n";
    run(input, output);
    assert(output.str() == "5 5 5 5 5 5 5 5 5 ");
  }
  {
    std::stringstream input;
    std::stringstream output;
    input << "3\n"
          << "3\n"
          << "1 2 3\n"
          << "3\n"
          << "4 5 6\n"
          << "3\n"
          << "7 8 9 \n";
    run(input, output);
    assert(output.str() == "1 2 3 4 5 6 7 8 9 ");
  }
   {
    std::stringstream input;
    std::stringstream output;
    input << "3\n"
          << "0\n"
          << "0\n"
          << "0\n"
          << "0\n";
    run(input, output);
    assert(output.str() == "");
}
}

int main() {

	run( std::cin, std::cout );
//	testQueue();
//    std::cout<<"test ok";
	return 0;
}