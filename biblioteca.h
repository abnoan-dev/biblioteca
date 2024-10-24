#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <stdbool.h>

#define EMAIL_LENGTH 80
#define PASSWORD_LENGTH 20
#define TITLE_LENGTH 50
#define AUTHOR_LENGTH 50

// Estrutura de usuário
typedef struct User {
    char username[EMAIL_LENGTH];
    char password[PASSWORD_LENGTH];
    struct User *next;
} User;

// Estrutura de livro
typedef struct Book {
    char title[TITLE_LENGTH];
    char author[AUTHOR_LENGTH];
    bool on_sale;
    struct Book *next;
} Book;

// Estrutura de item do carrinho
typedef struct CartItem {
    Book *book;
    struct CartItem *next;
} CartItem;

// TAD UserSystem
typedef struct {
    User *head;
} UserSystem;

void UserSystem_init(UserSystem *system);
void UserSystem_register(UserSystem *system);
bool UserSystem_login(UserSystem *system);
void UserSystem_save_to_file(UserSystem *system);
void UserSystem_load_from_file(UserSystem *system);

// TAD BookSystem
typedef struct {
    Book *head;
} BookSystem;

void BookSystem_init(BookSystem *system);
void BookSystem_add(BookSystem *system);
void BookSystem_list(BookSystem *system);
void BookSystem_save_to_file_txt(BookSystem *system);
void BookSystem_load_from_file_txt(BookSystem *system);
void BookSystem_edit(BookSystem *system);
void BookSystem_delete(BookSystem *system);
Book* BookSystem_find(BookSystem *system, const char *title);

// TAD CartSystem
typedef struct {
    CartItem *head;
} CartSystem;

void CartSystem_init(CartSystem *system);
void CartSystem_add(CartSystem *system, BookSystem *book_system);
void CartSystem_checkout(CartSystem *system);

#endif
