/* What I am going to create is going to be a library catalog of books 
   where you can add or remove a book.
   I will use Classes and Objects, Pointers and Dynamic Memory Management, 
   Structs and Enumerations, and Functions (including function overloading).
   I will implment this project by creating a class for books and a class 
   for the catalog as a total that the books fall into though vecotrs. Then
   for the adding and removing of a book I will create a function for each 
   one that does that. As well as I will create a enum for the book genres.
*/

#include <iostream>
#include <string>
#include <vector>

// Enum for book genres
enum Genre { Fiction, NonFiction, SciFi, Fantasy, Biography };

// Struct for book information
struct BookInfo {
    std::string title;
    std::string author;
    int year;
    Genre genre;
};

// Book class
class Book {
private:
    BookInfo info;

public:
    Book(std::string title, std::string author, int year, Genre genre) {
        info.title = title;
        info.author = author;
        info.year = year;
        info.genre = genre;
    }

    ~Book() {
        // Destructor 
    }

    void printDetails() const {
        std::cout << "Title: " << info.title << "\n"
                  << "Author: " << info.author << "\n"
                  << "Year: " << info.year << "\n"
                  << "Genre: " << getGenreName(info.genre) << "\n"
                  << "----------------------------\n";
    }

    static std::string getGenreName(Genre g) {
        switch (g) {
            case Fiction: return "Fiction";
            case NonFiction: return "Non-Fiction";
            case SciFi: return "Sci-Fi";
            case Fantasy: return "Fantasy";
            case Biography: return "Biography";
            default: return "Unknown";
        }
    }
};

// LibraryCatalog class
class LibraryCatalog {
private:
    std::vector<Book*> books;

public:
    ~LibraryCatalog() {
        for (Book* b : books) {
            delete b;
        }
    }

    // Overload #1: Add a book via pointer
    void addBook(Book* book) {
        books.push_back(book);
    }

    // Overload #2: Add a book by passing details directly
    void addBook(const std::string& title, const std::string& author, int year, Genre genre) {
        books.push_back(new Book(title, author, year, genre));
    }

    void removeBook(int index) {
        if (index >= 0 && index < books.size()) {
            delete books[index];
            books.erase(books.begin() + index);
        }
    }

    void printCatalog() const {
        std::cout << "\nLibrary Catalog:\n----------------------------\n";
        for (const Book* b : books) {
            b->printDetails();
        }
    }
};

// Main function demonstrating functionality
int main() {
    LibraryCatalog catalog;

    // Using pointer version
    catalog.addBook(new Book("Frankenstein", "Mary Shelley", 1818, NonFiction));

    // Using overloaded version with parameters
    catalog.addBook("1984", "George Orwell", 1949, Fiction);
    catalog.addBook("Poppy War", "R. F. Kuang", 2018, Fantasy);

    catalog.printCatalog();

    // Remove one book
    catalog.removeBook(1);
    std::cout << "After removing one book:\n";
    catalog.printCatalog();

    return 0;
}
