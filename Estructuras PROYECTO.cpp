#include <iostream>
#include <math.h>
#include <fstream>
#include <stdio.h>
#include <string>
using namespace std;

//SECCION_1: CLASE Dispositivo

class Dispositivo{
    private:
        string hostname;
        string ip; 

    public:
        //Relacion* relaciones; POR SOLUCIONAR
        Dispositivo *siguiente;
        Dispositivo *anterior;

        Dispositivo(string hostname, string ip);
        string getHostname();
        string getIp();
};

Dispositivo::Dispositivo(string hostname, string ip){
    this->hostname = hostname;
    this->ip = ip;
    siguiente = nullptr;
    anterior = nullptr;
}

string Dispositivo::getHostname(){
    return hostname;
}

string Dispositivo::getIp(){
    return ip;
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

        Relacion(string tipoDeConexion, int ping);
        string getTipoDeConexion();
        int getPing();
};

Relacion::Relacion(string tipoDeConexion, int ping){
    this->tipoDeConexion = tipoDeConexion;
    this->ping = ping;
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

//SECCION_4: CLASE ListaRelaciones

class ListaRelaciones{
    private:
        Relacion* lista;
    
    public:
        void insertarElemento(string tipoDeConexion, int ping);
        void mostrarListado();
        ListaRelaciones();
};

ListaRelaciones::ListaRelaciones(){
    lista = nullptr;
}

void ListaRelaciones::insertarElemento(string tipoDeConexion, int ping){
    Relacion *nuevaRelacion = new Relacion(tipoDeConexion, ping);

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
        cout<<actual->getTipoDeConexion()<<" ";
        cout<<actual->getPing()<<endl;
        actual = actual->siguiente;
    }
}

//SECCION 5: CLASE Utilitaria

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
    ListaDispositivo dispositivos;

    dispositivos.insertarElemento("ABC","192.168.0.1");
    dispositivos.insertarElemento("DEF","192.168.1.1");
    dispositivos.mostrarListado();

    return 0;
}