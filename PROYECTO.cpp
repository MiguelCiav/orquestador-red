#include <iostream>
#include <fstream>

using namespace std;

//SECCION_0: Adelanto de declaraciones

class ListaRelaciones;

//SECCION_1: CLASE Dispositivo

class Dispositivo{
    public:
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
    public:
        string tipoDeConexion; 
        int ping;
        int saltos;

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

//SECCION_3: CLASE ListaRelaciones

class ListaRelaciones{
    public:
        Relacion* lista;
        void insertarElemento(string tipoDeConexion, int ping, Dispositivo* destino);
        void mostrarListado();
        bool verificarExistencia(Dispositivo* destino);
        Relacion* buscarRelacion(Dispositivo* destino);
        void eliminarRelacion(Dispositivo *destino);
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

bool ListaRelaciones::verificarExistencia(Dispositivo* destino){

    Relacion* auxiliar = lista;

    while(auxiliar != nullptr){
        if(auxiliar->destino->getHostname() == destino->getHostname()){
            return true;
        }
        auxiliar = auxiliar->siguiente;
    }

    return false;
}

Relacion* ListaRelaciones::buscarRelacion(Dispositivo* destino){

    Relacion* auxiliar = lista;

    while(auxiliar != nullptr){
        if(auxiliar->destino->getHostname() == destino->getHostname()){
            return auxiliar;
        }
        auxiliar = auxiliar->siguiente;
    }

    return nullptr;
};

void ListaRelaciones::eliminarRelacion(Dispositivo *destino){

    Relacion* aux = buscarRelacion(destino);

    if(aux->anterior != nullptr && aux->siguiente != nullptr){

        aux->anterior->siguiente = aux->siguiente;
        aux->siguiente->anterior = aux->anterior;
        
    }

    if(aux->anterior == nullptr && aux->siguiente != nullptr){

        aux->siguiente->anterior = nullptr;
        
    }

    if(aux->anterior != nullptr && aux->siguiente == nullptr){

        aux->anterior->siguiente = nullptr;
        
    }

    if(lista == aux){

        lista = aux->siguiente;

    }

    delete aux;
}

//SECCION_4: CLASE ListaDispositivo

class ListaDispositivo{
    private:
        Dispositivo* lista;
    
    public:
        void insertarElemento(string hostname, string ip);
        void crearRelacion(Dispositivo* A, Dispositivo* B, int ping, string tipoDeConexion);
        void mostrarListado();
        void eliminarDispositivo(Dispositivo *Dispositivo);
        Dispositivo* buscarPorHostname(string hostname);
        Dispositivo* buscarPorIP(string ip);
        ListaDispositivo();
};

ListaDispositivo::ListaDispositivo(){
    lista = nullptr;
}

void ListaDispositivo::eliminarDispositivo(Dispositivo *Dispositivo){

    if(Dispositivo->anterior != nullptr && Dispositivo->siguiente != nullptr){

        Dispositivo->anterior->siguiente = Dispositivo->siguiente;
        Dispositivo->siguiente->anterior = Dispositivo->anterior;
        
    }

    if(Dispositivo->anterior != nullptr && Dispositivo->siguiente == nullptr){
        Dispositivo->anterior->siguiente = nullptr;
    }

    if(lista == Dispositivo){

        if(lista->siguiente == nullptr){
            lista = nullptr;
        } else {
            lista = Dispositivo->siguiente;
        }

    }

    delete Dispositivo;
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

void ListaDispositivo::crearRelacion(Dispositivo* A, Dispositivo* B, int ping, string tipoDeConexion){

    if(!A->relaciones->verificarExistencia(B) && !B->relaciones->verificarExistencia(A)){

        A->relaciones->insertarElemento(tipoDeConexion,ping,B);
        B->relaciones->insertarElemento(tipoDeConexion,ping,A);

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

//SECCION 6: CLASE Utilitaria

class Utilitaria{
    Dispositivo Dispositivos;
    ifstream archivoDescarga;
    ofstream archivoCarga;
    int L;
    int R;

    void Cargar( ){

    }

void  Descargar (string filename, ifstream &archivo, int L, int R){
        if (archivo.is_open()){
            archivo >> L;
            for (int i = 0; i < L; i++){
                Dispositivo NewD;
                archivo >> NewD.hostname;
                archivo >> NewD.ip;
                ListaDispositivo NewLD;
                NewLD.insertarElemento(NewD.hostname, NewD.ip);
            }
            
            archivo >> R;
            for (int i = 0; i < R; i++){
                Relacion NewR;
                ListaDispositivo NewLD;
                string hostname1;
                string hostname2;
                archivo >> hostname1;
                archivo >> hostname2;
                Dispositivo * A = NewLD.buscarPorHostname (hostname1);
                Dispositivo * B = NewLD.buscarPorHostname (hostname2);
                archivo >> NewR.saltos;
                archivo >> NewR.ping;
                archivo >> NewR.tipoDeConexion;
                NewLD.crearRelacion(A, B, NewR.ping, NewR.tipoDeConexion);
            }
            archivo.close();
		} else {
		cout << "No se pudo abrir el archivo" << endl;
	    }

    }
};

//Funcion que imprime en pantalla los datos de universidad, facultad, escuela etc...

void identificacion(){
    cout<<"Universidad Central de Venezuela"<<endl;
    cout<<"Facultad de Ciencias"<<endl;
    cout<<"Escuela de Computacion"<<endl;
    cout<<"Carlos Zavarce V30136703, Miguel Ciavato V30541929"<<endl;
    cout<<endl<<"Menu de opciones: "<<endl;
}

/*Funcion que muestra los sub-menus, retorna true si se regresa al menu principal,
retorna false si se quiere salir de la aplicacion*/

bool sub_menu(int opcion){
    
    int sub_opcion = 0;

    //Agregar informacion
    if(opcion == 1){

        while(sub_opcion != 3 || sub_opcion != 4){

            cout<<endl;
            identificacion();
            cout<<"1. Agregar dispositivo"<<endl;
            cout<<"2. Agregar ruta"<<endl;
            cout<<endl;
            cout<<"3. Volver a principal"<<endl;
            cout<<"4. Salir de la aplicacion"<<endl;
            cout<<endl;

            cin>>sub_opcion;

            switch (sub_opcion) {
                case 1:
                    break;
            
                case 2:
                    break;

                case 3:
                    return true;

                case 4:
                    return false;
            
                default:
                    cout<<"Entrada invalida, intente nuevamente. "<<endl;
                    break;
            }
        }
    }

    //Eliminar informacion
    if(opcion == 2){

        while(sub_opcion != 3 || sub_opcion != 4){

            cout<<endl;
            identificacion();
            cout<<"1. Eliminar dispositivo"<<endl;
            cout<<"2. Eliminar ruta"<<endl;
            cout<<endl;
            cout<<"3. Volver a principal"<<endl;
            cout<<"4. Salir de la aplicacion"<<endl;
            cout<<endl;

            cin>>sub_opcion;

            switch (sub_opcion) {
                case 1:
                    break;
            
                case 2:
                    break;

                case 3:
                    return true;

                case 4:
                    return false;
            
                default:
                    cout<<"Entrada invalida, intente nuevamente. "<<endl;
                    break;
            }
        }
    }

    //Buscar y listar
    if(opcion == 3){

        while(sub_opcion != 5 || sub_opcion != 6){

            cout<<endl;
            identificacion();
            cout<<"1. Consultar dispositivo"<<endl;
            cout<<"2. Listado de dispositivos"<<endl;
            cout<<"3. Buscar ruta (1: 5G, 2: fibra optica, 3: ambas)."<<endl;
            cout<<"4. Dispositivos adyacentes."<<endl;
            cout<<endl;
            cout<<"5. Volver a principal."<<endl;
            cout<<"6. Salir de la aplicacion."<<endl;
            cout<<endl;

            cin>>sub_opcion;

            switch (sub_opcion) {
                case 1:
                    break;
            
                case 2:
                    break;

                case 3:
                    break;

                case 4:
                    break;

                case 5:
                    return true;

                case 6:
                    return false;
            
                default:
                    cout<<"Entrada invalida, intente nuevamente. "<<endl;
                    break;
            }
        }
    }

    //Mostrar respaldos
    if(opcion == 4){

        while(sub_opcion != 3 || sub_opcion != 4){

            cout<<endl;
            identificacion();
            cout<<"1. Listado de dispositivos existentes"<<endl;
            cout<<"2. Listado de dispositivos eliminados"<<endl;
            cout<<"3. Listado de rutas eliminadas"<<endl;
            cout<<endl;
            cout<<"4. Volver a principal"<<endl;
            cout<<"5. Salir de la aplicacion"<<endl;
            cout<<endl;

            cin>>sub_opcion;

            switch (sub_opcion) {
                case 1:
                    break;
            
                case 2:
                    break;

                case 3:
                    break;

                case 4:
                    return true;

                case 5:
                    return false;
            
                default:
                    cout<<"Entrada invalida, intente nuevamente. "<<endl;
                    break;
            }
        }
    }
    
    return false;
}

//Funcion que muestra los creditos

void creditos(){
    cout<<endl;
    cout<<"Proyecto hecho con amol por Carlos Zavarce y Miguel Ciavato"<<endl;
    cout<<"Garantizamos 0 bugs en este codigo"<<endl;
    cout<<"Junio, 2023"<<endl;
}

//Funcion que muestra el menu principal en pantalla

void menu(){
    int opcion = 0;
    
    while(opcion != 6){

        identificacion();
        cout<<"1. Agregar informacion"<<endl;
        cout<<"2. Eliminar informacion"<<endl;
        cout<<"3. Buscar y listar"<<endl;
        cout<<"4. Mostrar respaldos"<<endl;
        cout<<endl;
        cout<<"5. Creditos"<<endl;
        cout<<"6. Salir de la aplicacion"<<endl<<endl;

        cin>>opcion;

        switch(opcion){
            case 1:
                if(!sub_menu(1)){
                    opcion = 6;
                }
                break;
            
            case 2:
                if(!sub_menu(2)){
                    opcion = 6;
                }
                break;
            
            case 3:
                if(!sub_menu(3)){
                    opcion = 6;
                }
                break;

            case 4:
                if(!sub_menu(4)){
                    opcion = 6;
                }
                break;

            case 5:
                creditos();
                break;
            
            case 6:
                break;

            default:
                cout<<"Entrada invalida, intente nuevamente. "<<endl;
        }

        cout<<endl;
    }
}

    
int main(){

    ListaDispositivo dispositivos;

    //PROCEDIMIENTO PARA CREAR NUEVOS DISPOSITIVOS

    dispositivos.insertarElemento("D1","192.168.1.1");
    dispositivos.insertarElemento("D2","192.168.0.1");
    dispositivos.insertarElemento("D3","192.168.1.1");
    dispositivos.insertarElemento("D4","192.168.1.1");

    //PROCEDIMIENTO PARA CREAR LISTAS DE RELACIONES EN DISPOSITIVOS

    dispositivos.buscarPorHostname("D1")->relaciones = new ListaRelaciones;
    dispositivos.buscarPorHostname("D2")->relaciones = new ListaRelaciones;
    dispositivos.buscarPorHostname("D3")->relaciones = new ListaRelaciones;
    dispositivos.buscarPorHostname("D4")->relaciones = new ListaRelaciones;

    //PROCEDIMIENTO PARA CREAR RELACIONES ENTRE DISPOSITIVOS

    dispositivos.crearRelacion(dispositivos.buscarPorHostname("D1"), dispositivos.buscarPorHostname("D2"), 124, "5G");
    dispositivos.crearRelacion(dispositivos.buscarPorHostname("D2"), dispositivos.buscarPorHostname("D3"), 124, "5G");
    dispositivos.crearRelacion(dispositivos.buscarPorHostname("D3"), dispositivos.buscarPorHostname("D4"), 124, "5G");
    
    dispositivos.mostrarListado();

    return 0;
}