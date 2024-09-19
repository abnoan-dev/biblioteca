#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdbool.h>

#define EMAIL_LENGTH 80
#define PASSWORD_LENGTH 20
#define TITLE_LENGTH 50
#define AUTHOR_LENGTH 50

// Estrutura de usuário
typedef struct {
    char username[EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

// Estrutura de livro
typedef struct {
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    bool on_sale;
} Book;

// Estrutura de item do carrinho
typedef struct {
    Book *book;
} CartItem;

// TAD UserSystem
typedef struct {
    User *users;
    int user_count;
} UserSystem;

void UserSystem_init(UserSystem *system);
void UserSystem_register(UserSystem *system);
bool UserSystem_login(UserSystem *system);
void UserSystem_save_to_file(UserSystem *system);
void UserSystem_load_from_file(UserSystem *system);

// TAD BookSystem
typedef struct {
    Book *books;
    int book_count;
} BookSystem;

void BookSystem_init(BookSystem *system);
void BookSystem_add(BookSystem *system);
void BookSystem_list(BookSystem *system);
void BookSystem_save_to_file_txt(BookSystem *system);
void BookSystem_load_from_file_txt(BookSystem *system);
void BookSystem_edit(BookSystem *system);
void BookSystem_delete(BookSystem *system);
void BookSystem_sort(BookSystem *system);
int BookSystem_binary_search(BookSystem *system, const char *title);

// TAD CartSystem
typedef struct {
    CartItem *items;
    int cart_count;
} CartSystem;

void CartSystem_init(CartSystem *system);
void CartSystem_add(CartSystem *system, BookSystem *book_system);
void CartSystem_checkout(CartSystem *system);

#endif
