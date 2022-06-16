#ifndef STR_TO_INFIX_H
#define STR_TO_INFIX_H

#include <string>

#include "../queue/MyQueue.h"
#include "../stack/MyStack.h"
#include "../token/token.h"
#include "../token/function.h"
#include "../token/integer.h"
#include "../token/operator.h"
#include "../token/leftparen.h"
#include "../token/rightparen.h"

Queue<Token*> strToInfix(string str) {
    Queue<Token*> infix;
    for (int i=0; i<str.length(); i++) {
        string word;
        switch (str[i]) {
            case '0' ... '9':
                while (str[i]>='0'&&str[i]<='9'){
                    word+=str[i];
                    i++;
                }
                infix.push(new Integer(stoi(word)));
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                word += str[i];
                infix.push(new Operator(word));
                break;
            case '(':
                infix.push(new LeftParen);
                break;
            case ')':
                infix.push(new RightParen);
                break;
            case 'a' ... 'z':
            case 'A' ... 'Z':
                if (str[i] == 'X') infix.push(new Function("X"));       
                while ((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z')) {
                    word+=str[i];
                    i++;
                }
                infix.push(new Function(word));
                break;
        } 
    }
    return infix;
}

#endif //STR_TO_INFIX