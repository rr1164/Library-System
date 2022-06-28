#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
class User
{
public:
    User(int theId, std::string theName);
    User() = default;
    
    std::string get_name() const;

    int get_id() const;


    void set_id(int newId);
    
    void insert_new_user(int newId,std::string newName) ;
    

    void set_name(std::string newName);

    virtual ~User();

protected:
private:
    int id;
    std::string name;
};
#endif