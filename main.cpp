#include <iostream>
#include <cstring>
#include <cstdio>

using namespace std;

template <typename T>
class TVector {
public:
    size_t Size;
    TVector(size_t newCapacity);
    TVector();
    ~TVector ();
    void PushBack (T value);
    void PrintVector ();
    T* Data;
    size_t Capacity;
    size_t GetOptimalCapacity (size_t newSize);
    void Resize (size_t newSize);
    size_t GetSize ();
};

template <typename T>
TVector<T>::TVector() {
    Capacity = 1;
    Size = 0;
    Data = new T[Capacity];
}

template <typename T>
TVector<T>::TVector (size_t newCapacity) {
    Capacity = 1;
    Size = 0;
    Capacity = GetOptimalCapacity (newCapacity);
    Data = new T[Capacity];
}

template <typename T>
void TVector<T>::PrintVector () {
    for (int i = 0; i < Size; i++) {
        printf("%u ", Data[i]);
    }
    printf("\n");
}

template <typename T>
void TVector<T>::PushBack (T value){
    Size++;
    if (Size > Capacity) {
        Resize(Size);
    }
    Data[Size - 1] = value;
}

template <typename T>
size_t TVector<T>::GetSize () {
    return Size;
}

template <typename T>
size_t TVector<T>::GetOptimalCapacity (size_t newCap) {
    size_t res = Capacity;
    while (res < newCap) {
        res *= 2;
    }
    return res;
}
template <typename T>
void TVector<T>::Resize (size_t newSize) {
    size_t optimalCap = GetOptimalCapacity(newSize);
    T* newData = new T[optimalCap];
    for (int i = 0; i < Size - 1; i++) {
        newData[i] = Data[i];
    }
    Capacity = optimalCap;
    delete [] Data;
    Data = newData;
    Size = newSize;
}

template <typename T>
TVector<T>::~TVector () {
    delete [] Data;
    Size = 0;
}

int max (int a, int b) {
    return a > b ? a : b;
}


int main() {
    TVector<unsigned int>* source = new TVector<unsigned int>(); //33554432
    char str[2048];

    cin.getline(str, 2048);
    unsigned int num;
    char* st = str;
    int res = 0;
    while (sscanf(st, "%u", &num) == 1) {
        source->PushBack(num);
        res++;
        while (*st != ' ' && *st != '\0') {
            st++;
        }
        if (*st == '\0') {
            break;
        }
        while (*st == ' ') {
            st++;
        }
    }
    source->PushBack(3785344415);
    int startPosition = source->Size;
    
    TVector<int>* lengthes = new TVector<int>();
    int count = 0;
    while (cin.getline(str, 2048)) {
        int i = 0;
        int curLength = 0;
        while (sscanf(str+i, "%u", &num) == 1) {
            source->PushBack(num);
            curLength++;
            count++;
            while (str[i] != ' ' && str[i] != '\0') {
                i++;
            }
            while (str[i] == ' ') {
                i++;
            }
            if (str[i] == '\0') {
                break;
            }
        }
        lengthes->PushBack(curLength);
    }
    TVector<int>* positions = new TVector<int>(max(lengthes->Size+1, 1)); // массив позиций начал строк
    if (lengthes->Size >= 2) {
        positions->Data[0] = 1;
        positions->Data[1] = lengthes->Data[0] + 1;
        positions->Size = 2;
    }
    else {
        positions->Data[0] = 1;
        positions->Size = 1;
    }
    for (int i = 2; i < lengthes->Size; i++) {
        positions->Data[i] = positions->Data[i-1] + lengthes->Data[i-1];
        positions->Size++;
    }
    
    delete lengthes;
    
    int* zFunc = new int[source->Size]; // z-функция
    memset(zFunc, 0, sizeof(int)*source->Size);
    int l = 0, r = 0;
    l += 1;
    l -= 1;
    for (int i = 1; i < source->Size; i++) {
//        if (i <= r) {
//            zFunc[i] = min(r-i+1, zFunc[i-1]);
//        }
        while (i + zFunc[i] < source->Size && source->Data[zFunc[i]] == source->Data[i+zFunc[i]]) {
            zFunc[i]++;
        }
        if (i+zFunc[i]-1 > r) {
            l = i;
            r = i + zFunc[i] - 1;
        }
    }
//    source->PrintVector();
//    positions->PrintVector();
//    for (int i = 0; i < source->Size; i++) {
//        printf("%d ", zFunc[i]);
//    }
//    printf("\n");
//    printf("res = %d\n", res);
    for (int i = 0; i < source->Size; i++) {
        if (zFunc[i] == res) {
            int j = 0;
            while ((positions->Data[j] <= i - res) && (j < positions->Size)) {
                j++;
            }
            printf("%d, %d\n", j, i - res + 1 - positions->Data[j-1]);
        }
    }
    delete source;
    delete [] zFunc;
    delete positions;
    return 0;
}
