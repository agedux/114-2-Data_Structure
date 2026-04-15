#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;


// 表示單張撲克牌的類別
class Card {
public:
    string colors; // 儲存撲克牌的花色
    string rank; // 儲存撲克牌的數值

    // 建立 constructor來初始化物件,當 Card 物件建立時,它會自動執行這個函式,並把 s 和 r 的值存入colors 和 rank
    Card(string s, string r) : colors(s), rank(r) {} 
    
    void display() const { // 顯示撲克牌的資訊
        cout << rank << " of " << colors << endl;
    }
};

// 實作 Stack
class Stack {
private:
    vector<Card> stack; // 表示 stack 是一個能存放 Card 類別物件的 vector

public:
    void push(const Card& card) {
        stack.push_back(card); // 將打亂的牌放入stack
    }

    Card pop() {
        if (!isEmpty()) {
            Card topcard = stack.back(); // 變數topcard 儲存上面第一張牌。back() 是std::vector 中取得最後一個元素的用法
            stack.pop_back(); // 將上面第一張牌從stack 中刪除
            topcard.display(); // 利用display 函式印出topcard
            return topcard;
        }
        return Card("", ""); // 若stack 為空，則回傳一張無數值的空牌
    }

    bool isEmpty() const {
        return stack.empty(); // 檢查stack 是否為空並回傳
    }
};

// 代表一副撲克牌的類別
class Deck {
private:
    vector<Card> cards; // 存放未洗牌的撲克牌
    Stack shuffledDeck; // 存放洗過的牌,用實作的 stack 來管理

public:
    Deck() { // 建立 constructor 來初始化物件
        string colors[] = { "Hearts", "Diamonds", "Clubs", "Spades" }; // 儲存撲克牌的花色
        
        string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9","10", "J", "Q", "K", "A" }; // 儲存撲克牌的數值

        // 利用迴圈將 52 張牌加入 cards 這個 vector 裡面
        for (int i = 0; i < 4; i++) { // 四種花色
            for (int j = 0; j < 13; j++) { // 13 種點數
                cards.push_back(Card(colors[i], ranks[j]));
            }
        }
    }

    // 洗牌(Hint:使用 shuffle 函數)
    void shuffleDeck() {
        random_device rd; // 取得種子
        mt19937 g(rd()); // 產生隨機數產生器
        shuffle(cards.begin(), cards.end(), g); // 將vector 打亂

        for (int i = 0; i < cards.size(); i++) {
            shuffledDeck.push(cards[i]); // 洗好的牌一張一張放入stack
        }
    }

    // 發牌 pop
    void drawAllCards() {
        for (int i = cards.size(); i > 0; i--) {
            shuffledDeck.pop(); // 牌一張一張從stack 發出
        }
    }
};


int main() {
    Deck deck; // 建立 deck 產生 52 張撲克牌
    deck.shuffleDeck(); // 進行洗牌並放入堆疊
    cout << "Shuffled deck:" << endl;
    deck.drawAllCards(); // 依序取出堆疊內的牌並顯示
    return 0;
}
