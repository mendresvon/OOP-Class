#include "MediaItem.h"

MediaItem::MediaItem(const std::string& id, const std::string& title, bool isBorrowed, const std::string& status)
    : id(id), title(title), isBorrowed(isBorrowed), status(status) {}

std::string MediaItem::getId() const {
    return id;
}

std::string MediaItem::getTitle() const {
    return title;
}

bool MediaItem::isBorrowedItem() const {
    return isBorrowed;
}

void MediaItem::setBorrowed(bool borrowed) {
    isBorrowed = borrowed;
}

std::string MediaItem::getStatus() const {
    return status;
}

void MediaItem::setStatus(const std::string& newStatus) {
    status = newStatus;
}

