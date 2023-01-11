#include "grafo.h"
#include "FuncionCaminosEulerianos.h" //RESUELVE ACTIVIDAD RUTAS (Consigna A)
#include "iostream"
#include <map>
#include <string>

using namespace std;

void AgregarCiudades(Grafo<int> &grafo, map<int,string> &nombres){  // se utiliza para agregar vertices por nombres de ciudades para la consigna A.
    char cad[50];
    int pos=1;
    char opcion='S';
    while (opcion!='N'&&opcion!='n'){
        cout<< "Ingrese el nombre de la ciudad a agregar \n";
        cin.getline(cad,40);
        string str = cad;
        grafo.agregar_vertice(pos);
        nombres.insert(make_pair(pos,str));
        pos++;
        cout<< "Quiere agregar otra ciudad? Cualquier letra para continar, N para parar. \n";
        cin>>opcion;
        cin.ignore();
    }
    opcion='S';
    while (opcion!='N'&&opcion!='n'){
        cout<< "Ingrese el arco a agregar \n Desde: ";
        cin.getline(cad,40);
        string str1 = cad;
        cout<< " Hasta: " ;
        cin.getline(cad,40);
        string str2=cad;
        for(auto it=nombres.begin();it!=nombres.end();it++){
            if(it->second==str1){
                for(auto it2=nombres.begin();it2!=nombres.end();it2++){
                    if(it2->second==str2){
                        grafo.agregar_arco(it->first,it2->first,0);
                    }
                }
            }
        }
        cout<< "Quiere agregar otro arco? Cualquier letra para continar, N para parar. \n";
        cin>>opcion;
        cin.ignore();
    }
}

void MostrarIndiceyNombre(map<int,string> nombres){
    cout <<"Indice " << "Ciudad \n\n";
    for(auto it=nombres.begin(); it!= nombres.end();it++){
        cout<< it->first<< "       "<<it->second<<endl;
    }
    cout<<endl;
}

int main()
{
	Grafo<int> g;               //g, g2, g3 y g4 grafos de prueba

	// Primero los vértices
	g.agregar_vertice(1);
	g.agregar_vertice(2);
	g.agregar_vertice(3);
	g.agregar_vertice(4);
	g.agregar_vertice(5);
	g.agregar_vertice(6);
	g.agregar_vertice(7);
	g.agregar_vertice(8);

	// Luego los arcos
	g.agregar_arco(1, 2, 1);
	g.agregar_arco(1, 3, 1);
	g.agregar_arco(1, 4, 1);
	g.agregar_arco(2, 6, 2);
	g.agregar_arco(3, 5, 3);
	g.agregar_arco(4, 7, 4);
	g.agregar_arco(5, 6, 5);
	g.agregar_arco(5,8,100);

	g.eliminar_arco(5,6);
	g.modificar_costo_arco(5,8,50);

    cout << " Estructura del grafo g:\n" << g << "\n";
    CaminoEuleriano(g);
     //no existe

    Grafo<int> g2;

    g2.agregar_vertice(1);
	g2.agregar_vertice(2);
	g2.agregar_vertice(3);
	g2.agregar_vertice(4);
	g2.agregar_vertice(5);
	g2.agregar_vertice(6);
	g2.agregar_vertice(7);
    g2.agregar_arco(1,2,1);
    g2.agregar_arco(1,3,2);
    g2.agregar_arco(1,4,7);
    g2.agregar_arco(1,6,2);
    g2.agregar_arco(2,3,13);
    g2.agregar_arco(2,5,8);
    g2.agregar_arco(2,7,2);
    g2.agregar_arco(5,6,6);
    g2.agregar_arco(6,7,12356);
    g2.eliminar_vertice(5);

    cout << " Estructura del grafo g2:\n" << g2 << "\n";
    CaminoEuleriano(g2);
    g2.vaciar();
    cout << " Estructura del grafo g2 luego de vaciar:\n" << g2 << "\n";
    CaminoEuleriano(g2);

    Grafo<int> g3;

    g3.agregar_vertice(1);
    g3.agregar_vertice(2);
    g3.agregar_vertice(3);
    g3.agregar_vertice(4);
    g3.agregar_vertice(5);
    g3.agregar_vertice(6);

    g3.agregar_arco(1,2,0);
    g3.agregar_arco(1,4,0);
    g3.agregar_arco(2,3,0);
    g3.agregar_arco(3,4,0);
    g3.agregar_arco(3,5,0);
    g3.agregar_arco(3,6,0);
    g3.agregar_arco(4,5,0);
    g3.agregar_arco(4,6,0);
    cout << "\n Estructura del grafo g3:\n" << g3 << "\n";
    CaminoEuleriano(g3); //ciclo

    Grafo<int> g4;

    g4.agregar_vertice(0);
    g4.agregar_vertice(-1);
    g4.agregar_vertice(2);
    g4.agregar_vertice(3);
    g4.agregar_vertice(4);
    g4.agregar_vertice(5);

    g4.agregar_arco(0,1,9);
    g4.agregar_arco(2,3,4);
    g4.agregar_arco(3,4,0);
    g4.agregar_arco(4,5,0);
    g4.agregar_arco(2,5,0);

    cout << "\n Estructura del grafo g4:\n" << g4 << "\n";
    CaminoEuleriano(g4);

    Grafo<int> g5;
    map<int,string> ciudades;
    AgregarCiudades(g5, ciudades);
    system("cls");                   //limpia la consola de todo lo anterior para facilitar la lectura de la salida para la consigna A.
    cout << "\n Estructura del grafo g5:\n" << g5 << "\n";
    MostrarIndiceyNombre(ciudades);
    CaminoEuleriano(g5);
	return 0;
}
