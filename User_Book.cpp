#include "User_Book.h"
using namespace std;
User::User(int theId, std::string theName, std::vector<Book> The_books_owned)
{
    set_id(theId);
    set_name(theName);
    set_books_owned(The_books_owned);
}
User::User()
{
}
vector<Book> User::get_books_owned() const
{
    return books_owned;
}
int User::get_id() const
{
    return id;
}
string User::get_name() const
{
    return name;
}
void User::set_id(int newId)
{
    id = newId;
    return;
}
void User::set_books_owned(vector<Book> newBooksOwned)
{
    books_owned = newBooksOwned;
    return;
}
void User::set_name(string newName)
{
    name = newName;
    return;
}
Book::Book(int theId, std::string theName, int theQuantity, vector<User> theBorrowers)
{
    set_quantity(theQuantity);
    set_name(theName);
    set_id(theId);
    set_borrwers(theBorrowers);
}
Book::Book()
{
}
string Book::get_name() const
{
    return name;
}
int Book::get_id() const
{
    return id;
}
int Book::get_quantity() const
{
    return quantity;
}
vector<User> Book::get_borrowers() const
{
    return borrowers;
}
void Book::set_borrwers(vector<User> newBorrowers)
{
    borrowers = newBorrowers;
    return;
}

void Book::set_quantity(int newQuantity)
{
    assert(newQuantity >= 0);
    cout << newQuantity << endl;
    quantity = newQuantity;
    return;
}
void Book::set_id(int newId)
{
    id = newId;
    return;
}
void Book::set_name(string newName)
{
    name = newName;
    return;
}
class BooksList
{
public:
    Book *insert_new_book(int id, int quantity, string name)
    {
        vector<User> empty_users_vector;
        Book *book = new Book{id, name, quantity, empty_users_vector};
        books.push_back(book);
        return book;
    }
    vector<Book *> get_list()
    {
        return books;
    }

    ~BooksList()
    {
        size_t sz = books.size();
        for (size_t i = 0; i < sz; ++i)
            delete books[i];
    }

private:
    std::vector<Book *> books;
};
class UsersList
{
public:
    User *insert_new_user(int id, string name)
    {
        vector<Book> empty_books_vector;
        User *user = new User(id, name, empty_books_vector);
        users.push_back(user);
        return user;
    }
    vector<User *> get_list()
    {
        return users;
    }

    ~UsersList()
    {
        size_t sz = users.size();
        for (size_t i = 0; i < sz; ++i)
            delete users[i];
    }

private:
    std::vector<User *> users;
};
Book::~Book()
{
    // dtor
}
User::~User()
{
    // dtor
}
