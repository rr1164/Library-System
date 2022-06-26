#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
class Book;
class User
{
public:
    User(int theId, std::string theName);
    User();
    
    std::string get_name() const;

    int get_id() const;

    std::vector<Book*> get_books_owned() const;

    void set_id(int newId);
    
    void insert_new_user(int newId,std::string newName) ;
    
    void set_books_owned(std::vector<Book*> newBooksOwned);

    void set_name(std::string newName);

    virtual ~User();

protected:
private:
    int id;
    std::string name;
    std::vector<Book*> books_owned;
};
#endif