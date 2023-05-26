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

    public:
        ListaRelaciones *relaciones;
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
    private:
        Relacion* lista;
    
    public:
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

    //Crear dispositivos en una lista de dispositivos

    dispositivos.insertarElemento("ABC","192.168.0.1");
    dispositivos.insertarElemento("DEF","192.168.1.1");
    dispositivos.mostrarListado();

    //Buscar por hostname

    cout<<endl<<"PRUEBA BUSQUEDA: "<<endl;
    Dispositivo *d1 = dispositivos.buscarPorHostname("ABC");
    cout<<d1->getHostname()<<" "<<d1->getIp();
    cout<<endl;

    //Crear Relacion

    cout<<endl<<"PRUEBA RELACION: "<<endl;

    d1->relaciones = new ListaRelaciones; //Crear una nueva lista de relaciones en el dispositivo
    d1->relaciones->insertarElemento("5G",124, dispositivos.buscarPorHostname("DEF")); //Insertar "DEF"
    d1->relaciones->mostrarListado(); //Mostrar relaciones

    return 0;
}