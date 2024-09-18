#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funções do TAD UserSystem
void UserSystem_init(UserSystem *system) {
    system->users = NULL;
    system->user_count = 0;
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
            system->users = realloc(system->users, (system->user_count + 1) * sizeof(User));
            if (!system->users) {
                printf("Erro de alocação de memoria.\n");
                exit(1);
            }
            printf("Escolha um nome de usuario: ");
            scanf("%s", username);
            printf("Escolha uma senha: ");
            scanf("%s", password);
            strcpy(system->users[system->user_count].username, username);
            strcpy(system->users[system->user_count].password, password);
            system->user_count++;
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
        for (int i = 0; i < system->user_count; i++) {
            if (strcmp(system->users[i].username, username) == 0 && strcmp(system->users[i].password, password) == 0) {
                printf("Login bem-sucedido!\n");
                return true;
            }
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
    fwrite(&system->user_count, sizeof(int), 1, file);
    fwrite(system->users, sizeof(User), system->user_count, file);
    fclose(file);
}

void UserSystem_load_from_file(UserSystem *system) {
    FILE *file = fopen("usuarios.bin", "rb");
    if (file == NULL) {
        printf("Nenhum arquivo de usuários encontrado.\n");
        return;
    }
    fread(&system->user_count, sizeof(int), 1, file);
    system->users = malloc(system->user_count * sizeof(User));
    fread(system->users, sizeof(User), system->user_count, file);
    fclose(file);
}

// Funções do TAD BookSystem
void BookSystem_init(BookSystem *system) {
    system->books = NULL;
    system->book_count = 0;
}

void BookSystem_add(BookSystem *system) {
    system->books = realloc(system->books, (system->book_count + 1) * sizeof(Book));
    if (!system->books) {
        printf("Erro de alocação de memoria.\n");
        exit(1);
    }
    printf("Digite o titulo do livro: ");
    scanf(" %[^\n]", system->books[system->book_count].title);
    printf("Digite o autor do livro: ");
    scanf(" %[^\n]", system->books[system->book_count].author);
    printf("O livro esta em promocao? (1 para sim, 0 para nao): ");
    int on_sale;
    scanf("%d", &on_sale);
    system->books[system->book_count].on_sale = (on_sale == 1);
    system->book_count++;
    BookSystem_sort(system);
    BookSystem_save_to_file(system);
    printf("Livro cadastrado com sucesso!\n");
}

void BookSystem_list(BookSystem *system) {
    if (system->book_count == 0) {
        printf("Nenhum livro cadastrado ainda.\n");
    } else {
        printf("Livros disponiveis:\n");
        for (int i = 0; i < system->book_count; i++) {
            printf("%s por %s%s\n", system->books[i].title, system->books[i].author, 
                system->books[i].on_sale ? " (Em promocao)" : "");
        }
    }
}

void BookSystem_save_to_file(BookSystem *system) {
    FILE *file = fopen("livros.bin", "wb");
    if (file == NULL) {
        printf("Erro ao abrir arquivo de livros.\n");
        return;
    }
    fwrite(&system->book_count, sizeof(int), 1, file);
    fwrite(system->books, sizeof(Book), system->book_count, file);
    fclose(file);
}

void BookSystem_load_from_file(BookSystem *system) {
    FILE *file = fopen("livros.bin", "rb");
    if (file == NULL) {
        printf("Nenhum arquivo de livros encontrado.\n");
        return;
    }
    fread(&system->book_count, sizeof(int), 1, file);
    system->books = malloc(system->book_count * sizeof(Book));
    fread(system->books, sizeof(Book), system->book_count, file);
    fclose(file);
}

int compare_books(const void *a, const void *b) {
    Book *book_a = (Book *)a;
    Book *book_b = (Book *)b;
    return strcmp(book_a->title, book_b->title);
}

void BookSystem_sort(BookSystem *system) {
    qsort(system->books, system->book_count, sizeof(Book), compare_books);
}

int BookSystem_binary_search(BookSystem *system, const char *title) {
    int left = 0, right = system->book_count - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(system->books[mid].title, title);
        if (cmp == 0) {
            return mid;
        }
        if (cmp < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// Funções do TAD CartSystem
void CartSystem_init(CartSystem *system) {
    system->items = NULL;
    system->cart_count = 0;
}

void CartSystem_add(CartSystem *system, BookSystem *book_system) {
    char title[TITLE_LENGTH];
    printf("Digite o titulo do livro que deseja adicionar ao carrinho: ");
    scanf(" %[^\n]", title);
    int index = BookSystem_binary_search(book_system, title);
    if (index != -1) {
        system->items = realloc(system->items, (system->cart_count + 1) * sizeof(CartItem));
        if (!system->items) {
            printf("Erro de alocação de memoria.\n");
            exit(1);
        }
        system->items[system->cart_count].book = &book_system->books[index];
        system->cart_count++;
        printf("Livro adicionado ao carrinho!\n");
    } else {
        printf("Livro nao encontrado.\n");
    }
}

void CartSystem_checkout(CartSystem *system) {
    if (system->cart_count == 0) {
        printf("O carrinho esta vazio.\n");
    } else {
        printf("Comprando os seguintes livros:\n");
        for (int i = 0; i < system->cart_count; i++) {
            printf("%s por %s\n", system->items[i].book->title, system->items[i].book->author);
        }
        free(system->items);
        system->items = NULL;
        system->cart_count = 0;
        printf("Compra finalizada!\n");
    }
}