#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Book.h"
#include "User.h"
class UsersManager {
   public:
    UsersManager() = default;

    User* find_user(int user_id) {
        int sz = users.size();
        for (int i = 0; i < sz; i++) {
            int current_user_id = users[i].get_id();
            if (current_user_id == user_id) {
                return &users[i];
            }
        }
        return nullptr;
    }

    bool user_exists(int user_id) {
        return find_user(user_id) != nullptr;
    }

    // inserting a new user with user id & user name
    bool add_new_user(int user_id, std::string user_name) {
        if (user_exists(user_id))
            return false;
        User user(user_id, user_name);
        users.push_back(user);
        return true;
    }

    void print_users() {
        int users_size = users.size();
        for (int i = 0; i < users_size; i++) {
            std::cout << users[i].get_name() << ' ';
        }
    }
    ~UsersManager(){
        users.clear();
    }
   private:
    // data of all users
    std::vector<User> users;
};

class BooksManager {
   public:
    BooksManager() = default;
    Book* find_book(int book_id) {
        int sz = books.size();
        for (int i = 0; i < sz; i++) {
            int current_book_id = books[i].get_id();
            if (current_book_id == book_id) {
                return &books[i];
            }
        }
        return nullptr;
    }

    bool book_exists(int book_id) {
        return find_book(book_id) != nullptr;
    }

    // inserting a new user with user id & user name
    bool add_new_book(int book_id, std::string book_name, int quantity) {
        if (book_exists(book_id))
            return false;
        Book book(book_id, book_name, quantity);
        books.push_back(book);
        return true;
    }

    void print_books() {
        int books_size = books.size();
        for (int i = 0; i < books_size; i++) {
            std::cout << books[i].get_name() << ' ';
        }
    }

    void search_for_a_book(std::string prefix) {
        int books_size = books.size();
        for (int i = 0; i < books_size; i++) {
            std::string book_name = books[i].get_name();
            if (book_name.compare(0, prefix.size(), prefix) == 0)
                std::cout << book_name << ' ';
        }
        std::cout << std::endl;
    }
    void sort_books_by_id() {
        sort(books.begin(), books.end(), [](const Book& lhs, const Book& rhs) {
            return lhs.get_id() < rhs.get_id();
        });
    }
    void sort_books_by_name() {
        sort(books.begin(),books.end(),[](const Book& lhs, const Book& rhs){
            return lhs.get_name() < rhs.get_name();});
    }
    ~BooksManager(){
        books.clear();
    }
   private:
    // data of all users
    std::vector<Book> books;
};
class BorrowingSystem {
   public:
    BorrowingSystem(UsersManager* userManager, BooksManager* booksManager)
        : usersmanager(userManager), booksmanager(booksManager) {
    }
    bool borrow_book(int user_id, int book_id) {
        User* user_borrowing = usersmanager->find_user(user_id);
        Book* book_to_be_borrowed = booksmanager->find_book(book_id);

        if (!user_borrowing || !book_to_be_borrowed || book_to_be_borrowed->get_quantity() <= 0 
            || check_user_borrowed_book(user_id,book_id))
            return false;

        int books_quantity = book_to_be_borrowed->get_quantity();

        book_to_be_borrowed->set_quantity(books_quantity - 1);

        std::vector<User>& book_borrowers = borrowers[book_id];

        User user_object{};

        user_object.set_id(user_borrowing->get_id());
        user_object.set_name(user_borrowing->get_name());
        book_borrowers.push_back(user_object);

        std::cout << "book borrowed successfully" << std::endl;

        return true;
    }
    bool check_user_borrowed_book(int user_id, int book_id) {
        for (std::pair<int, std::vector<User>> element : borrowers) {
            if (element.first == book_id) {
                std::vector<User> users_borrowing_book = element.second;
                int users_size = users_borrowing_book.size();
                for (int i = 0; i < users_size; i++)
                    if (user_id == users_borrowing_book[i].get_id())
                        return true;
            }
        }
        return false;
    }
    bool remove_borrower(int user_id, int book_id) {
        std::vector<User>& users_borrowing_book = borrowers[book_id];
        for (auto it = users_borrowing_book.begin(); it != users_borrowing_book.end(); it++) {
            if (user_id == it->get_id()) {
                users_borrowing_book.erase(it);
                return true;
            }
        }
        return false;
    }
    bool return_book(int user_id, int book_id) {
        User* user_borrowing = usersmanager->find_user(user_id);

        Book* book_to_be_borrowed = booksmanager->find_book(book_id);

        if (!user_borrowing || !book_to_be_borrowed || !check_user_borrowed_book(user_id, book_id))
            return false;

        int books_quantity = book_to_be_borrowed->get_quantity();

        book_to_be_borrowed->set_quantity(books_quantity + 1);

        assert(remove_borrower(user_id, book_id));

        std::cout << "book returned successfully" << std::endl;

        return true;
    }
    void print_borrowers_by_id(int book_id) {
        std::vector<User> users_borrowing = borrowers[book_id];
        int users_size = users_borrowing.size();
        for (int i = 0; i < users_size; i++)
            std::cout << users_borrowing[i].get_name() << ' ';
        std::cout << std::endl;
    }
    ~BorrowingSystem(){
        borrowers.clear();
    }
   private:
    UsersManager* usersmanager;
    BooksManager* booksmanager;
    std::unordered_map<int, std::vector<User>> borrowers;
};
void print_menu() {
    std::cout << std::endl;
    std::cout << "Library Menu: " << std::endl;
    std::cout << "1) Add book" << std::endl;
    std::cout << "2) search books by prefix" << std::endl;
    std::cout << "3) print who borrowed book by id" << std::endl;
    std::cout << "4) print library sorted by id" << std::endl;
    std::cout << "5) print library sorted by name" << std::endl;
    std::cout << "6) add user" << std::endl;
    std::cout << "7) borrow a book" << std::endl;
    std::cout << "8) user return book" << std::endl;
    std::cout << "9) print users" << std::endl;
    std::cout << "10) Exit" << std::endl;
    std::cout << "Enter your choice: [1-10] : ";
}

int main() {
    print_menu();
    UsersManager users_manager;
    BooksManager books_manager;
    BorrowingSystem borrowing_system(&users_manager, &books_manager);
    int command;
    while (std::cin >> command) {
        switch (command) {
            case 1: {
                /// add a new book to the system
                std::cout << "Enter book id,name & quantity: ";
                int id, quantity;
                std::string name;
                std::cin >> id >> name >> quantity;
                books_manager.add_new_book(id, name, quantity);
                break;
            }
            case 2: {
                /// search for a book
                std::cout << "Enter book name you are looking for: ";
                std::string name;
                std::cin >> name;
                books_manager.search_for_a_book(name);
                break;
            }
            case 3: {
                // print who borrowed book by name
                std::cout << "Input book id: ";
                int book_id;
                std::cin >> book_id;
                borrowing_system.print_borrowers_by_id(book_id);
                break;
            }
            case 4: {
                /// print all books sorted by id
                books_manager.sort_books_by_id();
                books_manager.print_books();
                break;
            }
            case 5: {
                /// print all books sorted lexicographically
                books_manager.sort_books_by_name();
                books_manager.print_books();
                break;
            }
            case 6: {
                /// add a new user to the system
                int id;
                std::string name;
                std::cout << "Enter user's id & name: ";
                std::cin >> id >> name;
                users_manager.add_new_user(id, name);
                break;
            }
            case 7: {
                /// let user borrow a book

                int user_id, book_id;

                std::cout << "Enter the user's id and the book's id you'd like to borrow: ";
                std::cin >> user_id >> book_id;

                if(!borrowing_system.borrow_book(user_id, book_id))
                    std::cout << "an error occured while borrowing the book" << std::endl;
                break;
            }
            case 8: {
                // return book function
                int user_id, book_id;

                std::cout << "Enter the user's id and the book's id you'd like to return: ";
                std::cin >> user_id >> book_id;

                if(!borrowing_system.return_book(user_id, book_id))
                        std::cout << "an error occured while returning the book" << std::endl;
            break;
            }
            case 9: {
                // print all users
                users_manager.print_users();
                break;
            }
            case 10:
                // exit
                return 1;
            default:
                std::cout << "not supported" << std::endl;
        }
        print_menu();
    }
    return 0;
}
