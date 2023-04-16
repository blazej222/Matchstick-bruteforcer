//0110000 - 1
//1101110 - 2
//1111010 - 3
//0110011 - 4
//1011011 - 5
//1011111 - 6
//1110000 - 7
//1111111 - 8
//1111011 - 9
//1111101 - 0

/*
Zabierasz z pierwszej ustawiasz w drugiej - pierwsza ∈ {6,7,8,9} 6->5, 7->1, 8->0_6_9, 9->5	druga ∈ {1,3,4,5,6,9,0} 3->9, 4->9 5->9, 6->8, 9->8 1->7
zabierasz z drugiej ustawiasz w pierwszej pierwsza ∈ {1,3,5,6,9,0} 3->9, 5->9, 6->8, 9->8 1->7	druga ∈ {6,7,8,9} 6->5, 7->1, 8->0_6_9, 9->5
Pierwsze dwa to jedna funckja tylko se odwracasz argumenty

zabierasz z pierwszej ustawiasz znak pierwsza ∈ {6,7,8,9} 6->5, 7->1, 8->0_6_9, 9->5
zabierasz z drugiej ustawiasz znak druga ∈ {6,7,8,9} 6->5, 7->1, 8->0_6_9, 9->5
również przemienne argumenty

zabierasz z pierwszej ustawiasz w pierwszej
zabierasz z drugiej ustawiasz w drugiej


--------- dla 2 ----- (niekompletne)
 Zabierasz dwa z pierwszej ustawiasz w pierwszej
 Zabierasz dwa z pierwszej ustawiasz w drugiej
 Zabierasz jedno z pierwszej ustawiasz w drugiej i jedno z drugiej ustawiasz w pierwszej
 Zabierasz jedno z pierwszej i ustawiasz znak na plus
*/
#include <iostream>
#include <string>
using namespace std;

class BadNumberException : public std::exception 
{
public:
    const char* what() {
        return "Exception1";
    }
};

class CustomString : public string
{
    public:
    void removeSpaces()
    {
        for(int i = 0;i<this->length();i++){
            size_t stringpos = this->find(" ");
            if(stringpos == string::npos) return;
            this->erase(stringpos,1);
        }
    }
};

class Equation {
public:
    enum modifier{
        NUM1PLUS,
        NUM2PLUS,
        NUM1MINUS,
        NUM2MINUS,
        SOLUTIONPLUS,
        SOLUTIONMINUS,
        NUM1TO2,
        NUM2TO1,
        NUM1TOSOL,
        NUM2TOSOL,
        NUM1TO1,
        NUM2TO2,
        SOLTONUM1,
        SOLTONUM2
    };

    bool num1[7] = { 0,0,0,0,0,0,0 }; // states representing digit as in sevseg display
    bool num2[7] = { 0,0,0,0,0,0,0 };
    bool solution[7] = { 0,0,0,0,0,0,0 };
    bool sign = true; // true = +, false = -

    int digitToNumber(bool num[]) {
        int tmp = 0;
        for (int i = 0; i < 7; i++) {
            if (num[i]) tmp = (tmp << 1) | 1; //set 1 if present
            else tmp = (tmp << 1); // 0 otherwise
        }
        switch (tmp) {
        case 0B0110000:
            return 1;
            break;
        case 0B1101110:
            return 2;
            break;
        case 0B1111010:
            return 3;
            break;
        case 0B0110011:
            return 4;
            break;
        case 0B1011011:
            return 5;
            break;
        case 0B1011111:
            return 6;
            break;
        case 0B1110000:
            return 7;
            break;
        case 0B1111111:
            return 8;
            break;
        case 0B1111011:
            return 9;
            break;
        case 0B1111101:
            return 0;
            break;
        default:
            return -1;
            break;
        }
    }

    void numberToDigit(int num, bool result[]) { //converts number from input to array of matches sign
        int tmp = 0;
        switch (num) {
        case 1:
            tmp = 0B0110000;
            break;
        case 2:
            tmp = 0B1101110;
            break;
        case 3:
            tmp = 0B1111010;
            break;
        case 4:
            tmp = 0B0110011;
            break;
        case 5:
            tmp = 0B1011011;
            break;
        case 6:
            tmp = 0B1011111;
            break;
        case 7:
            tmp = 0B1110000;
            break;
        case 8:
            tmp = 0B1111111;
            break;
        case 9:
            tmp = 0B1111011;
            break;
        case 0:
            tmp = 0B1111101;
            break;
        default:
            tmp = -1;
            break;
        }
        if (tmp == -1) throw BadNumberException();
        for (int i = 6; i >= 0; i--) {
            result[i] = tmp & 1;
            tmp = tmp >> 1;
        }
    }

    bool solveEquation(int num11,int num22,int sol) {
        //int sol = digitToNumber(solutionn); // convert it to number
        if (sign) { //if we have addition
            if (num11 + num22 == sol) { // 1+2=sol
                cout << num11 << " + " << num22 << " = " << sol << endl; //print end result
                return true;
            }
        }
        else {
            if (num1 - num2 == sol) return true; //1-2 = sol
            //else if (num2 - num1 == sol) return true; // 2-1 = sol
        }
        return false;
    }

    void printMessage(modifier mod){
        switch(mod){
            case NUM1TO2:
                cout << "Changed first number with the second number" <<endl;
                break;
            case NUM2TO1:
                cout << "Changed second number with the first number" <<endl;
                break;
            case NUM1TOSOL:
                cout <<"Changed first number with the solution" << endl;
                break;
            case NUM2TOSOL:
                cout <<"Changed second number with the solution" << endl;
                break;
            case SOLTONUM1:
                cout << "Changed solution with the first number" <<endl;
                break;
            case SOLTONUM2:
                cout << "Changed solution with the second number" <<endl;
                break;
            case NUM1TO1:
                cout <<"Changed first number with the first number" << endl;
                break;
            case NUM2TO2:
                cout <<"Changed second number with the second number" << endl;
                break;
            case NUM1PLUS:
                cout << "Changed first number with the operation sign" <<endl;
                break;
            case NUM2PLUS:
                cout << "Changed second number with the operation sign" <<endl;
                break;
            case SOLUTIONPLUS:
                cout <<"Changed solution with the operation sign" << endl;
                break;
            case NUM1MINUS:
                cout << "Changed first number with the operation sign" <<endl;
                break;
            case NUM2MINUS:
                cout << "Changed second number with the operation sign" <<endl;
                break;
            case SOLUTIONMINUS:
                cout <<"Changed solution with the operation sign" << endl;
                break;
            default:
                cout << "Unexpected" <<endl;
                break;
        }
    }

    bool takeOneAndAdd(bool num11[], bool num22[],modifier mod) {
        for (int i = 0; i < 7; i++) {
            if (num11[i]) { //find any segment that is set
                num11[i] = false; // take it
                if (digitToNumber(num11) == -1) { // if number created is incorrect
                    num11[i] = true; //return previous value
                    continue; //continue the loop in other iteration
                }
                for (int j = 0; j < 7; j++) { 
                    if (!num22[j]) { //find any segment in second that is not set
                        num22[j] = true; // set it
                        if (digitToNumber(num22) == -1) { //check if second number created is incorrect
                            num22[j] = false; // return preview value
                            continue; // continue with the loop
                        } 
                        //at this point we should have two valid values - lets solve it!

                        bool solres = false;
                        if(mod == NUM1TO2 || mod ==NUM2TO1)solres = solveEquation(digitToNumber(num11), digitToNumber(num22), digitToNumber(solution));
                        else if(mod == NUM1TOSOL) solres = solveEquation(digitToNumber(num1),digitToNumber(num22),digitToNumber(num11)); // means we're swapping num1 for solution, so num1 +- (changed)num2 = (changed)solution
                        else if(mod == NUM2TOSOL) solres = solveEquation(digitToNumber(num11),digitToNumber(num2),digitToNumber(num22)); //we're swapping num2 for a solution
                        else if(mod == NUM1TO1) solres = solveEquation(digitToNumber(num22),digitToNumber(num2),digitToNumber(solution));
                        else if(mod == NUM2TO2) solres = solveEquation(digitToNumber(num1),digitToNumber(num22),digitToNumber(solution));
                        if (solres) {
                            printMessage(mod);
                            cout << i << " => " << j << endl; //prints which was taken and added
                            return true;
                        }
                        num22[j] = false; //if not solved then set back 
                        continue;
                    } 
                }
                // if the first number was correct but it didnt make a proper equation with second
                num11[i] = true; // return previous state
            }
            //cout << "ok" << endl;
        }
        return false; //we've tried all combinations and none made sense
    }

        bool takeOneAndChangeSignToPlus(bool num11[], modifier mod) {
        if(sign) return false;
        for (int i = 0; i < 7; i++) {
            if (num11[i]) { //find any segment that is set
                num11[i] = false; // take it
                if (digitToNumber(num11) == -1) { // if number created is incorrect
                    num11[i] = true; //return previous value
                    continue; //continue the loop in other iteration
                }
                sign = true; //change equation sign
                //at this point we should have two valid numbers - lets solve it!
                bool solres = false;
                if(mod == NUM1PLUS) solres = solveEquation(digitToNumber(num11), digitToNumber(num2),digitToNumber(solution));
                else if (mod == NUM2PLUS) solres = solveEquation(digitToNumber(num1),digitToNumber(num11),digitToNumber(solution));
                else if(mod == SOLUTIONPLUS) solres = solveEquation(digitToNumber(num1),digitToNumber(num2),digitToNumber(num11));
                if (solres) {
                    printMessage(mod);
                    cout << i << " => " << "+" << endl; //prints which was taken and added
                    return true;
                }
                // if the first number was correct but it didnt make a proper equation with changed sign
                num11[i] = true; // return previous state
                sign = false; //return previous sign
                continue;
            } 
        }
        return false; //we've tried all combinations and none made sense

    }

    bool changeSignToMinusAndAddOne(bool num22[], modifier mod){
        if(!sign) return false;
        for (int j = 0; j < 7; j++) { 
            if (!num22[j]) { //find any segment in second that is not set
                num22[j] = true; // set it
                if (digitToNumber(num22) == -1) { //check if second number created is incorrect
                    num22[j] = false; // return preview value
                    continue; // continue with the loop
                } 
                //at this point we should have two valid values - lets solve it!
                sign = false;
                bool solres = false;
                if(mod == NUM1MINUS) solres = solveEquation(digitToNumber(num22), digitToNumber(num2),digitToNumber(solution));
                else if (mod == NUM2MINUS) solres = solveEquation(digitToNumber(num1),digitToNumber(num22),digitToNumber(solution));
                else if(mod == SOLUTIONMINUS) solres = solveEquation(digitToNumber(num1),digitToNumber(num2),digitToNumber(num22));
                if (solres) {
                    printMessage(mod);
                    cout << j << " => " << "-" << endl; //prints which was taken and added
                    return true;
                }
                num22[j] = false;
                sign = true;
                continue;
            }
            // if the first number was correct but it didnt make a proper equation with second
            //num22[j] = false; 
            sign = true;
        }         
        //cout << "ok" << endl;
        return false; //we've tried all combinations and none made sense       
    }
 

    bool solve() {
        if (takeOneAndAdd(num1, num2,NUM1TO2)) return true; //first with second
        if (takeOneAndAdd(num2, num1,NUM2TO1)) return true; //second with first
        if (takeOneAndAdd(num1,solution,NUM1TOSOL)) return true; //firt with solution
        if (takeOneAndAdd(num2,solution,NUM2TOSOL)) return true; // second with solution
        if (takeOneAndAdd(solution,num1,SOLTONUM1)) return true; //solution with first
        if (takeOneAndAdd(solution,num2,SOLTONUM2)) return true;
        if(takeOneAndAdd(num1,num1,NUM1TO1)) return true;
        if(takeOneAndAdd(num2,num2,NUM2TO2)) return true;
        //----------------------------------
        if(takeOneAndChangeSignToPlus(num1,NUM1PLUS)) return true;
        if(takeOneAndChangeSignToPlus(num2,NUM2PLUS)) return true;
        if(takeOneAndChangeSignToPlus(solution,SOLUTIONPLUS)) return true;
        //----------------------------------
        if(changeSignToMinusAndAddOne(num1,NUM1MINUS)) return true;
        if(changeSignToMinusAndAddOne(num2,NUM2PLUS)) return true;
        if(changeSignToMinusAndAddOne(solution,SOLUTIONMINUS)) return true;
        //takeOneAndAdd(num1, num2);
        return false;
    }
    bool convertFromInput(CustomString str){
        // TODO: write this method
    }
};

int main()
{

    Equation a;
    /*
    CustomString input;
    cin >> input;
    input.removeSpaces();
    */
    a.numberToDigit(5, a.num1);
    a.numberToDigit(5, a.num2);
    a.numberToDigit(8, a.solution);
    a.sign = false;
    // 5 + 5 = 8 => 5+3=8
    a.solve();
}
