#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>

// Função para exibir o menu principal
void menu() {
    printf("\n========= Menu: =============\n");
    printf("1. Cadastrar Livro\n");
    printf("2. Listar Livros\n");
    printf("3. Editar Livro\n");
    printf("4. Excluir Livro\n");
    printf("5. Adicionar ao Carrinho\n");
    printf("6. Finalizar Compra\n");
    printf("0. Sair\n");
    printf("=============================\n");
}

// Função principal de execução do programa
void run(UserSystem *user_system, BookSystem *book_system, CartSystem *cart_system) {
    UserSystem_load_from_file(user_system);
    BookSystem_load_from_file_txt(book_system);
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
                    BookSystem_save_to_file_txt(book_system);
                    return;
                case 1:
                    BookSystem_add(book_system);
                    break;
                case 2:
                    BookSystem_list(book_system);
                    break;
                case 3:
                    BookSystem_edit(book_system);
                    break;
                case 4:
                    BookSystem_delete(book_system);
                    break;
                case 5:
                    CartSystem_add(cart_system, book_system);
                    break;
                case 6:
                    CartSystem_checkout(cart_system);
                    break;
                default:
                    printf("Opcao invalida.\n");
                    break;
            }
        }
    }
}

// Função principal
int main() {
    UserSystem user_system;
    BookSystem book_system;
    CartSystem cart_system;

    UserSystem_init(&user_system);
    BookSystem_init(&book_system);
    CartSystem_init(&cart_system);

    run(&user_system, &book_system, &cart_system);

    return 0;
}
