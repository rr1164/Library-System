#include "Book.h"
#include <cassert>
Book::Book(int theId, std::string theName, int theQuantity)
{
    set_quantity(theQuantity);
    set_name(theName);
    set_id(theId);
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
Book::~Book(){
    name.clear();
}
