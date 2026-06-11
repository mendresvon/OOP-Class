#ifndef RENTAL_RECORD_H
#define RENTAL_RECORD_H

#include <string>

struct RentalRecord {
    std::string recordId;   // Unique record identifier (e.g. REC_10001)
    std::string username;   // Account username
    std::string itemId;     // MediaItem ID
    std::string itemTitle;  // MediaItem Title
    std::string borrowDate; // Borrow date YYYY-MM-DD
    std::string returnDate; // Return date YYYY-MM-DD or "Pending"
    double rentalFee;       // Rental fee computed upon return
    std::string status;     // "BORROWED", "RETURNED", or "OVERDUE"
};

#endif
