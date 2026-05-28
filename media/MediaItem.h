#ifndef MEDIA_ITEM_H
#define MEDIA_ITEM_H

#include <string>

class MediaItem {
protected:
    std::string id;
    std::string title;
    bool isBorrowed;

public:
    MediaItem(const std::string& id, const std::string& title, bool isBorrowed = false);
    virtual ~MediaItem() = default;

    std::string getId() const;
    std::string getTitle() const;
    bool isBorrowedItem() const;
    void setBorrowed(bool borrowed);

    // Pure virtual functions for polymorphism
    virtual double getFee(int days) const = 0;
    virtual std::string serialize() const = 0;
};

#endif
