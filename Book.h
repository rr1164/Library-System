
#ifndef BOOK_H
#define BOOK_H
#include <vector>
#include <string>
class User;
class Book
{
public:
    Book(int theId, std::string theName, int theQuantity, std::vector<User*> theBorrowers);
    Book();

    std::string get_name() const;

    int get_quantity() const;

    int get_id() const;

    std::vector<User*> get_borrowers() const;

    void set_quantity(int newQuantity);

    void set_name(std::string newName);

    void set_id(int newId);

    void set_borrwers(std::vector<User*> newborrowers);

    virtual ~Book();

protected:
private:
    int id;
    std::string name;
    int quantity;
    std::vector<User*> borrowers;
};
#endif