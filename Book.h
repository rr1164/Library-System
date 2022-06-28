
#ifndef BOOK_H
#define BOOK_H
#include <vector>
#include <string>

class Book
{
public:
    Book(int theId, std::string theName, int theQuantity);
    
    Book() = default;

    std::string get_name() const;

    int get_quantity() const;

    int get_id() const;

    void set_quantity(int newQuantity);

    void set_name(std::string newName);

    void set_id(int newId);


    virtual ~Book();

protected:
private:
    int id;
    std::string name;
    int quantity;
};
#endif