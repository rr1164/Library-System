#include "Book.h"
#include "User.h"
#include <vector>
#include <cassert>
#include <string>
Book::Book(int theId, std::string theName, int theQuantity, std::vector<User*> theBorrowers)
{
    set_quantity(theQuantity);
    set_name(theName);
    set_id(theId);
    set_borrwers(theBorrowers);
}
Book::Book()
{
}
std::string Book::get_name() const
{
    return name;
}
int Book::get_quantity() const
{
    return quantity;
}
int Book::get_id() const
{
    return id;
}

std::vector<User*> Book::get_borrowers() const
{
    return borrowers;
}
void Book::set_quantity(int newQuantity)
{
    assert(newQuantity >= 0);
    quantity = newQuantity;
    return;
}
void Book::set_name(std::string newName)
{
    name = newName;
    return;
}

void Book::set_id(int newId)
{
    id = newId;
    return;
}
void Book::set_borrwers(std::vector<User*> newborrowers)
{
    borrowers = newborrowers;
    return;
}

Book::~Book(){
    borrowers.clear();
}
