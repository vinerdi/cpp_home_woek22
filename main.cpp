#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

#define LOG_OPERATION(operation, book) \
    { \
        std::ofstream logFile("library.log", std::ios_base::app); \
        logFile << operation << ": " << book.getTitle() << " by " << book.getAuthor() << std::endl; \
    }

#define FIND_BOOK_BY_AUTHOR(manager, author) \
    { \
        auto books = manager.findBooksByAuthor(author); \
        for (const auto& book : books) { \
            std::cout << book.getTitle() << " by " << book.getAuthor() << std::endl; \
        } \
    }

namespace Library {
    class Book {
    private:
        std::string title;
        std::string author;
        int year;
        std::string genre;

    public:
        Book(const std::string& title, const std::string& author, int year, const std::string& genre)
            : title(title), author(author), year(year), genre(genre) {}

        std::string getTitle() const { return title; }
        std::string getAuthor() const { return author; }
        int getYear() const { return year; }
        std::string getGenre() const { return genre; }

        void setTitle(const std::string& title) { this->title = title; }
        void setAuthor(const std::string& author) { this->author = author; }
        void setYear(int year) { this->year = year; }
        void setGenre(const std::string& genre) { this->genre = genre; }
    };
}

namespace Management {
    class LibraryManager {
    private:
        std::vector<Library::Book> books;

    public:
        void addBook(const Library::Book& book) {
            books.push_back(book);
            LOG_OPERATION("Added", book);
        }

        void removeBook(const std::string& title) {
            books.erase(std::remove_if(books.begin(), books.end(),
                [&title](const Library::Book& book) { return book.getTitle() == title; }), books.end());
        }

        std::vector<Library::Book> findBooksByAuthor(const std::string& author) {
            std::vector<Library::Book> result;
            for (const auto& book : books) {
                if (book.getAuthor() == author) {
                    result.push_back(book);
                }
            }
            return result;
        }

        std::vector<Library::Book> getAllBooks() const {
            return books;
        }

        void sortBooksByTitle() {
            std::sort(books.begin(), books.end(), [](const Library::Book& a, const Library::Book& b) {
                return a.getTitle() < b.getTitle();
            });
        }

        void sortBooksByAuthor() {
            std::sort(books.begin(), books.end(), [](const Library::Book& a, const Library::Book& b) {
                return a.getAuthor() < b.getAuthor();
            });
        }

        void sortBooksByYear() {
            std::sort(books.begin(), books.end(), [](const Library::Book& a, const Library::Book& b) {
                return a.getYear() < b.getYear();
            });
        }
    };
}

int main() {
    Management::LibraryManager manager;

    Library::Book book1("Book One", "Author A", 2001, "Fiction");
    Library::Book book2("Book Two", "Author B", 2002, "Non-Fiction");
    Library::Book book3("Book Three", "Author A", 2003, "Fiction");

    manager.addBook(book1);
    manager.addBook(book2);
    manager.addBook(book3);

    std::cout << "Books by Author A:" << std::endl;
    FIND_BOOK_BY_AUTHOR(manager, "Author A");

    std::cout << "\nAll books sorted by title:" << std::endl;
    manager.sortBooksByTitle();
    for (const auto& book : manager.getAllBooks()) {
        std::cout << book.getTitle() << " by " << book.getAuthor() << std::endl;
    }

    return 0;
}
