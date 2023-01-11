#ifndef GRAFO_H_
#define GRAFO_H_

#include <list>
#include <iostream>
#include <algorithm>

using namespace std;

template <typename C> class Grafo  // Grafo no dirigido.
{

public:
    typedef pair<int, C> Arco;
    typedef pair<int, list<Arco>> nodo;
	// NOTA: Dependiendo de la implementación puede ser necesario incluir otras funciones constructuras
	Grafo();

	~Grafo();
    // Indica si el grafo tiene vertices o no. Complejidad O(1).
	bool esta_vacio() const;

    // Devuelve la cantidad de vertices adyacentes que tiene un vertice. Complejidad O(n)
	int cantidad_adyacentes(int vertice);

    //Devuelve la cantidad de vertices del grafo. Complejidad O(1).
	int devolver_longitud() const;

	//Indica si existe un vertice. Complejidad O(n).
	bool existe_vertice(int vertice) const;

    //Indica si existe un arco entre dos vertices. Complejidad O(n)
	bool existe_arco(int origen, int destino) const;

	// Devuelve el costo de un arco (origen,destino). Complejidad O(n).
	const C & costo_arco(int origen, int destino) const;

    // Recibe una lista vacia y la devuelve con los vertices del grafo en el orden que fueron agregados. Complejidad O(n).  {n = cantidad de vertices}
	void devolver_vertices(list<int> & vertices) const;

    // Recibe una lista vacia y la devuelve con todos los adyacentes de un vertice. Complejidad O(n)
	void devolver_adyacentes(int origen, list<Arco> & adyacentes) const;

    //Agrega un vertice al grafo. Complejidad O(1)
	void agregar_vertice(int vertice);

    //Elimina un vertice y todos sus arcos. Complejidad O(n^2) en el peor caso vertice conectado a todos los demas nodos).
	void eliminar_vertice(int vertice);

    //Modifica el costo de un arco entre 2 vertices. Complejidad O(n)
	void modificar_costo_arco(int origen, int destino, const C & costo);

    // Conecta 2 vertices. Complejidad O(n)
	void agregar_arco(int origen, int destino, const C & costo);

    // Desconecta 2 vertices. Complejidad O(n)
	void eliminar_arco(int origen, int destino);

    // Vacia el grafo. Complejidad O(1).
	void vaciar();

private:

    list<nodo> grafo;

};

template <typename C> Grafo<C>::Grafo(){}
template <typename C>	Grafo<C>::~Grafo(){}



template <typename C> bool Grafo<C>::esta_vacio() const
{
    return grafo.empty();
}

template<typename C> int Grafo<C>::cantidad_adyacentes(int vertice){
    if(existe_vertice(vertice)){
        auto it=grafo.begin();
        while(it->first!=vertice){
            it++;
        }
        return(it->second.size()-1);
    }
    return -1;
}

template <typename C> int Grafo<C>::devolver_longitud() const {
    return grafo.size();
}

template <typename C> bool Grafo<C>::existe_vertice(int buscado) const{
    for(auto it=grafo.begin();it!=grafo.end();it++){
        if (it->first==buscado){
            return true;
        }
    }
    return false;

}

template <typename C> bool Grafo<C>::existe_arco(int origen, int destino) const{
    if (existe_vertice(origen)&&existe_vertice(destino)){
        auto it= grafo.begin();
        while (it->first!=origen){
            it++;
        }
        if (it->first==origen){
                auto itady= it->second.begin();
                while (itady != it->second.end() && itady->first!=destino){
                    itady++;
                }
                if (itady->first== destino){
                    return true;
                }

        }
    }
    return false;

}

template <typename C> const C & Grafo<C>::costo_arco(int origen, int destino) const{
    if (existe_arco(origen,destino)){
        auto it= grafo.begin();
        while (it->first!=origen){
            it++;
        }
        auto itady= it->second.begin();
        while (itady != it->second.end() && itady->first!=destino){
            itady++;
        }

        return itady->second;
    }
}

template <typename C> void Grafo<C>::devolver_vertices(list<int> & verts)const{
    auto it = grafo.begin();
    while(it!=grafo.end()){
        verts.push_back(it->first);
        it++;
    }
}

template <typename C> void Grafo<C>::devolver_adyacentes(int origen, list<Arco> & adyacentes)const{
   if (existe_vertice(origen)){
        auto it= grafo.begin();
        while (it->first!=origen){
            it++;
        }
            for(auto ady =it->second.begin();ady!=it->second.end();ady++){
                if(origen!=ady->first){
                   adyacentes.push_back(*ady);
                }
            }
    }
}

template <typename C> void Grafo<C>::agregar_vertice(int nuevo){
    if(!existe_vertice(nuevo)){
        if (nuevo<0){nuevo=-nuevo;} //no se permiten vertices con indice negativo
        nodo vertnuevo;
        vertnuevo.first=nuevo;
        vertnuevo.second.push_back(make_pair(nuevo,0));
        grafo.push_back(vertnuevo);
    }
}

template <typename C> void Grafo<C>::eliminar_vertice(int vert){

    if (existe_vertice(vert)){

        list<pair<int,int>> adyacentes;
        devolver_adyacentes(vert,adyacentes);
        ;
        for(auto itAdy=adyacentes.begin();itAdy!=adyacentes.end();itAdy++){
            eliminar_arco(vert,itAdy->first);
        }
        auto it=grafo.begin();
        while (it!=grafo.end()&& it->first!= vert){
            it++;
        }
        it->second.clear();
        it= grafo.erase(it);
    }
}

template <typename C> void Grafo<C>:: modificar_costo_arco(int origen, int destino, const C & costo){
    if (existe_arco(origen,destino)){
        auto it=grafo.begin();
        while (it->first!= origen){it++;}
        auto itady=it->second.begin();
        while (itady->first!=destino) {itady++;}
        itady->second=costo;
        it=grafo.begin();
        while (it->first!= destino){it++;}
        itady=it->second.begin();
        while (itady->first!=origen) {itady++;}
        itady->second=costo;
    }
}

template<typename C> void Grafo<C>:: agregar_arco(int origen, int destino, const C & costo){
   if (existe_vertice(destino)&& existe_vertice(origen)){
        Arco nuevo;
        nuevo.first=destino;
        nuevo.second=costo;
        auto it=grafo.begin();
        while(it->first!=origen){it++;}
        it->second.push_back(nuevo);
        nuevo.first=origen;
        it=grafo.begin();
        while(it->first!=destino){it++;}
        it->second.push_back(nuevo);

    }
}

template <typename C> void Grafo<C>::eliminar_arco(int origen, int destino){

    if (existe_arco(origen,destino)){
        pair<int, C> borrar;
        borrar.first=destino;
        borrar.second=costo_arco(origen,destino);

        auto it= grafo.begin();
        while (it->first!=origen && it!= grafo.end() ){
            it++;
        }
        it->second.remove(borrar);
        borrar.first=origen;
        it =grafo.begin();
        while (it->first!=destino && it!= grafo.end() ){
            it++;
        }
        it->second.remove(borrar);
    }
}

template <typename C> void Grafo<C>::vaciar(){
    grafo.clear();
}

// Sobrecarga el operador << para que el grafo pueda ser mostrado por consola. Complejidad O(n^2) en el peor caso(todos los nodos conectados).
template <typename C> ostream & operator << (ostream & salida, const Grafo<C> & grafo)
{
    if(!grafo.esta_vacio()){
        // Recorremos todos los vertices
        list<int> vertices;
        grafo.devolver_vertices(vertices);
        list<int>::iterator v = vertices.begin();
        while (v != vertices.end()) {
            salida << "\n    " << *v << ":\n";
            // Recorremos todos los adyacentes de cada vertice
            list<pair<int,C>> adyacentes;
            grafo.devolver_adyacentes(*v, adyacentes);
            typename list<typename Grafo<C>::Arco>::iterator ady = adyacentes.begin();
            while (ady != adyacentes.end()) {
                if(ady->first!=*v){salida << "    " << *v << "-> " << ady->first << " (" << ady->second << ")\n";}
                ady++;
            }
            v++;
        }
        return salida;
    }
    salida << " El grafo no tiene vertices.\n";
    return salida;

}

#endif /* GRAFO_H_ */
