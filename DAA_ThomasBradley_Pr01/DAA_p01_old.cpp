#include <iostream>
using namespace std;

class Strategy {
    public: 
	virtual void AlgorithmInterface(int v[]) = 0;
 };


class Numbers : public Strategy  {
    void AlgorithmInterface(int array[]) {
        cout << "Numeros: ";
        for (int i{0}; i < 9; i++) {
            cout << array[i] << ' ';
        }
        cout << endl;
    }
};


// A 'ConcreteStrategy' class
class Spanish : public Strategy  {
    void AlgorithmInterface(int array[]) {
        cout << "Español: ";
        for (int i{0}; i < 9; i++) {
            switch (array[i]) {
                case 0:
                    cout << "cero ";
                    break;
                case 1:
                    cout << "uno ";
                    break;
                case 2: 
                    cout << "dos ";
                    break;
                case 3: 
                    cout << "tres ";
                    break;
                case 4:
                    cout << "cuatro ";
                    break;
                case 5:
                    cout << "cinco ";
                    break;
                case 6: 
                    cout << "seis ";
                    break;
                case 7: 
                    cout << "siete ";
                    break;
                case 8: 
                    cout << "ocho ";
                    break;
                case 9: 
                    cout << "nueve ";
                    break;
            }
        }
        cout << endl;
    }
};

 
// A 'ConcreteStrategy' class
class English : public Strategy  {
    void AlgorithmInterface(int array[]) {
        cout << "English: ";
        for (int i{0}; i < 9; i++) {
            switch (array[i]) {
                case 0:
                    cout << "zero ";
                    break;
                case 1:
                    cout << "one ";
                    break;
                case 2: 
                    cout << "two ";
                    break;
                case 3: 
                    cout << "three ";
                    break;
                case 4:
                    cout << "four ";
                    break;
                case 5:
                    cout << "five ";
                    break;
                case 6: 
                    cout << "six ";
                    break;
                case 7: 
                    cout << "seven ";
                    break;
                case 8: 
                    cout << "eight ";
                    break;
                case 9: 
                    cout << "nine ";
                    break;
            }
        }
        cout << endl;
    }
};

class Context {
    private:
	 Strategy *_strategy;
    public:
         // Constructor
         Context(Strategy *strategy) {
            _strategy = strategy;
         }
         
         void setContext(Strategy *strategy) {
            _strategy = strategy;
         }

         void ContextInterface(int v[]) {
            _strategy -> AlgorithmInterface(v);
         }

};

int main () {
   const int kNum = 9;
   int array[kNum];
   time_t t;
   srand((unsigned) time(&t));
   cout << "Vector: ";
   for (int i{0}; i < kNum; i++) {
      array[i] = rand() % 9 + 1;
      cout << array[i] << ' '; 
   }
   cout << endl;

   Context *context;
   context = new Context(new Numbers());
   context->ContextInterface(array);
   context->setContext(new Spanish());
   context->ContextInterface(array);
   context->setContext(new English());
   context->ContextInterface(array);
}