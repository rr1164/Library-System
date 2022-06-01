#include <bits/stdc++.h>
#include "User_Book.cpp"
using namespace std;


UsersList users;
vector<Book> empty_books_vector;
BooksList books;


void insert_new_book(int id,int quantity,string name);
bool Cmp_Id(Book* i, Book* j);
bool Cmp_name(Book* i, Book* j);
void print_all_books();
bool find_book(string name);
bool find_book(int book_id);
bool find_user(int user_id);
void return_book(User* user,Book* book);
void borrow_book(User* user,Book* book);
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
            vector<Book*> boks = books.get_list();
            for(int i = 0; i < boks.size(); i++)
            {
                bool flag = 0;
                Book* current_book = boks[i];
                string book_name = current_book->get_name();
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
            
            if(!find_book(name)){
                cout << "couldn't find book" << endl;
            }
            else{
                Book* bk;
                vector<Book*> boks;
                for(int i = 0; i < boks.size();i++){
                        Book* new_book = boks[i];
                        if(new_book->get_name().size() == name.size()){
                            if(new_book->get_name() == name){ 
                                bk = new_book;
                                break;
                            }
                        }
                }
                vector<User> borrowers = bk->get_borrowers();
                cout << "number of borrowers: " << borrowers.size() << ' ' << bk->get_quantity() << endl;
                for(int i = 0; i < borrowers.size(); i++){
                    cout << borrowers[i].get_name() << endl;
                }
            }
            break;
        }
        case 4:
        {
            vector<Book*> boks = books.get_list();
            sort(boks.begin(),boks.end(),Cmp_Id);
            print_all_books();
            break;
        }
        case 5:
        {
            /// print all books sorted lexicographically
            vector<Book*> boks = books.get_list();
            sort(boks.begin(),boks.end(),Cmp_name);
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

            Book* book;
            User* user;

            if(!find_user(user_id))
                cout << "user not found!" << endl;
            else if(!find_book(book_id))
                cout << "book not found" << endl;
            else{
                vector<Book*> boks = books.get_list();
                vector<User*> uses = users.get_list();
                for(int i = 0; i < boks.size();i++){
                        if(boks[i]->get_id() == book_id){
                                book = boks[i];
                                break;
                        }
                }
                for(int i = 0; i < uses.size();i++){
                        if(uses[i]->get_id() == user_id){
                                user = uses[i];
                                break;
                        }
                }
                borrow_book(user,book); 

            }
            break;
        }
        case 8:
        {
            int user_id, book_id;

            cout << "Enter the user's id and the book's id you'd like to return: ";
            cin>>user_id>>book_id;

            
            Book* book;
            User* user;

            if(!find_user(user_id))
                cout << "user not found!" << endl;
            else if(!find_book(book_id))
                cout << "book not found" << endl;
            else{
                vector<Book*> boks = books.get_list();
                vector<User*> uses = users.get_list();
                for(int i = 0; i < boks.size();i++){
                        if(boks[i]->get_id() == book_id){
                                book = boks[i];
                                break;
                        }
                }
                for(int i = 0; i < uses.size();i++){
                        if(uses[i]->get_id() == user_id){
                                user = uses[i];
                                break;
                        }
                }
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
        case 11:
        
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
    vector<Book*> boks = books.get_list();
    for(int i = 0; i < boks.size(); i++)
        cout << boks[i]->get_name() << endl;
    cout << endl;
}
void print_all_users()
{
    vector<User*> uses;
    for(int i = 0; i < uses.size(); i++)
        cout << uses[i]->get_name() << endl;
    cout << endl;
}
void borrow_book(User* user,Book* book)
{
    int quantity = book->get_quantity();
    if(!quantity)
        cout << "no available copies of " + book->get_name() << endl;
    else
    {
       bool flag = 0;
       
       vector<Book> books_owned  = user->get_books_owned();
    
       vector<User> users_borrowed = book->get_borrowers();


        for(int i = 0; i < books_owned.size();i++){
            Book bk = books_owned[i];
            if(bk.get_id() == book->get_id()){
                flag = 1;
                break;
            }
        }
        if(flag){
            cout << "user already owns " << book->get_name() << endl;
            return;
        }
        book->set_quantity(quantity - 1);


        books_owned.push_back(*book);

        user->set_books_owned(books_owned);

        users_borrowed.push_back(*user);

        book->set_borrwers(users_borrowed);

    }
}
void return_book(User* user,Book* book)
{
    vector<Book> books = user->get_books_owned();
    
    vector<User> users = book->get_borrowers();

    vector<Book>& books_owned = books;

    vector<User>& users_borrowed = users;

    int book_index = -1;

    int quantity = book->get_quantity();

    int user_index = -1;

    for(int i = 0; i < books_owned.size();i++){
        Book bk = books_owned[i];
        if(bk.get_id() == book->get_id()){
            book_index = i;
            break;
        }
    }
    if(book_index == -1){
            cout << "user doesn't own " + book->get_name() << endl;
            return;
    }


    book->set_quantity(quantity + 1);

    for(int i = 0; i < users_borrowed.size();i++){
        User us = users_borrowed[i];
        if(us.get_id() == user->get_id()){
            user_index = i;
            break;
        }
    }

    books_owned.erase(books_owned.begin() + book_index);

    users_borrowed.erase(users_borrowed.begin() + user_index);

    book->set_borrwers(users_borrowed);

    user->set_books_owned(books_owned);

}
bool find_book(string name)
{
    vector<Book*> boks = books.get_list();
    for(int i = 0; i < boks.size(); i++)
    {
        Book* current_book = boks[i];
        string book_name = current_book->get_name();
        bool flag = 0;
        if(name.size() != book_name.size())
            continue;
        for(int f = 0; f < min(name.size(),book_name.size()); f++){
            if(tolower(name[f]) != tolower(book_name[f])){
                flag = 1;
                break;
            }
        }
        if(!flag){
            return true;
        }
    }
    return false;
}
bool find_book(int book_id)
{
    vector<Book*> boks = books.get_list();
    for(int i = 0; i < boks.size(); i++)
    {
        Book* current_book = boks[i];
        if(book_id == current_book->get_id()){
            return true;
        }
    }
    return false;
}
bool find_user(int user_id)
{
    vector<User*> uses;
    for(int i = 0; i < uses.size(); i++)
    {
        User* current_user = uses[i];
        if(user_id == current_user->get_id()){
            return true;
        }
    }
    return false;
}
void add_user(int id,string name)
{
    User user{id,name,empty_books_vector};
    users.insert_new_user(id,name);
    
}
void insert_new_book(int id,int quantity,string name)
{
    books.insert_new_book(id,quantity,name);
}
bool Cmp_Id(Book* i, Book* j)
{
    return i->get_id() < j->get_id();
}
bool Cmp_name(Book* i, Book* j)
{
    return i->get_name() < j->get_name();
}
