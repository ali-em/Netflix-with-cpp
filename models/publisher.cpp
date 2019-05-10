#include "publisher.h"
using namespace std;
Publisher::Publisher(std::map<std::string, std::string> params) : User(params) {
    publisher = true;
}
void Publisher::addFilm(Film* film) {
    publishedFilms.push_back(film);
}
bool Publisher::hasFilm(int id) {
    for (auto f : publishedFilms)
        if (f->getId() == id && !f->isDeleted())
            return true;
    return false;
}
vector<Film*> Publisher::getFilms() {
    return publishedFilms;
}
