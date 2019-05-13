#ifndef COMMENT_HANDLER_H
#define COMMENT_HANDLER_H
#include <string>
#include "../models/modelHeaders.h"
#include "../views/view.h"
#include "login.h"
#include "tools.h"
class Database;
class CommentHandler {
   public:
    CommentHandler(Database*, View*, Login*);
    void sendComment(Parameters&);
    void sendReply(Parameters&);

   private:
    Database* DB;
    View* Res;
    Login* login;
    void validateSendingComment(Parameters& params);
};

#endif