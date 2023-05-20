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