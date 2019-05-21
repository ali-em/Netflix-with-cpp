#include "money_handler.h"
#include "../database/database.h"
using namespace std;

MoneyHandler::MoneyHandler(Database* db, Login* _login) : DB(db), login(_login) {}

void MoneyHandler::handleMoneyRequest(Parameters params) {
    User* user = login->getCurrentUser();
    if (Tools::checkParam(params, 1, "amount"))
        user->chargeMoney(stoi(params["amount"]));
    else {
        if (!user->isPublisher())
            throw PermissionDenied();
        else
            static_cast<Publisher*>(user)->getMoney();
    }
    View::success();
}
void MoneyHandler::handleBuyRequest(Parameters& params) {
    validateBuy(params);
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    Purchase* purchase = new Purchase(film->getPrice(), film->getRate());
    DB->addPurchase(purchase);
    User* user = login->getCurrentUser();
    user->addToPurchased(film);
    NotificationHandler::sendBuyNotif(user, DB->getPublisherByFilmId(stoi(params["film_id"])), film);
    View::success();
}

void MoneyHandler::validateBuy(Parameters& params) {
    if (!Tools::checkParam(params, 1, "film_id"))
        throw BadRequest();
    Film* film = DB->getFilmById(stoi(params["film_id"]));
    User* user = login->getCurrentUser();
    if (film->getPrice() > user->getMoney())
        throw BadRequest();
    if (user->isPurchased(film))
        throw BadRequest();
}