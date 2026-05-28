#include "Dvd.h"
#include <sstream>

Dvd::Dvd(const std::string& id, const std::string& title, bool isBorrowed,
         const std::string& director, int duration, const std::string& status)
    : MediaItem(id, title, isBorrowed, status), director(director), duration(duration) {}

std::string Dvd::getDirector() const {
    return director;
}

int Dvd::getDuration() const {
    return duration;
}

double Dvd::getFee(int days) const {
    return days * 20.0;
}

std::string Dvd::serialize() const {
    std::stringstream ss;
    ss << "DVD," << id << "," << title << "," << (isBorrowed ? "1" : "0") << "," << director << "," << duration << "," << status;
    return ss.str();
}

