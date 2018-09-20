#include "include/data_structures/avl_tree.hpp"
main(){

TREEAVL ap;
ap.avl_tree_create();
cout << "Altura del arbol: " <<ap.avl_tree_get_max_height() << endl;
cout << "Numero de error encontrado en la operacion: " << ap.error_tree() << endl;
}
