#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>

void menu() {
    printf("\n========= Menu: =============\n");
    printf("1. Cadastrar Livro\n");
    printf("2. Listar Livros\n");
    printf("3. Adicionar ao Carrinho\n");
    printf("4. Finalizar Compra\n");
    printf("0. Sair\n");
    printf("=============================\n");
}

void run(UserSystem *user_system, BookSystem *book_system, CartSystem *cart_system) {
    UserSystem_load_from_file(user_system);
    BookSystem_load_from_file(book_system);
    UserSystem_register(user_system);  // Adiciona um usuário inicial
    if (UserSystem_login(user_system)) {
        while (true) {
            menu();
            printf("Escolha uma opcao: ");
            int option;
            scanf("%d", &option);
            switch (option) {
                case 0:
                    printf("Saindo...\n");
                    UserSystem_save_to_file(user_system);
                    BookSystem_save_to_file(book_system);
                    return;
                case 1:
                    BookSystem_add(book_system);
                    break;
                case 2:
                    BookSystem_list(book_system);
                    break;
                case 3:
                    CartSystem_add(cart_system, book_system);
                    break;
                case 4:
                    CartSystem_checkout(cart_system);
                    break;
                default:
                    printf("Opcao invalida.\n");
                    break;
            }
        }
    }
}

int main() {
    UserSystem user_system;
    BookSystem book_system;
    CartSystem cart_system;

    UserSystem_init(&user_system);
    BookSystem_init(&book_system);
    CartSystem_init(&cart_system);

    run(&user_system, &book_system, &cart_system);

    free(user_system.users);
    free(book_system.books);
    free(cart_system.items);
    
    return 0;
}