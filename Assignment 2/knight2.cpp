#include "knight2.h"


//*********     KIEM TRA MAXHP CUA KY SI DE PHAN LOAI     *************
bool checkPaladin(int hp) {
    if (hp < 2)  return false;
    for (int i = 2; i <= hp / 2; i++) {
        if (hp % i == 0) return false;
    }
    return true;
}

bool checkDragon(int hp) {
    if (hp < 100 || hp > 999) return false;
    else {
        int c = hp % 10;
        int b = (hp / 10) % 10;
        int a = ((hp / 10) / 10) % 10;
        if ((pow(a,2) + pow(b,2)) == pow(c, 2) || (pow(a, 2) + pow(c, 2)) == pow(b, 2) || (pow(c, 2) + pow(b, 2)) == pow(a, 2)) {
            return true;
        }
        else return false;
    }
}
///********************************************///

















/* * * BEGIN implementation of class BaseOpponent * * */

bool  PhoenixDownI::canUse(BaseKnight* knight) {
    if (knight->get_hp() <= 0) return true;
    else return false;
}

void PhoenixDownI::use(BaseKnight* knight) {
    knight->set_hp(knight->get_maxhp());
}

bool PhoenixDownII::canUse(BaseKnight* knight) {
    if (knight->get_hp() < (knight->get_maxhp() / 4)) return true;
    else return false;
}

void PhoenixDownII::use(BaseKnight* knight) {
    knight->set_hp(knight->get_maxhp());
}

bool PhoenixDownIII::canUse(BaseKnight* knight) {
    if (knight->get_hp() < (knight->get_maxhp() / 3)) return true;
    else return false;
}

void PhoenixDownIII::use(BaseKnight* knight) {
    if (knight->get_hp() <= 0) {
        knight->set_hp(knight->get_maxhp() / 3);
    }
    else {
        knight->set_hp(knight->get_hp() + knight->get_maxhp() / 4);
    }

}

bool PhoenixDownIV::canUse(BaseKnight* knight) {
    if (knight->get_hp() < (knight->get_maxhp() / 2)) return true;
    else return false;
}

void PhoenixDownIV::use(BaseKnight* knight) {
    if (knight->get_hp() <= 0) {
        knight->set_hp(knight->get_maxhp() / 2);
    }
    else {
        knight->set_hp(knight->get_hp() + knight->get_maxhp() / 5);
    }

}

bool Anti::canUse(BaseKnight* knight) {
    if (knight->get_antidote() == 1) return true;
    else return false;
}

void Anti::use(BaseKnight* knight) {    
    knight->set_antidote(0);
}


/* * * END implementation of class BaseOpponent * * */


















/* * * BEGIN implementation of class BaseOpponent * * */

BaseOpponent::BaseOpponent(int id, int baseDamge, int gil, int a) {
    this->baseDamge = baseDamge;
    this->gil = gil;
    this->id = id;
    this->level0 = (a + this->id) % 10 + 1;
}

int BaseOpponent::get_level0() {
    return this->level0;
}

int BaseOpponent::get_gil() {
    return this->gil;
}

int BaseOpponent::get_baseDamge() {
    return this->baseDamge;
}
/* * * END implementation of class BaseOpponent * * */


/* * * BEGIN implementation of class MadBear * * */











/* * * BEGIN implementation of class BaseBag * * */


/* * * BEGIN implement the contruction of node  * * */

node* makeNode(ItemType a) { 
    node* newNode = new node;
    newNode->name = a;
    newNode->next = NULL;
    return newNode;

}


void pushFront(ItemType a, node** head) { 
    node* Newnode = makeNode(a);
    Newnode->next = *head;
    *head = Newnode;

}

int dem(node* head) {
    int dem = 0;
    node* temp = head;
    while (temp != NULL)
    {
        dem++;
        temp = temp->next;
    }
    return dem;
}

void check(node* head) {
    node* temp = head;
    while (temp != NULL) {
        cout << temp->name << " ";
        temp = temp->next;
    }
}

//ItemType find(node* head) {
//    node* temp = head;
//    while (temp != NULL) {
//        if (temp->name == PhoenixI) {
//            return PhoenixI;
//        }
//        else if (temp->name == PhoenixII) {
//            return PhoenixII;
//        }
//        else if (temp->name == PhoenixIII) {
//            return PhoenixIII;
//        }
//        else if (temp->name == PhoenixIV) {
//            return PhoenixIV;
//        }
//        else if (temp->name == Antidote) {
//            return Antidote;
//        }
//        else {
//            temp = temp->next;
//        }     
//    }
//    return NONE;
//}

void popFront(node** head) { /////////////////////////////////
    if (*head == NULL) return;
    node* a = *head; // giai phong bo nho cho node bi xoa
    *head = (*head)->next;
    //free(temp)
    delete a;
}


int vitri(node* head, ItemType a) { 
    node* temp = head;
    int x = 0;
    while (temp != NULL) {
        if (temp->name == a) {
            return x;
        }
        else {
            temp = temp->next;
            x++;
        }
    }
    return x = -1;
}



void erase(node** head, ItemType k) {  ////////////////////////
  
    int a = vitri(*head, k);

    if (a == -1) return;

    if (a == 0) popFront(head);
    else {
       
        node* temp = *head;
       
        for (int i = 1; i <= a - 2; i++) {
            temp = temp->next;
        }
        //temp : k - 1
        node* kth = temp->next; // node thu k
        //cho k-1 => ket noi voi node thu k + 1
        temp->next = kth->next;
        delete kth; // free(kth)
    }
}











/* * * END implement the contruction of node  * * */






BaseBag::BaseBag(BaseKnight* baseKnight, int phoniexdownI, int antidote) {
    node* head=nullptr;
    
    if (baseKnight->get_Type() == DRAGON) {
        if (phoniexdownI > 0) {
            for (int i = 0; i < phoniexdownI; i++) {
                pushFront(PhoenixI, &head);

            }

        }
        
        set_head(head);

    }
    else {
        if (phoniexdownI > 0) {
            for (int i = 0; i < phoniexdownI; i++) {
                pushFront(PhoenixI, &head);

            }

        }
        if (antidote > 0) {
            for (int i = 0; i < antidote; i++) {
                pushFront(Antidote, &head);
            }
        }
        set_head(head);


    }
    
}


void BaseBag::set_head(node* a) {
    this->head = a;
}

node* BaseBag::get_head() {
    return this->head;
}

string BaseBag::checkList() const {
    node* temp = this->head;
    string s = "";
    
    while (temp != NULL) {
        if (temp->name == Antidote) {
            s += "Antidote,";
            temp = temp->next;
        }
        else if (temp->name == PhoenixI) {
            s += "PhoenixI,";
            temp = temp->next;
        }
        else if (temp->name == PhoenixII) {
            s += "PhoenixII,";
            temp = temp->next;
        }
        else if (temp->name == PhoenixIII) {
            s += "PhoenixIII,";
            temp = temp->next;
        }
        else if (temp->name == PhoenixIV) {
            s += "PhoenixIV,";
            temp = temp->next;
        }

    };
    string a = s.substr(0, s.size() - 1);

    a += "]";
    return a;
    

   
}

bool BaseBag::insertFirst(BaseItem* item) { 
    
    return true;

}

BaseItem* BaseBag::get(ItemType itemType) {

    return nullptr;
}

string BaseBag::toString() const {
    string s("");
    string a = this->checkList();

    s += "Bag[count=" + to_string(dem(this->head)) + ";"
        + a;
    return s;
}


/* * * END implementation of class BaseBag * * */


















/* * * BEGIN implementation of class BaseKnight * * */

BaseKnight* BaseKnight::create(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote) {
    if (checkPaladin(maxhp) == true) {
        return new PaladinKnight(id, maxhp, level, phoenixdownI, gil, antidote);
    }
    else if (maxhp == 888) {
        return new LancelotKnight(id, maxhp, level, phoenixdownI, gil, antidote);
    }
    else if (checkDragon(maxhp) == true) {
        return new DragonKnight(id, maxhp, level, phoenixdownI, gil, antidote);
    }
    else {
        return new NormalKnight(id, maxhp, level, phoenixdownI, gil, antidote);
    }
}

string BaseKnight::toString() const {
    string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
    // inefficient version, students can change these code
    //      but the format output must be the same
    string s("");
    s += "[Knight:id:" + to_string(id) 
        + ",hp:" + to_string(hp) 
        + ",maxhp:" + to_string(maxhp)
        + ",level:" + to_string(level)
        + ",gil:" + to_string(gil)
        + "," + bag->toString()
        + ",knight_type:" + typeString[knightType]
        + "]";
    return s;
}

bool BaseKnight::fight(BaseOpponent* opponent) {
    if (this->get_level() >= opponent->get_level0()) return true;
    else return false;
}

KnightType BaseKnight::get_Type() {
    return this->knightType;
}

BaseBag* BaseKnight::get_bag() {
    return this->bag;
}


int BaseKnight::get_hp() {
    return this->hp;
}

void BaseKnight::set_hp(int a) {
    this->hp = a;
}

int BaseKnight::get_maxhp() {
    return this->maxhp;
}


int BaseKnight::get_gil() {
    return this->gil;
}

void BaseKnight::set_gil(int a) {
    this->gil = a;
}

int BaseKnight::get_antidote() {
    return this->get_Antidote;
}

void BaseKnight::set_antidote(int a) {
    this->get_Antidote = a;
}

int BaseKnight::get_level() {
    return this->level;
}

void BaseKnight::set_level(int a) {
    this->level = a;
}

int BaseKnight::get_get_Antidote() {
    return this->get_Antidote;
}

void BaseKnight::set_get_Antidote(int a) {
    this->get_Antidote = a;
}

/* * * END implementation of class BaseKnight * * */



/* * * BEGIN implementation of class NormalKnight * * */
NormalKnight::NormalKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote) {
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->knightType = NORMAL;
    this->bag = new BaseBag(this, phoenixdownI, antidote);
    // ham fight dc dinh nghia trong baseKnight nen mac nhien co san trong derived class 
}




/* * * END implementation of class NormalKnight * * */

// Nho tach tung truong hop ra vi moi hiep si se co 1 cach danh khac nhau


/* * * BEGIN implementation of class dragonKnight * * */
DragonKnight::DragonKnight (int id, int maxhp, int level, int phoenixdownI, int gil, int antidote) {
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->knightType = DRAGON;
    this->get_Antidote = antidote;
    this->bag = new BaseBag(this, phoenixdownI, antidote);
    // ham fight dc dinh nghia trong baseKnight nen mac nhien co san trong derived class 
}


/* * * END implementation of class dragonKnight * * */


/* * * BEGIN implementation of class lancelotKnight * * */
LancelotKnight::LancelotKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote) {
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->knightType = LANCELOT;
    this->bag = new BaseBag(this, phoenixdownI, antidote);
    // ham fight dc dinh nghia trong baseKnight nen mac nhien co san trong derived class 
}

/* * * END implementation of class lancelotKnight * * */


/* * * BEGIN implementation of class paladinKnight * * */
PaladinKnight::PaladinKnight(int id, int maxhp, int level, int phoenixdownI, int gil, int antidote) {
    this->id = id;
    this->hp = maxhp;
    this->maxhp = maxhp;
    this->level = level;
    this->gil = gil;
    this->knightType = PALADIN;
    this->bag = new BaseBag(this, phoenixdownI, antidote);
    // ham fight dc dinh nghia trong baseKnight nen mac nhien co san trong derived class 
}

/* * * END implementation of class paladinKnight * * */














/* * * BEGIN implementation of class ArmyKnights * * */

ArmyKnights::ArmyKnights(const string& file_armyknights) {
    ifstream stats(file_armyknights);
    if (!stats) {
        cout << "Cannot open file " << file_armyknights << "\n";
        exit(1);
    }
    stats >> this->soluong;


    for (int i = 0; i < soluong; i++) {
        int hp, lv, phoenixdownI, gil, antidote;
        stats >> hp >> lv >> phoenixdownI >> gil >> antidote;
        this->knights[i] = BaseKnight::create(i + 1, hp, lv, phoenixdownI, gil, antidote);
    }

}


bool ArmyKnights::fight(BaseOpponent* opponent) {
    return true;
}

bool ArmyKnights::adventure(Events* event) {
    return true;
}

int ArmyKnights::count() const {
    return this->soluong;
}

int ArmyKnights::get_soluong() {
    return this->soluong;
}

void ArmyKnights::set_soluong(int a) {
    this->soluong = a;
}

BaseKnight* ArmyKnights::lastKnight() const { //////////////////////////////////////////
    for (int i = this->count() - 1; i >= 0; i--) {
        if (this->knights[i]->death == 1) {
            if (i == 0) return NULL;
            else continue;
        }
        else return this->knights[i];
    }
    
}

bool ArmyKnights::hasExcaliburSword() const {
    if (this->Armybag[guom] == 1) return true;
    else return false;
}

bool ArmyKnights::hasGuinevereHair() const {
    if (this->Armybag[toc] == 1) return true;
    else return false;
}

bool ArmyKnights::hasLancelotSpear() const {
    if (this->Armybag[giao] == 1) return true;
    else return false;
}

bool ArmyKnights::hasPaladinShield() const {
    if (this->Armybag[khien] == 1) return true;
    else return false;
}

BaseKnight* ArmyKnights::Last_knight_fight() {
    return this->knights[Last_fight];
}

int ArmyKnights::get_Last_fight() {
    return this->Last_fight;
}

void ArmyKnights::set_Last_fight(int a) {
    this->Last_fight = a;
}

int number(ArmyKnights &a) {
    for (int i = a.count() - 1; i >= 0; i--) {
        if (a.get_knights()[i]->death == 1) {
            a.set_soluong(a.get_soluong() - 1);
        }
    }
    return a.get_soluong();
}


void ArmyKnights::printInfo() const {
    int a = this->count();
    for (int i = this->count() - 1; i >= 0; i--) {
        if (this->knights[i]->death == 1) {
            a -= 1;
        }
        else continue;
    }
    cout << "No. knights: " << a;
    if (a > 0) {
        BaseKnight * lknight = lastKnight(); // last knight
        cout << ";" << lknight->toString();
    }
    cout << ";PaladinShield:" << this->hasPaladinShield()
        << ";LancelotSpear:" << this->hasLancelotSpear()
        << ";GuinevereHair:" << this->hasGuinevereHair()
        << ";ExcaliburSword:" << this->hasExcaliburSword()
        << endl
        << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}

BaseKnight** ArmyKnights::get_knights() {
    return this->knights;
}

int ArmyKnights::get_Last_delete() {
    return this->Last_delete;
}

void ArmyKnights::set_Last_delete(int a) {
    this->Last_delete = a;
}

void ArmyKnights::setArmybag(BaoVat a) {
    this->Armybag[a] = 1;
}

int ArmyKnights::get_Last_receive_index() {
    return this->Last_receive_index;
}

void ArmyKnights::set_Last_receive_index(int a) {
    this->Last_receive_index = a;
}

BaseKnight* ArmyKnights::Last_knight_receive() {
    return this->knights[Last_receive_index];
}

int ArmyKnights::get_Last_gil() {
    return this->Last_gil;
}

void ArmyKnights::set_Last_gil(int a) {
    this->Last_gil = a;
}

BaseKnight* ArmyKnights::Last_knight_gil() {
    return this->knights[Last_gil];
}


BaseKnight* ArmyKnights::check(int a) {
    return this->knights[a];
}

int ArmyKnights::get_antidote_du() {
    return this->antidote_du;
}

void ArmyKnights::set_antidote_du(int a) {
    this->antidote_du = a;
}

int ArmyKnights::get_omega_weapon() {
    return this->omega_weapon;
}

void ArmyKnights::set_omega_weapon(int a) {
    this->omega_weapon = a;
}

/* * * END implementation of class ArmyKnights * * */



















/* * * BEGIN implementation of class Events * * */

Events::Events(const string& file_events) {

    ifstream event(file_events);
    if (!event) {
        cout << "Cannot open file " << file_events << "\n";
        exit(1);
    }
    event >> this->e;
    for (int i = 0; i < e; i++) {
        event >> this->events[i];
    }
}


int Events::count() const {
    return this->e;
}

int Events::get(int i) const {
    return this->events[i];
}

int* Events::get_events() {
    return this->events;
}

/* * * END implementation of class Events * * */















// ham su dung vat pham 

void useBag(node ** head, BaseKnight*& a,PhoenixDownI p1, PhoenixDownII p2, PhoenixDownIII p3, PhoenixDownIV p4, Anti an) {
    ItemType item = NONE;
    while (*head != NULL) {
        if ((*head)->name == PhoenixI) {
            if (p1.canUse(a) == true) {
                p1.use(a);
                item = PhoenixI;
                  //check lai xem xoa xong co bi doi bag ko (co doi nen phai set lai head)
                
                break;
            }
            else {
                *head = (*head)->next;
                continue;
            }
        }
        else if ((*head)->name == PhoenixII) {
            if (p2.canUse(a) == true) {
                p2.use(a);
                item = PhoenixII;
                
                break;
            }
            else {
                *head = (*head)->next;
                continue;
            }
        }
        else if ((*head)->name == PhoenixIII) {
            if (p3.canUse(a) == true) {
                p3.use(a);
                item = PhoenixIII;
                
                break;
            }
            else {
                *head = (*head)->next;
                continue;
            }
        }
        else if ((*head)->name == PhoenixIV) {
            if (p4.canUse(a) == true) {
                p4.use(a);
                item = PhoenixIV;
                
                break;
            }
            else {
                *head = (*head)->next;
                continue;
            }
        }
        else if ((*head)->name == Antidote) {    ///////////////////////////// antidote chinh sau
            if (an.canUse(a) == true) {
                an.use(a);
                item = Antidote;

                break;
            }
            else {
                *head = (*head)->next;
                continue;
            }
            
        }
    }
    node* temp1 = (a->get_bag()->get_head()); // temp nay de lay node head de xoa vat pham (neu co su dung)
    if (item != NONE) {
        erase(&temp1, item);
        a->get_bag()->set_head(temp1);
    }


}












// tao ham thuc thi cac su kien

//////// dang thieu dieu kien neu chet het

/// kiem tra lai phan printresult khi co nguoi chet 

void su_kien1_5(ArmyKnights& a, BaseOpponent b, PhoenixDownI p1, PhoenixDownII p2, PhoenixDownIII p3, PhoenixDownIV p4, Anti an) {
    
        if (a.Last_knight_fight()->get_level() >= b.get_level0() || a.Last_knight_fight()->get_Type() == LANCELOT || a.Last_knight_fight()->get_Type() == PALADIN) {

            a.Last_knight_gil()->set_gil(a.Last_knight_gil()->get_gil() + b.get_gil());       
            while (a.Last_knight_gil()->get_gil() > 999) {
                int x = a.Last_knight_gil()->get_gil() - 999;
                a.Last_knight_gil()->set_gil(999);

                a.set_Last_gil(a.get_Last_gil() - 1);
                if (a.get_Last_gil() < 0) {
                    break;
                }
                else {
                    a.Last_knight_gil()->set_gil(a.Last_knight_gil()->get_gil() + x);
                }
            }

            

        }
        else {
            a.Last_knight_fight()->set_hp((a.Last_knight_fight()->get_hp()) - b.get_baseDamge() * (b.get_level0() - a.Last_knight_fight()->get_level()));

            node* temp = (a.Last_knight_fight()->get_bag()->get_head());  // temp nay de kiem tra xem co vat pham nao dung duoc khong
            ItemType item = NONE;
            BaseKnight* hientai = a.Last_knight_fight();
            useBag(&temp, hientai, p1, p2, p3, p4, an);

            if (a.Last_knight_fight()->get_hp() <= 0) {
                if (a.Last_knight_fight()->get_gil() >= 100) {
                    a.Last_knight_fight()->set_gil(a.Last_knight_fight()->get_gil() - 100);
                    a.Last_knight_fight()->set_hp(a.Last_knight_fight()->get_maxhp() / 2);
                    a.set_Last_gil(a.get_Last_fight() - 1);
                    a.set_Last_fight(a.get_Last_fight() - 1);

                }
                else {
                     /// giu count lai vi ko thay doi dc
                    a.set_Last_gil(a.get_Last_fight() - 1); // cap nhat lai phan nhan gil                  
                    a.Last_knight_fight()->death=1;
                    a.set_Last_fight(a.get_Last_fight() - 1);
                    
                }
            }
            else {
                a.set_Last_gil(a.get_Last_fight() - 1);
                a.set_Last_fight(a.get_Last_fight() - 1);

            }
        }
    
    a.printInfo();
    if (a.count() <= 0) {
        //a.printResult(false);
    }
    

}

void su_kien6(ArmyKnights& a, BaseOpponent b, PhoenixDownI p1, PhoenixDownII p2, PhoenixDownIII p3, PhoenixDownIV p4, Anti an) {
     
        if (a.Last_knight_fight()->get_level() >= b.get_level0()) {

            a.Last_knight_fight()->set_level(a.Last_knight_fight()->get_level() + 1);
            if (a.Last_knight_fight()->get_level() > 10) a.Last_knight_fight()->set_level(10);
            
        }

        else {
            if (a.Last_knight_fight()->get_Type() == DRAGON) {
                a.set_Last_gil(a.get_Last_fight() - 1);
                a.set_Last_fight(a.get_Last_fight() - 1);
                
            }
            else {
                a.Last_knight_fight()->set_antidote(1);
                node* temp = (a.Last_knight_fight()->get_bag()->get_head());  // temp nay de kiem tra xem co vat pham nao dung duoc khong
                ItemType item = NONE;
                BaseKnight* hientai = a.Last_knight_fight();
                useBag(&temp, hientai, p1, p2, p3, p4, an);

                if (a.Last_knight_fight()->get_antidote() == 1) {
                    if (dem(a.Last_knight_fight()->get_bag()->get_head()) >= 3) {
                        for (int i = 0; i < 3; i++) {
                            node* xoa = a.Last_knight_fight()->get_bag()->get_head();
                            popFront(&xoa);
                            a.Last_knight_fight()->get_bag()->set_head(xoa);
                        }

                    }
                    else {
                        int x = dem(a.Last_knight_fight()->get_bag()->get_head());
                        for (int i = 0; i < x; i++) {
                            node* xoa = a.Last_knight_fight()->get_bag()->get_head();
                            popFront(&xoa);
                            a.Last_knight_fight()->get_bag()->set_head(xoa);
                        }
                    }
                    a.Last_knight_fight()->set_hp(a.Last_knight_fight()->get_hp() - 10);
                    node* temp1 = (a.Last_knight_fight()->get_bag()->get_head());  // temp nay de kiem tra xem co vat pham nao dung duoc khong
                    ItemType item = NONE;
                    BaseKnight* hientai = a.Last_knight_fight();
                    useBag(&temp1, hientai, p1, p2, p3, p4, an);

                    if (a.Last_knight_fight()->get_hp() <= 0) {
                        if (a.Last_knight_fight()->get_gil() >= 100) {
                            a.Last_knight_fight()->set_gil(a.Last_knight_fight()->get_gil() - 100);
                            a.Last_knight_fight()->set_hp(a.Last_knight_fight()->get_maxhp() / 2);
                            a.set_Last_gil(a.get_Last_fight() - 1);
                            a.set_Last_fight(a.get_Last_fight() - 1);

                        }
                        else {
                            /// giu count lai vi ko thay doi dc (ko thay doi so luong)
                            a.set_Last_gil(a.get_Last_fight() - 1); // cap nhat lai phan nhan gil
                            a.Last_knight_fight()->death = 1;
                            a.set_Last_fight(a.get_Last_fight() - 1);
                        }
                    }
                    else {
                        a.set_Last_gil(a.get_Last_fight() - 1);
                        a.set_Last_fight(a.get_Last_fight() - 1);

                    }
                }
                else {
                    a.set_Last_gil(a.get_Last_fight() - 1);
                    a.set_Last_fight(a.get_Last_fight() - 1);

                }
            }
           
        }
    

    a.printInfo();
    if (a.count() <= 0) {
        //a.printResult(false);
    }
    
}

void su_kien7(ArmyKnights& a, BaseOpponent b, PhoenixDownI p1, PhoenixDownII p2, PhoenixDownIII p3, PhoenixDownIV p4, Anti an) {
    // thua chi bi giam gil chu ko mat hp

     
        if (a.Last_knight_fight()->get_level() >= b.get_level0()) {

            a.Last_knight_fight()->set_gil(a.Last_knight_fight()->get_gil() * 2);
            while (a.Last_knight_gil()->get_gil() > 999) {
                int x = a.Last_knight_gil()->get_gil() - 999;
                a.Last_knight_gil()->set_gil(999);

                a.set_Last_gil(a.get_Last_gil() - 1);
                if (a.get_Last_gil() < 0) {
                    break;
                }
                else {
                    a.Last_knight_gil()->set_gil(a.Last_knight_gil()->get_gil() + x);
                }
            }
            
        }

        else {
            a.Last_knight_fight()->set_gil(a.Last_knight_fight()->get_gil() / 2);
            a.set_Last_gil(a.get_Last_fight() - 1);
            a.set_Last_fight(a.get_Last_fight() - 1);
        }
    
    a.printInfo();
}

void su_kien10(ArmyKnights& a, PhoenixDownI p1, PhoenixDownII p2, PhoenixDownIII p3, PhoenixDownIV p4, Anti an) {
    if (a.get_omega_weapon() == 0) {
         
            if (a.Last_knight_fight()->get_level() == 10 && a.Last_knight_fight()->get_hp() == a.Last_knight_fight()->get_maxhp()) {

                a.Last_knight_fight()->set_level(10);
                a.Last_knight_fight()->set_gil(999);
                a.set_omega_weapon(1);
                
            }
            else if (a.Last_knight_fight()->get_Type() == DRAGON) {
                a.Last_knight_fight()->set_level(10);
                a.Last_knight_fight()->set_gil(999);
                a.set_omega_weapon(1);
                
            }

            else {
                a.Last_knight_fight()->set_hp(0);
                node* temp = (a.Last_knight_fight()->get_bag()->get_head());  // temp nay de kiem tra xem co vat pham nao dung duoc khong
                ItemType item = NONE;
                BaseKnight* hientai = a.Last_knight_fight();
                useBag(&temp, hientai, p1, p2, p3, p4, an);

                if (a.Last_knight_fight()->get_hp() <= 0) {
                    if (a.Last_knight_fight()->get_gil() >= 100) {
                        a.Last_knight_fight()->set_gil(a.Last_knight_fight()->get_gil() - 100);
                        a.Last_knight_fight()->set_hp(a.Last_knight_fight()->get_maxhp() / 2);
                        a.set_Last_gil(a.get_Last_fight() - 1);
                        a.set_Last_fight(a.get_Last_fight() - 1);

                    }
                    else {                       
                        a.set_Last_gil(a.get_Last_fight() - 1); // cap nhat lai phan nhan gil
                        a.Last_knight_fight()->death = 1;
                        a.set_Last_fight(a.get_Last_fight() - 1);
                    }
                }
                else {
                    a.set_Last_gil(a.get_Last_fight() - 1);
                    a.set_Last_fight(a.get_Last_fight() - 1);

                }
            }
        
        a.printInfo();
        if (a.get_Last_fight() < 0) {
            //a.printResult(false);
        }
    }
    else {
        a.printInfo();      
    }
   
    
}

void su_kien11(ArmyKnights& a, PhoenixDownI p1, PhoenixDownII p2, PhoenixDownIII p3, PhoenixDownIV p4, Anti an) {
    if (a.hasPaladinShield() == false) {
         
            if (a.Last_knight_fight()->get_level() == 10) {
                a.setArmybag(khien);
                
            }
            else if (a.Last_knight_fight()->get_Type() == PALADIN && a.Last_knight_fight()->get_level() >= 8) {
                a.setArmybag(khien);
                
            }

            else {
                a.Last_knight_fight()->set_hp(0);
                node* temp = (a.Last_knight_fight()->get_bag()->get_head());  // temp nay de kiem tra xem co vat pham nao dung duoc khong
                ItemType item = NONE;
                BaseKnight* hientai = a.Last_knight_fight();
                useBag(&temp, hientai, p1, p2, p3, p4, an);

                if (a.Last_knight_fight()->get_hp() <= 0) {
                    if (a.Last_knight_fight()->get_gil() >= 100) {
                        a.Last_knight_fight()->set_gil(a.Last_knight_fight()->get_gil() - 100);
                        a.Last_knight_fight()->set_hp(a.Last_knight_fight()->get_maxhp() / 2);
                        a.set_Last_gil(a.get_Last_fight() - 1);
                        a.set_Last_fight(a.get_Last_fight() - 1);

                    }
                    else {
                        a.set_Last_gil(a.get_Last_fight() - 1); // cap nhat lai phan nhan gil
                        a.Last_knight_fight()->death = 1;
                        a.set_Last_fight(a.get_Last_fight() - 1);
                    }
                }
                else {
                    a.set_Last_gil(a.get_Last_fight() - 1);
                    a.set_Last_fight(a.get_Last_fight() - 1);

                }
            }
        
        a.printInfo();
        if (a.count() < 0) {
            
            //a.printResult(false);
        }
        
    }
    else {
        a.printInfo();
    }
}

void su_kien99(ArmyKnights& a, PhoenixDownI p1, PhoenixDownII p2, PhoenixDownIII p3, PhoenixDownIV p4, Anti an) {
    if (a.hasExcaliburSword()==true) {
        a.printInfo();
        //a.printResult(true);

    }
    else {
        if (a.hasGuinevereHair() == true && a.hasLancelotSpear() == true && a.hasPaladinShield() == true) {
            long long Hp_of_Ultimecia = 5000;
            int x = a.count();
            for (int i = 0; i < x; i++) {
                if (a.Last_knight_fight()->get_Type() == LANCELOT) {
                    Hp_of_Ultimecia = Hp_of_Ultimecia - static_cast<long long>((a.Last_knight_fight()->get_level() * a.Last_knight_fight()->get_hp() * 0.05));
                }
                else if (a.Last_knight_fight()->get_Type() == PALADIN) {
                    Hp_of_Ultimecia = Hp_of_Ultimecia - static_cast<long long>((a.Last_knight_fight()->get_level() * a.Last_knight_fight()->get_hp() * 0.06));
                }
                else if (a.Last_knight_fight()->get_Type() == DRAGON) {
                    Hp_of_Ultimecia = Hp_of_Ultimecia - static_cast<long long>((a.Last_knight_fight()->get_level() * a.Last_knight_fight()->get_hp() * 0.075));
                }
                else { // hiep si ban tron ko co tac dung :0 (bo else van duoc nhung de cho nho :)))
                   
                }
                if (Hp_of_Ultimecia > 0) {                   
                    a.set_Last_gil(a.get_Last_fight() - 1);
                    a.Last_knight_fight()->death = 1;
                    a.set_Last_fight(a.get_Last_fight() - 1);
                }
                else {
                    a.printInfo();
                    // a.printResult(true);
                    break;
                }
            }
            if (Hp_of_Ultimecia>0) {
                a.printInfo();
                // a.printResult(false);
            }
        }
        else {
            for (int i = 0; i < a.count(); i++) {
                a.get_knights()[i]->death = 1;
            }
            a.printInfo();
            //a.printResult(false);
        }
    }
}
// ket thuc phan tao ham thua thi cac su kien














// con paldin dang doi hoi dap cua thay :))




















/* * * BEGIN implementation of class KnightAdventure * * */


void KnightAdventure::loadArmyKnights(const string& file_name_knights) {

    ArmyKnights Kysi;
    Kysi = ArmyKnights(file_name_knights);
    this->armyKnights = Kysi;
}

void KnightAdventure::loadEvents(const string& file_name_events) {

    Events suKien;
    suKien = Events(file_name_events);
    this->events = suKien;
}

void KnightAdventure::run() {

    PhoenixDownI p1;
    PhoenixDownII p2;
    PhoenixDownIII p3;
    PhoenixDownIV p4;
    Anti an;

    // duyet antidote vi hiep si rong ko nhan antidote
    this->armyKnights.set_Last_receive_index(this->armyKnights.count() - 1);
    this->armyKnights.set_Last_gil(this->armyKnights.count() - 1);
    this->armyKnights.set_Last_fight(this->armyKnights.count() - 1);
    int z1 = 0, f = 0; // za va z dung de dem so hiep si chet
    for (int i = 0; i < (this->events).count(); i++) {
        

        if ((this->events).get(i) == 95) {
            
            if ((this->armyKnights).hasPaladinShield() == true) {
                this->armyKnights.printInfo();

            }
            else {
                (this->armyKnights).setArmybag(khien);
                this->armyKnights.printInfo();
            }
        }

        else if ((this->events).get(i) == 96) {
            if ((this->armyKnights).hasLancelotSpear() == true) {
                this->armyKnights.printInfo();

            }
            else {
                (this->armyKnights).setArmybag(giao);
                this->armyKnights.printInfo();
            }
        }

        else if ((this->events).get(i) == 97) {
            if ((this->armyKnights).hasGuinevereHair() == true) {
                this->armyKnights.printInfo();

            }
            else {
                (this->armyKnights).setArmybag(toc);
                this->armyKnights.printInfo();
            }
        }

        else if ((this->events).get(i) == 98) {
            if ((this->armyKnights).hasExcaliburSword() == true) {
                this->armyKnights.printInfo();
            }
            else {
                if (this->armyKnights.hasGuinevereHair() == true && this->armyKnights.hasLancelotSpear() == true && this->armyKnights.hasPaladinShield() == true) {
                    (this->armyKnights).setArmybag(guom);
                    this->armyKnights.printInfo();
                }
                else this->armyKnights.printInfo();
            }
        }

        else if ((this->events).get(i) == 112) {

            node* temp=nullptr;
            while (this->armyKnights.get_Last_receive_index() >= 0) {


                temp = this->armyKnights.Last_knight_receive()->get_bag()->get_head();
                int a = dem(temp);


                if (this->armyKnights.Last_knight_receive()->get_Type() == NORMAL) {
                    if (a < 19) {
                        pushFront(PhoenixII, &temp);
                        (this->armyKnights).Last_knight_receive()->get_bag()->set_head(temp);
                        this->armyKnights.printInfo();                        
                        break;
                    }
                    else {
                        this->armyKnights.set_Last_receive_index(this->armyKnights.get_Last_receive_index() - 1);
                        continue;
                    }
                }

                else if (this->armyKnights.Last_knight_receive()->get_Type() == DRAGON) {
                    if (a < 14) {
                        pushFront(PhoenixII, &temp);
                        (this->armyKnights).Last_knight_receive()->get_bag()->set_head(temp);
                        this->armyKnights.printInfo();
                        break;
                    }
                    else {
                        this->armyKnights.set_Last_receive_index(this->armyKnights.get_Last_receive_index() - 1);
                        continue;
                    }
                }

                else if (this->armyKnights.Last_knight_receive()->get_Type() == LANCELOT) {
                    if (a < 16) {
                        pushFront(PhoenixII, &temp);
                        (this->armyKnights).Last_knight_receive()->get_bag()->set_head(temp);
                        this->armyKnights.printInfo();
                        break;
                    }
                    else {
                        this->armyKnights.set_Last_receive_index(this->armyKnights.get_Last_receive_index() - 1);
                        continue;
                    }
                }

                else if (this->armyKnights.Last_knight_receive()->get_Type() == PALADIN) {
                    pushFront(PhoenixII, &temp);
                    (this->armyKnights).Last_knight_receive()->get_bag()->set_head(temp);
                    this->armyKnights.printInfo();
                    break;
                }

            }


        }

        else if ((this->events).get(i) == 113) {

            node* temp;
            while (this->armyKnights.get_Last_receive_index() >= 0) {


                temp = this->armyKnights.Last_knight_receive()->get_bag()->get_head();
                int a = dem(temp);


                if (this->armyKnights.Last_knight_receive()->get_Type() == NORMAL) {
                    if (a < 19) {
                        pushFront(PhoenixIII, &temp);
                        (this->armyKnights).Last_knight_receive()->get_bag()->set_head(temp);
                        this->armyKnights.printInfo();                        
                        break;
                    }
                    else {
                        this->armyKnights.set_Last_receive_index(this->armyKnights.get_Last_receive_index() - 1);
                        continue;
                    }
                }

                else if (this->armyKnights.Last_knight_receive()->get_Type() == DRAGON) {
                    if (a < 14) {
                        pushFront(PhoenixIII, &temp);
                        (this->armyKnights).Last_knight_receive()->get_bag()->set_head(temp);
                        this->armyKnights.printInfo();
                        break;
                    }
                    else {
                        this->armyKnights.set_Last_receive_index(this->armyKnights.get_Last_receive_index() - 1);
                        continue;
                    }
                }

                else if (this->armyKnights.Last_knight_receive()->get_Type() == LANCELOT) {
                    if (a < 16) {
                        pushFront(PhoenixIII, &temp);
                        (this->armyKnights).Last_knight_receive()->get_bag()->set_head(temp);
                        this->armyKnights.printInfo();
                        break;
                    }
                    else {
                        this->armyKnights.set_Last_receive_index(this->armyKnights.get_Last_receive_index() - 1);
                        continue;
                    }
                }

                else if (this->armyKnights.Last_knight_receive()->get_Type() == PALADIN) {
                    pushFront(PhoenixIII, &temp);
                    (this->armyKnights).Last_knight_receive()->get_bag()->set_head(temp);
                    this->armyKnights.printInfo();
                    break;
                }

            }


        }
        
        else if ((this->events).get(i) == 114) {

            node* temp;
            while (this->armyKnights.get_Last_receive_index() >= 0) {


                temp = this->armyKnights.Last_knight_receive()->get_bag()->get_head(); // nay chinh la node head de xet de tinh toan, khong phai node dau tien trong bag
                int a = dem(temp);


                if (this->armyKnights.Last_knight_receive()->get_Type() == NORMAL) {
                    if (a < 19) {
                        pushFront(PhoenixIV, &temp);
                        (this->armyKnights).Last_knight_receive()->get_bag()->set_head(temp);
                        this->armyKnights.printInfo();
                        break;
                    }
                    else {
                        this->armyKnights.set_Last_receive_index(this->armyKnights.get_Last_receive_index() - 1);
                        continue;
                    }
                }

                else if (this->armyKnights.Last_knight_receive()->get_Type() == DRAGON) {
                    if (a < 14) {
                        pushFront(PhoenixIV, &temp);
                        (this->armyKnights).Last_knight_receive()->get_bag()->set_head(temp);
                        this->armyKnights.printInfo();
                        break;
                    }
                    else {
                        this->armyKnights.set_Last_receive_index(this->armyKnights.get_Last_receive_index() - 1);
                        continue;
                    }
                }

                else if (this->armyKnights.Last_knight_receive()->get_Type() == LANCELOT) {
                    if (a < 16) {
                        pushFront(PhoenixIV, &temp);
                        (this->armyKnights).Last_knight_receive()->get_bag()->set_head(temp);
                        this->armyKnights.printInfo();
                        break;
                    }
                    else {
                        this->armyKnights.set_Last_receive_index(this->armyKnights.get_Last_receive_index() - 1);
                        continue;
                    }
                }

                else if (this->armyKnights.Last_knight_receive()->get_Type() == PALADIN) {
                    pushFront(PhoenixIV, &temp);
                    (this->armyKnights).Last_knight_receive()->get_bag()->set_head(temp);
                    this->armyKnights.printInfo();
                    break;
                }

            }


        }

        else if ((this->events).get(i) == 9) {
            this->armyKnights.lastKnight()->set_hp(this->armyKnights.lastKnight()->get_maxhp());
            this->armyKnights.printInfo();
        }

        else if ((this->events).get(i) == 8) {
            if (this->armyKnights.lastKnight()->get_gil() < 50) {
                if (this->armyKnights.lastKnight()->get_Type() == PALADIN) {
                    if (this->armyKnights.lastKnight()->get_hp() < (this->armyKnights.lastKnight()->get_maxhp()) / 3) {
                        this->armyKnights.lastKnight()->set_hp(this->armyKnights.lastKnight()->get_hp() + (this->armyKnights.lastKnight()->get_maxhp()) / 5);
                    }
                }
            
            }

            else {
                if (this->armyKnights.lastKnight()->get_hp() < (this->armyKnights.lastKnight()->get_maxhp()) / 3) {
                    this->armyKnights.lastKnight()->set_gil((this->armyKnights.lastKnight()->get_gil()) - 50);
                    this->armyKnights.lastKnight()->set_hp(this->armyKnights.lastKnight()->get_hp() + (this->armyKnights.lastKnight()->get_maxhp()) / 5);
                }
          
            }

            this->armyKnights.printInfo();
            
        }

        //else if ((this->events).get(i) == 1) {
        //    MadBear a{i};
        //    while (this->armyKnights.get_Last_fight() >= 0) {
        //        if (this->armyKnights.Last_knight_fight()->get_level() >= a.get_level0()) {
        //            this->armyKnights.Last_knight_gil()->set_gil(this->armyKnights.Last_knight_gil()->get_gil() + 100);
        //            while (this->armyKnights.Last_knight_gil()->get_gil() > 999) {
        //                int x = this->armyKnights.Last_knight_gil()->get_gil() - 999;
        //                this->armyKnights.Last_knight_gil()->set_gil(999);
        //                this->armyKnights.set_Last_gil(this->armyKnights.get_Last_gil() - 1);
        //                if (this->armyKnights.get_Last_gil() < 0) {
        //                    break;
        //                }
        //                else {
        //                    this->armyKnights.Last_knight_gil()->set_gil(this->armyKnights.Last_knight_gil()->get_gil() + x);
        //                }                     
        //            }
        //            
        //            break;
        //            
        //        }
        //        else {
        //            this->armyKnights.Last_knight_fight()->set_hp((this->armyKnights.Last_knight_fight()->get_hp()) - 10 * (a.get_level0() - this->armyKnights.Last_knight_fight()->get_level()));
        //            node* temp = (this->armyKnights.Last_knight_fight()->get_bag()->get_head());  // temp nay de kiem tra xem co vat pham nao dung duoc khong
        //            ItemType item=NONE;
        //            BaseKnight* hientai = this->armyKnights.Last_knight_fight();
        //            useBag(&temp, hientai, p1, p2, p3, p4);
        //            //while (temp != NULL) {
        //            //    if (temp->name == PhoenixI) {
        //            //        if (p1.canUse(this->armyKnights.Last_knight_fight()) == true) {
        //            //            p1.use(this->armyKnights.Last_knight_fight());
        //            //            item = PhoenixI;
        //            //              //check lai xem xoa xong co bi doi bag ko (co doi nen phai set lai head) (khoan earse voi o day)
        //            //            
        //            //            break;
        //            //        }
        //            //        else {
        //            //            temp = temp->next;
        //            //            continue;
        //            //        }
        //            //    }
        //            //    else if (temp->name == PhoenixII) {
        //            //        if (p2.canUse(this->armyKnights.Last_knight_fight()) == true) {
        //            //            p2.use(this->armyKnights.Last_knight_fight());
        //            //            
        //            //            item = PhoenixII;
        //            //            break;
        //            //        }
        //            //        else {
        //            //            temp = temp->next;
        //            //            continue;
        //            //        }
        //            //    }
        //            //    else if (temp->name == PhoenixIII) {
        //            //        if (p3.canUse(this->armyKnights.Last_knight_fight()) == true) {
        //            //            p3.use(this->armyKnights.Last_knight_fight());
        //            //            
        //            //            item = PhoenixIII;
        //            //            break;
        //            //        }
        //            //        else {
        //            //            temp = temp->next;
        //            //            continue;
        //            //        }
        //            //    }
        //            //    else if (temp->name == PhoenixIV) {
        //            //        if (p4.canUse(this->armyKnights.Last_knight_fight()) == true) {
        //            //            p4.use(this->armyKnights.Last_knight_fight());
        //            //            
        //            //            item = PhoenixIV;
        //            //            break;
        //            //        }
        //            //        else {
        //            //            temp = temp->next;
        //            //            continue;
        //            //        }
        //            //    }
        //            //    else if (temp->name == Antidote) {    ///////////////////////////// antidote chinh sau                       
        //            //            temp = temp->next;
        //            //            continue;                            
        //            //    }
        //            //}
        //            node* temp1= (this->armyKnights.Last_knight_fight()->get_bag()->get_head()); // temp nay de lay node head de xoa vat pham (neu co su dung)
        //            if (item != NONE) {
        //                erase(&temp1, item);
        //                this->armyKnights.Last_knight_fight()->get_bag()->set_head(temp1);
        //            }
        //           
        //            if (this->armyKnights.Last_knight_fight()->get_hp() <= 0) {
        //                if (this->armyKnights.Last_knight_fight()->get_gil() >= 100) {
        //                    this->armyKnights.Last_knight_fight()->set_gil(this->armyKnights.Last_knight_fight()->get_gil() - 100);
        //                    this->armyKnights.Last_knight_fight()->set_hp(this->armyKnights.Last_knight_fight()->get_maxhp() / 2);
        //                    this->armyKnights.set_Last_gil(this->armyKnights.get_Last_fight() - 1);
        //                    this->armyKnights.set_Last_fight(this->armyKnights.get_Last_fight() - 1);
        //                   
        //                }
        //                else {
        //                    this->armyKnights.set_soluong(this->armyKnights.count() - 1);
        //                    this->armyKnights.set_Last_gil(this->armyKnights.get_Last_fight() - 1); // cap nhat lai phan nhan gil
        //                    this->armyKnights.set_Last_fight(this->armyKnights.get_Last_fight() - 1);                      
        //                }
        //            }
        //            else {
        //                this->armyKnights.set_Last_gil(this->armyKnights.get_Last_fight() - 1);
        //                this->armyKnights.set_Last_fight(this->armyKnights.get_Last_fight() - 1);                       
        //            }
        //        }
        //    }
        //    this->armyKnights.printInfo();
        //    cout << this->armyKnights.check(0)->get_gil()<< endl;
        //   /* if (this->armyKnights.count() <= 0) {
        //        cout << "LOSE";
        //        break;
        //    } phan nay de in win lose cua ca doan  */
        //    
        //}

        else if ((this->events).get(i) == 1) {
            MadBear a{ i };
            su_kien1_5(this->armyKnights, a, p1, p2, p3, p4, an);
        }

        else if ((this->events).get(i) == 2) {
            Bandit a{ i };
            su_kien1_5(this->armyKnights, a, p1, p2, p3, p4, an);
        }

        else if ((this->events).get(i) == 3) {
            LordLupin a{ i };
            su_kien1_5(this->armyKnights, a, p1, p2, p3, p4, an);
        }

        else if ((this->events).get(i) == 4) {
            Elf a{ i };
            su_kien1_5(this->armyKnights, a, p1, p2, p3, p4, an);
        }

        else if ((this->events).get(i) == 5) {
            Troll a{ i };
            su_kien1_5(this->armyKnights, a, p1, p2, p3, p4, an);
        }

        else if ((this->events).get(i) == 6) {
            Tornbery a{ i };
            su_kien6(this->armyKnights, a, p1, p2, p3, p4, an);
        }

        else if ((this->events).get(i) == 7) {
            QueenCards a{ i };
            su_kien7(this->armyKnights, a, p1, p2, p3, p4, an);
        }

        else if ((this->events).get(i) == 10) {
            su_kien10(this->armyKnights, p1, p2, p3, p4, an);
        }

        else if ((this->events).get(i) == 11) {
            su_kien11(this->armyKnights, p1, p2, p3, p4, an);
        }
        
        else if ((this->events).get(i) == 99) {
            su_kien99(this->armyKnights, p1, p2, p3, p4, an);
        }
        else {

        }

        int z = 0;
        for (int i = this->armyKnights.count() - 1; i >= 0; i--) {
            if (this->armyKnights.get_knights()[i]->death == 1) {

                z += 1;
                if (z == this->armyKnights.count()) {
                    f += 1;
                    z1 = z; ///////////////////////// (tuc qua :)))
                }
            }
            else {
                this->armyKnights.set_Last_receive_index(i);
                this->armyKnights.set_Last_gil(i);
                this->armyKnights.set_Last_fight(i);
                break;
            }

        }
        if (f == 1) break;

        
    }
    /// co ban la xong su kien quai vat 1-5 r :0

    if (z1 == this->armyKnights.count()) this->armyKnights.printResult(false);
    else this->armyKnights.printResult(true);

    this->armyKnights.set_Last_delete(this->armyKnights.count());

    for (int i = 0; i < (this->armyKnights.count()); i++) {
        delete this->armyKnights.get_knights()[i]->get_bag();
        delete this->armyKnights.get_knights()[i];
    }


    delete[] this->events.get_events();
    delete[] this->armyKnights.get_knights();

}

/* * * END implementation of class KnightAdventure * * */