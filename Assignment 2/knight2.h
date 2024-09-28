#ifndef __KNIGHT2_H__
#define __KNIGHT2_H__

#include "main.h"

// #define DEBUG

enum ItemType { Antidote = 0, PhoenixI, PhoenixII, PhoenixIII, PhoenixIV, NONE };

enum KnightType { PALADIN = 0, LANCELOT, DRAGON, NORMAL , VOID};

enum BaoVat { khien = 0, giao, toc, guom };

class BaseItem;

class Events;

class BaseKnight;

struct node {
    ItemType name;
    node* next;
};


class BaseBag {
private:
    node* head = nullptr;
    int list_item[5] = { 0,0,0,0,0 };
public:

    BaseBag(BaseKnight* baseKnight, int phoniexdownI, int antidote);

    void set_head(node* a);

    node* get_head();

    string checkList() const;

    virtual bool insertFirst(BaseItem * item);
    virtual BaseItem * get(ItemType itemType);
    virtual string toString() const;
};













class BaseOpponent {
private:
    int id=0;
    int baseDamge=0;
    int level0=0;
    int gil=0;
public:
    BaseOpponent(int id, int baseDamge, int gil, int a);
    int get_level0();
    int get_gil();
    int get_baseDamge();
    
};

class MadBear :public BaseOpponent {
public:
    MadBear(int a) :BaseOpponent(1, 10, 100, a) {
    }
};

class Bandit :public BaseOpponent {
public:
    Bandit(int a) :BaseOpponent(2, 15, 150, a) {

    }
};

class LordLupin :public BaseOpponent {
public:
    LordLupin(int a) :BaseOpponent(3, 45, 450, a) {

    }
};

class Elf :public BaseOpponent {
public:
    Elf(int a) :BaseOpponent(4, 75, 750, a) {

    }
};

class Troll :public BaseOpponent {
public:
    Troll(int a) :BaseOpponent(5, 95, 800, a) {

    }
};

class Tornbery : public BaseOpponent { // special
public:
    Tornbery(int a) : BaseOpponent(6, 0, 0, a) {

    }
};

class QueenCards: public BaseOpponent { // special
public:
    QueenCards(int a) : BaseOpponent(7, 0, 0, a) {

    }
};














class BaseKnight {
protected:
    int id = 0;
    int hp = 0;
    int maxhp = 0;
    int level = 0;
    int gil = 0;
    BaseBag* bag = nullptr; 
    KnightType knightType = VOID;
    int get_Antidote = 0;
    // lam them phan antidte vi hiep si rong ko nhan antidote
 

public:
    int death = 0;
    static BaseKnight * create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI);
    string toString() const;
    bool fight(BaseOpponent* opponent);


    KnightType get_Type();

    BaseBag* get_bag();

    int get_hp();
    void set_hp(int a);

    int get_maxhp();

    int get_gil();
    void set_gil(int a);

    int get_antidote();
    void set_antidote(int a);

    int get_level();
    void set_level(int a);
    
    int get_get_Antidote();
    void set_get_Antidote(int a);


};


class NormalKnight : public BaseKnight {
public:
    NormalKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote);
    bool fight(BaseOpponent* opponent);  // chua dung vi da so sanh level trong ham sukien :))

};

class DragonKnight : public BaseKnight {
public:
    DragonKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote);
    bool fight(BaseOpponent* opponent);
    
};

class LancelotKnight : public BaseKnight {
public:
    LancelotKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote);
    bool fight(BaseOpponent* opponent);
};

class PaladinKnight : public BaseKnight {
public:
    PaladinKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote);
    bool fight(BaseOpponent* opponent);
};















class ArmyKnights {
private:
    int soluong = 0;
    BaseKnight** knights = new BaseKnight * [1000];
    int Armybag[4] = { 0,0,0,0 };
    int Last_receive_index = 0; // tinh tu 0, dung de nhan do
    int Last_gil = 0;  //dung de nhan gil   
    int Last_fight = 0; // dang bi du
    int Last_delete = 0; // dung de xoa
    int antidote_du = 0;  // de chuyen antidote cho hiep si khac
    int omega_weapon = 0;

public:
    ArmyKnights() = default;
    ArmyKnights(const string& file_armyknights);

    bool fight(BaseOpponent* opponent);

    bool adventure(Events* events);
    int count() const;
    BaseKnight* lastKnight() const;

    bool hasPaladinShield() const;
    bool hasLancelotSpear() const;
    bool hasGuinevereHair() const;
    bool hasExcaliburSword() const;

    void printInfo() const;
    void printResult(bool win) const;

    BaseKnight** get_knights();

    int get_Last_delete();
    void set_Last_delete(int a);

    void setArmybag(BaoVat a);

    int get_Last_receive_index();
    void set_Last_receive_index(int a);
    BaseKnight* Last_knight_receive();

    int get_soluong();
    void set_soluong(int a);

    BaseKnight* Last_knight_fight();
    int get_Last_fight();
    void set_Last_fight(int a);

    int get_Last_gil();
    void set_Last_gil(int a);
    BaseKnight* Last_knight_gil();

    int get_antidote_du();
    void set_antidote_du(int a);

    int get_omega_weapon();
    void set_omega_weapon(int a);

    BaseKnight* check(int a); ////////// check, sau nay nop bai nho xoa

};

















class BaseItem {
public:
    virtual bool canUse ( BaseKnight * knight ) = 0;
    virtual void use ( BaseKnight * knight ) = 0;
};

class PhoenixDownI : public BaseItem {
public:
    bool canUse(BaseKnight* knight) override;
    void use(BaseKnight* knight) override;
};

class PhoenixDownII : public BaseItem {
public:
    bool canUse(BaseKnight* knight) override;
    void use(BaseKnight* knight) override;
};

class PhoenixDownIII : public BaseItem {
public:
    bool canUse(BaseKnight* knight) override;
    void use(BaseKnight* knight) override;
};

class PhoenixDownIV : public BaseItem {
public:
    bool canUse(BaseKnight* knight) override;
    void use(BaseKnight* knight) override;
};

class Anti : public BaseItem {  // ham ke thua de ghi de ham ao use va canUse
public:
    bool canUse(BaseKnight* knight) override;
    void use(BaseKnight* knight) override;
};


















class Events {
private:
    int e = 0;
    int* events = new int[1000];

public:
    Events() = default;
    Events(const string& file_events);


    int count() const;
    int get(int i) const;

    int* get_events();


};






















class KnightAdventure {
private:
    ArmyKnights armyKnights;
    Events events;

public:
    KnightAdventure() = default;
    

    void loadArmyKnights(const string &);
    void loadEvents(const string &);
    void run();
};

#endif // __KNIGHT2_H__