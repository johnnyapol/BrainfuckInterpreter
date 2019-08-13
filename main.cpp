#include <iostream>
#include <vector>
#include <fstream>

#include <stack>

class TuringMachine {
    private:
        int position;
        std::vector<char> tape;

    public:
        TuringMachine() {
            this->position = 0;
            this->tape.push_back((char)0);
        }

        void move_tape(int pos) {
            this->position += pos;

            if (this->position == tape.size()) {
                // Increase tape
                tape.push_back((unsigned char)0);
            }

            if (this->position == -1) {
                this->position = 0;
            }
        }

        char& get_cell() {
            return this->tape[this->position];
        }

        void print() const {
            for (const unsigned char& c: this->tape) {
                std::cout << "[" << (int)c << "]";
            }

            std::cout << std::endl;
        }
};

int main(int argc, char** argv) {
    if (argc == 1) {
        std::cout << "Usage: " << argv[0] << " <input file>" << std::endl;
        return EXIT_FAILURE;
    }

    char* input_file = argv[1];

    TuringMachine tm;

    std::fstream file(input_file);

    std::vector<char> input_vector; 

    char c;
    while ((file >> c)) {
        input_vector.push_back(c);
    }

    char* input = &input_vector[0];

    std::stack<char*> positions;

    for (; (*input); input++) {
        switch ((int)(*input)) {
            case (int)'>': {
                tm.move_tape(1);
                continue;
            }

            case (int)'<': {
                tm.move_tape(-1);
                continue;
            }

            case (int)'+': {
                tm.get_cell()++;
                continue;
            }

            case (int)'-': {
                tm.get_cell()--;
                continue;
            }

            case (int)'.': {
                std::cout << tm.get_cell();
                continue;
            }

            case (int)',': {
                std::cin >> tm.get_cell();
                continue;
            }

            case (int)'[': {
                if (tm.get_cell()  == 0) {
                  int lefts_needed = 1;
                    input++;
                    for (; lefts_needed > 0; input++) {
                        if (*input == '[') {
                            lefts_needed++;
                        }

                        if (*input == ']') {
                            lefts_needed--;
                        }
                    } 
                    input--;
                    continue;
                } else {
                    positions.push(input);
                }
                continue;
            }

            case (int)']': {
                if (tm.get_cell() != 0) {
                    input = positions.top();
                } else {
                    positions.pop();
                }
                continue;
            }

            default: {
                continue;
            }
        }
    }
    std::cout << std::endl << "Done." << std::endl;

    std::cout << "Printing out cells" << std::endl;
    tm.print();
    return EXIT_SUCCESS;
}
