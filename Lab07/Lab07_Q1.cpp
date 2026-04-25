#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

// 定義 Stack 的節點結構
struct Node {
    char data;  // 存儲字符 (運算子或括號)
    Node* next; // 指向下一個節點
};

// 使用 linked list 實作 Stack
class Stack {
private:
    Node* top; // 指向堆疊頂端
public:
    Stack() { top = nullptr; } // 初始化堆疊

    // Push 操作：將元素放入堆疊
    void push(char ch) {
        Node* newNode = new Node; // 創建新節點
        newNode->data = ch;       // 存入數據
        newNode->next = top;      // 讓新節點指向目前的頂端
        top = newNode;            // 更新頂端指標
    }

    // Pop 操作：移除並回傳頂端元素
    char pop() {
        if (isEmpty()) return '\0'; // 若堆疊為空，回傳空字符
        char ch = top->data;         // 取得頂端元素
        Node* temp = top;            // 暫存頂端節點
        top = top->next;             // 移動頂端指標
        delete temp;                 // 釋放記憶體
        return ch;                   // 回傳彈出的元素
    }

    // Peek 操作：取得頂端元素但不移除
    char peek() {
        return (top ? top->data : '\0');
    }

    // 判斷堆疊是否為空
    bool isEmpty() {
        return top == nullptr;
    }
};

// 判斷運算子(加減乘除) 的優先順序
int precedence(char op) {
    // 設定乘除的優先值為2，加減的優先值為1
    if (op == '*' or op == '/') {
        return 2;
    }
    else if (op == '+' or op == '-') {
        return 1;
    }
    else {
        return 0;
    }
}

// 將中序表達式 (infix) 轉換為後序表達式 (postfix)
void InfixToPostfix(const char* infix, char* postfix) {
    Stack s;
    int k = 0;

    for (int i = 0; i < strlen(infix); i ++) { // 遍歷每個infix 元素
        
        if (isalnum(infix[i])) {
            postfix[k++] = infix[i]; //如果是字母或數字就放到postfix 裡，然後K 往後一格
        }
        else if (infix[i] == '(') {
            s.push(infix[i]); // 把左括號放入stack 裡
        }
        else if (infix[i] == ')') {
            while (s.peek() != '(' && not s.isEmpty()) {
                postfix[k++] = s.pop(); // 如果是右括號，開始pop stack 裡的元素並放入postfix 裡，直到左括號為止
            }
            if (s.peek() == '(') s.pop(); // 把左括號pop 掉
        }
        else {
            // 處理operators
            // 如果stack 裡operator 的precedence 比infix 的operator 還要大，就放到postfix 裡
            while (not s.isEmpty() && precedence(s.peek()) >= precedence(infix[i])) {
                postfix[k++] = s.pop();
            }
            s.push(infix[i]); // 把目前的operator 放入stack
        }
    }
    while (not s.isEmpty()) {
        postfix[k++] = s.pop(); // 確保沒有任何operators 殘留在stack
    }
    postfix[k] = '\0'; // 避免印出亂碼
}

int main() {
    char infix[100], postfix[100];
    cout << "Enter an Infix expression: ";
    cin >> infix; // 輸入中序表達式

    InfixToPostfix(infix, postfix); // 轉換為後序表達式
    cout << "Postfix expression: " << postfix << endl; // 輸出後序表達式

    return 0;
}

