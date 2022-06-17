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
    const bool debug = false;
    if (debug) std::cout << str << std::endl;
    Queue<Token*> infix;
    for (int i=0; i<str.length(); i++) {
        string word;
        switch (str[i]) {
            case '0' ... '9':
                while (str[i]>='0'&&str[i]<='9'){
                    word+=str[i++];
                }
                i--;
                infix.push(new Integer(stoi(word)));
                break;
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                word += str[i];
                if (debug) std::cout << word << std::endl;
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
                while ((str[i]>='a'&&str[i]<='z')||(str[i]>='A'&&str[i]<='Z')) {
                    word+=str[i++];
                }
                i--;
                infix.push(new Function(word));
                break;
            default:
                break;
        }
        if (debug) std::cout << infix; 
    }
    return infix;
}

#endif //STR_TO_INFIX