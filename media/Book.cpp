#include "Book.h"
#include <sstream>

Book::Book(const std::string& id, const std::string& title, bool isBorrowed,
           const std::string& author, const std::string& isbn, const std::string& status)
    : MediaItem(id, title, isBorrowed, status), author(author), isbn(isbn) {}

std::string Book::getAuthor() const {
    return author;
}

std::string Book::getIsbn() const {
    return isbn;
}

double Book::getFee(int days) const {
    if (days <= 7) {
        return days * 10.0;
    } else {
        return 70.0 + (days - 7) * 20.0;
    }
}

std::string Book::serialize() const {
    std::stringstream ss;
    ss << "BOOK," << id << "," << title << "," << (isBorrowed ? "1" : "0") << "," << author << "," << isbn << "," << status;
    return ss.str();
}

