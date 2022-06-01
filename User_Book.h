#ifndef USER_H
#define USER_H
#include <bits/stdc++.h>
class Book;
class User
{
    public:
        User(int theId,std::string theName,std::vector<Book> books_owned);
        User();
        std::string get_name() const;

        int get_id() const;

        std::vector<Book> get_books_owned() const;

        void set_id(int newId);

        void set_books_owned(std::vector<Book> newBooksOwned);

        void set_name(std::string newName);

        virtual ~User();

    protected:

    private:
        int id;
        std::string name;
        std::vector<Book> books_owned;
};
class Book
{
    public:
        Book(int theId,std::string theName,int theQuantity,std::vector<User> theBorrowers);
        Book();

        std::string get_name() const;

        int get_quantity() const;

        int get_id() const;

        std::vector<User> get_borrowers() const;

        void set_quantity(int newQuantity);

        void set_name(std::string newName);

        void set_id(int newId);

       void set_borrwers(std::vector<User> newborrowers);

        virtual ~Book();

    protected:

    private:
        int id;
        std::string name;
        int quantity;
        std::vector<User> borrowers;
};

#endif
