#include "knight.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}


//Tách chuỗi trong file thành các số nguyên (chuyển từ string sang int)
void number_of_event(string a, int x[])
{

    int i = 1;
    stringstream stream(a);
    while (1) {
        int n;
        stream >> n;
        x[i] = n;
        i += 1;
        if (!stream)
            break;
    }
}

// bảng damge của từng con quái 
double Basedamge(int a)
{
    double x[5] = { 1, 1.5, 4.5, 7.5, 9.5 };
    return x[a - 1];
}

// Hiệu ứng nấm MushMario 
int MushMario(int& HP, int level, int phoenixdown)
{
    int n1;
    n1 = (((level + phoenixdown) % 5) + 1) * 3;
    int s1 = 99;
    for (int i = 1; i < n1; i++)
    {
        s1 = s1 - i * 2;
    }
    return HP + (s1 % 100);

}

// Hiệu ứng nấm Fibonacci MushFibo
int fibonacci(int HP)
{
    int NewHP=0;
    int fb1 = 1, fb2 = 1;
    while (fb1+fb2 < HP)
    {
        NewHP = fb1 + fb2;
        fb2 = fb1;
        fb1 = NewHP;
    }
    return NewHP;
}

//kiểm tra số nguyên tố
bool checkNT(int MaxHP)
{
    if (MaxHP < 2) return false;
    int sq = sqrt(MaxHP);
    for (int i = 2; i <= sq; i++)
    {
        if (MaxHP % i == 0)
        {
            return false;
        }
    }
    return true;
}

//check vật phẩm
int check(string mondo)
{
    int a = 0;
    string x = "merlin";
    string y = "Merlin";
    if (mondo.find(x) != std::string::npos || mondo.find(y) != std::string::npos) return 2;
    else 
    {
        if (mondo.find('M') != -1 || mondo.find('m') != -1) ++a;
        if (mondo.find('E') != -1 || mondo.find('e') != -1) ++a;
        if (mondo.find('R') != -1 || mondo.find('r') != -1) ++a;
        if (mondo.find('L') != -1 || mondo.find('l') != -1) ++a;
        if (mondo.find('I') != -1 || mondo.find('i') != -1) ++a;
        if (mondo.find('N') != -1 || mondo.find('n') != -1) ++a;
    }
    if (a == 6) return 1;
    
    else return 0;


}

//check người chơi
int Player(int MaxHP)
{
    if (MaxHP == 999)
    {
        return 1;
    }
    else if (checkNT(MaxHP) == true)
    {
        return 2;
    }
    else return 3;

}

struct Info {
    int& hp;
    int& level;
    int& remedy;
    int& maidenkiss;
    int& phoenixdown;
    int& rescue;


    int turn_number = 0;
    int ordinal = 1;

    string event;
    string file_name;
    string name[3];


    int file_open = 0;
    int shaman = 0;
    int siren = 0;
    int asclepius = 0;
    int merlin = 0;

    Info() = default;
    Info(int& hp, int& level, int& remedy, int& maidenkiss, int& phoenixdown, int& rescue) : hp{ hp }, level{ level }, remedy{ remedy }, maidenkiss{ maidenkiss }, phoenixdown{ phoenixdown }, rescue{rescue} {}


};

void processEvent1_5(Info& info, int type, int MaxHP, int MaxLV, int player, int count )
{
    int i = info.ordinal;
    int b = i % 10;
    int level0 = i > 6 ? (b > 5 ? b : 5) : b;

    if (player == 1||player==2)
    {
        if (info.shaman > 0 && info.shaman - 1 == 0)
        {
            info.hp *= 5;
            if (info.hp >= MaxHP) info.hp = MaxHP;
            info.shaman = 0;

        }

        if (info.siren > 0 && info.siren - 1 == 0)
        {
            info.level = MaxLV;
            info.siren = 0;
        }
        if (info.level + 1 <= 10) info.level += 1;
        else info.level = 10;
        if (info.ordinal == count)
        {
            if (info.hp > 0)
            {
                info.rescue = 1;
            }

        }

       
    }

    else
    {
        if (info.shaman > 0)        // check hiệu ứng xấu  
        {
            info.shaman--;

        }
        if (info.siren > 0)
        {
            info.siren--;

        }

        if (info.level > level0)
        {
            if (info.level < 10)
            {
                info.level++;
                if (info.ordinal == count)
                {
                    if (info.hp > 0)
                    {
                        info.rescue = 1;
                    }

                }
                return;
            }
            else
            {
                info.level = 10;
                if (info.ordinal == count)
                {
                    if (info.hp > 0)
                    {
                        info.rescue = 1;
                    }

                }
                return;
            }
        }

        else if (info.level == level0)
        {
            
        }

        else
        {
            int damge = Basedamge(type) * level0 * 10;
            info.hp -= damge;
            if (info.hp <= 0 && info.phoenixdown <= 0)
            {
                info.rescue = 0;   
            }
            else if (info.hp <= 0 && info.phoenixdown > 0)
            {
                info.phoenixdown -= 1;
                info.hp =MaxHP;

            }
        }
    }
    if (info.shaman > 0 && info.shaman - 1 == 0 && info.hp > 0)
    {
        info.hp *= 5;
        if (info.hp >= MaxHP) info.hp = MaxHP;
        info.shaman = 0;

    }

    if (info.siren > 0 && info.siren - 1 == 0 && info.hp > 0)
    {
        info.level = MaxLV;
        info.siren = 0;
    }

    if (info.ordinal == count)
    {
        if (info.hp > 0)
        {
            info.rescue = 1;
        }
      
    }

}

void process_Event6(ifstream& stats, Info& info, int MaxHP, int MaxLV, int player, int count)  // shaman
{
    int i = info.ordinal; 
    int b = i % 10;
    int level0 = i > 6 ? (b > 5 ? b : 5) : b;


    if (info.shaman > 0||info.siren>0)        // check hiệu ứng xấu  
    {
        if (info.shaman > 0)
        {
            info.shaman--;
        }
        if (info.siren > 0)
        {
            info.shaman--;
        }

        if (info.ordinal == count)
        {
            if (info.hp > 0)
            {
                info.rescue = 1;
            }

        }
        return;

    }
   
    else if (info.shaman == 0)
    {

        if (player == 1 || player == 2)
        {
            if (info.shaman > 0 && info.shaman - 1 == 0)
            {
                info.hp *= 5;
                if (info.hp >= MaxHP) info.hp = MaxHP;
                info.shaman = 0;

            }

            if (info.siren > 0 && info.siren - 1 == 0)
            {
                info.level = MaxLV;
                info.siren = 0;
            }
            if (info.level + 2 <= 10) info.level += 2;
            else info.level = 10;

        }

        else
        {

            if (info.level > level0)
            {
                if (info.level + 2 <= 10) info.level += 2;
                else info.level = 10;
            }

            else if (info.level == level0)
            {

            }
            else
            {
                int modulo = info.hp % 5;
                if (info.hp <= 5)
                {
                    info.hp = 1;
                }
                else 
                {                   
                    info.hp /= 5;
                    info.shaman += 4;
                }
               
                if (info.remedy >= 1)
                {
                    info.remedy -= 1;
                    if (info.hp < 5)
                    {
                        info.hp = modulo;
                        info.shaman -= 4;
                    }
                    else 
                    {
                        info.hp = info.hp * 5 + modulo;
                        info.shaman -= 4;
                    }
                }
                
            }
        }
    }

    if (info.shaman > 0 && info.shaman - 1 == 0)
    {
        info.hp *= 5;
        if (info.hp >= MaxHP) info.hp = MaxHP;
        info.shaman = 0;

    }

    if (info.siren > 0 && info.siren - 1 == 0)
    {
        info.level = MaxLV;
        info.siren = 0;
    }

    if (info.ordinal == count)
    {
        if (info.hp > 0)
        {
            info.rescue = 1;
        }

    }

}      

void process_Event7(ifstream& stats, Info& info, int MaxLV, int MaxHP, int player, int count)    //siren
{
    int i = info.ordinal;
    int b = i % 10;
    int level0 = i > 6 ? (b > 5 ? b : 5) : b;

    if (info.shaman > 0 || info.siren > 0)        // check hiệu ứng xấu  
    {
        if (info.shaman > 0)
        {
            info.shaman--;
        }
        if (info.siren > 0)
        {
            info.shaman--;
        }
        if (info.ordinal == count)
        {
            if (info.hp > 0)
            {
                info.rescue = 1;
            }

        }

        return;

    }
    
    else if (info.siren == 0)
    {
        if (player == 1 || player == 2)
        {
            if (info.shaman > 0 && info.shaman - 1 == 0)
            {
                info.hp *= 5;
                if (info.hp >= MaxHP) info.hp = MaxHP;
                info.shaman = 0;

            }

            if (info.siren > 0 && info.siren - 1 == 0)
            {
                info.level = MaxLV;
                info.siren = 0;
            }
            if (info.level + 2 <= 10) info.level += 2;
            else info.level = 10;

        }

        else
        {


            if (info.level > level0)
            {
                if (info.level + 2 <= 10) info.level += 2;
                else info.level = 10;
            }

            else if (info.level == level0)
            {

            }
            else
            {
                info.level = 1;
                info.siren += 3;

                if (info.maidenkiss >= 1)
                {
                    info.maidenkiss -= 1;
                    info.level = MaxLV;
                    info.siren -= 3;
                }
                
            }
        }
    }
    if (info.shaman > 0 && info.shaman - 1 == 0)
    {
        info.hp *= 5;
        if (info.hp >= MaxHP) info.hp = MaxHP;
        info.shaman = 0;

    }

    if (info.siren > 0 && info.siren - 1 == 0)
    {
        info.level = MaxLV;
        info.siren = 0;
    }

    if (info.ordinal == count)
    {
        if (info.hp > 0)
        {
            info.rescue = 1;
        }

    }


}

void process_Event11(ifstream& stats, Info& info, int MaxHP, int MaxLV, int count)
{
    if (info.shaman > 0)        // check hiệu ứng xấu  
    {
        info.shaman--;

    }
    if (info.siren > 0)
    {
        info.siren--;

    }

    int n1;
    n1 = ((info.level + info.phoenixdown) % 5 + 1) * 3;
    int s1 = 99;
    int sum = 0;
    for (int i = 1; i <= n1; i++)
    {
        sum += s1;
        s1 -= 2;

    }
    info.hp += (sum % 100);  
   
    if (checkNT(info.hp))
    {
        info.hp++;
    }

    while (!checkNT(info.hp))
    {
        info.hp++;
    }
   
   
    if (info.hp >= MaxHP) info.hp = MaxHP;
  
    if (info.shaman > 0 && info.shaman - 1 == 0)
    {
        info.hp *= 5;
        if (info.hp >= MaxHP) info.hp = MaxHP;
        info.shaman = 0;

    }

    if (info.siren > 0 && info.siren - 1 == 0)
    {
        info.level = MaxLV;
        info.siren = 0;
    }

    if (info.ordinal == count)
    {
        if (info.hp > 0)
        {
            info.rescue = 1;
        }

    }
    
}

void process_Event12(ifstream& stats, Info& info, int MaxHP, int MaxLV, int count)
{
    if (info.shaman > 0)        // check hiệu ứng xấu  
    {
        info.shaman--;

    }
    if (info.siren > 0)
    {
        info.siren--;

    }
    if (info.hp == 1)
    {
        if (info.shaman > 0 && info.shaman - 1 == 0)
        {
            info.hp *= 5;
            if (info.hp >= MaxHP) info.hp = MaxHP;
            info.shaman = 0;

        }

        if (info.siren > 0 && info.siren - 1 == 0)
        {
            info.level = MaxLV;
            info.siren = 0;
        }
        return;
    }
        
    else
    {
        if (info.shaman > 0 && info.shaman - 1 == 0)
        {
            info.hp *= 5;
            if (info.hp >= MaxHP) info.hp = MaxHP;
            info.shaman = 0;

        }

        if (info.siren > 0 && info.siren - 1 == 0)
        {
            info.level = MaxLV;
            info.siren = 0;
        }
        info.hp = fibonacci(info.hp);
    }

    if (info.ordinal == count)
    {
        if (info.hp > 0)
        {
            info.rescue = 1;
        }

    }

}

void process_Event13(ifstream& stats, Info& info, int a, ifstream& mush, string x, int MaxHP, int MaxLV, int count)
{
    if (info.shaman > 0)        // check hiệu ứng xấu  
    {
        info.shaman--;

    }
    if (info.siren > 0)
    {
        info.siren--;

    }

    int soluong;                    // nhập dãy và xử lý dãy 13<ms>, chuẩn bị cho xét <ms>
    mush >> soluong;

    int dayso[100];
    int dayso3[100];
    int dayso4[100];
    for (int i = 0; i < soluong; i++)
    {
        mush >> dayso[i];
        dayso3[i] = dayso[i];
        dayso4[i] = dayso[i];
        mush.ignore(1000, ',');
    }  
    for (int i = 0; i < soluong; i++)            // xử lý các dãy số phụ cho các trường hợp riêng
    {
        if (dayso3[i] < 0) dayso3[i] = abs(dayso3[i]);
        dayso3[i] = (dayso3[i] * 17 + 9) % 257;
    }
    for (int i = 0; i < soluong; i++)          
    {
        if (dayso4[i] < 0)  dayso4[i] = abs(dayso4[i]);
        dayso4[i] = (dayso4[i] * 17 + 9) % 257;
    }

   
    int max = dayso[0], min = dayso[0], sochi_max = 0, sochi_min = 0;
    for (int i = 1; i < soluong; i++)
    {
        if (dayso[i] >= max)
        {
            max = dayso[i];
            sochi_max = i;
        }
        if (dayso[i] <= min)
        {
            min = dayso[i];
            sochi_min = i;
        }
    }

    int size_x = x.size();                  //xử lý <ms>
    int vitri = 0;
    while (vitri < size_x)
    {


        if (x[vitri] == '1')
        {
            info.hp = info.hp - (sochi_max + sochi_min);
            vitri++;
            if (info.hp < 1)
            {
                if (info.hp <= 0 && info.phoenixdown > 0)
                {
                    info.phoenixdown -= 1;
                    info.hp = MaxHP;

                }
                else if (info.hp <= 0 && info.phoenixdown <= 0)
                {
                    info.rescue = 0;
                    return;
                }
            }
            continue;
        }
        else if (x[vitri] == '2')
        {
            int mtx, mti, frag=0;
            for (int i = sochi_max + 1; i < soluong - 1; i++)
            {
                if (dayso[i] <= dayso[i + 1])
                {
                    mtx = -2, mti = -3;
                    info.hp -= (mtx + mti);
                    if (info.hp > MaxHP) info.hp = MaxHP;
                    if (info.hp <= 0 && info.phoenixdown > 0)
                    {
                        info.phoenixdown -= 1;
                        info.hp = MaxHP;

                    }
                    else if (info.hp <= 0 && info.phoenixdown <= 0) info.rescue = 0;
                    frag += 1;
                    break;
                }
                else continue;
            }
            for (int i = 0; i < sochi_max; i++)
            {
                if (dayso[i] >= dayso[i + 1])
                {
                    if (frag == 1)
                    {
                        break;
                    }
                    else
                    {
                        mtx = -2, mti = -3;
                        info.hp -= (mtx + mti);
                        if (info.hp > MaxHP) info.hp = MaxHP;
                        if (info.hp <= 0 && info.phoenixdown > 0)
                        {
                            info.phoenixdown -= 1;
                            info.hp = MaxHP;

                        }
                        else if (info.hp <= 0 && info.phoenixdown <= 0) info.rescue = 0;
                        frag += 1;
                        break;
                    }
                }
                else continue;
            }
            if (frag == 0)
            {
                info.hp -= (sochi_max + dayso[sochi_max]);
                if (info.hp > MaxHP) info.hp = MaxHP;
                if (info.hp <= 0 && info.phoenixdown > 0)
                {
                    info.phoenixdown -= 1;
                    info.hp = MaxHP;

                }
                else if (info.hp <= 0 && info.phoenixdown <= 0)
                {
                    info.rescue = 0;
                    return;
                }
            }
            vitri++;
            continue;
          
        }
        else if (x[vitri] == '3')
        {
            
            int MAX = dayso3[0], MIN = dayso3[0];
            int sochi_MAX = 0, sochi_MIN = 0;
            for (int i = 1; i < soluong; i++)
            {
                if (dayso3[i] > MAX)
                {
                    MAX = dayso3[i];
                    sochi_MAX = i;
                }
                if (dayso3[i] < MIN)
                {
                    MIN = dayso3[i];
                    sochi_MIN = i;
                }
            }
            info.hp = info.hp - (sochi_MAX + sochi_MIN);

            if (info.hp < 1)
            {
                if (info.hp <= 0 && info.phoenixdown > 0)
                {
                    info.phoenixdown -= 1;
                    info.hp = MaxHP;

                }
                else if (info.hp <= 0 && info.phoenixdown <= 0)
                {
                    info.rescue = 0;
                    return;
                }
            }
            else if (info.hp > MaxHP) info.hp = MaxHP;
            vitri++;
            
            continue;

        }
        else if (x[vitri] == '4')
        {
            int max2_3x, max2_3i;
            
            int mang4[3];
            for (int i = 0; i < 3; i++)
            {
                    mang4[i] = dayso4[i];
            }

            if (soluong < 2)
            {
                max2_3x = -5;
                max2_3i = -7;
                info.hp = info.hp - (max2_3i + max2_3x);
                if (info.hp > MaxHP) info.hp = MaxHP;
                if (info.hp <= 0 && info.phoenixdown > 0)
                {
                    info.phoenixdown -= 1;
                    info.hp = MaxHP;

                }
                else if (info.hp <= 0 && info.phoenixdown <= 0)
                {
                    info.rescue = 0;
                    return;
                }
            }
            else if (soluong == 2)
            {
                if (mang4[0] == mang4[1])
                {
                    max2_3x = -5;
                    max2_3i = -7;
                    info.hp = info.hp - (max2_3i + max2_3x);
                    if (info.hp > MaxHP) info.hp = MaxHP;
                    if (info.hp <= 0 && info.phoenixdown > 0)
                    {
                        info.phoenixdown -= 1;
                        info.hp = MaxHP;

                    }
                    else if (info.hp <= 0 && info.phoenixdown <= 0)
                    {
                        info.rescue = 0;
                        return;
                    }
                }
                else
                {
                    max2_3i = 1;
                    max2_3x = dayso4[max2_3i];
                    info.hp = info.hp - (max2_3i + max2_3x);
                }
            }
            else
            {
                int first = 0, second = -1;
                for (int i = 1; i < 3; i++) {
                    if (mang4[i] > mang4[first]) {
                        second = first;
                        first = i;
                    }
                    else if (mang4[i] != mang4[first] && (second == -1 || mang4[i] > mang4[second])) {
                        second = i;
                    }
                }

                max2_3i = second;

                if (max2_3i == -1)
                {
                    max2_3x = -5;
                    max2_3i = -7;
                    info.hp = info.hp - (max2_3i + max2_3x);
                    if (info.hp > MaxHP) info.hp = MaxHP;
                    if (info.hp <= 0 && info.phoenixdown > 0)
                    {
                        info.phoenixdown -= 1;
                        info.hp = MaxHP;

                    }
                    else if (info.hp <= 0 && info.phoenixdown <= 0)
                    {
                        info.rescue = 0;
                        return;
                    }
                }
                else
                {
                    max2_3x = dayso4[max2_3i];
                    info.hp = info.hp - (max2_3i + max2_3x);
                }
            }

            if (info.hp > MaxHP) info.hp = MaxHP;
            if (info.hp < 1)
            {
                if (info.hp <= 0 && info.phoenixdown > 0)
                {
                    info.phoenixdown -= 1;
                    info.hp = MaxHP;

                }
                else if (info.hp <= 0 && info.phoenixdown <= 0)
                {
                       info.rescue = 0;
                       return;
                }
            }
            vitri++;
            continue;

        }
        else return;
    }

    if (info.shaman > 0 && info.shaman - 1 == 0 && info.hp > 0)
    {
        info.hp *= 5;
        if (info.hp >= MaxHP) info.hp = MaxHP;
        info.shaman = 0;

    }

    if (info.siren > 0 && info.siren - 1 == 0 && info.hp > 0)
    {
        info.level = MaxLV;
        info.siren = 0;
    }
    if (info.ordinal == count)
    {
        if (info.hp > 0)
        {
            info.rescue = 1;
        }

    }
}

void process_Event15(ifstream& stats, Info& info, int MaxHP, int MaxLV, int count)
{
    if (info.shaman > 0)        // check hiệu ứng xấu  
    {
        info.shaman--;

    }
    if (info.siren > 0)
    {
        info.siren--;

    }

    

    if (info.remedy < 99)
    {
        info.remedy += 1;
        if (info.shaman > 0 && info.shaman - 1 == 0 && info.hp > 0)
        {
            info.hp *= 5;
            if (info.hp >= MaxHP) info.hp = MaxHP;
            info.shaman = 0;

        }

        if (info.siren > 0 && info.siren - 1 == 0 && info.hp > 0)
        {
            info.level = MaxLV;
            info.siren = 0;
        }
    }
    else info.remedy = 99;
     
    if (info.shaman != 0)
    {
        info.hp *= 5;
        if (info.hp >= MaxHP) info.hp = MaxHP;
        info.shaman = 0;
        info.remedy -= 1;
    }

    if (info.ordinal == count)
    {
        if (info.hp > 0)
        {
            info.rescue = 1;
        }

    }
}

void process_Event16(ifstream& stats, Info& info,int MaxHP, int MaxLV, int count)
{
    if (info.shaman > 0)        // check hiệu ứng xấu  
    {
        info.shaman--;

    }
    if (info.siren > 0)
    {
        info.siren--;

    }

    if (info.ordinal == count)
    {
        if (info.hp > 0)
        {
            info.rescue = 1;
        }

    }

    if (info.maidenkiss < 99)
    {
        
        if (info.shaman > 0 && info.shaman - 1 == 0 && info.hp > 0)
        {
            info.hp *= 5;
            if (info.hp >= MaxHP) info.hp = MaxHP;
            info.shaman = 0;

        }

        if (info.siren > 0 && info.siren - 1 == 0 && info.hp > 0)
        {
            info.level = MaxLV;
            info.siren = 0;

        }
        info.maidenkiss += 1;

    }
    else return;
    
    if (info.siren != 0)
    {
        info.level = MaxLV;
        info.maidenkiss -= 1;
        info.siren = 0;
    }
   
}

void process_Event17(ifstream& stats, Info& info, int MaxHP,int MaxLV, int count)
{
    if (info.shaman > 0)        // check hiệu ứng xấu  
    {
        info.shaman--;

    }
    if (info.siren > 0)
    {
        info.siren--;

    }


    if (info.phoenixdown < 99)
    {
        if (info.shaman > 0 && info.shaman - 1 == 0 && info.hp > 0)
        {
            info.hp *= 5;
            if (info.hp >= MaxHP) info.hp = MaxHP;
            info.shaman = 0;

        }
        if (info.siren > 0 && info.siren - 1 == 0 && info.hp > 0)
        {
            info.level = MaxLV;
            info.siren = 0;
        }
        info.phoenixdown += 1;
    }

    else info.phoenixdown = 99;

    if (info.ordinal == count)
    {
        if (info.hp > 0)
        {
            info.rescue = 1;
        }

    }
}

void process_Event18(ifstream& stats, Info& info, ifstream& merlin, int MaxHP, int MaxLV, int count)
{
    if (info.ordinal == count)
    {
        if (info.hp > 0)
        {
            info.rescue = 1;
        }

    }

    if (info.merlin >= 1) return;

    if (info.shaman > 0)        // check hiệu ứng xấu  
    {
        info.shaman--;

    }
    if (info.siren > 0)
    {
        info.siren--;

    }
    int sodong;
    merlin >> sodong;
    string mondo;
    int i = 1;
    while (i <= sodong)
    {
        merlin >> mondo;
        if (check(mondo) == 1)
        {
            if (info.hp > MaxHP - 2)
            {
                info.hp = MaxHP;
                info.merlin++;
                return;
            }
            else info.hp += 2;
            i++;
            continue;
        }
        else if (check(mondo) == 2)
        {
            if (info.hp > MaxHP - 3)
            {
                info.hp = MaxHP;
                info.merlin++;
                return;
            }
            else info.hp += 3;
            i++;
            continue;
        }
        else
        {
            i++;
            continue;

        }
  
    }
    info.merlin++;
    if (info.shaman > 0 && info.shaman - 1 == 0 && info.hp > 0)
    {
        info.hp *= 5;
        if (info.hp >= MaxHP) info.hp = MaxHP;
        info.shaman = 0;

    }

    if (info.siren > 0 && info.siren - 1 == 0 && info.hp > 0)
    {
        info.level = MaxLV;
        info.siren = 0;
    }
    

}

void process_Event19(ifstream& stats, Info& info, ifstream& asclepius, int MaxHP, int MaxLV, int count)
{
    if (info.ordinal == count)
    {
        if (info.hp > 0)
        {
            info.rescue = 1;
        }

    }

    if (info.asclepius >= 1)   return;

    if (info.shaman > 0)        // check hiệu ứng xấu  
    {
        info.shaman--;

    }
    if (info.siren > 0)
    {
        info.siren--;

    }

    int sodong;
    asclepius >> sodong;
    int socot;
    asclepius >> socot;
    int vatpham[100][100];
    for (int i = 0; i < sodong; i++)
    {
        for (int j = 0; j < socot; j++)
        {
            asclepius >> vatpham[i][j];
        }
    }
    for (int i = 0; i < sodong; i++)
    {
        int duoc_phep_lay = 0;
        for (int j = 0; j < socot; j++)
        {
            if (duoc_phep_lay == 3)   continue;
            else
            {
                if (vatpham[i][j] == 16)
                {
                    if (info.remedy == 99) { duoc_phep_lay++; continue; }
                    else
                    {
                        info.remedy++;
                        duoc_phep_lay++;
                        continue;
                    }
                }
                else if (vatpham[i][j] == 17)
                {
                    if (info.maidenkiss == 99) { duoc_phep_lay++; continue; }
                    else
                    {
                        info.maidenkiss++;
                        duoc_phep_lay++;
                        continue;
                    }
                }
                else if (vatpham[i][j] == 18)
                {
                    if (info.phoenixdown == 99) { duoc_phep_lay++; continue; }
                    else
                    {
                        info.phoenixdown++;
                        duoc_phep_lay++;
                        continue;
                    }
                }
                else continue;

            }

        }
    }
    info.asclepius++;
    if (info.shaman > 0 && info.shaman - 1 == 0 && info.hp > 0)
    {
        info.hp *= 5;
        if (info.hp >= MaxHP) info.hp = MaxHP;
        info.shaman = 0;

    }

    if (info.siren > 0 && info.siren - 1 == 0 && info.hp > 0)
    {
        info.level = MaxLV;
        info.siren = 0;
    }

    if (info.ordinal == count)
    {
        if (info.hp > 0)
        {
            info.rescue = 1;
        }

    }

}

int process_Event99(ifstream& stats, Info& info, int player, int MaxHP, int MaxLV)
{
    if (player == 1)
    {
        if (info.shaman > 0 && info.shaman - 1 == 0)
        {
            info.hp *= 5;
            if (info.hp >= MaxHP) info.hp = MaxHP;
            info.shaman = 0;

        }

        if (info.siren > 0 && info.siren - 1 == 0)
        {
            info.level = MaxLV;
            info.siren = 0;
        }
        info.level = 10;
        return 1;
    }
    else if (player == 2)
    {
        if (info.shaman > 0 && info.shaman - 1 == 0)
        {
            info.hp *= 5;
            if (info.hp >= MaxHP) info.hp = MaxHP;
            info.shaman = 0;

        }

        if (info.siren > 0 && info.siren - 1 == 0)
        {
            info.level = MaxLV;
            info.siren = 0;
        }
        if (info.level >= 8)
        {
            info.level = 10;
            return 1;

        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (info.shaman > 0 && info.shaman - 1 == 0)
        {
            info.hp *= 5;
            if (info.hp >= MaxHP) info.hp = MaxHP;
            info.shaman = 0;

        }

        if (info.siren > 0 && info.siren - 1 == 0)
        {
            info.level = MaxLV;
            info.siren = 0;
        }
        if (info.level == 10) return 1;
        else return 0;

    }

}

void adventureToKoopa(string file_input, int& HP, int& level, int& remedy, int& maidenkiss, int& phoenixdown, int& rescue) {

    // mở file để đọc bằng ifstream
    ifstream stats(file_input);

    // kiểm tra xem file đã được mở hay chưa
    if (!stats) {
        cout << "Cannot open file " << file_input << "\n";
        exit(1);
    }

    Info info   ( HP, level, remedy, maidenkiss, phoenixdown, rescue);
   
    stats >> info.hp;
    stats >> info.level;
    stats >> info.remedy;
    stats >> info.maidenkiss;
    stats >> info.phoenixdown;

/*
Vì ta khó có thể vừa đọc vừa xử lý các dữ liệu trong file cùng lúc được nên ta sẽ đọc hết file 1 lượt rồi xử lý sau.

Ta nhận thấy ở dòng sự kiện, số sự kiện là không xác định được nên ta sẽ chuyển dòng này vào 1 istringstream, sau đó từ istringstream 
truyền vào info_event cho trước để xét trường hợp, khi gặp sự kiện yêu cầu đọc dòng 3 (tên file), ta sẽ lại đọc từ file ra bằng ifstream.

Về cơ bản, ta vẫn có thể để dòng 2 đọc bằng ifs, dòng 3 cho vào iss. Tuy nhiên khi ấy, vì file đọc lần lượt từ trên xuống, mà số sự kiện
ở dòng 2 là không xác định được nên ta chưa thể cho dòng 3 vào iss ngay được.

*/
  
    string line;                            // tạo iss và biến dòng 2 thành iss
    stats.ignore(1000, '\n');
    getline(stats, line);  
    istringstream iss (line);

    int count=0;
    
    for (int i = 0; i < line.size(); i++)
    {      
        if (line[i]==' ')
        {
            ++count;            
        }      
    }
    ++count;
      
    getline(stats, info.file_name);            // chuyển dòng 3 vào 1 string rồi xử lý để lấy tên file
    size_t pos = 0;
    int a = 0;
    while (a<3)
    {
        pos = info.file_name.find(",");

        if (pos != std::string::npos)
        {
            info.name[a] = info.file_name.substr(0, pos);

            a++;
            info.file_name.erase(0, info.file_name.find("," ) + 1);

        }
        else
        {
            info.name[a]=info.file_name;
            break;
            
        }
    }
    
   
    int MaxHP = HP;
    int MaxLV = level;
    
    // check xem người chơi là ai
    int player = Player(info.hp);   
  
        while (iss >> info.event)               // từ iss của dòng 2 đã có bắt đầu đọc từng giá trị 
        {
           
            if (info.hp <= 0)
            {
                rescue = -1;              
                break;

            }
            int type;
            

            info.rescue = -1;
            
            // bắt đầu hành trình
           

            if (info.event == "0")
            {
                rescue = 1;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                break;
            }
            if (info.event == "1")
            {
                type = 1;
                processEvent1_5(info, type, MaxHP, MaxLV, player, count);
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        
            }
            if (info.event == "2")
            {
                type = 2;
                processEvent1_5(info, type, MaxHP, MaxLV, player, count);
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
               
            }
            if (info.event == "3")
            {
                type = 3;
                processEvent1_5(info, type, MaxHP, MaxLV, player, count);
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
               
            }
            if (info.event == "4")
            {
                type = 4;
                processEvent1_5(info, type, MaxHP, MaxLV, player, count);
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
               
            }
            if (info.event == "5")
            {
                type = 5;
                processEvent1_5(info, type, MaxHP, MaxLV, player, count);
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
              
            }
            if (info.event == "6")
            {
                process_Event6(stats, info, MaxHP, MaxLV, player, count);
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
               
            }
            if (info.event == "7")
            {
                process_Event7(stats, info, MaxLV, MaxHP, player, count);
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);    
                
            }
            if (info.event == "11")
            {
                process_Event11(stats, info, MaxHP, MaxLV, count);
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
               
            }
            if (info.event == "12")
            {
                process_Event12(stats, info, MaxHP, MaxLV, count);
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            }

            /*
            Ở đây ta gặp sự kiện 13 trong đó có yêu cầu đọc dòng 3 để xử lý tiếp, vì thế lúc này ta bắt đầu đọc dòng 3 bằng ifs

            Ta có thể "ăn gian" cách mở file 1 chút: Vì dòng 3 ta biết được số lượng file tối đa, hơn nữa mỗi file đều có tên khác
            nhau, ta chỉ cần đọc toàn bộ dòng 3 vào 1 string, tìm ra kí tự đặc trưng từ mỗi file rồi cắt string là sẽ tìm được tên file


            */

            if (info.event.size() > 2)
            {
                string x = info.event.substr(info.event.find("13") + 2);     //cắt chuỗi string cho TH 13
                int a = x.size();

                for (int i = 0; i < 3; i++)
                {
                    if (info.name[i].find("mus") != std::string::npos)
                    {
                        ifstream mush(info.name[i]);

                        if (!mush) {
                            std::cerr << "Cannot open file " << info.name[i] << "\n";
                            exit(1);
                        }
                        process_Event13(stats, info, a, mush, x, MaxHP, MaxLV, count);
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                       
                        mush.close();
                    }
                    else continue;

                }
            }
            if (info.event == "15")
            {
                process_Event15(stats, info, MaxHP, MaxLV, count);
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
               
            }
            if (info.event == "16")
            {
                process_Event16(stats, info, MaxHP, MaxLV, count);
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            }
            if (info.event == "17")
            {
                process_Event17(stats, info, MaxHP, MaxLV, count);
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
            }
            if (info.event == "18")
            {
                for (int i = 0; i < 3; i++)
                {
                    if (info.name[i].find("mer") != std::string::npos)
                    {
                        ifstream merlin(info.name[i]);

                        if (!merlin) {
                            std::cerr << "Cannot open file " << info.name[i] << "\n";
                            exit(1);
                        }

                        process_Event18(stats, info, merlin, MaxHP, MaxLV, count);
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                       
                        merlin.close();
                    }
                    else continue;
                    
                }
                 
                

            }
            if (info.event == "19")
            {

                for (int i = 0; i < 3; i++)
                {
                    if (info.name[i].find("ius") != std::string::npos)
                    {
                        ifstream asclepius(info.name[i]);

                        if (!asclepius) {
                            std::cerr << "Cannot open file " << info.name[i] << "\n";
                            exit(1);
                        }

                        process_Event19(stats, info, asclepius, MaxHP, MaxLV, count);
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                        
                        asclepius.close();
                    }
                    else continue;

                }
        }
            if (info.event == "99")
            {
                int a = process_Event99(stats, info, player, MaxHP, MaxLV);
                if (rescue == 1) continue;
                else 
                {
                    if (info.ordinal == count)
                    {
                        if (info.hp > 0)
                        {
                            info.rescue = 1;
                        }

                    }
                    else
                    {
                        if (a == 1)
                        {
                            rescue = 1;
                            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                        }
                        else
                        {
                            rescue = 0;
                            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                            break;
                        }

                    }
                }
               
                
            }

            // xử lý hiệu ứng (loại bỏ hiệu ứng xấu)
            if (info.shaman > 0 && info.shaman - 1 == 0)
            {
                info.hp *= 5;
                if (info.hp >= MaxHP) info.hp = MaxHP;
                info.shaman = 0;

            }

            if (info.siren > 0 && info.siren - 1 == 0)
            {
                info.level = MaxLV;
                info.siren = 0;
            }
           
            info.ordinal++;
       
            
        }

}
