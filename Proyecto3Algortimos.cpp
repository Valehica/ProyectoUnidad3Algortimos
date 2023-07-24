#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <cstdlib>
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <random>
#include <chrono>
#include <map>
#include <algorithm>

using namespace std;
using namespace std::chrono;
using std::cout;
using std::endl;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::chrono::duration_cast;

void clear() {
    #ifdef _WIN32
        system("cls"); // Comando para borrar la pantalla en Windows
    #else
        system("clear"); // Comando para borrar la pantalla en Linux
    #endif
}

void cambio(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}
/*ALGORIMOS DE ORDENAMINETO EXPONENCIAL*/
void selectionSort(vector<int>& arr, int type){//ascendente o descendente
    int n = arr.size();
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(type == 1){//ascendente
                if(arr[j] > arr[i]){
                    cambio(arr[j], arr[i]);
                }
            }else{//descendente
                if(arr[j] < arr[i]){
                    cambio(arr[j], arr[i]);
                }
            }        
        }
    }
}
void bubbleSort(vector<int>& arr, int type){
    int n = arr.size();
    for(int i = 0; i < n -1; i++){
        for (int j = 0; j < n -1 ; j++){
            if(type == 1){//ascendente
                if(arr[j] > arr[j+1]){
                    cambio(arr[j], arr[j+1]);
                }
            }else{//descendente
                if(arr[j] < arr[j+1]){
                    cambio(arr[j], arr[j+1]);
                }
            }
        }
    }
}
void insertionSort(vector<int>& arr, int type){
    int n = arr.size();
    for(int i = 0; i < n; i++){
        int j = i;
        if(type == 1){
            while(j > 0 && arr[j-1] > arr[j]){
                cambio(arr[j], arr[j-1]);
                j--;
            }
        }else{
           while(j > 0 && arr[j-1] < arr[j]){
                cambio(arr[j], arr[j-1]);
                j--;
            } 
        }  
    }
}
//shellsort
int getMaxK(int n) {
    int k = 1;
    while (k <= n / 3) {
        k = k * 3 + 1;
    }
    return k;
}
void shellSort(vector<int>& arr, int type) {
    int n = arr.size();
    int gap = getMaxK(n);

    while (gap > 0) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j = i;

            if(type == 1){
                while (j >= gap && arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
            }else{
                while (j >= gap && arr[j - gap] < temp) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
            }
            arr[j] = temp;
        }

        // Reducir el valor del gap para la siguiente iteración
        gap = (gap - 1) / 3;
    }
}

/*ALGORIMOS DE ORDENAMINETO LOGARITMICO*/
//merge sort
vector<int> merge(vector<int>& left, vector<int>& right, int type) {
    vector<int> merged;
    size_t leftIdx = 0;
    size_t rightIdx = 0;

    while (leftIdx < left.size() && rightIdx < right.size()) {
        //Cambiar de ascendente o descendente
        if(type == 1){
            if (left[leftIdx] <= right[rightIdx]) {
                merged.push_back(left[leftIdx]);
                leftIdx++;
            } else {
                merged.push_back(right[rightIdx]);
                rightIdx++;
            }
        }else{
            if (left[leftIdx] >= right[rightIdx]) {
                merged.push_back(left[leftIdx]);
                leftIdx++;
            } else {
                merged.push_back(right[rightIdx]);
                rightIdx++;
            }
        }
        
    }
    while (leftIdx < left.size()) {
        merged.push_back(left[leftIdx]);
        leftIdx++;
    }
    while (rightIdx < right.size()) {
        merged.push_back(right[rightIdx]);
        rightIdx++;
    }
    return merged;
}
vector<int> mergeSortReturn(vector<int>& arr, int type) {
    if (arr.size() <= 1) {
        return arr;
    }

    size_t mid = arr.size() / 2;
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());

    left = mergeSortReturn(left, type); 
    right = mergeSortReturn(right, type); 
    return merge(left, right, type); 
}
void mergeSort(vector<int>& arr, int type){
    vector<int> copyArr = mergeSortReturn(arr, type);
    arr= copyArr;
}
//Quicj sort
int partition(vector<int>& arr, int low, int high, int type) {
    int pivot = arr[high]; 
    int i = low - 1; 

    for (int j = low; j <= high - 1; j++) {
        if(type == 1){
            if (arr[j] <= pivot) {
                i++;
                cambio(arr[i], arr[j]);
            }    
        }else{
            if (arr[j] >= pivot) {
                i++;
                cambio(arr[i], arr[j]);
            }
        }  
    }

    cambio(arr[i + 1], arr[high]); 
    return i + 1;
}

void quickSortRecursive(vector<int>& arr, int low, int high, int type) {
    if (low < high) {
        int pivot = partition(arr, low, high, type); 
        quickSortRecursive(arr, low, pivot - 1, type); 
        quickSortRecursive(arr, pivot + 1, high, type); 
    }
}

void quickSort(vector<int>& arr, int type) {
    if (arr.empty()) {
        return;
    }

    int low = 0;
    int high = arr.size() - 1;
    quickSortRecursive(arr, low, high, type);
}

//heap sort
void heapify(vector<int>& arr, int n, int i, int type) {
    int largest = i; 
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    //cambiar de ascendente y descendente
    if(type == 1){
        // Si el hijo izquierdo es más grande que la raíz
        if (left < n && arr[left] > arr[largest]) {
            largest = left;
        }

        // Si el hijo derecho es más grande que el mayor actual
        if (right < n && arr[right] > arr[largest]) {
            largest = right;
        }
    }else{
        // Si el hijo izquierdo es más grande que la raíz
        if (left < n && arr[left] < arr[largest]) {
            largest = left;
        }

        // Si el hijo derecho es más grande que el mayor actual
        if (right < n && arr[right] < arr[largest]) {
            largest = right;
        }
    }
    
    // Si el mayor no es la raíz, intercambiar y hacer heapify en el subárbol afectado
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest, type);
    }
}

void heapSort(vector<int>& arr, int type) {
    int n = arr.size();

    // Construir un Max Heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, type);
    }
    // Extraer elementos del heap uno por uno
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0, type);
    }
}

//Imprimir
void printArray(vector<int> arr){
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " - ";
    }
    cout << endl;
}

/*PARA SABER CUANTOS SEGUNDOS PASAN*/
auto getTimeActual() {
    return high_resolution_clock::now();
}
template<typename T>
double printTime(T start, T end){
    auto timeElapsed = duration_cast<duration<double>>(end - start);
    cout << fixed << setprecision(6) << timeElapsed.count() << endl;
    return timeElapsed.count();
}
/*GENERADOR DE DATOS*/
void menuGeneradorDatos(int nMin, int nMax, vector<int>& aleatNotRepet, vector<int>& aleatSiRept, vector<int>& ordoen, vector<int>& inOrden){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(nMin,nMax);
    int rand = dist(gen);
    uniform_int_distribution<int> distAleatCon(0,rand);
    int number; 
    unordered_set<int> elementosUnicos;

    clear();
    cout << "Generando set de datos: "; 

    for(int i = 0; i < rand; i++){
        ordoen.push_back(i);
        inOrden.push_back(rand-i);
        aleatSiRept.push_back(distAleatCon(gen));
        aleatNotRepet.push_back(i);
    }
    shuffle(aleatNotRepet.begin(), aleatNotRepet.end(), std::mt19937(rd()));
    cout << rand  << " elementos en cada modo fueron generados" << endl;
}

/*MENU*/
int menuAsOdes(){//Menu para saber si es ascendente o descendente
    string opcion;
    bool valor = true;
    while (valor){
        cout << "Carrera de algortimos" << endl;
        cout << "1. Ascendente" << endl;
        cout << "2. Descendente" << endl;
        cout << "Opcion elegida: ";
        cin >> opcion;

        if(opcion == "1"){
            clear();
            return 1; //ascendente
        }else if(opcion == "2"){
            clear();
            return 2; //descendente
        }else{
            clear();
            cout << endl;
            cout << "La opcion elegida es incorrecta, intentalo nuevamente..." << endl << endl;
        }
    } 
    return 0;
}
void carreraPorTipo(int type, string tipoArr, vector<int>& arr){
    vector<int> arrCopy = arr;
    //timepo
    auto timePre = getTimeActual();
    auto timePost = getTimeActual();
    map<string, double> tiempos;
    
    cout << endl;
    cout << "Carrera por el Tablero: Modo " << tipoArr << " comenzo" <<endl;
    
    //accionar cada tipo de busqueda
    cout << "1. BubbleSort, ";
    timePre = getTimeActual();
    bubbleSort(arrCopy, type);
    timePost = getTimeActual();
    tiempos["BubbleSort"] = printTime(timePre, timePost);
    arrCopy = arr; 

    cout << "2. SelectionSort, ";
    timePre = getTimeActual();
    selectionSort(arrCopy, type);
    timePost = getTimeActual();
    tiempos["SelectionSort"] = printTime(timePre, timePost);
    arrCopy = arr; 

    cout << "3. InsertionSort, ";
    timePre = getTimeActual();
    insertionSort(arrCopy, type);
    timePost = getTimeActual();
    tiempos["InsertionSort"] = printTime(timePre, timePost);
    arrCopy = arr; 

    cout << "4. ShellSort, ";
    timePre = getTimeActual();
    shellSort(arrCopy, type);
    timePost = getTimeActual();
    tiempos["ShellSort"] = printTime(timePre, timePost);
    arrCopy = arr; 

    cout << "5. MergeSort, ";
    timePre = getTimeActual();
    mergeSort(arrCopy, type);
    timePost = getTimeActual();
    tiempos["MergeSort"] = printTime(timePre, timePost);
    arrCopy = arr; 

    /*
    cout << "6. QuickSort, ";
    timePre = getTimeActual();
    quickSort(arrCopy, type);
    timePost = getTimeActual();
    tiempos["QuickSort"] = printTime(timePre, timePost);
    arrCopy = arr; 
    */

    cout << "7. HeapSort, ";
    timePre = getTimeActual();
    heapSort(arrCopy, type);
    timePost = getTimeActual();
    tiempos["HeapSort"] = printTime(timePre, timePost);
    arrCopy = arr; 

    auto comienzo = tiempos.begin();
    double valorMinimo = comienzo->second;
    string valorMinString = comienzo->first; 

    for(const auto& elemento: tiempos){
        if(elemento.second < valorMinimo){
            valorMinimo = elemento.second;
            valorMinString = elemento.first;
        }
    }
    cout << endl << "El ganador es: " << valorMinString << " con un tiempo de " << fixed << setprecision(6) << valorMinimo << " segudnos "<<endl;  
     
}
void carrera(int type, vector<int>& aleatSinRepet, vector<int>& aleatConRept, vector<int>& ordoen, vector<int>& inOrden){
    //Primero ordenado o inversamente ordenado
    if(type == 1){
        //inversamente ordenado
        carreraPorTipo(type, "Inversamente Ordenado", inOrden);
    }else{
        //ordenado
        carreraPorTipo(type, "Ordenado", ordoen);
    }
    //aleat con repeticion
    carreraPorTipo(type, "Aleatorio Sin Duplicados", aleatSinRepet);
    //aleat sin repeticion
    carreraPorTipo(type, "Aleatorio Con Duplicados", aleatConRept);
}

int main() {
    //generacion de dato
    vector<int> aleatSinRep;
    vector<int> aleatConRep;
    vector<int> orden;
    vector<int> inOrden;
    
    int type; //ascendente o descendente 

    /*  PARA EL MAXIMO Y MINIMO DE DATOS

        Datos en el proyecto:
          >> Tablero de puntaje: 90000 - 100000 datos
          >> Determinacion de camino entre aldeas: 50000 - 70000 datos
          >> Dinujo o Renderizado de objetos: 7500 - 15000 datos
    */
    int minDatos = 90000;
    int maxDatos = 100000;

    type = menuAsOdes();
    menuGeneradorDatos(minDatos, maxDatos, aleatSinRep, aleatConRep, orden, inOrden);
    carrera(type, aleatSinRep, aleatConRep, orden, inOrden);
    
    return 0;
}
