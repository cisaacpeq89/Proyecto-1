#include <iostream>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <cstring>
#include <time.h>

using namespace std;

class TREEAVL   //Defino una clase TREEAVL
{
    struct nodo // Dentro de la clase defino una estructura que contendra la informacion de cada nodo
    {
        char nombre[30];
        int cedula;
        nodo* izqui;
        nodo* derec;
        nodo* padre;
        int altura;
    };

    nodo* origen;   //Esta variable es propia de la clase y me define el root del arbol
    int error_avlinter; //Esra variable es propia de la clase y contentra los errores en las funciones al ingresar datos o realizar acciones no validas

    nodo* avl_tree_insert(int numero_ced, char *nombre_reg, nodo* temp2){   //Esta funcion es la que me creara un nuevo nodo ademas me autobalancea el arbol
        if(numero_ced < 0){
            error_avlinter = 7;
            return temp2;
        }
        else if(temp2 == NULL){  //Si la direccion del nodo nuevo es NULL se reservara espacio para el nuevo nodo y se incorporan los valores correspondientes
            temp2 = new nodo;
            temp2->altura = 0;
            temp2->izqui = NULL;
            temp2->derec = NULL;
            temp2->padre = NULL;
            strcpy(temp2->nombre,nombre_reg);
            temp2->cedula = numero_ced;
        }
        else if(numero_ced < temp2->cedula){    //Si el nuevo valor a ingresar el menor al valor del nodo actual, se ira a la izquierda de dicho nodo
            temp2->izqui = avl_tree_insert(numero_ced, nombre_reg, temp2->izqui);
            if(avl_tree_get_size(temp2->izqui) - avl_tree_get_size(temp2->derec) == 2){ //Se precunta si el arbol esta desbalanceado en caso de estarlo se envian a las funciones de rotacion simplre o doble rotacion a la izquierda
                if(numero_ced < temp2->izqui->cedula){  //Si el arbol esta desbalanceado y observo si el nodo que posee una altura de 2 que su nodo izquierdo es mayor al nuevo dato ingresado en caso de ser correcto es evidente que que los dos nodos posteriores al altual estan a la izquierda uno del otro de forma que se debe hacer una rotacion simple a la derecha en caso contrario sera una rotacion parcial
                	temp2 = rotar_derecha(temp2);
				}else{
					temp2 = rotacion_parcial_derecha(temp2);
				}
            }
            temp2->izqui->padre = temp2;    //Defino la direccion del padre para cada nodo
        }
        else if(numero_ced > temp2->cedula){    //Entra en este else si el numero es mayor al nodo actual
            temp2->derec = avl_tree_insert(numero_ced, nombre_reg, temp2->derec);
            if((avl_tree_get_size(temp2->derec) - avl_tree_get_size(temp2->izqui))== 2){
                if(numero_ced > temp2->derec->cedula)
                    temp2 = rotar_izquierda(temp2);
                else
                    temp2 = rotacion_parcial_izquierda(temp2);
            }
            temp2->derec->padre = temp2;
        }
        else if(numero_ced == temp2->cedula){   //En caso de ingresar un nodo con un valor de cedula repetido se guarda un error
        	error_avlinter = 6;
        	return temp2;
		}
        temp2->altura = max(avl_tree_get_size(temp2->izqui), avl_tree_get_size(temp2->derec))+1; //Se calcula la altura del arbol esto en cada nodo
        return temp2;   //Retorna la direccion del nodo actual
    }

    nodo* avl_tree_remove(int temp3_cedula, char* temp3_nombre, nodo* temp_origen){ //Funcion recursiva para remover un nodo especifico
    if(temp_origen == NULL){// Pregunto si la direccion de nodo solicitado es nula, en caso de no serlo pasa al siguiente else
        error_avlinter = 2;
    }
    else if(temp3_cedula < temp_origen->cedula && temp_origen->izqui == NULL){ //Pregunta si el numero de cedula es menor al nodo actual y si su hijo izquierdo es nulo.
        error_avlinter = 3;
    }
    else if(temp3_cedula > temp_origen->cedula && temp_origen->derec == NULL){ //Pregunta si el numero de cedula es mayor al nodo actual y si su hijo derecho es nulo.
        error_avlinter = 3;
    }
    else if(temp3_cedula < temp_origen->cedula){    //Compara la cedula a borrar con el dato del nodo actual en caso de ser menor se dirije a la direccion izquierda del nodo actual
        temp_origen->izqui = avl_tree_remove(temp3_cedula,temp3_nombre,temp_origen->izqui);
        if(avl_tree_get_size(temp_origen->derec) - avl_tree_get_size(temp_origen->izqui) == 2){  //Pregunta si es necesario balancear
            if(temp3_cedula < temp_origen->derec->cedula){
                temp_origen = rotar_izquierda(temp_origen);
            }
            else{
                temp_origen = rotacion_parcial_izquierda(temp_origen);
            }
            temp_origen->izqui->padre = temp_origen;
        }
    }
    else if(temp3_cedula > temp_origen->cedula){    //Comnara la cedula a borrar  con el dato del nodo actual en caso de ser mayor se dirije a la direccion derecha del nodo actual
        temp_origen->derec = avl_tree_remove(temp3_cedula,temp3_nombre,temp_origen->derec);
        if(avl_tree_get_size(temp_origen->izqui) - avl_tree_get_size(temp_origen->derec) == 2){ //pregunta si es necesario balancear
            if(temp3_cedula < temp_origen->izqui->cedula){
                temp_origen = rotar_derecha(temp_origen);
            }
            else{
                temp_origen = rotacion_parcial_derecha(temp_origen);
            }
            temp_origen->derec->padre = temp_origen;
        }
    }
    else if(temp3_cedula == temp_origen->cedula){   //En caso de ser igual el numero de cedula con el dato de cedula del nodo actual entra a funcionar este if
        if(strncmp(temp_origen->nombre,temp3_nombre, strlen(temp3_nombre)) == 0){ //Este if entra a funcionar cuando se encuentra el numero de cedula que se quiere eliminar
            nodo* nodotemp;
            if(temp_origen->izqui != NULL){ //Comprueba si el nodo a eliminar tiene hijos a su izquierda
                if(temp_origen->izqui->derec != NULL){ //En caso de tener hijos a su izquierda pregunta si tiene algun nieto de lado derecho
                    nodotemp = temp_origen->izqui->derec;
                    nodotemp->izqui = temp_origen->izqui;
                    nodotemp->derec = temp_origen->derec;
                }
                else{   //En caso de no tener nieto a la derecha se coloca su hijo zquierdo en el sitio del padre
                    nodotemp = temp_origen->izqui;
                }
                Liberar_mem(temp_origen);
                temp_origen = nodotemp;
            }
            else if(temp_origen->derec != NULL){
                nodotemp = temp_origen->derec;
                Liberar_mem(temp_origen);
                temp_origen = nodotemp;
            }
            else{
               Liberar_mem(temp_origen);
               temp_origen = NULL;
            }

            error_avlinter = 0;
        }
        else{
            error_avlinter = 4;
        }
    }
    if(temp_origen != NULL){
    temp_origen->altura = max(avl_tree_get_size(temp_origen->izqui), avl_tree_get_size(temp_origen->derec))+1;
    }
    return temp_origen;
    }

    nodo* rotar_derecha(nodo* &temp3){  //Funcion privada para hacer una rotacion simple a la derecha
        nodo* tem_rot = temp3->izqui;
        temp3->izqui = tem_rot->derec;
        tem_rot->derec = temp3;
        temp3->altura = max(avl_tree_get_size(temp3->izqui), avl_tree_get_size(temp3->derec))+1;
        tem_rot->altura = max(avl_tree_get_size(tem_rot->izqui), temp3->altura)+1;
        return tem_rot;
    }

    nodo* rotar_izquierda(nodo* &temp4){    //Funcion privada para hacer una rotacion simple a la izquierda
        nodo* temp_rot = temp4->derec;
        temp4->derec = temp_rot->izqui;
        temp_rot->izqui = temp4;
        temp4->altura = max(avl_tree_get_size(temp4->izqui), avl_tree_get_size(temp4->derec))+1;
        temp_rot->altura = max(avl_tree_get_size(temp4->derec), temp4->altura)+1 ;
        return temp_rot;
    }

    nodo* rotacion_parcial_izquierda(nodo* &temp5){ //Funcion privada para hacer una doble rotacion a la izquierda
        temp5->derec = rotar_derecha(temp5->derec);
        return rotar_izquierda(temp5);
    }

    nodo* rotacion_parcial_derecha(nodo* &temp6){   //Funcion privada para hacer una doble rotacion a la derecha
        temp6->izqui = rotar_izquierda(temp6->izqui);
        return rotar_derecha(temp6);
    }

    int avl_tree_get_size(nodo* temp7){ //Funcion privada para obtner la altura de un nodo
        return (temp7 == NULL ? -1 : temp7->altura);
    }


    void Liberar_mem(nodo *temp8){  //Funcion privada para eliminar nodos o liberarlos de memoria
        if(temp8 == NULL)
            return;
        Liberar_mem(temp8->izqui);
        Liberar_mem(temp8->derec);
        delete temp8;
    }

    void print_tree(nodo* temp10){  //Funcion privada para crear un documento con el arbol creada este debe estar ordenado segun su cedula
    remove("..\\misc\\output\\max_and_min_id.txt");
    ofstream base;
    base.open("..\\misc\\output\\max_and_min_id.txt", ofstream::out | ofstream::app);
    if(temp10 == NULL){
        return;
    }
    else{
        print_tree(temp10->izqui);
        base << temp10->nombre << ", " << temp10->cedula << endl;
        print_tree(temp10->derec);
    }
    base.close();
    }

    void print_time_tree(float time_tot, int insertnum){ //Guarda el tiempo de ejecucion de la creacion del arbol
        ofstream base;
        base.open("misc\\data\\running_times.txt", ofstream::out| ofstream::app);
        base << "Numero de inserciones: " << insertnum << ", tiempo de ejecucion " << time_tot << " s." << endl;
        base.close();
    }

	void ordenar(nodo* temp11){ //Funcion privada para imprimir el arbol
        if(temp11 == NULL)
            return;
        ordenar(temp11->izqui);
		cout << temp11->cedula << " ";
		if(temp11 < temp11->izqui){
			error_avlinter = 8;
		}
		else{

			error_avlinter = 0;
		}
        ordenar(temp11->derec);
	}
    public:
    int error_avl;

    TREEAVL()   //Constructor
    {
        origen = NULL;
        error_avlinter = 0;
        error_avl = 0;
    }

    void avl_tree_insert(int temp_cedula, char* temp_nombre){   //Funcion publica para insertar valores en la base de datos
        origen = avl_tree_insert(temp_cedula, temp_nombre, origen);
    }

    void avl_tree_remove(int temp2_cedula, char* temp2_nombre){ //Funcion publica para remover valores en la base de datos
        origen = avl_tree_remove(temp2_cedula, temp2_nombre, origen);
    }


    void avl_tree_create(){ //Funcion publica para crear un arblo a partir de un documento existente
        char nombre_class[40], cedula_char[20];
        int cedula_class, lastchar, passchar, passced, tam_tree,cont_tree, insertnum;
        string texto, textemp;
        bool nomb_OK = false;
        ifstream linea_list,cont_list;
        float t0, t1, time_create;
        t0 = clock();
        linea_list.open("..\\misc\\input\\name_id_list.txt", ios::in);  //Accede al documento name_id_list
        cont_list.open("..\\misc\\input\\name_id_list.txt", ios::in);  //Accede al documento name_id_list para contar el numero de lineas
        if(linea_list.fail()){
        	error_avlinter = 5;
        	return;
		}
        if(cont_list.fail()){
        	error_avlinter = 5;
        	return;
		}
		passced = 0;
		passchar = 0;
		cont_tree = 0;
		tam_tree = 0;
		insertnum = 0;
        for(int j = 0; j < 19; j++){
            cedula_char[j]= ' ';
        }
        for(int p = 0; p < 39;p++){
            nombre_class[p] = ' ';
        }
        while(!cont_list.eof()){
            getline(cont_list,textemp);
            tam_tree = tam_tree + 1;
        }

        while(!linea_list.eof()){
            cont_tree = cont_tree + 1;
            getline(linea_list,texto);
            char alias[strlen(texto.c_str())];
            lastchar = 0;
		        strcpy(alias,texto.c_str());
		        for(int k = 0; k <= strlen(texto.c_str()); k++){
		            if(nomb_OK == false){
		                if(alias[k] != ','){
		                    if(alias[k]!= ' '){
                                nombre_class[k - lastchar + passchar]=alias[k];
		                    }
		                }else{
		                    nomb_OK = true;
		                    nombre_class[k - lastchar + passchar] = '\0';
		                    lastchar = k;
		                    passchar = 0;
		                }
		                if(alias[k+1] == '\0'){
                            passchar = k - lastchar;
		                }
		            }else{
		                if(alias[k] > 47 && alias[k] < 58){
                            cedula_char[k - 2 - lastchar + passced] = alias[k];
		                    if((alias[k+1] < 48  && alias[k+1] > 57) || (cont_tree == tam_tree && alias[k+1] == '\0') ||k -lastchar -1 == 9){
                                cedula_char[k - lastchar + passced] = '\0';
                                lastchar = k;
                                nomb_OK = false;
                                passced = 0;
                                cedula_class = atoi(cedula_char);
                                if(nombre_class[0] == ' '){
                                    for(int er = 1; er < 39; er++){
                                        nombre_class[er - 1] = nombre_class[er];
                                    }
                                }
                                insertnum++;
                                avl_tree_insert(cedula_class, nombre_class);
                                for(int j = 0; j < 19; j++){
                                    cedula_char[j]= ' ';
                                }
                                for(int p = 0; p < 39;p++){
                                    nombre_class[p] = ' ';
                                }
		                    }
		                }
		                if(alias[k+1] == '\0'){
                            passced = k - lastchar;
                        }
		            }
		        }
        }
        linea_list.close();
        cont_list.close();
        print_tree(origen);
        if(error_tree() == 0){
            Liberar_mem(origen);
        }
        t1 = clock();
        time_create = (t1 - t0)/ CLOCKS_PER_SEC;
        print_time_tree(time_create, insertnum); //Manda a grabar el tiempo que duro en correr el programa
    }

     int avl_tree_get_max_height(){ //Funcion publica para obener la altura maxima o de root del arbol
        if(avl_tree_get_size(origen) < 0){
            error_avlinter = 1;
        }
        else{
            return avl_tree_get_size(origen);
        }
     }
     int error_tree(){  //Funcion publica para acceder al registro de fallos de la clase
        error_avl = error_avlinter;
        return error_avl;
     }

	 void ordenar_tree(){   //Funcion publica para imprimir el arbol
		 ordenar(origen);
	 }
};
