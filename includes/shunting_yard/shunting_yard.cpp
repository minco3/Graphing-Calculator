#include "shunting_yard.h"

ShuntingYard::ShuntingYard() {
    queue;
}

ShuntingYard::ShuntingYard(const Queue<Token*>& input_q) {
    infix(input_q);
}

void ShuntingYard::infix(const Queue<Token*>& input_q) {
    queue = input_q;
}

// generate postfix queue from infix queue
Queue<Token*> ShuntingYard::postfix() {
    return shunting_yard();
}

Queue<Token*> ShuntingYard::postfix(const Queue<Token*>& input_q) {
    queue = input_q;
    return shunting_yard();
}

  // called by postfix() 
  Queue<Token*> ShuntingYard::shunting_yard() {
    const bool debug = true;
    Queue<Token*> input(queue), output;
    Stack<Token*> os; //operator stack
    while(!input.empty()) {
        switch(input.front()->TypeOf()) {
            case OPERATOR:
                while (!os.empty()) {
                    if (os.top()->TypeOf()==LPAREN) break;
                    else if (os.top()->TypeOf()==FUNCTION||static_cast<Operator*>(input.front())->getOrder()<=static_cast<Operator*>(os.top())->getOrder()
                        &&static_cast<Operator*>(input.front())->getOperator()!="^") {
                        output.push(os.pop());
                    } else break;
                }
            case LPAREN:
                os.push(input.pop());
                break;
            case RPAREN:
                while ((os.top()->TypeOf())!=LPAREN) {
                    output.push(os.pop());
                }
                input.pop(); // removing rparen
                os.pop(); // removing lparen
                break;
            case FUNCTION:
                if (static_cast<Function*>(input.front())->getFunction()!="X") {
                    while (!os.empty()&&
                        os.top()->TypeOf()==FUNCTION
                        ||os.top()->TypeOf()!=LPAREN) {
                    output.push(os.pop());
                }
                os.push(input.pop());
                    break;
                }
            default:
                output.push(input.pop());
                break;
        }
        if (debug) {
            cout << "output: " << output << "input: " << input;
            if (!os.empty()) cout << "os: " << os;
            cout << endl;
        }
    }
                  
                   
    while(!os.empty()) {
        output.push(os.pop());
    }
    return output;
  }