#include "User_Book.h"
using namespace std;
User::User(int theId,std::string theName,std::vector<Book> books_owned)
{
    set_id(theId);
    set_name(theName);
    set_books_owned(books_owned);
}
User::User(){

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
Book::Book(int theId,std::string theName,int theQuantity,vector<User> theBorrowers)
{
    set_quantity(theQuantity);
    set_name(theName);
    set_id(theId);
    set_borrwers(theBorrowers);
}
Book::Book(){

}
string Book::get_name() const
{
    return name;
}
int Book::get_id() const{
    return id;
}
int Book::get_quantity() const{
    return quantity;
}
vector<User> Book::get_borrowers() const{
    return borrowers;
}
void Book::set_borrwers(vector<User> newBorrowers){
    borrowers = newBorrowers;
    return;
}

void Book::set_quantity(int newQuantity)
{
    assert(quantity >= 0);
    quantity = newQuantity;
    return;
}
void Book::set_id(int newId)
{
    id = newId;
    return;
}
void Book::set_name(string newName){
    name = newName;
    return;
}
Book::~Book()
{
    //dtor
}
User::~User()
{
    //dtor
}
