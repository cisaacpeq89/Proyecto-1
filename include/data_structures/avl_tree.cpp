#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

class TREEAVL
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
    int error_avl;

    nodo* avl_tree_insert(int numero_ced, char *nombre_reg, nodo* temp2){
        if(temp2 == NULL){
            temp2 = new nodo;
            temp2->cedula= numero_ced;
            temp2->altura = 0;
            temp2->izqui = NULL;
            temp2->derec = NULL;
            temp2->padre = NULL;
            strcpy(temp2->nombre,nombre_reg);
        }
        else if(numero_ced < temp2->cedula){
            temp2->izqui = avl_tree_insert(numero_ced, nombre_reg, temp2->izqui);
            temp2 = temp2->izqui->padre;
            if(avl_tree_get_size(temp2->izqui) - avl_tree_get_size(temp2->derec) == 2)
            {
                if(numero_ced < temp2->izqui->cedula)
                    temp2 = rotar_derecha(temp2);
                else
                    temp2 = rotacion_parcial_derecha(temp2);
            }
        }
        else if(numero_ced > temp2->cedula){
            temp2->derec = avl_tree_insert(numero_ced, nombre_reg, temp2->derec);
            temp2 = temp2->derec->padre;
            if(avl_tree_get_size(temp2->derec) - avl_tree_get_size(temp2->izqui) == 2){
                if(numero_ced > temp2->derec->cedula)
                    temp2 = rotar_izquierda(temp2);
                else
                    temp2 = rotacion_parcial_izquierda(temp2);
            }
        }
        temp2->altura = max(avl_tree_get_size(temp2->izqui), avl_tree_get_size(temp2->derec))+1;
        return temp2;
    }

    nodo* rotar_derecha(nodo* &temp3){
        nodo* tem_rot = temp3->derec;
        temp3->izqui = tem_rot->izqui;
        tem_rot->derec = temp3;
        tem_rot->altura = max(avl_tree_get_size(temp3->izqui), avl_tree_get_size(temp3->derec))+1;
        tem_rot->altura = max(avl_tree_get_size(tem_rot->izqui), temp3->altura)+1;
        return tem_rot;
    }

    nodo* rotar_izquierda(nodo* &temp4){
        nodo* temp_rot = temp4->derec;
        temp4->derec = temp_rot->izqui;
        temp_rot->izqui = temp4;
        temp4->altura = max(avl_tree_get_size(temp4->izqui), avl_tree_get_size(temp4->derec))+1;
        temp_rot->altura = max(avl_tree_get_size(temp4->derec), temp4->altura)+1 ;
        return temp_rot;
    }

    nodo* rotacion_parcial_izquierda(nodo* &temp5){
        temp5->derec = rotar_derecha(temp5->derec);
        return rotar_izquierda(temp5);
    }

    nodo* rotacion_parcial_derecha(nodo* &temp6){
        temp6->izqui = rotar_izquierda(temp6->izqui);
        return rotar_derecha(temp6);
    }

    int avl_tree_get_size(nodo* temp7){
        return (temp7 == NULL ? -1 : temp7->altura);
    }

    void avl_tree_get_max_height(){
        if(origen !=   NULL){
            cout << origen->altura;
        }else{
            error_avl = 1;
        }
    }

    void Liberar_mem(nodo *temp8){
        if(temp8 == NULL)
            return;
        Liberar_mem(temp8->izqui);
        Liberar_mem(temp8->derec);
        delete temp8;
    }




    public:
    ARBOLVL()
    {
        origen = NULL;
        error_avl = 0;
    }

    void avl_tree_insert(int temp_cedula, char* temp_nombre){
        origen = avl_tree_insert(temp_cedula, temp_nombre, origen);
    }
    void avl_tree_create(){
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
        avl_tree_insert(cedula_class, nombre_class);
        }
        linea_list.close();
    }

};

main(){

return 0;
}
