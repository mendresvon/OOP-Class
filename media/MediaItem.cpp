#include "MediaItem.h"

MediaItem::MediaItem(const std::string& id, const std::string& title, bool isBorrowed)
    : id(id), title(title), isBorrowed(isBorrowed) {}

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
