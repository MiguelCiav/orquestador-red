#include <iostream>
#include <fstream>

using namespace std;

//Funcion que imprime en pantalla los datos de universidad, facultad, escuela etc...
void identificacion(){
    cout<<"Universidad Central de Venezuela"<<endl;
    cout<<"Facultad de Ciencias"<<endl;
    cout<<"Escuela de Computacion"<<endl;
    cout<<"Carlos Zavarce V30136703, Miguel Ciavato V30541929"<<endl;
    cout<<endl<<"Menu de opciones: "<<endl;
}

bool sub_menu(int opcion){
    cout<<endl;

    identificacion();
    cout<<"prueba";
    cout<<"prueba 2 kkk";
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
                break;
            
            case 2:
                break;
            
            case 3:
                break;

            case 4:
                break;

            case 5:
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

    menu();

    return 0;
}