#ifndef MEDIA_ITEM_H
#define MEDIA_ITEM_H

#include <string>

class MediaItem {
protected:
    std::string id;
    std::string title;
    bool isBorrowed;
    std::string status;

public:
    MediaItem(const std::string& id, const std::string& title, bool isBorrowed = false, const std::string& status = "ACTIVE");
    virtual ~MediaItem() = default;

    std::string getId() const;
    std::string getTitle() const;
    bool isBorrowedItem() const;
    void setBorrowed(bool borrowed);
    std::string getStatus() const;
    void setStatus(const std::string& newStatus);


    // Pure virtual functions for polymorphism
    virtual double getFee(int days) const = 0;
    virtual std::string serialize() const = 0;
};

#endif
