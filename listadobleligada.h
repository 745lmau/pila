#include <iostream>
using namespace std;

template <class T>
class ListaDobleLigada
{
        struct Nodo {
        T dato;
        Nodo *sig;
        Nodo *ant;

        Nodo(const T &dato, Nodo *sig = nullptr, Nodo *ant = nullptr)
        : dato(dato), sig(sig), ant(ant) {}
    };

    Nodo *head;
    Nodo *tail;
    size_t cont;
//};
public:
    ListaDobleLigada();
    ~ListaDobleLigada();

    bool empty();

    T* find(const T &dato);

    //Insertar
    void push_front(const T &dato);
    void push_back(const T &dato);
    void insert(const T &dato, size_t p);

   size_t size();

    ListaDobleLigada& operator<<(const T &dato)
    {
        push_back(dato);

        return *this;
    }

    //Recorridos
    void print();
    void print_reverse();
    T* front();
    T* back();

    //eliminar
    void pop_front();
    void pop_back();
    void erase(size_t p);

    void remove_if(const T& dato);
    T* operator[](size_t p)
    {
        size_t pos = 0;
        Nodo *temp = head;

        while(temp != nullptr)
        {
            if (p == pos){
                return &temp->dato;
            }
            temp = temp->sig;
            pos++;
        }
        return nullptr;
    }

//private:
};

template <class T>
ListaDobleLigada<T>::ListaDobleLigada()
{
    head = nullptr;
    tail = nullptr;
    cont = 0;
}

template <class T>
ListaDobleLigada<T>::~ListaDobleLigada()
{
    ///Eliminar todos los nodos;
    while (!empty()){
        pop_front();
    }
}

template <class T>
bool ListaDobleLigada<T>::empty()
{
    return cont == 0;
}

template <class T>
void ListaDobleLigada<T>::push_front(const T &dato)
{
    Nodo *nodo = new Nodo(dato, head);
    if (cont == 0){
        head = nodo;
        tail = nodo;
    } else {
        head->ant = nodo;
        head = nodo;
    }
    cont++;
}

template <class T>
void ListaDobleLigada<T>::push_back(const T &dato)
{
    Nodo *nodo = new Nodo(dato, nullptr, tail);
    if (cont == 0){
        head = nodo;
        tail = nodo;
    } else {
        tail->sig = nodo;
        tail = nodo;
    }
    cont++;
}

template <class T>
size_t ListaDobleLigada<T>::size()
{
    return cont;
}

template <class T>
void ListaDobleLigada<T>::print()
{
    Nodo *temp = head;

    while (temp !=  nullptr)
    {
        cout << temp->dato << endl;
        temp = temp->sig;
    }
}

template <class T>
void ListaDobleLigada<T>::print_reverse()
{
    Nodo *temp = tail;

    while (temp !=  nullptr)
    {
        cout << temp->dato << endl;
        temp = temp->ant;
    }
}

template <class T>
T* ListaDobleLigada<T>::front()
{
    if (empty()){
        return nullptr;
    }
    else{
        return &head->dato;
    }
}

template <class T>
T* ListaDobleLigada<T>::back()
{
    if (empty()){
        return nullptr;
    }
    else{
        return &tail->dato;
    }
}

template <class T>
T* ListaDobleLigada<T>::find(const T &dato)
{
	Nodo *temp = head; // Crear un temporal y asignarle el valor de head
	while (temp !=  nullptr)// Iterar por cada nodo hasta que temporal sea diferente de nulo
    {
        //cout << temp->dato << endl;
        //temp = temp->ant;

        if (dato == temp->dato){//Si nodo->dato es igual a temporal->dato:
        return &temp->dato; //retornar la direcci�n de memoria usando &temporal->dato
        }
        temp = temp->sig;//Saltar al siguiente:  nodo = temporal->sig
    }
        return nullptr; // Si no se encontr� el dato, retornar nullptr

}

template <class T>
void ListaDobleLigada<T>::pop_front()
{
    if (empty()){
        cout << "Lista vacia" << endl;
    }
    else if (cont == 1){
        delete head;
        head = nullptr;
        tail = nullptr;
        cont--;
    }else{
        Nodo *temp = head->sig;

        head->sig->ant = nullptr;
        delete head;
        head = temp;

        cont--;
    }
}

template <class T>
void ListaDobleLigada<T>::pop_back()
{
    if (empty()){
        cout << "Lista vacia" << endl;
    }
    else if (cont == 1){
        delete tail;
        head = nullptr;
        tail = nullptr;
        cont--;
    }else{
        Nodo *temp = tail->ant;
        temp->sig = nullptr;

        delete tail;
        tail = temp;
        cont--;
    }
}

template <class T>
void ListaDobleLigada<T>::insert(const T &dato, size_t p)
{
    if (p>=cont){
        cout << "Posicion no valida" << endl;
    }else if (p == 0){
        push_front(dato);
    }else{
        Nodo *temp = head->sig;
        size_t pos = 1;

        while (temp != nullptr)
        {
            if ( p == pos ){
                Nodo *nodo = new Nodo(dato);

                nodo->sig = temp;
                nodo->ant = temp->ant;

                temp->ant -> sig = nodo;
                nodo->sig -> ant = nodo;

                cont++;
                break;
            }
            temp = temp->sig;
            pos++;
        }
    }
}

template <class T>
void ListaDobleLigada<T>::erase(size_t p){
	if(p >= cont){
		cout << "Posici�n no v�lida" << endl;

	}else if (p == 0){
		pop_front();
	}else if(p == cont-1){
		pop_back();
	}else{
		Nodo *temp = head -> sig;
		size_t pos = 1;

		while (temp != nullptr){
			if(p == pos){
				temp ->ant ->sig = temp -> sig;
				temp -> sig -> ant = temp -> ant;

				delete temp;
				cont--;
				break;
			}
			temp = temp -> sig;
			pos++;
		}
	}
}

template <class T>
void ListaDobleLigada<T>::remove_if(const T& dato){
	if(empty()){
		cout << "Lista vac�a" << endl;
	}else{
		Nodo *temp = head;
		size_t pos = 0;
		while(temp ->sig != nullptr){
			if(temp->dato == dato){
				if(pos == 0){
					pop_front();
					temp = head;
				}else{
					erase(pos);
					temp = head;
					pos = 0;
				}
			} else{
				pos++;
				temp = temp -> sig;
			}
		}
		if(temp->dato == dato){
			pop_back();
		}
	}
}
