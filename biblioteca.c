#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funções do TAD UserSystem
void UserSystem_init(UserSystem *system) {
    system->head = NULL;
}

bool validate_email(const char *email) {
    return strchr(email, '@') && strlen(email) < EMAIL_LENGTH;
}

void UserSystem_register(UserSystem *system) {
    char email[EMAIL_LENGTH];
    char username[EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
    
    while (true) {
        printf("Digite seu e-mail: ");
        scanf("%s", email);
        if (validate_email(email)) {
            User *new_user = (User *)malloc(sizeof(User));
            if (!new_user) {
                printf("Erro de alocação de memoria.\n");
                exit(1);
            }
            printf("Escolha um nome de usuario: ");
            scanf("%s", username);
            printf("Escolha uma senha: ");
            scanf("%s", password);
            strcpy(new_user->username, username);
            strcpy(new_user->password, password);
            new_user->next = system->head;
            system->head = new_user;
            printf("Usuario cadastrado com sucesso!\n");
            break;
        } else {
            printf("E-mail invalido.\n");
        }
    }
}

bool UserSystem_login(UserSystem *system) {
    char username[EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];

    while (true) {
        printf("\n========= Login: =============\n");
        printf("Digite seu usuario: ");
        scanf("%s", username);
        printf("Digite sua senha: ");
        scanf("%s", password);
        printf("===============================\n");

        User *current = system->head;
        while (current != NULL) {
            if (strcmp(current->username, username) == 0 && strcmp(current->password, password) == 0) {
                printf("Login bem-sucedido!\n");
                return true;
            }
            current = current->next;
        }
        printf("Usuario ou senha incorretos.\n");
    }
}

void UserSystem_save_to_file(UserSystem *system) {
    FILE *file = fopen("usuarios.bin", "wb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo de usuários.\n");
        return;
    }
    User *current = system->head;
    while (current != NULL) {
        fwrite(current, sizeof(User), 1, file);
        current = current->next;
    }
    fclose(file);
}

void UserSystem_load_from_file(UserSystem *system) {
    FILE *file = fopen("usuarios.bin", "rb");
    if (file == NULL) {
        printf("Nenhum arquivo de usuários encontrado.\n");
        return;
    }
    
    User temp;
    while (fread(&temp, sizeof(User), 1, file)) {
        User *new_user = (User *)malloc(sizeof(User));
        if (!new_user) {
            printf("Erro de alocação de memoria.\n");
            exit(1);
        }
        strcpy(new_user->username, temp.username);
        strcpy(new_user->password, temp.password);
        new_user->next = system->head;
        system->head = new_user;
    }
    fclose(file);
}

// Funções do TAD BookSystem
void BookSystem_init(BookSystem *system) {
    system->head = NULL;
}

void BookSystem_add(BookSystem *system) {
    Book *new_book = (Book *)malloc(sizeof(Book));
    if (!new_book) {
        printf("Erro de alocação de memoria.\n");
        exit(1);
    }
    printf("Digite o titulo do livro: ");
    scanf(" %[^\n]", new_book->title);
    printf("Digite o autor do livro: ");
    scanf(" %[^\n]", new_book->author);
    printf("O livro esta em promocao? (1 para sim, 0 para nao): ");
    int on_sale;
    scanf("%d", &on_sale);
    new_book->on_sale = (on_sale == 1);
    
    new_book->next = system->head;
    system->head = new_book;
    
    BookSystem_save_to_file_txt(system);
    printf("Livro cadastrado com sucesso!\n");
}

void BookSystem_list(BookSystem *system) {
    if (system->head == NULL) {
        printf("Nenhum livro cadastrado ainda.\n");
    } else {
        printf("Livros disponiveis:\n");
        Book *current = system->head;
        while (current != NULL) {
            printf("%s por %s%s\n", current->title, current->author, current->on_sale ? " (Em promocao)" : "");
            current = current->next;
        }
    }
}

Book* BookSystem_find(BookSystem *system, const char *title) {
    Book *current = system->head;
    while (current != NULL) {
        if (strcmp(current->title, title) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void BookSystem_edit(BookSystem *system) {
    char title[TITLE_LENGTH];
    printf("Digite o titulo do livro que deseja editar: ");
    scanf(" %[^\n]", title);

    Book *book = BookSystem_find(system, title);
    if (book != NULL) {
        printf("Editando o livro: %s\n", book->title);
        printf("Digite o novo titulo (ou deixe em branco para manter): ");
        char new_title[TITLE_LENGTH];
        scanf(" %[^\n]", new_title);
        if (strlen(new_title) > 0) {
            strcpy(book->title, new_title);
        }

        printf("Digite o novo autor (ou deixe em branco para manter): ");
        char new_author[AUTHOR_LENGTH];
        scanf(" %[^\n]", new_author);
        if (strlen(new_author) > 0) {
            strcpy(book->author, new_author);
        }

        printf("O livro esta em promocao? (1 para sim, 0 para nao, -1 para manter): ");
        int on_sale;
        scanf("%d", &on_sale);
        if (on_sale == 1 || on_sale == 0) {
            book->on_sale = (on_sale == 1);
        }

        BookSystem_save_to_file_txt(system);
        printf("Livro editado com sucesso!\n");
    } else {
        printf("Livro nao encontrado.\n");
    }
}

void BookSystem_delete(BookSystem *system) {
    char title[TITLE_LENGTH];
    printf("Digite o titulo do livro que deseja excluir: ");
    scanf(" %[^\n]", title);

    Book *current = system->head;
    Book *prev = NULL;
    while (current != NULL) {
        if (strcmp(current->title, title) == 0) {
            if (prev == NULL) {
                system->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            BookSystem_save_to_file_txt(system);
            printf("Livro excluido com sucesso!\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Livro nao encontrado.\n");
}

void BookSystem_save_to_file_txt(BookSystem *system) {
    FILE *file = fopen("livros.txt", "w");
    if (file == NULL) {
        printf("Erro ao abrir arquivo de livros.\n");
        return;
    }
    Book *current = system->head;
    while (current != NULL) {
        fprintf(file, "%s,%s,%d\n", current->title, current->author, current->on_sale);
        current = current->next;
    }
    fclose(file);
}

void BookSystem_load_from_file_txt(BookSystem *system) {
    FILE *file = fopen("livros.txt", "r");
    if (file == NULL) {
        printf("Nenhum arquivo de livros encontrado.\n");
        return;
    }
    
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        Book *new_book = (Book *)malloc(sizeof(Book));
        if (!new_book) {
            printf("Erro de alocação de memoria.\n");
            exit(1);
        }
        sscanf(line, " %[^,],%[^,],%d", new_book->title, new_book->author, &new_book->on_sale);
        new_book->next = system->head;
        system->head = new_book;
    }
    fclose(file);
}

// Funções do TAD CartSystem
void CartSystem_init(CartSystem *system) {
    system->head = NULL;
}

void CartSystem_add(CartSystem *system, BookSystem *book_system) {
    char title[TITLE_LENGTH];
    printf("Digite o titulo do livro que deseja adicionar ao carrinho: ");
    scanf(" %[^\n]", title);

    Book *book = BookSystem_find(book_system, title);
    if (book != NULL) {
        CartItem *new_item = (CartItem *)malloc(sizeof(CartItem));
        if (!new_item) {
            printf("Erro de alocação de memoria.\n");
            exit(1);
        }
        new_item->book = book;
        new_item->next = system->head;
        system->head = new_item;
        printf("Livro adicionado ao carrinho.\n");
    } else {
        printf("Livro nao encontrado.\n");
    }
}

void CartSystem_checkout(CartSystem *system) {
    if (system->head == NULL) {
        printf("Carrinho vazio.\n");
        return;
    }

    printf("Livros no carrinho:\n");
    CartItem *current = system->head;
    while (current != NULL) {
        printf("%s por %s\n", current->book->title, current->book->author);
        current = current->next;
    }

    // Limpa o carrinho após a finalização
    while (system->head != NULL) {
        CartItem *temp = system->head;
        system->head = system->head->next;
        free(temp);
    }
    printf("Compra finalizada!\n");
}
