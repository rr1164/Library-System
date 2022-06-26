#include "Book.h"
#include "User.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
std::vector<User *> users;
std::vector<Book> empty_books_vector;
std::vector<Book *> books;

void insert_new_book(int id, int quantity, std::string name);
bool Cmp_Id(Book *i, Book *j);
bool Cmp_name(Book *i, Book *j);
void print_all_books(std::vector<Book *> boks);
bool find_book(std::string name);
bool find_book(int book_id);
bool find_user(int user_id);
void return_book(User *user, Book *book);
void borrow_book(User *user, Book *book);
void add_user(int id, std::string name);
void print_all_users();

int main() {
    std::cout << "Library Menu: " << std::endl;
    std::cout << "1) Add book" << std::endl;
    std::cout << "2) search books by prefix" << std::endl;
    std::cout << "3) print who borrowed book by name" << std::endl;
    std::cout << "4) print library by id" << std::endl;
    std::cout << "5) print library by name" << std::endl;
    std::cout << "6) add user" << std::endl;
    std::cout << "7) user borrow book" << std::endl;
    std::cout << "8) user return book" << std::endl;
    std::cout << "9) print users" << std::endl;
    std::cout << "10) Exit" << std::endl;
    std::cout << "Enter your choice: [1-10] : ";
    int command;
    while (std::cin >> command) {
        switch (command) {
            case 1: {
                /// add a new book to the system
                std::cout << "Enter book id,name & quantity: ";
                int id, quantity;
                std::string name;
                std::cin >> id >> name >> quantity;
                insert_new_book(id, quantity, name);
                break;
            }
            case 2: {
                /// search for a book
                std::cout << "Enter book name you are looking for: ";
                std::string name;
                std::cin >> name;
                bool found = 0;
                for (int i = 0; i < books.size(); i++) {
                    bool flag = 0;
                    Book *current_book = books[i];
                    std::string book_name = current_book->get_name();
                    for (int f = 0; f < std::min(name.size(), book_name.size()); f++) {
                        if (tolower(name[f]) != tolower(book_name[f])) {
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag) {
                        std::cout << (found != 0 ? ", " : "") << book_name;
                        found = 1;
                    }
                }
                std::cout << std::endl;
                break;
            }
            case 3: {
                std::cout << "Input book name: ";
                std::string name;
                std::cin >> name;

                if (!find_book(name)) {
                    std::cout << "couldn't find book" << std::endl;
                } else {
                    Book *bk = nullptr;
                    for (int i = 0; i < books.size(); i++) {
                        Book *new_book = books[i];
                        if (new_book->get_name().size() == name.size()) {
                            if (new_book->get_name() == name) {
                                bk = new_book;
                                break;
                            }
                        }
                    }
                    assert(bk);
                    std::vector<User *> borrowers = bk->get_borrowers();
                    std::cout << "number of borrowers: " << borrowers.size() << ' ' << bk->get_quantity() << std::endl;
                    for (int i = 0; i < borrowers.size(); i++) {
                        std::cout << borrowers[i]->get_name() << std::endl;
                    }
                }
                break;
            }
            case 4: {
                sort(books.begin(), books.end(), Cmp_Id);
                print_all_books(books);
                break;
            }
            case 5: {
                /// print all books sorted lexicographically
                sort(books.begin(), books.end(), Cmp_name);
                print_all_books(books);
                break;
            }
            case 6: {
                /// add a new user to the system
                int id;
                std::string name;
                std::cout << "Enter user's id & name: ";
                std::cin >> id >> name;
                add_user(id, name);
                break;
            }
            case 7: {
                /// let user borrow a book

                int user_id, book_id;

                std::cout << "Enter the user's id and the book's id you'd like to borrow: ";
                std::cin >> user_id >> book_id;

                Book *book = nullptr;
                User *user = nullptr;

                if (!find_user(user_id))
                    std::cout << "user not found!" << std::endl;
                else if (!find_book(book_id))
                    std::cout << "book not found" << std::endl;
                else {
                    for (int i = 0; i < books.size(); i++) {
                        if (books[i]->get_id() == book_id) {
                            book = books[i];
                            break;
                        }
                    }
                    for (int i = 0; i < users.size(); i++) {
                        if (users[i]->get_id() == user_id) {
                            user = users[i];
                            break;
                        }
                    }
                    borrow_book(user, book);
                }
                break;
            }
            case 8: {
                int user_id, book_id;

                std::cout << "Enter the user's id and the book's id you'd like to return: ";
                std::cin >> user_id >> book_id;

                Book *book;
                User *user;

                if (!find_user(user_id))
                    std::cout << "user not found!" << std::endl;
                else if (!find_book(book_id))
                    std::cout << "book not found" << std::endl;
                else {
                    for (int i = 0; i < books.size(); i++) {
                        if (books[i]->get_id() == book_id) {
                            book = books[i];
                            break;
                        }
                    }
                    for (int i = 0; i < users.size(); i++) {
                        if (users[i]->get_id() == user_id) {
                            user = users[i];
                            break;
                        }
                    }
                    return_book(user, book);
                }
                break;
            }
            case 9: {
                print_all_users();
                break;
            }
            case 10:
                return 1;
            case 11:

            default:
                std::cout << "not supported" << std::endl;
        }
        std::cout << std::endl;
        std::cout << "Library Menu: " << std::endl;
        std::cout << "1) Add book" << std::endl;
        std::cout << "2) search books by prefix" << std::endl;
        std::cout << "3) print who borrowed book by name" << std::endl;
        std::cout << "4) print library by id" << std::endl;
        std::cout << "5) print library by name" << std::endl;
        std::cout << "6) add user" << std::endl;
        std::cout << "7) borrow a book" << std::endl;
        std::cout << "8) user return book" << std::endl;
        std::cout << "9) print users" << std::endl;
        std::cout << "10) Exit" << std::endl;
        std::cout << "Enter your choice: [1-10] : ";
    }
    return 0;
}
void print_all_books(std::vector<Book *> boks) {
    for (int i = 0; i < boks.size(); i++)
        std::cout << boks[i]->get_name() << std::endl;
    std::cout << std::endl;
}
void print_all_users() {
    for (int i = 0; i < users.size(); i++)
        std::cout << users[i]->get_name() << std::endl;
    std::cout << std::endl;
}
void borrow_book(User *user, Book *book) {
    int quantity = book->get_quantity();
    if (!quantity)
        std::cout << "no available copies of " + book->get_name() << std::endl;
    else {
        bool flag = 0;

        std::vector<Book *> books_owned = user->get_books_owned();

        std::vector<User *> users_borrowed = book->get_borrowers();

        for (int i = 0; i < books_owned.size(); i++) {
            Book *bk = books_owned[i];
            if (bk->get_id() == book->get_id()) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            std::cout << "user already owns " << book->get_name() << std::endl;
            return;
        }
        book->set_quantity(quantity - 1);

        books_owned.push_back(book);

        user->set_books_owned(books_owned);

        users_borrowed.push_back(user);

        book->set_borrwers(users_borrowed);
    }
}
void return_book(User *user, Book *book) {
    std::vector<Book*> books = user->get_books_owned();

    std::vector<User*> users = book->get_borrowers();

    std::vector<Book*>& books_owned = books;

    std::vector<User*>& users_borrowed = users;

    int book_index = -1;

    int quantity = book->get_quantity();

    int user_index = -1;

    for (int i = 0; i < books_owned.size(); i++) {
        Book* bk = books_owned[i];
        if (bk->get_id() == book->get_id()) {
            book_index = i;
            break;
        }
    }
    if (book_index == -1) {
        std::cout << "user doesn't own " + book->get_name() << std::endl;
        return;
    }

    book->set_quantity(quantity + 1);

    for (int i = 0; i < users_borrowed.size(); i++) {
        User* us = users_borrowed[i];
        if (us->get_id() == user->get_id()) {
            user_index = i;
            break;
        }
    }

    books_owned.erase(books_owned.begin() + book_index);

    users_borrowed.erase(users_borrowed.begin() + user_index);

    book->set_borrwers(users_borrowed);

    user->set_books_owned(books_owned);
}
bool find_book(std::string name) {
    for (int i = 0; i < books.size(); i++) {
        Book *current_book = books[i];
        std::string book_name = current_book->get_name();
        bool flag = 0;
        if (name.size() != book_name.size())
            continue;
        for (int f = 0; f < std::min(name.size(), book_name.size()); f++) {
            if (tolower(name[f]) != tolower(book_name[f])) {
                flag = 1;
                break;
            }
        }
        if (!flag) {
            return true;
        }
    }
    return false;
}
bool find_book(int book_id) {
    for (int i = 0; i < books.size(); i++) {
        Book *current_book = books[i];
        if (book_id == current_book->get_id()) {
            return true;
        }
    }
    return false;
}
bool find_user(int user_id) {
    for (int i = 0; i < users.size(); i++) {
        User *current_user = users[i];
        if (user_id == current_user->get_id()) {
            return true;
        }
    }
    return false;
}
void add_user(int id, std::string name) {
     User *user = nullptr;
     user->set_id(id);
     user->set_name(name);
     users.push_back(user);
}
void insert_new_book(int id, int quantity, std::string name) {
     Book *book = nullptr;
     book->set_id(id);
     book->set_quantity(quantity);
     book->set_name(name);
     books.push_back(book);
}
bool Cmp_Id(Book *i, Book *j) {
    return i->get_id() < j->get_id();
}
bool Cmp_name(Book *i, Book *j) {
    std::string a = i->get_name(), b = j->get_name();
    for (int i = 0; i < a.size(); i++)
        a[i] = tolower(a[i]);
    for (int i = 0; i < b.size(); i++)
        b[i] = tolower(b[i]);
    return a < b;
}