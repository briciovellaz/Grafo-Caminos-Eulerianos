#ifndef FUNCIONCAMINOSEULERIANOS_H_INCLUDED
#define FUNCIONCAMINOSEULERIANOS_H_INCLUDED
#include <vector>
#include "Grafo.h"

using namespace std;

bool ArcoValido(int v, int u, Grafo<int> &g);
void ImprimirCamino(int v, Grafo<int> &g);
void CaminoEuleriano();
int ContarVerticesConectados(int u, vector<bool> &visitados, Grafo<int> g);
bool esConexo(Grafo<int> grafo);

bool esConexo(Grafo<int> grafo){    // verifica si el grafo es conexo mediante un DFS desde el primer vertice
    vector<bool> visitados;
    visitados = vector<bool>(grafo.devolver_longitud()+1,false);
    list<int> vertices;
    grafo.devolver_vertices(vertices);
    auto it=vertices.begin();
    int u = *it;
    int c2 = ContarVerticesConectados(u, visitados, grafo);
    return (c2==grafo.devolver_longitud());
}

void CaminoEuleriano(Grafo<int> grafo){

    list<int> vertices;
    grafo.devolver_vertices(vertices);

    if (!grafo.esta_vacio()){  // verifica que el grafo tenga vertices
        if (esConexo(grafo)){   //verifica que el grafo sea conexo
            int impares = 0; // cantidad de vertices con grado impar
            int vertice_impar; // guarda el vertice con grado impar si existe
            for(auto itVertices=vertices.begin(); itVertices!=vertices.end();itVertices++){
                if(grafo.cantidad_adyacentes(*itVertices)==0){
                    cout<< "El grafo tiene vertices sin adyacentes y no existe un camino que lo recorra. \n";   // si algun vertice no tiene adyacentes termina el algoritmo
                    return;
                }
                if(grafo.cantidad_adyacentes(*itVertices)%2==1){
                    impares++;                      //cuenta de vertices impares en el grafo
                    vertice_impar =*itVertices;    // guarda un vertice impar
                }
            }

            if(impares==0){

            // si la cantidad de vertices con grado impar es 0, el grafo contiene un CICLO(comienza y termina en el mismo vertice) euleriano
            // y se puede usar cualquier vertice como inicio

                auto it=vertices.begin();   // iterador apuntando al primer vertice del grafo
                Grafo<int> grafoaux=grafo;
                cout<<"Ciclo euleriano";
                ImprimirCamino(*it,grafoaux);// imprimimos el camino euleriano empezando desde el primer vertice.
                cout<<endl;
            }
            else if(impares==2){
            //si la cantidad de vertices con grado impar es 2, el grafo contiene un CAMINO(termina en un vertice distinto al original) euleriano
            // se toma un vertice inicial de grado impar

                Grafo<int> grafoaux=grafo;
                cout<<"Camino euleriano";
                ImprimirCamino(vertice_impar,grafoaux);  //imprime el vertice impar que se guardo anteriormente
                cout<<endl;
            }
            else{  // si no se cumple ninguna de las condiciones anteriores respecto a la paridad de los vertices, no existe un camino euleriano en el grafo.
                cout<<" No existe un camino que atraviese todos los arcos una sola vez ya que se tiene "<< impares<< " vertice/s de grado impar. \n";
            }

        } else {cout<< "El grafo no es conexo y no tiene un camino que lo recorra\n";}
    }else {cout << " El grafo no tiene vertices por lo que no hay caminos. \n";}  // si el grafo es vacio se termina el algoritmo

}

void ImprimirCamino(int v,Grafo<int> &g){

    list<pair<int,int>> adyacentes;
    g.devolver_adyacentes(v,adyacentes); // obtenemos los vertices adyacentes de v
    cout<<" --> "<<v<<""; //imprime el vertice actual
    if(g.cantidad_adyacentes(v)==0){  // si ya no hay vertices adyacentes, vuelve a la instancia anterior
        return;
    }

    if(g.cantidad_adyacentes(v)==1){    // cuando solo hay un vertice adyacente, lo elige para continuar
        auto it=adyacentes.begin();
        int u = it->first;
        g.eliminar_arco(u,v);  // elimina ese arco para no volver a tenerlo en cuenta
        ImprimirCamino(u, g); // sigue con el vertice u
        return;
    }

    for(auto it=adyacentes.begin();it!=adyacentes.end();it++){  // recorre todos los vertices adyacentes de v para encontrar un arco que no sea de corte
        if(ArcoValido(v, it->first, g)){ // si el arco (v, adyacente u) no es de corte, es un arco valido. Luego lo elimina del grafo y lo agrega al camino.
            g.eliminar_arco(v, it->first);
            ImprimirCamino(it->first,g);
            return;
        }
    }

}

bool ArcoValido(int v, int u, Grafo<int> &g){ // verifica si un arco no es puente
    int c1, c2;
    c1 = c2 = 0;
    vector<bool> visitados;

    // eliminamos el arco (v,u) y contamos los arcos alcanzables desde u
    g.eliminar_arco(v, u);
    visitados = vector<bool>(g.devolver_longitud()+1,false);
    c1 = ContarVerticesConectados(u, visitados, g);

    // lo volvemos a agregar y volvemos a contar
    g.agregar_arco(v, u,0);
    visitados = vector<bool>(g.devolver_longitud()+1,false);
    c2 = ContarVerticesConectados(u, visitados, g);

    if(c2 == c1) {return true;} // si c1==c2, entonces (v,u) no es un arco de corte y removerlo no desconecta el grafo
    else		 {return false;}// si c1 != c2, entonces (v, u) es de corte y si se elimina el grafo se vuelve no conexo

}

int ContarVerticesConectados(int u, vector<bool> &visitados, Grafo<int> g){   //DFS para contar los vertices alcanzables desde u
    visitados[u] = true;
    int count = 1;
    list<pair<int,int>> ady;
    g.devolver_adyacentes(u,ady);
    for(auto it=ady.begin();it!=ady.end();it++){
        if(!visitados[it->first]){
            count += ContarVerticesConectados(it->first, visitados, g);
        }
    }
    return count;

}

#endif // FUNCIONCAMINOSEULERIANOS_H_INCLUDED
