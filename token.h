#ifndef TOKEN_H
#define TOKEN_H
#include <map>

enum tokenID {
    error=0,
    identifier=1001,
    integer=1002,
    opordel=1003,
    keyword=1004,
    eoftk=1005
};

struct token {
    enum tokenID id;
    std::string instance;
    std::pair<int, int> pos;
    std::pair<int, int> size;
    std::map<int, std::string> idmap = {
        { error,      "\nSCANNER ERROR:\n"},
        { identifier, "idTK:" },
        { integer,    "numTK:" },
        { opordel,    "opTK:" },
        { keyword,    "kwTK:" },
        { eoftk,      "eofTK" }
    };
    token(enum tokenID tid, std::string tinst, std::pair<int, int> tpos,
        std::pair<int, int> tsize) : id(tid), instance(tinst), pos(tpos), size(tsize) {}
    std::string toString() {
        std::string out("");
        std::string posString("");
        std::string sizeString("");
        posString += std::to_string(std::get<0>(pos)) + ":" +\
                     std::to_string(std::get<1>(pos));
        sizeString += std::to_string(std::get<0>(size)) + ":" +\
                      std::to_string(std::get<1>(size));
        if (id == error) {
            out += idmap[id] + posString + ": " + instance;
        } else {
            out += idmap[id];
            out.append(16 - out.length(), ' ');
            out += instance;
            out.append(28 - out.length(), ' ');
            out += "Line " + posString;
        }

        return out;
    }
};

#endif
