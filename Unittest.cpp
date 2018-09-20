#include "include/data_structures/avl_tree.hpp"
void test_valores_invalidos(TREEAVL* temp_class);
void printerror(int error_inter);
void test_de_inserciones_con_rotaciones(TREEAVL *temp_class);
void test_de_banlaceo_y_ordenamiento(TREEAVL *temp_class);
void test_liberacion_de_memoria(TREEAVL *temp_class);

main(){

TREEAVL* test;
test = new   TREEAVL;
cout << "***Test de valores invalidos***\n \n";
test_valores_invalidos(test);
cout << "***Test de inserciones con rotaciones***\n \n";
test_de_inserciones_con_rotaciones(test);
cout << "***Verificacion de balanceo y ordenamiento***\n \n";
test_de_banlaceo_y_ordenamiento(test);
cout << "***Test de remocion de datos y liberacion de memoria***\n \n";
test_liberacion_de_memoria(test);


}

void test_liberacion_de_memoria(TREEAVL* temp_class){
    cout << "-Remover 5 datos, esperar balanceo y ordenamiento\n";
    (*temp_class).avl_tree_remove(3, " ");
    (*temp_class).avl_tree_remove(7, " ");
    (*temp_class).avl_tree_remove(10, " ");
    (*temp_class).avl_tree_remove(1, " ");
    (*temp_class).avl_tree_remove(8, " ");
    (*temp_class).ordenar_tree();
    cout << endl;
    printerror((*temp_class).error_tree());
    if((*temp_class).avl_tree_get_max_height() == 2){
        cout << "Balanceo OK\n";
    }
    else{
        cout <<"Fallo en balanceo\n";
    }
    cout << "-Eliminar todos los nodos del arbol\n";
    (*temp_class).avl_tree_remove(2, " ");
    (*temp_class).avl_tree_remove(5, " ");
    (*temp_class).avl_tree_remove(4, " ");
    (*temp_class).avl_tree_remove(9, " ");
    (*temp_class).avl_tree_remove(6, " ");
     printerror((*temp_class).error_tree());

}

void test_valores_invalidos(TREEAVL* temp_class){
    cout << "-Insertando una cedula negativa\n";
    (*temp_class).avl_tree_insert(-11920123,"Mario Fuentes");
    printerror((*temp_class).error_tree());
    cout << "-Insertando una cedula repetida\n";
    (*temp_class).avl_tree_insert(2,"Mario Fuentes");
    (*temp_class).avl_tree_insert(2,"Mario Fuentes");
    printerror((*temp_class).error_tree());
    cout << "-Eliminando una cedula que no esta en la base\n";
    (*temp_class).avl_tree_remove(3,"Mario Fuentes");
    printerror((*temp_class).error_tree());
    cout << "-Eliminando una cedula en un arbol vacio\n";
    (*temp_class).avl_tree_remove(2,"Mario Fuentes");
    (*temp_class).avl_tree_remove(2,"Mario Fuentes");
    printerror((*temp_class).error_tree());
    cout << "-Eliminando una cedula con un nombre diferente\n";
    (*temp_class).avl_tree_insert(2,"Mario Fuentes");
    (*temp_class).avl_tree_remove(2,"Mario Perez");
    printerror((*temp_class).error_tree());
    (*temp_class).avl_tree_remove(2,"Mario Fuentes");
    cout << "\n";
}
void test_de_inserciones_con_rotaciones(TREEAVL *temp_class){
    (*temp_class).avl_tree_insert(5," ");
    (*temp_class).avl_tree_insert(6," ");
    (*temp_class).avl_tree_insert(7," ");
    if((*temp_class).avl_tree_get_max_height() == 1){
        cout << "Rotacion a la izquierda OK\n";
    }
    else{
        cout << "Fallo de rotacion a la izquierda\n";
    }
    (*temp_class).avl_tree_insert(4," ");
    (*temp_class).avl_tree_insert(3," ");
    if((*temp_class).avl_tree_get_max_height() == 2){
        cout << "Rotacion a la derecha OK\n";
    }
    else{
        cout << "Fallo de rotacion a la derecha\n";
    }
    (*temp_class).avl_tree_insert(9," ");
    (*temp_class).avl_tree_insert(8," ");
    if((*temp_class).avl_tree_get_max_height() == 2){
        cout << "Rotacion doble a la izquierda OK\n";
    }
    else{
        cout << "Fallo de rotacion doble a la izquierda\n";
    }
    (*temp_class).avl_tree_insert(1," ");
    (*temp_class).avl_tree_insert(2," ");
    if((*temp_class).avl_tree_get_max_height() == 3){
        cout << "Rotacion doble a la derecha OK\n";
    }
    else{
        cout << "Fallo de rotacion doble a la derecha\n";
    }
    printerror((*temp_class).error_tree());
    cout << "\n";
}
void test_de_banlaceo_y_ordenamiento(TREEAVL* temp_class){
    cout << "-Insertando 10 valores comprobando banlanceo\n"; //Se inserta la cedula 10 y se comprueba la altura maxima del arbol para cpmprobar el balanceo
    (*temp_class).avl_tree_insert(10," ");
    if((*temp_class).avl_tree_get_max_height() == 3){
        cout << "Balanceo OK\n";
    }
    else{
        cout <<"Fallo en balanceo\n";
    }
    cout << "-Comprobando ordenamiento\n"; //
    (*temp_class).ordenar_tree();
    cout << endl;
    printerror((*temp_class).error_tree());
    cout << endl;
}

void printerror(int error_inter){
switch(error_inter){
case 0:
    cout << "no hay errores\n";
    break;
case 1:
    cout << "ERROR-altura maxima de una arbol vacio\n";
    break;
case 2:
    cout << "ERROR-borrar un dato en un arbol vacio\n";
    break;
case 3:
    cout << "ERROR-borrar un dato no existente en el arbol\n";
    break;
case 4:
    cout << "ERROR-borrar un numero de cedula con un nombre diferente al encontrado en la base de datos\n";
    break;
case 5:
    cout << "ERROR-abrir lista con direccion y o nombre erronea\n";
    break;
case 6:
    cout << "ERROR-se inserto una cedula repetida en la base de datos\n";
    break;
case 7:
    cout << "ERROR-numero de cedula negativo\n";
    break;
case 8:
    cout << "ERROR-no hay ordenamiento";
    break;
default:
    break;
}

}
