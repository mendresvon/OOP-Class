#include "Magazine.h"
#include <sstream>

Magazine::Magazine(const std::string& id, const std::string& title, bool isBorrowed,
                   int issueNum, int month, const std::string& status)
    : MediaItem(id, title, isBorrowed, status), issueNum(issueNum), month(month) {}

int Magazine::getIssueNum() const {
    return issueNum;
}

int Magazine::getMonth() const {
    return month;
}

double Magazine::getFee(int days) const {
    if (days <= 3) {
        return days * 5.0;
    } else {
        return 15.0 + (days - 3) * 10.0;
    }
}

std::string Magazine::serialize() const {
    std::stringstream ss;
    ss << "MAGAZINE," << id << "," << title << "," << (isBorrowed ? "1" : "0") << "," << issueNum << "," << month << "," << status;
    return ss.str();
}

