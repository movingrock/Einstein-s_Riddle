#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int house[5][5]; // 앞쪽은 집 번호, 뒷쪽은 enum Hint에 들어간 힌트 순서
int node = 0; // 연산이 끝날때까지 사용한 노드 수

enum Hint{COLOR, NATIONALITY, BEVERAGE, CIGAR, PET};
enum Color{BLUE, GREEN, RED, WHITE, YELLOW};
enum Nationality{BRIT, DANE, GERMAN, NORWEGIAN, SWEDE};
enum Beverage {BEER, COFFEE, MILK, TEA, WATER};
enum Cigar {BLUE_MASTER, DUNHILL, PALL_MALL, PRINCE, BLEND};
enum Pet {CAT, BIRD, DOG, FISH, HORSE};

// house 배열에 할당된 값을 문자로 바꿈.
string intToLetter(int j, int num) {
    string letter = "";

    switch (j) {
    case 0:
        switch (num)
        {
        case 0: letter = "BLUE"; break;
        case 1: letter = "GREEN"; break;
        case 2: letter = "RED"; break;
        case 3: letter = "WHITE"; break;
        case 4: letter = "YELLOW"; break;
        }
        break;
    case 1:
        switch (num)
        {
        case 0: letter = "BRIT"; break;
        case 1: letter = "DANE"; break;
        case 2: letter = "GERMAN"; break;
        case 3: letter = "NORWEGIAN"; break;
        case 4: letter = "SWEDE"; break;
        }
        break;
    case 2:
        switch (num)
        {
        case 0: letter = "BEER"; break;
        case 1: letter = "COFFEE"; break;
        case 2: letter = "MILK"; break;
        case 3: letter = "TEA"; break;
        case 4: letter = "WATER"; break;
        }
        break;
    case 3:
        switch (num)
        {
        case 0: letter = "BLUE_MASTER"; break;
        case 1: letter = "DUNHILL"; break;
        case 2: letter = "PALL_MALL"; break;
        case 3: letter = "PRINCE"; break;
        case 4: letter = "BLEND"; break;
        }
        break;
    case 4:
        switch (num)
        {
        case 0: letter = "CAT"; break;
        case 1: letter = "BIRD"; break;
        case 2: letter = "DOG"; break;
        case 3: letter = "FISH"; break;
        case 4: letter = "HORSE"; break;
        }
        break;
    }

    return letter;
}

// house배열과 연산 횟수를 출력
void Print() {
    cout << left << setw(8) << "NO." << setw(15) << "COLOR" << setw(15) << "NATIONALITY" << setw(15) << "DRINK" << setw(15) << "CIGAR" << setw(15) << "PET" << endl;
    for (int i = 0; i < 5; i++) {
        cout << i + 1 << "번 집: ";
        for (int j = 0; j < 5; j++)
        {
            cout << left << setw(15) << intToLetter(j,house[i][j]);
        }
        cout << endl;
    }
    cout << endl <<"연산에 사용된 Node 수: " << node << endl;
}

// 백트랙킹이 계속 돌면서 IsHint()에서 값의 참 거짓을 확인함.
bool IsHint() {
    // 같은 값이 들어가 있으면 false를 return 함.
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            for (int k = i + 1; k < 5; ++k)
                if (house[i][j] == house[k][j] && house[i][j] != -1 && house[k][j] != -1)
                    return false;
        }
    }

    // 주어진 15개의 힌트를 검사함.
    for (int i = 0; i < 5; i++) {
        //1)  The Brit lives in a redhouse.
        if (house[i][NATIONALITY] == BRIT && house[i][COLOR] != RED && house[i][COLOR] != -1) return false;

        //2)  The Swede keeps dogs as pets.
        if (house[i][NATIONALITY] == SWEDE && house[i][PET] != DOG && house[i][PET] != -1) return false;

        //3)  The Dane drinks tea.
        if (house[i][NATIONALITY] == DANE && house[i][BEVERAGE] != TEA && house[i][BEVERAGE] != -1) return false;

        //4)  The green house is on the left of the white house(next to it).
        if (i < 4 && house[i][COLOR] == GREEN && house[i + 1][COLOR] != WHITE && house[i + 1][COLOR] != -1) return false;

        //5)  The green house owner drinks coffee.
        if (house[i][COLOR] == GREEN && house[i][BEVERAGE] != COFFEE && house[i][BEVERAGE] != -1) return false;

        //6)  The person who smokes Pall Mall rears birds.
        if (house[i][CIGAR] == PALL_MALL && house[i][PET] != BIRD && house[i][PET] != -1) return false;

        //7)  The owner of the yellow house smokes Dunhill.
        if (house[i][COLOR] == YELLOW && house[i][CIGAR] != DUNHILL && house[i][CIGAR] != -1) return false;

        //8)  The man living in the house right in the center drinks milk.
        if (house[2][BEVERAGE] != MILK && house[2][BEVERAGE] != -1) return false;

        //9)  The Norwegian lives in the first(leftmost) house.
        if (house[0][NATIONALITY] != NORWEGIAN && house[0][NATIONALITY] != -1) return false;

        //10) The man who smokes Blend lives next to the one who keeps cats.
        if (house[i][CIGAR] == BLEND && !((i > 0 &&  (house[i - 1][PET] == CAT || house[i - 1][PET] == -1)) ||
            (i < 4 && (house[i + 1][PET] == CAT || house[i + 1][PET] == -1)))) return false;

        //11) The man who keeps horses lives next to the man who smokes Dunhill.
        if (house[i][PET] == HORSE && !((i > 0 &&  (house[i - 1][CIGAR] == DUNHILL || house[i - 1][CIGAR] == -1)) ||
            (i < 4 && (house[i + 1][CIGAR] == DUNHILL || house[i + 1][CIGAR] == -1)))) return false;

        //12) The owner who smokes Blue Master drinks beer.
        if (house[i][CIGAR] == BLUE_MASTER && house[i][BEVERAGE] != BEER && house[i][BEVERAGE] != -1) return false;

        //13) The German smokes Prince.
        if (house[i][NATIONALITY] == GERMAN && house[i][CIGAR] != PRINCE && house[i][CIGAR] != -1) return false;

        //14) The Norwegian lives next to the blue house.
        if (house[i][NATIONALITY] == NORWEGIAN && !((i > 0 &&  (house[i - 1][COLOR] == BLUE || house[i - 1][COLOR] == -1)) ||
            (i < 4 && (house[i + 1][COLOR] == BLUE || house[i + 1][COLOR] == -1)))) return false;

        //15) The man who smokes Blend has a neighbor who drinks water.
        if (house[i][CIGAR] == BLEND && !((i > 0 &&  (house[i - 1][BEVERAGE] == WATER || house[i - 1][BEVERAGE] == -1)) ||
            (i < 4 && (house[i + 1][BEVERAGE] == WATER || house[i + 1][BEVERAGE] == -1)))) return false;
    }
    return true;
}

// house[0][0]부터 검사해서 house[4][4]까지 검사함.
//
bool Einsteins_riddle(int houseNo, int hint){
    node++; // 함수가 실행될때마다 노드 개수를 하나씩 추가함.
    for (int i = 0; i < 5; i++) {
        house[houseNo][hint] = i;
        if (IsHint()) {
            int newHouseNo = (houseNo + 1) % 5;
            int newHint = hint;
            if (newHouseNo == 0) newHint += 1;
            if (newHint >= 5 || Einsteins_riddle(newHouseNo, newHint)) {
                return true;
            }
        }
    }
    house[houseNo][hint] = -1;
    return false;
}

// house배열에 -1로 초기화하고 Einsteins_riddle()함수를 실행시킴. 최종적으로 true를 반환하면 값을 출력함.
int main()
{
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            house[i][j] = -1;
        }
    }
    if (Einsteins_riddle(0, 0)) Print();
    return 0;
}