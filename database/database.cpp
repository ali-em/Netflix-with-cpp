#include "database.h"
using namespace std;

User* Database::findUserByUsername(string username) {
    for (auto user : users)
        if (user->getUsername() == username)
            return user;
    return NULL;
}
void Database::addUser(User* user) {
    users.push_back(user);
    user->setId(userId++);
}
User* Database::findUserByUsernameAndPassword(std::string username, std::string password) {
    for (auto user : users)
        if (user->getUsername() == username && user->getPassword() == password)
            return user;
    return NULL;
}
void Database::addFilm(Film* newFilm) {
    films.push_back(newFilm);
    newFilm->setId(filmId++);
}

Film* Database::getFilmById(int id) {
    for (auto f : films)
        if (f->getId() == id)
            return f;
    return NULL;
}
vector<Film*> Database::getFilms() {
    return films;
}
User* Database::findUserById(int userId) {
    for (auto user : users)
        if (user->getInfo().userId == userId)
            return user;
    return NULL;
}
void Database::addPurchase(Purchase* p) {
    purchases.push_back(p);
}
std::string Database::getRecommendedFilms(User* user) {
    vector<Film*> copyFilms = films;
    stringstream result;
    int i = 1;
    sort(copyFilms.begin(), copyFilms.end());
    for (auto f : copyFilms) {
        if (!user->isPurchased(f)) {
            result << i++ << ". " << f->getShortInfo() << endl;
        }
        if (i == 5)
            return result.str();
    }
    return result.str();
}
