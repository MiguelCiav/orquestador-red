#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//SECCION_0: Adelanto de declaraciones

class ListaRelaciones;

void quitarComa(string &palabra){

    if(palabra.at(palabra.length() - 1) == ','){
        palabra.pop_back();
    }

}

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
        Dispositivo (){}
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

//SECCION_3: CLASE ListaRelaciones

class ListaRelaciones{
    public:
        Relacion* lista;
        void insertarElemento(string tipoDeConexion, int ping, Dispositivo* destino);
        void mostrarListado();
        bool verificarExistencia(Dispositivo* destino);
        Relacion* buscarRelacion(Dispositivo* destino);
        void eliminarRelacion(Dispositivo *destino);
        void eliminarAdyacentes(Dispositivo* origen);
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

    if(aux->anterior != nullptr && aux->siguiente == nullptr){
        aux->anterior->siguiente = nullptr;
    }

    if(lista == aux){

        if(lista->siguiente == nullptr){
            lista = nullptr;
        } else {
            lista = aux->siguiente;
        }

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
        void eliminarRelacion(Dispositivo* A, Dispositivo* B, int &cantidadEliminada);
        void mostrarListado();
        void eliminarDispositivo(Dispositivo *Dispositivo);
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

void ListaDispositivo::crearRelacion(Dispositivo* A, Dispositivo* B, int ping, string tipoDeConexion){

    if(!A->relaciones->verificarExistencia(B) && !B->relaciones->verificarExistencia(A)){

        A->relaciones->insertarElemento(tipoDeConexion,ping,B);
        B->relaciones->insertarElemento(tipoDeConexion,ping,A);

    }

}

void ListaDispositivo::eliminarRelacion(Dispositivo* A, Dispositivo* B, int &cantidadEliminada){

    if(A->relaciones->verificarExistencia(B) && B->relaciones->verificarExistencia(A)){

        cout<<B->getHostname()<<" ";
        cout<<A->getHostname()<<" ";
        cout<<A->relaciones->buscarRelacion(B)->getPing()<<" ";
        cout<<A->relaciones->buscarRelacion(B)->getTipoDeConexion()<<endl;

        A->relaciones->eliminarRelacion(B);
        B->relaciones->eliminarRelacion(A);

        cantidadEliminada++;

    }

}

ListaDispositivo NewLD;

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
        void copiarPila(pilaDispositivos &pilaNueva);
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

void pilaDispositivos::copiarPila(pilaDispositivos &pilaNueva){

    nodo* aux = head;

    while(aux != nullptr){
        pilaNueva.insertarElemento(aux->Dispositivo);
        aux = aux->next;
    }

};

//5.2 Funcion BuscarRuta

void BuscarRuta(Dispositivo* origen, Dispositivo* destino, pilaDispositivos &pila, pilaDispositivos &soluciones){

    Relacion* relacionActual = origen->relaciones->lista;

    while(relacionActual != nullptr){

        if(!pila.verificarExistencia(relacionActual->destino)){

            if(relacionActual->destino->getHostname() == destino->getHostname()){

                soluciones.insertarElemento(destino);
                pila.copiarPila(soluciones);

            } else {

                pila.insertarElemento(relacionActual->destino);
                BuscarRuta(relacionActual->destino, destino, pila, soluciones);

            }
        }

        relacionActual = relacionActual->siguiente;
    }

    pila.extraerElemento();

}

//5.3 Funcion para eliminar rutas indirectas

void eliminarRutas(ListaDispositivo Dispositivos, Dispositivo* origen, Dispositivo* destino){

    pilaDispositivos pila;
    pilaDispositivos soluciones;
    int cantidadEliminada = 0;

    pila.insertarElemento(origen); 

    BuscarRuta(origen,destino,pila,soluciones);

    Dispositivo *actual = nullptr;
    Dispositivo *anterior = nullptr;

    cout<<"Entre los dispositivos "<<origen->getHostname();
    cout<<" y "<<destino->getHostname()<<" se eliminaron las siguientes rutas: \n\n";

    do{ 
        actual = soluciones.extraerElemento();
        if(anterior != nullptr && actual != nullptr){
            Dispositivos.eliminarRelacion(actual, anterior, cantidadEliminada);
        }
        anterior = actual;
    }while(actual != nullptr);

    cout<<endl<<"Total de rutas eliminadas: "<<cantidadEliminada<<endl;

}

//SECCION 6: CLASE Utilitaria

class Utilitaria{
    public:
        ifstream archivoDescarga;
        ofstream archivoCarga;
        int L;
        int R;

       void CargarDispositivoExist(ofstream &DispositivosNew, Dispositivo Listado[], int L){
            for (int i = 0; i < L; i++) {
            DispositivosNew << "<" << Listado[i].hostname << ">, " << "<" << Listado[i].ip << ">" << endl;
            }
        }

        void CargarDispositivoDelete(string hostname, string ip){

            archivoCarga.open("../Dispositivos_resp.dat");
            archivoCarga << "<" << hostname << ">, " << "<" << ip << ">" << endl;
            archivoCarga.close();

        }

        void CargarRuta(ofstream &RutasEliminadas){

            return;

        }

        void MostrarListado(string Dispositivos_dat, string Dispositivos_resp_dat, string  rutas_resp_dat, int N){
            if (N > 0 and N < 4 ){
                switch (N) {
                case 1:
                    
                    break;
                case 2:
                    
                    break;
                    
                case 3:
                    
                    break;
                }
            }else{
                cout << "Opcion invalida" << endl;
            }
        }

        void Descargar(){
            
            archivoDescarga.open("../Dispositivos.dat");

            if (archivoDescarga.is_open()){
                archivoDescarga >> L;
                for (int i = 0; i < L; i++){
                    
                    string hostname;
                    string ip;

                    archivoDescarga >> hostname;
                    quitarComa(hostname);

                    archivoDescarga >> ip;
                    quitarComa(ip);

                    NewLD.insertarElemento(hostname, ip);

                    NewLD.buscarPorHostname(hostname)->relaciones = new ListaRelaciones;
                }
                
                archivoDescarga >> R;

                for (int i = 0; i < R; i++){

                    string hostname1;
                    string hostname2;
                    string ping;
                    int pingEntero;
                    string tipoDeConexion;

                    archivoDescarga >> hostname1;
                    quitarComa(hostname1),

                    archivoDescarga >> hostname2;
                    quitarComa(hostname2);

                    Dispositivo *A = NewLD.buscarPorHostname(hostname1);

                    if(A == nullptr){
                        A = NewLD.buscarPorIP(hostname1);
                    }

                    Dispositivo *B = NewLD.buscarPorHostname(hostname2);

                    if(B == nullptr){
                        B = NewLD.buscarPorIP(hostname2);
                    }

                    archivoDescarga >> ping;
                    quitarComa(ping);

                    pingEntero = stoi(ping);

                    archivoDescarga >> tipoDeConexion;
                    quitarComa(tipoDeConexion);

                    NewLD.crearRelacion(A, B, pingEntero, tipoDeConexion);
                }

                archivoDescarga.close();

            } else {

                cout << "No se pudo abrir el archivo" << endl;

            }

        }

        Dispositivo *ModArreglo(Dispositivo Listado[],int indicador, int &L, string hostname, string ip){
            if (indicador == 1){
                const int L2 = L+1;
                Dispositivo NewListado[L2];

                for(int i = 0; i < L2; i++){
                    if (i < L){
                        NewListado [i] = Listado [i];
                    }else{
                        NewListado [i].hostname = hostname;
                        NewListado [i].ip = ip;
                    }
                }

                L = L2;

                return NewListado;

            } else if (indicador == 2) {

                const int L2 = L-1;
                int x = 0;

                Dispositivo NewListado[L2];

                for(int i = 0; i < L; i++) {

                    if (Listado[i].hostname == hostname and Listado[i].hostname == ip ){
                        x = 1;
                    }else if (x = 0){
                        NewListado[i].hostname  = hostname;
                        NewListado [i].ip = ip;
                    }else if (x = 1){
                        NewListado [i-1].hostname = hostname;
                        NewListado [i-1].ip = ip;
                    }

                }

                L = L2;
                return NewListado;
            }
        }

    void ListadoDeDispositivos(Dispositivo Listado[], int L){
        for (int i = 0; i < L; i++){
        cout << "<" << Listado[i].hostname << ">, <" << Listado[i].ip << ">" << endl;
        }
    }

    Dispositivo *OrdenarAlfabetico(Dispositivo Listado[], int L){
        for (int i = 0; i < L; i++){
            for (int j = i+1; j < L; j++ ){ 
                if (Listado[i].hostname > Listado[j].hostname){
                    swap(Listado, i, j);
                }
            }
        }
        return Listado;
    }

    Dispositivo *swap(Dispositivo Listado[], int i, int j) {
        string temp1 = Listado[i].hostname;
        string temp2 = Listado[i].ip;
        Listado[i].hostname = Listado[j].hostname;
        Listado[i].ip = Listado[j].ip;
        Listado[j].hostname = temp1;
        Listado[j].ip = temp2;
        return Listado;
    }
};

void ListaDispositivo::eliminarDispositivo(Dispositivo *Dispositivo){

    Utilitaria tool;
    tool.CargarDispositivoDelete(Dispositivo->getHostname(), Dispositivo->getIp());

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

//Funciones de cada parte del Menú

void agregarDispositivo(){

    string hostname;
    string ip;

    cin>>hostname;
    cin>>ip;

    quitarComa(hostname);

    NewLD.insertarElemento(hostname,ip);
    NewLD.buscarPorHostname(hostname)->relaciones = new ListaRelaciones;
    cout<<"El dispositivo "<<hostname<<" ha sido agregado.";
    cout<<endl;

}

void agregarRuta(){

    string hostname1;
    string hostname2;
    string pingEntrada;
    int pingEntero;
    string tipoDeConexion;

    cin>>hostname1;
    cin>>hostname2;
    cin>>pingEntrada;
    cin>>tipoDeConexion;

    quitarComa(hostname1);
    quitarComa(hostname2);
    quitarComa(pingEntrada);

    pingEntero = stoi(pingEntrada);

    NewLD.crearRelacion(NewLD.buscarPorHostname(hostname1),
    NewLD.buscarPorHostname(hostname2),pingEntero,tipoDeConexion);

    cout<<"Se agrego una ruta entre "<<hostname1<<" y "<<hostname2<<".";
    cout<<endl;

}

void eliminarRuta(){

    string ipOHostname1;
    string ipOHostname2;
    Dispositivo *dispositivo1;
    Dispositivo *dispositivo2;
    pilaDispositivos pila;
    pilaDispositivos soluciones;

    cin>>ipOHostname1;
    cin>>ipOHostname2;

    quitarComa(ipOHostname1);

    dispositivo1 = NewLD.buscarPorHostname(ipOHostname1);
    dispositivo2 = NewLD.buscarPorHostname(ipOHostname2);

    if(dispositivo1 != nullptr && dispositivo2 != nullptr){

        pila.insertarElemento(dispositivo1);
        eliminarRutas(NewLD,dispositivo1,dispositivo2);
        return;

    }

    dispositivo1 = NewLD.buscarPorIP(ipOHostname1);
    dispositivo2 = NewLD.buscarPorIP(ipOHostname2);

    if(dispositivo1 != nullptr && dispositivo2 != nullptr){

        pila.insertarElemento(dispositivo1);
        eliminarRutas(NewLD,dispositivo1,dispositivo2);

    }

}

void eliminarAdyacentes(Dispositivo* Origen){

    Relacion* actual = Origen->relaciones->lista;
    Relacion* aux;

    while(actual != nullptr){
        aux = actual;
        aux->destino->relaciones->eliminarRelacion(Origen);
        actual = actual->siguiente;
        delete aux;
    }

}

void EliminarDispositivo(){
    string hostname;

    cin>>hostname;
    eliminarAdyacentes(NewLD.buscarPorHostname(hostname));
    NewLD.eliminarDispositivo(NewLD.buscarPorHostname(hostname));
    
    cout<<"El dispositivo "<<hostname<<" fue eliminado del sistema.";
    cout<<endl;
}

void consultarDispositivo(){

    string ipOHostname;
    Dispositivo* dispositivo;

    cin>>ipOHostname;

    quitarComa(ipOHostname);

    dispositivo = NewLD.buscarPorHostname(ipOHostname);

    if(dispositivo != nullptr){
        cout<<dispositivo->getHostname()<<" "<<dispositivo->getIp();
        return;
    }

    dispositivo = NewLD.buscarPorIP(ipOHostname);

    if(dispositivo != nullptr){
        cout<<dispositivo->getHostname()<<" "<<dispositivo->getIp();
    }

}

void imprimirSoluciones(pilaDispositivos soluciones, Dispositivo* origen){

    Dispositivo* aux;
    aux = soluciones.extraerElemento();
    int cantidad = 1;
    int saltos = 0;
    bool inicio = true;

    while(aux != nullptr){

        if(aux->getHostname() == origen->getHostname() && inicio != true){
            cout<<"Saltos: "<<saltos;
            cantidad++;
            saltos = 0;
            cout<<endl;
        }
         
        cout<<aux->getHostname()<<", ";
        aux = soluciones.extraerElemento();

        inicio = false;
    }

    if(inicio != true){
        cout<<endl<<"Total de rutas encontradas: "<<cantidad<<endl;
    }

}

void buscarRutasEntreDispositivos(){

    string ipOHostname1;
    string ipOHostname2;
    Dispositivo *Dispositivo1;
    Dispositivo *Dispositivo2;

    cin>>ipOHostname1;
    cin>>ipOHostname2;

    Dispositivo1 = NewLD.buscarPorHostname(ipOHostname1);

    if(Dispositivo1 == nullptr){
        Dispositivo1 = NewLD.buscarPorIP(ipOHostname1);
    }

    Dispositivo2 = NewLD.buscarPorHostname(ipOHostname2);

    if(Dispositivo2 == nullptr){
        Dispositivo2 = NewLD.buscarPorIP(ipOHostname2);
    }

    pilaDispositivos pila;
    pilaDispositivos soluciones;

    pila.insertarElemento(Dispositivo1);
    BuscarRuta(Dispositivo1,Dispositivo2,pila,soluciones);
    
    cout<<"Entre los dispositivos "<<Dispositivo1->getHostname()<<
    " y "<<Dispositivo2->getHostname()<<" se encontraron las siguientes rutas: \n";

    imprimirSoluciones(soluciones,Dispositivo1);

}

void ListadoDeDispositivos(){

    NewLD.mostrarListado();

}

void dispositivosAdyacentes(){

    string ipOHostname;
    Dispositivo* dispositivo;

    cin>>ipOHostname;

    dispositivo = NewLD.buscarPorHostname(ipOHostname);

    if(dispositivo != nullptr){
        cout<<"Los dispositivos adyacentes a "<<dispositivo->getHostname()<<" son: \n\n";
        dispositivo->relaciones->mostrarListado();
        return;
    }

    dispositivo = NewLD.buscarPorIP(ipOHostname);

    if(dispositivo != nullptr){
        dispositivo->relaciones->mostrarListado();
    }

}

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

bool sub_menu(char opcion){
    
    char sub_opcion = 0;

    //Agregar informacion LISTO
    if(opcion == '1'){

        while(sub_opcion != '3' || sub_opcion != '4'){

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
                case '1':
                    agregarDispositivo();
                    break;
            
                case '2':
                    agregarRuta();
                    break;

                case '3':
                    return true;

                case '4':
                    return false;
            
                default:
                    cout<<"Entrada invalida, intente nuevamente. "<<endl;
                    break;
            }
        }
    }

    //Eliminar informacion
    if(opcion == '2'){

        while(sub_opcion != '3' || sub_opcion != '4'){

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
                case '1':
                    EliminarDispositivo();
                    break;
            
                case '2':
                    eliminarRuta();
                    break;

                case '3':
                    return true;

                case '4':
                    return false;
            
                default:
                    cout<<"Entrada invalida, intente nuevamente. "<<endl;
                    break;
            }
        }
    }

    //Buscar y listar
    if(opcion == '3'){

        while(sub_opcion != '5' || sub_opcion != '6'){

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
                case '1':
                    consultarDispositivo();
                    break;
            
                case '2':
                    ListadoDeDispositivos();
                    break;

                case '3':
                    buscarRutasEntreDispositivos();
                    break;

                case '4':
                    dispositivosAdyacentes();
                    break;

                case '5':
                    return true;

                case '6':
                    return false;
            
                default:
                    cout<<"Entrada invalida, intente nuevamente. "<<endl;
                    break;
            }
        }
    }

    //Mostrar respaldos
    if(opcion == '4'){

        while(sub_opcion != '3' || sub_opcion != '4'){

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
                case '1':
                    break;
            
                case '2':
                    break;

                case '3':
                    break;

                case '4':
                    return true;

                case '5':
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

    Utilitaria tool;
    tool.Descargar();

    char opcion = '0';
    
    while(opcion != '6'){

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
            case '1':
                if(!sub_menu('1')){
                    opcion = '6';
                }
                break;
            
            case '2':
                if(!sub_menu('2')){
                    opcion = '6';
                }
                break;
            
            case '3':
                if(!sub_menu('3')){
                    opcion = '6';
                }
                break;

            case '4':
                if(!sub_menu('4')){
                    opcion = '6';
                }
                break;

            case '5':
                creditos();
                break;
            
            case '6':
                break;

            default:
                cout<<"Entrada invalida, intente nuevamente. "<<endl;
        }

        cout<<endl;
    }
}

    
int main(){

    menu();

    //Commit salvador

    return 0;
}