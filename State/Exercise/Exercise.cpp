#include <vector>
#include <string>
using namespace std;

struct CombinationLock {
    vector<int> pass;
    vector<int> curr;
    int curr_dig{0};
    string status{"LOCKED"};

    CombinationLock(vector<int> a) : pass(a) {
        curr.resize(pass.size());
    }

    void enter_digit(int a) {
        if(curr_dig == 0) status = "";
        curr[curr_dig++] = a;
        if(curr_dig == pass.size()) {
            check_pass();
            return;
        }
        status += to_string(a);
    }

    void check_pass() {
        for(int i = 0; i < pass.size(); i++){
            if(pass[i] != curr[i]) {
                status = "ERROR";
                return;
            }
        }
        status = "OPEN";
    }
};

