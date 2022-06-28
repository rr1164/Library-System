#include "User.h"
User::User(int theId, std::string theName)
{
    set_id(theId);
    set_name(theName);
}
std::string User::get_name() const
{
    return name;
}
int User::get_id() const
{
    return id;
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
void User::set_name(std::string newName)
{
    name = newName;
    return;
}
User::~User(){
    name.clear();
}