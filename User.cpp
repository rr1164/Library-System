#include "User.h"
#include "Book.h"
User::User(int theId, std::string theName)
{
    set_id(theId);
    set_name(theName);
}
User::User()
{
}
std::string User::get_name() const
{
    return name;
}
int User::get_id() const
{
    return id;
}
std::vector<Book*> User::get_books_owned() const
{
    return books_owned;
}
void User::set_id(int newId)
{
    id = newId;
    return;
}
void User::insert_new_user(int newId,std::string newName){
    id = newId;
    name = newName;
    return;
}
void User::set_books_owned(std::vector<Book*> newBooksOwned)
{
    books_owned = newBooksOwned;
    return;
}
void User::set_name(std::string newName)
{
    name = newName;
    return;
}
User::~User(){
    books_owned.clear();
}