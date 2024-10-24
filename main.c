#include "biblioteca.h"
#include <stdio.h>

int main() {
    UserSystem user_system;
    BookSystem book_system;
    CartSystem cart_system;

    UserSystem_init(&user_system);
    BookSystem_init(&book_system);
    CartSystem_init(&cart_system);

    UserSystem_load_from_file(&user_system);
    BookSystem_load_from_file_txt(&book_system);

    int choice;
    do {
        printf("\n1. Registrar usuario\n");
        printf("2. Login\n");
        printf("3. Listar livros\n");
        printf("4. Adicionar livro ao carrinho\n");
        printf("5. Finalizar compra\n");
        printf("6. Adicionar livro \n");
        printf("7. Editar livro \n");
        printf("8. Excluir livro \n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                UserSystem_register(&user_system);
                break;
            case 2:
                if (UserSystem_login(&user_system)) {
                    // Após login, mostrar funcionalidades
                }
                break;
            case 3:
                BookSystem_list(&book_system);
                break;
            case 4:
                CartSystem_add(&cart_system, &book_system);
                break;
            case 5:
                CartSystem_checkout(&cart_system);
                break;
            case 6:
                BookSystem_add(&book_system);
                break;
            case 7:
                BookSystem_edit(&book_system);
                break;
            case 8:
                BookSystem_delete(&book_system);
                break;
            case 0:
                UserSystem_save_to_file(&user_system);
                BookSystem_save_to_file_txt(&book_system);
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (choice != 0);

    return 0;
}
