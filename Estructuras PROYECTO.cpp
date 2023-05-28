#include <iostream>
#include <math.h>
#include <fstream>
#include <stdio.h>
#include <string>
using namespace std;

//SECCION_0: Adelanto de declaraciones

class ListaRelaciones;

//SECCION_1: CLASE Dispositivo

class Dispositivo{
    private:
        string hostname;
        string ip;
        int numeroDeRelaciones;

    public:
        ListaRelaciones *relaciones;
        Dispositivo *siguiente;
        Dispositivo *anterior;

        Dispositivo(string hostname, string ip);
        string getHostname();
        string getIp();
        void sumarNumeroDeRelaciones();
};

Dispositivo::Dispositivo(string hostname, string ip){
    this->hostname = hostname;
    this->ip = ip;
    numeroDeRelaciones = 0;
    siguiente = nullptr;
    anterior = nullptr;
}

string Dispositivo::getHostname(){
    return hostname;
}

string Dispositivo::getIp(){
    return ip;
}

void Dispositivo::sumarNumeroDeRelaciones(){
    numeroDeRelaciones++;
}

//SECCION_2: CLASE Relacion

class Relacion{
    private:
        string tipoDeConexion; 
        int ping;

    public:
        Dispositivo *destino;
        Relacion *siguiente;
        Relacion *anterior;

        Relacion(string tipoDeConexion, int ping, Dispositivo *destino);
        string getTipoDeConexion();
        int getPing();
};

Relacion::Relacion(string tipoDeConexion, int ping, Dispositivo *destino){
    this->tipoDeConexion = tipoDeConexion;
    this->ping = ping;
    this->destino = destino;
    anterior = nullptr;
    siguiente = nullptr;
}

string Relacion::getTipoDeConexion(){
    return tipoDeConexion;
}

int Relacion::getPing(){
    return ping;
}

//SECCION_3: CLASE ListaDispositivo

class ListaDispositivo{
    private:
        Dispositivo* lista;
    
    public:
        void insertarElemento(string hostname, string ip);
        void mostrarListado();
        Dispositivo* buscarPorHostname(string hostname);
        Dispositivo* buscarPorIP(string ip);
        ListaDispositivo();
};

ListaDispositivo::ListaDispositivo(){
    lista = nullptr;
}

void ListaDispositivo::insertarElemento(string hostname, string ip){
    Dispositivo *nuevoDispositivo = new Dispositivo(hostname, ip);

    if(lista == nullptr){
        lista = nuevoDispositivo;
    } else {
        nuevoDispositivo->siguiente = lista;
        lista->anterior = nuevoDispositivo;
        lista = nuevoDispositivo;
    }
}

void ListaDispositivo::mostrarListado(){
    Dispositivo* actual = lista;

    while(actual != nullptr){
        cout<<actual->getHostname()<<" ";
        cout<<actual->getIp()<<endl;
        actual = actual->siguiente;
    }
}

Dispositivo* ListaDispositivo::buscarPorHostname(string hostname){
    Dispositivo* actual = lista;

    while(actual != nullptr){
        if(actual->getHostname() == hostname){
            return actual;
        }
        actual = actual->siguiente;
    }

    return nullptr;
}

Dispositivo* ListaDispositivo::buscarPorIP(string ip){
    Dispositivo* actual = lista;

    while(actual != nullptr){
        if(actual->getIp() == ip){
            return actual;
        }
        actual = actual->siguiente;
    }

    return nullptr;
}

//SECCION_4: CLASE ListaRelaciones

class ListaRelaciones{
    public:
        Relacion* lista;
        void insertarElemento(string tipoDeConexion, int ping, Dispositivo* destino);
        void mostrarListado();
        ListaRelaciones();
};

ListaRelaciones::ListaRelaciones(){
    lista = nullptr;
}

void ListaRelaciones::insertarElemento(string tipoDeConexion, int ping, Dispositivo* destino){
    Relacion *nuevaRelacion = new Relacion(tipoDeConexion, ping, destino);

    if(lista == nullptr){
        lista = nuevaRelacion;
    } else {
        nuevaRelacion->siguiente = lista;
        lista->anterior = nuevaRelacion;
        lista = nuevaRelacion;
    }
}

void ListaRelaciones::mostrarListado(){
    Relacion* actual = lista;

    while(actual != nullptr){
        cout<<actual->destino->getHostname()<<" ";
        cout<<actual->getTipoDeConexion()<<" ";
        cout<<actual->getPing()<<endl;
        actual = actual->siguiente;
    }
}

//SECCION 5: BACKTRACKING

//5.1. Pila de dispositivos recorridos

struct nodo{
    Dispositivo* Dispositivo;
    nodo* next;
};

class pilaDispositivos{
    private:
        nodo* head;

    public:
        void insertarElemento(Dispositivo* Dispositivo);
        bool verificarExistencia(Dispositivo* Dispositivo);
        void imprimirPila();
        Dispositivo* extraerElemento();
        pilaDispositivos();
    
};

pilaDispositivos::pilaDispositivos(){
    head = nullptr;
}

void pilaDispositivos::imprimirPila(){

    nodo* auxiliar = head;

    while(auxiliar != nullptr){

        cout<<auxiliar->Dispositivo->getHostname()<<" - ";
        auxiliar = auxiliar->next;

    }
}

void pilaDispositivos::insertarElemento(Dispositivo* Dispositivo){

    if(head == nullptr){
        head = new nodo;
        head->Dispositivo = Dispositivo;
        head->next = nullptr;
    } else {
        nodo* nuevoNodo = new nodo;
        nuevoNodo->next = head;
        nuevoNodo->Dispositivo = Dispositivo;
        head = nuevoNodo;
    }

}

bool pilaDispositivos::verificarExistencia(Dispositivo* Dispositivo){

    nodo* comparador = head;

    while(comparador != nullptr){
        if(comparador->Dispositivo->getHostname() == Dispositivo->getHostname()){
            return true;
        }
        comparador = comparador->next;
    }

    return false;
}

Dispositivo* pilaDispositivos::extraerElemento(){
    
    if(head != nullptr){

        nodo* aux = head;
        Dispositivo* retorno = head->Dispositivo;
        head = head->next;
        delete aux;
        return retorno;

    }

    return nullptr;
}

void BuscarRuta(Dispositivo* origen, Dispositivo* destino, pilaDispositivos &pila){

    Relacion* relacionActual = origen->relaciones->lista;

    while(relacionActual != nullptr){

        if(!pila.verificarExistencia(relacionActual->destino)){

            if(relacionActual->destino->getHostname() == destino->getHostname()){

                cout<<"DESTINO CONSEGUIDO ";
                cout<<destino->getHostname()<<" - ";
                pila.imprimirPila();
                cout<<endl;

            } else {

                pila.insertarElemento(relacionActual->destino);
                BuscarRuta(relacionActual->destino, destino, pila);

            }
        }

        relacionActual = relacionActual->siguiente;
    }

    pila.extraerElemento();

}

void crearRelacion(Dispositivo *&Dispositivo1, Dispositivo *&Dispositivo2, int ping, string conexion){

    Dispositivo1->relaciones->insertarElemento(conexion,ping,Dispositivo2);
    Dispositivo2->relaciones->insertarElemento(conexion,ping,Dispositivo1);

}

//SECCION 6: CLASE Utilitaria

class Utilitaria{
    Dispositivo Dispositivos;
    ifstream archivoDescarga;
    ofstream archivoCarga;
    int L;
    int R;

    void Cargar( ){

    }

    void  Descargar (){

    }

    void crearRelaciones(){

    }

    void buscarRelaciones() {

    }
};

int main(){



    return 0;
}