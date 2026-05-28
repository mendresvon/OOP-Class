#ifndef BOOK_H
#define BOOK_H

#include "MediaItem.h"

class Book : public MediaItem {
private:
    std::string author;
    std::string isbn;

public:
    Book(const std::string& id, const std::string& title, bool isBorrowed,
         const std::string& author, const std::string& isbn);

    std::string getAuthor() const;
    std::string getIsbn() const;

    // Polymorphic overrides
    double getFee(int days) const override;
    std::string serialize() const override;
};

#endif
