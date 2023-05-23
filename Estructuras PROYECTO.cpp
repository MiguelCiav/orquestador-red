#include <iostream>
#include <math.h>
#include <fstream>
#include <stdio.h>
#include <string>
using namespace std;



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

class Dispositivo{
    string hostname;
    string ip;
    Relacion relaciones; 
    Dispositivo *siguiente;
    Dispositivo *anterior; 
};

class Relacion{
    int tipoDeConexion; 
    int ping;
    Dispositivo *destino;
    Relacion *siguiente;
    Relacion *anterior;
};

class Lista {
    Lista *siguiente;
    Lista *anterior;

    void MostrarElemento (){

    }

    void eliminarElemento(){

    }

    void insertarElemento(){

    }

    void buscarElemento(){

    }

    void ordenar(){

    }
};