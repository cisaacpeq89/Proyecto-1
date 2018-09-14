#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

class ARBOLVL
{
    struct nodo
    {
        char nombre[2];
        int cedula;
        nodo* izqui;
        nodo* derec;
        nodo* padre;
        int altura;
    };

    nodo* origen;

    nodo* insert(int numero_ced, char *nombre_reg, nodo* temp2){
        if(temp2 == NULL)
        {
            temp2 = new nodo;
            temp2->cedula= numero_ced;
            temp2->altura = 0;
            temp2->izqui = NULL;
            temp2->derec = NULL;
            temp2->padre = NULL;
            strcpy(temp2->nombre,nombre_reg);
        }
        else if(numero_ced < temp2->cedula){
            temp2->izqui = insert(numero_ced, nombre_reg, temp2->izqui);
            if(altura_func(temp2->izqui) - altura_func(temp2->derec) == 2)
            {
                if(numero_ced < temp2->izqui->cedula)
                    temp2 = singleRightRotate(temp2);
                else
                    temp2 = doubleRightRotate(temp2);
            }
        }
        else if(numero_ced > temp2->cedula){
            temp2->derec = insert(numero_ced, nombre_reg, temp2->derec);
            if(altura_func(temp2->derec) - altura_func(temp2->izqui) == 2){
                if(numero_ced > temp2->derec->cedula)
                    temp2 = singleLeftRotate(temp2);
                else
                    temp2 = doubleLeftRotate(temp2);
            }
        }

        temp2->altura = max(altura_func(temp2->izqui), altura_func(temp2->derec))+1;
        return temp2;
    }
    nodo* singleRightRotate(nodo* &t){
        nodo* u = t->derec;
        t->izqui = u->izqui;
        u->derec = t;
        t->altura = max(altura_func(t->izqui), altura_func(t->derec))+1;
        u->altura = max(altura_func(u->izqui), t->altura)+1;
        return u;
    }

    nodo* singleLeftRotate(nodo* &t){
        nodo* u = t->derec;
        t->derec = u->izqui;
        u->izqui = t;
        t->altura = max(altura_func(t->izqui), altura_func(t->derec))+1;
        u->altura = max(altura_func(t->derec), t->altura)+1 ;
        return u;
    }

    nodo* doubleLeftRotate(nodo* &t){
        t->derec = singleRightRotate(t->derec);
        return singleLeftRotate(t);
    }

    nodo* doubleRightRotate(nodo* &t){
        t->izqui = singleLeftRotate(t->izqui);
        return singleRightRotate(t);
    }

    int altura_func(nodo* t){
        return (t == NULL ? -1 : t->altura);
    }

    void Liberar_mem(nodo *temp){
        if(temp == NULL)
            return;
        Liberar_mem(temp->izqui);
        Liberar_mem(temp->derec);
        delete temp;
    }



    public:
    ARBOLVL()
    {
        origen = NULL;
    }

    void insert(int temp_cedula, char* temp_nombre){
        origen = insert(temp_cedula, temp_nombre, origen);
    }
    void maketree(){
        char alias[50];
        char nombre_class[30], cedula_char[20];
        int cedula_class, lastchar;
        string texto;
        bool nomb_OK = false;
        ifstream linea_list;
        linea_list.open("base.txt");
        while(!linea_list.eof()){
        for(int j = 0; j<49;j++){
            alias[j]= ' ';
        }
        for(int j = 0; j < 19; j++){
            cedula_char[j]= ' ';
        }
        getline(linea_list,texto);
        strcpy(alias,texto.c_str());
        for(int k= 0; k < 49; k++){
            if(nomb_OK == false){
                if(alias[k] != ','){
                    nombre_class[k]=alias[k];
                }else{
                    nomb_OK = true;
                    lastchar = k;
                    for(int p = k; p < 49;p++){
                        nombre_class[p] = ' ';
                    }
                }
            }else{
                if(alias[k] != ' '){
                    cedula_char[k-lastchar -1]=alias[k];
                }
            }
        }
        cedula_class = atoi(cedula_char);
        nomb_OK = false;
        insert(cedula_class, nombre_class);
        }
        linea_list.close();
    }

};

main(){

return 0;
}
