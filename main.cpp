#include <bits/stdc++.h>
#include "User_Book.cpp"
using namespace std;


vector<Book> books;
vector<User> users;
vector<User> empty_users_vector;
vector<Book> empty_books_vector;


void insert_new_book(int id,int quantity,string name);
bool Cmp_Id(Book i, Book j);
bool Cmp_name(Book i, Book j);
void print_all_books();
bool find_book(string name,Book& bk);
bool find_book(int book_id,Book& bk);
bool find_user(int user_id,User& us);
void return_book(User user,Book book);
void borrow_book(User user,Book book);
void add_user(int id,string name);
void print_all_users();


int main()
{
    cout << "Library Menu: " << endl;
    cout << "1) Add book" << endl;
    cout << "2) search books by prefix" << endl;
    cout << "3) print who borrowed book by name" << endl;
    cout << "4) print library by id" << endl;
    cout << "5) print library by name" << endl;
    cout << "6) add user" << endl;
    cout << "7) user borrow book" << endl;
    cout << "8) user return book" << endl;
    cout << "9) print users" << endl;
    cout << "10) Exit" << endl;
    cout << "Enter your choice: [1-10] : ";
    int command;
    while(cin>>command)
    {

        switch(command)
        {
        case 1:
        {
            /// add a new book to the system
            cout << "Enter book id,name & quantity: ";
            int id,quantity;
            string name;
            cin>>id>>name>>quantity;
            insert_new_book(id,quantity,name);
            break;
        }
        case 2:
        {
            /// search for a book
            cout << "Enter book name you are looking for: ";
            string name;
            cin>>name;
            bool found = 0;
            for(int i = 0; i < books.size(); i++)
            {
                bool flag = 0;
                Book current_book = books[i];
                string book_name = current_book.get_name();
                for(int f = 0; f < min(name.size(),book_name.size()); f++){
                    if(tolower(name[f]) != tolower(book_name[f])){
                        flag = 1;
                        break;
                    }
                }
                if(!flag){
                    cout << (found != 0 ? ", " : "") << book_name;
                    found = 1;
                }
            }
            cout << endl;
            break;
        }
        case 3:
        {
            cout << "Input book name: ";
            string name;
            cin>>name;
            Book bk {};
            if(!find_book(name,bk)){
                cout << "couldn't find book" << endl;
            }
            else{
                vector<User> borrowers = bk.get_borrowers();
                for(int i = 0; i < borrowers.size(); i++){
                    cout << borrowers[i].get_name() << ' ';
                }
                cout << endl;
            }
            break;
        }
        case 4:
        {
            /// print all books sorted by their ids
            sort(books.begin(),books.end(),Cmp_Id);
            print_all_books();
            break;
        }
        case 5:
        {
            /// print all books sorted lexicographically
            sort(books.begin(),books.end(),Cmp_name);
            print_all_books();
            break;
        }
        case 6:
        {
            /// add a new user to the system
            int id;
            string name;
            cout << "Enter user's id & name: ";
            cin>>id>>name;
            add_user(id,name);
            break;
        }
        case 7:
        {
            /// let user borrow a book

            int user_id, book_id;

            cout << "Enter the user's id and the book's id you'd like to borrow: ";
            cin>>user_id>>book_id;

            Book book;
            User user;

            if(!find_user(user_id,user))
                cout << "user not found!" << endl;
            else if(!find_book(book_id,book))
                cout << "book not found" << endl;
            else{
                borrow_book(user,book);
            }
            break;
        }
        case 8:
        {
            int user_id, book_id;

            cout << "Enter the user's id and the book's id you'd like to return: ";
            cin>>user_id>>book_id;

            Book book;
            User user;

            if(!find_user(user_id,user))
                cout << "user not found!" << endl;
            else if(!find_book(book_id,book))
                cout << "book not found" << endl;
            else{
                return_book(user,book);
            }
            break;
        }
        case 9:
        {
            print_all_users();
            break;
        }
        case 10:
            return 1;
        default:
            cout << "not supported" << endl;
        }
        cout << endl;
        cout << "Library Menu: " << endl;
        cout << "1) Add book" << endl;
        cout << "2) search books by prefix" << endl;
        cout << "3) print who borrowed book by name" << endl;
        cout << "4) print library by id" << endl;
        cout << "5) print library by name" << endl;
        cout << "6) add user" << endl;
        cout << "7) borrow a book" << endl;
        cout << "8) user return book" << endl;
        cout << "9) print users" << endl;
        cout << "10) Exit" << endl;
        cout << "Enter your choice: [1-10] : ";
    }
    return 0;
}
void print_all_books()
{
    for(int i = 0; i < books.size(); i++)
        cout << books[i].get_name() << ' ';
    cout << endl;
}
void print_all_users()
{
    for(int i = 0; i < users.size(); i++)
        cout << users[i].get_name() << ' ';
    cout << endl;
}
void borrow_book(User user,Book book)
{
    int quantity = book.get_quantity();
    if(!quantity)
        cout << "no available copies of " + book.get_name() << endl;
    else
    {
       bool flag = 0;
       
       vector<Book> books = user.get_books_owned();
       vector<Book>& books_owned  = books;
    
       vector<User> users = book.get_borrowers();
       vector<User>& users_borrowed = users;


        for(int i = 0; i < books_owned.size();i++){
            Book bk = books_owned[i];
            if(bk.get_id() == book.get_id()){
                flag = 1;
                break;
            }
        }
        if(flag){
            cout << "user already owns " << book.get_name() << endl;
            return;
        }
        book.set_quantity(quantity - 1);


        books_owned.push_back(book);


        users_borrowed.push_back(user);
    }
}
void return_book(User user,Book book)
{
    vector<Book> books = user.get_books_owned();
    
    vector<User> users = book.get_borrowers();

    vector<Book>& books_owned = books;

    vector<User>& users_borrowed = users;

    int book_index = -1;

    int quantity = book.get_quantity();

    int user_index = -1;

    for(int i = 0; i < books_owned.size();i++){
        Book bk = books_owned[i];
        if(bk.get_id() == book.get_id()){
            book_index = i;
            break;
        }
    }
    if(book_index == -1){
            cout << "user doesn't own the book" << endl;
            return;
    }


    book.set_quantity(quantity + 1);

    for(int i = 0; i < users_borrowed.size();i++){
        User us = users_borrowed[i];
        if(us.get_id() == user.get_id()){
            user_index = i;
            break;
        }
    }

    books_owned.erase(books_owned.begin() + book_index);

    users_borrowed.erase(users_borrowed.begin() + user_index);

}
bool find_book(string name,Book & bk)
{
    for(int i = 0; i < books.size(); i++)
    {
        Book current_book = books[i];
        string book_name = current_book.get_name();
        for(int f = 0; f < min(name.size(),book_name.size()); f++)
        {
            if(tolower(name[f]) != tolower(book_name[f]))
            {
                bk = current_book;
                return true;
            }
        }
    }
    return false;
}
bool find_book(int book_id,Book& bk)
{
    for(int i = 0; i < books.size(); i++)
    {
        Book current_book = books[i];
        if(book_id == current_book.get_id()){
            bk = current_book;
            return true;
        }
    }
    return false;
}
bool find_user(int user_id,User& us)
{
    for(int i = 0; i < users.size(); i++)
    {
        User current_user = users[i];
        cout << user_id << ' ' << current_user.get_id() << endl;
        if(user_id == current_user.get_id()){
            us = current_user;
            return true;
        }
    }
    return false;
}
void add_user(int id,string name)
{
    cout << id << ' ' << name << endl;
    User user{id,name,empty_books_vector};
    cout << user.get_id()  << ' ' << user.get_name() << endl;
    users.push_back(user);
}
void insert_new_book(int id,int quantity,string name)
{
    Book book {id,name,quantity,empty_users_vector};
    books.push_back(book);
}
bool Cmp_Id(Book i, Book j)
{
    return i.get_id() < j.get_id();
}
bool Cmp_name(Book i, Book j)
{
    return i.get_name() < j.get_name();
}
